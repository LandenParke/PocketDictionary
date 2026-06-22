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

#include <stdio.h>
#include <assert.h>
#include "mossfw/sensorlib.h"
#include "sample_attitude.h"
#include "expecteddata.h"
#include "inputdata.h"

/****************************************************************************
 * Private Data
 ****************************************************************************/

static struct sqmatrix3f_s transform =
{
  .x =
    {
      .x = -1.0f, .y = 0.0f, .z = 0.0f
    },
  .y =
    {
      .x = 0.0f, .y = -1.0f, .z = 0.0f
    },
  .z =
    {
      .x = 0.0f, .y = 0.0f, .z = 1.0f
    }
};

static struct mosscalib_adjust_param_s acc_calibration =
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
          .x = 0.9932296872138977f, .y = 0.0f, .z = 0.0f
        },
      .y =
        {
          .x = 0.0f, .y = 0.9976474046707153f, .z = 0.0f
        },
      .z =
        {
          .x = 0.0f, .y = 0.0f, .z = 0.9727051854133606f
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

static struct mosscalib_adjust_param_s gyr_calibration =
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
        .x = 0.9784178137779236f, .y = 0.0f, .z = 0.0f
      },
    .y =
      {
        .x = 0.0f, .y = 1.0078259706497192f, .z = 0.0f
      },
    .z =
      {
        .x = 0.0f, .y = 0.0f, .z = 0.9969930052757263f
      }
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

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: sample_attitude
 ****************************************************************************/

int sample_attitude(void)
{
  size_t i;
  struct attitude_s *attitude = sample_attitude_initialization();
  sample_attitude_set_time_resolution(100);
  sample_attitude_set_resolution((16.0f * 9.8f) / 32768.0f,
                                 2000.0f / 32800.0f);
  sample_attitude_set_calibration(&acc_calibration, &gyr_calibration);
  sample_attitude_set_transform(&transform);
  int err = 0;

  err = attitude == NULL;

  /* frame 0 */

  for (i = 0; i < sizeof acc10 / sizeof(mossfw_data_v3ts_t) && !err; i++)
    {
      err = err || sample_attitude_input(attitude, &acc10[i], &gyr10[i], 1);
    }

  /* frame 1 */

  sample_attitude_reset_lpf();
  for (i = 0; i < sizeof acc14 / sizeof(mossfw_data_v3ts_t) && !err; i++)
    {
      err = err || sample_attitude_input(attitude, &acc14[i], &gyr14[i], 1);
    }

  sample_attitude_finalization(attitude);
  return err;
}

/****************************************************************************
 * name: main
 ****************************************************************************/

int main(void)
{
  int err = sample_attitude();
#ifdef TEST_ASSERTION
  assert(expecteddata_completed());
  printf("sample_attitude passed\n");
#endif
  return err;
}
