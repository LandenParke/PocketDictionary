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
#include "uc.h"
#include "ucsource.h"
#include "calculatetiltangle.h"
#include "calculatetiltgravity.h"
#include "calibrationacc.h"
#include "ucresult.h"

void ucpipeline_create(struct ucpipeline_s *pipeline)
{
    ucsource_create(&(pipeline->ucsource));
    calculatetiltangle_create(&(pipeline->calculatetiltangle));
    calculatetiltgravity_create(&(pipeline->calculatetiltgravity));
    calibrationacc_create(&(pipeline->calibrationacc));
    ucresult_create(&(pipeline->ucresult));

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

void ucpipeline_delete(struct ucpipeline_s *pipeline)
{
    ucsource_delete(&(pipeline->ucsource));
    calculatetiltangle_delete(&(pipeline->calculatetiltangle));
    calculatetiltgravity_delete(&(pipeline->calculatetiltgravity));
    calibrationacc_delete(&(pipeline->calibrationacc));
    ucresult_delete(&(pipeline->ucresult));
}

static struct ucpipeline_s pipeline;

struct ucpipeline_s *getucpipeline(void)
{
    return &pipeline;
}

void uc(void)
{
  ucpipeline_create(&pipeline);
  (*pipeline.ucsource.op)->operate(*pipeline.ucsource.op, 0);
  ucpipeline_delete(&pipeline);
  printf("framework jointest uc passed\n");
}
