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
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_component.h"
#include "component.h"
#include "eis_error/transformaxes_error.h"
#include "resampleinfo_error.h"
#include "eis_error/eis_error.h"

#define TRANSFORMAXES_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPENAME_ACCEL + \
                                  MOSSFW_DATA_TYPEARRAY_ARRAY)
#define TRANSFORMAXES_INPUTTYPE_GYR (MOSSFW_DATA_TYPE_FLOAT + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPENAME_GYRO + \
                                  MOSSFW_DATA_TYPEARRAY_ARRAY)
#define TRANSFORMAXES_INPUTTYPE_LINE (MOSSFW_DATA_TYPEARRAY_ARRAY)
#define TRANSFORMAXES_OUTPUTTYPE_ACC  TRANSFORMAXES_INPUTTYPE_ACC 
#define TRANSFORMAXES_OUTPUTTYPE_GYR  TRANSFORMAXES_INPUTTYPE_GYR
#define TRANSFORMAXES_OUTPUTTYPE_LINE TRANSFORMAXES_INPUTTYPE_LINE

static int transformaxes_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
    int ret = 0;
    int datasizeacc;
    int datasizegyr;
    int datasizeline;
    size_t numacc;
    size_t numgyr;
    size_t numline;
    mossfw_data_t *indataacc  = NULL;
    mossfw_data_t *indatagyr  = NULL;
    mossfw_data_t *indataline = NULL;
    int usedacc;
    int usedgyr;
    int usedline;

    datasizeacc  = mossfw_get_delivereddata_num(in->input);
    datasizegyr  = mossfw_get_delivereddata_num(in->input->cb_next);
    datasizeline = mossfw_get_delivereddata_num(in->input->cb_next->cb_next);
    indataacc = mossfw_get_delivereddata_array(in->input, datasizeacc, &usedacc);
    assert(indataacc != NULL);
    indatagyr = mossfw_get_delivereddata_array(in->input->cb_next, datasizegyr, &usedgyr);
    assert(indatagyr != NULL);
    if (0 < datasizeline)
      {
        indataline = mossfw_get_delivereddata_array(in->input->cb_next->cb_next, datasizeline, &usedline);
        assert(indataline != NULL);
      }
    numacc  = datasizeacc / sizeof(mossfw_data_v3f_t);
    numgyr  = datasizegyr / sizeof(mossfw_data_v3f_t);
    numline = datasizegyr / sizeof(struct resampleinfo_s);

#ifdef DEBUG_OUTPUT
    printf("TransformAxes ACC num = %d\n", numacc);
    printf("TransformAxes GYR num = %d\n", numgyr);
#endif

    if (0 < datasizeline)
      {
        ret = mossfw_deliver_dataarray(geteis_errorpipeline()->transformaxes.out[TRANSFORMAXES_LINE], indataline);
        assert(ret == 0);
      }
    ret = mossfw_deliver_dataarray(geteis_errorpipeline()->transformaxes.out[TRANSFORMAXES_ACC], indataacc);
    assert(ret == 0);
    ret = mossfw_deliver_dataarray(geteis_errorpipeline()->transformaxes.out[TRANSFORMAXES_GYR], indatagyr);
    assert(ret == 0);
    mossfw_data_free(indataacc);
    mossfw_data_free(indatagyr);
    mossfw_data_free(indataline);
    return ret;
}

void transformaxes_error_create(struct component_s *com)
{
  int i;

  if (com != NULL)
    {
      com->in_num  = TRANSFORMAXES_SIZE;
      com->out_num = TRANSFORMAXES_SIZE;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      com->in[TRANSFORMAXES_ACC]   = mossfw_input_create(TRANSFORMAXES_INPUTTYPE_ACC,  1);
      com->in[TRANSFORMAXES_GYR]   = mossfw_input_create(TRANSFORMAXES_INPUTTYPE_GYR,  1);
      com->in[TRANSFORMAXES_LINE]  = mossfw_input_create(TRANSFORMAXES_INPUTTYPE_LINE, 1);
      com->out[TRANSFORMAXES_ACC]  = mossfw_output_create(TRANSFORMAXES_OUTPUTTYPE_ACC);
      com->out[TRANSFORMAXES_GYR]  = mossfw_output_create(TRANSFORMAXES_OUTPUTTYPE_GYR);
      com->out[TRANSFORMAXES_LINE] = mossfw_output_create(TRANSFORMAXES_OUTPUTTYPE_LINE);
      com->op[0]  = mossfw_callback_op_create(transformaxes_operate_cb, 0, false);
      mossfw_set_waitcondition(com->in[TRANSFORMAXES_ACC], sizeof(mossfw_data_v3f_t), com->op[0]);
      mossfw_set_waitcondition(com->in[TRANSFORMAXES_GYR], sizeof(mossfw_data_v3f_t), com->op[0]);
      mossfw_set_waitcondition(com->in[TRANSFORMAXES_LINE], 1,                            com->op[0]);
    }
}

void transformaxes_error_delete(struct component_s *com)
{
    component_delete(com);
}
