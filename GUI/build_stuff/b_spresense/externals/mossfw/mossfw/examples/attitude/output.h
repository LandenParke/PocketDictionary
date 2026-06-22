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

#ifndef OUTPUT_H
#  define OUTPUT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#  include <stdint.h>
#  include "mossfw/mossfw_component.h"

/****************************************************************************
 * Public Data Types
 ****************************************************************************/

struct output_s
  {
    mossfw_input_t *inr;
    mossfw_input_t *ini;
    mossfw_callback_op_t *op;
  };

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

struct output_s *output_create(void);
void output_delete(struct output_s *com);

#endif
