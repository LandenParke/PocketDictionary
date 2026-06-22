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
#include <math.h>
#include <stdint.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_data.h"
#include "mossfw/mossdsp.h"
#if defined(MOSSFW_USE_ARMCMSIS_DSP)
#include "dsp/statistics_functions.h"
#endif

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

struct v3i64_s
  {
    int64_t x;
    int64_t y;
    int64_t z;
  };

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: rshift
 ****************************************************************************/

static int64_t rshift(int64_t in, unsigned int scale)
{
  return in >> scale;
}

/****************************************************************************
 * name: divround
 ****************************************************************************/

static int32_t divround(int32_t num, int32_t den)
{
  return num / den;
}

/****************************************************************************
 * name: overflowi16
 ****************************************************************************/

static int overflowi16(int64_t in)
{
  return in < INT16_MIN || INT16_MAX < in;
}

/****************************************************************************
 * name: sum_i
 ****************************************************************************/

static int32_t sum_i(const int16_t *in, unsigned int num)
{
  int32_t ret = 0;
  unsigned int i;

  for (i = 0; i < num; i++)
    {
      ret += *(in + i);
    }

  return ret;
}

/****************************************************************************
 * name: sum_f
 ****************************************************************************/

static float sum_f(const float *in, unsigned int num)
{
  float ret = 0.0f;
  unsigned int i;

  for (i = 0; i < num; i++)
    {
      ret += (float)*(in + i);
    }

  return ret;
}

/****************************************************************************
 * name: filter_i
 ****************************************************************************/

static int64_t filter_i(const int16_t *in,
                        unsigned int offset,
                        const struct mossdsp_firfilter_param_s *param)
{
  unsigned int inum;
  unsigned int i;
  int64_t ret = 0;

  inum = (offset < param->cnum ? offset : param->cnum);
  for (i = 0; i < inum; i++)
    {
      ret += *(in + offset - i - 1) * *(param->coefficients.i.coef + i);
    }

  for (i = inum; i < param->cnum; i++)
    {
      ret += *(param->lastdata.i + param->lnum + inum - i - 1) *
             *(param->coefficients.i.coef + i);
    }

  return ret;
}

/****************************************************************************
 * name: filter_f
 ****************************************************************************/

static float filter_f(const float *in,
                      unsigned int offset,
                      const struct mossdsp_firfilter_param_s *param)
{
  unsigned int num;
  unsigned int i;
  float ret = 0.0f;

  num = (offset < param->cnum ? offset : param->cnum);
  for (i = 0; i < num; i++)
    {
      ret += *(in + offset - i - 1) * *(param->coefficients.f + i);
    }

  for (i = num; i < param->cnum; i++)
    {
      ret += *(param->lastdata.f + param->lnum + num - i - 1) *
             *(param->coefficients.f + i);
    }

  return ret;
}

/****************************************************************************
 * name: filter_v3i
 ****************************************************************************/

static void filter_v3i(struct v3i64_s *out,
                        const mossfw_data_v3s_t *in,
                        unsigned int offset,
                        const struct mossdsp_firfilter_param_s *param)
{
  unsigned int inum;
  unsigned int i;

  inum = (offset < param->cnum ? offset : param->cnum);
  out->x = 0;
  out->y = 0;
  out->z = 0;
  for (i = 0; i < inum; i++)
    {
      out->x += (in + offset - i - 1)->x * *(param->coefficients.i.coef + i);
      out->y += (in + offset - i - 1)->y * *(param->coefficients.i.coef + i);
      out->z += (in + offset - i - 1)->z * *(param->coefficients.i.coef + i);
    }

  for (i = inum; i < param->cnum; i++)
    {
      out->x += (param->lastdata.v3i + param->lnum + inum - i - 1)->x *
                *(param->coefficients.i.coef + i);
      out->y += (param->lastdata.v3i + param->lnum + inum - i - 1)->y *
                *(param->coefficients.i.coef + i);
      out->z += (param->lastdata.v3i + param->lnum + inum - i - 1)->z *
                *(param->coefficients.i.coef + i);
    }

  return;
}

/****************************************************************************
 * name: filter_v3f
 ****************************************************************************/

static void filter_v3f(mossfw_data_v3f_t *out,
                      const mossfw_data_v3f_t *in,
                      unsigned int offset,
                      const struct mossdsp_firfilter_param_s *param)
{
  unsigned int num;
  unsigned int i;

  num = (offset < param->cnum ? offset : param->cnum);
  out->x = 0.0f;
  out->y = 0.0f;
  out->z = 0.0f;
  for (i = num; i < param->cnum; i++)
    {
      out->x += (param->lastdata.v3f + param->lnum + i - param->cnum)->x *
                *(param->coefficients.f - i + num + param->cnum - 1);
      out->y += (param->lastdata.v3f + param->lnum + i - param->cnum)->y *
                *(param->coefficients.f - i + num + param->cnum - 1);
      out->z += (param->lastdata.v3f + param->lnum + i - param->cnum)->z *
                *(param->coefficients.f - i + num + param->cnum - 1);
    }

  for (i = 0; i < num; i++)
    {
      out->x += (in + offset + i - num)->x *
                *(param->coefficients.f - i + num - 1);
      out->y += (in + offset + i - num)->y *
                *(param->coefficients.f - i + num - 1);
      out->z += (in + offset + i - num)->z *
                *(param->coefficients.f - i + num - 1);
    }

  return;
}

/****************************************************************************
 * name: filter_v3ti
 ****************************************************************************/

static void filter_v3ti(struct v3i64_s *out,
                        const mossfw_data_v3ts_t *in,
                        unsigned int offset,
                        const struct mossdsp_firfilter_param_s *param)
{
  unsigned int inum;
  unsigned int i;

  inum = (offset < param->cnum ? offset : param->cnum);
  out->x = 0;
  out->y = 0;
  out->z = 0;
  for (i = 0; i < inum; i++)
    {
      out->x += (in + offset - i - 1)->x * *(param->coefficients.i.coef + i);
      out->y += (in + offset - i - 1)->y * *(param->coefficients.i.coef + i);
      out->z += (in + offset - i - 1)->z * *(param->coefficients.i.coef + i);
    }

  for (i = inum; i < param->cnum; i++)
    {
      out->x += (param->lastdata.v3ti + param->lnum + inum - i - 1)->x *
                *(param->coefficients.i.coef + i);
      out->y += (param->lastdata.v3ti + param->lnum + inum - i - 1)->y *
                *(param->coefficients.i.coef + i);
      out->z += (param->lastdata.v3ti + param->lnum + inum - i - 1)->z *
                *(param->coefficients.i.coef + i);
    }

  return;
}

/****************************************************************************
 * name: filter_v3tf
 ****************************************************************************/

static void filter_v3tf(mossfw_data_v3tf_t *out,
                        const mossfw_data_v3tf_t *in,
                        unsigned int offset,
                        const struct mossdsp_firfilter_param_s *param)
{
  unsigned int num;
  unsigned int i;

  num = (offset < param->cnum ? offset : param->cnum);
  out->x = 0.0f;
  out->y = 0.0f;
  out->z = 0.0f;
  for (i = 0; i < num; i++)
    {
      out->x += (in + offset - i - 1)->x * *(param->coefficients.f + i);
      out->y += (in + offset - i - 1)->y * *(param->coefficients.f + i);
      out->z += (in + offset - i - 1)->z * *(param->coefficients.f + i);
    }

  for (i = num; i < param->cnum; i++)
    {
      out->x += (param->lastdata.v3tf + param->lnum + num - i - 1)->x *
                *(param->coefficients.f + i);
      out->y += (param->lastdata.v3tf + param->lnum + num - i - 1)->y *
                *(param->coefficients.f + i);
      out->z += (param->lastdata.v3tf + param->lnum + num - i - 1)->z *
                *(param->coefficients.f + i);
    }

  return;
}

