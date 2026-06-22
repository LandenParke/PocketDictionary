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
#ifndef __ATTITUDE_ERROR_H
#define __ATTITUDE_ERROR_H

struct attitudepipeline_error_s {
    struct component_s attitudesource;
    struct component_s eiscalib_acc;
    struct component_s eiscalib_gyr;
    struct component_s lpf_acc;
    struct component_s lpf_gyr;
    struct component_s transform_acc;
    struct component_s transform_gyr;
    struct component_s average_acc;
    struct component_s stable_acc;
    struct component_s estimate_poseacc;
    struct component_s complementary_filter_gyr;
    struct component_s complementary_filter_rot;
    struct component_s result;
};

void attitude_error(void);
struct attitudepipeline_error_s *getattitude_errorpipeline(void);

#endif  /* __ATTITUDE_ERROR_H */
