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
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "component.h"
#include "attitude_error_result.h"
#include "attitude_error_outputdata.h"
//#define DEBUG_OUTPUT

#define RESULT_ROT_INPUTTYPE (MOSSFW_DATA_TYPE_FLOAT + \
                              MOSSFW_DATA_TYPEGRP_Q + \
                              MOSSFW_DATA_TYPEARRAY_SINGLE)

static size_t nrot  = 0;

static void fltassert_epsilon(float a, float exp)
{
  const float epsilon = 300.0f * FLT_EPSILON;

#ifdef DEBUG_OUTPUT
  printf("fltassert_epsilon a = %.9e, exp = %.9e\n", a, exp);
#endif

  if (exp < 0)
    {
      assert(exp * (1.0f + epsilon) < a);
      assert(a < exp * (1.0f - epsilon));
    }
  else if (0 < exp)
    {
      assert(exp * (1.0f - epsilon) < a);
      assert(a < exp * (1.0f + epsilon));
    }
  else
    {
      assert(FLT_MIN < a);
      assert(a < FLT_MIN);
    }
}

static size_t rot_expect(mossfw_onedata_t *rot, mossfw_data_qf_t *exp, size_t *count)
{
#ifdef DEBUG_OUTPUT
  printf("rot_expect val = (%.9e %.9e %.9e %.9e), exp = (%.9e %.9e %.9e %.9e)\n",
          rot->qf.w, rot->qf.x, rot->qf.y, rot->qf.z,
          exp[*count].w, exp[*count].x, exp[*count].y, exp[*count].z);
  fflush(stdout);
#endif

  fltassert_epsilon(rot->qf.w, exp[*count].w);
  fltassert_epsilon(rot->qf.x, exp[*count].x);
  fltassert_epsilon(rot->qf.y, exp[*count].y);
  fltassert_epsilon(rot->qf.z, exp[*count].z);

  *count = *count + 1;
}

static int result_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  int ret = 0;
  mossfw_onedata_t data;

  mossfw_get_delivereddata_single(in->input, &data);
  rot_expect(&data, attitude_error_rot_expected, &nrot);

  return ret;
}

void attitude_error_result_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 0;
      com->op_num  = 1;
      com->in = malloc(com->in_num * sizeof(void *));
      com->op = malloc(com->op_num * sizeof(void *));
      com->out = NULL;
      com->in[0] = mossfw_input_create(RESULT_ROT_INPUTTYPE, 2);
      com->op[0] = mossfw_callback_op_create(result_operate_cb, 0, false);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_qf_t),   com->op[0]);
    }
}

void attitude_error_result_reset(void)
{
  nrot = 0;
}

void attitude_error_result_delete(struct component_s *com)
{
  component_delete(com);
}

int attitude_error_result_succeeded(void)
{
  int roterr;

  roterr  = (nrot  != attitude_error_sizeof_rot_expected() / (sizeof attitude_error_rot_expected[0]));
  return roterr;
}
