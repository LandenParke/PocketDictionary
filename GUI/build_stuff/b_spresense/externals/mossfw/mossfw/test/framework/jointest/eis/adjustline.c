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
#include "eis/adjustline.h"
#include "eis/resampleinfo.h"
#include "eis/eisallocator.h"
#include "eis/eis.h"

#define ADJUSTLINE_INPUTTYPE_ACC  (MOSSFW_DATA_TYPE_FLOAT + \
                                   MOSSFW_DATA_TYPEGRP_V3 + \
                                   MOSSFW_DATA_TYPENAME_ACCEL + \
                                   MOSSFW_DATA_TYPEARRAY_ARRAY)
#define ADJUSTLINE_INPUTTYPE_GYR  (MOSSFW_DATA_TYPE_FLOAT + \
                                   MOSSFW_DATA_TYPEGRP_V3 + \
                                   MOSSFW_DATA_TYPENAME_GYRO + \
                                   MOSSFW_DATA_TYPEARRAY_ARRAY)
#define ADJUSTLINE_INPUTTYPE_INDEX (MOSSFW_DATA_TYPE_INT32 + \
                                   MOSSFW_DATA_TYPEGRP_V3 + \
                                   MOSSFW_DATA_TYPEARRAY_ARRAY)
#define ADJUSTLINE_INPUTTYPE_LINE (MOSSFW_DATA_TYPE_INT32 + \
                                   MOSSFW_DATA_TYPEGRP_V2 + \
                                   MOSSFW_DATA_TYPEARRAY_ARRAY)
#define ADJUSTLINE_OUTPUTTYPE_ACC   ADJUSTLINE_INPUTTYPE_ACC 
#define ADJUSTLINE_OUTPUTTYPE_GYR   ADJUSTLINE_INPUTTYPE_GYR
#define ADJUSTLINE_OUTPUTTYPE_INDEX ADJUSTLINE_INPUTTYPE_INDEX
#define ADJUSTLINE_OUTPUTTYPE_LINE  ADJUSTLINE_INPUTTYPE_LINE

static int adjustline_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    int ret = 0;
    int sizeacc;
    int sizegyr;
    mossfw_data_t *dataacc  = NULL;
    mossfw_data_t *datagyr  = NULL;
    int accused  = 0;
    int gyrused  = 0;
    int lineused = 0;
    int indexused = 0;
    int err;

    mossfw_input_t *accinput = in->input;
    mossfw_input_t *gyrinput = in->input->cb_next;
    mossfw_input_t *indexinput = gyrinput->cb_next;
    mossfw_input_t *lineinput = indexinput->cb_next;

    mossfw_output_t **out0 = geteispipeline()->adjustline0.out;
    mossfw_output_t **out1 = geteispipeline()->adjustline1.out;
    mossfw_output_t **out = (indataid == ADJUSTLINE0 ? out0 : out1);

    mossfw_allocator_t *allocator = eisallocator_getallocator();
    assert(allocator != NULL);
    mossfw_data_t *emptyline  = mossfw_data_alloc(allocator, EISALLOCATOR_SIZE, true);
    mossfw_data_t *emptyindex = mossfw_data_alloc(allocator, EISALLOCATOR_SIZE, true);
    assert(emptyline != NULL);
    assert(emptyindex != NULL);
    emptyline->data_bytes = 1;
    emptyindex->data_bytes = 1;

    for (int i = 0; i < 3; i++)
      {
        sizeacc = mossfw_get_delivereddata_num(accinput);
        sizegyr = mossfw_get_delivereddata_num(gyrinput);
        assert(0 < sizeacc);
        assert(0 < sizegyr);
#ifdef DEBUG_OUTPUT
        printf("DEBUG adjustline_operate_cb() sizeacc = %d, sizegyr = %d\n", sizeacc, sizegyr);
#endif
        dataacc = mossfw_get_delivereddata_array(accinput, sizeacc, &accused);
        assert(dataacc);
        err = mossfw_deliver_dataarray(out[0], dataacc);
        assert(!err);
        mossfw_data_free(dataacc);

        datagyr = mossfw_get_delivereddata_array(gyrinput, sizegyr, &gyrused);
        assert(datagyr);
        err = mossfw_deliver_dataarray(out[1], datagyr);
        assert(!err);
        mossfw_data_free(datagyr);
        err = mossfw_deliver_dataarray(out[2], emptyindex);
        assert(!err);
        err = mossfw_deliver_dataarray(out[3], emptyline);
        assert(!err);
      }
 
    int sizeindex = mossfw_get_delivereddata_num(indexinput);
    int sizeline  = mossfw_get_delivereddata_num(lineinput);
    mossfw_data_t *dataindex = mossfw_get_delivereddata_array(indexinput, sizeindex, &indexused);
    assert(dataindex != NULL);
    mossfw_data_t *dataline = mossfw_get_delivereddata_array(lineinput, sizeline, &lineused);
    assert(dataline != NULL);
    err = mossfw_deliver_dataarray(out[2], dataindex);
    assert(!err);
    err = mossfw_deliver_dataarray(out[3], dataline);
    assert(!err);
    mossfw_data_free(dataindex);
    mossfw_data_free(dataline);

    sizeacc = mossfw_get_delivereddata_num(accinput);
    sizegyr = mossfw_get_delivereddata_num(gyrinput);
    assert(0 < sizeacc);
    assert(0 < sizegyr);
