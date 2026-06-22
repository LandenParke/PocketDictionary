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
#include "average.h"
#include "sar.h"

#define AVERAGE_BLKNUM      (128)

#define AVERAGE_INPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPENAME_ACCEL + \
                           MOSSFW_DATA_TYPEARRAY_SINGLE)

#define AVERAGE_OUTPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                               MOSSFW_DATA_TYPEGRP_V3 + \
                               MOSSFW_DATA_TYPENAME_ACCEL + \
                               MOSSFW_DATA_TYPEARRAY_SINGLE)

static int average_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  mossfw_onedata_t data;
  mossfw_onedata_t result;
  unsigned int i;

  (void)arg;

  /*
   * Confirm if all needed data is collected.
   * Othewise, nothing to do.
   */

  mossfw_data_v3s_t acc[64];
  mossfw_data_v3s_t out[2];
  for (i = 0; i < 64; i++)
    {
        mossfw_get_delivereddata_single(in->input, &data);
        acc[i].x = data.v3s.x;
        acc[i].y = data.v3s.y;
        acc[i].z = data.v3s.z;
    }
  mossdsp_averagev3i(&out[0], &acc[0],  32);
  mossdsp_averagev3i(&out[1], &acc[32], 32);
  result.v3s.x = out[0].x;
  result.v3s.y = out[0].y;
  result.v3s.z = out[0].z;
  mossfw_deliver_data(getsarpipeline()->average.out[0], &result);
  result.v3s.x = out[1].x;
  result.v3s.y = out[1].y;
  result.v3s.z = out[1].z;
  mossfw_deliver_data(getsarpipeline()->average.out[0], &result);

  return OK;
}

void average_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in  = malloc(sizeof(void *));
      com->out = malloc(sizeof(void *));
      com->op  = malloc(sizeof(void *));
      *com->in  = mossfw_input_create(AVERAGE_INPUTTYPE, AVERAGE_BLKNUM);
      *com->out = mossfw_output_create(AVERAGE_OUTPUTTYPE);
      *com->op  = mossfw_callback_op_create(average_operate_cb, AVERAGE_INPUTTYPE, false);
      mossfw_set_waitcondition(*com->in, 64 * sizeof(mossfw_data_v3s_t), *com->op);
  }
}

void average_delete(struct component_s *com)
{
    component_delete(com);
}
