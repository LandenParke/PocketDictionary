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
#include "mossfw/mosscalib.h"
#include "mossfw/mossfw_component.h"
#include "mossfw/mossfw_data.h"
#include "mossfw/components/eiscalibration.h"
#ifdef DEBUG_OUTPUT
#  include <stdio.h>
#endif

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

static struct mosscalib_adjust_param_s param_acc =
{
  .bias.f =
    {
      .x = -0.00009124391909f,
      .y = 0.00013157300316f,
      .z = 0.00061742110802f
    },
  .scalefactor =
    {
    .x =
      {
        .x = 0.9932296872138977f,
        .y = 0.0f,
        .z = 0.0f
      },
    .y =
      {
        .x = 0.0f,
        .y = 0.9976474046707153f,
        .z = 0.0f
      },
    .z =
      {
        .x = 0.0f,
        .y = 0.0f,
        .z = 0.9727051854133606f
      }
    },
  .misalignment =
    {
    .x =
      {
        .x = 1.0f,
        .y = 0.0022878649178892f,
        .z = -0.0111410999670625f
      },
    .y =
      {
        .x = 0.0f,
        .y = 1.0000000000000000f,
        .z = 0.0018858800176531f
      },
    .z =
      {
        .x = 0.0f,
        .y = 0.0000000000000000f,
        .z = 1.0000000000000000f
      }
  }
};

static struct mosscalib_adjust_param_s param_gyr =
{
  .bias.f =
    {
      .x = -0.12497810530476f,
      .y = -1.21626199688762f,
      .z = 1.12496595829725f
    },
  .scalefactor =
    {
      .x =
        {
          .x = 0.9784178137779236f,
          .y = 0.0f,
          .z = 0.0f},
      .y =
        {
          .x = 0.0f,
          .y = 1.0078259706497192f,
          .z = 0.0f},
      .z =
        {
          .x = 0.0f,
          .y = 0.0f,
          .z = 0.9969930052757263f}
    },
  .misalignment =
    {
      .x =
        {
          .x = 1.0f,
          .y = 0.0048000421375036f,
          .z = -0.0103387897834182f
        },
      .y =
        {
          .x = -0.0065536201000214f,
          .y = 1.0f,
          .z = 0.0002426705032121f
        },
      .z =
        {
          .x = 0.0087586073204875f,
          .y = -0.0016777249984443f,
          .z = 1.0f
        }
    }
};

static float accres = 1.0f;
static float gyrres = 1.0f;

static void *component = NULL;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: calibration_set_resolution
 ****************************************************************************/

void calibration_set_resolution(float acc_mps2, float gyr_dps)
{
  accres = acc_mps2;
  gyrres = gyr_dps;
}

/****************************************************************************
 * name: calibration_set_param
 ****************************************************************************/

void calibration_set_param(struct mosscalib_adjust_param_s *acc,
                           struct mosscalib_adjust_param_s *gyr)
{
  param_acc = *acc;
  param_gyr = *gyr;
}

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
 * name: calibration_main
 ****************************************************************************/