/****************************************************************************
 * name: filter_v3ia
 ****************************************************************************/

static void filter_v3ia(struct v3i64_s *out,
                        const struct vector3ia_s *in,
                        unsigned int offset,
                        const struct mossdsp_firfilter_param_s *param)
{
  struct mossdsp_firfilter_param_s p;

  p = *param;
  p.lastdata.i = param->lastdata.v3ia->x;
  out->x = filter_i(in->x, offset, &p);
  p.lastdata.i = param->lastdata.v3ia->y;
  out->y = filter_i(in->y, offset, &p);
  p.lastdata.i = param->lastdata.v3ia->z;
  out->z = filter_i(in->z, offset, &p);
  return;
}

/****************************************************************************
 * name: filter_v3fa
 ****************************************************************************/

static void filter_v3fa(mossfw_data_v3f_t *out,
                        const struct vector3fa_s *in,
                        unsigned int offset,
                        const struct mossdsp_firfilter_param_s *param)
{
  struct mossdsp_firfilter_param_s p;

  p = *param;
  p.lastdata.f = param->lastdata.v3fa->x;
  out->x = filter_f(in->x, offset, &p);
  p.lastdata.f = param->lastdata.v3fa->y;
  out->y = filter_f(in->y, offset, &p);
  p.lastdata.f = param->lastdata.v3fa->z;
  out->z = filter_f(in->z, offset, &p);
  return;
}

/****************************************************************************
 * name: filter_v3tia
 ****************************************************************************/

static void filter_v3tia(struct v3i64_s *out,
                          const struct vector3tia_s *in,
                          unsigned int offset,
                          const struct mossdsp_firfilter_param_s *param)
{
  struct mossdsp_firfilter_param_s p;

  p = *param;
  p.lastdata.i = param->lastdata.v3tia->x;
  out->x = filter_i(in->x, offset, &p);
  p.lastdata.i = param->lastdata.v3tia->y;
  out->y = filter_i(in->y, offset, &p);
  p.lastdata.i = param->lastdata.v3tia->z;
  out->z = filter_i(in->z, offset, &p);
  return;
}

/****************************************************************************
 * name: filter_v3tfa
 ****************************************************************************/

static void filter_v3tfa(mossfw_data_v3f_t *out,
                          const struct vector3tfa_s *in,
                          unsigned int offset,
                          const struct mossdsp_firfilter_param_s *param)
{
  struct mossdsp_firfilter_param_s p;

  p = *param;
  p.lastdata.f = param->lastdata.v3tfa->x;
  out->x = filter_f(in->x, offset, &p);
  p.lastdata.f = param->lastdata.v3tfa->y;
  out->y = filter_f(in->y, offset, &p);
  p.lastdata.f = param->lastdata.v3tfa->z;
  out->z = filter_f(in->z, offset, &p);
  return;
}

/****************************************************************************
 * name: filter_qf
 ****************************************************************************/

static void filter_qf(mossfw_data_qf_t *out,
                      const mossfw_data_qf_t *in,
                      unsigned int offset,
                      const struct mossdsp_firfilter_param_s *param)
{
  unsigned int num;
  unsigned int i;

  num = (offset < param->cnum ? offset : param->cnum);
  out->w = 0.0f;
  out->x = 0.0f;
  out->y = 0.0f;
  out->z = 0.0f;
  for (i = 0; i < num; i++)
    {
      out->w += (in + offset - i - 1)->w * *(param->coefficients.f + i);
      out->x += (in + offset - i - 1)->x * *(param->coefficients.f + i);
      out->y += (in + offset - i - 1)->y * *(param->coefficients.f + i);
      out->z += (in + offset - i - 1)->z * *(param->coefficients.f + i);
    }

  for (i = num; i < param->cnum; i++)
    {
      out->w += (param->lastdata.qf + param->lnum + num - i - 1)->w *
                *(param->coefficients.f + i);
      out->x += (param->lastdata.qf + param->lnum + num - i - 1)->x *
                *(param->coefficients.f + i);
      out->y += (param->lastdata.qf + param->lnum + num - i - 1)->y *
                *(param->coefficients.f + i);
      out->z += (param->lastdata.qf + param->lnum + num - i - 1)->z *
                *(param->coefficients.f + i);
    }

  return;
}

/****************************************************************************
 * name: filter_qtf
 ****************************************************************************/

static void filter_qtf(mossfw_data_qtf_t *out,
                        const mossfw_data_qtf_t *in,
                        unsigned int offset,
                        const struct mossdsp_firfilter_param_s *param)
{
  unsigned int num;
  unsigned int i;

  num = (offset < param->cnum ? offset : param->cnum);
  out->w = 0.0f;
  out->x = 0.0f;
  out->y = 0.0f;
  out->z = 0.0f;
  for (i = 0; i < num; i++)
    {
      out->w += (in + offset - i - 1)->w * *(param->coefficients.f + i);
      out->x += (in + offset - i - 1)->x * *(param->coefficients.f + i);
      out->y += (in + offset - i - 1)->y * *(param->coefficients.f + i);
      out->z += (in + offset - i - 1)->z * *(param->coefficients.f + i);
    }

  for (i = num; i < param->cnum; i++)
    {
      out->w += (param->lastdata.qtf + param->lnum + num - i - 1)->w *
                *(param->coefficients.f + i);
      out->x += (param->lastdata.qtf + param->lnum + num - i - 1)->x *
                *(param->coefficients.f + i);
      out->y += (param->lastdata.qtf + param->lnum + num - i - 1)->y *
                *(param->coefficients.f + i);
      out->z += (param->lastdata.qtf + param->lnum + num - i - 1)->z *
              *(param->coefficients.f + i);
    }

  return;
}

/****************************************************************************
 * name: firfilteri_element
 ****************************************************************************/

static int firfilteri_element(int16_t *out,
                              const int16_t *in,
                              unsigned int offset,
                              const struct mossdsp_firfilter_param_s *param)
{
  int64_t sum = 0;
  int err = 0;

  sum = filter_i(in, offset + 1, param);
  sum = rshift(sum, param->coefficients.i.scale);
  if (overflowi16(sum))
    {
      err = -1;
    }
  else
    {
      *(out + offset) = (int16_t) sum;
    }

  return err;
}

/****************************************************************************
 * name: firfilterv3i_element
 ****************************************************************************/

static int firfilterv3i_element(mossfw_data_v3s_t *out,
                              const mossfw_data_v3s_t *in,
                              unsigned int offset,
                              const struct mossdsp_firfilter_param_s *param)
{
  struct v3i64_s sum =
  {
    .x = 0, .y = 0, .z = 0
  };

  int err = 0;

  filter_v3i(&sum, in, offset + 1, param);
  sum.x = rshift(sum.x, param->coefficients.i.scale);
  sum.y = rshift(sum.y, param->coefficients.i.scale);
  sum.z = rshift(sum.z, param->coefficients.i.scale);
  if (overflowi16(sum.x) || overflowi16(sum.y) || overflowi16(sum.z))
    {
      err = -1;
    }
  else
    {
      (out + offset)->x = (int16_t) sum.x;
      (out + offset)->y = (int16_t) sum.y;
      (out + offset)->z = (int16_t) sum.z;
    }

  return err;
}

