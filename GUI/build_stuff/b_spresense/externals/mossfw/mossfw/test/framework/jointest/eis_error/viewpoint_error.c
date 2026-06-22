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
#include "eis_error/viewpoint_error.h"
#include "eis_error/eis_error.h"

#define VIEWPOINT_INPUTTYPE (MOSSFW_DATA_TYPE_FLOAT + \
                            MOSSFW_DATA_TYPEGRP_Q + \
                            MOSSFW_DATA_TYPEARRAY_ARRAY)
#define VIEWPOINT_OUTPUTTYPE VIEWPOINT_INPUTTYPE

static int viewpoint_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    int ret = 0;
    int num = 0;
    int datasize;
    mossfw_data_t *indata;
    size_t i;
    int used = 0;

    datasize = mossfw_get_delivereddata_num(in->input);
    indata = mossfw_get_delivereddata_array(in->input, datasize, &used);
    if (indataid == 0) {
        num = datasize / sizeof(mossfw_data_qf_t);
#ifdef DEBUG_OUTPUT
        printf("ViewPoint POSE num = %d\n", num);
        for (i = 0; i < num; i++) {
            printf("ViewPoint %0.16f %0.16f %0.16f %0.16f\n", indata->data.qf[i].w, indata->data.qf[i].x, indata->data.qf[i].y, indata->data.qf[i].z);
        }
#endif
        ret = mossfw_deliver_dataarray(geteis_errorpipeline()->viewpoint.out[0], indata);
        assert(ret == 0);
    }
    mossfw_data_free(indata);
    return ret;
}

void viewpoint_error_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      com->in[0]  = mossfw_input_create(VIEWPOINT_INPUTTYPE, 2);
      com->out[0] = mossfw_output_create(VIEWPOINT_OUTPUTTYPE);
      com->op[0]  = mossfw_callback_op_create(viewpoint_operate_cb, 0, false);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_qf_t), com->op[0]);
    }
}

void viewpoint_error_delete(struct component_s *com)
{
    component_delete(com);
}
