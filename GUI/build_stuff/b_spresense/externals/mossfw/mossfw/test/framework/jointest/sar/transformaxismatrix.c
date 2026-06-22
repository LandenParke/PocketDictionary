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
#include "transformaxismatrix.h"
#include "sar.h"

#define TRANSFORMAXISMATRIX_BLKNUM      (2)

#define TRANSFORMAXISMATRIX_INPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                              MOSSFW_DATA_TYPEGRP_V3 + \
                              MOSSFW_DATA_TYPEARRAY_SINGLE)

#define TRANSFORMAXISMATRIX_OUTPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                               MOSSFW_DATA_TYPEGRP_V3 + \
                               MOSSFW_DATA_TYPEARRAY_SINGLE)

static int transformaxismatrix_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  mossfw_onedata_t data;
  mossfw_onedata_t result;
  mossfw_data_v3s_t tin;
  mossfw_data_v3s_t out;
  static const struct sqmatrix3i_s param = {
    .x.x = 0, .x.y =  0, .x.z = -1,
    .y.x = 1, .y.y =  0, .y.z =  0,
    .z.x = 0, .z.y = -1, .z.z =  0
  };
  unsigned int n = 0;

  (void)arg;

  /*
   * Confirm if all needed data is collected.
   * Othewise, nothing to do.
   */

  mossfw_output_t *outacc = getsarpipeline()->transformaxismatrix_acc.out[0];
  mossfw_output_t *outgyr = getsarpipeline()->transformaxismatrix_gyr.out[0];
  mossfw_output_t *outmag = getsarpipeline()->transformaxismatrix_mag.out[0];
  mossfw_callback_op_t *acc = getsarpipeline()->transformaxismatrix_acc.op[0];
  mossfw_callback_op_t *gyr = getsarpipeline()->transformaxismatrix_gyr.op[0];
  mossfw_callback_op_t *mag = getsarpipeline()->transformaxismatrix_mag.op[0];
  mossfw_output_t *output = (in == acc) ? outacc : (in == gyr ? outgyr : outmag);
  mossfw_get_delivereddata_single(in->input, &data);
  tin.x = data.v3s.x;
  tin.y = data.v3s.y;
  tin.z = data.v3s.z;
  (void)mossdsp_transformaxismv3i(&out, &tin, 1, &param);
  result.v3s.x = out.x;
  result.v3s.y = out.y;
  result.v3s.z = out.z;
  mossfw_deliver_data(output, &result);
  return OK;
}

void transformaxismatrix_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in  = malloc(sizeof(void *));
      com->out = malloc(sizeof(void *));
      com->op  = malloc(sizeof(void *));
      *com->in = mossfw_input_create(TRANSFORMAXISMATRIX_INPUTTYPE, TRANSFORMAXISMATRIX_BLKNUM);
      *com->out = mossfw_output_create(TRANSFORMAXISMATRIX_OUTPUTTYPE);
      *com->op = mossfw_callback_op_create(transformaxismatrix_operate_cb, TRANSFORMAXISMATRIX_INPUTTYPE, false);
      mossfw_set_waitcondition(*com->in, sizeof(mossfw_data_v3s_t), *com->op);
    }
}

void transformaxismatrix_delete(struct component_s *com)
{
    component_delete(com);
}
