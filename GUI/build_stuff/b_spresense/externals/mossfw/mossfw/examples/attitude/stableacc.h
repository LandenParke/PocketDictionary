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
#ifndef __STABLEACC_H
#  define __STABLEACC_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#  include "mossfw/mossfw_component.h"
#  include "mossfw/mossfw_memoryallocator.h"

/****************************************************************************
 * Public Data Types
 ****************************************************************************/

struct stableacc_s
  {
    mossfw_input_t *input;
    mossfw_callback_op_t *op;
    mossfw_output_t *outstbl;
    mossfw_output_t *outacc;
    mossfw_allocator_t *alloc;
  };

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

struct stableacc_s *stableacc_create(mossfw_allocator_t * allocator);
void stableacc_delete(struct stableacc_s *stableacc);

#endif
