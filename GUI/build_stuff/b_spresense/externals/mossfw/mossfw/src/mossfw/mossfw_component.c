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

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <mossfw/mossfw_debug.h>
#include <mossfw/mossfw_data.h>
#include <mossfw/mossfw_ringbuff.h>
#include <mossfw/mossfw_ringbuffary.h>
#include <mossfw/mossfw_component.h>

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name:  data_typebytes
 ****************************************************************************/

static int data_typebytes(int type)
{
  int ret;
  switch (MOSSFW_DATA_TYPE(type) + MOSSFW_DATA_TYPEGRP(type))
    {
      case MOSSFW_DATA_TYPE_SHORT + MOSSFW_DATA_TYPEGRP_V8:
        ret = sizeof(mossfw_data_v8s_t);
        break;
      case MOSSFW_DATA_TYPE_INT32 + MOSSFW_DATA_TYPEGRP_V3:
        ret = sizeof(mossfw_data_v3i32_t);
        break;
      case MOSSFW_DATA_TYPE_INT32 + MOSSFW_DATA_TYPEGRP_V2:
        ret = sizeof(mossfw_data_v2i32_t);
        break;
      case MOSSFW_DATA_TYPE_INT32 + MOSSFW_DATA_TYPEGRP_V1:
        ret = sizeof(mossfw_data_v1i32_t);
        break;
      case MOSSFW_DATA_TYPE_SHORT + MOSSFW_DATA_TYPEGRP_V3:
        ret = sizeof(mossfw_data_v3s_t);
        break;
      case MOSSFW_DATA_TYPE_SHORT + MOSSFW_DATA_TYPEGRP_V2:
        ret = sizeof(mossfw_data_v2s_t);
        break;
      case MOSSFW_DATA_TYPE_SHORT + MOSSFW_DATA_TYPEGRP_V1:
        ret = sizeof(mossfw_data_v1s_t);
        break;
      case MOSSFW_DATA_TYPE_CHAR  + MOSSFW_DATA_TYPEGRP_V3:
        ret = sizeof(mossfw_data_v3c_t);
        break;
      case MOSSFW_DATA_TYPE_CHAR  + MOSSFW_DATA_TYPEGRP_V2:
        ret = sizeof(mossfw_data_v2c_t);
        break;
      case MOSSFW_DATA_TYPE_CHAR  + MOSSFW_DATA_TYPEGRP_V1:
        ret = sizeof(mossfw_data_v1c_t);
        break;
      case MOSSFW_DATA_TYPE_FLOAT + MOSSFW_DATA_TYPEGRP_V3:
        ret = sizeof(mossfw_data_v3f_t);
        break;
      case MOSSFW_DATA_TYPE_FLOAT + MOSSFW_DATA_TYPEGRP_V2:
        ret = sizeof(mossfw_data_v2f_t);
        break;
      case MOSSFW_DATA_TYPE_FLOAT + MOSSFW_DATA_TYPEGRP_V1:
        ret = sizeof(mossfw_data_v1f_t);
        break;
      case MOSSFW_DATA_TYPE_FLOAT + MOSSFW_DATA_TYPEGRP_Q:
        ret = sizeof(mossfw_data_qf_t);
        break;
      default:
        ret = 0;
        break;
    }

  return ret;
}

/****************************************************************************
 * name: is_enoughdata
 ****************************************************************************/

static bool is_enoughdata(mossfw_input_t *in)
{
  bool ret = false;
  int current_size;

  if (in)
    {
      mossfw_lock_take(&in->lock);

      if (in->wait_datasize >= 0)
        {
          current_size = MOSSFW_DATA_TYPE_ISARRAY(in->type) ?
                         mossfw_ringbuffarray_storedbytes(in->ringbuff.array) :
                         mossfw_ringbuff_storedbytes(in->ringbuff.single);
          ret = in->wait_datasize <= current_size;
        }

      mossfw_lock_give(&in->lock);
    }

  return ret;
}

