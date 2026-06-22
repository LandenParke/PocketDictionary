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
#include <math.h>
#include <assert.h>
#include <string.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossdsp.h"
#include "mossfw/mossfw_component.h"
#include "component.h"
#include "attitude_error_source.h"
#include "attitude_error_complementaryfilter.h"
#include "attitude_error.h"
//#define DEBUG_OUTPUT
#define PI 3.14159265358979323846f
#define COMPLEMENTARYFILTER_INPUTTYPE_GYR (MOSSFW_DATA_TYPE_FLOAT + \
                                          MOSSFW_DATA_TYPEGRP_V3 + \
                                          MOSSFW_DATA_TYPENAME_GYRO + \
                                          MOSSFW_DATA_TYPEARRAY_SINGLE)
#define COMPLEMENTARYFILTER_INPUTTYPE_Q (MOSSFW_DATA_TYPE_FLOAT + \
                                         MOSSFW_DATA_TYPEGRP_Q + \
                                          MOSSFW_DATA_TYPEARRAY_SINGLE)
#define COMPLEMENTARYFILTER_OUTPUTTYPE COMPLEMENTARYFILTER_INPUTTYPE_Q

static mossfw_allocator_t *allocator = NULL;

static unsigned int gyrcount = 0;
static mossfw_data_qf_t accpose = {
  .w = 1.0f,.x = 0.0f,.y = 0.0f,.z = 0.0f
};

static struct mossdsp_integrategyr_param_s param = {
  .lastout.f = {.w = 1.0f,.x = 0.0f,.y = 0.0f,.z = 0.0f},
  .dt = 3125,
  .res = {.tv_sec = 0,.tv_nsec = 100000},
  .scale_factor = 0.0f
};

static mossfw_data_qf_t normalize(mossfw_data_qf_t in)
{
  const float eps = 0.00100000005f;
  float norm;
  norm = sqrtf(in.w * in.w + in.x * in.x + in.y * in.y + in.z * in.z);
  if (eps < norm)
    {
      in.w = in.w * (1.0f / norm);
      in.x = in.x * (1.0f / norm);
      in.y = in.y * (1.0f / norm);
      in.z = in.z * (1.0f / norm);
    }
  return in;
}

