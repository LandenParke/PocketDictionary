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
#ifndef __LPF_ERROR_H
#define __LPF_ERROR_H

#include "component.h"

enum lpf_e {
    LPF_ACC0,
    LPF_GYR0,
    LPF_ACC1,
    LPF_GYR1,
    LPF_SIZE
};

void lpf_error_create(struct component_s *com, enum lpf_e type);
void lpf_error_delete(struct component_s *com);

#endif  /* __LPF_ERROR_H */

