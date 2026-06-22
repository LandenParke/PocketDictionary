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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mosscalib.h"
#include "mossfw/mossfw_component.h"
#include "component.h"
#include "eis_error/eisallocator_error.h"
#include "eis_error/eiscalibration_error.h"
#include "eis_error/eis_error.h"

#define EISCALIBRATION_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_SHORT + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPENAME_ACCEL + \
                                  MOSSFW_DATA_TYPEARRAY_ARRAY)
#define EISCALIBRATION_INPUTTYPE_GYR (MOSSFW_DATA_TYPE_SHORT + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPENAME_GYRO + \
                                  MOSSFW_DATA_TYPEARRAY_ARRAY)
#define EISCALIBRATION_OUTPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPENAME_ACCEL + \
                                  MOSSFW_DATA_TYPEARRAY_ARRAY)
#define EISCALIBRATION_OUTPUTTYPE_GYR (MOSSFW_DATA_TYPE_FLOAT + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPENAME_GYRO + \
                                  MOSSFW_DATA_TYPEARRAY_ARRAY)
#define EISCALIBRATION_MAXBLOCK (16 * 4)

static int eiscalibration_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
    int8_t ret = 0;
    mossfw_data_t *inmem = NULL;
    mossfw_data_t *outmem = NULL;
    size_t outsize;
    size_t size;
    size_t num;
    mossfw_data_v3f_t *outdata;
    enum eiscalibration_e outdataid;
    int used;
    size_t i;
    mossfw_allocator_t *allocator = NULL;

    size = mossfw_get_delivereddata_num(in->input);
    inmem = mossfw_get_delivereddata_array(in->input, size, &used);
    assert(inmem);
    num = inmem->data_bytes / sizeof(mossfw_data_v3s_t);
    outsize = num * sizeof(mossfw_data_v3f_t);
    outdata = (mossfw_data_v3f_t *)malloc(outsize);
    assert(outdata);

    if (arg == EISCALIBRATION_ACC0) {
        outdataid = EISCALIBRATION_ACC0;
        float coef = 208979584.0f;
        for (i = 0; i < num; i++) {
            outdata[i].x = inmem->data.v3s[i].x / coef;
            outdata[i].y = inmem->data.v3s[i].y / coef;
            outdata[i].z = inmem->data.v3s[i].z / coef;
#ifdef DEBUG_OUTPUT
            printf("ImuCalibration ACC0 %0.16f %0.16f %0.16f\n", outdata[i].x, outdata[i].y, outdata[i].z);
#endif
        }
    } else if (arg == EISCALIBRATION_GYR0) {
        outdataid = EISCALIBRATION_GYR0;
        float coef = 16400.0f;
        for (i = 0; i < num; i++) {
            outdata[i].x = inmem->data.v3s[i].x / coef;
            outdata[i].y = inmem->data.v3s[i].y / coef;
            outdata[i].z = inmem->data.v3s[i].z / coef;
#ifdef DEBUG_OUTPUT
            printf("ImuCalibration GYR0 %0.16f %0.16f %0.16f\n", outdata[i].x, outdata[i].y, outdata[i].z);
#endif
        }
    } else if (arg == EISCALIBRATION_ACC1) {
        struct mosscalib_adjust_param_s param = {
            .bias.f = {.x = -0.00000009124391909f, .y = 0.00000013157300316f, .z = 0.00000061742110802f},
	        .scalefactor = {
                .x = {.x = 0.9932296872138977f, .y = 0.0f,                .z = 0.0f},
                .y = {.x = 0.0f,                .y = 0.9976474046707153f, .z = 0.0f},
                .z = {.x = 0.0f,                .y = 0.0f,                .z = 0.9727051854133606f}
	        },
	        .misalignment = {
                .x = {.x = 1.0f, .y = 0.0022878649178892f, .z = -0.0111410999670625f},
                .y = {.x = 0.0f, .y = 1.0000000000000000f, .z =  0.0018858800176531f},
                .z = {.x = 0.0f, .y = 0.0000000000000000f, .z =  1.0000000000000000f}
	        }
       	};
        outdataid = EISCALIBRATION_ACC1;
        float coef = 208979584.0f;
        for (i = 0; i < num; i++) {
            outdata[i].x = inmem->data.v3s[i].x / coef;
            outdata[i].y = inmem->data.v3s[i].y / coef;
            outdata[i].z = inmem->data.v3s[i].z / coef;
        }
        mosscalib_adjustv3f(outdata, outdata, num, 0.0f, &param);
#ifdef DEBUG_OUTPUT
        for (i = 0; i < num; i++) {
            printf("ImuCalibration ACC1 %0.16f %0.16f %0.16f\n", outdata[i].x, outdata[i].y, outdata[i].z);
        }
#endif
    } else {  /* EISCALIBRATION_GYR1 */
        struct mosscalib_adjust_param_s param = {
            .bias.f = {.x = -0.00012497810530476f, .y = -0.00121626199688762f, .z = 0.00112496595829725f},
	        .scalefactor = {
                .x = {.x = 0.9784178137779236f, .y = 0.0f,                .z = 0.0f},
                .y = {.x = 0.0f,                .y = 1.0078259706497192f, .z = 0.0f},
                .z = {.x = 0.0f,                .y = 0.0f,                .z = 0.9969930052757263f}
	        },
	        .misalignment = {
                .x = {.x =  1.0f,                .y =  0.0048000421375036f, .z = -0.0103387897834182f},
                .y = {.x = -0.0065536201000214f, .y =  1.0f,                .z =  0.0002426705032121f},
                .z = {.x =  0.0087586073204875f, .y = -0.0016777249984443f, .z =  1.0f               }
	        }
        };
        outdataid = EISCALIBRATION_GYR1;
        float coef = 16400.0f;
        for (i = 0; i < num; i++) {
            outdata[i].x = inmem->data.v3s[i].x / coef;
            outdata[i].y = inmem->data.v3s[i].y / coef;
            outdata[i].z = inmem->data.v3s[i].z / coef;
        }
        mosscalib_adjustv3f(outdata, outdata, num, 0.0f, &param);
#ifdef DEBUG_OUTPUT
        for (i = 0; i < num; i++) {
            printf("ImuCalibration GYR1 %0.16f %0.16f %0.16f\n", outdata[i].x, outdata[i].y, outdata[i].z);
        }
#endif
    }

    allocator = eisallocator_error_getallocator();
    assert(allocator != NULL);
    assert(sizeof(mossfw_data_v3f_t) * num < EISALLOCATOR_SIZE);
    outmem = mossfw_data_alloc(allocator, EISALLOCATOR_SIZE, true);
    assert(outmem != NULL);
    for (i = 0; i < num; i++)
      {
        outmem->data.xyzf[i].x = outdata[i].x;
        outmem->data.xyzf[i].y = outdata[i].y;
        outmem->data.xyzf[i].z = outdata[i].z;
      }
    outmem->data_bytes = outsize;

    struct eispipeline_error_s *pipeline = geteis_errorpipeline();
    assert(pipeline != NULL);
    mossfw_output_t *output;
    if (arg == EISCALIBRATION_ACC0)
      {
        output = pipeline->eiscalibrationacc0.out[0];
      }
    else if (arg == EISCALIBRATION_GYR0)
      {
        output = pipeline->eiscalibrationgyr0.out[0];
      }
    else if (arg == EISCALIBRATION_ACC1)
      {
        output = pipeline->eiscalibrationacc1.out[0];
      }
    else if (arg == EISCALIBRATION_GYR1)
      {
        output = pipeline->eiscalibrationgyr1.out[0];
      }
    
    ret = mossfw_deliver_dataarray(output, outmem);
    assert(ret == 0);
    mossfw_data_free(inmem);
    mossfw_data_free(outmem);
    free(outdata);
    return ret;
}

