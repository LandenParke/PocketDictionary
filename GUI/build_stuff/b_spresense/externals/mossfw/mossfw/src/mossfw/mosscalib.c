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
#include "mossfw/mossfw_data.h"
#include "mossfw/mosscalib.h"
#include "mossfw/mossdsp.h"
#if defined(MOSSFW_USE_ARMCMSIS_DSP)
#include "dsp/statistics_functions.h"
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: unbiased_sd_v3i
 ****************************************************************************/

static void unbiased_sd_v3i(mossfw_data_v3f_t *out,
                            const mossfw_data_v3s_t *in,
                            unsigned int num,
                            const mossfw_data_v3s_t *average)
{
  int32_t sx = 0;
  int32_t sy = 0;
  int32_t sz = 0;
  unsigned int i;

  for (i = 0; i < num; i++)
    {
      sx += ((in + i)->x - average->x) * ((in + i)->x - average->x);
      sy += ((in + i)->y - average->y) * ((in + i)->y - average->y);
      sz += ((in + i)->z - average->z) * ((in + i)->z - average->z);
    }

  out->x = sqrtf((float)sx / (float)(num - 1));
  out->y = sqrtf((float)sy / (float)(num - 1));
  out->z = sqrtf((float)sz / (float)(num - 1));
}

/****************************************************************************
 * name: unbiased_sd_v3f
 ****************************************************************************/

static void unbiased_sd_v3f(mossfw_data_v3f_t *out,
                            const mossfw_data_v3f_t *in,
                            unsigned int num,
                            const mossfw_data_v3f_t *average)
{
  float sx = 0;
  float sy = 0;
  float sz = 0;
  unsigned int i;

  for (i = 0; i < num; i++)
    {
      sx += ((in + i)->x - average->x) * ((in + i)->x - average->x);
      sy += ((in + i)->y - average->y) * ((in + i)->y - average->y);
      sz += ((in + i)->z - average->z) * ((in + i)->z - average->z);
    }

  out->x = sqrtf(sx / (num - 1));
  out->y = sqrtf(sy / (num - 1));
  out->z = sqrtf(sz / (num - 1));
}

/****************************************************************************
 * name: unbiased_sd_v3ti
 ****************************************************************************/

static void unbiased_sd_v3ti(mossfw_data_v3f_t *out,
                            const mossfw_data_v3ts_t *in,
                            unsigned int num,
                            const mossfw_data_v3s_t *average)
{
  int32_t sx = 0;
  int32_t sy = 0;
  int32_t sz = 0;
  unsigned int i;

  for (i = 0; i < num; i++)
    {
      sx += ((in + i)->x - average->x) * ((in + i)->x - average->x);
      sy += ((in + i)->y - average->y) * ((in + i)->y - average->y);
      sz += ((in + i)->z - average->z) * ((in + i)->z - average->z);
    }

  out->x = sqrtf((float)sx / (float)(num - 1));
  out->y = sqrtf((float)sy / (float)(num - 1));
  out->z = sqrtf((float)sz / (float)(num - 1));
}

/****************************************************************************
 * name: unbiased_sd_v3tf
 ****************************************************************************/

static void unbiased_sd_v3tf(mossfw_data_v3f_t *out,
                            const mossfw_data_v3tf_t *in,
                            unsigned int num,
                            const mossfw_data_v3f_t *average)
{
  float sx = 0;
  float sy = 0;
  float sz = 0;
  unsigned int i;

  for (i = 0; i < num; i++)
    {
      sx += ((in + i)->x - average->x) * ((in + i)->x - average->x);
      sy += ((in + i)->y - average->y) * ((in + i)->y - average->y);
      sz += ((in + i)->z - average->z) * ((in + i)->z - average->z);
    }

  out->x = sqrtf(sx / (num - 1));
  out->y = sqrtf(sy / (num - 1));
  out->z = sqrtf(sz / (num - 1));
}

/****************************************************************************
 * name: unbiased_sd_v3ia
 ****************************************************************************/

static void unbiased_sd_v3ia(mossfw_data_v3f_t *out,
                            const struct vector3ia_s *in,
                            unsigned int num,
                            const mossfw_data_v3s_t *average)
{
  int32_t sx = 0;
  int32_t sy = 0;
  int32_t sz = 0;
  unsigned int i;

  for (i = 0; i < num; i++)
    {
      sx += (*(in->x + i) - average->x) * (*(in->x + i) - average->x);
      sy += (*(in->y + i) - average->y) * (*(in->y + i) - average->y);
      sz += (*(in->z + i) - average->z) * (*(in->z + i) - average->z);
    }

  out->x = sqrtf((float)sx / (float)(num - 1));
  out->y = sqrtf((float)sy / (float)(num - 1));
  out->z = sqrtf((float)sz / (float)(num - 1));
}

/****************************************************************************
 * name: unbiased_sd_v3fa
 ****************************************************************************/

