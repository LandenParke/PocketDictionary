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
#include <assert.h>
#include <math.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "uc.h"
#include "calculatetiltgravity.h"

#define ACC_CONVERT (0.00120)
#define DEGREE_CONVERT (57.29583)

#define CALCULATETILTGRAVITY_BLKNUM_ROT  (2)
#define CALCULATETILTGRAVITY_BLKNUM_ACC  (28)
#define CALCULATETILTGRAVITY_BLKNUM_OUT  (10)

#define CALCULATETILTGRAVITY_INPUTTYPE_ROT (MOSSFW_DATA_TYPE_FLOAT + \
                                            MOSSFW_DATA_TYPEGRP_Q + \
                                            MOSSFW_DATA_TYPEARRAY_ARRAY)

#define CALCULATETILTGRAVITY_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_SHORT + \
                                            MOSSFW_DATA_TYPEGRP_V3 + \
                                            MOSSFW_DATA_TYPENAME_ACCEL + \
                                            MOSSFW_DATA_TYPEARRAY_ARRAY)

#define CALCULATETILTGRAVITY_OUTPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                                             MOSSFW_DATA_TYPEGRP_V3 + \
                                             MOSSFW_DATA_TYPENAME_ACCEL + \
                                             MOSSFW_DATA_TYPEARRAY_ARRAY)

#define CALCULATETILTGRAVITY_OUTPUTTYPE_ROT (MOSSFW_DATA_TYPE_FLOAT + \
                                             MOSSFW_DATA_TYPEGRP_V1 + \
                                             MOSSFW_DATA_TYPEARRAY_ARRAY)

struct SensorCalibrationBuffer{
  double acc_x;
  double acc_y;
  double acc_z;
  double theta_angle;
};

static struct SensorCalibrationBuffer out_v;
static mossfw_allocator_t *allocatorv3f = NULL;
static mossfw_allocator_t *allocatorf   = NULL;

static int calculatetiltgravity_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  static mossfw_data_qf_t q;
  int ret = 0;
  int used = 0;
  int i;
  static mossfw_data_t *data = NULL;
  double acc_x;
  double acc_y;
  double acc_z;
  float v11;
  float v12;
  float v13;
  float v21;
  float v22;
  float v23;
  float v31;
  float v32;
  float v33;
  int sizerot = 0;
  int sizeacc = 0;
  
  sizerot = mossfw_get_delivereddata_num(in->input);
  sizeacc = mossfw_get_delivereddata_num(in->input->cb_next);

  data = mossfw_get_delivereddata_array(in->input, sizerot, &used);
  if (1 < sizerot)
    {
      q.w = data->data.qf[0].w;
      q.x = data->data.qf[0].x;
      q.y = data->data.qf[0].y;
      q.z = data->data.qf[0].z;
    }
  mossfw_data_free(data);
  if (0 < sizeacc)
    {
      data = mossfw_get_delivereddata_array(in->input->cb_next, sizeacc, &used);

      v11 = q.x * q.x - q.y * q.y - q.z * q.z + q.w * q.w;
      v12 = 2.0f * (q.x * q.y + q.z * q.w);
      v13 = 2.0f * (q.x * q.z - q.y * q.w);
      v21 = 2.0f * (q.x * q.y - q.z * q.w);
      v22 = -q.x * q.x + q.y * q.y - q.z * q.z + q.w * q.w;
      v23 = 2.0f * (q.y * q.z + q.x * q.w);
      v31 = 2.0f * (q.x * q.z + q.y * q.w);
      v32 = 2.0f * (q.y * q.z - q.x * q.w);
      v33 = -q.x * q.x - q.y * q.y + q.z * q.z + q.w * q.w;
    
      acc_x = data->data.v3s[0].x * ACC_CONVERT;
      acc_y = data->data.v3s[0].y * ACC_CONVERT;
      acc_z = data->data.v3s[0].z * ACC_CONVERT;
      out_v.acc_x = v11 * acc_x + v12 * acc_y + v13 * acc_z;
      out_v.acc_y = v21 * acc_x + v22 * acc_y + v23 * acc_z;
      out_v.acc_z = v31 * acc_x + v32 * acc_y + v33 * acc_z;
      out_v.theta_angle =
        acos(out_v.acc_z /
             sqrt(pow(out_v.acc_x, 2.0) + pow(out_v.acc_y, 2.0) +
                  pow(out_v.acc_z, 2.0))) * DEGREE_CONVERT;
      mossfw_data_free(data);

      data = mossfw_data_alloc(allocatorv3f, sizeof(mossfw_data_v3f_t), true);
      assert(data);
      data->data.v3f[0].x = out_v.acc_x;
      data->data.v3f[0].y = out_v.acc_y;
      data->data.v3f[0].z = out_v.acc_z;
      data->data_bytes = sizeof data->data.v3f[0];
      mossfw_deliver_dataarray(getucpipeline()->calculatetiltgravity.out[0], data);
      mossfw_data_free(data);

      data = mossfw_data_alloc(allocatorf, sizeof(mossfw_data_v1f_t), true);
      assert(data);
      data->data.v1f[0].x = (float)out_v.theta_angle;
      data->data_bytes = sizeof data->data.v1f[0];
      mossfw_deliver_dataarray(getucpipeline()->calculatetiltgravity.out[1], data);
      mossfw_data_free(data);
    }
  return 0;
}

void calculatetiltgravity_create(struct component_s *com)
{
  int val;

  if (com != NULL)
    {
      com->in_num    = 2;
      com->out_num   = 2;
      com->op_num    = 1;
      com->in    = malloc(com->in_num    * sizeof(void *));
      com->out   = malloc(com->out_num   * sizeof(void *));
      com->op    = malloc(com->op_num    * sizeof(void *));
      com->in[0]  = mossfw_input_create(CALCULATETILTGRAVITY_INPUTTYPE_ROT, CALCULATETILTGRAVITY_BLKNUM_ROT);
      com->in[1]  = mossfw_input_create(CALCULATETILTGRAVITY_INPUTTYPE_ACC, CALCULATETILTGRAVITY_BLKNUM_ACC);
      com->out[0] = mossfw_output_create(CALCULATETILTGRAVITY_OUTPUTTYPE_ACC);
      com->out[1] = mossfw_output_create(CALCULATETILTGRAVITY_OUTPUTTYPE_ROT);
      com->op[0]  = mossfw_callback_op_create(calculatetiltgravity_operate_cb, 0, false);
      allocatorv3f = mossfw_fixedmem_create(sizeof(mossfw_data_v3f_t), CALCULATETILTGRAVITY_BLKNUM_OUT * sizeof(mossfw_data_v3f_t));
      allocatorf   = mossfw_fixedmem_create(sizeof(mossfw_data_v1f_t), CALCULATETILTGRAVITY_BLKNUM_OUT * sizeof(mossfw_data_v1f_t));
      val = mossfw_set_waitcondition(com->in[0], 1, com->op[0]);
      assert(val == 0);
      val = mossfw_set_waitcondition(com->in[1], sizeof(mossfw_data_v3s_t), com->op[0]);
      assert(val == 0);
    }
}

void calculatetiltgravity_delete(struct component_s *com)
{
    component_delete(com);
    if (allocatorv3f != NULL)
      {
        mossfw_fixedmem_delete(allocatorv3f);
        allocatorv3f = NULL;
      }
    if (allocatorf != NULL)
      {
        mossfw_fixedmem_delete(allocatorf);
        allocatorf = NULL;
      }
}
