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
#include <string.h>
#include <assert.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossdsp.h"
#include "mossfw/mossfw_component.h"
#include "component.h"
#include "eis_error/transform_error.h"
#include "eis_error/eis_error.h"

#define get_time_eis(x)

#define TRANSFORM_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPENAME_ACCEL + \
                           MOSSFW_DATA_TYPEARRAY_ARRAY)
#define TRANSFORM_INPUTTYPE_GYR (MOSSFW_DATA_TYPE_FLOAT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPENAME_GYRO + \
                           MOSSFW_DATA_TYPEARRAY_ARRAY)
#define TRANSFORM_OUTPUTTYPE_ACC TRANSFORM_INPUTTYPE_ACC
#define TRANSFORM_OUTPUTTYPE_GYR TRANSFORM_INPUTTYPE_GYR

static const struct sqmatrix3f_s param = {
    .x = {.x =  0.0f, .y = 0.0f, .z = 1.0f},
    .y = {.x = -1.0f, .y = 0.0f, .z = 0.0f},
    .z = {.x =  0.0f, .y = 1.0f, .z = 0.0f}
};

static void print(unsigned long outdataid, mossfw_data_t *outbuf, size_t size)
{
    get_time_eis(173);
    mossfw_data_v3f_t *outdata = NULL;
    size_t num;
    size_t i;

    if (outdataid == TRANSFORM_ACC0) {
        num = size / sizeof(mossfw_data_v3f_t);
        outdata = outbuf->data.xyzf;
        for (i = 0; i < num; i++) {
            printf("Transform ACC %0.16f %0.16f %0.16f\n", outdata[i].x, outdata[i].y, outdata[i].z);
        }
    } else if (outdataid == TRANSFORM_GYR0) {
        num = size / sizeof(mossfw_data_v3f_t);
        outdata = outbuf->data.xyzf;
        for (i = 0; i < num; i++) {
            printf("Transform GYR %0.16f %0.16f %0.16f\n", outdata[i].x, outdata[i].y, outdata[i].z);
        }
    } else if (outdataid == TRANSFORM_ACC1) {
        num = size / sizeof(mossfw_data_v3f_t);
        outdata = outbuf->data.xyzf;
        for (i = 0; i < num; i++) {
            printf("Transform ACC %0.16f %0.16f %0.16f\n", outdata[i].x, outdata[i].y, outdata[i].z);
        }
    } else if (outdataid == TRANSFORM_GYR1) {
        num = size / sizeof(mossfw_data_v3f_t);
        outdata = outbuf->data.xyzf;
        for (i = 0; i < num; i++) {
            printf("Transform GYR %0.16f %0.16f %0.16f\n", outdata[i].x, outdata[i].y, outdata[i].z);
        }
    }
    get_time_eis(174);
}

static int transform_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    int ret = 0;
    int32_t data_size;
    size_t num;
    mossfw_data_t *mem = NULL;
    mossfw_data_v3f_t *indata;
    mossfw_data_v3f_t *outdata;
    size_t outsize = 0;
    size_t i;
    int used;

    get_time_eis(176);
    data_size = mossfw_get_delivereddata_num(in->input);
    mem = mossfw_get_delivereddata_array(in->input, data_size, &used);
    num = (size_t)mem->data_bytes / sizeof(mossfw_data_v3f_t);
    outsize = num * sizeof(mossfw_data_v3f_t);
    indata = malloc(mem->data_bytes);
    assert(indata);
    outdata = malloc(outsize);
    assert(outdata);
    get_time_eis(177);
    for (i = 0; i < num; i++)
      {
        indata[i].x = mem->data.xyzf[i].x;
        indata[i].y = mem->data.xyzf[i].y;
        indata[i].z = mem->data.xyzf[i].z;
      }
    (void)mossdsp_transformaxismv3f(outdata, indata, num, &param);
    for (i = 0; i < num; i++)
      {
        mem->data.xyzf[i].x = outdata[i].x;
        mem->data.xyzf[i].y = outdata[i].y;
        mem->data.xyzf[i].z = outdata[i].z;
      }
#ifdef DEBUG_OUTPUT
    print(indataid, mem, outsize);
#endif

    mossfw_output_t *output;
    if (indataid == TRANSFORM_ACC0)
      {
        output = geteis_errorpipeline()->transformacc0.out[0];
      }
    else if (indataid == TRANSFORM_GYR0)
      {
        output = geteis_errorpipeline()->transformgyr0.out[0];
      }
    else if (indataid == TRANSFORM_ACC1)
      {
        output = geteis_errorpipeline()->transformacc1.out[0];
      }
    else
      {
        output = geteis_errorpipeline()->transformgyr1.out[0];
      }

    ret = mossfw_deliver_dataarray(output, mem);
    assert(ret == 0);
    free(indata);
    free(outdata);
    mossfw_data_free(mem);
    get_time_eis(182);
    return ret;
}

void transform_error_create(struct component_s *com, enum transform_e type)
{
  if (com != NULL)
    {
      com->in_num    = 1;
      com->out_num   = 1;
      com->op_num    = 1;
      com->in        = malloc(com->in_num    * sizeof(void *));
      com->out       = malloc(com->out_num   * sizeof(void *));
      com->op        = malloc(com->op_num    * sizeof(void *));
      if (type == TRANSFORM_ACC0 || type == TRANSFORM_ACC1)
        {
          com->in[0]  = mossfw_input_create(TRANSFORM_INPUTTYPE_ACC, 1);
          com->out[0] = mossfw_output_create(TRANSFORM_OUTPUTTYPE_ACC);
        }
      else
        {
          com->in[0]  = mossfw_input_create(TRANSFORM_INPUTTYPE_GYR, 1);
          com->out[0] = mossfw_output_create(TRANSFORM_OUTPUTTYPE_GYR);
        }
      com->op[0]  = mossfw_callback_op_create(transform_operate_cb, (unsigned long)type, false);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_v3f_t), com->op[0]);
    }
}

void transform_error_delete(struct component_s *com)
{
    int i;
    component_delete(com);
}