static void unbiased_sd_v3fa(mossfw_data_v3f_t *out,
                            const struct vector3fa_s *in,
                            unsigned int num,
                            const mossfw_data_v3f_t *average)
{
  float sx = 0;
  float sy = 0;
  float sz = 0;
  unsigned int i;

  for (i = 0; i < num; i++)
    {
      sx += (*(in->x + i) - average->x) * (*(in->x + i) - average->x);
      sy += (*(in->y + i) - average->y) * (*(in->y + i) - average->y);
      sz += (*(in->z + i) - average->z) * (*(in->z + i) - average->z);
    }

  out->x = sqrtf(sx / (num - 1));
  out->y = sqrtf(sy / (num - 1));
  out->z = sqrtf(sz / (num - 1));
}

/****************************************************************************
 * name: unbiased_sd_v3tia
 ****************************************************************************/

static void unbiased_sd_v3tia(mossfw_data_v3f_t *out,
                              const struct vector3tia_s *in,
                              unsigned int num,
                              const mossfw_data_v3s_t *average)
{
  int32_t sx = 0;
  int32_t sy = 0;
  int32_t sz = 0;
  unsigned int i;

  for (i = 0; i < num; i++)
    {
      sx += (*(in->x + i) - average->x) * (*(in->x + i) - average->x);
      sy += (*(in->y + i) - average->y) * (*(in->y + i) - average->y);
      sz += (*(in->z + i) - average->z) * (*(in->z + i) - average->z);
    }

  out->x = sqrtf((float)sx / (float)(num - 1));
  out->y = sqrtf((float)sy / (float)(num - 1));
  out->z = sqrtf((float)sz / (float)(num - 1));
}

/****************************************************************************
 * name: unbiased_sd_v3tfa
 ****************************************************************************/

static void unbiased_sd_v3tfa(mossfw_data_v3f_t *out,
                              const struct vector3tfa_s *in,
                              unsigned int num,
                              const mossfw_data_v3f_t *average)
{
  float sx = 0;
  float sy = 0;
  float sz = 0;
  unsigned int i;

  for (i = 0; i < num; i++)
    {
      sx += (*(in->x + i) - average->x) * (*(in->x + i) - average->x);
      sy += (*(in->y + i) - average->y) * (*(in->y + i) - average->y);
      sz += (*(in->z + i) - average->z) * (*(in->z + i) - average->z);
    }

  out->x = sqrtf(sx / (num - 1));
  out->y = sqrtf(sy / (num - 1));
  out->z = sqrtf(sz / (num - 1));
}

/****************************************************************************
 * name: gyrbias_availablei
 ****************************************************************************/

static int gyrbias_availablei(mossfw_data_v3s_t *average,
                              mossfw_data_v3f_t *usd,
                              const struct mosscalib_gyrbias_param_s *param)
{
  int16_t ua;
  float uusd;
  int ret;

  average->x = average->x < 0 ? -average->x : average->x;
  average->y = average->y < 0 ? -average->y : average->y;
  average->z = average->z < 0 ? -average->z : average->z;
  ua = param->average.i < 0 ? -param->average.i : param->average.i;
  uusd = fabs(param->usd);
  ret = !(ua < average->x);
  ret = !(ua < average->y) && ret;
  ret = !(ua < average->z) && ret;
  ret = !(uusd < usd->x) && ret;
  ret = !(uusd < usd->y) && ret;
  ret = !(uusd < usd->z) && ret;
  return ret;
}

/****************************************************************************
 * name: gyrbias_availablef
 ****************************************************************************/

static int gyrbias_availablef(mossfw_data_v3f_t *average,
                              mossfw_data_v3f_t *usd,
                              const struct mosscalib_gyrbias_param_s *param)
{
  float ua;
  float uusd;
  int ret;

  ua = fabsf(param->average.f);
  uusd = fabsf(param->usd);
  ret = !(ua < fabsf(average->x));
  ret = !(ua < fabsf(average->y)) && ret;
  ret = !(ua < fabsf(average->z)) && ret;
  ret = !(uusd < usd->x) && ret;
  ret = !(uusd < usd->y) && ret;
  ret = !(uusd < usd->z) && ret;
  return ret;
}

/****************************************************************************
 * name: gyrbias_availablev3i
 ****************************************************************************/

static int gyrbias_availablev3i(const mossfw_data_v3s_t *in,
                                unsigned int offset,
                                const struct
                                mosscalib_gyrbias_param_s
                                *param)
{
  int ret = 0;
  int err;
  mossfw_data_v3s_t average =
    {
      .x = 0, .y = 0, .z = 0
    };

  mossfw_data_v3f_t usd;

  err = mossdsp_averagev3i(&average, in + offset, param->num);
  if (err == 0)
    {
      unbiased_sd_v3i(&usd, in + offset, param->num, &average);
      ret = gyrbias_availablei(&average, &usd, param);
    }

  return ret;
}

/****************************************************************************
 * name: gyrbias_availablev3f
 ****************************************************************************/