void eiscalibration_error_create(struct component_s *com, enum eiscalibration_e type)
{
  bool async = false;
  if (com != NULL)
    {
      com->in_num  = 1;
      com->out_num = 1;
      com->op_num  = 1;
      com->in      = malloc(com->in_num  * sizeof(void *));
      com->out     = malloc(com->out_num * sizeof(void *));
      com->op      = malloc(com->op_num  * sizeof(void *));
      if (type == EISCALIBRATION_ACC0 || type == EISCALIBRATION_ACC1)
        {
          com->in[0]  = mossfw_input_create(EISCALIBRATION_INPUTTYPE_ACC, 1);
          com->out[0] = mossfw_output_create(EISCALIBRATION_OUTPUTTYPE_ACC);
        }
      else /* EISCALIBRATION_GYR0 || EISCALIBRATION_GYR1 */
        {
          com->in[0]  = mossfw_input_create(EISCALIBRATION_INPUTTYPE_GYR, 1);
          com->out[0] = mossfw_output_create(EISCALIBRATION_OUTPUTTYPE_GYR);
        }
      if (type == EISCALIBRATION_ACC0)
        {
          async = true;
        }
      else if (type == EISCALIBRATION_GYR0)
        {
          async = true;
        }
      else if (type == EISCALIBRATION_ACC1)
        {
          async = true;
        }
      else if (type == EISCALIBRATION_GYR1)
        {
          async = true;
        }
      com->op[0]  = mossfw_callback_op_create(eiscalibration_operate_cb, (unsigned long)type, async);
      mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_v3s_t), com->op[0]);
    }
}

void eiscalibration_error_delete(struct component_s *com)
{
    component_delete(com);
}
