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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mossfw/mossfw_component.h"
#include "output.h"
#include "expecteddata.h"

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: output
 ****************************************************************************/

static int output(struct mossfw_callback_op_s *in, unsigned long arg)
{
  int ret = 0;
  int used;
  (void)arg;
  int sizer = mossfw_get_delivereddata_num(in->input);
  int sizei = mossfw_get_delivereddata_num(in->input->cb_next);
  mossfw_data_t *inr =
    mossfw_get_delivereddata_array(in->input, sizer, &used);
  mossfw_input_t *inputi = in->input->cb_next;
  mossfw_data_t *ini =
    mossfw_get_delivereddata_array(inputi, sizei, &used);
  int num = sizer / sizeof(mossfw_data_v1f_t);
  for (int i = 0; i < num; i++)
    {
      mossfw_data_qf_t indata;
      indata.w = inr->data.xf[i].x;
      indata.x = ini->data.xyzf[i].x;
      indata.y = ini->data.xyzf[i].y;
      indata.z = ini->data.xyzf[i].z;
      printf("%e %e %e %e\n", indata.w, indata.x, indata.y, indata.z);
      expecteddata(indata);
    }

  mossfw_data_free(inr);
  mossfw_data_free(ini);
  return ret;
}

/****************************************************************************
 * name: output_create
 ****************************************************************************/

struct output_s *output_create(void)
{
  int err = 0;
  struct output_s *ret = malloc(sizeof(struct output_s));
  if (ret)
    {
      uint32_t type = MOSSFW_DATA_TYPE_FLOAT |
        MOSSFW_DATA_TYPEARRAY_ARRAY;
      size_t sizef = sizeof(mossfw_data_v1f_t);
      size_t size3f = sizeof(mossfw_data_v3f_t);
      ret->inr = mossfw_input_create(type | MOSSFW_DATA_TYPEGRP_V1, 1);
      ret->ini = mossfw_input_create(type | MOSSFW_DATA_TYPEGRP_V3, 1);
      ret->op = mossfw_callback_op_create(output, 0, false);
      err = err || !ret->inr || !ret->ini;
      err = err || !ret->op;
      err = err || mossfw_set_waitcondition(ret->inr, sizef, ret->op);
      err = err || mossfw_set_waitcondition(ret->ini, size3f, ret->op);
    }

  if (err)
    {
      output_delete(ret);
      ret = NULL;
    }

  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: output_delete
 ****************************************************************************/

void output_delete(struct output_s *com)
{
  if (com)
    {
      mossfw_callback_op_delete(com->op);
      mossfw_input_delete(com->inr);
      mossfw_input_delete(com->ini);
    }

  free(com);
}
