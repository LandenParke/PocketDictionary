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
#include <string.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_component.h"
#include "mossfw/components/transform.h"
#include "mossfw/mossdsp.h"
#ifdef DEBUG_OUTPUT
#  include <stdio.h>
#endif

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

static struct sqmatrix3f_s param_gyr =
{
  .x =
    {.x = -1.0f, .y = 0.0f, .z = 0.0f},
  .y =
    {.x = 0.0f, .y = -1.0f, .z = 0.0f},
  .z =
    {.x = 0.0f, .y = 0.0f, .z = 1.0f}
};

static struct sqmatrix3f_s param_acc =
{
  .x =
    {.x = -1.0f, .y = 0.0f, .z = 0.0f},
  .y =
    {.x = 0.0f, .y = -1.0f, .z = 0.0f},
  .z =
    {.x = 0.0f, .y = 0.0f, .z = 1.0f}
};

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

#ifdef DEBUG_OUTPUT
/****************************************************************************
 * name: print
 ****************************************************************************/

static void print(unsigned int outdataid, mossfw_data_t * outdata,
                  size_t num)
{
  if (outdataid == TRANSFORM_ACC1)
    {
      for (size_t i = 0; i < num && outdata; i++)
        {
          printf("Transform ACC %0.16f %0.16f %0.16f\n",
                 outdata->data.xyzf[i].x, outdata->data.xyzf[i].y,
                 outdata->data.xyzf[i].z);
        }
    }

  else if (outdataid == TRANSFORM_GYR1)
    {
      for (size_t i = 0; i < num && outdata; i++)
        {
          printf("Transform GYR %0.16f %0.16f %0.16f\n",
                 outdata->data.xyzf[i].x, outdata->data.xyzf[i].y,
                 outdata->data.xyzf[i].z);
        }
    }
}

#endif

/****************************************************************************
 * name: transform_set_param
 ****************************************************************************/

void transform_set_param(struct sqmatrix3f_s *transform)
{
  param_acc = *transform;
  param_gyr = *transform;
}

/****************************************************************************
 * name: transform_main
 ****************************************************************************/

static int transform_main(mossfw_callback_op_t *in, unsigned long arg)
{
  int err = 0;
  int used;
  struct transform_s *com = getcomponent();
  int isize = mossfw_get_delivereddata_num(in->input);
  mossfw_data_t *idata =
    mossfw_get_delivereddata_array(in->input, isize, &used);
  const struct sqmatrix3f_s *param = NULL;
  mossfw_output_t *output = NULL;
  if (arg == TRANSFORM_ACC1)
    {
      param = &param_acc;
      output = com->outacc;
    }
  else
    {
      param = &param_gyr;
      output = com->outgyr;
    }

  size_t num = (size_t)isize / sizeof(mossfw_data_v3f_t);
  size_t osize = num * sizeof(mossfw_data_v3f_t);
  mossfw_data_t *odata = mossfw_data_alloc(com->alloc, osize, true);
  err = err || !odata;
  if (!err)
    {
      mossfw_data_v3f_t *iv3f = (mossfw_data_v3f_t *)&(idata->data.xyzf[0]);
      mossfw_data_v3f_t *ov3f = (mossfw_data_v3f_t *)&(odata->data.xyzf[0]);
      err = mossdsp_transformaxismv3f(ov3f, iv3f, num, param);
      odata->data_bytes = num * sizeof(mossfw_data_v3f_t);
      odata->timestamp = idata->timestamp;
    }

#ifdef DEBUG_OUTPUT
  print(arg, odata, num);
#endif
  err = err || mossfw_deliver_dataarray(output, odata);
  mossfw_data_free(idata);
  mossfw_data_free(odata);
  return err;
}

/****************************************************************************
 * name: transform_create
 ****************************************************************************/

struct transform_s *transform_create(mossfw_allocator_t *allocator)
{
  int err = 0;
  struct transform_s *ret = malloc(sizeof(struct transform_s));
  if (ret)
    {
      uint32_t type =
        MOSSFW_DATA_TYPE_FLOAT | MOSSFW_DATA_TYPEGRP_V3 |
        MOSSFW_DATA_TYPEARRAY_ARRAY;
      ret->inacc =
        mossfw_input_create(type | MOSSFW_DATA_TYPENAME_ACCEL, 1);
      ret->ingyr =
        mossfw_input_create(type | MOSSFW_DATA_TYPENAME_GYRO, 1);
      ret->opacc =
        mossfw_callback_op_create(transform_main, TRANSFORM_ACC1, false);
      ret->opgyr =
        mossfw_callback_op_create(transform_main, TRANSFORM_GYR1, false);
      ret->outacc =
        mossfw_output_create(type | MOSSFW_DATA_TYPENAME_ACCEL);
      ret->outgyr =
        mossfw_output_create(type | MOSSFW_DATA_TYPENAME_GYRO);
      ret->alloc = allocator;
      err = err || !ret->inacc || !ret->ingyr;
      err = err || !ret->opacc || !ret->opgyr;
      err = err || !ret->outacc || !ret->outgyr;
      err = err || !allocator;
      err = err ||
        mossfw_set_waitcondition(ret->inacc, sizeof(mossfw_data_v3f_t),
                                 ret->opacc);
      err = err ||
        mossfw_set_waitcondition(ret->ingyr, sizeof(mossfw_data_v3f_t),
                                 ret->opgyr);
    }

  if (err)
    {
      transform_delete(ret);
      ret = NULL;
    }

  setcomponent(ret);
  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: transform_delete
 ****************************************************************************/

void transform_delete(struct transform_s *com)
{
  if (com)
    {
      mossfw_output_delete(com->outacc);
      mossfw_output_delete(com->outgyr);
      mossfw_callback_op_delete(com->opacc);
      mossfw_callback_op_delete(com->opgyr);
      mossfw_input_delete(com->inacc);
      mossfw_input_delete(com->ingyr);
    }

  free(com);
}
