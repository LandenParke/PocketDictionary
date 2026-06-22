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
#include <math.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_data.h"
#include "mossfw/mossdsp.h"

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: interpolateinteger16
 ****************************************************************************/

static int16_t interpolateinteger16(int16_t in0,
                                    uint32_t dt0,
                                    int16_t in1,
                                    uint32_t dt1)
{
  int16_t ret = 0;
  int64_t val;
  int64_t dt;

  dt = (int64_t)dt0 + (int64_t)dt1;
  if (0 < dt)
    {
      val = (int64_t)dt1 * (int64_t)in0 + (int64_t)dt0 * (int64_t)in1;
      ret = (val + (val < 0 ? -dt : dt) / (int64_t)2) / dt;
    }

  return ret;
}

/****************************************************************************
 * name: interpolatefloat
 ****************************************************************************/

static float interpolatefloat(float in0,
                              uint32_t dt0,
                              float in1,
                              uint32_t dt1)
{
  float ret;
  ret = ((float)dt1 * in0 + (float)dt0 * in1) / ((float)dt0 + (float)dt1);
  return ret;
}

/****************************************************************************
 * name: mossdsp_interpolatei
 ****************************************************************************/

int16_t mossdsp_interpolatei(int16_t in0,
                            int16_t in1,
                            const struct mossdsp_interpolate_param_s *param)
{
  int16_t ret = 0;

  if (param != NULL)
    {
      ret = interpolateinteger16(in0, param->t  - param->t0,
                                 in1, param->t1 - param->t);
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_interpolatef
 ****************************************************************************/

float mossdsp_interpolatef(float in0,
                           float in1,
                           const struct mossdsp_interpolate_param_s *param)
{
  uint32_t dt0;
  uint32_t dt1;
  float ret = 0;

  if (param != NULL)
    {
      dt0 = param->t - param->t0;
      dt1 = param->t1 - param->t;
      ret = interpolatefloat(in0, dt0, in1, dt1);
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_interpolatev3i
 ****************************************************************************/

int mossdsp_interpolatev3i(mossfw_data_v3s_t *out,
                          const mossfw_data_v3s_t *in0,
                          const mossfw_data_v3s_t *in1,
                          const struct mossdsp_interpolate_param_s *param)
{
  int64_t dt = 0;
  uint32_t dt0;
  uint32_t dt1;
  int err;

  if (param != NULL)
    {
      dt0 = param->t  - param->t0;
      dt1 = param->t1 - param->t;
      dt = (int64_t)dt0 + (int64_t)dt1;
    }

  err = (out != NULL && in0 != NULL && in1 != NULL && dt != 0) - 1;
  if (!err)
    {
      out->x = interpolateinteger16(in0->x, dt0, in1->x, dt1);
      out->y = interpolateinteger16(in0->y, dt0, in1->y, dt1);
      out->z = interpolateinteger16(in0->z, dt0, in1->z, dt1);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_interpolatev3f
 ****************************************************************************/

int mossdsp_interpolatev3f(mossfw_data_v3f_t *out,
                          const mossfw_data_v3f_t *in0,
                          const mossfw_data_v3f_t *in1,
                          const struct mossdsp_interpolate_param_s *param)
{
  uint32_t dt0;
  uint32_t dt1;
  int err;

  err = (out != NULL && in0 != NULL && in1 != NULL && param != 0) - 1;
  if (!err)
    {
      dt0 = param->t - param->t0;
      dt1 = param->t1 - param->t;
      out->x = interpolatefloat(in0->x, dt0, in1->x, dt1);
      out->y = interpolatefloat(in0->y, dt0, in1->y, dt1);
      out->z = interpolatefloat(in0->z, dt0, in1->z, dt1);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_interpolatev3ti
 ****************************************************************************/

int mossdsp_interpolatev3ti(mossfw_data_v3ts_t *out,
                            const mossfw_data_v3ts_t *in0,
                            const mossfw_data_v3ts_t *in1,
                            const struct mossdsp_interpolate_param_s *param)
{
  uint16_t dt0 = 0;
  uint16_t dt1 = 0;
  int err;

  if (in0 != NULL && in1 != NULL && param != NULL)
    {
      dt0 = (uint16_t)param->t - in0->t;
      dt1 = in1->t - (uint16_t)param->t;
    }

  err = (out != 0 && ((uint32_t)0 < (uint32_t)dt0 + (uint32_t)dt1)) - 1;
  if (!err)
    {
      out->t = param->t;
      out->x = interpolateinteger16(in0->x, dt0, in1->x, dt1);
      out->y = interpolateinteger16(in0->y, dt0, in1->y, dt1);
      out->z = interpolateinteger16(in0->z, dt0, in1->z, dt1);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_interpolatev3tf
 ****************************************************************************/

int mossdsp_interpolatev3tf(mossfw_data_v3tf_t *out,
                            const mossfw_data_v3tf_t *in0,
                            const mossfw_data_v3tf_t *in1,
                            const struct mossdsp_interpolate_param_s *param)
{
  uint32_t dt0;
  uint32_t dt1;
  int err;

  err = (out != NULL && in0 != NULL && in1 != NULL && param != 0) - 1;
  if (!err)
    {
      dt0 = param->t - in0->t;
      dt1 = in1->t - param->t;
      out->x = interpolatefloat(in0->x, dt0, in1->x, dt1);
      out->y = interpolatefloat(in0->y, dt0, in1->y, dt1);
      out->z = interpolatefloat(in0->z, dt0, in1->z, dt1);
      out->t = param->t;
    }

  return err;
}

/****************************************************************************
 * name: quaternion_fp
 ****************************************************************************/

static mossfw_data_qf_t quaternion_fp(const mossfw_data_qf_t in,
                                      float coefficient)
{
  mossfw_data_qf_t ret;
  ret.w = in.w * coefficient;
  ret.x = in.x * coefficient;
  ret.y = in.y * coefficient;
  ret.z = in.z * coefficient;
  return ret;
}

/****************************************************************************
 * name: quaternion_add
 ****************************************************************************/

static mossfw_data_qf_t quaternion_add(mossfw_data_qf_t in0,
                                       mossfw_data_qf_t in1)
{
  mossfw_data_qf_t ret;
  ret.w = in0.w + in1.w;
  ret.x = in0.x + in1.x;
  ret.y = in0.y + in1.y;
  ret.z = in0.z + in1.z;
  return ret;
}

/****************************************************************************
 * name: interpolateq
 ****************************************************************************/

static void interpolateq(mossfw_data_qf_t *out,
                          const mossfw_data_qf_t *in0,
                          const mossfw_data_qf_t *in1,
                          const struct mossdsp_interpolate_param_s *param)
{
  float ip; /* inner product <in0, in1> */
  uint32_t dt0;
  uint32_t dt1;
  float c0;
  float c1;
  float theta;
  mossfw_data_qf_t q0;
  mossfw_data_qf_t q1;
  mossfw_data_qf_t val;

  dt0 = param->t - param->t0;
  dt1 = param->t1 - param->t;
  c0 = (float)dt0 / ((float)dt0 + (float)dt1);
  c1 = (float)dt1 / ((float)dt0 + (float)dt1);
  ip = in0->w * in1->w + in0->x * in1->x + in0->y * in1->y + in0->z * in1->z;
  if (fabsf(ip) > 0.95)
    {
      q0 = quaternion_fp(*in0, c1);
      q1 = quaternion_fp(*in1, c0 * ip / fabsf(ip));
      *out = quaternion_add(q0, q1);
    }
  else
    {
      theta = acos(fabsf(ip));
      q0 = quaternion_fp(*in0, sinf(c1 * theta));
      q1 = quaternion_fp(*in1, sinf(c0 * theta) * ip / fabsf(ip));
      val = quaternion_add(q0, q1);
      *out = quaternion_fp(val, 1.0f / sinf(theta));
    }
}

/****************************************************************************
 * name: qtypef
 ****************************************************************************/

static mossfw_data_qf_t qtypef(mossfw_data_qtf_t in)
{
  mossfw_data_qf_t ret;
  ret.w = in.w;
  ret.x = in.x;
  ret.y = in.y;
  ret.z = in.z;
  return ret;
}

/****************************************************************************
 * name: qtypetf
 ****************************************************************************/

static mossfw_data_qtf_t qtypetf(mossfw_data_qf_t in, uint32_t time)
{
  mossfw_data_qtf_t ret;
  ret.w = in.w;
  ret.x = in.x;
  ret.y = in.y;
  ret.z = in.z;
  ret.t = time;
  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossdsp_interpolateqf
 ****************************************************************************/

int mossdsp_interpolateqf(mossfw_data_qf_t *out,
                          const mossfw_data_qf_t *in0,
                          const mossfw_data_qf_t *in1,
                          const struct mossdsp_interpolate_param_s *param)
{
  int err;
  err = (out != NULL && in0 != NULL && in1 != NULL && param != 0) - 1;
  if (!err)
    {
      interpolateq(out, in0, in1, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_interpolateqtf
 ****************************************************************************/

int mossdsp_interpolateqtf(mossfw_data_qtf_t *out,
                          const mossfw_data_qtf_t *in0,
                          const mossfw_data_qtf_t *in1,
                          const struct mossdsp_interpolate_param_s *param)
{
  mossfw_data_qf_t i0;
  mossfw_data_qf_t i1;
  mossfw_data_qf_t val;
  struct mossdsp_interpolate_param_s pt;
  int err;
  err = (out != NULL && in0 != NULL && in1 != NULL && param != 0) - 1;
  if (!err)
    {
      i0 = qtypef(*in0);
      i1 = qtypef(*in1);
      pt.t = param->t;
      pt.t0 = in0->t;
      pt.t1 = in1->t;
      interpolateq(&val, &i0, &i1, &pt);
      *out = qtypetf(val, param->t);
    }

  return err;
}
