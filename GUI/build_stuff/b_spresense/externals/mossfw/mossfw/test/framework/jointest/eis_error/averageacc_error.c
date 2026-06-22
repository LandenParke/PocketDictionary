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
#include "eis_error/averageacc_error.h"
#include "eis_error/eis_error.h"

#define AVERAGEACC_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPENAME_ACCEL + \
                                  MOSSFW_DATA_TYPEARRAY_ARRAY)
#define AVERAGEACC_OUTPUTTYPE_ACC AVERAGEACC_INPUTTYPE_ACC

static int averageacc_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    static unsigned int count = 0;
    static unsigned int accnum = 0;
    static mossfw_data_v3f_t accumulate = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
    int8_t ret = 0;
    size_t num = 0;
    int datasize;
    mossfw_data_t *indata;
    size_t i;
    int used;

    datasize = mossfw_get_delivereddata_num(in->input);
    indata = mossfw_get_delivereddata_array(in->input, datasize, &used);
    assert(indata != NULL);
    num = indata->data_bytes / sizeof(mossfw_data_v3f_t);

    if (count == 0) {
        accumulate.x = 0.0f;
        accumulate.y = 0.0f;
        accumulate.z = 0.0f;
        accnum = 0;
    }
    for (i = 0; i < num; i++) {
        accumulate.x += indata->data.xyzf[i].x;
        accumulate.y += indata->data.xyzf[i].y;
        accumulate.z += indata->data.xyzf[i].z;
    }
    accnum = accnum + num;
#ifdef DEBUG_OUTPUT
    printf("AverageAcc num = %d\n", num);
#endif
    if (count == 3) {
        indata->data.xyzf[0].x = accumulate.x / accnum;
        indata->data.xyzf[0].y = accumulate.y / accnum;
        indata->data.xyzf[0].z = accumulate.z / accnum;
        indata->data_bytes = sizeof(mossfw_data_v3f_t);
#ifdef DEBUG_OUTPUT
        printf("AverageAcc %.7e %.7e %.7e\n", indata->data.xyzf[0].x, indata->data.xyzf[0].y, indata->data.xyzf[0].z);
        fflush(stdout);
#endif
        ret = mossfw_deliver_dataarray(geteis_errorpipeline()->averageacc.out[0], indata);
        assert(ret == 0);
    }
    else
      {
        indata->data_bytes = 1;
        ret = mossfw_deliver_dataarray(geteis_errorpipeline()->averageacc.out[0], indata);
        assert(ret == 0);
      }
    mossfw_data_free(indata);
    count = count < 3 ? count + 1 : 0;
    return ret;
}

void averageacc_error_create(struct component_s *com)
{
  bool async = true; 
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      com->in[0]  = mossfw_input_create(AVERAGEACC_INPUTTYPE_ACC, 1);
      com->out[0] = mossfw_output_create(AVERAGEACC_OUTPUTTYPE_ACC);
      com->op[0]  = mossfw_callback_op_create(averageacc_operate_cb, 0, async);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_v3f_t), com->op[0]);
    }
}

void averageacc_error_delete(struct component_s *com)
{
    component_delete(com);
}
