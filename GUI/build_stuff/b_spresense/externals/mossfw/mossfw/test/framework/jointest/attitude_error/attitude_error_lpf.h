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
#ifndef __ATTITUDE_ERROR_LPF_H
#define __ATTITUDE_ERROR_LPF_H

#include "component.h"
#include "attitude_error_source.h"

#define LPF_MAXDATA (ATTITUDESOURCE_MAXDATA + 7)
#define LPF_MAXBLOCK (4 * ATTITUDESOURCE_MAXDATA)

enum lpf_e {
    LPF_ACC,
    LPF_GYR,
    LPF_SIZE
};

void attitude_error_lpf_reset(void);
void attitude_error_lpf_create(struct component_s *com, enum lpf_e type);
void attitude_error_lpf_delete(struct component_s *com);

#endif  /* __ATTITUDE_ERROR_LPF_H */

