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
#include <math.h>
#include <string.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossdsp.h"
#include "mossfw/mossfw_component.h"
#include "mossfw/components/complementaryfilter.h"
#ifdef DEBUG_OUTPUT
#  include <stdio.h>
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define PI 3.14159265358979323846f

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

static void *component = NULL;
static unsigned int gyrcount = 0;

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
 * name: accrot
 ****************************************************************************/

static mossfw_data_qf_t accrot =
{
  .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f
};

/****************************************************************************
 * name: gyrparam
 ****************************************************************************/

static struct mossdsp_integrategyr_param_s gyrparam =
{
  .lastout.f =
    {
      .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f
    },

  .dt = 3125,
  .res =
    {
      .tv_sec = 0, .tv_nsec = 100000
    },

  .scale_factor = 0.0f
};

/****************************************************************************
 * name: normalize
 ****************************************************************************/

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

/****************************************************************************
 * name: calculateyawrotation
 ****************************************************************************/

static mossfw_data_qf_t calculateyawrotation(mossfw_data_qf_t rot)
{
  mossfw_data_qf_t ret =
    {
      .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f
    };

  float theta;
  float norm;

  theta = acosf(rot.w);
  norm = sqrtf(rot.x * rot.x + rot.y * rot.y + rot.z * rot.z);
  if (norm > 0.00001f)
    {
      ret.w = cosf(theta);
      ret.x = 0.0f;
      ret.y = sinf(theta) * (rot.y / norm);
      ret.z = 0.0f;
      ret = normalize(ret);
    }

  return ret;
}

/****************************************************************************
 * name: complementaryfilter
 ****************************************************************************/

static mossfw_data_qf_t complementaryfilter(mossfw_data_qf_t rotgyr,
  mossfw_data_qf_t rotacc)
{
  mossfw_data_qf_t ret =
    {
      .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f
    };

  mossfw_data_qf_t yawrot;
  mossfw_data_qf_t rot;
  struct mossdsp_interpolate_param_s param =
    {
      .t0 = 0, .t1 = 1000, .t = 1
    };

  yawrot = calculateyawrotation(rotgyr);
  mossdsp_multiplyqf(&rot, &yawrot, &rotacc, 1);
  mossdsp_interpolateqf(&ret, &rotgyr, &rot, &param);
  ret = normalize(ret);
  return ret;
}

/****************************************************************************
 * name: complementaryfilter_set_time_resolution
 ****************************************************************************/

void complementaryfilter_set_time_resolution(long nsec)
{
  gyrparam.res.tv_sec = nsec / 1000000000;
  gyrparam.res.tv_nsec = nsec % 1000000000;
}

/****************************************************************************
 * name: complementaryfilter_main
 ****************************************************************************/

static int complementaryfilter_main(mossfw_callback_op_t *in,
                                    unsigned long arg)
{
  int ret = 0;
  size_t calnum;
  size_t caloffset;
  int used;

  struct complementaryfilter_s *com = getcomponent();
  if (arg == ID_DATA_ESTIMATEPOSEACC)
    {
      int sizer = mossfw_get_delivereddata_num(in->input);
      int sizei = mossfw_get_delivereddata_num(in->input->cb_next);
      mossfw_data_t *inr =
        mossfw_get_delivereddata_array(in->input, sizer, &used);
      mossfw_data_t *ini =
        mossfw_get_delivereddata_array(in->input->cb_next, sizei, &used);
      accrot.w = inr->data.xf->x;
      accrot.x = ini->data.xyzf->x;
      accrot.y = ini->data.xyzf->y;
      accrot.z = ini->data.xyzf->z;
      gyrcount = 0;
#ifdef DEBUG_OUTPUT
      printf("ComplementaryFilter POSEACC num = %d\n",
             sizer / sizeof(mossfw_data_v1f_t));
#endif
    }
  else if (arg == COMPLEMENTARYFILTER_GYR1)
    {
      int size = mossfw_get_delivereddata_num(in->input);
      mossfw_data_t *ing =
        mossfw_get_delivereddata_array(in->input, size, &used);
      int num = size / sizeof(mossfw_data_v3f_t);
      int bufsize = num * sizeof(mossfw_data_qf_t);
      mossfw_data_t *bufdata = mossfw_data_alloc(com->allocq,
                                                             bufsize,
                                                             true);
      mossfw_data_qf_t *buf = (mossfw_data_qf_t *)(bufdata->data.xf);
#ifdef DEBUG_OUTPUT
      printf("ComplementaryFilter POSEGYR num = %d, (%e, %e, %e)\n", num,
             ing->data.xyzf->x, ing->data.xyzf->y, ing->data.xyzf->z);
#endif
      for (int i = 0; i < num; i++)
        {
          ing->data.xyzf[i].x = ing->data.xyzf[i].x * (PI / 180.0f);
          ing->data.xyzf[i].y = ing->data.xyzf[i].y * (PI / 180.0f);
          ing->data.xyzf[i].z = ing->data.xyzf[i].z * (PI / 180.0f);
        }

      mossfw_data_v3f_t *ingv3f = (mossfw_data_v3f_t *)ing->data.xyzf;
      if (gyrcount == 0)
        {
          calnum = num - 1;
          caloffset = 1;
          mossdsp_integrategyrv3f(buf, ingv3f, 1, &gyrparam);
          *buf = complementaryfilter(*buf, accrot);
          gyrparam.lastout.f = *buf;
        }
      else
        {
          calnum = num;
          caloffset = 0;
        }

      mossdsp_integrategyrv3f(&buf[caloffset], &ingv3f[caloffset],
                                calnum, &gyrparam);
      gyrparam.lastout.f = buf[caloffset + calnum - 1];
      mossfw_data_t *outdatare = mossfw_data_alloc(com->allocr,
                                                    num *
                                                    sizeof
                                                    (mossfw_data_v1f_t),
                                                    true);
      for (int i = 0; i < num; i++)
        {
          outdatare->data.xf[i].x = buf[i].w;
          outdatare->timestamp = ing->timestamp;
          ing->data.xyzf[i].x = buf[i].x;
          ing->data.xyzf[i].y = buf[i].y;
          ing->data.xyzf[i].z = buf[i].z;
        }

      outdatare->data_bytes = num * sizeof(mossfw_data_v1f_t);
#ifdef DEBUG_OUTPUT
      for (int i = 0; i < num; i++)
        {
          printf("IntegralGyr %0.16f %0.16f %0.16f %0.16f\n",
                 outdatare->data.xf[i].x, ing->data.xyzf[i].x,
                 ing->data.xyzf[i].y, ing->data.xyzf[i].z);
        }

#endif
      gyrcount = 1;
      ret = mossfw_deliver_dataarray(com->outr, outdatare);
      ret = mossfw_deliver_dataarray(com->outi, ing);
      mossfw_data_free(ing);
      mossfw_data_free(outdatare);
      mossfw_data_free(bufdata);
    }

  return ret;
}

