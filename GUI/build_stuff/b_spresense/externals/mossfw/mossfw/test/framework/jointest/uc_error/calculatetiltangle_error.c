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
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "mossfw/mossdsp.h"
#include "calibrationacc_error.h"
#include "uc_error.h"

#define PI_FLOAT ((float)M_PI)
#define CONVERT (0.00120)

#define  sinf(x)  sin(x)
#define  cosf(x)  cos(x)
#define  atanf(x)  atan(x)
#define  sqrtf(x)  sqrt(x)

#define CALCULATETILTANGLE_BLKNUM      (28)

#define CALCULATETILTANGLE_INPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                                      MOSSFW_DATA_TYPEGRP_V3 + \
                                      MOSSFW_DATA_TYPENAME_ACCEL + \
                                      MOSSFW_DATA_TYPEARRAY_ARRAY)

#define CALCULATETILTANGLE_OUTPUTTYPE_ROT (MOSSFW_DATA_TYPE_FLOAT + \
                                           MOSSFW_DATA_TYPEGRP_Q + \
                                           MOSSFW_DATA_TYPEARRAY_ARRAY)

#define CALCULATETILTANGLE_OUTPUTTYPE_ACC CALCULATETILTANGLE_INPUTTYPE

static int datacount = 0;
static int valid = 0;
static mossfw_allocator_t *allocator = NULL;

static int calculatetiltangle_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  int ret = 0;
  const int num = 1;
  int data_size;
  int i;
  mossfw_data_v3f_t accel;
  mossfw_data_t *data = NULL;
  mossfw_data_t *odata;
  int used;
  float xrad;
  float yrad;
  float trad = 0;
  mossfw_data_qf_t q1q2;
  mossfw_data_qf_t q1;
  mossfw_data_qf_t q2;
  mossfw_data_qf_t q3;
  mossfw_data_qf_t q;

  data = mossfw_get_delivereddata_array(in->input, num, &used);

  if (++datacount > 3)
    {
      accel.x = data->data.v3s[0].x * CONVERT;
      accel.y = data->data.v3s[0].y * CONVERT;
      accel.z = data->data.v3s[0].z * CONVERT;
      if (accel.z >= -5.0)
        {
            valid = valid + !valid;
        }
    }

  if (valid == 1)
    {
      xrad = atanf(accel.y / sqrtf(accel.x * accel.x + accel.z * accel.z));
      yrad = atanf(-accel.x / accel.z);
      xdeg_error = xrad * 180.0f / PI_FLOAT;
      ydeg_error = yrad * 180.0f / PI_FLOAT;

      trad = trad * PI_FLOAT / 180.0f;
      q1.w = cosf(xrad / 2.0f);
      q1.x = -sinf(xrad / 2.0f);
      q1.y = 0.0f;
      q1.z = 0.0f;
      q2.w = cosf(yrad / 2.0f);
      q2.x = 0.0f;
      q2.y = -cosf(xrad) * sinf(yrad / 2.0f);
      q2.z = -sinf(xrad) * sinf(yrad / 2.0f);
      q3.w = cosf(trad / 2.0f);
      q3.x = 0.0f;
      q3.y = 0.0f;
      q3.z = -sinf(trad / 2.0f);

      ret = mossdsp_multiplyqf(&q1q2, &q1, &q2, 1);
      ret = mossdsp_multiplyqf(&q, &q1q2, &q3, 1);
      odata = mossfw_data_alloc(allocator, sizeof(mossfw_data_qf_t), true);
      odata->data.qf[0].w = q.w;
      odata->data.qf[0].x = q.x;
      odata->data.qf[0].y = q.y;
      odata->data.qf[0].z = q.z;
      odata->data_bytes = sizeof odata->data.qf[0];
      mossfw_deliver_dataarray(getuc_errorpipeline()->calculatetiltangle.out[0], odata);
      mossfw_data_free(odata);
    }
  if (1 < valid) 
    {
      mossfw_deliver_dataarray(getuc_errorpipeline()->calculatetiltangle.out[1], data);
    }
  if (2 < valid) 
    {
      odata = mossfw_data_alloc(allocator, sizeof(mossfw_data_qf_t), true);
      odata->data_bytes = 1;
      mossfw_deliver_dataarray(getuc_errorpipeline()->calculatetiltangle.out[0], odata);
      mossfw_data_free(odata);
    }
  valid = valid + (valid == 1 || valid == 2);
  mossfw_data_free(data);

  return ret;
}

void calculatetiltangle_error_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 2;
      com->op_num  = 1;
      com->in  = malloc(com->in_num * sizeof(void *));
      com->out = malloc(com->out_num * sizeof(void *));
      com->op  = malloc(com->op_num * sizeof(void *));
      if (allocator == NULL)
        {
          allocator = mossfw_fixedmem_create(sizeof(mossfw_data_qf_t), 1);
          assert(allocator != NULL);
        }
      *com->in = mossfw_input_create(CALCULATETILTANGLE_INPUTTYPE, CALCULATETILTANGLE_BLKNUM);
      com->out[0] = mossfw_output_create(CALCULATETILTANGLE_OUTPUTTYPE_ROT);
      com->out[1] = mossfw_output_create(CALCULATETILTANGLE_OUTPUTTYPE_ACC);
      *com->op  = mossfw_callback_op_create(calculatetiltangle_operate_cb, 0, false);
      mossfw_set_waitcondition(*(com->in), sizeof(mossfw_data_v3s_t), *(com->op));
    }
    valid = 0;
    datacount = 0;
}

void calculatetiltangle_error_delete(struct component_s *com)
{
    component_delete(com);
    if (allocator != NULL)
      {
        mossfw_fixedmem_delete(allocator);
        allocator = NULL;
      }
}
