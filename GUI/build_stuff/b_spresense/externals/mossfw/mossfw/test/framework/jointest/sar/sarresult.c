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
#include <assert.h>
#include <stdlib.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "component.h"
#include "sarresult.h"

#define RESULT_ACC_INPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                              MOSSFW_DATA_TYPEGRP_V3 + \
                              MOSSFW_DATA_TYPENAME_ACCEL + \
                              MOSSFW_DATA_TYPEARRAY_SINGLE)
#define RESULT_GYR_INPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                              MOSSFW_DATA_TYPEGRP_V3 + \
                              MOSSFW_DATA_TYPENAME_GYRO + \
                              MOSSFW_DATA_TYPEARRAY_SINGLE)
#define RESULT_MAG_INPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                              MOSSFW_DATA_TYPEGRP_V3 + \
                              MOSSFW_DATA_TYPEARRAY_SINGLE)
#define RESULT_ROT_INPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                              MOSSFW_DATA_TYPEGRP_V3 + \
                              MOSSFW_DATA_TYPEARRAY_SINGLE)

static const mossfw_data_v3s_t accref[] = {
    {.x = 5614, .y = 2506, .z = -4367}, 
    {.x = 7049, .y = 2648, .z = -2044}
}; 

static const mossfw_data_v3s_t gyrref[] = {
    {.x = 531, .y =   76, .z = -745},
    {.x = 176, .y = -131, .z =  -94}
};

static const mossfw_data_v3s_t magref[] = {
    {.x = 437, .y = -6011, .z = -6902},
    {.x = 420, .y = -6021, .z = -6960}
};

static const mossfw_data_v3s_t rotref[] = {
    {.x = 186, .y = -159, .z = -12},
    {.x = 185, .y = -159, .z = -11}
};

static unsigned int accomplished = 0;

static int result_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  mossfw_onedata_t result[2];
  mossfw_input_t *input;

  (void) arg;
  input = in->input;
  assert(input != NULL);
  mossfw_get_delivereddata_single(input, &result[0]);
  mossfw_get_delivereddata_single(input, &result[1]);
  assert(result[0].v3s.x == accref[0].x);
  assert(result[0].v3s.y == accref[0].y);
  assert(result[0].v3s.z == accref[0].z);
  assert(result[1].v3s.x == accref[1].x);
  assert(result[1].v3s.y == accref[1].y);
  assert(result[1].v3s.z == accref[1].z);

  input = input->cb_next;
  assert(input != NULL);
  mossfw_get_delivereddata_single(input, &result[0]);
  mossfw_get_delivereddata_single(input, &result[1]);
  assert(result[0].v3s.x == gyrref[0].x);
  assert(result[0].v3s.y == gyrref[0].y);
  assert(result[0].v3s.z == gyrref[0].z);
  assert(result[1].v3s.x == gyrref[1].x);
  assert(result[1].v3s.y == gyrref[1].y);
  assert(result[1].v3s.z == gyrref[1].z);

  input = input->cb_next;
  assert(input != NULL);
  mossfw_get_delivereddata_single(input, &result[0]);
  mossfw_get_delivereddata_single(input, &result[1]);
  assert(result[0].v3s.x == magref[0].x);
  assert(result[0].v3s.y == magref[0].y);
  assert(result[0].v3s.z == magref[0].z);
  assert(result[1].v3s.x == magref[1].x);
  assert(result[1].v3s.y == magref[1].y);
  assert(result[1].v3s.z == magref[1].z);

  input = input->cb_next;
  assert(input != NULL);
  mossfw_get_delivereddata_single(input, &result[0]);
  mossfw_get_delivereddata_single(input, &result[1]);
  assert(result[0].v3s.x == rotref[0].x);
  assert(result[0].v3s.y == rotref[0].y);
  assert(result[0].v3s.z == rotref[0].z);
  assert(result[1].v3s.x == rotref[1].x);
  assert(result[1].v3s.y == rotref[1].y);
  assert(result[1].v3s.z == rotref[1].z);

  accomplished = 1;
  return OK;
}

void sarresult_create(struct component_s *com)
{
  int val;

  if (com != NULL)
    {
      com->in_num  = 4;
      com->out_num = 0;
      com->op_num  = 1;
      com->in = malloc(com->in_num * sizeof(void *));
      com->op = malloc(com->op_num * sizeof(void *));
      com->out = NULL;
      com->in[SARRESULT_ACC] = mossfw_input_create(RESULT_ACC_INPUTTYPE, 2);
      com->in[SARRESULT_GYR] = mossfw_input_create(RESULT_GYR_INPUTTYPE, 2);
      com->in[SARRESULT_MAG] = mossfw_input_create(RESULT_MAG_INPUTTYPE, 2);
      com->in[SARRESULT_ROT] = mossfw_input_create(RESULT_ROT_INPUTTYPE, 2);
      com->op[0] = mossfw_callback_op_create(result_operate_cb, 0, false);
      val = mossfw_set_waitcondition(com->in[SARRESULT_ACC], 2 * sizeof(mossfw_data_v3s_t), com->op[0]);
      assert(val == 0);
      val = mossfw_set_waitcondition(com->in[SARRESULT_GYR], 2 * sizeof(mossfw_data_v3s_t), com->op[0]);
      assert(val == 0);
      val = mossfw_set_waitcondition(com->in[SARRESULT_MAG], 2 * sizeof(mossfw_data_v3s_t), com->op[0]);
      assert(val == 0);
      val = mossfw_set_waitcondition(com->in[SARRESULT_ROT], 2 * sizeof(mossfw_data_v3s_t), com->op[0]);
      assert(val == 0);
    }
  accomplished = 0;
}

void sarresult_delete(struct component_s *com)
{
  component_delete(com);
  assert(accomplished == 1);
}
