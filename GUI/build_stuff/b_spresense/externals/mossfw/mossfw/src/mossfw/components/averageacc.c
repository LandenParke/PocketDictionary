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
#include <stdlib.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_component.h"
#include "mossfw/components/averageacc.h"
#ifdef DEBUG_OUTPUT
#  include <stdio.h>
#endif

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

static uint32_t accblknum = 107;
static void *component = NULL;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: getcomponent
 ****************************************************************************/

static void *getcomponent(void)
{
  return component;
}

/****************************************************************************
 * name: setcomponent
 ****************************************************************************/

void setcomponent(void *obj)
{
  component = obj;
}

/****************************************************************************
 * name: averageacc_setnum
 ****************************************************************************/

void averageacc_setnum(uint32_t num)
{
  accblknum = num;
}

/****************************************************************************
 * name: averageacc_main
 ****************************************************************************/

static int averageacc_main(struct mossfw_callback_op_s *in,
                            unsigned long arg)
{
  static uint32_t count = 0;
  static uint32_t accnum = 0;
  static mossfw_data_t *accumulate = NULL;
  int ret = 0;
  size_t num = 0;
  int size;
  int init = 0;
  int used;

  (void)arg;
  struct averageacc_s *com = getcomponent();
  size = mossfw_get_delivereddata_num(in->input);
  mossfw_data_t *indata =
    mossfw_get_delivereddata_array(in->input, size, &used);
  num = size / sizeof(mossfw_data_v3f_t);

  if (accumulate == NULL)
    {
      accumulate = indata;
      mossfw_data_refer(accumulate);
      init = 1;
    }

  for (size_t i = init; i < num; i++)
    {
      accumulate->data.xyzf->x += indata->data.xyzf[i].x;
      accumulate->data.xyzf->y += indata->data.xyzf[i].y;
      accumulate->data.xyzf->z += indata->data.xyzf[i].z;
      accumulate->timestamp     = indata->timestamp;
    }

  count = count + 1;
  accnum = accnum + num;
#ifdef DEBUG_OUTPUT
  printf("AverageAcc num = %lu, timestamp = %u\n", num, indata->timestamp);
#endif

  if (count == accblknum)
    {
      accumulate->data.xyzf->x = accumulate->data.xyzf->x / accnum;
      accumulate->data.xyzf->y = accumulate->data.xyzf->y / accnum;
      accumulate->data.xyzf->z = accumulate->data.xyzf->z / accnum;
#ifdef DEBUG_OUTPUT
      printf("AverageAcc %0.16f %0.16f %0.16f\n", accumulate->data.xyzf->x,
              accumulate->data.xyzf->y, accumulate->data.xyzf->z);
#endif
      ret = mossfw_deliver_dataarray(com->output, accumulate);
      mossfw_data_free(accumulate);
      accumulate = NULL;
      count = 0;
      accnum = 0;
    }

  mossfw_data_free(indata);
  return ret;
}

/****************************************************************************
 * name: averageacc_create
 ****************************************************************************/

struct averageacc_s *averageacc_create(mossfw_allocator_t *allocator)
{
  int err = 0;
  struct averageacc_s *ret = malloc(sizeof(struct averageacc_s));
  if (ret)
    {
      uint32_t type =
        MOSSFW_DATA_TYPE_FLOAT | MOSSFW_DATA_TYPEGRP_V3 |
        MOSSFW_DATA_TYPEARRAY_ARRAY;
      ret->input =
        mossfw_input_create(type | MOSSFW_DATA_TYPENAME_ACCEL, 5);
      ret->op = mossfw_callback_op_create(averageacc_main, 0, false);
      ret->output =
        mossfw_output_create(type | MOSSFW_DATA_TYPENAME_ACCEL);
      ret->allocator = allocator;
      err = err || !allocator;
      err = err || !ret->input;
      err = err || !ret->op;
      err = err || !ret->output;
      err = err ||
        mossfw_set_waitcondition(ret->input, sizeof(mossfw_data_v3f_t),
    ret->op);
    }

  if (err)
    {
      averageacc_delete(ret);
      ret = NULL;
    }

  setcomponent(ret);
  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: averageacc_delete
 ****************************************************************************/

void averageacc_delete(struct averageacc_s *averageacc)
{
  if (averageacc != NULL)
    {
      mossfw_output_delete(averageacc->output);
      mossfw_callback_op_delete(averageacc->op);
      mossfw_input_delete(averageacc->input);
    }

  free(averageacc);
}
