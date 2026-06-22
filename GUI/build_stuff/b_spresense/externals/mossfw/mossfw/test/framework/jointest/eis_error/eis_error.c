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
#include "eis_error/eisallocator_error.h"
#include "eis_error/eissource_error.h"
#include "eis_error/eiscalibration_error.h"
#include "eis_error/lpf_error.h"
#include "eis_error/transform_error.h"
#include "eis_error/adjustline_error.h"
#include "eis_error/selector_error.h"
#include "eis_error/transformaxes_error.h"
#include "eis_error/dcoffset_error.h"
#include "eis_error/averageacc_error.h"
#include "eis_error/stableacc_error.h"
#include "eis_error/estimateposeacc_error.h"
#include "eis_error/complementaryfilter_error.h"
#include "eis_error/axisseparation_error.h"
#include "eis_error/viewpoint_error.h"
#include "eis_error/poseresample_error.h"
#include "eis_error/eissink_error.h"
#include "eis_error/eis_error.h"

void eispipeline_error_create(struct eispipeline_error_s *pipeline)
{
  int ret;
  if (pipeline != NULL) {

    // initialize components
    eisallocator_error_create();
    eissource_error_create(&(pipeline->eissource));
    eiscalibration_error_create(&(pipeline->eiscalibrationacc0), EISCALIBRATION_ACC0);
    eiscalibration_error_create(&(pipeline->eiscalibrationgyr0), EISCALIBRATION_GYR0);
    eiscalibration_error_create(&(pipeline->eiscalibrationacc1), EISCALIBRATION_ACC1);
    eiscalibration_error_create(&(pipeline->eiscalibrationgyr1), EISCALIBRATION_GYR1);
    lpf_error_create(&(pipeline->lpfacc0), LPF_ACC0);
    lpf_error_create(&(pipeline->lpfacc1), LPF_ACC1);
    lpf_error_create(&(pipeline->lpfgyr0), LPF_GYR0);
    lpf_error_create(&(pipeline->lpfgyr1), LPF_GYR1);
    transform_error_create(&(pipeline->transformacc0), TRANSFORM_ACC0);
    transform_error_create(&(pipeline->transformacc1), TRANSFORM_ACC1);
    transform_error_create(&(pipeline->transformgyr0), TRANSFORM_GYR0);
    transform_error_create(&(pipeline->transformgyr1), TRANSFORM_GYR1);
    adjustline_error_create(&(pipeline->adjustline0), ADJUSTLINE0);
    adjustline_error_create(&(pipeline->adjustline1), ADJUSTLINE1);
    selector_error_create(&(pipeline->selector), 0);
    transformaxes_error_create(&(pipeline->transformaxes));
    dcoffset_error_create(&(pipeline->dcoffset));
    averageacc_error_create(&(pipeline->averageacc));
    stableacc_error_create(&(pipeline->stableacc));
    estimateposeacc_error_create(&(pipeline->estimateposeacc));
    complementaryfilter_error_create(&(pipeline->complementaryfilter));
    axisseparation_error_create(&(pipeline->axisseparation));
    viewpoint_error_create(&(pipeline->viewpoint));
    poseresample_error_create(&(pipeline->poseresample));
    eissink_error_create(&(pipeline->eissink));

    /* Bind data path */
    /*
     * +--------+    +------------------+    +----------+    +----------------+    +---------+    +----------+        +------+
     * |        | -> | calibration acc0 | -> | lpf acc0 | -> | transform acc0 | -> |         | -> |          | -----> |      |
     * |        |    + -----------------+    +----------+    +----------------+    | adjust  |    |          |        |      |
     * |        |    +------------------+    +----------+    +----------------+    | line 0  |    |          |        |      |
     * |        | -> | calibration gyr0 | -> | lpf gyr0 | -> | transform gyr0 | -> |         | -> |          | -----> |      |
     * | source |    + -----------------+    +----------+    +----------------+    |         |    | selector |        |      |
     * |        | ---------------- line -----------------------------------------> |         |    |          | -----> |      |
     * |        |                                                                  +---------+    |          |        |      |
     * |        |    +------------------+    +----------+    +----------------+    +---------+    |          |        |      |
     * |        | -> | calibration acc1 | -> | lpf acc1 | -> | transform acc1 | -> |         | -> |          | ->(2)  |      |
     * |        |    + -----------------+    +----------+    +----------------+    | adjust  |    |          |        |      |
     * |        |    +------------------+    +----------+    +----------------+    | line 1  |    |          |        |      |
     * |        | -> | calibration gyr1 | -> | lpf gyr1 | -> | transform gyr1 | -> |         | -> |          | ->(3)  |      |
     * |        |    +------------------+    +----------+    +----------------+    |         |    |          |        |      |
     * |        | ---------------- line -----------------------------------------> |         |    |          | ->(4)  | sink |
     * |        |                                                                  +---------+    |          |        |      |
     * |        | -------------- offset --------------------------------------------------------> |          |        |      |
     * +--------+                                                                                 +----------+        |      |
     *                                                                                                                |      |
     *       +-----------+    +--------+                                                 +------------+               |      |
     * (2)-> |           | -> |        | ----------------------------------------------> | comple-    |               |      |
     *       | transform |    | dc     |    +---------+    +--------+    +----------+    | mentary    | - rot ->(5)   |      |
     * (3)-> | axes      | -> | offset | -> | average | -> | stable | -> | estimate | -> | filter     |               |      |
     * (4)-> |           | -> |        |    |         |    |        |    | poseacc  |    |            |               |      |
     *       +-----------+    +--------+    +---------+    +--------+    +----------+    +------------+               |      |
     *                                                                                                                |      |
     *       +------------+    +-------+    +----------+                                                              |      |
     * (5)-> | axis       | -> | view  | -> | pose     | -- rot ----------------------------------------------------> |      |
     *       | separation |    | point |    | resample |                                                              |      |
     *       +------------+    +-------+    +----------+                                                              +------+
     */
/*
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_ACC0], pipeline->eiscalibrationacc0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_GYR0], pipeline->eiscalibrationgyr0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_LINE0], pipeline->adjustline0.in[ADJUSTLINE_LINE], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_ACC1], pipeline->eiscalibrationacc1.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_GYR1], pipeline->eiscalibrationgyr1.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_LINE1], pipeline->adjustline1.in[ADJUSTLINE_LINE], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_OFFSET], pipeline->selector.in[SELECTOR_OFFSET], (uint32_t)-1);
    assert(ret == 0);
*/
    ret = mossfw_bind_inout(pipeline->eiscalibrationacc0.out[0], pipeline->lpfacc0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eiscalibrationgyr0.out[0], pipeline->lpfgyr0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eiscalibrationacc1.out[0], pipeline->lpfacc1.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eiscalibrationgyr1.out[0], pipeline->lpfgyr1.in[0], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->lpfacc0.out[0], pipeline->transformacc0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->lpfgyr0.out[0], pipeline->transformgyr0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->lpfacc1.out[0], pipeline->transformacc1.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->lpfgyr1.out[0], pipeline->transformgyr1.in[0], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->transformacc0.out[0], pipeline->adjustline0.in[ADJUSTLINE_ACC], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->transformgyr0.out[0], pipeline->adjustline0.in[ADJUSTLINE_GYR], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->transformacc1.out[0], pipeline->adjustline1.in[ADJUSTLINE_ACC], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->transformgyr1.out[0], pipeline->adjustline1.in[ADJUSTLINE_GYR], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->adjustline0.out[ADJUSTLINE_ACC],  pipeline->selector.in[SELECTOR0_ACC],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->adjustline0.out[ADJUSTLINE_GYR],  pipeline->selector.in[SELECTOR0_GYR],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->adjustline0.out[ADJUSTLINE_LINE], pipeline->selector.in[SELECTOR0_LINE], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->adjustline1.out[ADJUSTLINE_ACC],  pipeline->selector.in[SELECTOR1_ACC],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->adjustline1.out[ADJUSTLINE_GYR],  pipeline->selector.in[SELECTOR1_GYR],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->adjustline1.out[ADJUSTLINE_LINE], pipeline->selector.in[SELECTOR1_LINE], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR0_ACC],  pipeline->eissink.in[EISSINK_ACC],   (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR0_GYR],  pipeline->eissink.in[EISSINK_GYR],   (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR0_LINE],  pipeline->eissink.in[EISSINK_LINE], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR1_ACC],  pipeline->transformaxes.in[TRANSFORMAXES_ACC],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR1_GYR],  pipeline->transformaxes.in[TRANSFORMAXES_GYR],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR1_LINE], pipeline->transformaxes.in[TRANSFORMAXES_LINE], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->transformaxes.out[TRANSFORMAXES_ACC],  pipeline->dcoffset.in[DCOFFSET_ACC],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->transformaxes.out[TRANSFORMAXES_GYR],  pipeline->dcoffset.in[DCOFFSET_GYR],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->transformaxes.out[TRANSFORMAXES_LINE], pipeline->dcoffset.in[DCOFFSET_LINE], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->dcoffset.out[DCOFFSET_ACC], pipeline->averageacc.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->dcoffset.out[DCOFFSET_GYR], pipeline->complementaryfilter.in[COMPLEMENTARYFILTER_GYR], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->dcoffset.out[DCOFFSET_LINE], pipeline->poseresample.in[POSERESAMPLE_LINE], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->averageacc.out[0], pipeline->stableacc.in[0], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->stableacc.out[0], pipeline->estimateposeacc.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->stableacc.out[1], pipeline->estimateposeacc.in[1], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->estimateposeacc.out[0], pipeline->complementaryfilter.in[COMPLEMENTARYFILTER_ROT], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->complementaryfilter.out[0], pipeline->axisseparation.in[0], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->axisseparation.out[0], pipeline->viewpoint.in[0], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->viewpoint.out[0], pipeline->poseresample.in[POSERESAMPLE_ROT], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->poseresample.out[0], pipeline->eissink.in[EISSINK_ROT], (uint32_t)-1);
    assert(ret == 0);
  }
}

