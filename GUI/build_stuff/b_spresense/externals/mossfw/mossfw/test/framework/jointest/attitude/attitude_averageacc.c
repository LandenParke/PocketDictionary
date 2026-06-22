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
#include <assert.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_component.h"
#include "component.h"
#include "attitude_averageacc.h"
#include "attitude.h"
//#define DEBUG_OUTPUT

#define AVERAGEACC_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPENAME_ACCEL + \
                                  MOSSFW_DATA_TYPEARRAY_SINGLE)
#define AVERAGEACC_OUTPUTTYPE_ACC AVERAGEACC_INPUTTYPE_ACC

static uint32_t ACCBLKNUM = 107;
static uint32_t count = 0;
static uint32_t accnum = 0;
static mossfw_data_v3f_t accumulate = {.x = 0.0f,.y = 0.0f,.z = 0.0f };

static int attitude_averageacc_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
  int8_t ret = 0;
  size_t num = 0;
  int datasize;
  mossfw_onedata_t data;
  mossfw_onedata_t outdata;

  datasize = mossfw_get_delivereddata_single(in->input, &data);
  num = datasize / sizeof(mossfw_data_v3f_t);
  accumulate.x += data.xyzf.x;
  accumulate.y += data.xyzf.y;
  accumulate.z += data.xyzf.z;
  count = count + 1;
  accnum = accnum + num;

  if (ACCBLKNUM == count)
    {
      accumulate.x = accumulate.x / accnum;
      accumulate.y = accumulate.y / accnum;
      accumulate.z = accumulate.z / accnum;
#ifdef DEBUG_OUTPUT
      printf("AverageAcc %0.16f %0.16f %0.16f\n", accumulate.x, accumulate.y, accumulate.z);
#endif
      outdata.xyzf.x = accumulate.x;
      outdata.xyzf.y = accumulate.y;
      outdata.xyzf.z = accumulate.z;
      ret = mossfw_deliver_data(getattitudepipeline()->average_acc.out[0], &outdata);
      assert(ret == 0);

      count = 0;
      accnum = 0;
      accumulate.x = 0.0f;
      accumulate.y = 0.0f;
      accumulate.z = 0.0f;
    }

  return ret;
}

void attitude_average_acc_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      com->in[0]  = mossfw_input_create(AVERAGEACC_INPUTTYPE_ACC, 2);
      com->out[0] = mossfw_output_create(AVERAGEACC_OUTPUTTYPE_ACC);
      com->op[0]  = mossfw_callback_op_create(attitude_averageacc_operate_cb, 0, false);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_v3f_t), com->op[0]);
    }
  count = 0;
  accnum = 0;
  accumulate.x = 0.0f;
  accumulate.y = 0.0f;
  accumulate.z = 0.0f;
}

void attitude_average_acc_delete(struct component_s *com)
{
    component_delete(com);
}
