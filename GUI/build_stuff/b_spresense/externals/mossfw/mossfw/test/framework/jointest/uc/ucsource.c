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
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "component.h"
#include "ucsource.h"
#include "uc.h"

#define UCSOURCE_OUTPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                            MOSSFW_DATA_TYPEGRP_V3 + \
                            MOSSFW_DATA_TYPENAME_ACCEL + \
                            MOSSFW_DATA_TYPEARRAY_ARRAY)

static mossfw_allocator_t *allocator = NULL;

static mossfw_data_v3s_t user_data[] = {
    {.x = 16615, .y = 496, .z = -32768},
    {.x = -441, .y = 21479, .z = 746},
    {.x = 12, .y = 27120, .z = 11648},
    {.x = -3863, .y = 20299, .z = 240},
    {.x = 2, .y = 697, .z = 692},
    {.x = 6, .y = 2137, .z = 2122},
    {.x = 10, .y = 2874, .z = 2861},
    {.x = 5, .y = 2874, .z = 2858},
    {.x = -3, .y = 2879, .z = 2856},
    {.x = 1, .y = 2874, .z = 2865},
    {.x = 6, .y = 2870, .z = 2870},
    {.x = 2, .y = 2869, .z = 2867},
    {.x = -3, .y = 2870, .z = 2865},
    {.x = -3, .y = 2872, .z = 2864}
};

static int ucsource_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  mossfw_data_t *data;
  int ret = 0;
  size_t i;

  for (i = 0; i < sizeof user_data / sizeof user_data[0]; i++)
    {
      data = mossfw_data_alloc(allocator, sizeof user_data[0], true);
      data->data.v3s[0] = user_data[i];
      data->data_bytes = sizeof data->data.v3s[0];
      mossfw_deliver_dataarray(getucpipeline()->ucsource.out[0], data);
      mossfw_data_free(data);
    }
  return ret;
}

void ucsource_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 0;
      com->out_num = 1;
      com->op_num  = 1;
      com->in = NULL;
      com->out = malloc(com->out_num * sizeof(void *));
      com->op = malloc(com->op_num * sizeof(void *));
      if (allocator == NULL)
        {
          allocator = mossfw_fixedmem_create(sizeof(mossfw_data_v3s_t), 2 * sizeof user_data / sizeof user_data[0]);
        }
      *com->out = mossfw_output_create(UCSOURCE_OUTPUTTYPE);
      *com->op  = mossfw_callback_op_create(ucsource_operate_cb, 0, false);
    }
}

void ucsource_delete(struct component_s *com)
{
    component_delete(com);
    if (allocator != NULL)
      {
        mossfw_fixedmem_delete(allocator);
        allocator = NULL;
      }
}
