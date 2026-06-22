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
#ifndef __SAR_H
#define __SAR_H

struct sarpipeline_s {
    struct component_s sarsource;
    struct component_s adjustgyro;
    struct component_s average;
    struct component_s transformaxismatrix_acc;
    struct component_s transformaxismatrix_gyr;
    struct component_s transformaxismatrix_mag;
    struct component_s transformaxisquaternion_acc;
    struct component_s transformaxisquaternion_gyr;
    struct component_s transformaxisquaternion_mag;
    struct component_s decimate_acc;
    struct component_s decimate_gyr;
    struct component_s multiplyqf;
    struct component_s transformquaternion;
    struct component_s testestimatorcomponent;
    struct component_s result;
};

void sar(void);
struct sarpipeline_s *getsarpipeline(void);

#endif  /* __SAR_H */