/****************************************************************************
 * name: all_enouchdata
 ****************************************************************************/

static bool all_enoughdata(mossfw_callback_op_t *op)
{
  bool ret = false;
  mossfw_input_t *in = op->input;

  if (in)
    {
      ret = true;
      while (ret && in)
        {
          ret &= is_enoughdata(in);
          in = in->cb_next;
        }
    }

  return ret;
}

/****************************************************************************
 * name: async_worker
 ****************************************************************************/

static void *async_worker(void *arg)
{
  mossfw_callback_op_t *op = (mossfw_callback_op_t *)arg;

  while (op->async->is_running)
    {
      mossfw_lock_take(&op->lock);

      while (op->async->is_running && !all_enoughdata(op))
        {
          mossfw_condition_wait(&op->async->cond, &op->lock);
        }

      mossfw_lock_give(&op->lock);

      if (op->operate)
        {
          mossfw_lock_take(&op->lock);

          while (op->async->is_running && all_enoughdata(op))
            {
              op->operate(op, op->op_arg);
            }

          mossfw_lock_give(&op->lock);
        }
    }

  return NULL;
}

/****************************************************************************
 * name: add_bind_tail
 ****************************************************************************/

static void add_bind_tail(mossfw_output_t *out, mossfw_input_t *in)
{
  mossfw_input_t *tmp;

  mossfw_lock_take(&out->bindlock);

  if (out->binded)
    {
      for (tmp = out->binded; tmp->bind_next; tmp = tmp->bind_next);
      tmp->bind_next = in;
    }
  else
    {
      out->binded = in;
    }

  in->bind_next = NULL;
  mossfw_lock_give(&out->bindlock);
}

/****************************************************************************
 * name: rem_binded
 ****************************************************************************/

static int rem_binded(mossfw_output_t *out, mossfw_input_t *in)
{
  int ret = -EINVAL;
  mossfw_input_t *tmp;
  mossfw_input_t *last;

  if (out && in)
    {
      mossfw_lock_take(&out->bindlock);

      last = NULL;
      for (tmp = out->binded; tmp; tmp = tmp->bind_next)
        {
          if (in == tmp)
            {
              if (last)
                {
                  last->bind_next = tmp->bind_next;
                }
              else
                {
                  out->binded = tmp->bind_next;
                }

              tmp->bind_next = NULL;
              ret = 0;
              break;
            }

          last = tmp;
        }

      mossfw_lock_give(&out->bindlock);
    }

  return ret;
}

/****************************************************************************
 * name: send_to_input
 ****************************************************************************/

static bool send_to_input(mossfw_input_t *in, mossfw_onedata_t *dat)
{
  if (mossfw_ringbuff_setdata(in->ringbuff.single, dat, false))
    {
      if (in->op)
        {
          mossfw_lock_take(&in->op->lock);

          if (in->op->async)
            {
              mossfw_condition_notice(&in->op->async->cond);
            }

          mossfw_lock_give(&in->op->lock);
        }

      return true;
    }

  return false;
}

/****************************************************************************
 * name: send_to_inputarray
 ****************************************************************************/

static bool send_to_inputarray(mossfw_input_t *in, mossfw_data_t *dat)
{
  if (mossfw_ringbuffarray_setdata(in->ringbuff.array, dat, false))
    {
      if (in->op)
        {
          mossfw_lock_take(&in->op->lock);

          if (in->op->async)
            {
              mossfw_condition_notice(&in->op->async->cond);
            }

          mossfw_lock_give(&in->op->lock);
        }

      return true;
    }

  return false;
}

/****************************************************************************
 * name: call_operator
 ****************************************************************************/

static void call_operator(mossfw_input_t *in)
{
  mossfw_callback_op_t *op = in->op;

  if (op)
    {
      mossfw_lock_take(&op->lock);

      if (op->operate && !op->async)
        {
          while (all_enoughdata(op))
            {
              op->operate(op, op->op_arg);
            }
        }

      mossfw_lock_give(&op->lock);
    }
}

