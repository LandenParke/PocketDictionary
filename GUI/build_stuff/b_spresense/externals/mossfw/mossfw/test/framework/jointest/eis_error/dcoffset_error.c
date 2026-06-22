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
#include "eis_error/dcoffset_error.h"
#include "eis_error/resampleinfo_error.h"
#include "eis_error/eis_error.h"

#define DCOFFSET_INPUTTYPE_ACC  (MOSSFW_DATA_TYPE_FLOAT + \
                                 MOSSFW_DATA_TYPEGRP_V3 + \
                                 MOSSFW_DATA_TYPENAME_ACCEL + \
                                 MOSSFW_DATA_TYPEARRAY_ARRAY)
#define DCOFFSET_INPUTTYPE_GYR  (MOSSFW_DATA_TYPE_FLOAT + \
                                 MOSSFW_DATA_TYPEGRP_V3 + \
                                 MOSSFW_DATA_TYPENAME_GYRO + \
                                 MOSSFW_DATA_TYPEARRAY_ARRAY)
#define DCOFFSET_INPUTTYPE_LINE (MOSSFW_DATA_TYPEARRAY_ARRAY)
#define DCOFFSET_OUTPUTTYPE_ACC DCOFFSET_INPUTTYPE_ACC 
#define DCOFFSET_OUTPUTTYPE_GYR DCOFFSET_INPUTTYPE_GYR
#define DCOFFSET_OUTPUTTYPE_LINE DCOFFSET_INPUTTYPE_LINE

static int dcoffset_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    int ret = 0;
    int datasizeacc  = 0;
    int datasizegyr  = 0;
    int datasizeline = 0;
    int numacc  = 0;
    int numgyr  = 0;
    int numline = 0;
    mossfw_data_t *indataacc  = NULL;
    mossfw_data_t *indatagyr  = NULL;
    mossfw_data_t *indataline = NULL;
    int usedacc;
    int usedgyr;
    int usedline;
    size_t i;

    datasizeacc  = mossfw_get_delivereddata_num(in->input);
    datasizegyr  = mossfw_get_delivereddata_num(in->input->cb_next);
    datasizeline = mossfw_get_delivereddata_num(in->input->cb_next->cb_next);
    numacc  = datasizeacc  / sizeof(mossfw_data_v3f_t);
    numgyr  = datasizegyr  / sizeof(mossfw_data_v3f_t);
    numline = datasizeline / sizeof(struct resampleinfo_s);
    indataacc = mossfw_get_delivereddata_array(in->input, datasizeacc, &usedacc);
    assert(indataacc);
    indatagyr = mossfw_get_delivereddata_array(in->input->cb_next, datasizegyr, &usedgyr);
    assert(indatagyr);
    if (0 < datasizeline)
      {
        indataline = mossfw_get_delivereddata_array(in->input->cb_next->cb_next, datasizeline, &usedline);
      }
#ifdef DEBUG_OUTPUT
    printf("DCOffset ACC num = %d\n", numacc);
    for (i = 0; i < numacc; i++) {
        printf("DCOffset ACC %0.16f %0.16f %0.16f\n", indataacc->data.xyzf[i].x, indataacc->data.xyzf[i].y, indataacc->data.xyzf[i].z);
    }
    printf("DCOffset GYR num = %d\n", numgyr);
    for (i = 0; i < numgyr; i++) {
        printf("DCOffset GYR %0.16f %0.16f %0.16f\n", indatagyr->data.xyzf[i].x, indatagyr->data.xyzf[i].y, indatagyr->data.xyzf[i].z);
    }
#endif
    ret = mossfw_deliver_dataarray(geteis_errorpipeline()->dcoffset.out[2], indataline);
    assert(ret == 0);
    ret = mossfw_deliver_dataarray(geteis_errorpipeline()->dcoffset.out[0], indataacc);
    assert(ret == 0);
    ret = mossfw_deliver_dataarray(geteis_errorpipeline()->dcoffset.out[1], indatagyr);
    assert(ret == 0);
    mossfw_data_free(indataacc);
    mossfw_data_free(indatagyr);
    mossfw_data_free(indataline);
    return ret;
}

void dcoffset_error_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = DCOFFSET_SIZE;
      com->out_num = DCOFFSET_SIZE;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      com->in[DCOFFSET_ACC]   = mossfw_input_create(DCOFFSET_INPUTTYPE_ACC, 1);
      com->in[DCOFFSET_GYR]   = mossfw_input_create(DCOFFSET_INPUTTYPE_GYR, 1);
      com->in[DCOFFSET_LINE]  = mossfw_input_create(DCOFFSET_INPUTTYPE_LINE, 1);
      com->out[DCOFFSET_ACC]  = mossfw_output_create(DCOFFSET_OUTPUTTYPE_ACC);
      com->out[DCOFFSET_GYR]  = mossfw_output_create(DCOFFSET_OUTPUTTYPE_GYR);
      com->out[DCOFFSET_LINE] = mossfw_output_create(DCOFFSET_OUTPUTTYPE_LINE);
      com->op[0]  = mossfw_callback_op_create(dcoffset_operate_cb, 0, false);
      mossfw_set_waitcondition(com->in[DCOFFSET_ACC], sizeof(mossfw_data_v3f_t), com->op[0]);
      mossfw_set_waitcondition(com->in[DCOFFSET_GYR], sizeof(mossfw_data_v3f_t), com->op[0]);
      mossfw_set_waitcondition(com->in[DCOFFSET_LINE], 1,                            com->op[0]);
    }
}

void dcoffset_error_delete(struct component_s *com)
{
    component_delete(com);
}
