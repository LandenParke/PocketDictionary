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
#include "eis/stableacc.h"
#include "eis/eis.h"

#define STABLEACC_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                                 MOSSFW_DATA_TYPEGRP_V3 + \
                                 MOSSFW_DATA_TYPENAME_ACCEL + \
                                 MOSSFW_DATA_TYPEARRAY_ARRAY)
#define STABLEACC_OUTPUTTYPE_ACC STABLEACC_INPUTTYPE_ACC
#define STABLEACC_OUTPUTTYPE_STABLE (MOSSFW_DATA_TYPE_CHAR + \
                                 MOSSFW_DATA_TYPEGRP_V1 + \
                                 MOSSFW_DATA_TYPENAME_ACCEL + \
                                 MOSSFW_DATA_TYPEARRAY_ARRAY)
#define STABLEACC_MAXBLOCK 8

static mossfw_allocator_t *allocator = NULL;

static int stableacc_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    static unsigned int count = 0;
    static unsigned int accnum = 0;
    static mossfw_data_v3f_t average[] = {
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f}
    };
    int ret = 0;
    size_t num = 0;
    int datasize;
    mossfw_data_t *indata = NULL;
    float sum = 0.0f;
    float sqsum = 0.0f;
    float timeaverage;
    float sqtimeaverage;
    mossfw_data_t *stablemem;
    size_t i;
    int used;

    datasize = mossfw_get_delivereddata_num(in->input);
    num = datasize / sizeof(mossfw_data_v3f_t);
    indata = mossfw_get_delivereddata_array(in->input, datasize, &used);
    assert(indata != NULL);

    for (i = 0; i < sizeof average / sizeof(mossfw_data_v3f_t) - 1; i++) {
        average[i] = average[i + 1];
    }
    average[sizeof average / sizeof(mossfw_data_v3f_t) - 1] = indata->data.xyzf[0];
    timeaverage = sum * (1.0f / (float)(sizeof average / sizeof(mossfw_data_v3f_t)));
    sqtimeaverage = sqsum * (1.0f / (float)(sizeof average / sizeof(mossfw_data_v3f_t)));
    stablemem = mossfw_data_alloc(allocator, sizeof(char), true);
    assert(stablemem != NULL);
    stablemem->data.xc[0].x = 1;
    stablemem->data_bytes = sizeof(mossfw_data_v1c_t);
#ifdef DEBUG_OUTPUT
    for (i = 0; i < num; i++) {
        printf("StableAcc acc %0.16f %0.16f %0.16f\n", indata->data.xyzf[i].x, indata->data.xyzf[i].y, indata->data.xyzf[i].z);
    }
    printf("StableAcc stable = %d\n", stablemem->data.xc[0].x);
#endif

    ret = mossfw_deliver_dataarray(geteispipeline()->stableacc.out[0], indata);
    assert(ret == 0);
    ret = mossfw_deliver_dataarray(geteispipeline()->stableacc.out[1], stablemem);
    assert(ret == 0);
    mossfw_data_free(indata);
    mossfw_data_free(stablemem);
    return ret;
}

void stableacc_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 2;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      com->in[0]  = mossfw_input_create(STABLEACC_INPUTTYPE_ACC, 1);
      com->out[0] = mossfw_output_create(STABLEACC_OUTPUTTYPE_ACC);
      com->out[1] = mossfw_output_create(STABLEACC_OUTPUTTYPE_STABLE);
      com->op[0]  = mossfw_callback_op_create(stableacc_operate_cb, 0, false);
      mossfw_set_waitcondition(com->in[0], 1, com->op[0]);
      if (allocator == NULL)
        {
          allocator = mossfw_fixedmem_create(sizeof(char), STABLEACC_MAXBLOCK);
          assert(allocator);
        }
    }
}

void stableacc_delete(struct component_s *com)
{
    component_delete(com);
    if (allocator != NULL)
      {
        mossfw_fixedmem_delete(allocator);
        allocator = NULL;
      }
}