void eispipeline_noerror_create(struct eispipeline_error_s *pipeline)
{
  int ret;
  if (pipeline != NULL) {

    // initialize components
    eisallocator_error_create();
    eissource_error_create(&(pipeline->eissource));
    eiscalibration_error_create(&(pipeline->eiscalibrationacc0), EISCALIBRATION_ACC0);
    eiscalibration_error_create(&(pipeline->eiscalibrationgyr0), EISCALIBRATION_GYR0);
    eiscalibration_error_create(&(pipeline->eiscalibrationacc1), EISCALIBRATION_ACC1);
    eiscalibration_error_create(&(pipeline->eiscalibrationgyr1), EISCALIBRATION_GYR1);
    lpf_error_create(&(pipeline->lpfacc0), LPF_ACC0);
    lpf_error_create(&(pipeline->lpfacc1), LPF_ACC1);
    lpf_error_create(&(pipeline->lpfgyr0), LPF_GYR0);
    lpf_error_create(&(pipeline->lpfgyr1), LPF_GYR1);
    transform_error_create(&(pipeline->transformacc0), TRANSFORM_ACC0);
    transform_error_create(&(pipeline->transformacc1), TRANSFORM_ACC1);
    transform_error_create(&(pipeline->transformgyr0), TRANSFORM_GYR0);
    transform_error_create(&(pipeline->transformgyr1), TRANSFORM_GYR1);
    adjustline_error_create(&(pipeline->adjustline0), ADJUSTLINE0);
    adjustline_error_create(&(pipeline->adjustline1), ADJUSTLINE1);
    selector_error_create(&(pipeline->selector), 0);
    transformaxes_error_create(&(pipeline->transformaxes));
    dcoffset_error_create(&(pipeline->dcoffset));
    averageacc_error_create(&(pipeline->averageacc));
    stableacc_error_create(&(pipeline->stableacc));
    estimateposeacc_error_create(&(pipeline->estimateposeacc));
    complementaryfilter_error_create(&(pipeline->complementaryfilter));
    axisseparation_error_create(&(pipeline->axisseparation));
    viewpoint_error_create(&(pipeline->viewpoint));
    poseresample_error_create(&(pipeline->poseresample));
    eissink_error_create(&(pipeline->eissink));

    /* Bind data path */
    /*
     * +--------+    +------------------+    +----------+    +----------------+    +---------+    +----------+        +------+
     * |        | -> | calibration acc0 | -> | lpf acc0 | -> | transform acc0 | -> |         | -> |          | -----> |      |
     * |        |    + -----------------+    +----------+    +----------------+    | adjust  |    |          |        |      |
     * |        |    +------------------+    +----------+    +----------------+    | line 0  |    |          |        |      |
     * |        | -> | calibration gyr0 | -> | lpf gyr0 | -> | transform gyr0 | -> |         | -> |          | -----> |      |
     * | source |    + -----------------+    +----------+    +----------------+    |         |    | selector |        |      |
     * |        | ---------------- line -----------------------------------------> |         |    |          | -----> |      |
     * |        |                                                                  +---------+    |          |        |      |
     * |        |    +------------------+    +----------+    +----------------+    +---------+    |          |        |      |
     * |        | -> | calibration acc1 | -> | lpf acc1 | -> | transform acc1 | -> |         | -> |          | ->(2)  |      |
     * |        |    + -----------------+    +----------+    +----------------+    | adjust  |    |          |        |      |
     * |        |    +------------------+    +----------+    +----------------+    | line 1  |    |          |        |      |
     * |        | -> | calibration gyr1 | -> | lpf gyr1 | -> | transform gyr1 | -> |         | -> |          | ->(3)  |      |
     * |        |    +------------------+    +----------+    +----------------+    |         |    |          |        |      |
     * |        | ---------------- line -----------------------------------------> |         |    |          | ->(4)  | sink |
     * |        |                                                                  +---------+    |          |        |      |
     * |        | -------------- offset --------------------------------------------------------> |          |        |      |
     * +--------+                                                                                 +----------+        |      |
     *                                                                                                                |      |
     *       +-----------+    +--------+                                                 +------------+               |      |
     * (2)-> |           | -> |        | ----------------------------------------------> | comple-    |               |      |
     *       | transform |    | dc     |    +---------+    +--------+    +----------+    | mentary    | - rot ->(5)   |      |
     * (3)-> | axes      | -> | offset | -> | average | -> | stable | -> | estimate | -> | filter     |               |      |
     * (4)-> |           | -> |        |    |         |    |        |    | poseacc  |    |            |               |      |
     *       +-----------+    +--------+    +---------+    +--------+    +----------+    +------------+               |      |
     *                                                                                                                |      |
     *       +------------+    +-------+    +----------+                                                              |      |
     * (5)-> | axis       | -> | view  | -> | pose     | -- rot ----------------------------------------------------> |      |
     *       | separation |    | point |    | resample |                                                              |      |
     *       +------------+    +-------+    +----------+                                                              +------+
     */

    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_ACC0], pipeline->eiscalibrationacc0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_GYR0], pipeline->eiscalibrationgyr0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_LINE0], pipeline->adjustline0.in[ADJUSTLINE_LINE], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_ACC1], pipeline->eiscalibrationacc1.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_GYR1], pipeline->eiscalibrationgyr1.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_LINE1], pipeline->adjustline1.in[ADJUSTLINE_LINE], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eissource.out[EISSOURCE_OFFSET], pipeline->selector.in[SELECTOR_OFFSET], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->eiscalibrationacc0.out[0], pipeline->lpfacc0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eiscalibrationgyr0.out[0], pipeline->lpfgyr0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eiscalibrationacc1.out[0], pipeline->lpfacc1.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->eiscalibrationgyr1.out[0], pipeline->lpfgyr1.in[0], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->lpfacc0.out[0], pipeline->transformacc0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->lpfgyr0.out[0], pipeline->transformgyr0.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->lpfacc1.out[0], pipeline->transformacc1.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->lpfgyr1.out[0], pipeline->transformgyr1.in[0], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->transformacc0.out[0], pipeline->adjustline0.in[ADJUSTLINE_ACC], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->transformgyr0.out[0], pipeline->adjustline0.in[ADJUSTLINE_GYR], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->transformacc1.out[0], pipeline->adjustline1.in[ADJUSTLINE_ACC], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->transformgyr1.out[0], pipeline->adjustline1.in[ADJUSTLINE_GYR], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->adjustline0.out[ADJUSTLINE_ACC],  pipeline->selector.in[SELECTOR0_ACC],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->adjustline0.out[ADJUSTLINE_GYR],  pipeline->selector.in[SELECTOR0_GYR],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->adjustline0.out[ADJUSTLINE_LINE], pipeline->selector.in[SELECTOR0_LINE], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->adjustline1.out[ADJUSTLINE_ACC],  pipeline->selector.in[SELECTOR1_ACC],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->adjustline1.out[ADJUSTLINE_GYR],  pipeline->selector.in[SELECTOR1_GYR],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->adjustline1.out[ADJUSTLINE_LINE], pipeline->selector.in[SELECTOR1_LINE], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR0_ACC],  pipeline->eissink.in[EISSINK_ACC],   (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR0_GYR],  pipeline->eissink.in[EISSINK_GYR],   (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR0_LINE],  pipeline->eissink.in[EISSINK_LINE], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR1_ACC],  pipeline->transformaxes.in[TRANSFORMAXES_ACC],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR1_GYR],  pipeline->transformaxes.in[TRANSFORMAXES_GYR],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->selector.out[SELECTOR1_LINE], pipeline->transformaxes.in[TRANSFORMAXES_LINE], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->transformaxes.out[TRANSFORMAXES_ACC],  pipeline->dcoffset.in[DCOFFSET_ACC],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->transformaxes.out[TRANSFORMAXES_GYR],  pipeline->dcoffset.in[DCOFFSET_GYR],  (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->transformaxes.out[TRANSFORMAXES_LINE], pipeline->dcoffset.in[DCOFFSET_LINE], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->dcoffset.out[DCOFFSET_ACC], pipeline->averageacc.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->dcoffset.out[DCOFFSET_GYR], pipeline->complementaryfilter.in[COMPLEMENTARYFILTER_GYR], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->dcoffset.out[DCOFFSET_LINE], pipeline->poseresample.in[POSERESAMPLE_LINE], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->averageacc.out[0], pipeline->stableacc.in[0], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->stableacc.out[0], pipeline->estimateposeacc.in[0], (uint32_t)-1);
    assert(ret == 0);
    ret = mossfw_bind_inout(pipeline->stableacc.out[1], pipeline->estimateposeacc.in[1], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->estimateposeacc.out[0], pipeline->complementaryfilter.in[COMPLEMENTARYFILTER_ROT], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->complementaryfilter.out[0], pipeline->axisseparation.in[0], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->axisseparation.out[0], pipeline->viewpoint.in[0], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->viewpoint.out[0], pipeline->poseresample.in[POSERESAMPLE_ROT], (uint32_t)-1);
    assert(ret == 0);

    ret = mossfw_bind_inout(pipeline->poseresample.out[0], pipeline->eissink.in[EISSINK_ROT], (uint32_t)-1);
    assert(ret == 0);
  }
}

