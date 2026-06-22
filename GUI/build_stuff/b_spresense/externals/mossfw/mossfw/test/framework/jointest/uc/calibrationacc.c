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
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "component.h"
#include "calibrationacc.h"
#include "uc.h"

#define ACCMAX    10
#define DEVMOTION  3
#define ANGLE     45

#define CALIBRATIONACC_BLKNUM   (1)

#define CALIBRATIONACC_INPUTTYPE_ACC (MOSSFW_DATA_TYPE_FLOAT + \
                                      MOSSFW_DATA_TYPEGRP_V3 + \
                                      MOSSFW_DATA_TYPENAME_ACCEL + \
                                      MOSSFW_DATA_TYPEARRAY_ARRAY)

#define CALIBRATIONACC_INPUTTYPE_ROT (MOSSFW_DATA_TYPE_FLOAT + \
                                      MOSSFW_DATA_TYPEGRP_V1 + \
                                      MOSSFW_DATA_TYPEARRAY_ARRAY)

#define CALIBRATIONACC_OUTPUTTYPE (MOSSFW_DATA_TYPE_CHAR + \
                                   MOSSFW_DATA_TYPEGRP_V1 + \
                                   MOSSFW_DATA_TYPEARRAY_ARRAY)


static uint16_t component1_offset;
static mossfw_allocator_t *allocator = NULL;
static unsigned int accnum = 0;
static unsigned int rotnum = 0;

float xdeg = 0;
float ydeg = 0;

static int calibrationacc_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  static double accx[ACCMAX];
  static double accy[ACCMAX];
  static double accz[ACCMAX];
  static double rot[ACCMAX];
  static mossfw_data_t *accdata = NULL;
  static mossfw_data_t *rotdata = NULL;
  static int accdataused;
  static int rotdataused;
  mossfw_data_t *data;
  int sgn = 0;
  int ret = 0;
  double avg = 0.0;
  double dev = 0.0;
  int16_t offsetq;
  int16_t xdegq;
  int16_t ydegq;
  int sizeacc = 0;
  int sizerot = 0;

  sizeacc = mossfw_get_delivereddata_num(in->input);
  sizerot = mossfw_get_delivereddata_num(in->input->cb_next);

  if (0 < sizeacc && accnum < ACCMAX)
    {
      accdata = mossfw_get_delivereddata_array(in->input, sizeacc, &accdataused);
      assert(accdata);
      accx[accnum] = accdata->data.v3f[0].x;
      accy[accnum] = accdata->data.v3f[0].y;
      accz[accnum] = accdata->data.v3f[0].z;
      accnum++;
      mossfw_data_free(accdata);
    }
  if (0 < sizerot && rotnum < ACCMAX)
    {
      rotdata = mossfw_get_delivereddata_array(in->input->cb_next, sizerot, &rotdataused);
      assert(rotdata);
      rot[rotnum] = rotdata->data.v1f[0].x;
      rotnum++;
      mossfw_data_free(rotdata);
    }

  if (accnum == ACCMAX && rotnum == ACCMAX)
    {
      double sum = 0;
      uint8_t refc = 0;
      double sqsum = 0;
      for (int i = 0; i < ACCMAX; i++)
        {
          sum = sum + rot[i];
        }
      avg = sum / ACCMAX;
      for (int i = 0; i < ACCMAX; i++)
        {
          sqsum = sqsum + (rot[i] - avg) * (rot[i] - avg);
          if (100 > fabs(rot[i] - avg))
            {
              refc = i;
            }
        }
      dev = sqrt(sqsum / ACCMAX);
      if ((dev < DEVMOTION) && (avg > ANGLE) && (accz[refc] > 0))
        {
          sgn = (accz[refc] >= 0) ? 1 : -1;
        }
      double accxr = accx[refc];
      double accyr = accy[refc];
      offsetq = (int16_t)((90 * sgn - acos(accx[refc] / sqrt((accxr * accxr) + (accyr * accyr))) * 57.29583 * sgn) * 64.0f);
      xdegq = (int16_t)(xdeg * 64.0f);
      ydegq = (int16_t)(ydeg * 64.0f);

      data = mossfw_data_alloc(allocator, 6 * sizeof(mossfw_data_v1c_t), true);
      data->data.xc[0].x = (int8_t) (((int16_t) offsetq & 0xff00) >> 8);
      data->data.xc[1].x = (int8_t) (offsetq & 0x00ff);
      data->data.xc[2].x = (int8_t) (((int16_t) xdegq & 0xff00) >> 8);
      data->data.xc[3].x = (int8_t) (xdegq & 0x00ff);
      data->data.xc[4].x = (int8_t) (((int16_t) ydegq & 0xff00) >> 8);
      data->data.xc[5].x = (int8_t) (ydegq & 0x00ff);
      data->data_bytes = 6 * sizeof data->data.xc[0];
      mossfw_deliver_dataarray(getucpipeline()->calibrationacc.out[0], data);
      mossfw_data_free(data);
    }
    
  return ret;
}

void calibrationacc_create(struct component_s *com)
{
  int val;

  if (com != NULL)
    {
      com->in_num    = 2;
      com->out_num   = 1;
      com->op_num    = 1;
      com->in    = malloc(com->in_num  * sizeof(void *));
      com->out   = malloc(com->out_num * sizeof(void *));
      com->op    = malloc(com->op_num  * sizeof(void *));
      if (allocator == NULL)
        {
          allocator = mossfw_fixedmem_create(6 * sizeof(mossfw_data_v1c_t), 1);
          assert(allocator != NULL);
        }
      com->in[0] = mossfw_input_create(CALIBRATIONACC_INPUTTYPE_ACC, CALIBRATIONACC_BLKNUM);
      com->in[1] = mossfw_input_create(CALIBRATIONACC_INPUTTYPE_ROT, CALIBRATIONACC_BLKNUM);
      *com->out = mossfw_output_create(CALIBRATIONACC_OUTPUTTYPE);
      com->op[0] = mossfw_callback_op_create(calibrationacc_operate_cb, 0, false);
      val = mossfw_set_waitcondition(com->in[0], sizeof(mossfw_data_v3f_t), com->op[0]);
      assert(val == 0);
      val = mossfw_set_waitcondition(com->in[1], sizeof(mossfw_data_v1f_t), com->op[0]);
      assert(val == 0);
    }
    accnum = 0;
    rotnum = 0;
}

void calibrationacc_delete(struct component_s *com)
{
    component_delete(com);
    if (allocator != NULL)
      {
        mossfw_fixedmem_delete(allocator);
        allocator = NULL;
      }
}
