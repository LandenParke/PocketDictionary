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
#include <math.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_data.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifndef NULL
#  define NULL    (0)
#endif

#ifndef TRUE
#  define TRUE    (1)
#endif

#ifndef FALSE
#  define FALSE    (0)
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: transformqanglesf_element
 ****************************************************************************/

static void transformqanglesf_element(mossfw_data_v3f_t * out,
                                      const mossfw_data_qf_t * in)
{
  float x = atan2f(2.0f * (in->y * in->z + in->w * in->x),
                   1.0f - 2.0f * (in->x * in->x + in->y * in->y));
  float y = -asinf(2.0f * (in->x * in->z - in->w * in->y));
  float z = atan2f(2.0f * (in->x * in->y + in->w * in->z),
                   1.0f - 2.0f * (in->y * in->y + in->z * in->z));
  out->x = x;
  out->y = y;
  out->z = z;
}

/****************************************************************************
 * name: transformqanglestf_element
 ****************************************************************************/

static void transformqanglestf_element(mossfw_data_v3tf_t * out,
                                       const mossfw_data_qtf_t * in)
{
  float x = atan2f(2.0f * (in->y * in->z + in->w * in->x),
                   1.0f - 2.0f * (in->x * in->x + in->y * in->y));
  float y = -asinf(2.0f * (in->x * in->z - in->w * in->y));
  float z = atan2f(2.0f * (in->x * in->y + in->w * in->z),
                   1.0f - 2.0f * (in->y * in->y + in->z * in->z));
  out->x = x;
  out->y = y;
  out->z = z;
  out->t = in->t;
}

/****************************************************************************
 * name: transformanglesf_element
 ****************************************************************************/

static void transformanglesf_element(mossfw_data_qf_t * out,
                                     const mossfw_data_v3f_t * in)
{
  float w =
    cosf(in->x / 2) * cosf(in->y / 2) * cosf(in->z / 2) +
    sinf(in->x / 2) * sinf(in->y / 2) * sinf(in->z / 2);
  float x =
    sinf(in->x / 2) * cosf(in->y / 2) * cosf(in->z / 2) -
    cosf(in->x / 2) * sinf(in->y / 2) * sinf(in->z / 2);
  float y =
    sinf(in->x / 2) * cosf(in->y / 2) * sinf(in->z / 2) +
    cosf(in->x / 2) * sinf(in->y / 2) * cosf(in->z / 2);
  float z =
    cosf(in->x / 2) * cosf(in->y / 2) * sinf(in->z / 2) -
    sinf(in->x / 2) * sinf(in->y / 2) * cosf(in->z / 2);
  out->w = w;
  out->x = x;
  out->y = y;
  out->z = z;
}

/****************************************************************************
 * name: transformanglestf_element
 ****************************************************************************/

static void transformanglestf_element(mossfw_data_qtf_t * out,
                                      const mossfw_data_v3tf_t * in)
{
  float w =
    cosf(in->x / 2) * cosf(in->y / 2) * cosf(in->z / 2) +
    sinf(in->x / 2) * sinf(in->y / 2) * sinf(in->z / 2);
  float x =
    sinf(in->x / 2) * cosf(in->y / 2) * cosf(in->z / 2) -
    cosf(in->x / 2) * sinf(in->y / 2) * sinf(in->z / 2);
  float y =
    sinf(in->x / 2) * cosf(in->y / 2) * sinf(in->z / 2) +
    cosf(in->x / 2) * sinf(in->y / 2) * cosf(in->z / 2);
  float z =
    cosf(in->x / 2) * cosf(in->y / 2) * sinf(in->z / 2) -
    sinf(in->x / 2) * sinf(in->y / 2) * cosf(in->z / 2);
  out->w = w;
  out->x = x;
  out->y = y;
  out->z = z;
  out->t = in->t;
}

/****************************************************************************
 * name: transformqazimuthf_element
 ****************************************************************************/

static void transformqazimuthf_element(mossfw_data_v3f_t * out,
                                       const mossfw_data_qf_t * in)
{
  float a12 = 2.0f * (in->x * in->y + in->w * in->z);
  float a22 = in->w * in->w - in->x * in->x + in->y * in->y - in->z * in->z;
  float a31 = 2.0f * (in->x * in->z + in->w * in->y);
  float a32 = 2.0f * (in->y * in->z - in->w * in->x);
  float a33 = in->w * in->w - in->x * in->x - in->y * in->y + in->z * in->z;
  float sgn = a33 < 0.0f ? -1.0f : 1.0f;

  out->x = atanf(a12 / a22);
  out->y = atanf(-a32 / (sgn * sqrtf(a12 * a12 + a22 * a22)));
  out->z = asinf(-a31);
}

/****************************************************************************
 * name: transformqazimuthtf_element
 ****************************************************************************/

static void transformqazimuthtf_element(mossfw_data_v3tf_t * out,
                                        const mossfw_data_qtf_t * in)
{
  float a12 = 2.0f * (in->x * in->y + in->w * in->z);
  float a22 = in->w * in->w - in->x * in->x + in->y * in->y - in->z * in->z;
  float a31 = 2.0f * (in->x * in->z + in->w * in->y);
  float a32 = 2.0f * (in->y * in->z - in->w * in->x);
  float a33 = in->w * in->w - in->x * in->x - in->y * in->y + in->z * in->z;
  float sgn = a33 < 0.0f ? -1.0f : 1.0f;

  out->x = atanf(a12 / a22);
  out->y = atanf(-a32 / (sgn * sqrtf(a12 * a12 + a22 * a22)));
  out->z = asinf(-a31);
  out->t = in->t;
}

