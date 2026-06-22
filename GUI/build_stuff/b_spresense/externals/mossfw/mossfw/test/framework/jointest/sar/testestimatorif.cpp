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
#include "testestimator.h"
#include <cstddef>
extern "C" {
#include "mossfw/sensorlib.h"
#include "testestimatorif.h"
}

void *TestEstimator_instance(float b, float f, float a, float g, int ga, float bi)
{
    return (void *)new TestEstimator(b, f, a, g, (bool)ga, bi);
}

void TestEstimator_initimu(void *testestimator, mossfw_data_v3f_t *a)
{
    float in[3];
    in[0] = a->x;
    in[1] = a->y;
    in[2] = a->z;
    ((TestEstimator *)testestimator)->initialize(in);
}

void TestEstimator_update(void *testestimator, mossfw_data_v3f_t *a, mossfw_data_v3f_t *g, mossfw_data_v3f_t *m)
{
    float data[9];
    data[0] = a->x;
    data[1] = a->y;
    data[2] = a->z;
    data[3] = g->x;
    data[4] = g->y;
    data[5] = g->z;
    data[6] = m->x;
    data[7] = m->y;
    data[8] = m->z;
    ((TestEstimator *)testestimator)->update(data);
}

void TestEstimator_getq(void *testestimator, mossfw_data_qf_t *out)
{
    float quaternion[4];
    ((TestEstimator *)testestimator)->get(quaternion);
    out->w = quaternion[0];
    out->x = quaternion[1];
    out->y = quaternion[2];
    out->z = quaternion[3];
}
