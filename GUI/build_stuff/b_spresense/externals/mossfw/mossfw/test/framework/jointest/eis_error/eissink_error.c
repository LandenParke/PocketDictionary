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
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <float.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/mossfw_data.h"
#include "mossfw/sensorlib.h"
#include "component.h"
#include "eis_error/eissink_error.h"
#include "eis_error/resampleinfo_error.h"
#include "eis_error/outputdata_error.h"

#define EISSINK_INPUTTYPE_ACC  (MOSSFW_DATA_TYPE_FLOAT + \
                                MOSSFW_DATA_TYPEGRP_V3 + \
                                MOSSFW_DATA_TYPENAME_ACCEL + \
                                MOSSFW_DATA_TYPEARRAY_ARRAY)
#define EISSINK_INPUTTYPE_GYR  (MOSSFW_DATA_TYPE_FLOAT + \
                                MOSSFW_DATA_TYPEGRP_V3 + \
                                MOSSFW_DATA_TYPENAME_GYRO + \
                                MOSSFW_DATA_TYPEARRAY_ARRAY)
#define EISSINK_INPUTTYPE_LINE (MOSSFW_DATA_TYPEARRAY_ARRAY)
#define EISSINK_INPUTTYPE_ROT  (MOSSFW_DATA_TYPE_FLOAT + \
                                MOSSFW_DATA_TYPEGRP_Q + \
                                MOSSFW_DATA_TYPEARRAY_ARRAY)

static size_t nacc  = 0;
static size_t ngyr  = 0;
static size_t nline = 0;
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

static size_t rot_expect(mossfw_data_t *rot, mossfw_data_qf_t *exp, size_t *count)
{
    size_t i;
    int num;

    num = rot->data_bytes / sizeof(mossfw_data_qf_t);
    for (i = 0; i < num; i++) {
#ifdef DEBUG_OUTPUT
        printf("rot_expect val = (%.9e %.9e %.9e %.9e), exp = (%.9e %.9e %.9e %.9e)\n",
               rot->data.qf[i].w, rot->data.qf[i].x, rot->data.qf[i].y, rot->data.qf[i].z,
               exp[*count + i].w, exp[*count + i].x, exp[*count + i].y, exp[*count + i].z);
        fflush(stdout);
#endif
        fltassert_epsilon(rot->data.qf[i].w, exp[*count + i].w);
        fltassert_epsilon(rot->data.qf[i].x, exp[*count + i].x);
        fltassert_epsilon(rot->data.qf[i].y, exp[*count + i].y);
        fltassert_epsilon(rot->data.qf[i].z, exp[*count + i].z);
    }
    *count = *count + num;
}

static void vec3_expect(mossfw_data_t *vec3, mossfw_data_v3f_t *exp, size_t *count)
{
    int i;
    int num;

    num = vec3->data_bytes / sizeof(mossfw_data_v3f_t);
    for (i = 0; i < num; i++)
      {
#ifdef DEBUG_OUTPUT
          printf("vec3_expect val = (%.9e %.9e %.9e), exp = (%.9e %.9e %.9e)\n",
                 vec3->data.xyzf[i].x, vec3->data.xyzf[i].y, vec3->data.xyzf[i].z,
                 exp[*count + i].x, exp[*count + i].y, exp[*count + i].z);
          fflush(stdout);
#endif
          fltassert_epsilon(vec3->data.xyzf[i].x, exp[*count + i].x);
          fltassert_epsilon(vec3->data.xyzf[i].y, exp[*count + i].y);
          fltassert_epsilon(vec3->data.xyzf[i].z, exp[*count + i].z);
      }
    *count = *count + num;
}

static void resampleinfo_expect(mossfw_data_t *linedata, struct resampleinfo_s *exp, size_t *count)
{
    int i;
    struct resampleinfo_s *data;
    int num;

    data = (void *)linedata->data.v1c;
    num = linedata->data_bytes / sizeof(struct resampleinfo_s);
    for (i = 0; i < num; i++)
      {
          assert(data[i].slerpflg == exp[*count + i].slerpflg);
          assert(data[i].q1idx    == exp[*count + i].q1idx);
          assert(data[i].q2idx    == exp[*count + i].q2idx);
          assert(data[i].line1    == exp[*count + i].line1);
          assert(data[i].line2    == exp[*count + i].line2);
      }
    *count = *count + num;
}

