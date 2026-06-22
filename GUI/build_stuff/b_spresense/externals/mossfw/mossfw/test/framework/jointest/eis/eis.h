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
#ifndef __EIS_H
#define __EIS_H

struct eispipeline_s {
    struct component_s eissource;
    struct component_s eiscalibrationacc0;
    struct component_s eiscalibrationgyr0;
    struct component_s eiscalibrationacc1;
    struct component_s eiscalibrationgyr1;
    struct component_s lpfacc0;
    struct component_s lpfgyr0;
    struct component_s lpfacc1;
    struct component_s lpfgyr1;
    struct component_s transformacc0;
    struct component_s transformgyr0;
    struct component_s transformacc1;
    struct component_s transformgyr1;
    struct component_s adjustline0;
    struct component_s adjustline1;
    struct component_s selector;
    struct component_s transformaxes;
    struct component_s dcoffset;
    struct component_s averageacc;
    struct component_s stableacc;
    struct component_s estimateposeacc;
    struct component_s complementaryfilter;
    struct component_s axisseparation;
    struct component_s viewpoint;
    struct component_s poseresample;
    struct component_s eissink;
};

void eis(void);
struct eispipeline_s *geteispipeline(void);

#endif  /* __EIS_H */
