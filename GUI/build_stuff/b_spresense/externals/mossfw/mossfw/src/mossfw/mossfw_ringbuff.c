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
#include <mossfw/mossfw_ringbuff.h>

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: increment_idx
 ****************************************************************************/

static int increment_idx(mossfw_ringbuffer_t *buff, int idx)
{
  idx += buff->block_sz;
  return idx >= buff->buff_len ? idx - buff->buff_len : idx;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossfw_ringbuff_create
 ****************************************************************************/

mossfw_ringbuffer_t *mossfw_ringbuff_create(int block_sz, int block_num)
{
  mossfw_ringbuffer_t *ret = NULL;

  if (block_sz > 0 && block_num > 0)
    {
      ret = (mossfw_ringbuffer_t *)malloc(sizeof(mossfw_ringbuffer_t));
      if (ret)
        {
          ret->buff_len = block_sz * block_num;
          ret->buffer = (char *)malloc(ret->buff_len);
          if (ret->buffer)
            {
              ret->block_sz = block_sz;
              ret->ridx = 0;
              ret->widx = 0;
              ret->is_empty = true;
              ret->is_stop = false;
              mossfw_lock_init(&ret->lock);
              mossfw_condition_init(&ret->cond);
            }
          else
            {
              free(ret);
              ret = NULL;
            }
        }
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_ringbuff_delete
 ****************************************************************************/

void mossfw_ringbuff_delete(mossfw_ringbuffer_t *buff)
{
  if (buff)
    {
      if (buff->buffer)
        {
          free(buff->buffer);
        }

      free(buff);
    }
}

/****************************************************************************
 * name: mossfw_ringbuff_isempty
 ****************************************************************************/

static bool mossfw_ringbuff_isempty_nolock(mossfw_ringbuffer_t *buff)
{
  return buff->ridx == buff->widx && buff->is_empty;
}

bool mossfw_ringbuff_isempty(mossfw_ringbuffer_t *buff)
{
  bool ret;
  mossfw_lock_take(&buff->lock);
  ret = mossfw_ringbuff_isempty_nolock(buff);
  mossfw_lock_give(&buff->lock);
  return ret;
}

/****************************************************************************
 * name: mossfw_ringbuff_isfull
 ****************************************************************************/

static bool mossfw_ringbuff_isfull_nolock(mossfw_ringbuffer_t *buff)
{
  return buff->ridx == buff->widx && !buff->is_empty;
}

bool mossfw_ringbuff_isfull(mossfw_ringbuffer_t *buff)
{
  bool ret;
  mossfw_lock_take(&buff->lock);
  ret = mossfw_ringbuff_isfull_nolock(buff);
  mossfw_lock_give(&buff->lock);
  return ret;
}

/****************************************************************************
 * name: mossfw_ringbuff_storednum
 ****************************************************************************/

static int mossfw_ringbuff_storedbytes_nolock(mossfw_ringbuffer_t *buff)
{
  return (buff->is_empty) ? 0 :
         (buff->widx == buff->ridx) ? buff->buff_len :
         (buff->widx > buff->ridx) ? buff->widx - buff->ridx :
         buff->widx - buff->ridx + buff->buff_len;
}

int mossfw_ringbuff_storedbytes(mossfw_ringbuffer_t *buff)
{
  int ret;
  mossfw_lock_take(&buff->lock);
  ret = mossfw_ringbuff_storedbytes_nolock(buff);
  mossfw_lock_give(&buff->lock);
  return ret;
}

static int mossfw_ringbuff_storednum_nolock(mossfw_ringbuffer_t *buff)
{
  return mossfw_ringbuff_storedbytes_nolock(buff) / buff->block_sz;
}

int mossfw_ringbuff_storednum(mossfw_ringbuffer_t *buff)
{
  int ret;
  mossfw_lock_take(&buff->lock);
  ret = mossfw_ringbuff_storednum_nolock(buff);
  mossfw_lock_give(&buff->lock);
  return ret;
}

/****************************************************************************
 * name: mossfw_ringbufr_getdata
 ****************************************************************************/

void *mossfw_ringbuff_getdata(mossfw_ringbuffer_t *buff, bool nonblock)
{
  mossfw_lock_take(&buff->lock);

  if (nonblock)
    {
      if (buff->is_stop || mossfw_ringbuff_isempty_nolock(buff))
        {
          mossfw_lock_give(&buff->lock);
          return NULL;
        }
    }
  else
    {
      while (!buff->is_stop && mossfw_ringbuff_isempty_nolock(buff))
        {
          mossfw_condition_wait(&buff->cond, &buff->lock);
        }

      if (buff->is_stop)
        {
          mossfw_lock_give(&buff->lock);
          return NULL;
        }
    }

  mossfw_condition_notice(&buff->cond);
  mossfw_lock_give(&buff->lock);

  return &((char *)buff->buffer)[buff->ridx];
}

/****************************************************************************
 * name: mossfw_ringbuff_setdata
 ****************************************************************************/

bool mossfw_ringbuff_setdata(mossfw_ringbuffer_t *buff, void *blk,
                             bool nonblock)
{
  mossfw_lock_take(&buff->lock);

  if (nonblock)
    {
      if (buff->is_stop || mossfw_ringbuff_isfull_nolock(buff))
        {
          mossfw_lock_give(&buff->lock);
          return false;
        }
    }
  else
    {
      while (!buff->is_stop && mossfw_ringbuff_isfull_nolock(buff))
        {
          mossfw_condition_wait(&buff->cond, &buff->lock);
        }

      if (buff->is_stop)
        {
          mossfw_lock_give(&buff->lock);
          return false;
        }
    }

  memcpy(&((char *)buff->buffer)[buff->widx], blk,
         buff->block_sz);
  buff->widx = increment_idx(buff, buff->widx);
  buff->is_empty = false;

  mossfw_condition_notice(&buff->cond);
  mossfw_lock_give(&buff->lock);

  return true;
}

/****************************************************************************
 * name: mossfw_ringbuff_releasedata
 ****************************************************************************/

void mossfw_ringbuff_releaseblock(mossfw_ringbuffer_t *buff)
{
  mossfw_lock_take(&buff->lock);

  if (!mossfw_ringbuff_isempty_nolock(buff))
    {
      buff->ridx = increment_idx(buff, buff->ridx);
      if (buff->widx == buff->ridx)
        {
          buff->is_empty = true;
        }
    }

  mossfw_lock_give(&buff->lock);
}

/****************************************************************************
 * name: mossfw_ringbuff_setstop
 ****************************************************************************/

void mossfw_ringbuff_setstop(mossfw_ringbuffer_t *buff, bool stop)
{
  mossfw_lock_take(&buff->lock);
  buff->is_stop = stop;
  mossfw_condition_notice(&buff->cond);
  mossfw_lock_give(&buff->lock);
}
