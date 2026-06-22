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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_component.h"
#include "component.h"
#include "eis/selector.h"
#include "eis/resampleinfo.h"
#include "eis/eis.h"

#define SELECTOR_INPUTTYPE_ACC  (MOSSFW_DATA_TYPE_FLOAT + \
                                 MOSSFW_DATA_TYPEGRP_V3 + \
                                 MOSSFW_DATA_TYPENAME_ACCEL + \
                                 MOSSFW_DATA_TYPEARRAY_ARRAY)
#define SELECTOR_INPUTTYPE_GYR  (MOSSFW_DATA_TYPE_FLOAT + \
                                 MOSSFW_DATA_TYPEGRP_V3 + \
                                 MOSSFW_DATA_TYPENAME_GYRO + \
                                 MOSSFW_DATA_TYPEARRAY_ARRAY)
#define SELECTOR_INPUTTYPE_INDEX (MOSSFW_DATA_TYPE_INT32 + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPEARRAY_ARRAY)
#define SELECTOR_INPUTTYPE_LINE (MOSSFW_DATA_TYPE_INT32 + \
                                 MOSSFW_DATA_TYPEGRP_V2 + \
                                 MOSSFW_DATA_TYPEARRAY_ARRAY)
#define SELECTOR_INPUTTYPE_OFFSET (MOSSFW_DATA_TYPE_SHORT + \
                                   MOSSFW_DATA_TYPEGRP_V1 + \
                                   MOSSFW_DATA_TYPEARRAY_SINGLE)
#define SELECTOR_OUTPUTTYPE_ACC   SELECTOR_INPUTTYPE_ACC
#define SELECTOR_OUTPUTTYPE_GYR   SELECTOR_INPUTTYPE_GYR
#define SELECTOR_OUTPUTTYPE_INDEX SELECTOR_INPUTTYPE_INDEX
#define SELECTOR_OUTPUTTYPE_LINE  SELECTOR_INPUTTYPE_LINE
#define get_time_eis(x)

int selector_setoffset (mossfw_input_t *input, unsigned long indataid)
{
    int ret;
    mossfw_onedata_t data;
    unsigned int offset = 0;
    ret = mossfw_get_delivereddata_single(input, &data);
    assert(ret == sizeof(short));
    offset = data.xs.x;
    return offset;
}

