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

#include <stdint.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_data.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef NULL
#define NULL    (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#ifndef FALSE
#define FALSE    (0)
#endif

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

struct transformaxis_v3i64_s
  {
    int64_t x;
    int64_t y;
    int64_t z;
  };

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: overflowv3i
 ****************************************************************************/

static int overflowv3i(struct transformaxis_v3i64_s in)
{
  return in.x < INT16_MIN || INT16_MAX < in.x ||
         in.y < INT16_MIN || INT16_MAX < in.y ||
         in.z < INT16_MIN || INT16_MAX < in.z;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3i_element
 ****************************************************************************/

static int mossdsp_transformaxismv3i_element(mossfw_data_v3s_t *out,
                                            const mossfw_data_v3s_t *in,
                                            const struct sqmatrix3i_s *param)
{
  struct transformaxis_v3i64_s sum =
    {
      .x = 0, .y = 0, .z = 0
    };

  int ret = 0;

  sum.x = (int64_t)param->x.x*(int64_t)in->x +
          (int64_t)param->x.y*(int64_t)in->y +
          (int64_t)param->x.z*(int64_t)in->z;
  sum.y = (int64_t)param->y.x*(int64_t)in->x +
          (int64_t)param->y.y*(int64_t)in->y +
          (int64_t)param->y.z*(int64_t)in->z;
  sum.z = (int64_t)param->z.x*(int64_t)in->x +
          (int64_t)param->z.y*(int64_t)in->y +
          (int64_t)param->z.z*(int64_t)in->z;

  if (overflowv3i(sum))
    {
      return ret = -1;
    }
  else
    {
      out->x = (int16_t) sum.x;
      out->y = (int16_t) sum.y;
      out->z = (int16_t) sum.z;
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3f_element
 ****************************************************************************/

static void mossdsp_transformaxismv3f_element(mossfw_data_v3f_t *out,
                                            const mossfw_data_v3f_t *in,
                                            const struct sqmatrix3f_s *param)
{
  out->x = param->x.x*in->x + param->x.y*in->y + param->x.z*in->z;
  out->y = param->y.x*in->x + param->y.y*in->y + param->y.z*in->z;
  out->z = param->z.x*in->x + param->z.y*in->y + param->z.z*in->z;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3ia_element
 ****************************************************************************/

static int mossdsp_transformaxismv3ia_element(struct vector3ia_s *out,
                                            const struct vector3ia_s *in,
                                            const struct sqmatrix3i_s *param)
{
  struct transformaxis_v3i64_s sum =
    {
      .x = 0, .y = 0, .z = 0
    };

  int ret = 0;

  sum.x = (int64_t)param->x.x*(int64_t)(*in->x) +
          (int64_t)param->x.y*(int64_t)(*in->y) +
          (int64_t)param->x.z*(int64_t)(*in->z);
  sum.y = (int64_t)param->y.x*(int64_t)(*in->x) +
          (int64_t)param->y.y*(int64_t)(*in->y) +
          (int64_t)param->y.z*(int64_t)(*in->z);
  sum.z = (int64_t)param->z.x*(int64_t)(*in->x) +
          (int64_t)param->z.y*(int64_t)(*in->y) +
          (int64_t)param->z.z*(int64_t)(*in->z);

  if (overflowv3i(sum))
    {
      return ret = -1;
    }
  else
    {
      *out->x = (int16_t) sum.x;
      *out->y = (int16_t) sum.y;
      *out->z = (int16_t) sum.z;
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3fa_element
 ****************************************************************************/

static void mossdsp_transformaxismv3fa_element(struct vector3fa_s *out,
                                            const struct vector3fa_s *in,
                                            const struct sqmatrix3f_s *param)
{
  *out->x = param->x.x*(*in->x) + param->x.y*(*in->y) + param->x.z*(*in->z);
  *out->y = param->y.x*(*in->x) + param->y.y*(*in->y) + param->y.z*(*in->z);
  *out->z = param->z.x*(*in->x) + param->z.y*(*in->y) + param->z.z*(*in->z);
}

/****************************************************************************
 * name: mossdsp_transformaxismv3ti_element
 ****************************************************************************/

static int mossdsp_transformaxismv3ti_element(mossfw_data_v3ts_t *out,
                                            const mossfw_data_v3ts_t *in,
                                            const struct sqmatrix3i_s *param)
{
  struct transformaxis_v3i64_s sum =
    {
      .x = 0, .y = 0, .z = 0
    };

  int ret = 0;

  sum.x = (int64_t)param->x.x*(int64_t)in->x +
          (int64_t)param->x.y*(int64_t)in->y +
          (int64_t)param->x.z*(int64_t)in->z;
  sum.y = (int64_t)param->y.x*(int64_t)in->x +
          (int64_t)param->y.y*(int64_t)in->y +
          (int64_t)param->y.z*(int64_t)in->z;
  sum.z = (int64_t)param->z.x*(int64_t)in->x +
          (int64_t)param->z.y*(int64_t)in->y +
          (int64_t)param->z.z*(int64_t)in->z;

  if (overflowv3i(sum))
    {
      return ret = -1;
    }
  else
    {
      out->x = (int16_t) sum.x;
      out->y = (int16_t) sum.y;
      out->z = (int16_t) sum.z;
      out->t = in->t;
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3tf_element
 ****************************************************************************/

static void mossdsp_transformaxismv3tf_element(mossfw_data_v3tf_t *out,
                                            const mossfw_data_v3tf_t *in,
                                            const struct sqmatrix3f_s *param)
{
  out->x = param->x.x*in->x + param->x.y*in->y + param->x.z*in->z;
  out->y = param->y.x*in->x + param->y.y*in->y + param->y.z*in->z;
  out->z = param->z.x*in->x + param->z.y*in->y + param->z.z*in->z;
  out->t = in->t;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3tia_element
 ****************************************************************************/

static int mossdsp_transformaxismv3tia_element(struct vector3tia_s *out,
                                            const struct vector3tia_s *in,
                                            const struct sqmatrix3i_s *param)
{
  struct transformaxis_v3i64_s sum =
    {
      .x = 0, .y = 0, .z = 0
    };

  int ret = 0;

  sum.x = param->x.x*(*in->x) + param->x.y*(*in->y) + param->x.z*(*in->z);
  sum.y = param->y.x*(*in->x) + param->y.y*(*in->y) + param->y.z*(*in->z);
  sum.z = param->z.x*(*in->x) + param->z.y*(*in->y) + param->z.z*(*in->z);
  if (overflowv3i(sum))
    {
      return ret = -1;
    }
  else
    {
      *out->x = (int16_t) sum.x;
      *out->y = (int16_t) sum.y;
      *out->z = (int16_t) sum.z;
      *out->t = *in->t;
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3tfa_element
 ****************************************************************************/

static void mossdsp_transformaxismv3tfa_element(struct vector3tfa_s *out,
                                            const struct vector3tfa_s *in,
                                            const struct sqmatrix3f_s *param)
{
  *out->x = param->x.x*(*in->x) + param->x.y*(*in->y) + param->x.z*(*in->z);
  *out->y = param->y.x*(*in->x) + param->y.y*(*in->y) + param->y.z*(*in->z);
  *out->z = param->z.x*(*in->x) + param->z.y*(*in->y) + param->z.z*(*in->z);
  *out->t = *in->t;
}

/****************************************************************************
 * name: mossdsp_transformaxisqv3f_element
 ****************************************************************************/

static void mossdsp_transformaxisqv3f_element(mossfw_data_v3f_t *out,
                                              const mossfw_data_v3f_t *in,
                                              const mossfw_data_qf_t *param)
{
  mossfw_data_qf_t x_data;
  mossfw_data_qf_t q1;
  mossfw_data_qf_t ans_qx;

  x_data.w = 0;
  x_data.x = in->x;
  x_data.y = in->y;
  x_data.z = in->z;

  q1.w =  param->w;
  q1.x = -param->x;
  q1.y = -param->y;
  q1.z = -param->z;

  ans_qx.w = param->w *  x_data.w -
             param->x *  x_data.x -
             param->y *  x_data.y -
             param->z *  x_data.z;

  ans_qx.x = param->x *  x_data.w +
             param->w *  x_data.x +
             param->y *  x_data.z -
             param->z *  x_data.y;

  ans_qx.y = param->w *  x_data.y +
             param->y *  x_data.w +
             param->z *  x_data.x -
             param->x *  x_data.z;

  ans_qx.z = param->w *  x_data.z +
             param->z *  x_data.w +
             param->x *  x_data.y -
             param->y *  x_data.x;

  out->x = ans_qx.x * q1.w +
           ans_qx.w * q1.x +
           ans_qx.y * q1.z -
           ans_qx.z * q1.y;

  out->y = ans_qx.w * q1.y +
           ans_qx.y * q1.w +
           ans_qx.z * q1.x -
           ans_qx.x * q1.z;

  out->z = ans_qx.w * q1.z +
           ans_qx.z * q1.w +
           ans_qx.x * q1.y -
           ans_qx.y * q1.x;
}

/****************************************************************************
 * name: mossdsp_transformaxisqv3fa_element
 ****************************************************************************/

static void mossdsp_transformaxisqv3fa_element(struct vector3fa_s *out,
                                              const struct vector3fa_s *in,
                                              const mossfw_data_qf_t *param)
{
  mossfw_data_qf_t x_data;
  mossfw_data_qf_t q1;
  mossfw_data_qf_t ans_qx;

  x_data.w = 0;
  x_data.x = *in->x;
  x_data.y = *in->y;
  x_data.z = *in->z;

  q1.w =  param->w;
  q1.x = -param->x;
  q1.y = -param->y;
  q1.z = -param->z;

  ans_qx.w = param->w * x_data.w -
             param->x * x_data.x -
             param->y * x_data.y -
             param->z * x_data.z;

  ans_qx.x = param->x * x_data.w +
             param->w * x_data.x +
             param->y * x_data.z -
             param->z * x_data.y;

  ans_qx.y = param->w * x_data.y +
             param->y * x_data.w +
             param->z * x_data.x -
             param->x * x_data.z;

  ans_qx.z = param->w * x_data.z +
             param->z * x_data.w +
             param->x * x_data.y -
             param->y * x_data.x;

  *out->x = ans_qx.x * q1.w +
            ans_qx.w * q1.x +
            ans_qx.y * q1.z -
            ans_qx.z * q1.y;

  *out->y = ans_qx.w * q1.y +
            ans_qx.y * q1.w +
            ans_qx.z * q1.x -
            ans_qx.x * q1.z;

  *out->z = ans_qx.w * q1.z +
            ans_qx.z * q1.w +
            ans_qx.x * q1.y -
            ans_qx.y * q1.x;
}

/****************************************************************************
 * name: mossdsp_transformaxisqv3tf_element
 ****************************************************************************/

static void mossdsp_transformaxisqv3tf_element(mossfw_data_v3tf_t *out,
                                              const mossfw_data_v3tf_t *in,
                                              const mossfw_data_qf_t *param)
{
  mossfw_data_qf_t x_data;
  mossfw_data_qf_t q1;
  mossfw_data_qf_t ans_qx;

  x_data.w = 0;
  x_data.x = in->x;
  x_data.y = in->y;
  x_data.z = in->z;

  q1.w =  param->w;
  q1.x = -param->x;
  q1.y = -param->y;
  q1.z = -param->z;

  ans_qx.w = param->w * x_data.w -
             param->x * x_data.x -
             param->y * x_data.y -
             param->z * x_data.z;

  ans_qx.x = param->x * x_data.w +
             param->w * x_data.x +
             param->y * x_data.z -
             param->z * x_data.y;

  ans_qx.y = param->w * x_data.y +
             param->y * x_data.w +
             param->z * x_data.x -
             param->x * x_data.z;

  ans_qx.z = param->w * x_data.z +
             param->z * x_data.w +
             param->x * x_data.y -
             param->y * x_data.x;

  out->x = ans_qx.x * q1.w +
           ans_qx.w * q1.x +
           ans_qx.y * q1.z -
           ans_qx.z * q1.y;
  out->y = ans_qx.w * q1.y +
           ans_qx.y * q1.w +
           ans_qx.z * q1.x -
           ans_qx.x * q1.z;
  out->z = ans_qx.w * q1.z +
           ans_qx.z * q1.w +
           ans_qx.x * q1.y -
           ans_qx.y * q1.x;
  out->t = in->t;
}

/****************************************************************************
 * name: mossdsp_transformaxisqv3tfa_element
 ****************************************************************************/

static void mossdsp_transformaxisqv3tfa_element(struct vector3tfa_s *out,
                                              const struct vector3tfa_s *in,
                                              const mossfw_data_qf_t *param)
{
  mossfw_data_qf_t x_data;
  mossfw_data_qf_t q1;
  mossfw_data_qf_t ans_qx;

  x_data.w = 0;
  x_data.x = *in->x;
  x_data.y = *in->y;
  x_data.z = *in->z;

  q1.w =  param->w;
  q1.x = -param->x;
  q1.y = -param->y;
  q1.z = -param->z;

  ans_qx.w = param->w * x_data.w -
             param->x * x_data.x -
             param->y * x_data.y -
             param->z * x_data.z;

  ans_qx.x = param->x * x_data.w +
             param->w * x_data.x +
             param->y * x_data.z -
             param->z * x_data.y;

  ans_qx.y = param->w * x_data.y +
             param->y * x_data.w +
             param->z * x_data.x -
             param->x * x_data.z;

  ans_qx.z = param->w * x_data.z +
             param->z * x_data.w +
             param->x * x_data.y -
             param->y * x_data.x;

  *out->x = ans_qx.x * q1.w +
            ans_qx.w * q1.x +
            ans_qx.y * q1.z -
            ans_qx.z * q1.y;
  *out->y = ans_qx.w * q1.y +
            ans_qx.y * q1.w +
            ans_qx.z * q1.x -
            ans_qx.x * q1.z;
  *out->z = ans_qx.w * q1.z +
            ans_qx.z * q1.w +
            ans_qx.x * q1.y -
            ans_qx.y * q1.x;
  *out->t = *in->t;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossdsp_transformaxismv3i
 ****************************************************************************/

int mossdsp_transformaxismv3i(mossfw_data_v3s_t *out,
                              const mossfw_data_v3s_t *in,
                              unsigned int num,
                              const struct sqmatrix3i_s *param)
{
  int ret = 0;
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      ret = mossdsp_transformaxismv3i_element(&out[i], &in[i], param);
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3f
 ****************************************************************************/

int mossdsp_transformaxismv3f(mossfw_data_v3f_t *out,
                              const mossfw_data_v3f_t *in,
                              unsigned int num,
                              const struct sqmatrix3f_s *param)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      mossdsp_transformaxismv3f_element(&out[i], &in[i], param);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3ia
 ****************************************************************************/

int mossdsp_transformaxismv3ia(struct vector3ia_s *out,
                              const struct vector3ia_s *in,
                              unsigned int num,
                              const struct sqmatrix3i_s *param)
{
  int ret = 0;
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      ret = mossdsp_transformaxismv3ia_element(&out[i], &in[i], param);
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3fa
 ****************************************************************************/

int mossdsp_transformaxismv3fa(struct vector3fa_s *out,
                              const struct vector3fa_s *in,
                              unsigned int num,
                              const struct sqmatrix3f_s *param)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      mossdsp_transformaxismv3fa_element(&out[i], &in[i], param);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3ti
 ****************************************************************************/

int mossdsp_transformaxismv3ti(mossfw_data_v3ts_t *out,
                              const mossfw_data_v3ts_t *in,
                              unsigned int num,
                              const struct sqmatrix3i_s *param)
{
  int ret = 0;
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      ret = mossdsp_transformaxismv3ti_element(&out[i], &in[i], param);
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3tf
 ****************************************************************************/

int mossdsp_transformaxismv3tf(mossfw_data_v3tf_t *out,
                              const mossfw_data_v3tf_t *in,
                              unsigned int num,
                              const struct sqmatrix3f_s *param)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      mossdsp_transformaxismv3tf_element(&out[i], &in[i], param);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3tia
 ****************************************************************************/

int mossdsp_transformaxismv3tia(struct vector3tia_s *out,
                                const struct vector3tia_s *in,
                                unsigned int num,
                                const struct sqmatrix3i_s *param)
{
  int ret = 0;
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      ret = mossdsp_transformaxismv3tia_element(&out[i], &in[i], param);
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_transformaxismv3tfa
 ****************************************************************************/

int mossdsp_transformaxismv3tfa(struct vector3tfa_s *out,
                                const struct vector3tfa_s *in,
                                unsigned int num,
                                const struct sqmatrix3f_s *param)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      mossdsp_transformaxismv3tfa_element(&out[i], &in[i], param);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformaxisqv3f
 ****************************************************************************/

int mossdsp_transformaxisqv3f(mossfw_data_v3f_t *out,
                              const mossfw_data_v3f_t *in,
                              unsigned int num,
                              const mossfw_data_qf_t *param)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      mossdsp_transformaxisqv3f_element(&out[i], &in[i], param);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformaxisqv3fa
 ****************************************************************************/

int mossdsp_transformaxisqv3fa(struct vector3fa_s *out,
                                const struct vector3fa_s *in,
                                unsigned int num,
                                const mossfw_data_qf_t *param)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      mossdsp_transformaxisqv3fa_element(&out[i], &in[i], param);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformaxisqv3tf
 ****************************************************************************/

int mossdsp_transformaxisqv3tf(mossfw_data_v3tf_t *out,
                                const mossfw_data_v3tf_t *in,
                                unsigned int num,
                                const mossfw_data_qf_t *param)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      mossdsp_transformaxisqv3tf_element(&out[i], &in[i], param);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformaxisqv3tfa
 ****************************************************************************/

int mossdsp_transformaxisqv3tfa(struct vector3tfa_s *out,
                                const struct vector3tfa_s *in,
                                unsigned int num,
                                const mossfw_data_qf_t *param)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0 || param == NULL)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      mossdsp_transformaxisqv3tfa_element(&out[i], &in[i], param);
    }

  return 0;
}