/****************************************************************************
 * name: mossdsp_transformqanglesf
 ****************************************************************************/

int mossdsp_transformqanglesf(mossfw_data_v3f_t * out,
                              const mossfw_data_qf_t * in,
                              unsigned int num)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      transformqanglesf_element(&out[i], &in[i]);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformqanglestf
 ****************************************************************************/

int mossdsp_transformqanglestf(mossfw_data_v3tf_t * out,
                               const mossfw_data_qtf_t * in,
                               unsigned int num)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      transformqanglestf_element(&out[i], &in[i]);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformanglesf
 ****************************************************************************/

int mossdsp_transformanglesf(mossfw_data_qf_t * out,
                             const mossfw_data_v3f_t * in,
                             unsigned int num)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      transformanglesf_element(&out[i], &in[i]);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformanglestf
 ****************************************************************************/

int mossdsp_transformanglestf(mossfw_data_qtf_t * out,
                              const mossfw_data_v3tf_t * in,
                              unsigned int num)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      transformanglestf_element(&out[i], &in[i]);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformqazimuthf
 ****************************************************************************/

int mossdsp_transformqazimuthf(mossfw_data_v3f_t * out,
                               const mossfw_data_qf_t * in,
                               unsigned int num)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      transformqazimuthf_element(&out[i], &in[i]);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_transformqazimuthtf
 ****************************************************************************/

int mossdsp_transformqazimuthtf(mossfw_data_v3tf_t * out,
                                const mossfw_data_qtf_t * in,
                                unsigned int num)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      transformqazimuthtf_element(&out[i], &in[i]);
    }

  return 0;
}

/****************************************************************************
 * name: multiplyqf_element
 ****************************************************************************/

static void multiplyqf_element(mossfw_data_qf_t * out,
                               const mossfw_data_qf_t * in0,
                               const mossfw_data_qf_t * in1)
{
  out->w = in0->w * in1->w -
    in0->x * in1->x - in0->y * in1->y - in0->z * in1->z;

  out->x = in0->x * in1->w +
    in0->w * in1->x + in0->y * in1->z - in0->z * in1->y;

  out->y = in0->w * in1->y +
    in0->y * in1->w + in0->z * in1->x - in0->x * in1->z;

  out->z = in0->w * in1->z +
    in0->z * in1->w + in0->x * in1->y - in0->y * in1->x;
}

/****************************************************************************
 * name: multiplyqtf_element
 ****************************************************************************/

static void multiplyqtf_element(mossfw_data_qtf_t * out,
                                const mossfw_data_qtf_t * in0,
                                const mossfw_data_qtf_t * in1)
{
  out->w = in0->w * in1->w -
    in0->x * in1->x - in0->y * in1->y - in0->z * in1->z;

  out->x = in0->x * in1->w +
    in0->w * in1->x + in0->y * in1->z - in0->z * in1->y;

  out->y = in0->w * in1->y +
    in0->y * in1->w + in0->z * in1->x - in0->x * in1->z;

  out->z = in0->w * in1->z +
    in0->z * in1->w + in0->x * in1->y - in0->y * in1->x;

  out->t = in0->t;
}

/****************************************************************************
 * name: conjugateqf_element
 ****************************************************************************/

static void conjugateqf_element(mossfw_data_qf_t * out,
                                const mossfw_data_qf_t * in)
{
  out->w = in->w;
  out->x = -in->x;
  out->y = -in->y;
  out->z = -in->z;
}

/****************************************************************************
 * name: conjugateqtf_element
 ****************************************************************************/

static void conjugateqtf_element(mossfw_data_qtf_t * out,
                                 const mossfw_data_qtf_t * in)
{
  out->w = in->w;
  out->x = -in->x;
  out->y = -in->y;
  out->z = -in->z;

  out->t = in->t;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossdsp_multiplyqf
 ****************************************************************************/

int mossdsp_multiplyqf(mossfw_data_qf_t * out,
                       const mossfw_data_qf_t * in0,
                       const mossfw_data_qf_t * in1, unsigned int num)
{
  unsigned int i;

  if (out == NULL || in0 == NULL || in1 == NULL || num == 0)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      multiplyqf_element(&out[i], &in0[i], &in1[i]);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_multiplyqtf
 ****************************************************************************/

int mossdsp_multiplyqtf(mossfw_data_qtf_t * out,
                        const mossfw_data_qtf_t * in0,
                        const mossfw_data_qtf_t * in1, unsigned int num)
{
  unsigned int i;

  if (out == NULL || in0 == NULL || in1 == NULL || num == 0)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      multiplyqtf_element(&out[i], &in0[i], &in1[i]);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_conjugateqf
 ****************************************************************************/

int mossdsp_conjugateqf(mossfw_data_qf_t * out,
                        const mossfw_data_qf_t * in, unsigned int num)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      conjugateqf_element(&out[i], &in[i]);
    }

  return 0;
}

/****************************************************************************
 * name: mossdsp_conjugateqtf
 ****************************************************************************/

int mossdsp_conjugateqtf(mossfw_data_qtf_t * out,
                         const mossfw_data_qtf_t * in, unsigned int num)
{
  unsigned int i;

  if (out == NULL || in == NULL || num == 0)
    {
      return -1;
    }

  for (i = 0; i < num; i++)
    {
      conjugateqtf_element(&out[i], &in[i]);
    }

  return 0;
}