static int gyrbias_availablev3f(const mossfw_data_v3f_t *in,
                                unsigned int offset,
                                const struct
                                mosscalib_gyrbias_param_s
                                *param)
{
  int ret = 0;
  int err;
  mossfw_data_v3f_t average =
    {
      .x = 0.0f, .y = 0.0f, .z = 0.0f
    };

  mossfw_data_v3f_t usd;

  err = mossdsp_averagev3f(&average, in + offset, param->num);
  if (err == 0)
    {
      unbiased_sd_v3f(&usd, in + offset, param->num, &average);
      ret = gyrbias_availablef(&average, &usd, param);
    }

  return ret;
}

/****************************************************************************
 * name: gyrbias_availablev3ti
 ****************************************************************************/

static int gyrbias_availablev3ti(const mossfw_data_v3ts_t *in,
                                unsigned int offset,
                                const struct
                                mosscalib_gyrbias_param_s
                                *param)
{
  int ret = 0;
  int err;
  mossfw_data_v3s_t average =
    {
      .x = 0, .y = 0, .z = 0
    };

  mossfw_data_v3f_t usd;

  err = mossdsp_averagev3ti(&average, in + offset, param->num);
  if (err == 0)
    {
      unbiased_sd_v3ti(&usd, in + offset, param->num, &average);
      ret = gyrbias_availablei(&average, &usd, param);
    }

  return ret;
}

/****************************************************************************
 * name: gyrbias_availablev3tf
 ****************************************************************************/

static int gyrbias_availablev3tf(const mossfw_data_v3tf_t *in,
                                unsigned int offset,
                                const struct
                                mosscalib_gyrbias_param_s
                                *param)
{
  int ret = 0;
  int err;
  mossfw_data_v3f_t average =
    {
      .x = 0.0f, .y = 0.0f, .z = 0.0f
    };

  mossfw_data_v3f_t usd;

  err = mossdsp_averagev3tf(&average, in + offset, param->num);
  if (err == 0)
    {
      unbiased_sd_v3tf(&usd, in + offset, param->num, &average);
      ret = gyrbias_availablef(&average, &usd, param);
    }

  return ret;
}

/****************************************************************************
 * name: gyrbias_availablev3ia
 ****************************************************************************/

static int gyrbias_availablev3ia(const struct vector3ia_s *in,
  unsigned int offset,
  const struct
  mosscalib_gyrbias_param_s
  *param)
{
  int ret = 0;
  int err;
  mossfw_data_v3s_t average =
    {
      .x = 0, .y = 0, .z = 0
    };

  mossfw_data_v3f_t usd;
  struct vector3ia_s inoffset;

  inoffset.x = in->x + offset;
  inoffset.y = in->y + offset;
  inoffset.z = in->z + offset;
  err = mossdsp_averagev3ia(&average, &inoffset, param->num);
  if (err == 0)
    {
      unbiased_sd_v3ia(&usd, &inoffset, param->num, &average);
      ret = gyrbias_availablei(&average, &usd, param);
    }

  return ret;
}

/****************************************************************************
 * name: gyrbias_availablev3fa
 ****************************************************************************/

static int gyrbias_availablev3fa(const struct vector3fa_s *in,
                                  unsigned int offset,
                                  const struct
                                  mosscalib_gyrbias_param_s
                                  *param)
{
  int ret = 0;
  int err;
  mossfw_data_v3f_t average =
    {
      .x = 0.0f, .y = 0.0f, .z = 0.0f
    };

  mossfw_data_v3f_t usd;
  struct vector3fa_s inoffset;

  inoffset.x = in->x + offset;
  inoffset.y = in->y + offset;
  inoffset.z = in->z + offset;
  err = mossdsp_averagev3fa(&average, &inoffset, param->num);
  if (err == 0)
    {
      unbiased_sd_v3fa(&usd, &inoffset, param->num, &average);
      ret = gyrbias_availablef(&average, &usd, param);
    }

  return ret;
}

/****************************************************************************
 * name: gyrbias_availablev3tia
 ****************************************************************************/

static int gyrbias_availablev3tia(const struct vector3tia_s *in,
                                  unsigned int offset,
                                  const struct
                                  mosscalib_gyrbias_param_s
                                  *param)
{
  int ret = 0;
  int err;
  mossfw_data_v3s_t average =
    {
      .x = 0, .y = 0, .z = 0
    };

  mossfw_data_v3f_t usd;
  struct vector3tia_s inoffset;

  inoffset.x = in->x + offset;
  inoffset.y = in->y + offset;
  inoffset.z = in->z + offset;
  inoffset.t = in->t + offset;
  err = mossdsp_averagev3tia(&average, &inoffset, param->num);
  if (err == 0)
    {
      unbiased_sd_v3tia(&usd, &inoffset, param->num, &average);
      ret = gyrbias_availablei(&average, &usd, param);
    }

  return ret;
}

/****************************************************************************
 * name: gyrbias_availablev3tfa
 ****************************************************************************/

