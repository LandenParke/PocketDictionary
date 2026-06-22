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
#include "attitude_transform.h"
#include "attitude.h"
//#define DEBUG_OUTPUT
#define get_time_eis(x)

#define TRANSFORM_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                                MOSSFW_DATA_TYPEGRP_V3 + \
                                MOSSFW_DATA_TYPENAME_ACCEL + \
                                MOSSFW_DATA_TYPEARRAY_SINGLE)
#define TRANSFORM_INPUTTYPE_GYR (MOSSFW_DATA_TYPE_FLOAT + \
                                MOSSFW_DATA_TYPEGRP_V3 + \
                                MOSSFW_DATA_TYPENAME_GYRO + \
                                MOSSFW_DATA_TYPEARRAY_SINGLE)
#define TRANSFORM_OUTPUTTYPE_ACC TRANSFORM_INPUTTYPE_ACC
#define TRANSFORM_OUTPUTTYPE_GYR TRANSFORM_INPUTTYPE_GYR

static struct sqmatrix3f_s param_gyr = {
  .x = {.x = -1.0f,.y = 0.0f,.z = 0.0f},
  .y = {.x = 0.0f,.y = -1.0f,.z = 0.0f},
  .z = {.x = 0.0f,.y = 0.0f,.z = 1.0f}
};

static struct sqmatrix3f_s param_acc = {
  .x = {.x = -1.0f,.y = 0.0f,.z = 0.0f},
  .y = {.x = 0.0f,.y = -1.0f,.z = 0.0f},
  .z = {.x = 0.0f,.y = 0.0f,.z = 1.0f}
};

#ifdef DEBUG_OUTPUT
static void print(unsigned long outdataid, void *outbuf, size_t size)
{
  get_time_eis(173);
  size_t i;
  size_t num = size / sizeof(mossfw_data_v3f_t);
  mossfw_data_v3f_t *out = NULL;
  out = outbuf;

  if (outdataid == TRANSFORM_ACC)
    {
      for (i = 0; i < num; i++)
        {
          printf("Transform ACC %0.16f %0.16f %0.16f\n", out[i].x, out[i].y, out[i].z);
        }
    }
  else
    {
      for (i = 0; i < num; i++)
        {
          printf("Transform GYR %0.16f %0.16f %0.16f\n", out[i].x, out[i].y, out[i].z);
        }
    }
  get_time_eis(174);
}
#endif
static int attitude_transform_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
  int ret = 0;
  int32_t data_size;
  size_t num;
  const struct sqmatrix3f_s *param = NULL;
  mossfw_onedata_t data;
  mossfw_onedata_t outdata;
  mossfw_data_v3f_t *inbuf = NULL;
  mossfw_data_v3f_t *outbuf = NULL;

  inbuf  = (mossfw_data_v3f_t *)malloc(sizeof(mossfw_data_v3f_t));
  outbuf = (mossfw_data_v3f_t *)malloc(sizeof(mossfw_data_v3f_t));

  get_time_eis(176);

  data_size = mossfw_get_delivereddata_single(in->input, &data);
  inbuf->x = data.xyzf.x;
  inbuf->y = data.xyzf.y;
  inbuf->z = data.xyzf.z;
  mossfw_output_t *output;
  if (indataid == TRANSFORM_ACC)
    {
      param = &param_acc;
      output = getattitudepipeline()->transform_acc.out[0];
    }
  else
    {
      param = &param_gyr;
      output = getattitudepipeline()->transform_gyr.out[0];
    }
  num = data_size / sizeof(mossfw_data_v3f_t);
  mossdsp_transformaxismv3f(outbuf, inbuf, num, &param_acc);

#ifdef DEBUG_OUTPUT
  print(indataid, outbuf, data_size);
#endif

  outdata.xyzf.x = outbuf->x;
  outdata.xyzf.y = outbuf->y;
  outdata.xyzf.z = outbuf->z;
  ret = mossfw_deliver_data(output, &outdata);
  assert(ret == 0);

  free(outbuf);
  free(inbuf);

  get_time_eis(182);

  return ret;
}

void attitude_transform_create(struct component_s *com, enum transform_e type)
{
  if (com != NULL)
    {
      com->in_num    = 1;
      com->out_num   = 1;
      com->op_num    = 1;
      com->in        = malloc(com->in_num    * sizeof(void *));
      com->out       = malloc(com->out_num   * sizeof(void *));
      com->op        = malloc(com->op_num    * sizeof(void *));
      if (type == TRANSFORM_ACC)
        {
          com->in[0]  = mossfw_input_create(TRANSFORM_INPUTTYPE_ACC, 2);
          com->out[0] = mossfw_output_create(TRANSFORM_OUTPUTTYPE_ACC);
        }
      else
        {
          com->in[0]  = mossfw_input_create(TRANSFORM_INPUTTYPE_GYR, 2);
          com->out[0] = mossfw_output_create(TRANSFORM_OUTPUTTYPE_GYR);
        }
      com->op[0]  = mossfw_callback_op_create(attitude_transform_operate_cb, (unsigned long)type, false);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_v3f_t), com->op[0]);
    }
}

void attitude_transform_delete(struct component_s *com)
{
    component_delete(com);
}
