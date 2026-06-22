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
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "component.h"
#include "ucresult_error.h"

#define UCRESULT_INPUTTYPE (MOSSFW_DATA_TYPE_CHAR + \
                            MOSSFW_DATA_TYPEGRP_V1 + \
                            MOSSFW_DATA_TYPEARRAY_ARRAY)

static const uint8_t ref[] = {
  20, 179, 19, 205, 21, 156
}; 

static unsigned int refnum = 0;

static int ucresult_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  static mossfw_data_t *result = NULL;
  int datanum = 6;
  int used;

  (void) arg;
  if (refnum == 0)
    {
      result = mossfw_get_delivereddata_array(in->input, datanum, &used);
      assert(result);
      assert((uint8_t)result->data.xc[0].x == ref[0]);
      assert((uint8_t)result->data.xc[1].x == ref[1]);
      assert((uint8_t)result->data.xc[2].x == ref[2]);
      assert((uint8_t)result->data.xc[3].x == ref[3]);
      assert((uint8_t)result->data.xc[4].x == ref[4]);
      assert((uint8_t)result->data.xc[5].x == ref[5]);
      mossfw_data_free(result);
    }
  refnum++;
  return OK;
}

void ucresult_error_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 0;
      com->op_num  = 1;
      com->in = malloc(com->in_num * sizeof(void *));
      com->op = malloc(com->op_num * sizeof(void *));
      com->out = NULL;
      *com->in = mossfw_input_create(UCRESULT_INPUTTYPE, 6);
      *com->op = mossfw_callback_op_create(ucresult_operate_cb, 0, false);
      mossfw_set_waitcondition(*com->in, 6 * sizeof(mossfw_data_v1c_t), *com->op);
    }
  refnum = 0;
}

void ucresult_error_delete(struct component_s *com)
{
  component_delete(com);
}

int ucerror_result_succeeded(void)
{
  return (refnum == 1);
}
