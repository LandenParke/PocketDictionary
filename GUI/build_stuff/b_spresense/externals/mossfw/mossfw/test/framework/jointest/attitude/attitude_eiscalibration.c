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
#include <stdlib.h>
#include <assert.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "mossfw/mosscalib.h"
#include "attitudesource.h"
#include "attitude_eiscalibration.h"
#include "attitude.h"
//#define DEBUG_OUTPUT

#define EISCALIBRATION_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_SHORT + \
                                      MOSSFW_DATA_TYPEGRP_V3 + \
                                      MOSSFW_DATA_TYPENAME_ACCEL + \
                                      MOSSFW_DATA_TYPEARRAY_SINGLE)
#define EISCALIBRATION_INPUTTYPE_GYR (MOSSFW_DATA_TYPE_SHORT + \
                                      MOSSFW_DATA_TYPEGRP_V3 + \
                                      MOSSFW_DATA_TYPENAME_GYRO + \
                                      MOSSFW_DATA_TYPEARRAY_SINGLE)
#define EISCALIBRATION_OUTPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                                      MOSSFW_DATA_TYPEGRP_V3 + \
                                      MOSSFW_DATA_TYPENAME_ACCEL + \
                                      MOSSFW_DATA_TYPEARRAY_SINGLE)
#define EISCALIBRATION_OUTPUTTYPE_GYR (MOSSFW_DATA_TYPE_FLOAT + \
                                      MOSSFW_DATA_TYPEGRP_V3 + \
                                      MOSSFW_DATA_TYPENAME_GYRO + \
                                      MOSSFW_DATA_TYPEARRAY_SINGLE)
#define EISCALIBRATION_MAXBLOCK (16 * 4)

static mossfw_allocator_t *allocator = NULL;

static struct mosscalib_adjust_param_s param_acc = {
  .bias.f = {.x = -0.00009124391909f,
             .y = 0.00013157300316f,
             .z = 0.00061742110802f},
  .scalefactor = {
                  .x = {.x = 0.9932296872138977f,.y = 0.0f,.z = 0.0f},
                  .y = {.x = 0.0f,.y = 0.9976474046707153f,.z = 0.0f},
                  .z = {.x = 0.0f,.y = 0.0f,.z = 0.9727051854133606f}
                  },
  .misalignment = {
                   .x = {.x = 1.0f,
                         .y = 0.0022878649178892f,
                         .z = -0.0111410999670625f},
                   .y = {.x = 0.0f,
                         .y = 1.0000000000000000f,
                         .z = 0.0018858800176531f},
                   .z = {.x = 0.0f,
                         .y = 0.0000000000000000f,
                         .z = 1.0000000000000000f}
                   }
};

static struct mosscalib_adjust_param_s param_gyr = {
  .bias.f = {.x = -0.12497810530476f,
             .y = -1.21626199688762f,
             .z = 1.12496595829725f},
  .scalefactor = {
                  .x = {.x = 0.9784178137779236f,.y = 0.0f,.z = 0.0f},
                  .y = {.x = 0.0f,.y = 1.0078259706497192f,.z = 0.0f},
                  .z = {.x = 0.0f,.y = 0.0f,.z = 0.9969930052757263f}
                  },
  .misalignment = {
                   .x = {.x = 1.0f,
                         .y = 0.0048000421375036f,
                         .z = -0.0103387897834182f},
                   .y = {.x = -0.0065536201000214f,
                         .y = 1.0f,
                         .z = 0.0002426705032121f},
                   .z = {.x = 0.0087586073204875f,
                         .y = -0.0016777249984443f,
                         .z = 1.0f}
                   }
};

static int eiscalibration_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  int8_t ret = 0;
  mossfw_data_v3f_t *inbuf;
  mossfw_data_v3f_t *outbuf;
  mossfw_onedata_t data;
  mossfw_onedata_t outdata;
  struct mosscalib_adjust_param_s *param = NULL;
  float coef = 0.0f;

  mossfw_get_delivereddata_single(in->input, &data);
  inbuf  = (mossfw_data_v3f_t *)malloc(sizeof(mossfw_data_v3f_t));
  outbuf = (mossfw_data_v3f_t *)malloc(sizeof(mossfw_data_v3f_t));

  mossfw_output_t *output;
  if (arg == EISCALIBRATION_ACC)
    {
      param = &param_acc;
      coef = ((16.0f * 9.8f) / 32768.0f) / 1000.0f;
      output = getattitudepipeline()->eiscalib_acc.out[0];
    } 
  else  // arg == EISCALIBRATION_GYR
    {
      param = &param_gyr;
      coef = 2000.0f / 32800.0f;
      output = getattitudepipeline()->eiscalib_gyr.out[0];
    }

  inbuf->x = data.v3s.x * coef;
  inbuf->y = data.v3s.y * coef;
  inbuf->z = data.v3s.z * coef;
  mosscalib_adjustv3f(outbuf, inbuf, 1, 0.0f, param);
#ifdef DEBUG_OUTPUT
  if (arg == EISCALIBRATION_ACC)
    {
      printf("ImuCalibration ACC %0.16f %0.16f %0.16f\n", outbuf->x, outbuf->y, outbuf->z);
    }
  else
    {
      printf("ImuCalibration GYR %0.16f %0.16f %0.16f\n", outbuf->x, outbuf->y, outbuf->z);
    }
#endif
  outdata.xyzf.x = outbuf->x;
  outdata.xyzf.y = outbuf->y;
  outdata.xyzf.z = outbuf->z;
  ret = mossfw_deliver_data(output, &outdata);
  assert(ret == 0);

  free(inbuf);
  free(outbuf);
  return ret;
}

void attitude_eiscalibration_create(struct component_s *com, enum eiscalibration_e type)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      if (allocator == NULL)
        {
          allocator = mossfw_fixedmem_create(ATTITUDESOURCE_MAXDATA * sizeof(mossfw_data_v3f_t), ATTITUDESOURCE_MAXBLOCK);
          assert(allocator);
        }
      if (type == EISCALIBRATION_ACC)
        {
          com->in[0]  = mossfw_input_create(EISCALIBRATION_INPUTTYPE_ACC, 2);
          com->out[0] = mossfw_output_create(EISCALIBRATION_OUTPUTTYPE_ACC);
        }
      else /* EISCALIBRATION_GYR */
        {
          com->in[0]  = mossfw_input_create(EISCALIBRATION_INPUTTYPE_GYR, 2);
          com->out[0] = mossfw_output_create(EISCALIBRATION_OUTPUTTYPE_GYR);
        }
      com->op[0]  = mossfw_callback_op_create(eiscalibration_operate_cb, (unsigned long)type, false);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_v3s_t), com->op[0]);
    }
}

void attitude_eiscalibration_delete(struct component_s *com)
{
    component_delete(com);
    if (allocator != NULL)
      {
        mossfw_fixedmem_delete(allocator);
        allocator = NULL;
      }
}
