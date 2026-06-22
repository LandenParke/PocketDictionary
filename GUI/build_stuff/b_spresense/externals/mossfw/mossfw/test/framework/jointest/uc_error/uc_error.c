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
#include "ucsource_error.h"
#include "calculatetiltangle_error.h"
#include "calculatetiltgravity_error.h"
#include "calibrationacc_error.h"
#include "ucresult_error.h"
#include "uc_error.h"

void ucpipeline_error_create(struct ucpipeline_error_s *pipeline)
{
    ucsource_error_create(&(pipeline->ucsource));
    calculatetiltangle_error_create(&(pipeline->calculatetiltangle));
    calculatetiltgravity_error_create(&(pipeline->calculatetiltgravity));
    calibrationacc_error_create(&(pipeline->calibrationacc));
    ucresult_error_create(&(pipeline->ucresult));

    /*
     * +--------+    +-------------+        +-------------+        +-------------+    +--------+
     * | uc     | -> | calcurate   | -rot-> | calculate   | -rot-> | calibration | -> | uc     |
     * | source |    | tiltangle   | -acc-> | tiltgravity | -acc-> | acc         |    | result |
     * +--------+    + ------------+        +-------------+        +-------------+    +--------+
     */
//    mossfw_bind_inout(*pipeline->ucsource.out, *pipeline->calculatetiltangle.in, (uint32_t)-1);
//    mossfw_bind_inout(pipeline->calculatetiltangle.out[0], pipeline->calculatetiltgravity.in[0], (uint32_t)-1);
//    mossfw_bind_inout(pipeline->calculatetiltangle.out[1], pipeline->calculatetiltgravity.in[1], (uint32_t)-1);
//    mossfw_bind_inout(pipeline->calculatetiltgravity.out[0], pipeline->calibrationacc.in[0], (uint32_t)-1);
//    mossfw_bind_inout(pipeline->calculatetiltgravity.out[1], pipeline->calibrationacc.in[1], (uint32_t)-1);
//    mossfw_bind_inout(*pipeline->calibrationacc.out, *pipeline->ucresult.in, (uint32_t)-1);
}

void ucpipeline_noerror_create(struct ucpipeline_error_s *pipeline)
{
    ucsource_error_create(&(pipeline->ucsource));
    calculatetiltangle_error_create(&(pipeline->calculatetiltangle));
    calculatetiltgravity_error_create(&(pipeline->calculatetiltgravity));
    calibrationacc_error_create(&(pipeline->calibrationacc));
    ucresult_error_create(&(pipeline->ucresult));

    /*
     * +--------+    +-------------+        +-------------+        +-------------+    +--------+
     * | uc     | -> | calcurate   | -rot-> | calculate   | -rot-> | calibration | -> | uc     |
     * | source |    | tiltangle   | -acc-> | tiltgravity | -acc-> | acc         |    | result |
     * +--------+    + ------------+        +-------------+        +-------------+    +--------+
     */
    mossfw_bind_inout(*pipeline->ucsource.out, *pipeline->calculatetiltangle.in, (uint32_t)-1);
    mossfw_bind_inout(pipeline->calculatetiltangle.out[0], pipeline->calculatetiltgravity.in[0], (uint32_t)-1);
    mossfw_bind_inout(pipeline->calculatetiltangle.out[1], pipeline->calculatetiltgravity.in[1], (uint32_t)-1);
    mossfw_bind_inout(pipeline->calculatetiltgravity.out[0], pipeline->calibrationacc.in[0], (uint32_t)-1);
    mossfw_bind_inout(pipeline->calculatetiltgravity.out[1], pipeline->calibrationacc.in[1], (uint32_t)-1);
    mossfw_bind_inout(*pipeline->calibrationacc.out, *pipeline->ucresult.in, (uint32_t)-1);
}

void ucpipeline_error_delete(struct ucpipeline_error_s *pipeline)
{
    ucsource_error_delete(&(pipeline->ucsource));
    calculatetiltangle_error_delete(&(pipeline->calculatetiltangle));
    calculatetiltgravity_error_delete(&(pipeline->calculatetiltgravity));
    calibrationacc_error_delete(&(pipeline->calibrationacc));
    ucresult_error_delete(&(pipeline->ucresult));
}

static struct ucpipeline_error_s pipeline;

struct ucpipeline_error_s *getuc_errorpipeline(void)
{
    return &pipeline;
}

void uc_error(void)
{

  ucpipeline_error_create(&pipeline);
  (*pipeline.ucsource.op)->operate(*pipeline.ucsource.op, 0);
  ucpipeline_error_delete(&pipeline);

  ucpipeline_noerror_create(&pipeline);
  (*pipeline.ucsource.op)->operate(*pipeline.ucsource.op, 0);
  ucpipeline_error_delete(&pipeline);

  assert(ucerror_result_succeeded() == 1);
  printf("framework jointest uc error passed\n");
}
