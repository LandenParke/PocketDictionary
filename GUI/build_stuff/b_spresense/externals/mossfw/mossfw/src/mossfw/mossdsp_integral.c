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

#include <errno.h>
#include <stdio.h>
#include <math.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_data.h"
#include "mossfw/mossdsp.h"

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossdsp_integrategyrv3f_element
 ****************************************************************************/

static void mossdsp_integrategyrv3f_element(mossfw_data_qf_t *out,
                                            const mossfw_data_qf_t *inq,
                                            const mossfw_data_v3f_t *ing,
                                            float dt)
{
  mossfw_data_v3f_t gyr;
  mossfw_data_qf_t qv;
  float abs;

  gyr.x = (ing->x * dt) / 2.0f;
  gyr.y = (ing->y * dt) / 2.0f;
  gyr.z = (ing->z * dt) / 2.0f;
  qv.w = (inq->w - gyr.x * inq->x) -
          (gyr.y * inq->y + gyr.z * inq->z);
  qv.x = (gyr.x * inq->w + inq->x) +
          (gyr.z * inq->y - gyr.y * inq->z);
  qv.y = (gyr.y * inq->w - gyr.z * inq->x) +
          (inq->y + gyr.x * inq->z);
  qv.z = (gyr.z * inq->w + gyr.y * inq->x) -
          (gyr.x * inq->y - inq->z);
  abs = sqrtf((qv.w * qv.w + qv.x * qv.x) +
          (qv.y * qv.y + qv.z * qv.z));
  out->w = qv.w / abs;
  out->x = qv.x / abs;
  out->y = qv.y / abs;
  out->z = qv.z / abs;
}

/****************************************************************************
 * name: mossdsp_integrategyrv3ti_element
 ****************************************************************************/

static void mossdsp_integrategyrv3ti_element(mossfw_data_qtf_t *out,
                                              const mossfw_data_qtf_t *inq,
                                              const mossfw_data_v3ts_t *ing,
                                              float res, float scale_factor)
{
  mossfw_data_qf_t oq;
  mossfw_data_qf_t iq;
  mossfw_data_v3f_t gy;
  iq.w = inq->w;
  iq.x = inq->x;
  iq.y = inq->y;
  iq.z = inq->z;
  gy.x = ing->x * scale_factor;
  gy.y = ing->y * scale_factor;
  gy.z = ing->z * scale_factor;
  mossdsp_integrategyrv3f_element(&oq, &iq, &gy,
                                    (float)(ing->t - inq->t) * res);
  out->w = oq.w;
  out->x = oq.x;
  out->y = oq.y;
  out->z = oq.z;
  out->t = ing->t;
}

/****************************************************************************
 * name: mossdsp_integrategyrv3tf_element
 ****************************************************************************/

