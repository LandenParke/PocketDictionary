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
#include "eis/resampleinfo.h"
#include "eis/poseresample.h"
#include "eis/eisallocator.h"
#include "eis/eis.h"

#define POSERESAMPLE_INPUTTYPE_ROT (MOSSFW_DATA_TYPE_FLOAT + \
                                MOSSFW_DATA_TYPEGRP_Q + \
                                MOSSFW_DATA_TYPEARRAY_ARRAY)
#define POSERESAMPLE_INPUTTYPE_INDEX (MOSSFW_DATA_TYPE_INT32 + \
                                      MOSSFW_DATA_TYPEGRP_V3 + \
                                      MOSSFW_DATA_TYPEARRAY_ARRAY)
#define POSERESAMPLE_INPUTTYPE_LINE  (MOSSFW_DATA_TYPE_INT32 + \
                                      MOSSFW_DATA_TYPEGRP_V2 + \
                                      MOSSFW_DATA_TYPEARRAY_ARRAY)
#define POSERESAMPLE_OUTPUTTYPE POSERESAMPLE_INPUTTYPE_ROT

static mossfw_data_t *poseresample(mossfw_data_t *index, int numindex, mossfw_data_t *rot, int numrot, mossfw_allocator_t *alloc)
{
    mossfw_data_t *outmem = NULL;
    int i;

    assert(index);
    assert(0 < numindex);
    assert(alloc);

    if (rot)
      {
        outmem = mossfw_data_alloc(alloc, EISALLOCATOR_SIZE, true);
        assert(outmem);
        assert(numindex * sizeof(mossfw_data_qf_t) < EISALLOCATOR_SIZE);

        for (i = 0; i < numindex; i++)
          {
            assert(index->data.xyzi32[i].y < numrot);
            outmem->data.qf[i].w = rot->data.qf[index->data.xyzi32[i].y].w;
            outmem->data.qf[i].x = rot->data.qf[index->data.xyzi32[i].y].x;
            outmem->data.qf[i].y = rot->data.qf[index->data.xyzi32[i].y].y;
            outmem->data.qf[i].z = rot->data.qf[index->data.xyzi32[i].y].z;
          }
        outmem->data_bytes = numindex * sizeof(mossfw_data_qf_t);
      }
    return outmem;
}

static int poseresample_operate_cb(struct mossfw_callback_op_s *in, unsigned long indataid)
{
    mossfw_data_t *indatarot   = NULL;
    mossfw_data_t *indataindex = NULL;
    mossfw_data_t *indataline  = NULL;
    mossfw_data_t *outmem      = NULL;
    mossfw_allocator_t *alloc = NULL;
    int8_t ret = 0;
    int usedrot   = 0;
    int usedindex = 0;
    int usedline  = 0;

    int datasizerot   = mossfw_get_delivereddata_num(in->input);
    int datasizeindex = mossfw_get_delivereddata_num(in->input->cb_next);
    int datasizeline  = mossfw_get_delivereddata_num(in->input->cb_next->cb_next);
    int numrot   = datasizerot   / sizeof(mossfw_data_qf_t);
#ifdef DEBUG_OUTPUT
    printf("PoseResample POSE num = %d, LINE num = %d\n", numrot, numindex);
#endif

    if (0 < datasizerot)
      {
        indatarot = mossfw_get_delivereddata_array(in->input, datasizerot, &usedrot);
        assert(indatarot != NULL);
#ifdef DEBUG_OUTPUT
        int i;
        for (i = 0; i < numrot; i++)
          {
            printf("PoseResample %.7e %.7e %.7e %.7e\n", indatarot->data.qf[i].w, indatarot->data.qf[i].x, indatarot->data.qf[i].y, indatarot->data.qf[i].z);
          }
#endif
      }
    indataindex = mossfw_get_delivereddata_array(in->input->cb_next,         datasizeindex, &usedindex);
    assert(indataindex != NULL);
    indataline = mossfw_get_delivereddata_array(in->input->cb_next->cb_next, datasizeline,  &usedline);
    assert(indataline != NULL);
    int numindex = indataindex->data_bytes / sizeof(mossfw_data_v3i32_t);
    int numline  = indataline->data_bytes  / sizeof(mossfw_data_v2i32_t);
    assert(numindex == numline);
    if (0 < numindex && 0 < numline)
      {
#ifdef DEBUG_OUTPUT
	mossfw_data_v3i32_t *index = indataindex->data.xyzi32;
	mossfw_data_v2i32_t  *line  = indataline->data.xyi32;
        for (int i = 0; i < numindex; i++)
          {
            printf("PoseResample %d %d %d %d %d\n", index[i].x, index[i].y, index[i].z, line[i].x, line[i].y);
          }
#endif
        alloc = eisallocator_getallocator();
        assert(alloc);
        assert(numindex * sizeof(mossfw_data_qf_t) <= EISALLOCATOR_SIZE);
        outmem = poseresample(indataindex, numindex, indatarot, numrot, alloc);
        assert(outmem);
#ifdef DEBUG_OUTPUT
        int i;
        for (i = 0; i < numindex; i++)
          {
            printf("PoseResample %e %e %e %e\n", outmem->data.qf[i].w, outmem->data.qf[i].x, outmem->data.qf[i].y, outmem->data.qf[i].z);
          }
#endif
        ret = mossfw_deliver_dataarray(geteispipeline()->poseresample.out[0], outmem);
        assert(ret == 0);
      }
    mossfw_data_free(indatarot);
    mossfw_data_free(indataindex);
    mossfw_data_free(indataline);
    mossfw_data_free(outmem);
    return ret;
}

void poseresample_create(struct component_s *com)
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
      com->in[POSERESAMPLE_INDEX] = mossfw_input_create(POSERESAMPLE_INPUTTYPE_INDEX, 2);
      com->in[POSERESAMPLE_LINE]  = mossfw_input_create(POSERESAMPLE_INPUTTYPE_LINE,  2);
      com->out[0] = mossfw_output_create(POSERESAMPLE_OUTPUTTYPE);
      com->op[0]  = mossfw_callback_op_create(poseresample_operate_cb, 0, false);
      ret = mossfw_set_waitcondition(com->in[POSERESAMPLE_ROT], sizeof(mossfw_data_qf_t), com->op[0]);
      assert(ret == 0);
      ret = mossfw_set_waitcondition(com->in[POSERESAMPLE_INDEX],   1,                          com->op[0]);
      assert(ret == 0);
      ret = mossfw_set_waitcondition(com->in[POSERESAMPLE_LINE],    1,                          com->op[0]);
      assert(ret == 0);
    }
}

void poseresample_delete(struct component_s *com)
{
    component_delete(com);
}