/****************************************************************************
 * name: complementaryfilter_create
 ****************************************************************************/

struct complementaryfilter_s *complementaryfilter_create(mossfw_allocator_t *
  allocatorr,
  mossfw_allocator_t *
  allocatorq)
{
  int err = 0;
  struct complementaryfilter_s *ret =
    malloc(sizeof(struct complementaryfilter_s));
  if (ret)
    {
      uint32_t typegyr = MOSSFW_DATA_TYPE_FLOAT |
        MOSSFW_DATA_TYPEGRP_V3 |
        MOSSFW_DATA_TYPENAME_GYRO | MOSSFW_DATA_TYPEARRAY_ARRAY;
      uint32_t typerot = MOSSFW_DATA_TYPE_FLOAT |
        MOSSFW_DATA_TYPEARRAY_ARRAY;
      ret->ingyr = mossfw_input_create(typegyr, 1);
      ret->inrotr =
        mossfw_input_create(typerot | MOSSFW_DATA_TYPEGRP_V1, 1);
      ret->inroti =
        mossfw_input_create(typerot | MOSSFW_DATA_TYPEGRP_V3, 1);
      ret->opgyr =
        mossfw_callback_op_create(complementaryfilter_main,
                                  COMPLEMENTARYFILTER_GYR1, false);
      ret->oprot =
        mossfw_callback_op_create(complementaryfilter_main,
                                  ID_DATA_ESTIMATEPOSEACC, false);
      ret->outr = mossfw_output_create(typerot | MOSSFW_DATA_TYPEGRP_V1);
      ret->outi = mossfw_output_create(typerot | MOSSFW_DATA_TYPEGRP_V3);
      ret->allocr = allocatorr;
      ret->allocq = allocatorq;
      err = err || !ret->ingyr;
      err = err || !ret->inrotr;
      err = err || !ret->inroti;
      err = err || !ret->opgyr;
      err = err || !ret->oprot;
      err = err || !allocatorr;
      err = err || !allocatorq;
      err = err ||
        mossfw_set_waitcondition(ret->ingyr, sizeof(mossfw_data_v3f_t),
                                 ret->opgyr);
      err = err ||
        mossfw_set_waitcondition(ret->inrotr, sizeof(mossfw_data_v1f_t),
                                 ret->oprot);
      err = err ||
        mossfw_set_waitcondition(ret->inroti,
                                 sizeof(mossfw_data_v3f_t), ret->oprot);
    }

  if (err)
    {
      complementaryfilter_delete(ret);
      ret = NULL;
    }

  setcomponent(ret);
  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: complementaryfilter_delete
 ****************************************************************************/

void complementaryfilter_delete(struct complementaryfilter_s *com)
{
  if (com)
    {
      mossfw_output_delete(com->outr);
      mossfw_output_delete(com->outi);
      mossfw_callback_op_delete(com->oprot);
      mossfw_callback_op_delete(com->opgyr);
      mossfw_input_delete(com->ingyr);
      mossfw_input_delete(com->inrotr);
      mossfw_input_delete(com->inroti);
    }

  free(com);
}
