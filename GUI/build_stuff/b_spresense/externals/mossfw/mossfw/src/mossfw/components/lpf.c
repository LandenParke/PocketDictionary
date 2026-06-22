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
#ifdef DEBUG_OUTPUT
#  include <stdio.h>
#endif
#include "mossfw/sensorlib.h"
#include "mossfw/mossdsp.h"
#include "mossfw/mossfw_component.h"
#include "mossfw/components/lpf.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
#define FILTER_COEFFICIENT_SIZE 13

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

static float acc1coefficients[] =
{
  0.0637490004f, 0.0699850023f, 0.0754000023f, 0.0798150003f,
  0.0830819979f, 0.0850870013f, 0.0857639983f, 0.0850870013f,
  0.0830819979f, 0.0798150003f, 0.0754000023f, 0.0699850023f,
  0.0637490004f
};

static float gyr1coefficients[] =
{
  0.000874990015f, 0.0581309982f, -0.000905640016f, -0.0995739996f,
  0.000924279972f, 0.3028f, 0.475510001f, 0.3028f,
  0.000924279972f, -0.0995739996f, -0.000905640016f, 0.0581309982f,
  0.000874990015f
};

static mossfw_data_v3f_t acc1lastdata[] =
{
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f}
};

static mossfw_data_v3f_t gyr1lastdata[] =
{
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f},
  {.x = 0.0f, .y = 0.0f, .z = 0.0f}
};

static struct mossdsp_firfilter_param_s acc1param =
{
  .coefficients.f = acc1coefficients,
  .cnum = 13,
  .lastdata.v3f = acc1lastdata,
  .lnum = 12,
  .delay = 0
};

static struct mossdsp_firfilter_param_s gyr1param =
{
  .coefficients.f = gyr1coefficients,
  .cnum = 13,
  .lastdata.v3f = gyr1lastdata,
  .lnum = 12,
  .delay = 0
};

static int acc1count = 0;
static int gyr1count = 0;

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
 * name: initparam
 ****************************************************************************/

static void initparam(struct mossdsp_firfilter_param_s *param,
  mossfw_data_t *indata, unsigned int num)
{
  size_t len;
  size_t i;

  len = param->lnum - param->cnum / 2;
  len = len < num ? len : num;
  for (i = 0; i < param->lnum - len; i++)
    {
      param->lastdata.v3f[i].x = indata->data.xyzf[0].x;
      param->lastdata.v3f[i].y = indata->data.xyzf[0].y;
      param->lastdata.v3f[i].z = indata->data.xyzf[0].z;
    }

  for (i = 0; i < len; i++)
    {
      param->lastdata.v3f[param->lnum - len + i].x = indata->data.xyzf[i].x;
      param->lastdata.v3f[param->lnum - len + i].y = indata->data.xyzf[i].y;
      param->lastdata.v3f[param->lnum - len + i].z = indata->data.xyzf[i].z;
    }
}

/****************************************************************************
 * name: updateparam
 ****************************************************************************/

