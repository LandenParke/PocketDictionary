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
#include <assert.h>

#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "component.h"

#include "attitude.h"
#include "attitudesource.h"
#include "attitude_eiscalibration.h"
#include "attitude_lpf.h"
#include "attitude_transform.h"
#include "attitude_averageacc.h"
#include "attitude_stableacc.h"
#include "attitude_estimateposeacc.h"
#include "attitude_complementaryfilter.h"
#include "attituderesult.h"


void attitudepipeline_create(struct attitudepipeline_s *pipeline)
{
  if (pipeline != NULL) {

    // initialize components
    attitudesource_create(&(pipeline->attitudesource));
    attitude_eiscalibration_create(&(pipeline->eiscalib_acc), EISCALIBRATION_ACC);
    attitude_eiscalibration_create(&(pipeline->eiscalib_gyr), EISCALIBRATION_GYR);
    attitude_lpf_reset();
    attitude_lpf_create(&(pipeline->lpf_acc), LPF_ACC);
    attitude_lpf_create(&(pipeline->lpf_gyr), LPF_GYR);
    attitude_transform_create(&(pipeline->transform_acc), TRANSFORM_ACC);
    attitude_transform_create(&(pipeline->transform_gyr), TRANSFORM_GYR);
    attitude_average_acc_create(&(pipeline->average_acc));
    attitude_stable_acc_create(&(pipeline->stable_acc));
    attitude_estimate_poseacc_create(&(pipeline->estimate_poseacc));
    attitude_complementaryfilter_reset();
    attitude_complementaryfilter_create(&(pipeline->complementary_filter_gyr),COMPLEMENTARYFILTER_GYR);
    attitude_complementaryfilter_create(&(pipeline->complementary_filter_rot),COMPLEMENTARYFILTER_ROT);
    attituderesult_create(&(pipeline->result));

    /* Bind data path */
    /*
     * +----------+     +-------------+    +-----+    +---------- +    +---------+    +--------+    +----------+     +---------------+     +--------+
     * |          | --> | Eis         | -> | LPF | -> | Transform | -> | Average | -> | Stable | -> | Estimate | --> |               |     |        |
     * | attitude | acc | Calibration |    |     |    |           |    | ACC     |    | ACC    |    | PoseACC  | rot | Complementary |     | result |
     * | source   |     + ------------+    +-----+    +-----------+    +---------+    +--------+    +----------+     | Filter        | --> |        |
     * |          |                                                                                                  |               | rot |        |
     * |          |     +-------------+    +-----+    +---------- +                                                  |               |     |        |
     * |          | --> | Eis         | -> | LPF | -> | Transform | -----------------------------------------------> |               |     |        |
     * |          | gyr | Calibration |    |     |    |           |                                                  |               |     |        |
     * |          |     +-------------+    +-----+    +-----------+                                                  +---------------+     +--------+
     * |          |                                                                 
     * +----------+ 
     */

    mossfw_bind_inout(pipeline->attitudesource.out[ATTITUDESOURCE_ACC], *pipeline->eiscalib_acc.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->eiscalib_acc.out, *pipeline->lpf_acc.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->lpf_acc.out, *pipeline->transform_acc.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->transform_acc.out, *pipeline->average_acc.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->average_acc.out, *pipeline->stable_acc.in, (uint32_t)-1);
    mossfw_bind_inout(pipeline->stable_acc.out[ATTITUDESOURCE_ACC], pipeline->estimate_poseacc.in[ATTITUDESOURCE_ACC], (uint32_t)-1);
    mossfw_bind_inout(pipeline->stable_acc.out[ATTITUDESOURCE_GYR], pipeline->estimate_poseacc.in[ATTITUDESOURCE_GYR], (uint32_t)-1);
    mossfw_bind_inout(*pipeline->estimate_poseacc.out, *pipeline->complementary_filter_rot.in, (uint32_t)-1);

    mossfw_bind_inout(pipeline->attitudesource.out[ATTITUDESOURCE_GYR], *pipeline->eiscalib_gyr.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->eiscalib_gyr.out, *pipeline->lpf_gyr.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->lpf_gyr.out, *pipeline->transform_gyr.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->transform_gyr.out, *pipeline->complementary_filter_gyr.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->complementary_filter_gyr.out, *pipeline->result.in, (uint32_t)-1);
  }
}

void attitudepipeline_delete(struct attitudepipeline_s *pipeline)
{
  attitudesource_delete(&(pipeline->attitudesource));
  attitude_eiscalibration_delete(&(pipeline->eiscalib_acc));
  attitude_eiscalibration_delete(&(pipeline->eiscalib_gyr));
  attitude_lpf_delete(&(pipeline->lpf_acc));
  attitude_lpf_delete(&(pipeline->lpf_gyr));
  attitude_transform_delete(&(pipeline->transform_acc));
  attitude_transform_delete(&(pipeline->transform_gyr));
  attitude_average_acc_delete(&(pipeline->average_acc));
  attitude_stable_acc_delete(&(pipeline->stable_acc));
  attitude_estimate_delete(&(pipeline->estimate_poseacc));
  attitude_complementaryfilter_delete(&(pipeline->complementary_filter_gyr));
  attitude_complementaryfilter_delete(&(pipeline->complementary_filter_rot));
  attituderesult_delete(&(pipeline->result));
}

static  struct attitudepipeline_s pipeline;

struct attitudepipeline_s *getattitudepipeline(void)
{
    return &pipeline;
}

void attitude(void)
{

  attitudepipeline_create(&pipeline);
  (*pipeline.attitudesource.op)->operate(*pipeline.attitudesource.op, 0);
  attitudepipeline_delete(&pipeline);
  assert(attituderesult_succeeded() == 0);
  printf("framework jointest attitude passed\n");
}
