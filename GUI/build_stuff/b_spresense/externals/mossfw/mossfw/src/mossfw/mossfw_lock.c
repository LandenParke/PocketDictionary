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

#include <sched.h>
#include <mossfw/mossfw_lock.h>

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossfw_create_thread_attr
 ****************************************************************************/

int mossfw_create_thread_attr(mossfw_thread_t *tid,
                              mossfw_start_t func, void *arg,
                              int prior, int stksz)
{
  int ret;
  pthread_attr_t attr;
  struct sched_param sparam;

  pthread_attr_init(&attr);
  sparam.sched_priority = prior;
  pthread_attr_setschedparam(&attr, &sparam);
  pthread_attr_setstacksize(&attr, stksz);
  ret = pthread_create(tid, &attr, func, arg);
  pthread_attr_destroy(&attr);

  return ret;
}
