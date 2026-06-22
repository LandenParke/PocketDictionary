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
#include "mossfw/mossdsp.h"
#include "component.h"
#include "multiplyqf.h"
#include "sar.h"

#define MULTIPLYQF_BLKNUM      (2)

#define MULTIPLYQF_INPUTTYPE (MOSSFW_DATA_TYPE_FLOAT + \
                              MOSSFW_DATA_TYPEGRP_Q + \
                              MOSSFW_DATA_TYPEARRAY_SINGLE)

#define MULTIPLYQF_OUTPUTTYPE (MOSSFW_DATA_TYPE_FLOAT + \
                               MOSSFW_DATA_TYPEGRP_Q + \
                               MOSSFW_DATA_TYPEARRAY_SINGLE)

static int multiplyqf_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  mossfw_onedata_t data;
  mossfw_onedata_t result;
  mossfw_data_qf_t qin;
  mossfw_data_qf_t qout;
  const static mossfw_data_qf_t param = {
    .w = 0.987731278,
    .x = -0.0694560111,
    .y = -0.139513001,
    .z = -0.00994706526
  };

  (void)in;
  (void)arg;

  /*
   * Confirm if all needed data is collected.
   * Othewise, nothing to do.
   */

  mossfw_get_delivereddata_single(in->input, &data);
  qin.w = data.qf.w;
  qin.x = data.qf.x;
  qin.y = data.qf.y;
  qin.z = data.qf.z;
  (void)mossdsp_multiplyqf(&qout, &qin, &param, 1);
  result.qf.w = qout.w / 16384.0f;
  result.qf.x = qout.x / 16384.0f;
  result.qf.y = qout.y / 16384.0f;
  result.qf.z = qout.z / 16384.0f;
  mossfw_deliver_data(getsarpipeline()->multiplyqf.out[0], &result);
  return OK;
}

void multiplyqf_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in  = malloc(sizeof(void *));
      com->out = malloc(sizeof(void *));
      com->op  = malloc(sizeof(void *));
      *com->in  = mossfw_input_create(MULTIPLYQF_INPUTTYPE, MULTIPLYQF_BLKNUM);
      *com->out = mossfw_output_create(MULTIPLYQF_OUTPUTTYPE);
      *com->op  = mossfw_callback_op_create(multiplyqf_operate_cb, MULTIPLYQF_INPUTTYPE, false);
      mossfw_set_waitcondition(*com->in, sizeof(mossfw_data_qf_t), *com->op);
    }
}

void multiplyqf_delete(struct component_s *com)
{
    component_delete(com);
}
