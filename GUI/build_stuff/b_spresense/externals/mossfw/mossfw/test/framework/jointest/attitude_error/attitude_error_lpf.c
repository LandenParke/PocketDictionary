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
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossdsp.h"
#include "mossfw/mossfw_component.h"
#include "component.h"
#include "attitude_error_lpf.h"
#include "attitude_error.h"
//#define DEBUG_OUTPUT
#define FILTER_COEFFICIENT_SIZE 13

#define LPF_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPENAME_ACCEL + \
                           MOSSFW_DATA_TYPEARRAY_SINGLE)
#define LPF_INPUTTYPE_GYR (MOSSFW_DATA_TYPE_FLOAT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPENAME_GYRO + \
                           MOSSFW_DATA_TYPEARRAY_SINGLE)
#define LPF_OUTPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                            MOSSFW_DATA_TYPEGRP_V3 + \
                            MOSSFW_DATA_TYPENAME_ACCEL + \
                            MOSSFW_DATA_TYPEARRAY_SINGLE)
#define LPF_OUTPUTTYPE_GYR (MOSSFW_DATA_TYPE_FLOAT + \
                            MOSSFW_DATA_TYPEGRP_V3 + \
                            MOSSFW_DATA_TYPENAME_GYRO + \
                            MOSSFW_DATA_TYPEARRAY_SINGLE)

static float acccoefficients[] = {
  0.0637490004f, 0.0699850023f, 0.0754000023f, 0.0798150003f,
  0.0830819979f, 0.0850870013f, 0.0857639983f, 0.0850870013f,
  0.0830819979f, 0.0798150003f, 0.0754000023f, 0.0699850023f,
  0.0637490004f
};

static float gyrcoefficients[] = {
  0.000874990015f, 0.0581309982f, -0.000905640016f, -0.0995739996f,
  0.000924279972f, 0.3028f, 0.475510001f, 0.3028f,
  0.000924279972f, -0.0995739996f, -0.000905640016f, 0.0581309982f,
  0.000874990015f
};

static mossfw_data_v3f_t acclastdata[] = {
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f}
};

static mossfw_data_v3f_t gyrlastdata[] = {
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f},
  {.x = 0.0f,.y = 0.0f,.z = 0.0f}
};

static struct mossdsp_firfilter_param_s accparam = {
  .coefficients.f = acccoefficients,
  .cnum = 13,
  .lastdata.v3f = acclastdata,
  .lnum = 12,
  .delay = 0
};
static struct mossdsp_firfilter_param_s gyrparam = {
  .coefficients.f = gyrcoefficients,
  .cnum = 13,
  .lastdata.v3f = gyrlastdata,
  .lnum = 12,
  .delay = 0
};

static int acccount = 0;
static int gyrcount = 0;

static mossfw_allocator_t *allocator = NULL;

static void attitude_initparam(struct mossdsp_firfilter_param_s *param,
                      mossfw_data_v3f_t *indata, int num)
{
  size_t len;
  size_t i;

  len = param->lnum - param->cnum / 2;
  len = len < num ? len : num;
  for (i = 0; i < param->lnum - len; i++)
    {
      param->lastdata.v3f[i] = indata[0];
    }
  for (i = 0; i < len; i++)
    {
      param->lastdata.v3f[param->lnum - len + i] = indata[i];
    }
}

static void attitude_updateparam(struct mossdsp_firfilter_param_s *param,
                        mossfw_data_v3f_t *indata, size_t indatasize)
{
  size_t i;
  size_t lastdatalen;

  lastdatalen = indatasize < param->lnum ? param->lnum - indatasize : 0;
  for (i = 0; i < lastdatalen; i++)
    {
      param->lastdata.v3f[i] =
        param->lastdata.v3f[param->lnum - lastdatalen + i];
    }
  for (i = 0; i < param->lnum - lastdatalen; i++)
    {
      param->lastdata.v3f[lastdatalen + i] = indata[i];
    }
}

