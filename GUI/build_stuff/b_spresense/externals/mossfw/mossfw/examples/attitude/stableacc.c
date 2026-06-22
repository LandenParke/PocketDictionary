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
#include <math.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_component.h"
#include "stableacc.h"
#ifdef DEBUG_OUTPUT
#  include <stdio.h>
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

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

static void setcomponent(void *obj)
{
  component = obj;
}

/****************************************************************************
 * name: variancev3tf
 ****************************************************************************/

static mossfw_data_v3f_t variancev3tf(mossfw_data_v3tf_t *data, int len)
{
  mossfw_data_v3f_t ret;
  float sumx = 0.0f;
  float sumy = 0.0f;
  float sumz = 0.0f;
  float sqsumx = 0.0f;
  float sqsumy = 0.0f;
  float sqsumz = 0.0f;
  float averagex = 0.0f;
  float averagey = 0.0f;
  float averagez = 0.0f;
  for (int i = 0; i < len; i++)
    {
      sumx += data[i].x;
      sumy += data[i].y;
      sumz += data[i].z;
      sqsumx += data[i].x * data[i].x;
      sqsumy += data[i].y * data[i].y;
      sqsumz += data[i].z * data[i].z;
    }

  averagex = sumx / len;
  averagey = sumy / len;
  averagez = sumz / len;
  ret.x = ((sqsumx * sqsumx) / len) - (averagex * averagex);
  ret.y = ((sqsumy * sqsumy) / len) - (averagey * averagey);
  ret.z = ((sqsumz * sqsumz) / len) - (averagez * averagez);
  return ret;
}

/****************************************************************************
 * name: stableacc_main
 ****************************************************************************/

static int stableacc_main(struct mossfw_callback_op_s *in, unsigned long arg)
{
  static mossfw_data_v3tf_t mean[] =
  {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
  };

  int err = 0;
  int used;
  size_t len = sizeof mean / sizeof(mossfw_data_v3tf_t);
  float dt = 0.0f;
  float threshold = 0.0f;

  (void)arg;
  struct stableacc_s *com = getcomponent();
  int size = mossfw_get_delivereddata_num(in->input);
  mossfw_data_t *ina =
    mossfw_get_delivereddata_array(in->input, size, &used);

  for (size_t i = 0; i < len - 1; i++)
    {
      mean[i] = mean[i + 1];
    }

  mean[len - 1].x = ina->data.v3f->x;
  mean[len - 1].y = ina->data.v3f->y;
  mean[len - 1].z = ina->data.v3f->z;
  mean[len - 1].t = ina->timestamp;
  for (size_t i = 0; i < len - 1; i++)
    {
      dt += (mean[i + 1].t - mean[i].t) / 1000000.0f;
    }

  mossfw_data_v3f_t variance = variancev3tf(mean, len);
  size_t sizes = sizeof(mossfw_data_v1s_t);
  mossfw_data_t *datastable =
    mossfw_data_alloc(com->alloc, sizes, true);
  err = err || !datastable;
  if (datastable)
    {
      float sqlen = mean[len - 1].x * mean[len - 1].x +
                    mean[len - 1].y * mean[len - 1].y +
                    mean[len - 1].z * mean[len - 1].z;
      threshold = 0.25 * sqlen * dt * dt;
      datastable->data.xs->x = threshold > variance.x &&
                               threshold > variance.y &&
                               threshold > variance.z;
      datastable->data_bytes = sizeof(mossfw_data_v1s_t);
    }

#ifdef DEBUG_OUTPUT
  printf(
    "StableAcc dt = %e, variance.x = %e, variance.y = %e, variance.z = %e\n",
    dt, variance.x, variance.y, variance.z);
  printf("StableAcc threshold = %e, stable = %d\n",
            threshold, datastable->data.xs->x);
  printf("StableAcc %u, %e, %e, %e, %d\n", ina->timestamp, ina->data.xyzf->x,
            ina->data.xyzf->y, ina->data.xyzf->z, datastable->data.xs->x);
#endif

  err = err || mossfw_deliver_dataarray(com->outacc, ina);
  err = err || mossfw_deliver_dataarray(com->outstbl, datastable);
  mossfw_data_free(ina);
  mossfw_data_free(datastable);
  return err;
}

/****************************************************************************
 * name: stableacc_create
 ****************************************************************************/

struct stableacc_s *stableacc_create(mossfw_allocator_t *allocator)
{
  int err = 0;
  struct stableacc_s *ret = malloc(sizeof(struct stableacc_s));
  if (ret)
    {
      uint32_t typeacc = MOSSFW_DATA_TYPE_FLOAT |
        MOSSFW_DATA_TYPEGRP_V3 |
        MOSSFW_DATA_TYPENAME_ACCEL | MOSSFW_DATA_TYPEARRAY_ARRAY;
      uint32_t typestable = MOSSFW_DATA_TYPE_SHORT |
        MOSSFW_DATA_TYPEGRP_V1 |
        MOSSFW_DATA_TYPENAME_ACCEL | MOSSFW_DATA_TYPEARRAY_ARRAY;
      ret->input = mossfw_input_create(typeacc, 1);
      ret->op = mossfw_callback_op_create(stableacc_main, 0, false);
      ret->outstbl = mossfw_output_create(typestable);
      ret->outacc = mossfw_output_create(typeacc);
      ret->alloc = allocator;
      err = err || !ret->input;
      err = err || !ret->op;
      err = err || !ret->outstbl || !ret->outacc;
      err = err || !allocator;
      size_t size = sizeof(mossfw_data_v3f_t);
      err = err || mossfw_set_waitcondition(ret->input, size, ret->op);
    }

  if (err)
    {
      stableacc_delete(ret);
      ret = NULL;
    }

  setcomponent(ret);
  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: stableacc_delete
 ****************************************************************************/

void stableacc_delete(struct stableacc_s *stableacc)
{
  if (stableacc)
    {
      mossfw_output_delete(stableacc->outacc);
      mossfw_output_delete(stableacc->outstbl);
      mossfw_callback_op_delete(stableacc->op);
      mossfw_input_delete(stableacc->input);
    }

  free(stableacc);
}
