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
#ifndef __SELECTOR_ERROR_H
#define __SELECTOR_ERROR_H

#include "component.h"

enum selector_e {
    SELECTOR0,
    SELECTOR1
};

enum selector_data_e {
    SELECTOR0_ACC,
    SELECTOR0_GYR,
    SELECTOR0_LINE,
    SELECTOR1_ACC,
    SELECTOR1_GYR,
    SELECTOR1_LINE,
    SELECTOR_OFFSET,
    SELECTOR_SIZE
};

void selector_error_create(struct component_s *com, int type);
void selector_error_delete(struct component_s *com);

#endif  /* __SELECTOR_ERROR_H */

