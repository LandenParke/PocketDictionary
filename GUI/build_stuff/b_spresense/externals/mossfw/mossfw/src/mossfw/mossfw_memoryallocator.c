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
#include <stdlib.h>

#include <mossfw/mossfw_debug.h>
#include <mossfw/mossfw_lock.h>
#include <mossfw/mossfw_data.h>
#include <mossfw/mossfw_memoryallocator.h>

/****************************************************************************
 * Private Data Types
 ****************************************************************************/

struct mossfw_fixed_mempool_s
{
  int block_sz;
  int block_num;
  void *data_area;
  mossfw_data_container_t *free;
  mossfw_lock_t lock;
  mossfw_condition_t cond;
};
typedef struct mossfw_fixed_mempool_s mossfw_fixed_mempool_t;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: add_tail
 ****************************************************************************/

static void add_tail(mossfw_data_container_t **list,
                     mossfw_data_container_t *item)
{
  if (*list == NULL)
    {
      *list = item;
    }
  else
    {
      mossfw_data_container_t *tmp;
      for (tmp = *list; tmp->next; tmp = tmp->next);
      tmp->next = item;
    }
}

/****************************************************************************
 * name: init_container
 ****************************************************************************/

static void init_container(mossfw_fixed_mempool_t *pool,
                           mossfw_data_container_t *ctr,
                           mossfw_data_t *item,
                           char *data)
{
  item->refcnt = 0;
  item->data_bytes = 0;
  mossfw_lock_init(&item->lock);
  item->data.xc = (mossfw_data_v1c_t *)data;
  item->timestamp = 0;
  item->fs = 0;

  add_tail(&pool->free, ctr);
}

/****************************************************************************
 * name: count_free
 ****************************************************************************/

static int count_free(mossfw_fixed_mempool_t *pool)
{
  int cnt = 0;
  mossfw_data_container_t *container;

  for (container = pool->free; container; container = container->next)
    {
      cnt++;
    }

  return cnt;
}

/****************************************************************************
 * name: mossfw_fixedmem_allocate
 ****************************************************************************/

static mossfw_data_t *mossfw_fixedmem_allocate(void *inst, int size,
                                               bool nonblock)
{
  mossfw_data_container_t *ctr = NULL;
  mossfw_fixed_mempool_t *pool = (mossfw_fixed_mempool_t *)inst;

  if (pool->block_sz == size)
    {
      mossfw_lock_take(&pool->lock);

      if (nonblock)
        {
          if (!pool->free)
            {
              mossfw_lock_give(&pool->lock);
              return NULL;
            }
        }
      else
        {
          while (!pool->free)
            {
              mossfw_condition_wait(&pool->cond, &pool->lock);
            }
        }

      ctr = pool->free;
      pool->free = ctr->next;

      ctr->next = NULL;
      ctr->data->refcnt = 1;
      ctr->data->data_bytes = 0;
      ctr->data->timestamp = 0;

      mossfw_lock_give(&pool->lock);
    }

  return ctr ? ctr->data : NULL;
}

/****************************************************************************
 * name: mossfw_fixedmem_free
 ****************************************************************************/

static void mossfw_fixedmem_free(void *inst,
                              mossfw_data_t *mem)
{
  mossfw_fixed_mempool_t *pool = (mossfw_fixed_mempool_t *)inst;
  mossfw_data_container_t *ctr = &((mossfw_data_container_t *)mem)[-1];

  ctr->next = NULL;
  mossfw_lock_take(&pool->lock);
  add_tail(&pool->free, ctr);
  mossfw_lock_give(&pool->lock);

  mossfw_condition_notice(&pool->cond);
}

/****************************************************************************
 * name: mossfw_fixedmem_getblksize
 ****************************************************************************/