/****************************************************************************
 * name: firfilterv3ti_element
 ****************************************************************************/

static int firfilterv3ti_element(mossfw_data_v3ts_t *out,
                              const mossfw_data_v3ts_t *in,
                              unsigned int offset,
                              const struct mossdsp_firfilter_param_s *param)
{
  struct v3i64_s sum =
  {
    .x = 0, .y = 0, .z = 0
  };

  int err = 0;

  filter_v3ti(&sum, in, offset + 1, param);
  sum.x = rshift(sum.x, param->coefficients.i.scale);
  sum.y = rshift(sum.y, param->coefficients.i.scale);
  sum.z = rshift(sum.z, param->coefficients.i.scale);
  if (overflowi16(sum.x) || overflowi16(sum.y) || overflowi16(sum.z))
    {
      err = -1;
    }
  else
    {
      (out + offset)->x = (int16_t) sum.x;
      (out + offset)->y = (int16_t) sum.y;
      (out + offset)->z = (int16_t) sum.z;
      (out + offset)->t = (in + offset)->t - param->delay;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_firfilterv3ia_element
 ****************************************************************************/

static int mossdsp_firfilterv3ia_element(struct vector3ia_s *out,
  const struct vector3ia_s *in,
  unsigned int offset,
  const struct mossdsp_firfilter_param_s *param)
{
  struct v3i64_s sum =
  {
    .x = 0, .y = 0, .z = 0
  };

  int err = 0;

  filter_v3ia(&sum, in, offset + 1, param);
  sum.x = rshift(sum.x, param->coefficients.i.scale);
  sum.y = rshift(sum.y, param->coefficients.i.scale);
  sum.z = rshift(sum.z, param->coefficients.i.scale);
  if (overflowi16(sum.x) || overflowi16(sum.y) || overflowi16(sum.z))
    {
      err = -1;
    }
  else
    {
      *(out->x + offset) = (int16_t) sum.x;
      *(out->y + offset) = (int16_t) sum.y;
      *(out->z + offset) = (int16_t) sum.z;
    }

  return err;
}

/****************************************************************************
 * name: firfilterv3tia_element
 ****************************************************************************/

static int firfilterv3tia_element(struct vector3tia_s *out,
                              const struct vector3tia_s *in,
                              unsigned int offset,
                              const struct mossdsp_firfilter_param_s *param)
{
  struct v3i64_s sum =
  {
    .x = 0, .y = 0, .z = 0
  };

  int err = 0;

  filter_v3tia(&sum, in, offset + 1, param);
  sum.x = rshift(sum.x, param->coefficients.i.scale);
  sum.y = rshift(sum.y, param->coefficients.i.scale);
  sum.z = rshift(sum.z, param->coefficients.i.scale);
  if (overflowi16(sum.x) || overflowi16(sum.y) || overflowi16(sum.z))
    {
      err = -1;
    }
  else
    {
      *(out->x + offset) = (int16_t) sum.x;
      *(out->y + offset) = (int16_t) sum.y;
      *(out->z + offset) = (int16_t) sum.z;
      *(out->t + offset) = *(in->t + offset) - param->delay;
    }

  return err;
}

/****************************************************************************
 * name: ffparami
 ****************************************************************************/

static void ffparami(struct mossdsp_firfilter_param_s *out,
                     struct mossdsp_iirfilter_param_s *param)
{
  out->coefficients.i.coef  = param->coef.i.ff;
  out->cnum                 = param->coef.i.ffnum;
  out->lastdata             = param->fflastdata;
  out->lnum                 = param->fflnum;
  out->coefficients.i.scale = param->coef.i.scale;
  out->delay                = param->delay;
}

/****************************************************************************
 * name: ffparamf
 ****************************************************************************/

static void ffparamf(struct mossdsp_firfilter_param_s *out,
                     struct mossdsp_iirfilter_param_s *param)
{
  out->coefficients.f  = param->coef.f.ff;
  out->cnum            = param->coef.f.ffnum;
  out->lastdata        = param->fflastdata;
  out->lnum            = param->fflnum;
  out->delay           = param->delay;
}

/****************************************************************************
 * name: fbparami
 ****************************************************************************/

static void fbparami(struct mossdsp_firfilter_param_s *out,
                     struct mossdsp_iirfilter_param_s *param)
{
  out->coefficients.i.coef  = param->coef.i.fb;
  out->cnum                 = param->coef.i.fbnum;
  out->lastdata             = param->fblastdata;
  out->lnum                 = param->fblnum;
  out->coefficients.i.scale = param->coef.i.scale;
  out->delay                = param->delay;
}

/****************************************************************************
 * name: fbparamf
 ****************************************************************************/

static void fbparamf(struct mossdsp_firfilter_param_s *out,
                     struct mossdsp_iirfilter_param_s *param)
{
  out->coefficients.f  = param->coef.f.fb;
  out->cnum            = param->coef.f.fbnum;
  out->lastdata        = param->fblastdata;
  out->lnum            = param->fblnum;
  out->delay           = param->delay;
}

/****************************************************************************
 * name: iirfilteri_element
 ****************************************************************************/

static int iirfilteri_element(int16_t *out,
                              unsigned int ooffset,
                              const int16_t *in,
                              unsigned int ioffset,
                              struct mossdsp_iirfilter_param_s *param)
{
  int64_t sum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  int ret = 0;

  ffparami(&ff, param);
  fbparami(&fb, param);
  sum = rshift((filter_i(in, ioffset + 1, &ff) +
      filter_i(out, ooffset, &fb)), param->coef.i.scale);
  if (overflowi16(sum))
    {
      ret = -1;
    }
  else
    {
      *(out + ooffset) = (int16_t) sum;
    }

  return ret;
}

/****************************************************************************
 * name: iirfilterv3i_element
 ****************************************************************************/

static int iirfilterv3i_element(mossfw_data_v3s_t *out,
                                unsigned int ooffset,
                                const mossfw_data_v3s_t *in,
                                unsigned int ioffset,
                                struct mossdsp_iirfilter_param_s *param)
{
  struct v3i64_s ffsum =
  {
    .x = 0, .y = 0, .z = 0
  };

  struct v3i64_s fbsum =
  {
    .x = 0, .y = 0, .z = 0
  };

  struct v3i64_s sum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  int ret = 0;

  ffparami(&ff, param);
  fbparami(&fb, param);
  filter_v3i(&ffsum, in, ioffset + 1, &ff);
  filter_v3i(&fbsum, out, ooffset, &fb);
  sum.x = rshift((ffsum.x + fbsum.x), param->coef.i.scale);
  sum.y = rshift((ffsum.y + fbsum.y), param->coef.i.scale);
  sum.z = rshift((ffsum.z + fbsum.z), param->coef.i.scale);
  if (overflowi16(sum.x) || overflowi16(sum.y) || overflowi16(sum.z))
    {
      ret = -1;
    }
  else
    {
      (out + ooffset)->x = (int16_t) sum.x;
      (out + ooffset)->y = (int16_t) sum.y;
      (out + ooffset)->z = (int16_t) sum.z;
    }

  return ret;
}

/****************************************************************************
 * name: iirfilterv3ia_element
 ****************************************************************************/

static int iirfilterv3ia_element(struct vector3ia_s *out,
                                  unsigned int ooffset,
                                  const struct vector3ia_s *in,
                                  unsigned int ioffset,
                                  struct mossdsp_iirfilter_param_s *param)
{
  struct v3i64_s ffsum =
  {
    .x = 0, .y = 0, .z = 0
  };

  struct v3i64_s fbsum =
  {
    .x = 0, .y = 0, .z = 0
  };

  struct v3i64_s sum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  int ret = 0;

  ffparami(&ff, param);
  fbparami(&fb, param);
  filter_v3ia(&ffsum, in, ioffset + 1, &ff);
  filter_v3ia(&fbsum, out, ooffset, &fb);
  sum.x = rshift((ffsum.x + fbsum.x), param->coef.i.scale);
  sum.y = rshift((ffsum.y + fbsum.y), param->coef.i.scale);
  sum.z = rshift((ffsum.z + fbsum.z), param->coef.i.scale);
  if (overflowi16(sum.x) || overflowi16(sum.y) || overflowi16(sum.z))
    {
      ret = -1;
    }
  else
    {
      *(out->x + ooffset) = (int16_t) sum.x;
      *(out->y + ooffset) = (int16_t) sum.y;
      *(out->z + ooffset) = (int16_t) sum.z;
    }

  return ret;
}

/****************************************************************************
 * name: iirfilterv3ti_element
 ****************************************************************************/

static int iirfilterv3ti_element(mossfw_data_v3ts_t *out,
                                  unsigned int ooffset,
                                  const mossfw_data_v3ts_t *in,
                                  unsigned int ioffset,
                                  struct mossdsp_iirfilter_param_s *param)
{
  struct v3i64_s ffsum =
  {
    .x = 0, .y = 0, .z = 0
  };

  struct v3i64_s fbsum =
  {
    .x = 0, .y = 0, .z = 0
  };

  struct v3i64_s sum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  int ret = 0;

  ffparami(&ff, param);
  fbparami(&fb, param);
  filter_v3ti(&ffsum, in, ioffset + 1, &ff);
  filter_v3ti(&fbsum, out, ooffset, &fb);
  sum.x = rshift((ffsum.x + fbsum.x), param->coef.i.scale);
  sum.y = rshift((ffsum.y + fbsum.y), param->coef.i.scale);
  sum.z = rshift((ffsum.z + fbsum.z), param->coef.i.scale);
  if (overflowi16(sum.x) || overflowi16(sum.y) || overflowi16(sum.z))
    {
      ret = -1;
    }
  else
    {
      (out + ooffset)->x = (int16_t) sum.x;
      (out + ooffset)->y = (int16_t) sum.y;
      (out + ooffset)->z = (int16_t) sum.z;
      (out + ooffset)->t = (in + ioffset)->t - param->delay;
    }

  return ret;
}

/****************************************************************************
 * name: iirfilterv3tia_element
 ****************************************************************************/

static int iirfilterv3tia_element(struct vector3tia_s *out,
                                  unsigned int ooffset,
                                  const struct vector3tia_s *in,
                                  unsigned int ioffset,
                                  struct mossdsp_iirfilter_param_s *param)
{
  struct v3i64_s ffsum =
  {
    .x = 0, .y = 0, .z = 0
  };

  struct v3i64_s fbsum =
  {
    .x = 0, .y = 0, .z = 0
  };

  struct v3i64_s sum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  int ret = 0;

  ffparami(&ff, param);
  fbparami(&fb, param);
  filter_v3tia(&ffsum, in, ioffset + 1, &ff);
  filter_v3tia(&fbsum, out, ooffset, &fb);
  sum.x = rshift((ffsum.x + fbsum.x), param->coef.i.scale);
  sum.y = rshift((ffsum.y + fbsum.y), param->coef.i.scale);
  sum.z = rshift((ffsum.z + fbsum.z), param->coef.i.scale);
  if (overflowi16(sum.x) || overflowi16(sum.y) || overflowi16(sum.z))
    {
      ret = -1;
    }
  else
    {
      *(out->x + ooffset) = (int16_t) sum.x;
      *(out->y + ooffset) = (int16_t) sum.y;
      *(out->z + ooffset) = (int16_t) sum.z;
      *(out->t + ooffset) = *(in->t + ioffset) - param->delay;
    }

  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossdsp_firfilteri
 ****************************************************************************/

int mossdsp_firfilteri(int16_t *out,
                        const int16_t *in,
                        unsigned int num,
                        const struct mossdsp_firfilter_param_s *param)
{
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coefficients.i.coef != NULL &&
          param->lastdata.i != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      err = firfilteri_element(out, in, i, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_firfilterf
 ****************************************************************************/

int mossdsp_firfilterf(float *out,
                      const float *in,
                      unsigned int num,
                      const struct mossdsp_firfilter_param_s *param)
{
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coefficients.f != NULL &&
          param->lastdata.f != NULL) - 1;
  for (i = 0; i < num && !err; i++)
    {
      *(out + i) = filter_f(in, i + 1, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_firfilterv3i
 ****************************************************************************/

int mossdsp_firfilterv3i(mossfw_data_v3s_t *out,
                        const mossfw_data_v3s_t *in,
                        unsigned int num,
                        const struct mossdsp_firfilter_param_s *param)
{
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coefficients.i.coef != NULL &&
          param->lastdata.v3i != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      err = firfilterv3i_element(out, in, i, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_firfilterv3f
 ****************************************************************************/

int mossdsp_firfilterv3f(mossfw_data_v3f_t *out,
                        const mossfw_data_v3f_t *in,
                        unsigned int num,
                        const struct mossdsp_firfilter_param_s *param)
{
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coefficients.f != NULL &&
          param->lastdata.v3f != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      filter_v3f(out + i, in, i + 1, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_firfilterv3ti
 ****************************************************************************/

int mossdsp_firfilterv3ti(mossfw_data_v3ts_t *out,
                          const mossfw_data_v3ts_t *in,
                          unsigned int num,
                          const struct mossdsp_firfilter_param_s *param)
{
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coefficients.i.coef != NULL &&
          param->lastdata.v3ti != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      err = firfilterv3ti_element(out, in, i, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_firfilterv3tf
 ****************************************************************************/

int mossdsp_firfilterv3tf(mossfw_data_v3tf_t *out,
                          const mossfw_data_v3tf_t *in,
                          unsigned int num,
                          const struct mossdsp_firfilter_param_s *param)
{
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coefficients.f != NULL &&
          param->lastdata.v3tf != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      filter_v3tf(out + i, in, i + 1, param);
      (out + i)->t = (in + i)->t - param->delay;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_firfilterv3ia
 ****************************************************************************/

int mossdsp_firfilterv3ia(struct vector3ia_s *out,
                          const struct vector3ia_s *in,
                          unsigned int num,
                          const struct mossdsp_firfilter_param_s *param)
{
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL && out->z != NULL) - 1;
  err = (!err && in->x != NULL && in->y != NULL && in->z != NULL) - 1;
  err = (!err && param->coefficients.i.coef != NULL &&
          param->lastdata.v3i != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      err = mossdsp_firfilterv3ia_element(out, in, i, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_firfilterv3fa
 ****************************************************************************/

int mossdsp_firfilterv3fa(struct vector3fa_s *out,
                          const struct vector3fa_s *in,
                          unsigned int num,
                          const struct mossdsp_firfilter_param_s *param)
{
  mossfw_data_v3f_t sum;
  unsigned int i;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL && out->z != NULL) - 1;
  err = (!err && in->x != NULL && in->y != NULL && in->z != NULL) - 1;
  err = (!err && param->coefficients.f != NULL &&
          param->lastdata.v3f != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      filter_v3fa(&sum, in, i + 1, param);
      *(out->x + i) = sum.x;
      *(out->y + i) = sum.y;
      *(out->z + i) = sum.z;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_firfilterv3tia
 ****************************************************************************/

int mossdsp_firfilterv3tia(struct vector3tia_s *out,
                            const struct vector3tia_s *in,
                            unsigned int num,
                            const struct mossdsp_firfilter_param_s *param)
{
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL &&
          out->z != NULL && out->t != NULL) - 1;
  err = (!err &&  in->x != NULL &&  in->y != NULL &&
          in->z != NULL &&  in->t != NULL) - 1;
  err = (!err && param->coefficients.i.coef != NULL &&
          param->lastdata.v3i != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      err = firfilterv3tia_element(out, in, i, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_firfilterv3tfa
 ****************************************************************************/

int mossdsp_firfilterv3tfa(struct vector3tfa_s *out,
                            const struct vector3tfa_s *in,
                            unsigned int num,
                            const struct mossdsp_firfilter_param_s *param)
{
  mossfw_data_v3f_t sum;
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL &&
          out->z != NULL && out->t != NULL) - 1;
  err = (!err &&  in->x != NULL &&  in->y != NULL &&
          in->z != NULL &&  in->t != NULL) - 1;
  err = (!err && param->coefficients.f != NULL &&
          param->lastdata.v3fa != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      filter_v3tfa(&sum, in, i + 1, param);
      *(out->x + i) = sum.x;
      *(out->y + i) = sum.y;
      *(out->z + i) = sum.z;
      *(out->t + i) = *(in->t + i) - param->delay;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_iirfilteri
 ****************************************************************************/

int mossdsp_iirfilteri(int16_t *out,
                        const int16_t *in,
                        unsigned int num,
                        struct mossdsp_iirfilter_param_s *param)
{
  int err = 0;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coef.i.ff != NULL &&
          param->fflastdata.v3ti != NULL) - 1;
  err = (!err && param->coef.i.fb != NULL &&
          param->fblastdata.v3ti != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      err = iirfilteri_element(out, i, in, i, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_iirfilterf
 ****************************************************************************/

int mossdsp_iirfilterf(float *out,
                        const float *in,
                        unsigned int num,
                        struct mossdsp_iirfilter_param_s *param)
{
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coef.f.ff != NULL &&
          param->fflastdata.v3f != NULL) - 1;
  err = (!err && param->coef.f.fb != NULL &&
          param->fblastdata.v3f != NULL) - 1;
  if (!err)
    {
      ffparamf(&ff, param);
      fbparamf(&fb, param);
    }

  for (i = 0; i < num && !err; i++)
    {
      *(out + i) = filter_f(in, i + 1, &ff) + filter_f(out, i, &fb);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_iirfilterv3i
 ****************************************************************************/

int mossdsp_iirfilterv3i(mossfw_data_v3s_t *out,
                          const mossfw_data_v3s_t *in,
                          unsigned int num,
                          struct mossdsp_iirfilter_param_s *param)
{
  int err = 0;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coef.i.ff != NULL &&
          param->fflastdata.v3ti != NULL) - 1;
  err = (!err && param->coef.i.fb != NULL &&
          param->fblastdata.v3ti != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      err = iirfilterv3i_element(out, i, in, i, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_iirfilterv3f
 ****************************************************************************/

int mossdsp_iirfilterv3f(mossfw_data_v3f_t *out,
                        const mossfw_data_v3f_t *in,
                        unsigned int num,
                        struct mossdsp_iirfilter_param_s *param)
{
  mossfw_data_v3f_t ffsum;
  mossfw_data_v3f_t fbsum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coef.f.ff != NULL &&
          param->fflastdata.v3f != NULL) - 1;
  err = (!err && param->coef.f.fb != NULL &&
          param->fblastdata.v3f != NULL) - 1;
  if (!err)
    {
      ffparamf(&ff, param);
      fbparamf(&fb, param);
    }

  for (i = 0; i < num && !err; i++)
    {
      filter_v3f(&ffsum, in, i + 1, &ff);
      filter_v3f(&fbsum, out,    i, &fb);
      (out + i)->x = ffsum.x + fbsum.x;
      (out + i)->y = ffsum.y + fbsum.y;
      (out + i)->z = ffsum.z + fbsum.z;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_iirfilterv3ti
 ****************************************************************************/

int mossdsp_iirfilterv3ti(mossfw_data_v3ts_t *out,
                          const mossfw_data_v3ts_t *in,
                          unsigned int num,
                          struct mossdsp_iirfilter_param_s *param)
{
  int err = 0;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coef.i.ff != NULL &&
          param->fflastdata.v3ti != NULL) - 1;
  err = (!err && param->coef.i.fb != NULL &&
          param->fblastdata.v3ti != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      err = iirfilterv3ti_element(out, i, in, i, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_iirfilterv3tf
 ****************************************************************************/

int mossdsp_iirfilterv3tf(mossfw_data_v3tf_t *out,
                          const mossfw_data_v3tf_t *in,
                          unsigned int num,
                          struct mossdsp_iirfilter_param_s *param)
{
  mossfw_data_v3tf_t ffsum;
  mossfw_data_v3tf_t fbsum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  int err;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->coef.f.ff != NULL &&
          param->fflastdata.v3tf != NULL) - 1;
  err = (!err && param->coef.f.fb != NULL &&
          param->fblastdata.v3tf != NULL) - 1;
  if (!err)
    {
      ffparamf(&ff, param);
      fbparamf(&fb, param);
    }

  for (i = 0; i < num && err == 0; i++)
    {
      filter_v3tf(&ffsum, in, i + 1, &ff);
      filter_v3tf(&fbsum, out,    i, &fb);
      (out + i)->x = ffsum.x + fbsum.x;
      (out + i)->y = ffsum.y + fbsum.y;
      (out + i)->z = ffsum.z + fbsum.z;
      (out + i)->t = (in + i)->t - param->delay;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_iirfilterv3ia
 ****************************************************************************/

int mossdsp_iirfilterv3ia(struct vector3ia_s *out,
                          const struct vector3ia_s *in,
                          unsigned int num,
                          struct mossdsp_iirfilter_param_s *param)
{
  int err = 0;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL && out->z != NULL) - 1;
  err = (!err &&  in->x != NULL &&  in->y != NULL &&  in->z != NULL) - 1;
  err = (!err && param->coef.i.ff != NULL &&
          param->fflastdata.v3ia != NULL) - 1;
  err = (!err && param->coef.i.fb != NULL &&
          param->fblastdata.v3ia != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      err = iirfilterv3ia_element(out, i, in, i, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_iirfilterv3fa
 ****************************************************************************/

int mossdsp_iirfilterv3fa(struct vector3fa_s *out,
                          const struct vector3fa_s *in,
                          unsigned int num,
                          struct mossdsp_iirfilter_param_s *param)
{
  mossfw_data_v3f_t ffsum;
  mossfw_data_v3f_t fbsum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  int err = 0;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL && out->z != NULL) - 1;
  err = (!err &&  in->x != NULL &&  in->y != NULL &&  in->z != NULL) - 1;
  err = (!err && param->coef.f.ff != NULL &&
          param->fflastdata.v3fa != NULL) - 1;
  err = (!err && param->coef.f.fb != NULL &&
          param->fblastdata.v3fa != NULL) - 1;
  if (!err)
    {
      ffparamf(&ff, param);
      fbparamf(&fb, param);
    }

  for (i = 0; i < num && err == 0; i++)
    {
      filter_v3fa(&ffsum, in, i + 1, &ff);
      filter_v3fa(&fbsum, out,    i, &fb);
      *(out->x + i) = ffsum.x + fbsum.x;
      *(out->y + i) = ffsum.y + fbsum.y;
      *(out->z + i) = ffsum.z + fbsum.z;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_iirfilterv3tia
 ****************************************************************************/

int mossdsp_iirfilterv3tia(struct vector3tia_s *out,
                            const struct vector3tia_s *in,
                            unsigned int num,
                            struct mossdsp_iirfilter_param_s *param)
{
  int err = 0;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL &&
          out->z != NULL && out->t != NULL) - 1;
  err = (!err &&  in->x != NULL &&  in->y != NULL &&
          in->z != NULL &&  in->t != NULL) - 1;
  err = (!err && param->coef.i.ff != NULL &&
          param->fflastdata.v3tia != NULL) - 1;
  err = (!err && param->coef.i.fb != NULL &&
          param->fblastdata.v3tia != NULL) - 1;
  for (i = 0; i < num && err == 0; i++)
    {
      err = iirfilterv3tia_element(out, i, in, i, param);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_iirfilterv3tfa
 ****************************************************************************/

int mossdsp_iirfilterv3tfa(struct vector3tfa_s *out,
                            const struct vector3tfa_s *in,
                            unsigned int num,
                            struct mossdsp_iirfilter_param_s *param)
{
  mossfw_data_v3f_t ffsum;
  mossfw_data_v3f_t fbsum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  int err = 0;
  unsigned int i;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL &&
          out->z != NULL && out->t != NULL) - 1;
  err = (!err &&  in->x != NULL &&  in->y != NULL &&
          in->z != NULL &&  in->t != NULL) - 1;
  err = (!err && param->coef.f.ff != NULL &&
          param->fflastdata.v3tfa != NULL) - 1;
  err = (!err && param->coef.f.fb != NULL &&
          param->fblastdata.v3tfa != NULL) - 1;
  if (!err)
    {
      ffparamf(&ff, param);
      fbparamf(&fb, param);
    }

  for (i = 0; i < num && err == 0; i++)
    {
      filter_v3tfa(&ffsum, in, i + 1, &ff);
      filter_v3tfa(&fbsum, out,    i, &fb);
      *(out->x + i) = ffsum.x + fbsum.x;
      *(out->y + i) = ffsum.y + fbsum.y;
      *(out->z + i) = ffsum.z + fbsum.z;
      *(out->t + i) = *(in->t + i) - param->delay;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimatei
 ****************************************************************************/

int mossdsp_decimatei(int16_t *out,
                      const int16_t *in,
                      unsigned int num,
                      struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->filterparam.coef.i.ff != NULL &&
          param->filterparam.fflastdata.i != NULL) - 1;
  err = (!err && param->filterparam.coef.i.fb != NULL &&
          param->filterparam.fblastdata.i != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      err = iirfilteri_element(out, j, in, i, &(param->filterparam));
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimatef
 ****************************************************************************/

int mossdsp_decimatef(float *out,
                      const float *in,
                      unsigned int num,
                      struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->filterparam.coef.f.ff != NULL &&
          param->filterparam.fflastdata.f != NULL) - 1;
  err = (!err && param->filterparam.coef.f.fb != NULL &&
          param->filterparam.fblastdata.f != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
      ffparamf(&ff, &param->filterparam);
      fbparamf(&fb, &param->filterparam);
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      *(out + j) = filter_f(in, i + 1, &ff) + filter_f(out, j, &fb);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimatev3i
 ****************************************************************************/

int mossdsp_decimatev3i(mossfw_data_v3s_t *out,
                        const mossfw_data_v3s_t *in,
                        unsigned int num,
                        struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->filterparam.coef.i.ff != NULL &&
          param->filterparam.fflastdata.v3i != NULL) - 1;
  err = (!err && param->filterparam.coef.i.fb != NULL &&
          param->filterparam.fblastdata.v3i != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      err = iirfilterv3i_element(out, j, in, i, &(param->filterparam));
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimatev3f
 ****************************************************************************/

int mossdsp_decimatev3f(mossfw_data_v3f_t *out,
                        const mossfw_data_v3f_t *in,
                        unsigned int num,
                        struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  mossfw_data_v3f_t ffsum;
  mossfw_data_v3f_t fbsum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->filterparam.coef.f.ff != NULL &&
          param->filterparam.fflastdata.v3f != NULL) - 1;
  err = (!err && param->filterparam.coef.f.fb != NULL &&
          param->filterparam.fblastdata.v3f != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
      ffparamf(&ff, &param->filterparam);
      fbparamf(&fb, &param->filterparam);
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      filter_v3f(&ffsum, in, i + 1, &ff);
      filter_v3f(&fbsum, out,    j, &fb);
      (out + j)->x = ffsum.x + fbsum.x;
      (out + j)->y = ffsum.y + fbsum.y;
      (out + j)->z = ffsum.z + fbsum.z;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimatev3ti
 ****************************************************************************/

int mossdsp_decimatev3ti(mossfw_data_v3ts_t *out,
                          const mossfw_data_v3ts_t *in,
                          unsigned int num,
                          struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->filterparam.coef.i.ff != NULL &&
          param->filterparam.fflastdata.v3ti != NULL) - 1;
  err = (!err && param->filterparam.coef.i.fb != NULL &&
          param->filterparam.fblastdata.v3ti != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      err = iirfilterv3ti_element(out, j, in, i, &(param->filterparam));
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimatev3tf
 ****************************************************************************/

int mossdsp_decimatev3tf(mossfw_data_v3tf_t *out,
                        const mossfw_data_v3tf_t *in,
                        unsigned int num,
                        struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  mossfw_data_v3tf_t ffsum;
  mossfw_data_v3tf_t fbsum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->filterparam.coef.f.ff != NULL &&
          param->filterparam.fflastdata.v3tf != NULL) - 1;
  err = (!err && param->filterparam.coef.f.fb != NULL &&
          param->filterparam.fblastdata.v3tf != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
      ffparamf(&ff, &param->filterparam);
      fbparamf(&fb, &param->filterparam);
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      filter_v3tf(&ffsum, in, i + 1, &ff);
      filter_v3tf(&fbsum, out,    j, &fb);
      (out + j)->x = ffsum.x + fbsum.x;
      (out + j)->y = ffsum.y + fbsum.y;
      (out + j)->z = ffsum.z + fbsum.z;
      (out + j)->t = (in + i)->t - param->filterparam.delay;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimatev3ia
 ****************************************************************************/

int mossdsp_decimatev3ia(struct vector3ia_s *out,
                        const struct vector3ia_s *in,
                        unsigned int num,
                        struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL && out->z != NULL) - 1;
  err = (!err &&  in->x != NULL &&  in->y != NULL &&  in->z != NULL) - 1;
  err = (!err && param->filterparam.coef.i.ff != NULL &&
          param->filterparam.fflastdata.v3ia != NULL) - 1;
  err = (!err && param->filterparam.coef.i.fb != NULL &&
          param->filterparam.fblastdata.v3ia != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      err = iirfilterv3ia_element(out, j, in, i, &(param->filterparam));
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimatev3fa
 ****************************************************************************/

int mossdsp_decimatev3fa(struct vector3fa_s *out,
                        const struct vector3fa_s *in,
                        unsigned int num,
                        struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  mossfw_data_v3f_t ffsum;
  mossfw_data_v3f_t fbsum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL && out->z != NULL) - 1;
  err = (!err &&  in->x != NULL &&  in->y != NULL &&  in->z != NULL) - 1;
  err = (!err && param->filterparam.coef.i.ff != NULL &&
          param->filterparam.fflastdata.v3ia != NULL) - 1;
  err = (!err && param->filterparam.coef.i.fb != NULL &&
          param->filterparam.fblastdata.v3ia != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
      ffparamf(&ff, &param->filterparam);
      fbparamf(&fb, &param->filterparam);
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      filter_v3fa(&ffsum, in, i + 1, &ff);
      filter_v3fa(&fbsum, out,    j, &fb);
      *(out->x + j) = ffsum.x + fbsum.x;
      *(out->y + j) = ffsum.y + fbsum.y;
      *(out->z + j) = ffsum.z + fbsum.z;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimatev3tia
 ****************************************************************************/

int mossdsp_decimatev3tia(struct vector3tia_s *out,
                          const struct vector3tia_s *in,
                          unsigned int num,
                          struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL &&
          out->z != NULL && out->t != NULL) - 1;
  err = (!err &&  in->x != NULL &&  in->y != NULL &&
          in->z != NULL &&  in->t != NULL) - 1;
  err = (!err && param->filterparam.coef.i.ff != NULL &&
          param->filterparam.fflastdata.v3tia != NULL) - 1;
  err = (!err && param->filterparam.coef.i.fb != NULL &&
          param->filterparam.fblastdata.v3tia != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      err = iirfilterv3tia_element(out, j, in, i, &(param->filterparam));
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimatev3tfa
 ****************************************************************************/

int mossdsp_decimatev3tfa(struct vector3tfa_s *out,
                          const struct vector3tfa_s *in,
                          unsigned int num,
                          struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  mossfw_data_v3f_t ffsum;
  mossfw_data_v3f_t fbsum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL &&
          out->z != NULL && out->t != NULL) - 1;
  err = (!err &&  in->x != NULL &&  in->y != NULL &&
          in->z != NULL &&  in->t != NULL) - 1;
  err = (!err && param->filterparam.coef.i.ff != NULL &&
          param->filterparam.fflastdata.v3tia != NULL) - 1;
  err = (!err && param->filterparam.coef.i.fb != NULL &&
          param->filterparam.fblastdata.v3tia != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
      ffparamf(&ff, &param->filterparam);
      fbparamf(&fb, &param->filterparam);
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      filter_v3tfa(&ffsum, in, i + 1, &ff);
      filter_v3tfa(&fbsum, out,    j, &fb);
      *(out->x + j) = ffsum.x + fbsum.x;
      *(out->y + j) = ffsum.y + fbsum.y;
      *(out->z + j) = ffsum.z + fbsum.z;
      *(out->t + j) = *(in->t + i) - param->filterparam.delay;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimateqf
 ****************************************************************************/

int mossdsp_decimateqf(mossfw_data_qf_t *out,
                      const mossfw_data_qf_t *in,
                      unsigned int num,
                      struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  mossfw_data_qf_t ffsum;
  mossfw_data_qf_t fbsum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->filterparam.coef.f.ff != NULL &&
          param->filterparam.fflastdata.qf != NULL) - 1;
  err = (!err && param->filterparam.coef.f.fb != NULL &&
          param->filterparam.fblastdata.qf != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
      ffparamf(&ff, &param->filterparam);
      fbparamf(&fb, &param->filterparam);
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      filter_qf(&ffsum, in, i + 1, &ff);
      filter_qf(&fbsum, out,    j, &fb);
      (out + j)->w = ffsum.w + fbsum.w;
      (out + j)->x = ffsum.x + fbsum.x;
      (out + j)->y = ffsum.y + fbsum.y;
      (out + j)->z = ffsum.z + fbsum.z;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_decimateqtf
 ****************************************************************************/

int mossdsp_decimateqtf(mossfw_data_qtf_t *out,
                        const mossfw_data_qtf_t *in,
                        unsigned int num,
                        struct mossdsp_decimate_param_s *param)
{
  unsigned int offset = 0;
  mossfw_data_qtf_t ffsum;
  mossfw_data_qtf_t fbsum;
  struct mossdsp_firfilter_param_s ff;
  struct mossdsp_firfilter_param_s fb;
  unsigned int i;
  unsigned int j;
  int err;

  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && param->filterparam.coef.f.ff != NULL &&
          param->filterparam.fflastdata.qtf != NULL) - 1;
  err = (!err && param->filterparam.coef.f.fb != NULL &&
          param->filterparam.fblastdata.qtf != NULL) - 1;
  if (!err)
    {
      offset = param->offset;
      ffparamf(&ff, &param->filterparam);
      fbparamf(&fb, &param->filterparam);
    }

  for (i = offset, j = 0; i < num && !err; i += param->factor, j++)
    {
      filter_qtf(&ffsum, in, i + 1, &ff);
      filter_qtf(&fbsum, out,    j, &fb);
      (out + j)->w = ffsum.w + fbsum.w;
      (out + j)->x = ffsum.x + fbsum.x;
      (out + j)->y = ffsum.y + fbsum.y;
      (out + j)->z = ffsum.z + fbsum.z;
      (out + j)->t = (in + i)->t - param->filterparam.delay;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_averagei
 ****************************************************************************/

int16_t mossdsp_averagei(const int16_t *in, unsigned int num)
{
  int16_t ret = 0;
#if defined(MOSSFW_USE_ARMCMSIS_DSP)
  arm_mean_q15(in, num, &ret);
#else
  int err;

  err = ((in != NULL) && (0 < num)) - 1;
  if (!err)
    {
      ret = (int16_t) divround(sum_i(in, num), (int32_t)num);
    }

#endif
  return ret;
}

/****************************************************************************
 * name: mossdsp_averagef
 ****************************************************************************/

float mossdsp_averagef(const float *in, unsigned int num)
{
  float ret = 0.0f;
  int err;

  err = ((in != NULL) && (0 < num)) - 1;
  if (!err)
    {
      ret = sum_f(in, num) / (float)num;
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_averagev3i
 ****************************************************************************/

int mossdsp_averagev3i(mossfw_data_v3s_t *out,
                      const mossfw_data_v3s_t *in,
                      unsigned int num)
{
  int err = 0;
  unsigned int i;
  int32_t sumx = 0;
  int32_t sumy = 0;
  int32_t sumz = 0;

  err = (out != NULL && in != NULL && 0 < num) - 1;
  for (i = 0; i < num && !err; i++)
    {
      sumx += (in + i)->x;
      sumy += (in + i)->y;
      sumz += (in + i)->z;
    }

  if (!err)
    {
      out->x = divround(sumx, (int32_t)num);
      out->y = divround(sumy, (int32_t)num);
      out->z = divround(sumz, (int32_t)num);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_averagev3f
 ****************************************************************************/

int mossdsp_averagev3f(mossfw_data_v3f_t *out,
                      const mossfw_data_v3f_t *in,
                      unsigned int num)
{
  int err = 0;
  unsigned int i;
  float sumx = 0;
  float sumy = 0;
  float sumz = 0;

  err = (out != NULL && in != NULL && 0 < num) - 1;
  for (i = 0; i < num && !err; i++)
    {
      sumx += (in + i)->x;
      sumy += (in + i)->y;
      sumz += (in + i)->z;
    }

  if (!err)
    {
      out->x = sumx / (float) num;
      out->y = sumy / (float) num;
      out->z = sumz / (float) num;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_averagev3ia
 ****************************************************************************/

int mossdsp_averagev3ia(mossfw_data_v3s_t *out,
                        const struct vector3ia_s *in,
                        unsigned int num)
{
  int err = 0;

  err = (out != NULL && in != NULL && 0 < num) - 1;
  err = (!err && in->x != NULL && in->y != NULL && in->z != NULL) - 1;
  if (!err)
    {
      out->x = mossdsp_averagei(in->x, num);
      out->y = mossdsp_averagei(in->y, num);
      out->z = mossdsp_averagei(in->z, num);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_averagev3fa
 ****************************************************************************/

int mossdsp_averagev3fa(mossfw_data_v3f_t *out,
                        const struct vector3fa_s *in,
                        unsigned int num)
{
  int err = 0;

  err = (out != NULL && in != NULL && 0 < num) - 1;
  err = (!err && in->x != NULL && in->y != NULL && in->z != NULL) - 1;
  if (!err)
    {
      out->x = mossdsp_averagef(in->x, num);
      out->y = mossdsp_averagef(in->y, num);
      out->z = mossdsp_averagef(in->z, num);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_averagev3ti
 ****************************************************************************/

int mossdsp_averagev3ti(mossfw_data_v3s_t *out,
                        const mossfw_data_v3ts_t *in,
                        unsigned int num)
{
  int err = 0;
  unsigned int i;
  int32_t sumx = 0;
  int32_t sumy = 0;
  int32_t sumz = 0;

  err = (out != NULL && in != NULL && 0 < num) - 1;
  for (i = 0; i < num && !err; i++)
    {
      sumx += (in + i)->x;
      sumy += (in + i)->y;
      sumz += (in + i)->z;
    }

  if (!err)
    {
      out->x = divround(sumx, (int32_t) num);
      out->y = divround(sumy, (int32_t) num);
      out->z = divround(sumz, (int32_t) num);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_averagev3tf
 ****************************************************************************/

int mossdsp_averagev3tf(mossfw_data_v3f_t *out,
                        const mossfw_data_v3tf_t *in,
                        unsigned int num)
{
  int err = 0;
  unsigned int i;
  float sumx = 0;
  float sumy = 0;
  float sumz = 0;

  err = (out != NULL && in != NULL && 0 < num) - 1;
  for (i = 0; i < num && !err; i++)
    {
      sumx += (in + i)->x;
      sumy += (in + i)->y;
      sumz += (in + i)->z;
    }

  if (!err)
    {
      out->x = sumx / (float) num;
      out->y = sumy / (float) num;
      out->z = sumz / (float) num;
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_averagev3tia
 ****************************************************************************/

int mossdsp_averagev3tia(mossfw_data_v3s_t *out,
                          const struct vector3tia_s *in,
                          unsigned int num)
{
  int err = 0;

  err = (out != NULL && in != NULL && 0 < num) - 1;
  err = (!err && in->t != NULL && in->x != NULL &&
          in->y != NULL && in->z != NULL) - 1;
  if (!err)
    {
      out->x = mossdsp_averagei(in->x, num);
      out->y = mossdsp_averagei(in->y, num);
      out->z = mossdsp_averagei(in->z, num);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_averagev3tfa
 ****************************************************************************/

int mossdsp_averagev3tfa(mossfw_data_v3f_t *out,
                        const struct vector3tfa_s *in,
                        unsigned int num)
{
  int err = 0;

  err = (out != NULL && in != NULL && 0 < num) - 1;
  err = (!err && in->t != NULL && in->x != NULL &&
          in->y != NULL && in->z != NULL) - 1;
  if (!err)
    {
      out->x = mossdsp_averagef(in->x, num);
      out->y = mossdsp_averagef(in->y, num);
      out->z = mossdsp_averagef(in->z, num);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_variancei
 ****************************************************************************/

int16_t mossdsp_variancei(const int16_t *in, unsigned int num)
{
  int32_t ret = 0;
  float mse = 0.0f;
  float average;
  float var;
  int err;
  unsigned int i;

  err = ((in != NULL) && (1 < num)) - 1;
  if (!err)
    {
      average = (float)sum_i(in, num) / (float)num;
    }

  for (i = 0; i < num && !err; i++)
    {
      mse += (*(in + i) - average) * (*(in + i) - average);
    }

  if (!err)
    {
      var = (mse / num) + 0.5f;
      ret = INT16_MAX < var ? INT16_MAX : var;
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_variancef
 ****************************************************************************/

float mossdsp_variancef(const float *in, unsigned int num)
{
  float ret = 0;
  float mse = 0.0f;
  float average;
  int err;
  unsigned int i;

  err = ((in != NULL) && (1 < num)) - 1;
  if (!err)
    {
      average = sum_f(in, num) / (float)num;
    }

  for (i = 0; i < num && !err; i++)
    {
      mse += (*(in + i) - average) * (*(in + i) - average);
    }

  if (!err)
    {
      ret = mse / num;
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_unbiasedsdi
 ****************************************************************************/

int16_t mossdsp_unbiasedsdi(const int16_t *in, unsigned int num)
{
  unsigned int i;
  float average;
  float mse = 0.0f;
  int err = 0;
  int16_t ret = 0;

  err = ((in != NULL) && (1 < num)) - 1;
  if (!err)
    {
      average = (float)sum_i(in, num) / (float)num;
    }

  for (i = 0; i < num && !err; i++)
    {
      mse += (*(in + i) - average) * (*(in + i) - average);
    }

  if (!err)
    {
      ret = (int16_t) (sqrtf(mse / (num - 1)) + 0.5f);
    }

  return ret;
}

/****************************************************************************
 * name: mossdsp_unbiasedsdf
 ****************************************************************************/

float mossdsp_unbiasedsdf(const float *in, unsigned int num)
{
  unsigned int i;
  float average;
  float mse = 0.0f;
  int err = 0;
  float ret = 0;

  err = ((in != NULL) && (1 < num)) - 1;
  if (!err)
    {
      average = sum_f(in, num) / (float)num;
    }

  for (i = 0; i < num && !err; i++)
    {
      mse += (*(in + i) - average) * (*(in + i) - average);
    }

  if (!err)
    {
      ret = (sqrtf(mse / (float)(num - 1)));
    }

  return ret;
}
