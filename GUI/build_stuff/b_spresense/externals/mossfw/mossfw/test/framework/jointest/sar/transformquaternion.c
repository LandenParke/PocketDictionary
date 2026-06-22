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
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "component.h"
#include "transformquaternion.h"
#include "sar.h"

#define TRANSFORMQUATERNION_BLKNUM      (2)
#define RAD_TO_DEG(rad) ((rad) * 180.0f / 3.1415926535897932384626433832795f)

#define TRANSFORMQUATERNION_INPUTTYPE (MOSSFW_DATA_TYPE_FLOAT + \
                              MOSSFW_DATA_TYPEGRP_Q + \
                              MOSSFW_DATA_TYPEARRAY_SINGLE)

#define TRANSFORMQUATERNION_OUTPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                               MOSSFW_DATA_TYPEGRP_V3 + \
                               MOSSFW_DATA_TYPEARRAY_SINGLE)

static int transformquaternion_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  mossfw_onedata_t data;
  mossfw_onedata_t result;
  mossfw_data_v3f_t outf;
  mossfw_data_v3s_t outi;
  float a12;
  float a22;
  float a31;
  float a32;
  float a33;
  unsigned int n = 0;

  (void)in;
  (void)arg;

  /*
   * Confirm if all needed data is collected.
   * Othewise, nothing to do.
   */

  mossfw_get_delivereddata_single(in->input, &data);
  a12 = 2.0f * (data.qf.x * data.qf.y - data.qf.z * data.qf.w);
  a22 = -data.qf.x * data.qf.x + data.qf.y * data.qf.y - data.qf.z * data.qf.z + data.qf.w * data.qf.w;
  a31 = 2.0f * (data.qf.x * data.qf.z - data.qf.y * data.qf.w);
  a32 = 2.0f * (data.qf.y * data.qf.z + data.qf.x * data.qf.w);
  a33 = -data.qf.x * data.qf.x - data.qf.y * data.qf.y + data.qf.z * data.qf.z +
         data.qf.w * data.qf.w;

  outf.x = RAD_TO_DEG(atan2f(a12, a22));
  if (outf.x < 0.0f)
    {
      outf.x = 360.0f + outf.x;
    }
  outf.y =
    RAD_TO_DEG(atan2f
                       (-a32, copysignf(sqrtf(a12 * a12 + a22 * a22), a33)));
  outf.z = RAD_TO_DEG(asinf(-a31));

  outi.x = ((int16_t) (outf.x * 64.0f)) >> 6;
  outi.y = ((int16_t) (outf.y * 64.0f)) >> 6;
  outi.z = ((int16_t) (outf.z * 64.0f)) >> 6;

  result.v3s.x = outi.x;
  result.v3s.y = outi.y;
  result.v3s.z = outi.z;
  mossfw_deliver_data(getsarpipeline()->transformquaternion.out[0], &result);
  return OK;
}

void transformquaternion_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in  = malloc(sizeof(void *));
      com->out = malloc(sizeof(void *));
      com->op  = malloc(sizeof(void *));
      *com->in  = mossfw_input_create(TRANSFORMQUATERNION_INPUTTYPE, TRANSFORMQUATERNION_BLKNUM);
      *com->out = mossfw_output_create(TRANSFORMQUATERNION_OUTPUTTYPE);
      *com->op  = mossfw_callback_op_create(transformquaternion_operate_cb, TRANSFORMQUATERNION_INPUTTYPE, false);
      mossfw_set_waitcondition(*com->in, sizeof(mossfw_data_qf_t), *com->op);
    }
}

void transformquaternion_delete(struct component_s *com)
{
    component_delete(com);
}
