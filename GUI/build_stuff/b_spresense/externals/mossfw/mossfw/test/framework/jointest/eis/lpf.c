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
#include <string.h>
#include <assert.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossdsp.h"
#include "mossfw/mossfw_component.h"
#include "component.h"
#include "eis/lpf.h"
#include "eis/eisallocator.h"
#include "eis/eis.h"

#define FILTER_COEFFICIENT_SIZE 13

#define LPF_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPENAME_ACCEL + \
                           MOSSFW_DATA_TYPEARRAY_ARRAY)
#define LPF_INPUTTYPE_GYR (MOSSFW_DATA_TYPE_FLOAT + \
                           MOSSFW_DATA_TYPEGRP_V3 + \
                           MOSSFW_DATA_TYPENAME_GYRO + \
                           MOSSFW_DATA_TYPEARRAY_ARRAY)
#define LPF_OUTPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                            MOSSFW_DATA_TYPEGRP_V3 + \
                            MOSSFW_DATA_TYPENAME_ACCEL + \
                            MOSSFW_DATA_TYPEARRAY_ARRAY)
#define LPF_OUTPUTTYPE_GYR (MOSSFW_DATA_TYPE_FLOAT + \
                            MOSSFW_DATA_TYPEGRP_V3 + \
                            MOSSFW_DATA_TYPENAME_GYRO + \
                            MOSSFW_DATA_TYPEARRAY_ARRAY)


static float acc0coefficients[] = {
    0.0675159991f,  0.0720349997f,    0.0758979991f, 0.0790079981f,
    0.0812890008f,  0.0826800019f,    0.0831480026f, 0.0826800019f,
    0.0812890008f,  0.0790079981f,    0.0758979991f, 0.0720349997f,
    0.0675159991f
};

static float gyr0coefficients[] = {
    0.0465199985f, -0.000923309999f, -0.072958f,    -0.0598339997f,
    0.0924530029f,  0.297890007f,     0.393700004f,  0.297890007f,
    0.0924530029f, -0.0598339997f,   -0.072958f,    -0.000923309999f,
    0.0465199985f
};

static float acc1coefficients[] = {
    0.0637490004f,  0.0699850023f,    0.0754000023f, 0.0798150003f, 
    0.0830819979f,  0.0850870013f,    0.0857639983f, 0.0850870013f,
    0.0830819979f,  0.0798150003f,    0.0754000023f, 0.0699850023f,
    0.0637490004f
};

static float gyr1coefficients[] = {
    0.000874990015f, 0.0581309982f, -0.000905640016f, -0.0995739996f,
    0.000924279972f, 0.3028f,        0.475510001f,     0.3028f,
    0.000924279972f, -0.0995739996f, -0.000905640016f, 0.0581309982f,
    0.000874990015f
};

static mossfw_data_v3f_t acc0lastdata[] = {
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f}
};
 
static mossfw_data_v3f_t gyr0lastdata[] = {
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f}
};

static mossfw_data_v3f_t acc1lastdata[] = {
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f}
};

static mossfw_data_v3f_t gyr1lastdata[] = {
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f}, {.x = 0.0f, .y = 0.0f, .z = 0.0f}
};
 
static struct mossdsp_firfilter_param_s acc0param = {
    .coefficients.f = acc0coefficients,
    .cnum = 13,
    .lastdata.v3f = acc0lastdata,
    .lnum = 12,
    .delay = 0
};
static struct mossdsp_firfilter_param_s gyr0param = {
    .coefficients.f = gyr0coefficients,
    .cnum = 13,
    .lastdata.v3f = gyr0lastdata,
    .lnum = 12,
    .delay = 0
};
static struct mossdsp_firfilter_param_s acc1param = {
    .coefficients.f = acc1coefficients,
    .cnum = 13,
    .lastdata.v3f = acc1lastdata,
    .lnum = 12,
    .delay = 0
};
static struct mossdsp_firfilter_param_s gyr1param = {
    .coefficients.f = gyr1coefficients,
    .cnum = 13,
    .lastdata.v3f = gyr1lastdata,
    .lnum = 12,
    .delay = 0
};

static int acc0count = 0;
static int acc1count = 0;
static int gyr0count = 0;
static int gyr1count = 0;

