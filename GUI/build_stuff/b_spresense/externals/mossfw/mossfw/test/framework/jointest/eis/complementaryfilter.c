/****************************************************************************
 * Copyright 2023 Sony Semiconductor Solutions Corporation
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossdsp.h"
#include "mossfw/mossfw_component.h"
#include "component.h"
#include "eis/eisallocator.h"
#include "eis/complementaryfilter.h"
#include "eis/eis.h"

#define PI 3.14159265358979323846f
#define COMPLEMENTARYFILTER_INPUTTYPE_GYR (MOSSFW_DATA_TYPE_FLOAT + \
                                          MOSSFW_DATA_TYPEGRP_V3 + \
                                          MOSSFW_DATA_TYPENAME_GYRO + \
                                          MOSSFW_DATA_TYPEARRAY_ARRAY)
#define COMPLEMENTARYFILTER_INPUTTYPE_Q (MOSSFW_DATA_TYPE_FLOAT + \
                                         MOSSFW_DATA_TYPEGRP_Q + \
                                          MOSSFW_DATA_TYPEARRAY_ARRAY)
#define COMPLEMENTARYFILTER_OUTPUTTYPE COMPLEMENTARYFILTER_INPUTTYPE_Q
#define MIN_GYR 23

static struct mossdsp_integrategyr_param_s integrateparam = {
    .lastout.f = {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    .dt = 3125,
    .res = {.tv_sec = 0, .tv_nsec = 100000},
    .scale_factor = 0.0f
};
static mossfw_data_qf_t accpose = {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
static unsigned int gyrcount = 0;
static int poseupdated = 1;
static mossfw_data_t *indatagyr = NULL;

static mossfw_data_qf_t normalize(mossfw_data_qf_t in)
{
    const float eps = 0.00100000005f;
    float norm;
    norm = sqrtf(in.w * in.w + in.x * in.x + in.y * in.y + in.z * in.z);
    if (eps < norm) {
        in.w = in.w * (1.0f / norm);
        in.x = in.x * (1.0f / norm);
        in.y = in.y * (1.0f / norm);
        in.z = in.z * (1.0f / norm);
    }
    return in;
}

static mossfw_data_qf_t slerp(mossfw_data_qf_t q0, mossfw_data_qf_t q1, float coef)
{
    mossfw_data_qf_t ret = {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
    ret = q0;
    return ret;
}

static mossfw_data_qf_t calculateYawRotation(mossfw_data_qf_t pose)
{
    mossfw_data_qf_t ret = {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
    float theta;
    float norm;

    theta = acosf(pose.w);
    norm = sqrtf(pose.x * pose.x + pose.y * pose.y + pose.z * pose.z);
    if (norm > 0.00001f) {
        ret.w = cosf(theta);
        ret.x = 0.0f;
        ret.y = sinf(theta) * (pose.y / norm);
        ret.z = 0.0f;
        ret = normalize(ret);
    }
    return ret;
}

static mossfw_data_qf_t complementaryfilter(mossfw_data_qf_t gyrpose, mossfw_data_qf_t accpose)
{
    mossfw_data_qf_t ret = {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
    mossfw_data_qf_t yawrot;
    mossfw_data_qf_t pose;
    const float complementary_filter_coef = 0.999000013;
    struct mossdsp_interpolate_param_s param = {.t0 = 0, .t1 = 1000, .t = 1};

    yawrot = calculateYawRotation(gyrpose);
    mossdsp_multiplyqf(&pose, &yawrot, &accpose, 1);
    mossdsp_interpolateqf(&ret, &gyrpose, &pose, &param);
    ret = normalize(ret);
    return ret;
}

static mossfw_input_t *getinput(struct mossfw_callback_op_s *op, unsigned long indataid)
{
    mossfw_input_t *ret;
    int i;

    ret = op->input;
    for (i = 0; i < indataid && ret != NULL; i++)
      {
        ret = ret->cb_next;
      }
    return ret;
}

static mossfw_data_t *process_gyr(mossfw_data_t *indata, mossfw_data_qf_t *pose)
{
    int datasizegyr = 0;
    int num = 0;
    mossfw_data_v3f_t *ingyr = NULL;
    mossfw_data_qf_t *outdata = NULL;
    mossfw_allocator_t *allocator = NULL;
    mossfw_data_t *outmem = NULL;
    size_t i;
    size_t calnum;
    size_t caloffset;
    int used = 0;

    assert(indata != NULL);
    num = indata->data_bytes / sizeof(mossfw_data_v3f_t);
    ingyr = (mossfw_data_v3f_t *)malloc(num * sizeof(mossfw_data_v3f_t));
    outdata = (mossfw_data_qf_t *)malloc(num * sizeof(mossfw_data_qf_t));
    assert(num * sizeof(mossfw_data_qf_t) <= EISALLOCATOR_SIZE);
    allocator = eisallocator_getallocator();
    assert(allocator != NULL);
    outmem = mossfw_data_alloc(allocator, EISALLOCATOR_SIZE, true);
    assert(outmem != NULL);
    for (i = 0; i < num; i++)
      {
        ingyr[i].x =  indata->data.xyzf[i].y * (PI / 180.0f);
        ingyr[i].y = -indata->data.xyzf[i].z * (PI / 180.0f);
        ingyr[i].z =  indata->data.xyzf[i].x * (PI / 180.0f);
      }
    if (pose != NULL) {
        calnum = num - 1;
        caloffset = 1;
        mossdsp_integrategyrv3f(outdata, ingyr, 1, &integrateparam);
        integrateparam.lastout.f = complementaryfilter(*outdata, *pose);
        *outdata = integrateparam.lastout.f;
    } else {
        calnum = num;
        caloffset = 0;
    }
    mossdsp_integrategyrv3f(&outdata[caloffset], &ingyr[caloffset], calnum, &integrateparam);
    integrateparam.lastout.f = outdata[caloffset + calnum - 1];

    for (i = 0; i < num; i++)
      {
        outmem->data.qf[i].w = outdata[i].w;
        outmem->data.qf[i].x = outdata[i].x;
        outmem->data.qf[i].y = outdata[i].y;
        outmem->data.qf[i].z = outdata[i].z;
      }
    outmem->data_bytes = num * sizeof(mossfw_data_qf_t);
    free(outdata);
    free(ingyr);
    return outmem;
}

static int complementaryfilter_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    int8_t ret = 0;
    int datasizegyr = 0;
    int datasizerot = 0;
    mossfw_data_t *indata = NULL;
    mossfw_data_t *outmem = NULL;
    void *inlinedata;
    size_t i;
    mossfw_input_t *input = NULL;
    int used = 0;

    datasizegyr = mossfw_get_delivereddata_num(in->input);
    datasizerot = mossfw_get_delivereddata_num(in->input->cb_next);
    mossfw_data_t *indatarot = mossfw_get_delivereddata_array(in->input->cb_next, datasizerot, &used);
    assert(indatarot != NULL);
    int numrot = indatarot->data_bytes / sizeof(mossfw_data_qf_t);
    if (0 < datasizegyr) {
        if (gyrcount == 0 && poseupdated == 0)
          {
            indatagyr = mossfw_get_delivereddata_array(in->input, datasizegyr, &used);
#ifdef DEBUG_OUTPUT
            printf("DEBUG complementaryfilter_operate_cb() gyrcount == %d, poseupdate == %d\n", gyrcount, poseupdated);
            fflush(stdout);
#endif
            poseupdated = gyrcount == 0 ? 0 : poseupdated;
            gyrcount = gyrcount < 3 ? gyrcount + 1 : 0;
          }
        else
          {
            if (indatagyr != NULL)
              {
                outmem = process_gyr(indatagyr, &accpose);
                mossfw_data_free(indatagyr);
                indatagyr = NULL;
                if (outmem != NULL) {
                    ret = mossfw_deliver_dataarray(geteispipeline()->complementaryfilter.out[0], outmem);
                    assert(ret == 0);
                }
                mossfw_data_free(outmem);
              }
            indata = mossfw_get_delivereddata_array(in->input, datasizegyr, &used);
            outmem = process_gyr(indata, gyrcount == 0 ? &accpose : NULL);
            assert(outmem);
            ret = mossfw_deliver_dataarray(geteispipeline()->complementaryfilter.out[0], outmem);
            assert(ret == 0);
            mossfw_data_free(outmem);
            poseupdated = gyrcount == 0 ? 0 : poseupdated;
            gyrcount = gyrcount < 3 ? gyrcount + 1 : 0;
          }
        mossfw_data_free(indata);
    } else { /* LINE */
    }
    if (0 < numrot) {
        accpose.w = indatarot->data.qf[0].w;
        accpose.x = indatarot->data.qf[0].x;
        accpose.y = indatarot->data.qf[0].y;
        accpose.z = indatarot->data.qf[0].z;
#ifdef DEBUG_OUTPUT
        printf("ComplementaryFilter POSEACC numrot = %d\n", numrot);
        fflush(stdout);
#endif
        poseupdated = 1;
    }
    mossfw_data_free(indatarot);
    return ret;
}


