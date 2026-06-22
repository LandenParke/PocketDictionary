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

#ifndef SAMPLE_ATTITUDE_INPUT
#  define SAMPLE_ATTITUDE_INPUT

/****************************************************************************
 * Included Files
 ****************************************************************************/

#  include <stdint.h>
#  include "mossfw/sensorlib.h"
#  include "mossfw/mosscalib.h"
#  include "mossfw/components/eiscalibration.h"
#  include "mossfw/components/lpf.h"
#  include "mossfw/components/transform.h"
#  include "mossfw/components/averageacc.h"
#  include "mossfw/components/estimateposeacc.h"
#  include "mossfw/components/complementaryfilter.h"
#  include "stableacc.h"
#  include "output.h"

/****************************************************************************
 * Public Data Types
 ****************************************************************************/

struct attitude_s
  {
    mossfw_allocator_t *alloc3s;
    mossfw_allocator_t *alloc3f;
    mossfw_allocator_t *allocf;
    mossfw_allocator_t *allocs;
    mossfw_allocator_t *allocq;
    mossfw_output_t *sensoracc;
    mossfw_output_t *sensorgyr;
    struct eiscalibration_s *calib;
    struct lpf_s *lpf;
    struct transform_s *trans;
    struct averageacc_s *avg;
    struct stableacc_s *stbl;
    struct estimateposeacc_s *est;
    struct complementaryfilter_s *cf;
    struct output_s *output;
  };

struct attitude_s *sample_attitude_initialization(void);

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

void sample_attitude_set_averageacc_num(uint32_t num);
void sample_attitude_set_time_resolution(long nsec);
void sample_attitude_set_resolution(float acc_mps2, float gyr_dps);
void sample_attitude_set_calibration(struct mosscalib_adjust_param_s *acc,
                                     struct mosscalib_adjust_param_s *gyr);
void sample_attitude_set_transform(struct sqmatrix3f_s *transform);
void sample_attitude_reset_lpf(void);
int sample_attitude_input(struct attitude_s *attitude,
                          mossfw_data_v3ts_t *acc,
                          mossfw_data_v3ts_t *gyr,
                          uint32_t num);
void sample_attitude_finalization(struct attitude_s *attitude);

int8_t sample_attitude_init(void);
int8_t sample_attitude_unregister_init(void);

#endif