int mossfw_fixedmem_getblksize(void *priv)
{
  return ((mossfw_fixed_mempool_t *)priv)->block_sz;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossfw_fixedmem_create
 ****************************************************************************/

mossfw_allocator_t *mossfw_fixedmem_create(int block_sz, int block_num)
{
  int i;
  mossfw_allocator_t *ret;
  mossfw_fixed_mempool_t *pool;
  mossfw_data_container_t *ctr;
  mossfw_data_t *dat;

  if (!block_sz || !block_num)
    {
      return NULL;
    }

  ret = (mossfw_allocator_t *)malloc(sizeof(mossfw_allocator_t));

  if (ret)
    {
      pool = (mossfw_fixed_mempool_t *)
                malloc(sizeof(mossfw_fixed_mempool_t));
      if (!pool)
        {
          free(ret);
          return NULL;
        }

      pool->free = NULL;
      pool->block_sz = block_sz;
      pool->block_num = block_num;
      mossfw_lock_init(&pool->lock);
      mossfw_condition_init(&pool->cond);

      for (i = 0; i < block_num; i++)
        {
          ctr = (mossfw_data_container_t *)
                    malloc(sizeof(mossfw_data_container_t) +
                           sizeof(mossfw_data_t) + (block_sz));
          if (ctr)
            {
              dat = (mossfw_data_t *)&ctr[1];
              dat->data.xc = (mossfw_data_v1c_t *)&dat[1];
              ctr->next = NULL;
              ctr->data = dat;
              init_container(pool, ctr, dat, (char *)&dat[1]);
              dat->allocator = ret;
            }
          else
            {
              while (pool->free)
                {
                  ctr = pool->free->next;
                  free(pool->free);
                  pool->free = ctr;
                }

              free(pool);
              free(ret);

              return NULL;
            }
        }

      ret->alloc = mossfw_fixedmem_allocate;
      ret->free = mossfw_fixedmem_free;
      ret->get_blksz = mossfw_fixedmem_getblksize;
      ret->priv = (void *)pool;
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_fixedmem_delete
 ****************************************************************************/

int mossfw_fixedmem_delete(mossfw_allocator_t *inst)
{
  mossfw_fixed_mempool_t *pool;
  mossfw_data_container_t *ctr;
  int ret = ERROR;

  if (inst)
    {
      pool = (mossfw_fixed_mempool_t *)inst->priv;
      if (pool)
        {
          mossfw_lock_take(&pool->lock);

          if (count_free(pool) != pool->block_num)
            {
              mossfw_dprint("Some memory are leaked....!"
                            " exp:%d, act:%d\n",
                            pool->block_num, count_free(pool));
            }

          while (pool->free)
            {
              ctr = pool->free->next;
              free(pool->free);
              pool->free = ctr;
            }

          mossfw_lock_give(&pool->lock);
          mossfw_lock_fin(&pool->lock);

          free(pool);
          ret = OK;
        }

      free(inst);
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_data_alloc
 ****************************************************************************/

mossfw_data_t *mossfw_data_alloc(mossfw_allocator_t *inst, int size,
                                 bool nonblock)
{
  if (inst)
    {
      return inst->alloc(inst->priv, size, nonblock);
    }

  return NULL;
}

/****************************************************************************
 * name: mossfw_data_free
 ****************************************************************************/

void mossfw_data_free(mossfw_data_t *mem)
{
  if (mem)
    {
      mossfw_lock_take(&mem->lock);
      mem->refcnt--;
      if (mem->refcnt <= 0)
        {
          /* No one uses this memory block any more.
           * So the lock can be unlocked safely.
           */

          mossfw_lock_give(&mem->lock);
          mem->allocator->free(mem->allocator->priv, mem);
        }
      else
        {
          mossfw_lock_give(&mem->lock);
        }
    }
}

/****************************************************************************
 * name: mossfw_data_refer
 ****************************************************************************/

void mossfw_data_refer(mossfw_data_t *mem)
{
  if (mem)
    {
      mossfw_lock_take(&mem->lock);
      mem->refcnt++;
      mossfw_lock_give(&mem->lock);
    }
}

/****************************************************************************
 * name: mossfw_allocate_blocksize
 ****************************************************************************/

int mossfw_fixedsize_allocator(mossfw_allocator_t *inst)
{
  int ret = -1;
  if (inst)
    {
      ret = inst->get_blksz(inst->priv);
    }

  return ret;
}
