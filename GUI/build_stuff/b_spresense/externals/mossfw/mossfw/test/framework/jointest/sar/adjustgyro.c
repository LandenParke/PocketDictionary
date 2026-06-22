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
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "component.h"
#include "adjustgyro.h"
#include "sar.h"

#define ADJUSTGYRO_BLKNUM      (2)

#define ADJUSTGYRO_INPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                              MOSSFW_DATA_TYPEGRP_V3 + \
                              MOSSFW_DATA_TYPENAME_GYRO + \
                              MOSSFW_DATA_TYPEARRAY_SINGLE)

#define ADJUSTGYRO_OUTPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                               MOSSFW_DATA_TYPEGRP_V3 + \
                               MOSSFW_DATA_TYPENAME_GYRO + \
                               MOSSFW_DATA_TYPEARRAY_SINGLE)

static int adjustgyro_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  mossfw_data_v3s_t gyro_offset = {.x = 1,.y = -3,.z = 5 };
  mossfw_onedata_t gyro;
  mossfw_onedata_t result;

  (void)in;
  (void)arg;

  /*
   * Confirm if all needed data is collected.
   * Othewise, nothing to do.
   */

  mossfw_get_delivereddata_single(in->input,  &gyro);

  result.v3s.x = gyro.v3s.x - gyro_offset.x;
  result.v3s.y = gyro.v3s.y - gyro_offset.y;
  result.v3s.z = gyro.v3s.z - gyro_offset.z;

  mossfw_deliver_data(getsarpipeline()->adjustgyro.out[0], &result);

  return OK;
}

void adjustgyro_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in  = malloc(com->in_num  * sizeof(void *));
      com->out = malloc(com->out_num * sizeof(void *));
      com->op  = malloc(com->op_num  * sizeof(void *));
      *(com->in)  = mossfw_input_create(ADJUSTGYRO_INPUTTYPE, ADJUSTGYRO_BLKNUM);
      *(com->out) = mossfw_output_create(ADJUSTGYRO_OUTPUTTYPE);
      *(com->op)  = mossfw_callback_op_create(adjustgyro_operate_cb, ADJUSTGYRO_INPUTTYPE, false);
      mossfw_set_waitcondition(*(com->in), sizeof(mossfw_data_v3s_t), *(com->op));
    }
}

void adjustgyro_delete(struct component_s *com)
{
    component_delete(com);
}
