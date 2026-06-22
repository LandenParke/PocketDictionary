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
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "component.h"
#include "sarsource.h"
#include "adjustgyro.h"
#include "average.h"
#include "transformaxismatrix.h"
#include "transformaxisquaternion.h"
#include "decimate.h"
#include "testestimatorcomponent.h"
#include "multiplyqf.h"
#include "transformquaternion.h"
#include "sarresult.h"
#include "sar.h"

void sarpipeline_create(struct sarpipeline_s *pipeline)
{
  if (pipeline != NULL) {

    // initialize components
    sarsource_create(&(pipeline->sarsource));
    adjustgyro_create(&(pipeline->adjustgyro));
    average_create(&(pipeline->average));
    transformaxismatrix_create(&(pipeline->transformaxismatrix_acc));
    transformaxismatrix_create(&(pipeline->transformaxismatrix_gyr));
    transformaxismatrix_create(&(pipeline->transformaxismatrix_mag));
    transformaxisquaternion_create(&(pipeline->transformaxisquaternion_acc));
    transformaxisquaternion_create(&(pipeline->transformaxisquaternion_gyr));
    transformaxisquaternion_create(&(pipeline->transformaxisquaternion_mag));
    decimate_create(&(pipeline->decimate_acc), 2);
    decimate_create(&(pipeline->decimate_gyr), 4);
    testestimatorcomponent_create(&(pipeline->testestimatorcomponent));
    multiplyqf_create(&(pipeline->multiplyqf));
    transformquaternion_create(&(pipeline->transformquaternion));
    sarresult_create(&(pipeline->result));

    /* Bind data path */
    /*
     * +--------+    +---------+    +------------+        +---------- +                    +---------------+    +--------+
     * |        | -> | average | -> | transform  | -----> | decimate  | -----------------> | transformaxis | -> |        |
     * |        |    |         |    | axismatrix | ---+   | (2)       |                    | quaternion    |    |        |
     * |        |    + --------+    +------------+    |   +-----------+                    +---------------+    |        |
     * |        |                                     |                                                         |        |
     * |        |    +---------+    +------------+    |   +---------- +                    +---------------+    |        |
     * |        | -> | adjust  | -> | transform  | -----> | decimate  | -----------------> | transformaxis | -> |        |
     * | sar    |    | gyro    |    | axismatrix | -+ |   | (4)       |                    | quaternion    |    |        |
     * | source |    +---------+    +------------+  | |   +-----------+                    +---------------+    | result |
     * |        |                                   | |                                                         |        |
     * |        |                   +------------+  | +-> +-----------+                    +---------------+    |        |
     * |        | ----------------> | transform  |  +---> |           | -----------------> | transformaxis | -> |        |
     * |        |                   | axismatrix | -----> | test      |                    | quaternion    |    |        |
     * |        |                   +------------+        | estimator |                    +---------------+    |        |
     * |        |                                         | component |                                         |        |
     * |        |                                         |           |    +----------+    +---------------+    |        |
     * |        |                                         |           | -> | multiply | -> | transform     | -> |        |
     * |        |                                         |           |    | qf       |    | quaternion    |    |        |
     * +--------+                                         +-----------+    +----------+    +---------------+    +--------+
     */
    mossfw_bind_inout(pipeline->sarsource.out[SARSOURCECOMPONENT_ACC], *pipeline->average.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->average.out, *pipeline->transformaxismatrix_acc.in, MOSSFW_DATA_TYPE_MASK + MOSSFW_DATA_TYPEGRP_MASK + MOSSFW_DATA_TYPEARRAY_MASK);
    mossfw_bind_inout(*pipeline->transformaxismatrix_acc.out, *pipeline->decimate_acc.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->transformaxismatrix_acc.out, pipeline->testestimatorcomponent.in[TestEstimatorCOMPONENT_INACC], MOSSFW_DATA_TYPE_MASK + MOSSFW_DATA_TYPEGRP_MASK + MOSSFW_DATA_TYPEARRAY_MASK);
    mossfw_bind_inout(*pipeline->decimate_acc.out, *pipeline->transformaxisquaternion_acc.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->transformaxisquaternion_acc.out, pipeline->result.in[SARRESULT_ACC], MOSSFW_DATA_TYPE_MASK + MOSSFW_DATA_TYPEGRP_MASK + MOSSFW_DATA_TYPEARRAY_MASK);

    mossfw_bind_inout(pipeline->sarsource.out[SARSOURCECOMPONENT_GYR], *pipeline->adjustgyro.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->adjustgyro.out, *pipeline->transformaxismatrix_gyr.in, MOSSFW_DATA_TYPE_MASK + MOSSFW_DATA_TYPEGRP_MASK + MOSSFW_DATA_TYPEARRAY_MASK);
    mossfw_bind_inout(*pipeline->transformaxismatrix_gyr.out, *pipeline->decimate_gyr.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->transformaxismatrix_gyr.out, pipeline->testestimatorcomponent.in[TestEstimatorCOMPONENT_INGYR], MOSSFW_DATA_TYPE_MASK + MOSSFW_DATA_TYPEGRP_MASK + MOSSFW_DATA_TYPEARRAY_MASK);
    mossfw_bind_inout(*pipeline->decimate_gyr.out, *pipeline->transformaxisquaternion_gyr.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->transformaxisquaternion_gyr.out, pipeline->result.in[SARRESULT_GYR], MOSSFW_DATA_TYPE_MASK + MOSSFW_DATA_TYPEGRP_MASK + MOSSFW_DATA_TYPEARRAY_MASK);

    mossfw_bind_inout(pipeline->sarsource.out[SARSOURCECOMPONENT_MAG], *pipeline->transformaxismatrix_mag.in, MOSSFW_DATA_TYPE_MASK + MOSSFW_DATA_TYPEGRP_MASK + MOSSFW_DATA_TYPEARRAY_MASK);
    mossfw_bind_inout(*pipeline->transformaxismatrix_mag.out, pipeline->testestimatorcomponent.in[TestEstimatorCOMPONENT_INMAG], MOSSFW_DATA_TYPE_MASK + MOSSFW_DATA_TYPEGRP_MASK + MOSSFW_DATA_TYPEARRAY_MASK);
    mossfw_bind_inout(pipeline->testestimatorcomponent.out[TestEstimatorCOMPONENT_OUTMAG], *pipeline->transformaxisquaternion_mag.in, MOSSFW_DATA_TYPE_MASK + MOSSFW_DATA_TYPEGRP_MASK + MOSSFW_DATA_TYPEARRAY_MASK);
    mossfw_bind_inout(*pipeline->transformaxisquaternion_mag.out, pipeline->result.in[SARRESULT_MAG], MOSSFW_DATA_TYPE_MASK + MOSSFW_DATA_TYPEGRP_MASK + MOSSFW_DATA_TYPEARRAY_MASK);

    mossfw_bind_inout(pipeline->testestimatorcomponent.out[TestEstimatorCOMPONENT_OUTROT], *pipeline->multiplyqf.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->multiplyqf.out, *pipeline->transformquaternion.in, (uint32_t)-1);
    mossfw_bind_inout(*pipeline->transformquaternion.out, pipeline->result.in[SARRESULT_ROT], (uint32_t)-1);
  }
}

