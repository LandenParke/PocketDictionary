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
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "mossfw/mossdsp.h"
#include "component.h"
#include "transformaxisquaternion.h"
#include "sar.h"

#define TRANSFORMAXISQUATERNION_BLKNUM      (2)

#define TRANSFORMAXISQUATERNION_INPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                              MOSSFW_DATA_TYPEGRP_V3 + \
                              MOSSFW_DATA_TYPEARRAY_SINGLE)

#define TRANSFORMAXISQUATERNION_OUTPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                               MOSSFW_DATA_TYPEGRP_V3 + \
                               MOSSFW_DATA_TYPEARRAY_SINGLE)

static int transformaxisquaternion_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  mossfw_onedata_t data;
  mossfw_onedata_t result;
  mossfw_data_v3f_t tin;
  mossfw_data_v3f_t out;
  const mossfw_data_qf_t param = {
    .w = 0.9877312779f,
    .x = 0.06945601106f,
    .y = 0.1395130008f,
    .z = 0.009947065264f
  };
  unsigned int n = 0;

  (void)arg;

  /*
   * Confirm if all needed data is collected.
   * Othewise, nothing to do.
   */

  mossfw_output_t *outacc = getsarpipeline()->transformaxisquaternion_acc.out[0];
  mossfw_output_t *outgyr = getsarpipeline()->transformaxisquaternion_gyr.out[0];
  mossfw_output_t *outmag = getsarpipeline()->transformaxisquaternion_mag.out[0];
  mossfw_callback_op_t *acc = getsarpipeline()->transformaxisquaternion_acc.op[0];
  mossfw_callback_op_t *gyr = getsarpipeline()->transformaxisquaternion_gyr.op[0];
  mossfw_callback_op_t *mag = getsarpipeline()->transformaxisquaternion_mag.op[0];
  mossfw_output_t *output = (in == acc) ? outacc : (in == gyr ? outgyr : outmag);
  mossfw_get_delivereddata_single(in->input, &data);
  tin.x = data.v3s.x;
  tin.y = data.v3s.y;
  tin.z = data.v3s.z;
  (void)mossdsp_transformaxisqv3f(&out, &tin, 1, &param);
  result.v3s.x = out.x;
  result.v3s.y = out.y;
  result.v3s.z = out.z;
  mossfw_deliver_data(output, &result);
  return OK;
}

void transformaxisquaternion_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in  = malloc(sizeof(void *));
      com->out = malloc(sizeof(void *));
      com->op  = malloc(sizeof(void *));
      *com->in = mossfw_input_create(TRANSFORMAXISQUATERNION_INPUTTYPE, TRANSFORMAXISQUATERNION_BLKNUM);
      *com->out = mossfw_output_create(TRANSFORMAXISQUATERNION_OUTPUTTYPE);
      *com->op = mossfw_callback_op_create(transformaxisquaternion_operate_cb, TRANSFORMAXISQUATERNION_INPUTTYPE, false);
      mossfw_set_waitcondition(*com->in, sizeof(mossfw_data_v3s_t), *com->op);
  }
}

void transformaxisquaternion_delete(struct component_s *com)
{
    component_delete(com);
}