void complementaryfilter_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 2;
      com->out_num = 1;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      com->in[COMPLEMENTARYFILTER_GYR]  = mossfw_input_create(COMPLEMENTARYFILTER_INPUTTYPE_GYR, 1);
      com->in[COMPLEMENTARYFILTER_ROT]  = mossfw_input_create(COMPLEMENTARYFILTER_INPUTTYPE_Q, 1);
      com->out[0] = mossfw_output_create(COMPLEMENTARYFILTER_OUTPUTTYPE);
      com->op[0]  = mossfw_callback_op_create(complementaryfilter_operate_cb, 0, false);
      mossfw_set_waitcondition(com->in[COMPLEMENTARYFILTER_GYR], MIN_GYR * sizeof(mossfw_data_v3f_t), com->op[0]);
      mossfw_set_waitcondition(com->in[COMPLEMENTARYFILTER_ROT], 1, com->op[0]);
    }
    integrateparam.lastout.f.w = 1.0f;
    integrateparam.lastout.f.x = 0.0f;
    integrateparam.lastout.f.y = 0.0f;
    integrateparam.lastout.f.z = 0.0f;
    accpose.w = 1.0f;
    accpose.x = 0.0f;
    accpose.y = 0.0f;
    accpose.z = 0.0f;
    gyrcount = 0;
    poseupdated = 1;
    indatagyr = NULL;
}

void complementaryfilter_delete(struct component_s *com)
{
    component_delete(com);
}