static mossfw_data_v3f_t acc0buf;
static mossfw_data_v3f_t acc1buf;
static mossfw_data_v3f_t gyr0buf;
static mossfw_data_v3f_t gyr1buf;

static void initparam(struct mossdsp_firfilter_param_s *param, mossfw_data_v3f_t *indata)
{
    size_t i;
    for (i = 0; i < param->cnum / 2; i++) {
        param->lastdata.v3f[i] = indata[0];
    }
    for (i = param->cnum / 2; i < param->lnum; i++) {
        param->lastdata.v3f[i] = indata[i - param->cnum / 2];
    }
}

static void updateparam(struct mossdsp_firfilter_param_s *param, mossfw_data_v3f_t *indata)
{
    size_t i;
    for (i = 0; i < param->lnum; i++) {
        param->lastdata.v3f[i] = indata[i];
    }
}

static void print(unsigned long arg, mossfw_data_t *outbuf, size_t size)
{
    mossfw_data_t *out = NULL;
    size_t i;

    if (arg == LPF_ACC0) {
        out = outbuf;
        printf("LPF ACC\n");
    } else if (arg == LPF_GYR0) {
        out = outbuf;
        printf("LPF GYR\n");
    } else if (arg == LPF_ACC1) {
        out = outbuf;
        printf("LPF ACC\n");
    } else if (arg == LPF_GYR1) {
        out = outbuf;
        printf("LPF GYR\n");
    }
    for (i = 0; out != NULL && i < size / sizeof(mossfw_data_v3f_t); i++)
      {
        printf("LPF %0.16f %0.16f %0.16f\n", outbuf->data.xyzf[i].x, outbuf->data.xyzf[i].y, outbuf->data.xyzf[i].z);
      }
}

