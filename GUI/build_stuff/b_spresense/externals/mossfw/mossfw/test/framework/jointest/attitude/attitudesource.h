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
#ifndef __ATTITUDESOURCE_H
#define __ATTITUDESOURCE_H

#include <stddef.h>
#include <mossfw/mossfw_component.h>
#include "component.h"

#define ATTITUDESOURCE_MAXDATA 300
#define ATTITUDESOURCE_MAXBLOCK 32

enum attitudesource_e {
    ATTITUDESOURCE_ACC,
    ATTITUDESOURCE_GYR,
};

void attitudesource_create(struct component_s *com);
void attitudesource_delete(struct component_s *com);

#endif  /* __ATTITUDESOURCE_H */