#ifdef DEBUG_OUTPUT
static void print(unsigned long arg, void *outbuf, size_t size)
{
  mossfw_data_v3f_t *out = NULL;
  size_t i;

  if (arg == LPF_ACC)
    {
      out = outbuf;
      printf("LPF ACC\n");
    }
  else if (arg == LPF_GYR)
    {
      out = outbuf;
      printf("LPF GYR\n");
    }
  for (i = 0; out != NULL && i < size / sizeof(mossfw_data_v3f_t); i++)
    {
      printf("LPF %0.16f %0.16f %0.16f\n", out[i].x, out[i].y, out[i].z);
    }
}
#endif
static int attitude_lpf_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  int ret = 0;
  int num = 1;
  int data_size;
  mossfw_data_v3f_t *outbuf = NULL;
  mossfw_data_v3f_t *inbuf = NULL;
  size_t outnum = 0;
  size_t inoffset = 0;
  size_t outsize = 0;
  int *count = NULL;
  struct mossdsp_firfilter_param_s *param;
  uint32_t inupdateoffset;
  mossfw_onedata_t data;
  mossfw_onedata_t outdata;

  inbuf  = (mossfw_data_v3f_t *)malloc(sizeof(mossfw_data_v3f_t));

  data_size = mossfw_get_delivereddata_single(in->input, &data);
  inbuf->x = data.xyzf.x;
  inbuf->y = data.xyzf.y;
  inbuf->z = data.xyzf.z;

  mossfw_output_t *output;
  if (arg == LPF_ACC)
    {
      param = &accparam;
      count = &acccount;
      output = getattitude_errorpipeline()->lpf_acc.out[0];
    }
  else // arg == LPF_GYR
    {
      param = &gyrparam;
      count = &gyrcount;
      output = getattitude_errorpipeline()->lpf_gyr.out[0];
    }
  num = data_size / sizeof(mossfw_data_v3f_t);
  if (*count == 0)
    {
      attitude_initparam(param, inbuf, num);
    }
  inoffset = *count < FILTER_COEFFICIENT_SIZE / 2 ? FILTER_COEFFICIENT_SIZE / 2 - *count : 0;
  inoffset = inoffset < num ? inoffset : num;
  outnum = num - inoffset;
  outsize = outnum * sizeof(mossfw_data_v3f_t);
  if (0 < outsize) 
    {
      outbuf = (mossfw_data_v3f_t *)malloc(outsize);
      mossdsp_firfilterv3f(outbuf, inbuf, outnum, param);
    }
  inupdateoffset = num < param->lnum ? 0 : num - param->lnum;
  attitude_updateparam(param, inbuf, num - inupdateoffset);
  *count = ((*count + num < FILTER_COEFFICIENT_SIZE) ? *count + num : FILTER_COEFFICIENT_SIZE);
#ifdef DEBUG_OUTPUT
  print(arg, outbuf, outsize);
#endif

  if (outbuf != NULL)
    {
      outdata.xyzf.x = outbuf->x;
      outdata.xyzf.y = outbuf->y;
      outdata.xyzf.z = outbuf->z;
      ret = mossfw_deliver_data(output, &outdata);
      assert(ret == 0);
    }
  free(outbuf);
  free(inbuf);

  return ret;
}

void attitude_error_lpf_reset(void)
{
  acccount = 0;
  gyrcount = 0;
}

void attitude_error_lpf_create(struct component_s *com, enum lpf_e type)
{
  if (com != NULL)
    {
      com->in_num    = 1;
      com->out_num   = 1;
      com->op_num    = 1;
      com->in        = malloc(com->in_num    * sizeof(void *));
      com->out       = malloc(com->out_num   * sizeof(void *));
      com->op        = malloc(com->op_num    * sizeof(void *));
      if (allocator == NULL)
        {
          allocator = mossfw_fixedmem_create(LPF_MAXDATA * sizeof(mossfw_data_v3f_t), LPF_MAXBLOCK);
        }
      if (type == LPF_ACC)
        {
          com->in[0]  = mossfw_input_create(LPF_INPUTTYPE_ACC, 2);
          com->out[0] = mossfw_output_create(LPF_OUTPUTTYPE_ACC);
        }
      else
        {
          com->in[0]  = mossfw_input_create(LPF_INPUTTYPE_GYR, 2);
          com->out[0] = mossfw_output_create(LPF_OUTPUTTYPE_GYR);
        }
      com->op[0]  = mossfw_callback_op_create(attitude_lpf_operate_cb, (unsigned long)type, false);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_v3f_t), com->op[0]);
    }
}

void attitude_error_lpf_delete(struct component_s *com)
{
  component_delete(com);
  if (allocator != NULL)
    {
      mossfw_fixedmem_delete(allocator);
      allocator = NULL;
    }
}
