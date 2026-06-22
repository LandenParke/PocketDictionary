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
#include <float.h>
#include <string.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_component.h"
#include "component.h"
#include "eis_error/resampleinfo_error.h"
#include "eis_error/poseresample_error.h"
#include "eis_error/eisallocator_error.h"
#include "eis_error/eis_error.h"

#define POSERESAMPLE_INPUTTYPE_ROT (MOSSFW_DATA_TYPE_FLOAT + \
                                MOSSFW_DATA_TYPEGRP_Q + \
                                MOSSFW_DATA_TYPEARRAY_ARRAY)

#define POSERESAMPLE_INPUTTYPE_LINE (MOSSFW_DATA_TYPEARRAY_ARRAY)
#define POSERESAMPLE_OUTPUTTYPE POSERESAMPLE_INPUTTYPE_ROT

static mossfw_data_t *poseresample(mossfw_data_t *line, int numline, mossfw_data_t *rot, int numrot, mossfw_allocator_t *alloc)
{
    mossfw_data_t *outmem = NULL;
    struct resampleinfo_s *info;
    int i;

    assert(line);
    assert(0 < numline);
    assert(alloc);

    info = (void *)line->data.v1c;
    if (rot)
      {
        outmem = mossfw_data_alloc(alloc, EISALLOCATOR_SIZE, true);
        assert(outmem);
        assert(numline * sizeof(mossfw_data_qf_t) < EISALLOCATOR_SIZE);

        for (i = 0; i < numline; i++)
          {
            assert(info[i].q1idx < numrot);
            outmem->data.qf[i].w = rot->data.qf[info[i].q1idx].w;
            outmem->data.qf[i].x = rot->data.qf[info[i].q1idx].x;
            outmem->data.qf[i].y = rot->data.qf[info[i].q1idx].y;
            outmem->data.qf[i].z = rot->data.qf[info[i].q1idx].z;
          }
        outmem->data_bytes = numline * sizeof(mossfw_data_qf_t);
      }
    return outmem;
}

static int poseresample_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    mossfw_data_t *indatarot = NULL;
    int numrot = 0;
    int datasizerot = 0;
    mossfw_data_t *indataline = NULL;
    mossfw_data_t *outmem = NULL;
    mossfw_allocator_t *alloc = NULL;
    int8_t ret = 0;
    int numline = 0;
    int datasizeline = 0;
    int usedrot  = 0;
    int usedline = 0;

    datasizerot  = mossfw_get_delivereddata_num(in->input);
    datasizeline = mossfw_get_delivereddata_num(in->input->cb_next);
    numrot = datasizerot / sizeof(mossfw_data_qf_t);

#ifdef DEBUG_OUTPUT
    printf("PoseResample POSE num = %d, LINE num = %d\n", numrot, numline);
#endif

    if (0 < datasizerot)
      {
        indatarot = mossfw_get_delivereddata_array(in->input, datasizerot, &usedrot);
        assert(indatarot != NULL);
#ifdef DEBUG_OUTPUT
        for (int i = 0; i < numrot; i++)
          {
            printf("PoseResample %.7e %.7e %.7e %.7e\n", indatarot->data.qf[i].w, indatarot->data.qf[i].x, indatarot->data.qf[i].y, indatarot->data.qf[i].z);
          }
#endif
      }
    indataline = mossfw_get_delivereddata_array(in->input->cb_next, datasizeline, &usedline);
    numline = indataline->data_bytes / sizeof(struct resampleinfo_s);
    assert(indataline != NULL);
    if (0 < numline)
      {
#ifdef DEBUG_OUTPUT
        struct resampleinfo_s *info;
        int i;

        info = (void *)indataline->data.v1c;
        for (i = 0; i < numline; i++)
          {
            printf("PoseResample %d %d %d %d %d\n", info->slerpflg, info->q1idx, info->q2idx, info->line1, info->line2);
          }
#endif
        alloc = eisallocator_error_getallocator();
        assert(alloc);
        assert(numline * sizeof(mossfw_data_qf_t) <= EISALLOCATOR_SIZE);
        outmem = poseresample(indataline, numline, indatarot, numrot, alloc);
        assert(outmem);
#ifdef DEBUG_OUTPUT
        for (int i = 0; i < numline; i++)
          {
            printf("PoseResample %e %e %e %e\n", outmem->data.qf[i].w, outmem->data.qf[i].x, outmem->data.qf[i].y, outmem->data.qf[i].z);
          }
#endif
        ret = mossfw_deliver_dataarray(geteis_errorpipeline()->poseresample.out[0], outmem);
        assert(ret == 0);
      }
    mossfw_data_free(indatarot);
    mossfw_data_free(indataline);
    mossfw_data_free(outmem);
    return ret;
}

void poseresample_error_create(struct component_s *com)
{
  int ret;

  if (com != NULL)
    {
      com->in_num  = POSERESAMPLE_SIZE;
      com->out_num = 1;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      com->in[POSERESAMPLE_ROT]  = mossfw_input_create(POSERESAMPLE_INPUTTYPE_ROT, 2);
      com->in[POSERESAMPLE_LINE] = mossfw_input_create(POSERESAMPLE_INPUTTYPE_LINE, 2);
      com->out[0] = mossfw_output_create(POSERESAMPLE_OUTPUTTYPE);
      com->op[0]  = mossfw_callback_op_create(poseresample_operate_cb, 0, false);
      ret = mossfw_set_waitcondition(com->in[POSERESAMPLE_ROT], sizeof(mossfw_data_qf_t), com->op[0]);
      assert(ret == 0);
      ret = mossfw_set_waitcondition(com->in[POSERESAMPLE_LINE], 1,                          com->op[0]);
      assert(ret == 0);
    }
}

void poseresample_error_delete(struct component_s *com)
{
    component_delete(com);
}