static mossfw_data_qf_t calculateYawRotation(mossfw_data_qf_t pose)
{
  mossfw_data_qf_t ret = {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
  float theta;
  float norm;

  theta = acosf(pose.w);
  norm = sqrtf(pose.x * pose.x + pose.y * pose.y + pose.z * pose.z);
  if (norm > 0.00001f)
    {
      ret.w = cosf(theta);
      ret.x = 0.0f;
      ret.y = sinf(theta) * (pose.y / norm);
      ret.z = 0.0f;
      ret = normalize(ret);
    }
    return ret;
}

static mossfw_data_qf_t complementaryfilter(mossfw_data_qf_t gyrpose, mossfw_data_qf_t accpose)
{
  mossfw_data_qf_t ret = {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
  mossfw_data_qf_t yawrot;
  mossfw_data_qf_t pose;
  const float complementary_filter_coef = 0.999000013;
  struct mossdsp_interpolate_param_s param = {.t0 = 0, .t1 = 1000, .t = 1};

  yawrot = calculateYawRotation(gyrpose);
  mossdsp_multiplyqf(&pose, &yawrot, &accpose, 1);
  mossdsp_interpolateqf(&ret, &gyrpose, &pose, &param);
  ret = normalize(ret);
  return ret;
}

void attitude_error_complementaryfilter_set_time_resolution(long nsec)
{
  param.res.tv_sec  = nsec / 1000000000;
  param.res.tv_nsec = nsec % 1000000000;
}

static int attitude_complementaryfilter_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
  int8_t ret = 0;
  int num = 0;
  mossfw_data_qf_t *outdata = NULL;
  mossfw_data_qf_t *outbuf = NULL;
  mossfw_data_v3f_t ingyr;
  void *inlinedata;
  size_t calnum;
  size_t caloffset;
  size_t outsize;
  size_t i;
  mossfw_input_t *input = NULL;
  mossfw_onedata_t data;
  int datasize;
  mossfw_data_qf_t qf;

  if (indataid == COMPLEMENTARYFILTER_ROT)
    {
      datasize = mossfw_get_delivereddata_single(in->input, &data);
      accpose.w = data.qf.w;
      accpose.x = data.qf.x;
      accpose.y = data.qf.y;
      accpose.z = data.qf.z;
      num = datasize / sizeof(mossfw_data_qf_t);
      gyrcount = 0;
#ifdef DEBUG_OUTPUT
      printf("ComplementaryFilter POSEACC num = %d\n", num);
#endif
    }
  else if (indataid == COMPLEMENTARYFILTER_GYR)
    {
      datasize = mossfw_get_delivereddata_single(in->input, &data);
      ingyr.x = data.xyzf.x;
      ingyr.y = data.xyzf.y;
      ingyr.z = data.xyzf.z;
      num = datasize / sizeof(mossfw_data_v3f_t);
      outdata = (mossfw_data_qf_t *)malloc(sizeof(mossfw_data_qf_t));
      outbuf  = (mossfw_data_qf_t *)malloc(sizeof(mossfw_data_qf_t));
#ifdef DEBUG_OUTPUT
      printf("ComplementaryFilter POSEGYR num = %d\n", num);
#endif
      ingyr.x = ingyr.x * (PI / 180.0f);
      ingyr.y = ingyr.y * (PI / 180.0f);
      ingyr.z = ingyr.z * (PI / 180.0f);
      if (gyrcount == 0)
        {
          calnum = num - 1;
          caloffset = 1;
          mossdsp_integrategyrv3f(outbuf, &ingyr, 1, &param);
          outdata->w = outbuf->w;
          outdata->x = outbuf->x;
          outdata->y = outbuf->y;
          outdata->z = outbuf->z;
          qf = complementaryfilter(*outdata, accpose);
          param.lastout.f.w = qf.w;
          param.lastout.f.x = qf.x;
          param.lastout.f.y = qf.y;
          param.lastout.f.z = qf.z;
          *outdata = qf;
          outbuf->w = qf.w;
          outbuf->x = qf.x;
          outbuf->y = qf.y;
          outbuf->z = qf.z;
        }
      else
        {
          calnum = num;
          caloffset = 0;
        }
      mossdsp_integrategyrv3f(outbuf, &ingyr, calnum, &param);
      outdata->w = outbuf->w;
      outdata->x = outbuf->x;
      outdata->y = outbuf->y;
      outdata->z = outbuf->z;
      param.lastout.f = *outbuf;
#ifdef DEBUG_OUTPUT
      printf("IntegralGyr %0.16f %0.16f %0.16f %0.16f\n", outdata->w, outdata->x, outdata->y, outdata->z);
#endif
      gyrcount = 1;

      data.qf.w = outdata->w;
      data.qf.x = outdata->x;
      data.qf.y = outdata->y;
      data.qf.z = outdata->z;
      mossfw_output_t *output;
      if (indataid == COMPLEMENTARYFILTER_GYR)
        {
          output = getattitude_errorpipeline()->complementary_filter_gyr.out[0];
        }
      else
        {
          output = getattitude_errorpipeline()->complementary_filter_rot.out[0];
        }
      ret = mossfw_deliver_data(output, &data);
    }
  assert(ret == 0);
  free(outdata);
  free(outbuf);
  return ret;
}

void attitude_error_complementaryfilter_create(struct component_s *com, enum complementaryfilter_e type)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));

      if (type == COMPLEMENTARYFILTER_GYR)
        {
          com->in[0]  = mossfw_input_create(COMPLEMENTARYFILTER_INPUTTYPE_GYR, 2);
          com->out[0] = mossfw_output_create(COMPLEMENTARYFILTER_OUTPUTTYPE);
          com->op[0]  = mossfw_callback_op_create(attitude_complementaryfilter_operate_cb, (unsigned long)type, false);
          mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_v3f_t), com->op[0]);
        }
      else
        {
          com->in[0]  = mossfw_input_create(COMPLEMENTARYFILTER_INPUTTYPE_Q, 2);
          com->out[0] = mossfw_output_create(COMPLEMENTARYFILTER_OUTPUTTYPE);
          com->op[0]  = mossfw_callback_op_create(attitude_complementaryfilter_operate_cb, (unsigned long)type, false);
          mossfw_set_waitcondition(com->in[0], 1, com->op[0]);
        }

      if (allocator == NULL)
        {
          allocator = mossfw_fixedmem_create(ATTITUDESOURCE_MAXDATA * sizeof(mossfw_data_qf_t), ATTITUDESOURCE_MAXBLOCK);
          assert(allocator);
        }
    }
}

void attitude_error_complementaryfilter_delete(struct component_s *com)
{
    component_delete(com);
    if (allocator != NULL)
      {
        mossfw_fixedmem_delete(allocator);
        allocator = NULL;
      }
}

void attitude_error_complementaryfilter_reset(void)
{
    gyrcount = 0;
    param.lastout.f.w = 1.0f;
    param.lastout.f.x = 0.0f;
    param.lastout.f.y = 0.0f;
    param.lastout.f.z = 0.0f;
    param.dt = 3125;
    param.res.tv_sec = 0;
    param.res.tv_nsec = 100000;
    param.scale_factor = 0.0f;
    accpose.w = 1.0f;
    accpose.x = 0.0f;
    accpose.y = 0.0f;
    accpose.z = 0.0f;
}
