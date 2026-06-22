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
#include "eis_error/estimateposeacc_error.h"
#include "eis_error/eis_error.h"

#define ESTIMATEPOSEACC_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                                       MOSSFW_DATA_TYPEGRP_V3 + \
                                       MOSSFW_DATA_TYPENAME_ACCEL + \
                                       MOSSFW_DATA_TYPEARRAY_ARRAY)
#define ESTIMATEPOSEACC_INPUTTYPE_STABLE (MOSSFW_DATA_TYPE_CHAR + \
                                    MOSSFW_DATA_TYPEGRP_V1 + \
                                    MOSSFW_DATA_TYPENAME_ACCEL + \
                                    MOSSFW_DATA_TYPEARRAY_ARRAY)
#define ESTIMATEPOSEACC_OUTPUTTYPE (MOSSFW_DATA_TYPE_FLOAT + \
                              MOSSFW_DATA_TYPEGRP_Q + \
                              MOSSFW_DATA_TYPEARRAY_ARRAY)
#define ESTIMATEPOSEACC_MAXBLOCK 8

static mossfw_allocator_t *allocator = NULL;

static mossfw_data_v3f_t normalizev3f(mossfw_data_v3f_t in, float e)
{
    float norm;
    mossfw_data_v3f_t ret;

    norm = sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
    ret.x = (norm > e) ? in.x * (1.0f / norm) : in.x;
    ret.y = (norm > e) ? in.y * (1.0f / norm) : in.y;
    ret.z = (norm > e) ? in.z * (1.0f / norm) : in.z;
    return ret;
}

static mossfw_data_qf_t normalizeq(mossfw_data_qf_t in)
{
    float norm;
    mossfw_data_qf_t ret;

    norm = sqrt(in.w * in.w + in.x * in.x + in.y * in.y + in.z * in.z);
    if (norm <= 1.0e-3f) ret = in;
    else {
        ret.w = in.w * (1.0f / norm);
        ret.x = in.x * (1.0f / norm);
        ret.y = in.y * (1.0f / norm);
        ret.z = in.z * (1.0f / norm);
    }
    return ret;
}

static int estimateposeacc_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    int8_t ret = 0;
    int num = 0;
    int datasize;
    int datasizestable;
    mossfw_data_t *indata;
    mossfw_data_t *indatastable;
    mossfw_data_qf_t outdata;
    mossfw_data_t *outmem = NULL;
    mossfw_data_v3f_t indatav3f;
    mossfw_data_v3f_t accnorm;
    mossfw_data_v3f_t accunit;
    float cos_theta;
    mossfw_data_v3f_t rotaxis;
    float theta;
    int used = 0;
    int usedstable = 0;

    datasize       = mossfw_get_delivereddata_num(in->input);
    datasizestable = mossfw_get_delivereddata_num(in->input->cb_next);
    num = datasize / sizeof(mossfw_data_v3f_t);

    indata = mossfw_get_delivereddata_array(in->input, datasize, &used);
    assert(indata);
    indatastable = mossfw_get_delivereddata_array(in->input->cb_next, datasizestable, &usedstable);
    assert(indatastable);

    if (0 < num)
      {
        indatav3f.x = indata->data.xyzf[0].x;
        indatav3f.y = indata->data.xyzf[0].y;
        indatav3f.z = indata->data.xyzf[0].z;
        accnorm = normalizev3f(indatav3f, 1.0e-9f);
        accunit.x =  accnorm.y;
        accunit.y = -accnorm.z;
        accunit.z =  accnorm.x;
        cos_theta = -accunit.y;
        rotaxis.x = accunit.z;
        rotaxis.y = 0.0f;
        rotaxis.z = -accunit.x;
        rotaxis = normalizev3f(rotaxis, 10e-3f);
        theta = acosf(cos_theta);
        outdata.w = cosf(theta * 0.5f);
        outdata.x = rotaxis.x * sinf(theta * 0.5f);
        outdata.y = rotaxis.y * sinf(theta * 0.5f);
        outdata.z = rotaxis.z * sinf(theta * 0.5f);
        outdata = normalizeq(outdata);
        outmem = mossfw_data_alloc(allocator, sizeof(mossfw_data_qf_t), true);
        assert(outmem);
        outmem->data.qf[0].w = outdata.w;
        outmem->data.qf[0].x = outdata.x;
        outmem->data.qf[0].y = outdata.y;
        outmem->data.qf[0].z = outdata.z;
        outmem->data_bytes = sizeof(mossfw_data_qf_t);
        if (indatastable->data.xc[0].x) {
    #ifdef DEBUG_OUTPUT
            printf("EstimatePoseAcc %0.16f %0.16f %0.16f %0.16f\n", outmem->data.qf[0].w, outmem->data.qf[0].x, outmem->data.qf[0].y, outmem->data.qf[0].z);
    #endif
            ret = mossfw_deliver_dataarray(geteis_errorpipeline()->estimateposeacc.out[0], outmem);
            assert(ret == 0);
        }
        else
          {
            ret = mossfw_deliver_dataarray(geteis_errorpipeline()->estimateposeacc.out[0], indatastable);
            assert(ret == 0);
          }
    }
    else
      {
         ret = mossfw_deliver_dataarray(geteis_errorpipeline()->estimateposeacc.out[0], indatastable);
         assert(ret == 0);
      }
    mossfw_data_free(indata);
    mossfw_data_free(indatastable);
    mossfw_data_free(outmem);
    return ret;
}

void estimateposeacc_error_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 2;
      com->out_num = 1;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      if (allocator == NULL)
        {
          allocator = mossfw_fixedmem_create(sizeof(mossfw_data_qf_t), ESTIMATEPOSEACC_MAXBLOCK);
          assert(allocator);
        }
      com->in[0]  = mossfw_input_create(ESTIMATEPOSEACC_INPUTTYPE_ACC, 1);
      com->in[1]  = mossfw_input_create(ESTIMATEPOSEACC_INPUTTYPE_STABLE, 1);
      com->out[0] = mossfw_output_create(ESTIMATEPOSEACC_OUTPUTTYPE);
      com->op[0]  = mossfw_callback_op_create(estimateposeacc_operate_cb, 0, false);
      mossfw_set_waitcondition(com->in[0], 1, com->op[0]);
      mossfw_set_waitcondition(com->in[1], sizeof(mossfw_data_v1c_t), com->op[0]);
    }
}

void estimateposeacc_error_delete(struct component_s *com)
{
    component_delete(com);
    if (allocator != NULL)
      {
        mossfw_fixedmem_delete(allocator);
        allocator = NULL;
      }
}
