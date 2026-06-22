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
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_component.h"
#include "mossfw/components/estimateposeacc.h"
#ifdef DEBUG_OUTPUT
#  include <stdio.h>
#endif

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

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
 * name: normalizev3f
 ****************************************************************************/

static mossfw_data_v3f_t normalizev3f(mossfw_data_v3f_t in, float e)
{
  float norm;
  mossfw_data_v3f_t ret;

  norm = sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
  ret.x = (norm > e) ? in.x * (1.0f / norm) : in.x;
  ret.y = (norm > e) ? in.y * (1.0f / norm) : in.y;
  ret.z = (norm > e) ? in.z * (1.0f / norm) : in.z;
  return ret;
}

/****************************************************************************
 * name: normalizeq
 ****************************************************************************/

static mossfw_data_qf_t normalizeq(mossfw_data_qf_t in)
{
  float norm;
  mossfw_data_qf_t ret;

  norm = sqrt(in.w * in.w + in.x * in.x + in.y * in.y + in.z * in.z);
  if (norm <= 1.0e-3f)
    ret = in;
  else
    {
      ret.w = in.w * (1.0f / norm);
      ret.x = in.x * (1.0f / norm);
      ret.y = in.y * (1.0f / norm);
      ret.z = in.z * (1.0f / norm);
    }

  return ret;
}

/****************************************************************************
 * name: estimateposeacc_main
 ****************************************************************************/

int estimateposeacc_main(struct mossfw_callback_op_s *in, unsigned long arg)
{
  int err = 0;
  mossfw_data_qf_t outbuf;
  mossfw_data_v3f_t accunit;
  float cos_theta;
  mossfw_data_v3f_t rotaxis;
  float theta;
  int used;

  (void)arg;
  struct estimateposeacc_s *com = getcomponent();
  int sizea = mossfw_get_delivereddata_num(in->input);
  int sizes = mossfw_get_delivereddata_num(in->input->cb_next);
  mossfw_data_t *ina = mossfw_get_delivereddata_array
                                        (in->input, sizea, &used);
  mossfw_data_t *indatastable =
    mossfw_get_delivereddata_array(in->input->cb_next, sizes, &used);

  accunit = normalizev3f(*(mossfw_data_v3f_t *)ina->data.xyzf, 1.0e-9f);
  cos_theta = -accunit.y;
  rotaxis.x = accunit.z;
  rotaxis.y = 0.0f;
  rotaxis.z = -accunit.x;
  rotaxis = normalizev3f(rotaxis, 10e-3f);
  theta = acosf(cos_theta);
  outbuf.w = cosf(theta * 0.5f);
  outbuf.x = rotaxis.x * sinf(theta * 0.5f);
  outbuf.y = rotaxis.y * sinf(theta * 0.5f);
  outbuf.z = rotaxis.z * sinf(theta * 0.5f);
  outbuf = normalizeq(outbuf);
  size_t sizef = sizeof(mossfw_data_v1f_t);
  mossfw_data_t *outdatare = mossfw_data_alloc(com->alloc, sizef, true);
  err = err || !outdatare;
  if (!err)
    {
      outdatare->data.xf->x = outbuf.w;
      outdatare->data_bytes = sizeof(mossfw_data_v1f_t);
      ina->data.xyzf->x = outbuf.x;
      ina->data.xyzf->y = outbuf.y;
      ina->data.xyzf->z = outbuf.z;
    }

  if (indatastable->data.xs->x)
    {
#ifdef DEBUG_OUTPUT
      printf("EstimatePoseAcc %e %e %e %e\n", outdatare->data.xf->x,
             ina->data.xyzf->x, ina->data.xyzf->y, ina->data.xyzf->z);
      fflush(stdout);
#endif
      err = err || mossfw_deliver_dataarray(com->outr, outdatare);
      err = err || mossfw_deliver_dataarray(com->outi, ina);
    }

  mossfw_data_free(ina);
  return err;
}

/****************************************************************************
 * name: estimateposeacc_create
 ****************************************************************************/

struct estimateposeacc_s *estimateposeacc_create
                                    (mossfw_allocator_t *allocator)
{
  int err = 0;
  struct estimateposeacc_s *ret = malloc(sizeof(struct estimateposeacc_s));
  if (ret)
    {
      uint32_t itypeacc = MOSSFW_DATA_TYPE_FLOAT |
        MOSSFW_DATA_TYPEGRP_V3 |
        MOSSFW_DATA_TYPENAME_ACCEL | MOSSFW_DATA_TYPEARRAY_ARRAY;
      uint32_t itypestable = MOSSFW_DATA_TYPE_SHORT |
        MOSSFW_DATA_TYPEGRP_V1 |
        MOSSFW_DATA_TYPENAME_ACCEL | MOSSFW_DATA_TYPEARRAY_ARRAY;
      uint32_t otype = MOSSFW_DATA_TYPE_FLOAT |
        MOSSFW_DATA_TYPEARRAY_ARRAY;
      ret->inacc = mossfw_input_create(itypeacc, 1);
      ret->instbl = mossfw_input_create(itypestable, 1);
      ret->op = mossfw_callback_op_create(estimateposeacc_main, 0, false);
      ret->outr = mossfw_output_create(otype | MOSSFW_DATA_TYPEGRP_V1);
      ret->outi = mossfw_output_create(otype | MOSSFW_DATA_TYPEGRP_V3);
      ret->alloc = allocator;
      err = err || !ret->inacc;
      err = err || !ret->instbl;
      err = err || !ret->op;
      err = err || !ret->outr;
      err = err || !ret->outi;
      err = err || !allocator;
      err = err ||
        mossfw_set_waitcondition(ret->inacc, sizeof(mossfw_data_v3f_t),
                              ret->op);
      err = err ||
        mossfw_set_waitcondition(ret->instbl, sizeof(mossfw_data_v1s_t),
                              ret->op);
    }

  if (err)
    {
      estimateposeacc_delete(ret);
      ret = NULL;
    }

  setcomponent(ret);
  return ret;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: estimateposeacc_delete
 ****************************************************************************/

void estimateposeacc_delete(struct estimateposeacc_s *estimateposeacc)
{
  if (estimateposeacc)
    {
      mossfw_output_delete(estimateposeacc->outr);
      mossfw_output_delete(estimateposeacc->outi);
      mossfw_callback_op_delete(estimateposeacc->op);
      mossfw_input_delete(estimateposeacc->inacc);
      mossfw_input_delete(estimateposeacc->instbl);
    }

  free(estimateposeacc);
}
