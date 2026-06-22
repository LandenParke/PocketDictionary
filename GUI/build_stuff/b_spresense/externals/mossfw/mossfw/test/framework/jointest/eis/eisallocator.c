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
#include <stdio.h>
#include "eis/eisallocator.h"
#include "mossfw/mossfw_component.h"
#include "mossfw/mossfw_data.h"

static mossfw_allocator_t *allocator = NULL;

int eisallocator_create(void)
{
  if (allocator == NULL)
    {
        allocator = mossfw_fixedmem_create(EISALLOCATOR_SIZE, EISALLOCATOR_MAXBLOCK);
    }
  return allocator == NULL;
}

int eisallocator_delete(void)
{
    int err = 0;
    if (allocator != NULL)
      {
        err = mossfw_fixedmem_delete(allocator);
        allocator = NULL;
      }
    return err;
}

mossfw_allocator_t *eisallocator_getallocator(void)
{
    return allocator;
}