int selector_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    int8_t ret = 0;
    int datasizesel  = 0;
    size_t numacc   = 0;
    size_t numgyr   = 0;
    size_t numindex = 0;
    size_t numline  = 0;
    mossfw_input_t *inputsel  = NULL;
    mossfw_data_t *indataacc  = NULL;
    mossfw_data_t *indatagyr  = NULL;
    mossfw_data_t *indataindex = NULL;
    mossfw_data_t *indataline = NULL;
    size_t outsizeacc;
    size_t outsizegyr;
    size_t i;
    int used;
    int usedindex;
    int usedline;
    int offset = 0;

    mossfw_input_t *inputacc   = in->input;
    mossfw_input_t *inputgyr   = inputacc->cb_next;
    mossfw_input_t *inputindex = inputgyr->cb_next;
    mossfw_input_t *inputline  = inputindex->cb_next;

    mossfw_output_t *outputacc;
    mossfw_output_t *outputgyr;
    mossfw_output_t *outputindex;
    mossfw_output_t *outputline;

    if (indataid == SELECTOR0)
      {
        outputacc   = geteispipeline()->selector.out[SELECTOR0_ACC];
        outputgyr   = geteispipeline()->selector.out[SELECTOR0_GYR];
        outputindex = geteispipeline()->selector.out[SELECTOR0_INDEX];
        outputline  = geteispipeline()->selector.out[SELECTOR0_LINE];
      }
    else
      {
        outputacc   = geteispipeline()->selector.out[SELECTOR1_ACC];
        outputgyr   = geteispipeline()->selector.out[SELECTOR1_GYR];
        outputindex = geteispipeline()->selector.out[SELECTOR1_INDEX];
        outputline  = geteispipeline()->selector.out[SELECTOR1_LINE];
      }
    
    int datasizeacc   = mossfw_get_delivereddata_num(inputacc);
    int datasizegyr   = mossfw_get_delivereddata_num(inputgyr);
    int datasizeindex = mossfw_get_delivereddata_num(inputindex);
    int datasizeline  = mossfw_get_delivereddata_num(inputline);
    indataacc  = mossfw_get_delivereddata_array(inputacc, datasizeacc, &used);
    assert(indataacc != NULL);
    numacc  = (size_t)datasizeacc / sizeof(mossfw_data_v3f_t);
    indatagyr  = mossfw_get_delivereddata_array(inputgyr, datasizegyr, &used);
    assert(indatagyr != NULL);
    numgyr  = (size_t)datasizegyr / sizeof(mossfw_data_v3f_t);
    indataindex = mossfw_get_delivereddata_array(inputindex, datasizeindex, &usedindex);
    indataline = mossfw_get_delivereddata_array(inputline, datasizeline, &usedline);
    assert(indataindex);
    assert(indataline);
    numindex = (size_t)datasizeindex / sizeof(mossfw_data_v3i32_t);
    numline  = (size_t)datasizeline  / sizeof(mossfw_data_v2i32_t);
    if (indataid == SELECTOR0) {
#ifdef DEBUG_OUTPUT
        printf("DEBUG selector_operate_cb() 0 numacc = %lu, numgyr = %lu, numline = %lu\n", numacc, numgyr, numline);
#endif
        ret = mossfw_deliver_dataarray(outputindex, indataindex);
        assert(ret == 0);
        ret = mossfw_deliver_dataarray(outputline, indataline);
        assert(ret == 0);
        ret = mossfw_deliver_dataarray(outputacc, indataacc);
        assert(ret == 0);
        ret = mossfw_deliver_dataarray(outputgyr, indatagyr);
        assert(ret == 0);
      }
    else if (indataid == SELECTOR1)
      {
        inputsel = inputline->cb_next;
        datasizesel = mossfw_get_delivereddata_num(inputsel);
#ifdef DEBUG_OUTPUT
        printf("DEBUG selector_operate_cb() 1 numacc = %lu, numgyr = %lu, numline = %lu, numsel = %lu\n", numacc, numgyr, numline, datasizesel / 2);
#endif
        if (0 < datasizesel)
          {
              offset = selector_setoffset(inputsel, indataid);
          }
        numacc = offset < numacc ? numacc - offset : 0;
        outsizeacc = numacc * sizeof(mossfw_data_v3f_t);
        if (offset != 0)
          {
            for (i = 0; i < numacc; i++)
              {
                indataacc->data.xyzf[i] = indataacc->data.xyzf[i + offset];
              }
            indataacc->data_bytes = outsizeacc;
          }
#ifdef DEBUG_OUTPUT
        printf("Selector ACC1 num = %d\n", numacc);
        for (i = 0; i < numacc; i++)
          {
            printf("Selector ACC %0.16f %0.16f %0.16f\n", indataacc->data.xyzf[i].x, indataacc->data.xyzf[i].y, indataacc->data.xyzf[i].z);
          }
#endif
        numgyr = offset < numgyr ? numgyr - offset : 0;
        outsizegyr = numgyr * sizeof(mossfw_data_v3f_t);
        if (offset != 0)
          {
            for (i = 0; i < numgyr; i++)
              {
                indatagyr->data.xyzf[i] = indatagyr->data.xyzf[i + offset];
              }
          }
        indatagyr->data_bytes = outsizegyr;
#ifdef DEBUG_OUTPUT
        printf("Selector GYR1 num = %d\n", numgyr);
        for (i = 0; i < numgyr; i++)
          {
            printf("Selector GYR %0.16f %0.16f %0.16f\n", indatagyr->data.xyzf[i].x, indatagyr->data.xyzf[i].y, indatagyr->data.xyzf[i].z);
          }
#endif
        ret = mossfw_deliver_dataarray(outputindex, indataindex);
        assert(ret == 0);
        ret = mossfw_deliver_dataarray(outputline, indataline);
        assert(ret == 0);
        ret = mossfw_deliver_dataarray(outputacc, indataacc);
        assert(ret == 0);
        ret = mossfw_deliver_dataarray(outputgyr, indatagyr);
        assert(ret == 0);
      }
    else
      {
        assert(0);
      }
    mossfw_data_free(indataacc);
    mossfw_data_free(indatagyr);
    mossfw_data_free(indataindex);
    mossfw_data_free(indataline);
    offset = 0;
    return ret;
}

