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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <mossfw/mossfw_debug.h>

/****************************************************************************
 * Public Data
 ****************************************************************************/

pthread_t avoid_id = -1;

/****************************************************************************
 * Private Data
 ****************************************************************************/

static bool is_inited = false;
static mossfw_lock_t mossfw_dlock;

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossfw_debug_init
 ****************************************************************************/

void mossfw_debug_init(void)
{
  if (is_inited == false)
    {
      mossfw_lock_init(&mossfw_dlock);
      is_inited = true;
    }
}

/****************************************************************************
 * name: mossfw_dprint
 ****************************************************************************/

void mossfw_dprint(const char *fmt, ...)
{
  va_list ap;

  if (is_inited)
    {
      mossfw_lock_take(&mossfw_dlock);

      va_start(ap, fmt);
      vfprintf(stdout, fmt, ap);
      va_end(ap);

      mossfw_lock_give(&mossfw_dlock);
    }
}