void sarpipeline_delete(struct sarpipeline_s *pipeline)
{
  sarsource_delete(&(pipeline->sarsource));
  adjustgyro_delete(&(pipeline->adjustgyro));
  average_delete(&(pipeline->average));
  transformaxismatrix_delete(&(pipeline->transformaxismatrix_acc));
  transformaxismatrix_delete(&(pipeline->transformaxismatrix_gyr));
  transformaxismatrix_delete(&(pipeline->transformaxismatrix_mag));
  transformaxisquaternion_delete(&(pipeline->transformaxisquaternion_acc));
  transformaxisquaternion_delete(&(pipeline->transformaxisquaternion_gyr));
  transformaxisquaternion_delete(&(pipeline->transformaxisquaternion_mag));
  decimate_delete(&(pipeline->decimate_acc));
  decimate_delete(&(pipeline->decimate_gyr));
  testestimatorcomponent_delete(&(pipeline->testestimatorcomponent));
  multiplyqf_delete(&(pipeline->multiplyqf));
  transformquaternion_delete(&(pipeline->transformquaternion));
  sarresult_delete(&(pipeline->result));
}

static struct sarpipeline_s pipeline;

struct sarpipeline_s *getsarpipeline(void)
{
    return &pipeline;
}

void sar(void)
{

  sarpipeline_create(&pipeline);
  (*pipeline.sarsource.op)->operate(*pipeline.sarsource.op, 0);
  sarpipeline_delete(&pipeline);
  printf("framework jointest sar passed\n");
}