void eispipeline_error_delete(struct eispipeline_error_s *pipeline)
{
  eissource_error_delete(&(pipeline->eissource));
  eiscalibration_error_delete(&(pipeline->eiscalibrationacc0));
  eiscalibration_error_delete(&(pipeline->eiscalibrationgyr0));
  eiscalibration_error_delete(&(pipeline->eiscalibrationacc1));
  eiscalibration_error_delete(&(pipeline->eiscalibrationgyr1));
  lpf_error_delete(&(pipeline->lpfacc0));
  lpf_error_delete(&(pipeline->lpfgyr0));
  lpf_error_delete(&(pipeline->lpfacc1));
  lpf_error_delete(&(pipeline->lpfgyr1));
  transform_error_delete(&(pipeline->transformacc0));
  transform_error_delete(&(pipeline->transformgyr0));
  transform_error_delete(&(pipeline->transformacc1));
  transform_error_delete(&(pipeline->transformgyr1));
  adjustline_error_delete(&(pipeline->adjustline0));
  adjustline_error_delete(&(pipeline->adjustline1));
  selector_error_delete(&(pipeline->selector));
  transformaxes_error_delete(&(pipeline->transformaxes));
  dcoffset_error_delete(&(pipeline->dcoffset));
  averageacc_error_delete(&(pipeline->averageacc));
  stableacc_error_delete(&(pipeline->stableacc));
  complementaryfilter_error_delete(&(pipeline->complementaryfilter));
  estimateposeacc_error_delete(&(pipeline->estimateposeacc));
  axisseparation_error_delete(&(pipeline->axisseparation));
  viewpoint_error_delete(&(pipeline->viewpoint));
  poseresample_error_delete(&(pipeline->poseresample));
  eissink_error_delete(&(pipeline->eissink));
  eisallocator_error_delete();
}

static struct eispipeline_error_s pipeline;

struct eispipeline_error_s *geteis_errorpipeline(void)
{
    return &pipeline;
}

void eis_error(void)
{
  const struct timespec time = {.tv_sec = 0, .tv_nsec = 1000};
  int time_count = 0;
  eispipeline_error_create(&pipeline);
  (*pipeline.eissource.op)->operate(*pipeline.eissource.op, 0);
  eispipeline_error_delete(&pipeline);

  eispipeline_noerror_create(&pipeline);
  (*pipeline.eissource.op)->operate(*pipeline.eissource.op, 0);
  int succeeded = eissink_error_succeeded();
  while (succeeded != 0 && time_count < 1000) {
    int sleep_err = nanosleep(&time, NULL);
    assert(sleep_err != -1);
    succeeded = eissink_error_succeeded();
    time_count = time_count + 1;
  }
  eispipeline_error_delete(&pipeline);
  succeeded = eissink_error_succeeded();
  assert(succeeded == 0);
  printf("framework jointest eis error passed\n");
}
