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
#ifndef TESTESTIMATORIF_H
#define TESTESTIMATORIF_H
void *TestEstimator_instance(float b, float f, float a, float g, int ga, float bi);
void TestEstimator_initimu(void *testestimator, mossfw_data_v3f_t *a);
void TestEstimator_update(void *testestimator, mossfw_data_v3f_t *a, mossfw_data_v3f_t *g, mossfw_data_v3f_t *m);
void TestEstimator_getq(void *testestimator, mossfw_data_qf_t *out);
#endif