#ifdef DEBUG_OUTPUT
    printf("DEBUG adjustline_operate_cb() sizeacc = %d, sizegyr = %d\n", sizeacc, sizegyr);
#endif

    dataacc = mossfw_get_delivereddata_array(accinput, sizeacc, &accused);
    assert(dataacc);
    err = mossfw_deliver_dataarray(out[0], dataacc);
    assert(!err);
    mossfw_data_free(dataacc);

    datagyr = mossfw_get_delivereddata_array(gyrinput, sizegyr, &gyrused);
    assert(datagyr);
    err = mossfw_deliver_dataarray(out[1], datagyr);
    assert(!err);
    mossfw_data_free(datagyr);
    mossfw_data_free(emptyline);
    mossfw_data_free(emptyindex);

    return ret;
}

void adjustline_create(struct component_s *com, enum adjustline_e type)
{
  const bool async = true;
  if (com != NULL)
    {
      com->in_num    = ADJUSTLINE_SIZE;
      com->out_num   = ADJUSTLINE_SIZE;
      com->op_num    = 1;
      com->in        = malloc(com->in_num  * sizeof(void *));
      com->out       = malloc(com->out_num * sizeof(void *));
      com->op        = malloc(com->op_num  * sizeof(void *));
      com->in[ADJUSTLINE_ACC]  = mossfw_input_create(ADJUSTLINE_INPUTTYPE_ACC, 5);
      assert(com->in[ADJUSTLINE_ACC] != NULL);
      com->in[ADJUSTLINE_GYR]  = mossfw_input_create(ADJUSTLINE_INPUTTYPE_GYR, 5);
      assert(com->in[ADJUSTLINE_GYR] != NULL);
      com->in[ADJUSTLINE_INDEX] = mossfw_input_create(ADJUSTLINE_INPUTTYPE_INDEX, 1);
      assert(com->in[ADJUSTLINE_INDEX] != NULL);
      com->in[ADJUSTLINE_LINE] = mossfw_input_create(ADJUSTLINE_INPUTTYPE_LINE, 1);
      assert(com->in[ADJUSTLINE_LINE] != NULL);
      com->out[ADJUSTLINE_ACC] = mossfw_output_create(ADJUSTLINE_OUTPUTTYPE_ACC);
      assert(com->out[ADJUSTLINE_ACC] != NULL);
      com->out[ADJUSTLINE_GYR] = mossfw_output_create(ADJUSTLINE_OUTPUTTYPE_GYR);
      assert(com->out[ADJUSTLINE_GYR] != NULL);
      com->out[ADJUSTLINE_INDEX] = mossfw_output_create(ADJUSTLINE_OUTPUTTYPE_INDEX);
      assert(com->out[ADJUSTLINE_INDEX] != NULL);
      com->out[ADJUSTLINE_LINE] = mossfw_output_create(ADJUSTLINE_OUTPUTTYPE_LINE);
      assert(com->out[ADJUSTLINE_LINE] != NULL);
      com->op[0]  = mossfw_callback_op_create(adjustline_operate_cb, (unsigned long)type, async);
      assert(com->op[0] != NULL);
      mossfw_set_waitcondition(com->in[ADJUSTLINE_ACC], 169  * sizeof(mossfw_data_v3f_t),   com->op[0]);
      mossfw_set_waitcondition(com->in[ADJUSTLINE_GYR], 169  * sizeof(mossfw_data_v3f_t),   com->op[0]);
      mossfw_set_waitcondition(com->in[ADJUSTLINE_INDEX], 64 * sizeof(mossfw_data_v3i32_t), com->op[0]);
      mossfw_set_waitcondition(com->in[ADJUSTLINE_LINE],  64 * sizeof(mossfw_data_v2i32_t), com->op[0]);
    }
}

void adjustline_delete(struct component_s *com)
{
    int i;
    component_delete(com);
}