static int lpf_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
    int ret = 0;
    int num = 0;
    int data_size;
    mossfw_data_v3f_t *indata;
    mossfw_data_v3f_t *outbuf = NULL;
    mossfw_data_v3f_t *inbuf = NULL;
    size_t outnum = 0;
    size_t calnum = 0;
    size_t outbufnum = 0;
    size_t inbufnum = 0;
    size_t inoffset = 0;
    size_t caloffset = 0;
    size_t outsize = 0;
    mossfw_data_t *inmem = NULL;
    mossfw_data_t *outmem = NULL;
    int i;
    int used;
    mossfw_allocator_t *allocator = NULL;

    data_size = mossfw_get_delivereddata_num(in->input);
    inmem = mossfw_get_delivereddata_array(in->input, data_size, &used);
    assert(inmem);
    num = inmem->data_bytes / sizeof(mossfw_data_v3f_t);
    indata = malloc(num * sizeof(mossfw_data_v3f_t));
    for (i = 0; i < num; i++)
      {
          indata[i].x = inmem->data.xyzf[i].x;
          indata[i].y = inmem->data.xyzf[i].y;
          indata[i].z = inmem->data.xyzf[i].z;
      }

    if (arg == LPF_ACC0) {
        if (acc0count == 0) {
            initparam(&acc0param, indata);
            inoffset = FILTER_COEFFICIENT_SIZE / 2;
            caloffset = 0;
            calnum = num - inoffset;
            outnum = num - inoffset - 1;
            outbufnum = num - inoffset;
            inbufnum = num;
        } else if (acc0count == 3) {
            inoffset  = 0;
            caloffset = 1;
            calnum    = num + FILTER_COEFFICIENT_SIZE / 2;
            outnum    = num + FILTER_COEFFICIENT_SIZE / 2 + 1;
            outbufnum = num + FILTER_COEFFICIENT_SIZE / 2 + 1;
            inbufnum  = num + FILTER_COEFFICIENT_SIZE / 2;
        } else {
            inoffset = 0;
            caloffset = 1;
            calnum = num;
            outnum = num;
            outbufnum = num + 1;
            inbufnum = num;
        }
        outsize = outnum * sizeof(mossfw_data_v3f_t);
        outbuf = (mossfw_data_v3f_t *)malloc(outbufnum * sizeof(mossfw_data_v3f_t));
        inbuf  = (mossfw_data_v3f_t *)malloc(inbufnum * sizeof(mossfw_data_v3f_t));
        memcpy(inbuf, indata, num * sizeof(mossfw_data_v3f_t));
        for (i = 0; i < inbufnum - num; i++) inbuf[num + i] = indata[num - 1];
        outbuf[0] = acc0buf;
        mossdsp_firfilterv3f(&outbuf[caloffset], &inbuf[inoffset], calnum, &acc0param);
        updateparam(&acc0param, &indata[num - acc0param.lnum]);
        acc0buf = outbuf[caloffset + calnum - 1];
        acc0count = acc0count < 3 ? acc0count + 1 : 0;
    } else if (arg == LPF_GYR0) {
        if (gyr0count == 0) {
            initparam(&gyr0param, indata);
            inoffset = FILTER_COEFFICIENT_SIZE / 2;
            caloffset = 0;
            calnum = num - inoffset;
            outnum = num - inoffset - 1;
            outbufnum = num - inoffset;
            inbufnum = num;
        } else if (gyr0count == 3) {
            inoffset  = 0;
            caloffset = 1;
            calnum    = num + FILTER_COEFFICIENT_SIZE / 2;
            outnum    = num + FILTER_COEFFICIENT_SIZE / 2 + 1;
            outbufnum = num + FILTER_COEFFICIENT_SIZE / 2 + 1;
            inbufnum  = num + FILTER_COEFFICIENT_SIZE / 2;
        } else {
            inoffset = 0;
            caloffset = 1;
            calnum = num;
            outnum = num;
            outbufnum = num + 1;
            inbufnum = num;
        }
        outsize = outnum * sizeof(mossfw_data_v3f_t);
        outbuf = (mossfw_data_v3f_t *)malloc(outbufnum * sizeof(mossfw_data_v3f_t));
        inbuf  = (mossfw_data_v3f_t *)malloc( inbufnum * sizeof(mossfw_data_v3f_t));
        memcpy(inbuf, indata, num * sizeof(mossfw_data_v3f_t));
        for (i = 0; i < inbufnum - num; i++) inbuf[num + i] = indata[num - 1];
        outbuf[0] = gyr0buf;
        mossdsp_firfilterv3f(&outbuf[caloffset], &inbuf[inoffset], calnum, &gyr0param);
        updateparam(&gyr0param, &indata[num - gyr0param.lnum]);
        gyr0buf = outbuf[caloffset + calnum - 1];
        gyr0count = gyr0count < 3 ? gyr0count + 1 : 0;
    } else if (arg == LPF_ACC1) {
        if (acc1count == 0) {
            initparam(&acc1param, indata);
            inoffset = FILTER_COEFFICIENT_SIZE / 2;
            caloffset = 0;
            calnum = num - inoffset;
            outnum = num - inoffset - 1;
            outbufnum = num - inoffset;
            inbufnum = num;
        } else if (acc1count == 3) {
            inoffset  = 0;
            caloffset = 1;
            calnum    = num + FILTER_COEFFICIENT_SIZE / 2;
            outnum    = num + FILTER_COEFFICIENT_SIZE / 2 + 1;
            outbufnum = num + FILTER_COEFFICIENT_SIZE / 2 + 1;
            inbufnum  = num + FILTER_COEFFICIENT_SIZE / 2;
        } else {
            inoffset = 0;
            caloffset = 1;
            calnum = num;
            outnum = num;
            outbufnum = num + 1;
            inbufnum = num;
        }
        outsize = outnum * sizeof(mossfw_data_v3f_t);
        outbuf = (mossfw_data_v3f_t *)malloc(outbufnum * sizeof(mossfw_data_v3f_t));
        inbuf  = (mossfw_data_v3f_t *)malloc( inbufnum * sizeof(mossfw_data_v3f_t));
        memcpy(inbuf, indata, num * sizeof(mossfw_data_v3f_t));
        for (i = 0; i < inbufnum - num; i++) inbuf[num + i] = indata[num - 1];
        outbuf[0] = acc1buf;
        mossdsp_firfilterv3f(&outbuf[caloffset], &inbuf[inoffset], calnum, &acc1param);
        updateparam(&acc1param, &indata[num - acc1param.lnum]);
        acc1buf = outbuf[caloffset + calnum - 1];
        acc1count = acc1count < 3 ? acc1count + 1 : 0;
    } else {  /* LPF_GYR1 */
        if (gyr1count == 0) {
            initparam(&gyr1param, indata);
            inoffset = FILTER_COEFFICIENT_SIZE / 2;
            caloffset = 0;
            calnum = num - inoffset;
            outnum = num - inoffset - 1;
            outbufnum = num - inoffset;
            inbufnum = num;
        } else if (gyr1count == 3) {
            inoffset  = 0;
            caloffset = 1;
            calnum    = num + FILTER_COEFFICIENT_SIZE / 2;
            outnum    = num + FILTER_COEFFICIENT_SIZE / 2 + 1;
            outbufnum = num + FILTER_COEFFICIENT_SIZE / 2 + 1;
            inbufnum  = num + FILTER_COEFFICIENT_SIZE / 2;
        } else {
            inoffset = 0;
            caloffset = 1;
            calnum = num;
            outnum = num;
            outbufnum = num + 1;
            inbufnum = num;
        }
        outsize = outnum * sizeof(mossfw_data_v3f_t);
        outbuf = (mossfw_data_v3f_t *)malloc(outbufnum * sizeof(mossfw_data_v3f_t));
        inbuf  = (mossfw_data_v3f_t *)malloc( inbufnum * sizeof(mossfw_data_v3f_t));
        memcpy(inbuf, indata, num * sizeof(mossfw_data_v3f_t));
        for (i = 0; i < inbufnum - num; i++) inbuf[num + i] = indata[num - 1];
        outbuf[0] = gyr1buf;
        mossdsp_firfilterv3f(&outbuf[caloffset], &inbuf[inoffset], calnum, &gyr1param);
        updateparam(&gyr1param, &indata[num - gyr1param.lnum]);
        gyr1buf = outbuf[caloffset + calnum - 1];
        gyr1count = gyr1count < 3 ? gyr1count + 1 : 0;
    }
    allocator = eisallocator_getallocator();
    assert(allocator != NULL);
    assert(outnum * sizeof(mossfw_data_v3f_t) <= EISALLOCATOR_SIZE);
    outmem = mossfw_data_alloc(allocator, EISALLOCATOR_SIZE, true);
    assert(outmem);
    for (i = 0; i < outnum; i++)
      {
        outmem->data.xyzf[i].x = outbuf[i].x;
        outmem->data.xyzf[i].y = outbuf[i].y;
        outmem->data.xyzf[i].z = outbuf[i].z;
      }
    outmem->data_bytes = outsize;