static int gyrbias_availablev3tfa(const struct vector3tfa_s *in,
                                  unsigned int offset,
                                  const struct
                                  mosscalib_gyrbias_param_s
                                  *param)
{
  int ret = 0;
  int err;
  mossfw_data_v3f_t average =
    {
      .x = 0.0f, .y = 0.0f, .z = 0.0f
    };

  mossfw_data_v3f_t usd;
  struct vector3tfa_s inoffset;

  inoffset.x = in->x + offset;
  inoffset.y = in->y + offset;
  inoffset.z = in->z + offset;
  inoffset.t = in->t + offset;
  err = mossdsp_averagev3tfa(&average, &inoffset, param->num);
  if (err == 0)
    {
      unbiased_sd_v3tfa(&usd, &inoffset, param->num, &average);
      ret = gyrbias_availablef(&average, &usd, param);
    }

  return ret;
}

/****************************************************************************
 * name: adjustscalemisalign
 ****************************************************************************/

static mossfw_data_v3f_t adjustscalemisalign(float inx, float iny, float inz,
  const struct mosscalib_adjust_param_s *param)
{
  mossfw_data_v3f_t vec;
  struct sqmatrix3f_s mis;
  mossfw_data_v3f_t ret;

  vec.x = inx * param->scalefactor.x.x;
  vec.y = iny * param->scalefactor.y.y;
  vec.z = inz * param->scalefactor.z.z;
  mis = param->misalignment;
  ret.x = vec.x * mis.x.x + vec.y * mis.x.y + vec.z * mis.x.z;
  ret.y = vec.x * mis.y.x + vec.y * mis.y.y + vec.z * mis.y.z;
  ret.z = vec.x * mis.z.x + vec.y * mis.z.y + vec.z * mis.z.z;
  return ret;
}

/****************************************************************************
 * name: adjustf
 ****************************************************************************/

static mossfw_data_v3f_t adjustf(const float inx, const float iny,
    const float inz, const struct mosscalib_adjust_param_s *param)
{
  mossfw_data_v3f_t ret;
  float vx;
  float vy;
  float vz;

  vx = inx - param->bias.f.x;
  vy = iny - param->bias.f.y;
  vz = inz - param->bias.f.z;
  ret = adjustscalemisalign(vx, vy, vz, param);
  return ret;
}

/****************************************************************************
 * name: adjusti
 ****************************************************************************/

static mossfw_data_v3s_t adjusti(const int16_t inx, const int16_t iny,
    const int16_t inz, const struct mosscalib_adjust_param_s *param)
{
  mossfw_data_v3f_t vec;
  mossfw_data_v3s_t ret;
  float vx;
  float vy;
  float vz;

  vx = inx - param->bias.i.x;
  vy = iny - param->bias.i.y;
  vz = inz - param->bias.i.z;
  vec = adjustscalemisalign(vx, vy, vz, param);
  ret.x = vec.x + (vec.x < 0.0f ? -0.5f : 0.5f);
  ret.y = vec.y + (vec.y < 0.0f ? -0.5f : 0.5f);
  ret.z = vec.z + (vec.z < 0.0f ? -0.5f : 0.5f);
  return ret;
}

/****************************************************************************
 * name: mosscalib_gyrbiasv3i
 ****************************************************************************/

