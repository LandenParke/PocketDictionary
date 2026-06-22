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
#include "mossfw/mossfw_data.h"
#include "mossfw/sensorlib.h"
#include "component.h"
#include "testestimatorcomponent.h"
#include "testestimatorif.h"
#include "sar.h"

#define TestEstimatorCOMPONENT_ACCBLKNUM 4
#define TestEstimatorCOMPONENT_GYRBLKNUM 8
#define TestEstimatorCOMPONENT_MAGBLKNUM 4
#define TestEstimatorCOMPONENT_INPUT_ACC 0
#define TestEstimatorCOMPONENT_INPUT_GYR 1
#define TestEstimatorCOMPONENT_INPUT_MAG 2

#define TestEstimatorCOMPONENT_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_SHORT + \
                                     MOSSFW_DATA_TYPEGRP_V3 + \
                                     MOSSFW_DATA_TYPENAME_ACCEL + \
                                     MOSSFW_DATA_TYPEARRAY_SINGLE)
#define TestEstimatorCOMPONENT_INPUTTYPE_GYR (MOSSFW_DATA_TYPE_SHORT + \
                                     MOSSFW_DATA_TYPEGRP_V3 + \
                                     MOSSFW_DATA_TYPENAME_GYRO + \
                                     MOSSFW_DATA_TYPEARRAY_SINGLE)
#define TestEstimatorCOMPONENT_INPUTTYPE_MAG (MOSSFW_DATA_TYPE_SHORT + \
                                     MOSSFW_DATA_TYPEGRP_V3 + \
                                     MOSSFW_DATA_TYPEARRAY_SINGLE)

#define TestEstimatorCOMPONENT_OUTPUTTYPE_MAG TestEstimatorCOMPONENT_INPUTTYPE_MAG
#define TestEstimatorCOMPONENT_OUTPUTTYPE_ROT  (MOSSFW_DATA_TYPE_FLOAT + \
                               MOSSFW_DATA_TYPEGRP_Q + \
                               MOSSFW_DATA_TYPEARRAY_SINGLE)

static void *testestimator = NULL;
static const float g = 9.80665f;
static const float pi = 3.141592653589793f;

static int testestimatorcomponent_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  static mossfw_data_v3f_t acc;
  static mossfw_data_v3f_t gyr;
  static mossfw_data_v3f_t mag;
  static int acc_valid = 0;
  static int gyr_valid = 0;
  static int mag_valid = 0;
  static int updatecount = 0;

  mossfw_data_qf_t rot;
  mossfw_onedata_t data;
  mossfw_onedata_t magout;
  mossfw_onedata_t rotout;
  unsigned int i;

  (void)arg;

  /*
   * Confirm if all needed data is collected.
   * Othewise, nothing to do.
   */
  mossfw_get_delivereddata_single(in->input, &data);
  acc.x = data.v3s.x * 4.0f * g / (float)0x8000;
  acc.y = data.v3s.y * 4.0f * g / (float)0x8000;
  acc.z = data.v3s.z * 4.0f * g / (float)0x8000;
  acc_valid = 1;

  mossfw_get_delivereddata_single(in->input->cb_next, &data);
  mossfw_get_delivereddata_single(in->input->cb_next, &data);
  gyr.x = data.v3s.x * 2000.0f * pi / ((float)0x8000 * 180.0f);
  gyr.y = data.v3s.y * 2000.0f * pi / ((float)0x8000 * 180.0f);
  gyr.z = data.v3s.z * 2000.0f * pi / ((float)0x8000 * 180.0f);
  gyr_valid = 1;
  mossfw_get_delivereddata_single(in->input->cb_next->cb_next, &data);
  mag.x = data.v3s.x * 36000.0f / (float)0x8000;
  mag.y = data.v3s.y * 36000.0f / (float)0x8000;
  mag.z = data.v3s.z * 36000.0f / (float)0x8000;
  magout.v3s.x = data.v3s.x;
  magout.v3s.y = data.v3s.y;
  magout.v3s.z = data.v3s.z;
  mag_valid = 1;
  TestEstimator_update(testestimator, &acc, &gyr, &mag);
  acc_valid = 0;
  gyr_valid = 0;
  mag_valid = 0;
  updatecount = updatecount + 1;
  if (2 <= updatecount)
    {
      mossfw_deliver_data(getsarpipeline()->testestimatorcomponent.out[0], &magout);
      TestEstimator_getq(testestimator, &rot);
      rotout.qf.w = (int16_t) (rot.w * (float)(1 << 14));
      rotout.qf.x = (int16_t) (rot.x * (float)(1 << 14));
      rotout.qf.y = (int16_t) (rot.y * (float)(1 << 14));
      rotout.qf.z = (int16_t) (rot.z * (float)(1 << 14));
      mossfw_deliver_data(getsarpipeline()->testestimatorcomponent.out[1], &rotout);
      updatecount = 0;
    }

  return OK;
}

void testestimatorcomponent_create(struct component_s *com)
{
  mossfw_data_v3f_t initacc = { .x = 958.0f, .y = 675.0f, .z = -1849.0f };

  if (com != NULL) {
    com->in_num  = 3;
    com->op_num  = 1;
    com->out_num = 2;
    com->in  = malloc(com->in_num  * sizeof(void *));
    com->op  = malloc(com->op_num  * sizeof(void *));
    com->out = malloc(com->out_num * sizeof(void *));
    com->in[TestEstimatorCOMPONENT_INACC] = mossfw_input_create(TestEstimatorCOMPONENT_INPUTTYPE_ACC, TestEstimatorCOMPONENT_ACCBLKNUM);
    com->in[TestEstimatorCOMPONENT_INGYR] = mossfw_input_create(TestEstimatorCOMPONENT_INPUTTYPE_GYR, TestEstimatorCOMPONENT_GYRBLKNUM);
    com->in[TestEstimatorCOMPONENT_INMAG] = mossfw_input_create(TestEstimatorCOMPONENT_INPUTTYPE_MAG, TestEstimatorCOMPONENT_MAGBLKNUM);
    com->out[TestEstimatorCOMPONENT_OUTMAG] = mossfw_output_create(TestEstimatorCOMPONENT_OUTPUTTYPE_MAG);
    com->out[TestEstimatorCOMPONENT_OUTROT] = mossfw_output_create(TestEstimatorCOMPONENT_OUTPUTTYPE_ROT);
    com->op[0] = mossfw_callback_op_create(testestimatorcomponent_operate_cb, 0, false);
    mossfw_set_waitcondition(com->in[TestEstimatorCOMPONENT_INACC], 1 * sizeof(mossfw_data_v3s_t), com->op[0]);
    mossfw_set_waitcondition(com->in[TestEstimatorCOMPONENT_INGYR], 2 * sizeof(mossfw_data_v3s_t), com->op[0]);
    mossfw_set_waitcondition(com->in[TestEstimatorCOMPONENT_INMAG], 1 * sizeof(mossfw_data_v3s_t), com->op[0]);
    testestimator = TestEstimator_instance(0.0f, 100.0f / 3.0f, 0.0f, 0.0f, 0, 100.0f);
    initacc.x = initacc.x * 4.0f * g / (float)0x8000;
    initacc.y = initacc.y * 4.0f * g / (float)0x8000;
    initacc.z = initacc.z * 4.0f * g / (float)0x8000;
    TestEstimator_initimu(testestimator, &initacc);
  }
}

void testestimatorcomponent_delete(struct component_s *com)
{
    component_delete(com);
}