static void mossdsp_integrategyrv3tf_element(mossfw_data_qtf_t *out,
                                              const mossfw_data_qtf_t *inq,
                                              const mossfw_data_v3tf_t *ing,
                                              float res)
{
  mossfw_data_qf_t oq;
  mossfw_data_qf_t iq;
  mossfw_data_v3f_t gy;
  iq.w = inq->w;
  iq.x = inq->x;
  iq.y = inq->y;
  iq.z = inq->z;
  gy.x = ing->x;
  gy.y = ing->y;
  gy.z = ing->z;
  mossdsp_integrategyrv3f_element(&oq, &iq, &gy,
                                    (float)(ing->t - inq->t) * res);
  out->w = oq.w;
  out->x = oq.x;
  out->y = oq.y;
  out->z = oq.z;
  out->t = ing->t;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossdsp_integrategyrv3i
 ****************************************************************************/

int mossdsp_integrategyrv3i(mossfw_data_qf_t *out,
                            const mossfw_data_v3s_t *in,
                            unsigned int num,
                            const struct mossdsp_integrategyr_param_s *param)
{
  mossfw_data_qf_t pre;
  int err;
  float dt;
  unsigned int i;
  mossfw_data_v3f_t gyr;

  err = (out != NULL && in != NULL && num != 0 && param != NULL) - 1;
  if (!err)
    {
      dt = (float)param->dt * ((float)param->res.tv_sec +
            (float)param->res.tv_nsec / 1000000000.0f);
      pre = param->lastout.f;
    }

  for (i = 0; i < num && !err; i++)
    {
      gyr.x = (float)(in + i)->x * param->scale_factor;
      gyr.y = (float)(in + i)->y * param->scale_factor;
      gyr.z = (float)(in + i)->z * param->scale_factor;
      mossdsp_integrategyrv3f_element(out + i, &pre, &gyr, dt);
      pre = *(out + i);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_integrategyrv3f
 ****************************************************************************/

int mossdsp_integrategyrv3f(mossfw_data_qf_t *out,
                            const mossfw_data_v3f_t *in,
                            unsigned int num,
                            const struct mossdsp_integrategyr_param_s *param)
{
  mossfw_data_qf_t pre;
  int err;
  float dt;
  unsigned int i;

  err = (out != NULL && in != NULL && num != 0 && param != NULL) - 1;
  if (!err)
    {
      dt = (float)param->dt * ((float)param->res.tv_sec +
            (float)param->res.tv_nsec / 1000000000.0f);
      pre = param->lastout.f;
    }

  for (i = 0; i < num && !err; i++)
    {
      mossdsp_integrategyrv3f_element(out + i, &pre, in + i, dt);
      pre = *(out + i);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_integrategyrv3ti
 ****************************************************************************/

int mossdsp_integrategyrv3ti(mossfw_data_qtf_t *out,
                            const mossfw_data_v3ts_t *in,
                            unsigned int num,
                            const struct mossdsp_integrategyr_param_s *param)
{
  mossfw_data_qtf_t pre;
  int err;
  float res;
  unsigned int i;

  err = (out != NULL && in != NULL && num != 0 && param != NULL) - 1;
  if (!err)
    {
      pre = param->lastout.tf;
      res = (float)param->res.tv_sec +
            (float)param->res.tv_nsec / 1000000000.0f;
    }

  for (i = 0; i < num && !err; i++)
    {
      mossdsp_integrategyrv3ti_element(out + i, &pre, in + i, res,
                                        param->scale_factor);
      pre = *(out + i);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_integrategyrv3tf
 ****************************************************************************/

int mossdsp_integrategyrv3tf(mossfw_data_qtf_t *out,
                            const mossfw_data_v3tf_t *in,
                            unsigned int num,
                            const struct mossdsp_integrategyr_param_s *param)
{
  mossfw_data_qtf_t pre;
  int err;
  float res;
  unsigned int i;

  err = (out != NULL && in != NULL && num != 0 && param != NULL) - 1;
  if (!err)
    {
      pre = param->lastout.tf;
      res = (float)param->res.tv_sec +
            (float)param->res.tv_nsec / 1000000000.0f;
    }

  for (i = 0; i < num && !err; i++)
    {
      mossdsp_integrategyrv3tf_element(out + i, &pre, in + i, res);
      pre = *(out + i);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_integrategyrv3ia
 ****************************************************************************/

int mossdsp_integrategyrv3ia(mossfw_data_qf_t *out,
                            const struct vector3ia_s *in,
                            unsigned int num,
                            const struct mossdsp_integrategyr_param_s *param)
{
  mossfw_data_qf_t pre;
  int err;
  float dt;
  mossfw_data_v3f_t vin;
  unsigned int i;

  err = (out != NULL && in != NULL && num != 0 && param != NULL) - 1;
  err = (!err && in->x != NULL && in->y != NULL && in->z != NULL) - 1;
  if (!err)
    {
      dt = (float)param->dt * ((float)param->res.tv_sec +
            (float)param->res.tv_nsec / 1000000000.0f);
      pre = param->lastout.f;
    }

  for (i = 0; i < num && !err; i++)
    {
      vin.x = *(in->x + i) * param->scale_factor;
      vin.y = *(in->y + i) * param->scale_factor;
      vin.z = *(in->z + i) * param->scale_factor;
      mossdsp_integrategyrv3f_element(out + i, &pre, &vin, dt);
      pre = *(out + i);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_integrategyrv3fa
 ****************************************************************************/

int mossdsp_integrategyrv3fa(mossfw_data_qf_t *out,
                            const struct vector3fa_s *in,
                            unsigned int num,
                            const struct mossdsp_integrategyr_param_s *param)
{
  mossfw_data_qf_t pre;
  int err;
  float dt;
  mossfw_data_v3f_t vin;
  unsigned int i;

  err = (out != NULL && in != NULL && num != 0 && param != NULL) - 1;
  err = (!err && in->x != NULL && in->y != NULL && in->z != NULL) - 1;
  if (!err)
    {
      dt = (float)param->dt * ((float)param->res.tv_sec +
            (float)param->res.tv_nsec / 1000000000.0f);
      pre = param->lastout.f;
    }

  for (i = 0; i < num && !err; i++)
    {
      vin.x = *(in->x + i);
      vin.y = *(in->y + i);
      vin.z = *(in->z + i);
      mossdsp_integrategyrv3f_element(out + i, &pre, &vin, dt);
      pre = *(out + i);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_integrategyrv3tia
 ****************************************************************************/

int mossdsp_integrategyrv3tia(mossfw_data_qtf_t *out,
                            const struct vector3tia_s *in,
                            unsigned int num,
                            const struct mossdsp_integrategyr_param_s *param)
{
  mossfw_data_qtf_t pre;
  int err;
  float res;
  mossfw_data_v3ts_t vin;
  unsigned int i;

  err = (out != NULL && in != NULL && num != 0 && param != NULL) - 1;
  err = (!err && in->t != NULL && in->x != NULL &&
            in->y != NULL && in->z != NULL) - 1;
  if (!err)
    {
      pre = param->lastout.tf;
      res = (float)param->res.tv_sec +
                  (float)param->res.tv_nsec / 1000000000.0f;
    }

  for (i = 0; i < num && !err; i++)
    {
      vin.t = *(in->t + i);
      vin.x = *(in->x + i);
      vin.y = *(in->y + i);
      vin.z = *(in->z + i);
      mossdsp_integrategyrv3ti_element(out + i, &pre, &vin, res,
                                        param->scale_factor);
      pre = *(out + i);
    }

  return err;
}

/****************************************************************************
 * name: mossdsp_integrategyrv3tfa
 ****************************************************************************/

int mossdsp_integrategyrv3tfa(mossfw_data_qtf_t *out,
                            const struct vector3tfa_s *in,
                            unsigned int num,
                            const struct mossdsp_integrategyr_param_s *param)
{
  mossfw_data_qtf_t pre;
  int err;
  float res;
  mossfw_data_v3tf_t vin;
  unsigned int i;

  err = (out != NULL && in != NULL && num != 0 && param != NULL) - 1;
  err = (!err && in->t != NULL && in->x != NULL &&
            in->y != NULL && in->z != NULL) - 1;
  if (!err)
    {
      pre = param->lastout.tf;
      res = (float)param->res.tv_sec +
            (float)param->res.tv_nsec / 1000000000.0f;
    }

  for (i = 0; i < num && !err; i++)
    {
      vin.t = *(in->t + i);
      vin.x = *(in->x + i);
      vin.y = *(in->y + i);
      vin.z = *(in->z + i);
      mossdsp_integrategyrv3tf_element(out + i, &pre, &vin, res);
      pre = *(out + i);
    }

  return err;
}
