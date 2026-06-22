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
#ifndef __TESTESTIMATORCOMPONENT_H
#define __TESTESTIMATORCOMPONENT_H

#include "component.h"

#define TestEstimatorCOMPONENT_INACC 0
#define TestEstimatorCOMPONENT_INGYR 1
#define TestEstimatorCOMPONENT_INMAG 2
#define TestEstimatorCOMPONENT_OUTMAG 0
#define TestEstimatorCOMPONENT_OUTROT 1

void testestimatorcomponent_create(struct component_s *com);
void testestimatorcomponent_delete(struct component_s *com);

#endif  /* __AVERAGE_H */

