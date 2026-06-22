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

#include <string.h>
#include <stdlib.h>
#include <mossfw/mossfw_debug.h>
#include <mossfw/mossfw_memoryallocator.h>
#include <mossfw/mossfw_ringbuffary.h>

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: add_tail
 ****************************************************************************/

/****************************************************************************
 * name: add_tail
 ****************************************************************************/

static void add_tail(mossfw_data_container_t *top,
                     mossfw_data_container_t *item)
{
  for (; top->next; top = top->next);
  top->next = item;
}

/****************************************************************************
 * name: mossfw_data_container_t
 ****************************************************************************/

static mossfw_data_container_t *find_free(mossfw_data_container_t *ctr,
                                          int num)
{
  int i;
  mossfw_data_container_t *ret = NULL;

  for (i = 0; i < num; i++)
    {
      if (ctr[i].data == NULL)
        {
          ret = &ctr[i];
          break;
        }
    }

  return ret;
}

/****************************************************************************
 * name: init_containers
 ****************************************************************************/

static void init_containers(mossfw_ringbuffarray_t *ary, int num)
{
  int i;

  for (i = 0; i < num; i++)
    {
      ary->top[i].data = NULL;
      ary->top[i].next = NULL;
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossfw_ringbuffarray_create
 ****************************************************************************/

mossfw_ringbuffarray_t *mossfw_ringbuffarray_create(int depth)
{
  mossfw_ringbuffarray_t *ret;

  ret = (mossfw_ringbuffarray_t *)malloc(sizeof(mossfw_ringbuffarray_t));
  if (ret)
    {
      ret->top = (mossfw_data_container_t *)
                  malloc(sizeof(mossfw_data_container_t) * depth);
      if (!ret->top)
        {
          free(ret);
          return NULL;
        }

      init_containers(ret, depth);

      ret->stored = NULL;
      ret->total_depth = depth;
      ret->stored_num = 0;
      ret->stored_bytes = 0;
      ret->usedidx = 0;
      ret->is_stop = false;
      mossfw_lock_init(&ret->lock);
      mossfw_condition_init(&ret->cond);
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_ringbuffarray_delete
 ****************************************************************************/

void mossfw_ringbuffarray_delete(mossfw_ringbuffarray_t *ary)
{
  if (ary)
    {
      mossfw_lock_take(&ary->lock);
      if (ary->stored)
        {
          for (; ary->stored; ary->stored = ary->stored->next)
            {
              mossfw_data_free(ary->stored->data);
            }
        }

      free(ary->top);
      mossfw_lock_give(&ary->lock);
      free(ary);
    }
}

/****************************************************************************
 * name: mossfw_ringbuffarray_isempty
 ****************************************************************************/

static bool mossfw_ringbuffarray_isempty_nolock(mossfw_ringbuffarray_t *ary)
{
  return ary->stored == NULL;
}

bool mossfw_ringbuffarray_isempty(mossfw_ringbuffarray_t *ary)
{
  bool ret = true;

  if (ary)
    {
      mossfw_lock_take(&ary->lock);
      ret = mossfw_ringbuffarray_isempty_nolock(ary);
      mossfw_lock_give(&ary->lock);
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_ringbuffarray_isfull
 ****************************************************************************/

static bool mossfw_ringbuffarray_isfull_nolock(mossfw_ringbuffarray_t *ary)
{
  return ary->total_depth == ary->stored_num;
}

bool mossfw_ringbuffarray_isfull(mossfw_ringbuffarray_t *ary)
{
  bool ret = false;

  if (ary)
    {
      mossfw_lock_take(&ary->lock);
      ret = mossfw_ringbuffarray_isfull_nolock(ary);
      mossfw_lock_give(&ary->lock);
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_ringbuffarray_storednum
 ****************************************************************************/

static int
mossfw_ringbuffarray_storednum_nolock(mossfw_ringbuffarray_t *ary)
{
  return ary->stored_num;
}

int mossfw_ringbuffarray_storednum(mossfw_ringbuffarray_t *ary)
{
  int ret = 0;

  if (ary)
    {
      mossfw_lock_take(&ary->lock);
      ret = mossfw_ringbuffarray_storednum_nolock(ary);
      mossfw_lock_give(&ary->lock);
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_ringbuffarray_storedbytes
 ****************************************************************************/

static int
mossfw_ringbuffarray_storedbytes_nolock(mossfw_ringbuffarray_t *ary)
{
  return ary->stored_bytes;
}

int mossfw_ringbuffarray_storedbytes(mossfw_ringbuffarray_t *ary)
{
  int ret = 0;

  if (ary)
    {
      mossfw_lock_take(&ary->lock);
      ret = mossfw_ringbuffarray_storedbytes_nolock(ary);
      mossfw_lock_give(&ary->lock);
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_ringbuffarray_getdata
 ****************************************************************************/

mossfw_data_t *mossfw_ringbuffarray_getdata(mossfw_ringbuffarray_t *ary,
                                            int *used, bool nonblock)
{
  mossfw_data_t *ret = NULL;
  mossfw_data_container_t *ctr = NULL;

  if (ary)
    {
      mossfw_lock_take(&ary->lock);

      if (nonblock)
        {
          if (ary->is_stop || mossfw_ringbuffarray_isempty_nolock(ary))
            {
              mossfw_lock_give(&ary->lock);
              return NULL;
            }
        }
      else
        {
          while (!ary->is_stop && mossfw_ringbuffarray_isempty_nolock(ary))
            {
              mossfw_condition_wait(&ary->cond, &ary->lock);
            }

          if (ary->is_stop)
            {
              mossfw_lock_give(&ary->lock);
              return NULL;
            }
        }

      ctr = ary->stored;
      ret = ctr->data;
      ctr->data = NULL; /* This effects as free the container */

      ary->stored = ctr->next;
      ary->stored_num--;
      ary->stored_bytes -= (ret->data_bytes - ary->usedidx);

      if (used)
        {
          *used = ary->usedidx;
        }

      ary->usedidx = 0;

      mossfw_condition_notice(&ary->cond);
      mossfw_lock_give(&ary->lock);

      /* No need delete and refer for mamupilating reference counter.
       * Because just increment and decrement it.
       */
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_ringbuffarray_releasedata
 ****************************************************************************/

mossfw_data_t *mossfw_ringbuffarray_releasedata(mossfw_ringbuffarray_t *ary)
{
  mossfw_data_t *ret = NULL;
  mossfw_data_container_t *ctr = NULL;

  if (ary)
    {
      mossfw_lock_take(&ary->lock);

      if (mossfw_ringbuffarray_isempty_nolock(ary))
        {
          mossfw_lock_give(&ary->lock);
          return NULL;
        }

      ctr = ary->stored;
      ret = ctr->data;
      ctr->data = NULL; /* This effects as free the container */

      ary->stored = ctr->next;
      ary->stored_num--;
      ary->stored_bytes -= (ret->data_bytes - ary->usedidx);

      ary->usedidx = 0;

      mossfw_lock_give(&ary->lock);

      /* No need delete and refer for mamupilating reference counter.
       * Because just increment and decrement it.
       */
    }

  return ret;
}
/****************************************************************************
 * name: mossfw_ringbuffarray_backdatarest
 ****************************************************************************/

bool mossfw_ringbuffarray_backdatarest(mossfw_ringbuffarray_t *ary,
                                    mossfw_data_t *dat, int used,
                                    bool nonblock)
{
  mossfw_data_container_t *ctr;

  if (ary)
    {
      mossfw_lock_take(&ary->lock);
      if (dat->data_bytes <= used)
        {
          mossfw_lock_give(&ary->lock);
          mossfw_dprint("Called %s with over-used data.\n", __func__);
          mossfw_dprint("No store the data on top.\n");
          return false;
        }

      if (ary->usedidx)
        {
          mossfw_lock_give(&ary->lock);
          mossfw_dprint("Called %s in spite of "
                     "still remain some rest data...\n", __func__);
          return false;
        }

      if (nonblock)
        {
          if (ary->is_stop || mossfw_ringbuffarray_isfull_nolock(ary))
            {
              mossfw_lock_give(&ary->lock);
              return false;
            }
        }
      else
        {
          while (!ary->is_stop && mossfw_ringbuffarray_isfull_nolock(ary))
            {
              mossfw_condition_wait(&ary->cond, &ary->lock);
            }

          if (ary->is_stop)
            {
              mossfw_lock_give(&ary->lock);
              return false;
            }
        }

      ctr = find_free(ary->top, ary->total_depth);

      mossfw_data_refer(dat);
      ctr->data = dat;
      ctr->next = NULL;
      if (ary->stored)
        {
          ctr->next = ary->stored;
        }

      ary->stored = ctr;

      ary->stored_num++;
      ary->stored_bytes += (dat->data_bytes - used);
      ary->usedidx = used;

      mossfw_condition_notice(&ary->cond);
      mossfw_lock_give(&ary->lock);

      return true;
    }

  return false;
}

/****************************************************************************
 * name: mossfw_ringbuffarray_setdata
 ****************************************************************************/

bool mossfw_ringbuffarray_setdata(mossfw_ringbuffarray_t *ary,
                               mossfw_data_t *dat, bool nonblock)
{
  mossfw_data_container_t *ctr;

  if (ary)
    {
      mossfw_lock_take(&ary->lock);

      if (nonblock)
        {
          if (ary->is_stop || mossfw_ringbuffarray_isfull_nolock(ary))
            {
              mossfw_lock_give(&ary->lock);
              return false;
            }
        }
      else
        {
          while (!ary->is_stop && mossfw_ringbuffarray_isfull_nolock(ary))
            {
              mossfw_condition_wait(&ary->cond, &ary->lock);
            }

          if (ary->is_stop)
            {
              mossfw_lock_give(&ary->lock);
              return false;
            }
        }

      ctr = find_free(ary->top, ary->total_depth);

      mossfw_data_refer(dat);
      ctr->data = dat;
      ctr->next = NULL;
      if (ary->stored)
        {
          add_tail(ary->stored, ctr);
        }
      else
        {
          ary->stored = ctr;
        }

      ary->stored_num++;
      ary->stored_bytes += dat->data_bytes;

      mossfw_condition_notice(&ary->cond);
      mossfw_lock_give(&ary->lock);

      return true;
    }

  return false;
}

/****************************************************************************
 * name: mossfw_ringbuffarray_setstop
 ****************************************************************************/

void mossfw_ringbuffarray_setstop(mossfw_ringbuffarray_t *ary, bool stop)
{
  mossfw_lock_take(&ary->lock);
  ary->is_stop = stop;
  mossfw_condition_notice(&ary->cond);
  mossfw_lock_give(&ary->lock);
}
