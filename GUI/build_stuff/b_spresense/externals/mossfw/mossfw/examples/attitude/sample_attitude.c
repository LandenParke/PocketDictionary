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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossfw_data.h"
#include "mossfw/components/complementaryfilter.h"
#include "mossfw/components/eiscalibration.h"
#include "mossfw/components/averageacc.h"
#include "mossfw/components/lpf.h"
#include "mossfw/components/transform.h"
#include "mossfw/components/averageacc.h"
#include "mossfw/components/estimateposeacc.h"
#include "stableacc.h"
#include "sample_attitude.h"

/****************************************************************************
 * Public Data
 ****************************************************************************/

struct attitude_s *sample_attitude_initialization(void)
{
  int err = 0;

  struct attitude_s *att =
    (struct attitude_s *)malloc(sizeof(struct attitude_s));
  if (att)
    {
      uint32_t type =
        MOSSFW_DATA_TYPE_SHORT | MOSSFW_DATA_TYPEGRP_V3 |
        MOSSFW_DATA_TYPEARRAY_ARRAY;
      uint32_t typea = type | MOSSFW_DATA_TYPENAME_ACCEL;
      uint32_t typeg = type | MOSSFW_DATA_TYPENAME_GYRO;
      size_t size3s = sizeof(mossfw_data_v3s_t);
      size_t size3f = sizeof(mossfw_data_v3f_t);
      size_t sizes = sizeof(mossfw_data_v1s_t);
      size_t sizef = sizeof(mossfw_data_v1f_t);
      size_t sizeq = sizeof(mossfw_data_qf_t);
      att->alloc3s = mossfw_fixedmem_create(size3s, 10);
      att->alloc3f = mossfw_fixedmem_create(size3f, 10);
      att->allocf = mossfw_fixedmem_create(sizef, 10);
      att->allocs = mossfw_fixedmem_create(sizes, 5);
      att->allocq = mossfw_fixedmem_create(sizeq, 10);
      att->sensoracc = mossfw_output_create(typea);
      att->sensorgyr = mossfw_output_create(typeg);
      att->calib = eiscalibration_create(att->alloc3f);
      att->lpf = lpf_create(att->alloc3f);
      att->trans = transform_create(att->alloc3f);
      att->avg = averageacc_create(att->alloc3f);
      att->stbl = stableacc_create(att->allocs);
      att->est = estimateposeacc_create(att->allocf);
      att->cf = complementaryfilter_create(att->allocf, att->allocq);
      att->output = output_create();
      err = err || !att->alloc3s || !att->alloc3f;
      err = err || !att->allocf || !att->allocq;
      err = err || !att->sensoracc || !att->sensorgyr;
      err = err || !att->calib;
      err = err || !att->lpf;
      err = err || !att->trans;
      err = err || !att->avg;
      err = err || !att->stbl;
      err = err || !att->est;
      err = err || !att->cf;
      uint32_t msk = 0xffffffff;
      err = err || mossfw_bind_inout(att->sensoracc, att->calib->inacc, msk);
      err = err || mossfw_bind_inout(att->sensorgyr, att->calib->ingyr, msk);
      err = err || mossfw_bind_inout(att->calib->outacc,
                                     att->lpf->inacc, msk);
      err = err || mossfw_bind_inout(att->calib->outgyr,
                                     att->lpf->ingyr, msk);
      err = err || mossfw_bind_inout(att->lpf->outacc,
                                     att->trans->inacc, msk);
      err = err || mossfw_bind_inout(att->lpf->outgyr,
                                     att->trans->ingyr, msk);
      err = err || mossfw_bind_inout(att->trans->outacc,
                                     att->avg->input, msk);
      err = err || mossfw_bind_inout(att->avg->output,
                                     att->stbl->input, msk);
      err = err || mossfw_bind_inout(att->stbl->outacc,
                                     att->est->inacc, msk);
      err = err || mossfw_bind_inout(att->stbl->outstbl,
                                     att->est->instbl, msk);
      err = err || mossfw_bind_inout(att->trans->outgyr,
                                     att->cf->ingyr, msk);
      err = err || mossfw_bind_inout(att->est->outr, att->cf->inrotr, msk);
      err = err || mossfw_bind_inout(att->est->outi, att->cf->inroti, msk);
      err = err || mossfw_bind_inout(att->cf->outr, att->output->inr, msk);
      err = err || mossfw_bind_inout(att->cf->outi, att->output->ini, msk);
    }
  if (err)
    {
      sample_attitude_finalization(att);
      att = NULL;
    }
  return att;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: sample_attitude_set_time_resolution
 ****************************************************************************/

void sample_attitude_set_time_resolution(long nsec)
{
  complementaryfilter_set_time_resolution(nsec);
}

/****************************************************************************
 * name: sample_attitude_set_resolution
 ****************************************************************************/

void sample_attitude_set_resolution(float acc_mps2, float gyr_dps)
{
  calibration_set_resolution(acc_mps2, gyr_dps);
}

/****************************************************************************
 * name: sample_attitude_set_calibration
 ****************************************************************************/

void sample_attitude_set_calibration(struct mosscalib_adjust_param_s *acc,
                                     struct mosscalib_adjust_param_s *gyr)
{
  calibration_set_param(acc, gyr);
}

/****************************************************************************
 * name: sample_attitude_set_transform
 ****************************************************************************/

void sample_attitude_set_transform(struct sqmatrix3f_s *transform)
{
  transform_set_param(transform);
}

/****************************************************************************
 * name: sample_attitude_set_averageacc_num
 ****************************************************************************/

void sample_attitude_set_averageacc_num(uint32_t num)
{
  averageacc_setnum(num);
}

/****************************************************************************
 * name: sample_attitude_reset_lpf
 ****************************************************************************/

void sample_attitude_reset_lpf(void)
{
  lpf_reset();
}

/****************************************************************************
 * name: sample_attitude_input
 ****************************************************************************/

int sample_attitude_input(struct attitude_s *att,
                          mossfw_data_v3ts_t *acc, mossfw_data_v3ts_t *gyr,
                          uint32_t num)
{
  int err = 0;
  for (uint32_t i = 0; i < num && !err; i++)
    {
      size_t size = sizeof(mossfw_data_v3s_t);
      mossfw_data_t *dataacc =
        mossfw_data_alloc(att->alloc3s, size * num, true);
      mossfw_data_t *datagyr =
        mossfw_data_alloc(att->alloc3s, size * num, true);
      err = err || dataacc == NULL;
      err = err || datagyr == NULL;
      if (!err)
        {
          datagyr->data_bytes = sizeof(mossfw_data_v3s_t);
          datagyr->timestamp = gyr[i].t;
          datagyr->data.xyzs[i].x = gyr[i].x;
          datagyr->data.xyzs[i].y = gyr[i].y;
          datagyr->data.xyzs[i].z = gyr[i].z;
          err = err || mossfw_deliver_dataarray(att->sensorgyr, datagyr);
          dataacc->data_bytes = sizeof(mossfw_data_v3s_t);
          dataacc->timestamp = acc[i].t;
          dataacc->data.xyzs[i].x = acc[i].x;
          dataacc->data.xyzs[i].y = acc[i].y;
          dataacc->data.xyzs[i].z = acc[i].z;
          err = err || mossfw_deliver_dataarray(att->sensoracc, dataacc);
        }

      mossfw_data_free(dataacc);
      mossfw_data_free(datagyr);
    }

  return err;
}

/****************************************************************************
 * name: sample_attitude_finalization
 ****************************************************************************/

void sample_attitude_finalization(struct attitude_s *att)
{
  if (att != NULL)
    {
      complementaryfilter_delete(att->cf);
      estimateposeacc_delete(att->est);
      stableacc_delete(att->stbl);
      averageacc_delete(att->avg);
      transform_delete(att->trans);
      lpf_delete(att->lpf);
      eiscalibration_delete(att->calib);
      mossfw_output_delete(att->sensoracc);
      mossfw_output_delete(att->sensorgyr);
      mossfw_fixedmem_delete(att->alloc3s);
      mossfw_fixedmem_delete(att->alloc3f);
      mossfw_fixedmem_delete(att->allocf);
      mossfw_fixedmem_delete(att->allocs);
      mossfw_fixedmem_delete(att->allocq);
    }

  free(att);
}