static int eissink_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  int ret = 0;
  mossfw_input_t *inputacc;
  mossfw_input_t *inputgyr;
  mossfw_input_t *inputline;
  mossfw_input_t *inputrot;
  int sizeacc  = 0;
  int sizegyr  = 0;
  int sizeline = 0;
  int sizerot  = 0;
  mossfw_data_t *indataacc  = NULL;
  mossfw_data_t *indatagyr  = NULL;
  mossfw_data_t *indataline = NULL;
  mossfw_data_t *indatarot = NULL;
  int usedacc;
  int usedgyr;
  int usedline;
  int usedrot;

  assert(arg == 0 || arg == 1);
  if (arg == 0)
    {
      inputacc  = in->input;
      inputgyr  = inputacc->cb_next;
      inputline = inputgyr->cb_next;
      sizeacc   = mossfw_get_delivereddata_num(inputacc);
      sizegyr   = mossfw_get_delivereddata_num(inputgyr);
      sizeline  = mossfw_get_delivereddata_num(inputline);
    }
  else 
    {
      inputrot  = in->input;
      sizerot  = mossfw_get_delivereddata_num(inputrot);
    }

  if (0 < sizeacc)
    {
      indataacc = mossfw_get_delivereddata_array(inputacc, sizeacc, &usedacc);
      assert(indataacc);
      vec3_expect(indataacc, acc_error_expected, &nacc);
    }
  if (0 < sizegyr)
    {
      indatagyr = mossfw_get_delivereddata_array(inputgyr, sizegyr, &usedgyr);
      assert(indatagyr);
      vec3_expect(indatagyr, gyr_error_expected, &ngyr);
    }
  if (0 < sizeline)
    {
      indataline = mossfw_get_delivereddata_array(inputline, sizeline, &usedline);
      assert(indataline);
      if (1 < sizeline)
        {
          resampleinfo_expect(indataline, resampleinfo_error_expected, &nline);
        }
    }
  if (0 < sizerot)
    {
      indatarot = mossfw_get_delivereddata_array(inputrot, sizerot, &usedrot);
      assert(indatarot);
      rot_expect(indatarot, rot_error_expected, &nrot);
    }
    mossfw_data_free(indataacc);
    mossfw_data_free(indatagyr);
    mossfw_data_free(indataline);
    mossfw_data_free(indatarot);
    return ret;
}

void eissink_error_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num    = EISSINK_SIZE;
      com->out_num   = 0;
      com->op_num    = 2;
      com->in        = malloc(com->in_num * sizeof(void *));
      com->out       = NULL;
      com->op        = malloc(com->op_num  * sizeof(void *));
      com->in[EISSINK_ACC]   = mossfw_input_create(EISSINK_INPUTTYPE_ACC,  2);
      com->in[EISSINK_GYR]   = mossfw_input_create(EISSINK_INPUTTYPE_GYR,  2);
      com->in[EISSINK_LINE]  = mossfw_input_create(EISSINK_INPUTTYPE_LINE, 2);
      com->in[EISSINK_ROT]   = mossfw_input_create(EISSINK_INPUTTYPE_ROT,  2);
      com->op[0] = mossfw_callback_op_create(eissink_operate_cb, 0, false);
      com->op[1] = mossfw_callback_op_create(eissink_operate_cb, 1, false);
      mossfw_set_waitcondition(com->in[EISSINK_ACC], sizeof(mossfw_data_v3s_t), com->op[0]);
      mossfw_set_waitcondition(com->in[EISSINK_GYR], sizeof(mossfw_data_v3s_t), com->op[0]);
      mossfw_set_waitcondition(com->in[EISSINK_LINE], 1,                            com->op[0]);
      mossfw_set_waitcondition(com->in[EISSINK_ROT], sizeof(mossfw_data_qf_t),   com->op[1]);
    }
    nacc  = 0;
    ngyr  = 0;
    nline = 0;
    nrot  = 0;
}

void eissink_error_delete(struct component_s *com)
{
    component_delete(com);
}

/* return 0 is succeeded */
int eissink_error_succeeded(void)
{
    int accerr;
    int gyrerr;
    int lineerr;
    int roterr;

    accerr  = (nacc  != sizeof_acc_error_expected() / (sizeof acc_error_expected[0]));
    gyrerr  = (ngyr  != sizeof_gyr_error_expected() / (sizeof gyr_error_expected[0]));
    lineerr = (nline != sizeof_resampleinfo_error_expected() / (sizeof resampleinfo_error_expected[0]));
    roterr  = (nrot  != sizeof_rot_error_expected() / (sizeof rot_error_expected[0]));
    return accerr || gyrerr || lineerr || roterr;
}