/****************************************************************************
 * name: add_op_tail
 ****************************************************************************/

static void add_op_tail(mossfw_callback_op_t *op, mossfw_input_t *in)
{
  mossfw_input_t *tmp;

  if (op->input)
    {
      for (tmp = op->input; tmp->cb_next; tmp = tmp->cb_next);
      tmp->cb_next = in;
    }
  else
    {
      op->input = in;
    }

  in->cb_next = NULL;
}

/****************************************************************************
 * name: rem_op
 ****************************************************************************/

static void rem_op(mossfw_callback_op_t *op, mossfw_input_t *in)
{
  mossfw_input_t *tmp;
  mossfw_input_t *last;

  if (op->input == in)
    {
      op->input = in->cb_next;
      in->cb_next = NULL;
    }
  else
    {
      last = NULL;
      for (tmp = op->input; tmp; tmp = tmp->cb_next)
        {
          if (in == tmp)
            {
              last->cb_next = tmp->cb_next;
              tmp->cb_next = NULL;
            }

          last = tmp;
        }
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: mossfw_start_callback_op
 ****************************************************************************/

int mossfw_start_callback_op(mossfw_callback_op_t *op)
{
  if (op && op->async)
    {
      if (op->stack_sz > 0 && op->prio > 0)
        {
          return mossfw_create_thread_attr(&op->async->tid, async_worker,
                                           (void *)op, op->prio,
                                           op->stack_sz);
        }
      else
        {
          return mossfw_create_thread(&op->async->tid, async_worker,
                                      (void *)op);
        }
    }
  else
    {
      return OK;
    }
}

/****************************************************************************
 * name: mossfw_input_create
 ****************************************************************************/

mossfw_input_t *mossfw_input_create(uint32_t type, int block_num)
{
  mossfw_input_t *ret = NULL;
  int type_bytes;

  type_bytes = data_typebytes(type);

  if (type_bytes)
    {
      ret = (mossfw_input_t *)malloc(sizeof(mossfw_input_t));
      if (ret)
        {
          switch (MOSSFW_DATA_TYPEARRAY(type))
            {
              case MOSSFW_DATA_TYPEARRAY_SINGLE:
                ret->ringbuff.single =
                              mossfw_ringbuff_create(type_bytes, block_num);
                break;
              case MOSSFW_DATA_TYPEARRAY_ARRAY:
                ret->ringbuff.array = mossfw_ringbuffarray_create(block_num);
                break;
              default:
                ret->ringbuff.single = NULL;
                break;
            }

          if (ret->ringbuff.single == NULL)
            {
              free(ret);
              return NULL;
            }

          ret->type = type;
          ret->out = NULL;
          ret->wait_datasize = -1;
          mossfw_lock_init(&ret->lock);
          ret->op = NULL;
          ret->bind_next = NULL;
          ret->cb_next = NULL;
        }
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_output_create
 ****************************************************************************/

mossfw_output_t *mossfw_output_create(uint32_t type)
{
  mossfw_output_t *ret;

  ret = (mossfw_output_t *)malloc(sizeof(mossfw_output_t));
  if (ret)
    {
      mossfw_lock_init(&ret->bindlock);
      ret->binded = NULL;
      ret->type = type;
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_callback_op_create
 ****************************************************************************/

mossfw_callback_op_t *mossfw_callback_op_create(mossfw_operator_t op,
                                                unsigned long arg,
                                                bool async)
{
  return mossfw_callback_op_create_attr(op, arg, async, -1, -1);
}

/****************************************************************************
 * name: mossfw_callback_op_create_attr
 ****************************************************************************/

mossfw_callback_op_t *mossfw_callback_op_create_attr(mossfw_operator_t op,
                                                     unsigned long arg,
                                                     bool async, int prio,
                                                     int stacksz)
{
  mossfw_callback_op_t *ret = NULL;

  if (op)
    {
      ret = (mossfw_callback_op_t *)malloc(sizeof(mossfw_callback_op_t));

      if (ret)
        {
          ret->async = NULL;
          if (async)
            {
              ret->async = (mossfw_async_op_t *)
                               malloc(sizeof(mossfw_async_op_t));
              if (!ret->async)
                {
                  free(ret);
                  return NULL;
                }

              ret->async->is_running = true;
              mossfw_condition_init(&ret->async->cond);
            }

          mossfw_lock_init(&ret->lock);
          ret->operate = op;
          ret->op_arg = arg;
          ret->prio = prio;
          ret->stack_sz = stacksz;
          ret->input = NULL;

          if (mossfw_start_callback_op(ret) != OK)
            {
              mossfw_dprint("Error to start async thread...\n");
              free(ret->async);
              free(ret);
              return NULL;
            }
        }
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_input_delete
 ****************************************************************************/

void mossfw_input_delete(mossfw_input_t *in)
{
  if (in)
    {
      if (in->ringbuff.single)
        {
          switch (MOSSFW_DATA_TYPEARRAY(in->type))
            {
              case MOSSFW_DATA_TYPEARRAY_SINGLE:
                mossfw_ringbuff_delete(in->ringbuff.single);
                break;
              case MOSSFW_DATA_TYPEARRAY_ARRAY:
                {
                  mossfw_data_t *dat;

                  /* force stop false to get stored buffer */

                  in->ringbuff.array->is_stop = false;
                  for (dat = mossfw_ringbuffarray_getdata(in->ringbuff.array,
                                                          NULL, true);
                       dat;
                       dat = mossfw_ringbuffarray_getdata(in->ringbuff.array,
                                                          NULL, true))
                    {
                      mossfw_data_free(dat);
                    }
                }

                mossfw_ringbuffarray_delete(in->ringbuff.array);
                break;
              default:
                break;
            }
        }

      in->ringbuff.single = NULL;

      free(in);
    }
}

/****************************************************************************
 * name: mossfw_output_delete
 ****************************************************************************/

void mossfw_output_delete(mossfw_output_t *out)
{
  if (out)
    {
      free(out);
    }
}

/****************************************************************************
 * name: mossfw_callback_op_delete
 ****************************************************************************/

void mossfw_callback_op_delete(mossfw_callback_op_t *op)
{
  mossfw_input_t *in;
  mossfw_input_t *last;
  if (op)
    {
      if (op->async)
        {
          mossfw_stop_callback_op(op);
        }

      mossfw_lock_take(&op->lock);

      in = op->input;
      while (in)
        {
          last = in;
          in->op = NULL;

          in = in->cb_next;
          last->cb_next = NULL;
        }

      mossfw_lock_give(&op->lock);

      if (op->async)
        {
          free(op->async);
        }

      free(op);
    }
}

/****************************************************************************
 * name: mossfw_bind_inout
 ****************************************************************************/

int mossfw_bind_inout(mossfw_output_t *out, mossfw_input_t *in,
                      uint32_t mask)
{
  if (!out || !in)
    {
      return -EINVAL;
    }

  /* ARRAY or SIMGLE must be checked. */

  mask |= MOSSFW_DATA_TYPEARRAY_MASK;
  if ((out->type & mask) != (in->type & mask))
    {
      return -EIO;
    }

  if (in->out)
    {
      return -EALREADY;
    }

  add_bind_tail(out, in);
  in->out = out;

  return OK;
}

/****************************************************************************
 * name: mossfw_unbind_inout
 ****************************************************************************/

int mossfw_unbind_inout(mossfw_output_t *out, mossfw_input_t *in)
{
  int ret;

  ret = rem_binded(out, in);
  if (ret == 0)
    {
      in->out = NULL;
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_output_ismultibinded
 ****************************************************************************/

bool mossfw_output_ismultibinded(mossfw_output_t *out)
{
  bool ret = false;

  if (out)
    {
      mossfw_lock_take(&out->bindlock);
      ret = (out->binded && out->binded->bind_next);
      mossfw_lock_give(&out->bindlock);
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_deliver_data
 ****************************************************************************/

int mossfw_deliver_data(mossfw_output_t *out, mossfw_onedata_t *dat)
{
  int ret = -EAGAIN;
  mossfw_input_t *in;

  if (!out || !dat)
    {
      return -EINVAL;
    }

  if (!MOSSFW_DATA_TYPE_ISSINGLE(out->type))
    {
      return -EIO;
    }

  mossfw_lock_take(&out->bindlock);

  for (in = out->binded; in; in = in->bind_next)
    {
      if (send_to_input(in, dat))
        {
          call_operator(in);
          ret = OK;
        }
    }

  mossfw_lock_give(&out->bindlock);

  return ret;
}

/****************************************************************************
 * name: mossfw_deliver_dataarray
 ****************************************************************************/

int mossfw_deliver_dataarray(mossfw_output_t *out, mossfw_data_t *dat)
{
  int ret = -EAGAIN;
  mossfw_input_t *in;

  if (!out || !dat)
    {
      return -EINVAL;
    }

  if (!MOSSFW_DATA_TYPE_ISARRAY(out->type))
    {
      return -EIO;
    }

  mossfw_lock_take(&out->bindlock);

  for (in = out->binded; in; in = in->bind_next)
    {
      if (send_to_inputarray(in, dat))
        {
          call_operator(in);
          ret = OK;
        }
    }

  mossfw_lock_give(&out->bindlock);

  return ret;
}

/****************************************************************************
 * name: mossfw_stop_callback_op
 ****************************************************************************/

void mossfw_stop_callback_op(mossfw_callback_op_t *op)
{
  mossfw_async_op_t *as;

  if (op)
    {
      mossfw_lock_take(&op->lock);
      if (op->async)
        {
          as = op->async;
          if (as->is_running)
            {
              as->is_running = false;
              mossfw_condition_notice(&as->cond);
              mossfw_lock_give(&op->lock);
              mossfw_thread_join(&as->tid);
              return;
            }
        }
      mossfw_lock_give(&op->lock);
    }

}

/****************************************************************************
 * name: mossfw_get_delivereddata_num
 ****************************************************************************/

int mossfw_get_delivereddata_num(mossfw_input_t *in)
{
  int ret = -EINVAL;

  if (in)
    {
      ret = MOSSFW_DATA_TYPE_ISARRAY(in->type) ?
                 mossfw_ringbuffarray_storedbytes(in->ringbuff.array) :
                 mossfw_ringbuff_storedbytes(in->ringbuff.single);
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_deliverback_dataarray
 ****************************************************************************/

bool mossfw_deliverback_dataarray(mossfw_input_t *in, mossfw_data_t *dat,
                               int used)
{
  if (in && dat)
    {
      return mossfw_ringbuffarray_backdatarest(in->ringbuff.array,
                                               dat, used, false);
    }

  return false;
}

/****************************************************************************
 * name: mossfw_release_delivereddata_array
 ****************************************************************************/

mossfw_data_t *mossfw_release_delivereddata_array(mossfw_input_t *in)
{
  mossfw_data_t *ret = NULL;

  if (in)
    {
      if (MOSSFW_DATA_TYPE_ISARRAY(in->type))
        {
          ret = mossfw_ringbuffarray_releasedata(in->ringbuff.array);
        }
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_get_delivereddata_array
 ****************************************************************************/

mossfw_data_t *mossfw_get_delivereddata_array(mossfw_input_t *in,
                                              int sz, int *used)
{
  mossfw_data_t *ret = NULL;

  if (in)
    {
      if (MOSSFW_DATA_TYPE_ISARRAY(in->type))
        {
          if (mossfw_ringbuffarray_storedbytes(in->ringbuff.array) >= sz)
            {
              ret = mossfw_ringbuffarray_getdata(in->ringbuff.array,
                                                 used, true);
            }
        }
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_get_delivereddata_single
 ****************************************************************************/

int mossfw_get_delivereddata_single(mossfw_input_t *in,
                                    mossfw_onedata_t *rdat)
{
  int ret = -EINVAL;

  if (in)
    {
      if (MOSSFW_DATA_TYPE_ISSINGLE(in->type))
        {
          if (rdat)
            {
              ret = data_typebytes(in->type);
              if (mossfw_ringbuff_storedbytes(in->ringbuff.single) >= ret)
                {
                  memcpy(rdat,
                         mossfw_ringbuff_getdata(in->ringbuff.single, true),
                         ret);
                  mossfw_ringbuff_releaseblock(in->ringbuff.single);
                }
              else
                {
                  ret = 0;
                }
            }
        }
    }

  return ret;
}

/****************************************************************************
 * name: mossfw_set_waitcondition
 ****************************************************************************/

int mossfw_set_waitcondition(mossfw_input_t *in, int wait_size,
                             mossfw_callback_op_t *op)
{
  if (in == NULL || wait_size == 0 || op == NULL)
    {
      return -EINVAL;
    }

  mossfw_lock_take(&in->lock);
  in->wait_datasize = wait_size;
  mossfw_lock_give(&in->lock);

  if (MOSSFW_DATA_TYPE_ISARRAY(in->type))
    {
      mossfw_ringbuffarray_setstop(in->ringbuff.array,
                                   wait_size < 0 ? true : false);
    }
  else
    {
      mossfw_ringbuff_setstop(in->ringbuff.single,
                              wait_size < 0 ? true : false);
    }

  mossfw_lock_take(&op->lock);
  in->op = op;
  add_op_tail(op, in);
  mossfw_lock_give(&op->lock);

  return OK;
}

/****************************************************************************
 * name: mossfw_unset_waitcondition
 ****************************************************************************/

int mossfw_unset_waitcondition(mossfw_input_t *in,
                               mossfw_callback_op_t *op)
{
  if (in == NULL)
    {
      return -EINVAL;
    }

  mossfw_lock_take(&in->lock);
  in->wait_datasize = -1;
  mossfw_lock_give(&in->lock);

  if (MOSSFW_DATA_TYPE_ISARRAY(in->type))
    {
      mossfw_ringbuffarray_setstop(in->ringbuff.array, true);
    }
  else
    {
      mossfw_ringbuff_setstop(in->ringbuff.single, true);
    }

  mossfw_lock_take(&op->lock);

  if (in->op == op)
    {
      rem_op(op, in);
      in->op = NULL;
    }

  mossfw_lock_give(&op->lock);

  return OK;
}

/****************************************************************************
 * name: mossfw_update_waitsize
 ****************************************************************************/

int mossfw_update_waitsize(mossfw_input_t *in, int wait_size)
{
  int old_val;

  if (MOSSFW_DATA_TYPE_ISARRAY(in->type))
    {
      mossfw_ringbuffarray_setstop(in->ringbuff.array,
                                   wait_size < 0 ? true : false);
    }
  else
    {
      mossfw_ringbuff_setstop(in->ringbuff.single,
                              wait_size < 0 ? true : false);
    }

  mossfw_lock_take(&in->lock);
  old_val = in->wait_datasize;
  in->wait_datasize = wait_size;
  mossfw_lock_give(&in->lock);

  mossfw_lock_take(&in->op->lock);

  if (in->op->async)
    {
      mossfw_condition_notice(&in->op->async->cond);
    }

  mossfw_lock_give(&in->op->lock);

  return old_val;
}

/****************************************************************************
 * name: mossfw_get_fanout
 ****************************************************************************/

int mossfw_get_fanout(mossfw_output_t *out)
{
  int ret = 0;
  mossfw_input_t *tmp;

  if (out)
    {
      for (tmp = out->binded; tmp;
           tmp = tmp->bind_next, ret++);
    }

  return ret;
}