int mosscalib_gyrbiasv3i(mossfw_data_v3s_t *out,
                        const mossfw_data_v3s_t *in,
                        unsigned int num,
                        const struct mosscalib_gyrbias_param_s *param)
{
  int32_t sx = 0;
  int32_t sy = 0;
  int32_t sz = 0;
  int err;
  unsigned int i;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  for (i = 0; !err && i + param->num <= num; i += param->num)
    {
      err = !gyrbias_availablev3i(in, i, param);
    }

  for (i = 0; i < num && !err; i++)
    {
      sx += (in + i)->x;
      sy += (in + i)->y;
      sz += (in + i)->z;
    }

  if (!err)
    {
      out->x = (int16_t) (sx / (int32_t) num);
      out->y = (int16_t) (sy / (int32_t) num);
      out->z = (int16_t) (sz / (int32_t) num);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gyrbiasv3f
 ****************************************************************************/

int mosscalib_gyrbiasv3f(mossfw_data_v3f_t *out,
                        const mossfw_data_v3f_t *in,
                        unsigned int num,
                        const struct mosscalib_gyrbias_param_s *param)
{
  float sx = 0;
  float sy = 0;
  float sz = 0;
  int err;
  unsigned int i;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  for (i = 0; !err && i + param->num <= num; i += param->num)
    {
      err = !gyrbias_availablev3f(in, i, param);
    }

  for (i = 0; i < num && !err; i++)
    {
      sx += (in + i)->x;
      sy += (in + i)->y;
      sz += (in + i)->z;
    }

  if (!err)
    {
      out->x = sx / num;
      out->y = sy / num;
      out->z = sz / num;
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gyrbiasv3ti
 ****************************************************************************/

int mosscalib_gyrbiasv3ti(mossfw_data_v3s_t *out,
                          const mossfw_data_v3ts_t *in,
                          unsigned int num,
                          const struct mosscalib_gyrbias_param_s *param)
{
  int32_t sx = 0;
  int32_t sy = 0;
  int32_t sz = 0;
  int err;
  unsigned int i;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  for (i = 0; !err && i + param->num <= num; i += param->num)
    {
      err = !gyrbias_availablev3ti(in, i, param);
    }

  for (i = 0; i < num && !err; i++)
    {
      sx += (in + i)->x;
      sy += (in + i)->y;
      sz += (in + i)->z;
    }

  if (!err)
    {
      out->x = (int16_t) (sx / (int32_t) num);
      out->y = (int16_t) (sy / (int32_t) num);
      out->z = (int16_t) (sz / (int32_t) num);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gyrbiasv3tf
 ****************************************************************************/

int mosscalib_gyrbiasv3tf(mossfw_data_v3f_t *out,
                          const mossfw_data_v3tf_t *in,
                          unsigned int num,
                          const struct mosscalib_gyrbias_param_s *param)
{
  float sx = 0;
  float sy = 0;
  float sz = 0;
  int err;
  unsigned int i;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  for (i = 0; !err && i + param->num <= num; i += param->num)
    {
      err = !gyrbias_availablev3tf(in, i, param);
    }

  for (i = 0; i < num && !err; i++)
    {
      sx += (in + i)->x;
      sy += (in + i)->y;
      sz += (in + i)->z;
    }

  if (!err)
    {
      out->x = sx / num;
      out->y = sy / num;
      out->z = sz / num;
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gyrbiasv3ia
 ****************************************************************************/

int mosscalib_gyrbiasv3ia(mossfw_data_v3s_t *out,
                          const struct vector3ia_s *in,
                          unsigned int num,
                          const struct mosscalib_gyrbias_param_s *param)
{
  int32_t sx = 0;
  int32_t sy = 0;
  int32_t sz = 0;
  int err;
  unsigned int i;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  err = err || in->x == NULL || in->y == NULL || in->z == NULL;
  for (i = 0; !err && i + param->num <= num; i += param->num)
    {
      err = !gyrbias_availablev3ia(in, i, param);
    }

  for (i = 0; i < num && !err; i++)
    {
      sx += *(in->x + i);
      sy += *(in->y + i);
      sz += *(in->z + i);
    }

  if (!err)
    {
      out->x = (int16_t) (sx / (int32_t) num);
      out->y = (int16_t) (sy / (int32_t) num);
      out->z = (int16_t) (sz / (int32_t) num);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gyrbiasv3fa
 ****************************************************************************/

int mosscalib_gyrbiasv3fa(mossfw_data_v3f_t *out,
                          const struct vector3fa_s *in,
                          unsigned int num,
                          const struct mosscalib_gyrbias_param_s *param)
{
  float sx = 0;
  float sy = 0;
  float sz = 0;
  int err;
  unsigned int i;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  err = err || in->x == NULL || in->y == NULL || in->z == NULL;
  for (i = 0; !err && i + param->num <= num; i += param->num)
    {
      err = !gyrbias_availablev3fa(in, i, param);
    }

  for (i = 0; i < num && !err; i++)
    {
      sx += *(in->x + i);
      sy += *(in->y + i);
      sz += *(in->z + i);
    }

  if (!err)
    {
      out->x = sx / num;
      out->y = sy / num;
      out->z = sz / num;
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gyrbiasv3tia
 ****************************************************************************/

int mosscalib_gyrbiasv3tia(mossfw_data_v3s_t *out,
                            const struct vector3tia_s *in,
                            unsigned int num,
                            const struct mosscalib_gyrbias_param_s *param)
{
  int32_t sx = 0;
  int32_t sy = 0;
  int32_t sz = 0;
  int err;
  unsigned int i;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  err = err || in->x == NULL || in->y == NULL ||
            in->z == NULL || in->t == NULL;
  for (i = 0; !err && i + param->num <= num; i += param->num)
    {
      err = !gyrbias_availablev3tia(in, i, param);
    }

  for (i = 0; i < num && !err; i++)
    {
      sx += *(in->x + i);
      sy += *(in->y + i);
      sz += *(in->z + i);
    }

  if (!err)
    {
      out->x = (int16_t) (sx / (int32_t) num);
      out->y = (int16_t) (sy / (int32_t) num);
      out->z = (int16_t) (sz / (int32_t) num);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gyrbiasv3tfa
 ****************************************************************************/

int mosscalib_gyrbiasv3tfa(mossfw_data_v3f_t *out,
                            const struct vector3tfa_s *in,
                            unsigned int num,
                            const struct mosscalib_gyrbias_param_s *param)
{
  float sx = 0;
  float sy = 0;
  float sz = 0;
  int err;
  unsigned int i;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  err = err || in->x == NULL || in->y == NULL ||
          in->z == NULL || in->t == NULL;
  for (i = 0; !err && i + param->num <= num; i += param->num)
    {
      err = !gyrbias_availablev3tfa(in, i, param);
    }

  for (i = 0; i < num && !err; i++)
    {
      sx += *(in->x + i);
      sy += *(in->y + i);
      sz += *(in->z + i);
    }

  if (!err)
    {
      out->x = sx / num;
      out->y = sy / num;
      out->z = sz / num;
    }

  return !err - 1;
}

/****************************************************************************
 * name: gravityaccf
 ****************************************************************************/

static void gravityaccf(mossfw_data_qf_t *out,
                        const mossfw_data_v3f_t *acc,
                        const struct mosscalib_gravity_param_s *param)
{
  mossfw_data_qf_t qz;
  mossfw_data_qf_t q0;
  mossfw_data_qf_t q1;
  mossfw_data_v3f_t yaxis;
  mossfw_data_v3f_t yd;
  float theta;
  float phi;
  float ax;
  float ay;
  float az;
  float aa;

  ax =
    acc->x * (float)param->haxis.x +
    acc->y * (float)param->haxis.y + acc->z * (float)param->haxis.z;
  az =
    acc->x * (float)param->vaxis.x +
    acc->y * (float)param->vaxis.y + acc->z * (float)param->vaxis.z;
  aa =
    acc->x * acc->x + acc->y * acc->y +
    acc->z * acc->z;
#ifndef STELVIO
  theta = acosf(az / sqrtf(aa));
  qz.w = sqrtf(2.0f) / 2.0f;
  qz.x = (float)param->vaxis.x * (sqrtf(2.0f) / 2.0f);
  qz.y = (float)param->vaxis.y * (sqrtf(2.0f) / 2.0f);
  qz.z = (float)param->vaxis.z * (sqrtf(2.0f) / 2.0f);
#else
  theta = acos(az / sqrtf(aa));
  qz.w = sqrt(2.0f) / 2.0f;
  qz.x = (float)param->vaxis.x * (sqrt(2.0f) / 2.0f);
  qz.y = (float)param->vaxis.y * (sqrt(2.0f) / 2.0f);
  qz.z = (float)param->vaxis.z * (sqrt(2.0f) / 2.0f);
#endif
  (void)mossdsp_transformaxisqv3f(&yaxis, &(param->haxis), 1, &qz);
  ay = acc->x * yaxis.x + acc->y * yaxis.y + acc->z * yaxis.z;
#ifndef STELVIO
  phi = (ay > 0.0f ? 1.0f : -1.0f) * acos(ax / (sqrtf(ax * ax + ay * ay)));
  q0.w = cosf(phi / 2.0f);
  q0.x = param->vaxis.x * sinf(phi / 2.0f);
  q0.y = param->vaxis.y * sinf(phi / 2.0f);
  q0.z = param->vaxis.z * sinf(phi / 2.0f);
#else
  phi = (ay > 0.0f ? 1.0f : -1.0f) * acos(ax / (sqrt(ax * ax + ay * ay)));
  q0.w = cos(phi / 2.0f);
  q0.x = param->vaxis.x * sin(phi / 2.0f);
  q0.y = param->vaxis.y * sin(phi / 2.0f);
  q0.z = param->vaxis.z * sin(phi / 2.0f);
#endif
  (void)mossdsp_transformaxisqv3f(&yd, &yaxis, 1, &q0);
#ifndef STELVIO
  q1.w = cosf(theta / 2.0f);
  q1.x = yd.x * sinf(theta / 2.0f);
  q1.y = yd.y * sinf(theta / 2.0f);
  q1.z = yd.z * sinf(theta / 2.0f);
#else
  q1.w = cos(theta / 2.0);
  q1.x = yd.x * sin(theta / 2.0);
  q1.y = yd.y * sin(theta / 2.0);
  q1.z = yd.z * sin(theta / 2.0);
#endif
  (void)mossdsp_multiplyqf(out, &q1, &q0, 1);
  out->x = -out->x;
  out->y = -out->y;
  out->z = -out->z;
}

/****************************************************************************
 * name: gravityacci
 ****************************************************************************/

static void gravityacci(mossfw_data_qf_t *out,
                        const mossfw_data_v3s_t *acc,
                        const struct mosscalib_gravity_param_s *param)
{
  mossfw_data_v3f_t facc;

  facc.x = acc->x;
  facc.y = acc->y;
  facc.z = acc->z;
  gravityaccf(out, &facc, param);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mosscalib_gravityv3i
 ****************************************************************************/

int mosscalib_gravityv3i(mossfw_data_qf_t *out,
                        const mossfw_data_v3s_t *in,
                        unsigned int num,
                        const struct mosscalib_gravity_param_s *param)
{
  mossfw_data_v3s_t acc;
  int err;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  if (!err)
    {
      (void)mossdsp_averagev3i(&acc, in, num);
      gravityacci(out, &acc, param);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gravityv3f
 ****************************************************************************/

int mosscalib_gravityv3f(mossfw_data_qf_t *out,
                        const mossfw_data_v3f_t *in,
                        unsigned int num,
                        const struct mosscalib_gravity_param_s *param)
{
  mossfw_data_v3f_t acc;
  int err;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  if (!err)
    {
      (void)mossdsp_averagev3f(&acc, in, num);
      gravityaccf(out, &acc, param);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gravityv3ti
 ****************************************************************************/

int mosscalib_gravityv3ti(mossfw_data_qf_t *out,
                          const mossfw_data_v3ts_t *in,
                          unsigned int num,
                          const struct mosscalib_gravity_param_s *param)
{
  mossfw_data_v3s_t acc;
  int err;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  if (!err)
    {
      (void)mossdsp_averagev3ti(&acc, in, num);
      gravityacci(out, &acc, param);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gravityv3tf
 ****************************************************************************/

int mosscalib_gravityv3tf(mossfw_data_qf_t *out,
                          const mossfw_data_v3tf_t *in,
                          unsigned int num,
                          const struct mosscalib_gravity_param_s *param)
{
  mossfw_data_v3f_t acc;
  int err;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  if (!err)
    {
      (void)mossdsp_averagev3tf(&acc, in, num);
      gravityaccf(out, &acc, param);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gravityv3ia
 ****************************************************************************/

int mosscalib_gravityv3ia(mossfw_data_qf_t *out,
                          const struct vector3ia_s *in,
                          unsigned int num,
                          const struct mosscalib_gravity_param_s *param)
{
  mossfw_data_v3s_t acc;
  int err;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  err = err || in->x == NULL || in->y == NULL || in->z == NULL;
  if (!err)
    {
      (void)mossdsp_averagev3ia(&acc, in, num);
      gravityacci(out, &acc, param);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gravityv3fa
 ****************************************************************************/

int mosscalib_gravityv3fa(mossfw_data_qf_t *out,
                          const struct vector3fa_s *in,
                          unsigned int num,
                          const struct mosscalib_gravity_param_s *param)
{
  mossfw_data_v3f_t acc;
  int err;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  err = err || in->x == NULL || in->y == NULL || in->z == NULL;
  if (!err)
    {
      (void)mossdsp_averagev3fa(&acc, in, num);
      gravityaccf(out, &acc, param);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gravityv3tia
 ****************************************************************************/

int mosscalib_gravityv3tia(mossfw_data_qf_t *out,
                            const struct vector3tia_s *in,
                            unsigned int num,
                            const struct mosscalib_gravity_param_s *param)
{
  mossfw_data_v3s_t acc;
  int err;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  err = err || in->x == NULL || in->y == NULL ||
          in->z == NULL || in->t == NULL;
  if (!err)
    {
      (void)mossdsp_averagev3tia(&acc, in, num);
      gravityacci(out, &acc, param);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_gravityv3tfa
 ****************************************************************************/

int mosscalib_gravityv3tfa(mossfw_data_qf_t *out,
                            const struct vector3tfa_s *in,
                            unsigned int num,
                            const struct mosscalib_gravity_param_s *param)
{
  mossfw_data_v3f_t acc;
  int err;

  err = out == NULL || in == NULL || num < 1 || param == NULL;
  err = err || in->x == NULL || in->y == NULL ||
          in->z == NULL || in->t == NULL;
  if (!err)
    {
      (void)mossdsp_averagev3tfa(&acc, in, num);
      gravityaccf(out, &acc, param);
    }

  return !err - 1;
}

/****************************************************************************
 * name: mosscalib_adjustv3i
 ****************************************************************************/

int mosscalib_adjustv3i(mossfw_data_v3s_t *out,
                        const mossfw_data_v3s_t *in,
                        unsigned int num, int16_t temperature,
                        const struct mosscalib_adjust_param_s *param)
{
  int err;
  unsigned int i;

  (void)temperature;
  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  for (i = 0; i < num && !err; i++)
    {
      *(out + i) = adjusti((in + i)->x, (in + i)->y, (in + i)->z, param);
    }

  return err;
}

/****************************************************************************
 * name: mosscalib_adjustv3f
 ****************************************************************************/

int mosscalib_adjustv3f(mossfw_data_v3f_t *out,
                        const mossfw_data_v3f_t *in,
                        unsigned int num, float temperature,
                        const struct mosscalib_adjust_param_s *param)
{
  int err;
  unsigned int i;

  (void)temperature;
  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  for (i = 0; i < num && !err; i++)
    {
      *(out + i) = adjustf((in + i)->x, (in + i)->y, (in + i)->z, param);
    }

  return err;
}

/****************************************************************************
 * name: mosscalib_adjustv3ti
 ****************************************************************************/

int mosscalib_adjustv3ti(mossfw_data_v3ts_t *out,
                        const mossfw_data_v3ts_t *in,
                        unsigned int num, int16_t temperature,
                        const struct mosscalib_adjust_param_s *param)
{
  int err;
  unsigned int i;
  mossfw_data_v3s_t vec;

  (void)temperature;
  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  for (i = 0; i < num && !err; i++)
    {
      vec = adjusti((in + i)->x, (in + i)->y, (in + i)->z, param);
      (out + i)->x = vec.x;
      (out + i)->y = vec.y;
      (out + i)->z = vec.z;
      (out + i)->t = (in + i)->t;
    }

  return err;
}

/****************************************************************************
 * name: mosscalib_adjustv3tf
 ****************************************************************************/

int mosscalib_adjustv3tf(mossfw_data_v3tf_t *out,
                        const mossfw_data_v3tf_t *in,
                        unsigned int num, float temperature,
                        const struct mosscalib_adjust_param_s *param)
{
  int err;
  unsigned int i;
  mossfw_data_v3f_t vec;

  (void)temperature;
  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  for (i = 0; i < num && !err; i++)
    {
      vec = adjustf((in + i)->x, (in + i)->y, (in + i)->z, param);
      (out + i)->x = vec.x;
      (out + i)->y = vec.y;
      (out + i)->z = vec.z;
      (out + i)->t = (in + i)->t;
    }

  return err;
}

/****************************************************************************
 * name: mosscalib_adjustv3ia
 ****************************************************************************/

int mosscalib_adjustv3ia(struct vector3ia_s *out,
                          const struct vector3ia_s *in,
                          unsigned int num, int16_t temperature,
                          const struct mosscalib_adjust_param_s *param)
{
  int err;
  unsigned int i;
  mossfw_data_v3s_t vec;

  (void)temperature;
  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL && out->z != NULL) - 1;
  err = (!err && in->x != NULL && in->y != NULL && in->z != NULL) - 1;
  for (i = 0; i < num && !err; i++)
    {
      vec = adjusti(*(in->x + i), *(in->y + i), *(in->z + i), param);
      *(out->x + i) = vec.x;
      *(out->y + i) = vec.y;
      *(out->z + i) = vec.z;
    }

  return err;
}

/****************************************************************************
 * name: mosscalib_adjustv3fa
 ****************************************************************************/

int mosscalib_adjustv3fa(struct vector3fa_s *out,
                          const struct vector3fa_s *in,
                          unsigned int num, float temperature,
                          const struct mosscalib_adjust_param_s *param)
{
  int err;
  unsigned int i;
  mossfw_data_v3f_t vec;

  (void)temperature;
  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL && out->z != NULL) - 1;
  err = (!err && in->x != NULL && in->y != NULL && in->z != NULL) - 1;
  for (i = 0; i < num && !err; i++)
    {
      vec = adjustf(*(in->x + i), *(in->y + i), *(in->z + i), param);
      *(out->x + i) = vec.x;
      *(out->y + i) = vec.y;
      *(out->z + i) = vec.z;
    }

  return err;
}

/****************************************************************************
 * name: mosscalib_adjustv3tia
 ****************************************************************************/

int mosscalib_adjustv3tia(struct vector3tia_s *out,
                          const struct vector3tia_s *in,
                          unsigned int num, int16_t temperature,
                          const struct mosscalib_adjust_param_s *param)
{
  int err;
  unsigned int i;
  mossfw_data_v3s_t vec;

  (void)temperature;
  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL &&
          out->z != NULL && out->t != NULL) - 1;
  err = (!err && in->x != NULL && in->y != NULL &&
          in->z != NULL && in->t != NULL) - 1;
  for (i = 0; i < num && !err; i++)
    {
      vec = adjusti(*(in->x + i), *(in->y + i), *(in->z + i), param);
      *(out->x + i) = vec.x;
      *(out->y + i) = vec.y;
      *(out->z + i) = vec.z;
      *(out->t + i) = *(in->t + i);
    }

  return err;
}

/****************************************************************************
 * name: mosscalib_adjustv3tfa
 ****************************************************************************/

int mosscalib_adjustv3tfa(struct vector3tfa_s *out,
                          const struct vector3tfa_s *in,
                          unsigned int num, float temperature,
                          const struct mosscalib_adjust_param_s *param)
{
  int err;
  unsigned int i;
  mossfw_data_v3f_t vec;

  (void)temperature;
  err = (out != NULL && in != NULL && 0 < num && param != NULL) - 1;
  err = (!err && out->x != NULL && out->y != NULL &&
          out->z != NULL && out->t != NULL) - 1;
  err = (!err && in->x != NULL && in->y != NULL &&
          in->z != NULL && in->t != NULL) - 1;
  for (i = 0; i < num && !err; i++)
    {
      vec = adjustf(*(in->x + i), *(in->y + i), *(in->z + i), param);
      *(out->x + i) = vec.x;
      *(out->y + i) = vec.y;
      *(out->z + i) = vec.z;
      *(out->t + i) = *(in->t + i);
    }

  return err;
}