static void updateparam(struct mossdsp_firfilter_param_s *param,
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
/****************************************************************************
 * name: print
 ****************************************************************************/

static void print(unsigned long indataid, mossfw_data_t *outdata)
{
  size_t i;

  if (outdata)
    {
      if (indataid == ID_DATA_LPF_ACC1)
        {
          printf("LPF ACC\n");
        }
      else if (indataid == ID_DATA_LPF_GYR1)
        {
          printf("LPF GYR\n");
        }

      for (i = 0;
           outdata != NULL &&
           i < outdata->data_bytes / sizeof(mossfw_data_v3f_t); i++)
        {
          printf("LPF %0.16f %0.16f %0.16f\n", outdata->data.xyzf[i].x,
                 outdata->data.xyzf[i].y, outdata->data.xyzf[i].z);
        }
    }
}
#endif

/****************************************************************************
 * name: lpf_reset
 ****************************************************************************/

void lpf_reset(void)
{
  acc1count = 0;
  gyr1count = 0;
}

/****************************************************************************
 * name: lpf_main
 ****************************************************************************/

int lpf_main(struct mossfw_callback_op_s *in, unsigned long arg)
{
  int err = 0;
  unsigned int num = 0;
  size_t outnum = 0;
  struct mossdsp_firfilter_param_s *param;
  int *count = NULL;
  int used;
  mossfw_output_t *output = NULL;
  mossfw_data_t *outdata = NULL;

  struct lpf_s *com = getcomponent();
  int size = mossfw_get_delivereddata_num(in->input);
  mossfw_data_t *indata =
    mossfw_get_delivereddata_array(in->input, size, &used);

  if (arg == ID_DATA_LPF_ACC1)
    {
      param = &acc1param;
      count = &acc1count;
      output = com->outacc;
    }
  else
    {
      param = &gyr1param;
      count = &gyr1count;
      output = com->outgyr;
    }

  num = (unsigned int)size / sizeof(mossfw_data_v3f_t);
  if (*count == 0)
    {
      initparam(param, indata, num);
    }

  int halfcoeffsize = FILTER_COEFFICIENT_SIZE / 2;
  size_t inoffset = *count < halfcoeffsize ? halfcoeffsize - *count : 0;
  inoffset = inoffset < num ? inoffset : num;
  outnum = num - inoffset;
  if (0 < outnum)
    {
      size_t outdatasize = outnum * sizeof(mossfw_data_v3f_t);
      outdata = mossfw_data_alloc(com->alloc, outdatasize, false);
      err = err || !outdata;
      if (!err)
        {
          mossfw_data_v3f_t *ov3f = (mossfw_data_v3f_t *)outdata->data.xyzf;
          mossdsp_firfilterv3f(&ov3f[0], &ov3f[inoffset], outnum, param);
          outdata->timestamp = indata->timestamp;
          outdata->data_bytes = outnum * sizeof(mossfw_data_v3f_t);
        }
    }

  uint32_t inupdateoffset = num < param->lnum ? 0 : num - param->lnum;
  mossfw_data_v3f_t *iv3f = (mossfw_data_v3f_t *)(indata->data.xyzf);
  updateparam(param, &iv3f[inupdateoffset], num - inupdateoffset);
  unsigned int coeffsize = FILTER_COEFFICIENT_SIZE;
  *count = ((*count + num < coeffsize) ? *count + num : coeffsize);
#ifdef DEBUG_OUTPUT
  print(arg, outdata);
#endif
  err = err || mossfw_deliver_dataarray(output, outdata);
  mossfw_data_free(indata);
  mossfw_data_free(outdata);
  return err;
}

/****************************************************************************
 * name: lpf_create
 ****************************************************************************/

struct lpf_s *lpf_create(mossfw_allocator_t *allocator)
{
  int err = 0;
  struct lpf_s *lpf = malloc(sizeof(struct lpf_s));
  if (lpf)
    {
      uint32_t type =
        MOSSFW_DATA_TYPE_FLOAT | MOSSFW_DATA_TYPEGRP_V3 |
        MOSSFW_DATA_TYPEARRAY_ARRAY;
      int wait_size = sizeof(mossfw_data_v3f_t);
      lpf->inacc =
        mossfw_input_create(type | MOSSFW_DATA_TYPENAME_ACCEL, 1);
      lpf->ingyr =
        mossfw_input_create(type | MOSSFW_DATA_TYPENAME_GYRO, 1);
      lpf->opacc = mossfw_callback_op_create
    (lpf_main, ID_DATA_LPF_ACC1, false);
      lpf->opgyr = mossfw_callback_op_create
    (lpf_main, ID_DATA_LPF_GYR1, false);
      lpf->outacc =
        mossfw_output_create(type | MOSSFW_DATA_TYPENAME_ACCEL);
      lpf->outgyr =
        mossfw_output_create(type | MOSSFW_DATA_TYPENAME_GYRO);
      lpf->alloc = allocator;
      err = err || !lpf->inacc || !lpf->ingyr;
      err = err || !lpf->outacc || !lpf->outgyr;
      err = err || !lpf->opacc || !lpf->opgyr;
      err = err || !allocator;
      err = err || mossfw_set_waitcondition
    (lpf->inacc, wait_size, lpf->opacc);
      err = err || mossfw_set_waitcondition
    (lpf->ingyr, wait_size, lpf->opgyr);
    }

  if (err)
    {
      lpf_delete(lpf);
      lpf = NULL;
    }

  setcomponent(lpf);
  return lpf;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: lpf_delete
 ****************************************************************************/

void lpf_delete(struct lpf_s *lpf)
{
  if (lpf)
    {
      mossfw_output_delete(lpf->outacc);
      mossfw_output_delete(lpf->outgyr);
      mossfw_callback_op_delete(lpf->opacc);
      mossfw_callback_op_delete(lpf->opgyr);
      mossfw_input_delete(lpf->inacc);
      mossfw_input_delete(lpf->ingyr);
    }

  free(lpf);
}
