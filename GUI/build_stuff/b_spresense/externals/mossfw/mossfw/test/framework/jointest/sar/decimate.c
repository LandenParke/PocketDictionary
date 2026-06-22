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
#include "component.h"
#include "decimate.h"
#include "sar.h"

#define DECIMATE_BLKNUM      (8)

#define DECIMATE_INPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPEARRAY_SINGLE)

#define DECIMATE_OUTPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                               MOSSFW_DATA_TYPEGRP_V3 + \
                               MOSSFW_DATA_TYPEARRAY_SINGLE)

static int decimate_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  mossfw_onedata_t data;
  unsigned int n = 0;
  unsigned int i;

  /*
   * Confirm if all needed data is collected.
   * Othewise, nothing to do.
   */

  for (i = 0; i < arg; i++)
    {
      mossfw_get_delivereddata_single(in->input, &data);
    }
  mossfw_output_t *outacc = getsarpipeline()->decimate_acc.out[0];
  mossfw_output_t *outgyr = getsarpipeline()->decimate_gyr.out[0];
  mossfw_deliver_data(arg == 2 ? outacc : outgyr, &data);

  return OK;
}

void decimate_create(struct component_s *com, unsigned long param)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in  = malloc(sizeof(void *));
      com->out = malloc(sizeof(void *));
      com->op  = malloc(sizeof(void *));
      *com->in  = mossfw_input_create(DECIMATE_INPUTTYPE, DECIMATE_BLKNUM);
      *com->out = mossfw_output_create(DECIMATE_OUTPUTTYPE);
      *com->op  = mossfw_callback_op_create(decimate_operate_cb, param, false);
      mossfw_set_waitcondition(*com->in, param * sizeof(mossfw_data_v3s_t), *com->op);
    }
}

void decimate_delete(struct component_s *com)
{
    component_delete(com);
}
