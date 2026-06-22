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
#include "attitude_stableacc.h"
#include "attitude.h"
//#define DEBUG_OUTPUT
#define STABLEACC_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                                 MOSSFW_DATA_TYPEGRP_V3 + \
                                 MOSSFW_DATA_TYPENAME_ACCEL + \
                                 MOSSFW_DATA_TYPEARRAY_SINGLE)
#define STABLEACC_OUTPUTTYPE_ACC STABLEACC_INPUTTYPE_ACC
#define STABLEACC_OUTPUTTYPE_STABLE (MOSSFW_DATA_TYPE_CHAR + \
                                 MOSSFW_DATA_TYPEGRP_V1 + \
                                 MOSSFW_DATA_TYPENAME_ACCEL + \
                                 MOSSFW_DATA_TYPEARRAY_SINGLE)
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
  float sum = 0.0f;
  float sqsum = 0.0f;
  float timeaverage;
  float sqtimeaverage;
  size_t i;
  mossfw_onedata_t data;
  mossfw_onedata_t outdata;
  mossfw_data_v3f_t *inbuf = NULL;
  mossfw_onedata_t acc;
  mossfw_onedata_t stable;

  mossfw_get_delivereddata_single(in->input, &data);
  inbuf  = (mossfw_data_v3f_t *)malloc(sizeof(mossfw_data_v3f_t));
  inbuf->x = data.xyzf.x;
  inbuf->y = data.xyzf.y;
  inbuf->z = data.xyzf.z;

  for (i = 0; i < sizeof average / sizeof(mossfw_data_v3f_t) - 1; i++)
    {
      average[i] = average[i + 1];
    }
  average[sizeof average / sizeof(mossfw_data_v3f_t) - 1] = *inbuf;
  timeaverage = sum * (1.0f / (float)(sizeof average / sizeof(mossfw_data_v3f_t)));
  sqtimeaverage = sqsum * (1.0f / (float)(sizeof average / sizeof(mossfw_data_v3f_t)));
  stable.xc.x = 1;
  acc.xyzf.x = inbuf->x;
  acc.xyzf.y = inbuf->y;
  acc.xyzf.z = inbuf->z;
#ifdef DEBUG_OUTPUT
  printf("StableAcc %0.16f %0.16f %0.16f\n", acc.xyzf.x, acc.xyzf.y, acc.xyzf.z);
#endif
  ret = mossfw_deliver_data(getattitudepipeline()->stable_acc.out[0], &acc);
  assert(ret == 0);
  ret = mossfw_deliver_data(getattitudepipeline()->stable_acc.out[1], &stable);
  assert(ret == 0);

  return ret;
}

void attitude_stable_acc_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 2;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      com->in[0]  = mossfw_input_create(STABLEACC_INPUTTYPE_ACC, 2);
      com->out[0] = mossfw_output_create(STABLEACC_OUTPUTTYPE_ACC);
      com->out[1] = mossfw_output_create(STABLEACC_OUTPUTTYPE_STABLE);
      com->op[0]  = mossfw_callback_op_create(stableacc_operate_cb, 0, false);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_v3f_t), com->op[0]);
      if (allocator == NULL)
        {
          allocator = mossfw_fixedmem_create(sizeof(char), STABLEACC_MAXBLOCK);
          assert(allocator);
        }
    }
}

void attitude_stable_acc_delete(struct component_s *com)
{
    component_delete(com);
    if (allocator != NULL)
      {
        mossfw_fixedmem_delete(allocator);
        allocator = NULL;
      }
}