void selector_create(struct component_s *com, int type)
{
  int i;
  if (com != NULL)
    {
      com->in_num  = SELECTOR_SIZE;
      com->out_num = SELECTOR_SIZE;
      com->op_num  = 2;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      for (i = 0; i < com->in_num; i++)
        {
          com->in[i] = NULL;
        }
      for (i = 0; i < com->out_num; i++)
        {
          com->out[i] = NULL;
        }
      for (i = 0; i < com->op_num; i++)
        {
          com->op[i] = NULL;
        }
      com->in[SELECTOR0_ACC]   = mossfw_input_create(SELECTOR_INPUTTYPE_ACC,    1);
      com->in[SELECTOR0_GYR]   = mossfw_input_create(SELECTOR_INPUTTYPE_GYR,    1);
      com->in[SELECTOR0_INDEX] = mossfw_input_create(SELECTOR_INPUTTYPE_INDEX,  1);
      com->in[SELECTOR0_LINE]  = mossfw_input_create(SELECTOR_INPUTTYPE_LINE,   1);
      com->in[SELECTOR1_ACC]   = mossfw_input_create(SELECTOR_INPUTTYPE_ACC,    1);
      com->in[SELECTOR1_GYR]   = mossfw_input_create(SELECTOR_INPUTTYPE_GYR,    1);
      com->in[SELECTOR1_INDEX] = mossfw_input_create(SELECTOR_INPUTTYPE_INDEX,  1);
      com->in[SELECTOR1_LINE]  = mossfw_input_create(SELECTOR_INPUTTYPE_LINE,   1);
      com->in[SELECTOR_OFFSET] = mossfw_input_create(SELECTOR_INPUTTYPE_OFFSET, 5);
      com->out[SELECTOR0_ACC]   = mossfw_output_create(SELECTOR_OUTPUTTYPE_ACC);
      com->out[SELECTOR0_GYR]   = mossfw_output_create(SELECTOR_OUTPUTTYPE_GYR);
      com->out[SELECTOR0_INDEX] = mossfw_output_create(SELECTOR_OUTPUTTYPE_INDEX);
      com->out[SELECTOR0_LINE]  = mossfw_output_create(SELECTOR_OUTPUTTYPE_LINE);
      com->out[SELECTOR1_ACC]   = mossfw_output_create(SELECTOR_OUTPUTTYPE_ACC);
      com->out[SELECTOR1_GYR]   = mossfw_output_create(SELECTOR_OUTPUTTYPE_GYR);
      com->out[SELECTOR1_INDEX] = mossfw_output_create(SELECTOR_OUTPUTTYPE_INDEX);
      com->out[SELECTOR1_LINE]  = mossfw_output_create(SELECTOR_OUTPUTTYPE_LINE);
      com->op[0] = mossfw_callback_op_create(selector_operate_cb, SELECTOR0, false);
      com->op[1] = mossfw_callback_op_create(selector_operate_cb, SELECTOR1, false);
      mossfw_set_waitcondition(com->in[SELECTOR0_ACC], sizeof(mossfw_data_v3f_t), com->op[0]);
      mossfw_set_waitcondition(com->in[SELECTOR0_GYR], sizeof(mossfw_data_v3f_t), com->op[0]);
      mossfw_set_waitcondition(com->in[SELECTOR0_INDEX], 1,                           com->op[0]);
      mossfw_set_waitcondition(com->in[SELECTOR0_LINE],  1,                           com->op[0]);
      mossfw_set_waitcondition(com->in[SELECTOR1_ACC], sizeof(mossfw_data_v3f_t), com->op[1]);
      mossfw_set_waitcondition(com->in[SELECTOR1_GYR], sizeof(mossfw_data_v3f_t), com->op[1]);
      mossfw_set_waitcondition(com->in[SELECTOR1_INDEX], 1,                           com->op[1]);
      mossfw_set_waitcondition(com->in[SELECTOR1_LINE],  1,                           com->op[1]);
      mossfw_set_waitcondition(com->in[SELECTOR_OFFSET], sizeof(short),               com->op[1]);
    }
}

void selector_delete(struct component_s *com)
{
    int i;
    component_delete(com);
}