#ifdef DEBUG_OUTPUT
    print(arg, outmem, outsize);
#endif
    mossfw_output_t *outacc0 = geteispipeline()->lpfacc0.out[0];
    mossfw_output_t *outgyr0 = geteispipeline()->lpfgyr0.out[0];
    mossfw_output_t *outacc1 = geteispipeline()->lpfacc1.out[0];
    mossfw_output_t *outgyr1 = geteispipeline()->lpfgyr1.out[0];
    mossfw_output_t *output;
    if (arg == LPF_ACC0)
      {
        output = outacc0;
      }
    else if (arg == LPF_GYR0)
      {
        output = outgyr0;
      }
    else if (arg == LPF_ACC1)
      {
        output = outacc1;
      }
    else
      {
        output = outgyr1;
      }
    ret = mossfw_deliver_dataarray(output, outmem);
    assert(ret == 0);
    free(outbuf);
    free(inbuf);
    free(indata);
    mossfw_data_free(inmem);
    mossfw_data_free(outmem);
    return ret;
}

void lpf_create(struct component_s *com, enum lpf_e type)
{
  if (com != NULL)
    {
      com->in_num    = 1;
      com->out_num   = 1;
      com->op_num    = 1;
      com->in        = malloc(com->in_num    * sizeof(void *));
      com->out       = malloc(com->out_num   * sizeof(void *));
      com->op        = malloc(com->op_num    * sizeof(void *));
      if (type == LPF_ACC0 || type == LPF_ACC1)
        {
          com->in[0]  = mossfw_input_create(LPF_INPUTTYPE_ACC, 1);
          com->out[0] = mossfw_output_create(LPF_OUTPUTTYPE_ACC);
        }
      else
        {
          com->in[0]  = mossfw_input_create(LPF_INPUTTYPE_GYR, 1);
          com->out[0] = mossfw_output_create(LPF_OUTPUTTYPE_GYR);
        }
      com->op[0]  = mossfw_callback_op_create(lpf_operate_cb, (unsigned long)type, false);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_v3f_t), com->op[0]);
    }
}

void lpf_delete(struct component_s *com)
{
    component_delete(com);
}