static int calibration_main(mossfw_callback_op_t *in, unsigned long arg)
{
  int err = 0;
  mossfw_output_t *output = NULL;
  struct mosscalib_adjust_param_s *param = NULL;
  float coef = 0.0f;
  uint32_t *lasttimestamp = NULL;
  int used = 0;

  struct eiscalibration_s *com = getcomponent();
  int size = mossfw_get_delivereddata_num(in->input);
  mossfw_data_t *indata =
    mossfw_get_delivereddata_array(in->input, size, &used);
  if (arg == ID_DATA_ACC1)
    {
      param = &param_acc;
      coef = accres / 1000.0f;
      lasttimestamp = &com->acclasttimestamp;
      output = com->outacc;
    }
  else
    {
      param = &param_gyr;
      coef = gyrres;
      lasttimestamp = &com->gyrlasttimestamp;
      output = com->outgyr;
    }

  size_t num = (size_t)size / sizeof(mossfw_data_v3s_t);
  mossfw_data_t *outdata =
    mossfw_data_alloc(com->alloc, sizeof(mossfw_data_v3f_t), true);
  err = err || !outdata;
  for (size_t i = 0; i < num && !err; i++)
    {
      outdata->data.xyzf[i].x = indata->data.xyzs[i].x * coef;
      outdata->data.xyzf[i].y = indata->data.xyzs[i].y * coef;
      outdata->data.xyzf[i].z = indata->data.xyzs[i].z * coef;
    }

  if (!err)
    {
      outdata->timestamp = (*lasttimestamp & 0xffff0000) | indata->timestamp;
      if ((uint32_t) indata->timestamp < (*lasttimestamp & 0xffff))
        {
          outdata->timestamp = outdata->timestamp + 0x10000u;
        }

      *lasttimestamp = outdata->timestamp;
      mosscalib_adjustv3f((mossfw_data_v3f_t *)outdata->data.xyzf,
                  (mossfw_data_v3f_t *)outdata->data.xyzf, num, 0.0f, param);
      outdata->data_bytes = sizeof(mossfw_data_v3f_t);
    }

#ifdef DEBUG_OUTPUT
  if (arg == ID_DATA_ACC1)
    {
      for (i = 0; i < num; i++)
        {
          printf("ImuCalibration ACC1 %0.16f %0.16f %0.16f %u\n",
                 outdata->data.xyzf[i].x, outdata->data.xyzf[i].y,
                 outdata->data.xyzf[i].z, (uint32_t) outdata->timestamp);
        }
    }
  else if (arg == ID_DATA_GYR1)
    {
      for (i = 0; i < num; i++)
        {
          printf("ImuCalibration GYR1 %0.16f %0.16f %0.16f %u\n",
                 outdata->data.xyzf[i].x, outdata->data.xyzf[i].y,
                 outdata->data.xyzf[i].z, (uint32_t) outdata->timestamp);
        }
    }

#endif

  err = err || mossfw_deliver_dataarray(output, outdata);
  mossfw_data_free(indata);
  mossfw_data_free(outdata);
  return err;
}

/****************************************************************************
 * name: eiscalibration_create
 ****************************************************************************/

struct eiscalibration_s *eiscalibration_create(mossfw_allocator_t *allocator)
{
  int err = 0;
  struct eiscalibration_s *ret = malloc(sizeof(struct eiscalibration_s));
  if (ret)
    {
      uint32_t itype =
        MOSSFW_DATA_TYPE_SHORT | MOSSFW_DATA_TYPEGRP_V3 |
        MOSSFW_DATA_TYPEARRAY_ARRAY;
      uint32_t otype =
        MOSSFW_DATA_TYPE_FLOAT | MOSSFW_DATA_TYPEGRP_V3 |
        MOSSFW_DATA_TYPEARRAY_ARRAY;
      ret->inacc =
        mossfw_input_create(itype | MOSSFW_DATA_TYPENAME_ACCEL, 1);
      ret->ingyr =
        mossfw_input_create(itype | MOSSFW_DATA_TYPENAME_GYRO, 1);
      ret->opacc =
        mossfw_callback_op_create(calibration_main, ID_DATA_ACC1, false);
      ret->opgyr =
        mossfw_callback_op_create(calibration_main, ID_DATA_GYR1, false);
      ret->outacc =
        mossfw_output_create(otype | MOSSFW_DATA_TYPENAME_ACCEL);
      ret->outgyr =
        mossfw_output_create(otype | MOSSFW_DATA_TYPENAME_GYRO);
      ret->alloc = allocator;
      ret->acclasttimestamp = 0;
      ret->gyrlasttimestamp = 0;
      err = err || !ret->inacc || !ret->ingyr;
      err = err || !ret->opacc || !ret->opgyr;
      err = err || !ret->outacc || !ret->outgyr;
      err = err || !allocator;
      err = err ||
        mossfw_set_waitcondition(ret->inacc, sizeof(mossfw_data_v3s_t),
                                 ret->opacc);
      err = err ||
        mossfw_set_waitcondition(ret->ingyr, sizeof(mossfw_data_v3s_t),
                                 ret->opgyr);
    }

  if (err)
    {
      eiscalibration_delete(ret);
      ret = NULL;
    }

  setcomponent(ret);
  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: eiscalibration_delete
 ****************************************************************************/

void eiscalibration_delete(struct eiscalibration_s *eiscalibration)
{
  if (eiscalibration)
    {
      mossfw_output_delete(eiscalibration->outacc);
      mossfw_output_delete(eiscalibration->outgyr);
      mossfw_callback_op_delete(eiscalibration->opacc);
      mossfw_callback_op_delete(eiscalibration->opgyr);
      mossfw_input_delete(eiscalibration->inacc);
      mossfw_input_delete(eiscalibration->ingyr);
    }

  free(eiscalibration);
}
