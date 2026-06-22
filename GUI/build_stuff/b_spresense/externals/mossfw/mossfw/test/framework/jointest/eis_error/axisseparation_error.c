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
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_component.h"
#include "component.h"
#include "eis_error/axisseparation_error.h"
#include "eis_error/eis_error.h"

#define AXIS_INDEX_YAW   0
#define AXIS_INDEX_PITCH 1
#define AXIS_INDEX_ROLL  2
#define PI 3.14159265358979323846f
#define AXISSEPARATION_INPUTTYPE (MOSSFW_DATA_TYPE_FLOAT + \
                            MOSSFW_DATA_TYPEGRP_Q + \
                            MOSSFW_DATA_TYPEARRAY_ARRAY)
#define AXISSEPARATION_OUTPUTTYPE AXISSEPARATION_INPUTTYPE

static mossfw_data_v3f_t normalizev3f(mossfw_data_v3f_t in, float eps)
{
    float norm;
    norm = sqrtf(in.x * in.x + in.y * in.y + in.z * in.z);
    if (eps < norm) {
        in.x = in.x * (1.0f / norm);
        in.y = in.y * (1.0f / norm);
        in.z = in.z * (1.0f / norm);
    }
    return in;
}

static mossfw_data_qf_t normalize(mossfw_data_qf_t in, float eps)
{
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

static mossfw_data_qf_t separateRotate(mossfw_data_qf_t in)
{
    const float eps = 1.0e-5f;
    const float s_gain[4] = { 1.0f,  0.0f,  1.0f,  0.0f };
    const float s_sign[4] = { 1.0f, -1.0f, -1.0f, -1.0f };
    mossfw_data_qf_t ret;
    float theta;
    mossfw_data_v3f_t sep;

    ret.w = in.w;
    ret.x = -0.0f;
    ret.y = -in.y;
    ret.z = 0.0f;
    ret = normalize(ret, eps);
    theta = acosf(ret.w) * 2.0f;
    if ((fabs(theta) < eps) || (fabs(theta) > (PI * 2.0f - eps))) {
        sep.x = 0.0f;
        sep.y = 0.0f;
        sep.z = 0.0f;
    } else {
        sep.x = ret.x * (1.0f / sinf(theta * 0.5f));
        sep.y = ret.y * (1.0f / sinf(theta * 0.5f));
        sep.z = ret.z * (1.0f / sinf(theta * 0.5f));
        sep = normalizev3f(sep, eps);
        sep.x = sep.x * sinf(theta * 0.5f);
        sep.y = sep.y * sinf(theta * 0.5f);
        sep.z = sep.z * sinf(theta * 0.5f);
        ret.x = sep.x;
        ret.y = sep.y;
        ret.z = sep.z;
    }
    return ret;
}

static mossfw_data_qf_t calc(int index, mossfw_data_qf_t previous_result)
{
    mossfw_data_qf_t ret;

    ret = separateRotate(previous_result);
    ret = normalize(previous_result, 0.001f);
    return ret;
}

static mossfw_data_qf_t estimateCameraPose(mossfw_data_qf_t camera, unsigned int head_count)
{
    mossfw_data_qf_t ret;
    mossfw_data_qf_t pitch;
    mossfw_data_qf_t roll;

    pitch = calc(AXIS_INDEX_YAW,  camera);
    roll  = calc(AXIS_INDEX_PITCH, pitch);
    ret   = calc(AXIS_INDEX_ROLL,   roll);
    return ret;
}

static int axisseparation_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    static unsigned int posecount = 0;
    int8_t ret = 0;
    int num = 0;
    int datasize;
    mossfw_data_qf_t *inposedata;
    mossfw_data_t *posemem;
    void *inlinedata;
    mossfw_data_qf_t *outbuf = NULL;
    size_t outsize;
    size_t i;
    int used;

    datasize = mossfw_get_delivereddata_num(in->input);
    num = datasize / sizeof(mossfw_data_qf_t);
    posemem = mossfw_get_delivereddata_array(in->input, datasize, &used);
    assert(posemem);
    inposedata = (mossfw_data_qf_t *)malloc(num * sizeof(mossfw_data_qf_t));
    outsize = num * sizeof(mossfw_data_qf_t);
    outbuf = (mossfw_data_qf_t *)malloc(num * sizeof(mossfw_data_qf_t));
#ifdef DEBUG_OUTPUT
    printf("AxisSeparation POSE num = %d\n", num);
#endif
    for (i = 0; i < num; i++) {
        inposedata[i].w = posemem->data.qf[i].w;
        inposedata[i].x = posemem->data.qf[i].x;
        inposedata[i].y = posemem->data.qf[i].y;
        inposedata[i].z = posemem->data.qf[i].z;
    }
    for (i = 0; i < num; i++) {
        outbuf[i] = estimateCameraPose(inposedata[i], posecount != 0 || i != 0);
#ifdef DEBUG_OUTPUT
        printf("AxisSeparation %0.16f %0.16f %0.16f %0.16f\n", outbuf[i].w, outbuf[i].x, outbuf[i].y, outbuf[i].z);
#endif
    }
    for (i = 0; i < num; i++)
      {
          posemem->data.qf[i].w = outbuf[i].w;
          posemem->data.qf[i].x = outbuf[i].x;
          posemem->data.qf[i].y = outbuf[i].y;
          posemem->data.qf[i].z = outbuf[i].z;
      }
    ret = mossfw_deliver_dataarray(geteis_errorpipeline()->axisseparation.out[0], posemem);
    assert(ret == 0);
    posecount = posecount < 3 ? posecount + 1 : 0;
    free(inposedata);
    free(outbuf);
    mossfw_data_free(posemem);
    return ret;
}

void axisseparation_error_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      com->in[0]  = mossfw_input_create(AXISSEPARATION_INPUTTYPE, 2);
      com->out[0] = mossfw_output_create(AXISSEPARATION_OUTPUTTYPE);
      com->op[0]  = mossfw_callback_op_create(axisseparation_operate_cb, 0, false);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_qf_t), com->op[0]);
    }
}

void axisseparation_error_delete(struct component_s *com)
{
    component_delete(com);
}
