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
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include "dummy_component1.h"
#include "dummy_component2.h"
#include "mossfw/mossfw_component.h"
#include "mossfw/mossfw_debug.h"
#include "unity.h"
#include "malloctest.h"
#include "pthreadtest.h"
#include "mossfw_component.c"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define MEM_BLKLEN (16)
#define MEM_BLKNUM (2)
#define TEST_ASYNC_LOOPNUM 1000000ul

/****************************************************************************
 * Private Deta Types
 ****************************************************************************/

/****************************************************************************
 * Private Deta
 ****************************************************************************/

static mossfw_allocator_t *memalc;
static mossfw_output_t *accel_out;
static mossfw_output_t *gyro_out;

static mossfw_input_t *result1_out;
static mossfw_callback_op_t *op1;

static mossfw_input_t *result2_out;
static mossfw_callback_op_t *op2;

static mossfw_allocator_t *memalc4simple;
static mossfw_input_t *simple_in;
static mossfw_output_t *simple_out;
static mossfw_data_t *simple_dat_exp;
static mossfw_callback_op_t *simple_op;

static bool is_called;
static bool is_called2;

static int result2_idx;

static volatile unsigned long async_thread_num;
static volatile unsigned long async_callback_num;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: test_app_result1_cb
 ****************************************************************************/

static int test_app_result1_cb(mossfw_callback_op_t *op, unsigned long arg)
{
  mossfw_onedata_t result;

  (void) arg;
  mossfw_get_delivereddata_single(op->input,  &result);

  if (is_called == false)
    {
      TEST_ASSERT_EQUAL(11, (int)result.xyzf.x);
      TEST_ASSERT_EQUAL(22, (int)result.xyzf.y);
      TEST_ASSERT_EQUAL(33, (int)result.xyzf.z);
    }

  is_called = true;
  return OK;
}

/****************************************************************************
 * name: test_app_simple_check
 ****************************************************************************/

static int test_app_simple_check(mossfw_callback_op_t *op, unsigned long arg)
{
  int sz;
  int idx;
  mossfw_data_t *dat;

  (void)arg;

  dat = mossfw_get_delivereddata_array(op->input,
                        sizeof(mossfw_data_v3f_t) * MEM_BLKLEN,
                        NULL);
  for (sz = 0, idx = 0;
       sz < dat->data_bytes;
       sz += sizeof(mossfw_data_v3f_t) * 3, idx++)
    {
      TEST_ASSERT_EQUAL(idx, (int)(dat->data.xyzf[idx].x));
      TEST_ASSERT_EQUAL((idx + 1), (int)(dat->data.xyzf[idx].y));
      TEST_ASSERT_EQUAL((idx + 2), (int)(dat->data.xyzf[idx].z));
    }

  mossfw_data_free(dat);

  return OK;
}

/****************************************************************************
 * name: test_app_result2_cb
 ****************************************************************************/

static int test_app_result2_cb(mossfw_callback_op_t *op, unsigned long arg)
{
  int i;
  int i_ary;
  int expected;
  int used;
  mossfw_data_t *dat;

  (void)arg;

  is_called2 = true;

  dat = mossfw_get_delivereddata_array(op->input,
                        sizeof(mossfw_data_v3f_t) * MEM_BLKLEN / 2,
                        &used);

  for (i = 0; dat->data_bytes > used && i < MEM_BLKLEN / 2;
       i++, used += sizeof(mossfw_data_v3f_t), result2_idx++)
    {
      i_ary = used / sizeof(mossfw_data_v3f_t);

      expected = result2_idx + 0 + result2_idx * 20;
      TEST_ASSERT_EQUAL(expected, (int)dat->data.xyzf[i_ary].x);
      expected = result2_idx + 1 + result2_idx * 40;
      TEST_ASSERT_EQUAL(expected, (int)dat->data.xyzf[i_ary].y);
      expected = result2_idx + 2 + result2_idx * 60;
      TEST_ASSERT_EQUAL(expected, (int)dat->data.xyzf[i_ary].z);
    }

  if (dat->data_bytes > used)
    {
      /*
       * To use remaining data on next time,
       * The memory block can be stored to top of the FIFO.
       */

      mossfw_deliverback_dataarray(op->input, dat, used);
    }

  mossfw_data_free(dat);

  return OK;
}

/****************************************************************************
 * name: send_simple_once
 ****************************************************************************/

static void send_simple_once(void)
{
  int idx;
  mossfw_data_t *dat;

  dat = mossfw_data_alloc(memalc4simple,
                             sizeof(mossfw_data_v3f_t) * MEM_BLKLEN, false);
  TEST_ASSERT_NOT_EQUAL(NULL, dat);

  for (dat->data_bytes = 0, idx = 0;
       dat->data_bytes < mossfw_fixedsize_allocator(memalc4simple);
       dat->data_bytes += sizeof(mossfw_data_v3f_t) * 3, idx++)
    {
      dat->data.xyzf[idx].x = (float)idx;
      dat->data.xyzf[idx].y = (float)(idx + 1);
      dat->data.xyzf[idx].z = (float)(idx + 2);
    }

  simple_dat_exp = dat;
  mossfw_deliver_dataarray(simple_out, dat);
  mossfw_data_free(dat);
}

static int async_callback(struct mossfw_callback_op_s *in, unsigned long arg)
{
  int ret = 0;
  int num;
  int used;
  mossfw_data_t *data;
  (void)arg;
  num = mossfw_get_delivereddata_num(in->input);
  data = mossfw_get_delivereddata_array(in->input, num, &used);
  mossfw_data_free(data);
  async_callback_num++;
  return ret;
}

static void *async_thread(void *arg)
{
  const uint32_t type = MOSSFW_DATA_TYPE_SHORT +
                        MOSSFW_DATA_TYPEGRP_V3 +
                        MOSSFW_DATA_TYPENAME_GYRO +
                        MOSSFW_DATA_TYPEARRAY_ARRAY;
  const int block_len = 16;
  const int block_sz = block_len * sizeof(mossfw_data_v3s_t);
  mossfw_allocator_t *allocator;
  mossfw_output_t *out;
  mossfw_input_t *in;
  mossfw_callback_op_t *op;
  mossfw_data_t *data;
  int err;
  unsigned long int i;

  TEST_ASSERT(arg == NULL);
  allocator = mossfw_fixedmem_create(block_sz, 8);
  TEST_ASSERT(allocator);

  out = mossfw_output_create(type);
  TEST_ASSERT(out);
  in = mossfw_input_create(type, 1);
  TEST_ASSERT(in);
  op = mossfw_callback_op_create(async_callback, 0, true);
  TEST_ASSERT(op);
  err = mossfw_set_waitcondition(in, 1, op);
  TEST_ASSERT(!err);
  err = mossfw_bind_inout(out, in, ~0);
  TEST_ASSERT(!err);

  for (i = 0; i < TEST_ASYNC_LOOPNUM; i++)
    {
      data = mossfw_data_alloc(allocator, block_sz, true);
      TEST_ASSERT(data);
      data->data_bytes = block_sz;
      err = mossfw_deliver_dataarray(out, data);
      TEST_ASSERT(!err);
      mossfw_data_free(data);
      async_thread_num++;
    }
  sleep(1);
  mossfw_output_delete(out);
  mossfw_callback_op_delete(op);
  mossfw_input_delete(in);
  return NULL;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: setUp
 ****************************************************************************/

void setUp(void)
{
  mossfw_debug_init();

  memalc = mossfw_fixedmem_create(sizeof(mossfw_data_v3f_t) * MEM_BLKLEN,
                      MEM_BLKNUM);

  accel_out = mossfw_output_create(DUMMY1_ACCELTYPE);
  gyro_out = mossfw_output_create(DUMMY1_GYROTYPE);

  /* For dummy 1 component */

  init_dummy1();

  result1_out = mossfw_input_create(DUMMY1_OUTPUTTYPE, 2);
  op1 = mossfw_callback_op_create(test_app_result1_cb, 0, false);

  mossfw_set_waitcondition(result1_out, sizeof(mossfw_data_v3f_t), op1);

  /* For dummy2 component */

  init_dummy2(memalc);

  result2_out = mossfw_input_create(DUMMY2_OUTPUTTYPE, 2);
  op2 = mossfw_callback_op_create(test_app_result2_cb, 0, false);

  mossfw_set_waitcondition(result2_out, sizeof(mossfw_data_v3f_t) * MEM_BLKLEN / 2, op2);

  /* Bind data path */
  /*
   *                    +--------+
   * Accel out -----+-> |sync    |
   *                |   | dummy1 | -----> result1_out
   * Gyro out  ---+-|-> |sync    |
   *              | |   +--------+
   *              | |
   *              | |   +--------+
   *              | *-> |async   |
   *              |     | dummy2 | -----> result2_out
   *              +---> |async   |
   *                    +--------+
   */

  TEST_ASSERT_EQUAL(OK, mossfw_bind_inout(accel_out, dummy1_get_accelinput(), (uint32_t)-1));
  TEST_ASSERT_EQUAL(OK, mossfw_bind_inout(gyro_out, dummy1_get_gyroinput(), (uint32_t)-1));
  TEST_ASSERT_EQUAL(OK, mossfw_bind_inout(dummy1_get_output(), result1_out, (uint32_t)-1));

  TEST_ASSERT_EQUAL(OK, mossfw_bind_inout(accel_out, dummy2_get_accelinput(), (uint32_t)-1));
  TEST_ASSERT_EQUAL(OK, mossfw_bind_inout(gyro_out, dummy2_get_gyroinput(), (uint32_t)-1));
  TEST_ASSERT_EQUAL(OK, mossfw_bind_inout(dummy2_get_output(), result2_out, (uint32_t)-1));

  /*
   * For Simple test.
   *
   *  simple_out ------> simple_in
   */

  memalc4simple = mossfw_fixedmem_create(sizeof(mossfw_data_v3f_t) * MEM_BLKLEN,
                      MEM_BLKNUM);
  simple_out = mossfw_output_create(MOSSFW_DATA_TYPE_FLOAT |
                               MOSSFW_DATA_TYPEGRP_V3 |
                               MOSSFW_DATA_TYPENAME_GYRO |
                               MOSSFW_DATA_TYPEARRAY_ARRAY);
  simple_in = mossfw_input_create(MOSSFW_DATA_TYPE_FLOAT |
                               MOSSFW_DATA_TYPEGRP_V3 |
                               MOSSFW_DATA_TYPENAME_GYRO |
                               MOSSFW_DATA_TYPEARRAY_ARRAY, 2);

  simple_op = mossfw_callback_op_create(test_app_simple_check, 0, true);
  mossfw_set_waitcondition(simple_in,
                        sizeof(mossfw_data_v3f_t) * MEM_BLKLEN,
                        simple_op);
  TEST_ASSERT_EQUAL(OK, mossfw_bind_inout(simple_out, simple_in, (uint32_t)-1));

  async_thread_num = 0;
  async_callback_num = 0;
}

/****************************************************************************
 * name: tearDown
 ****************************************************************************/

void tearDown(void)
{
  mossfw_callback_op_delete(simple_op);
  mossfw_input_delete(simple_in);
  mossfw_output_delete(simple_out);

  mossfw_callback_op_delete(op1);
  mossfw_input_delete(result1_out);
  mossfw_output_delete(accel_out);
  mossfw_output_delete(gyro_out);
  mossfw_callback_op_delete(op2);
  mossfw_input_delete(result2_out);

  final_dummy1();
  final_dummy2();
  mossfw_fixedmem_delete(memalc4simple);
}

/****************************************************************************
 * name: test_Simple
 ****************************************************************************/

void test_Simple(void)
{
  send_simple_once();
  send_simple_once();
  send_simple_once();
  send_simple_once();
  sleep(1);
}

/****************************************************************************
 * name: test_ExecuteOnePath
 ****************************************************************************/

void test_ExecuteOnePath(void)
{
  mossfw_onedata_t accel;
  mossfw_onedata_t gyro;

  result2_idx = 0;

  /* Dummy accel data */

  accel.xyzs.x = 1;
  accel.xyzs.y = 2;
  accel.xyzs.z = 3;

  /* Dummy Gyro data */

  gyro.xyzs.x = 10;
  gyro.xyzs.y = 20;
  gyro.xyzs.z = 30;

  is_called = false;

  /* Accelemater driver delivers one sample */

  mossfw_deliver_data(accel_out, &accel);

  /*
   * Now accel data is delivered but gyro data is not.
   * So result is not deliverd.
   */

  TEST_ASSERT_EQUAL(false, is_called);

  /* Gyro driver delivers one sample */

  mossfw_deliver_data(gyro_out, &gyro);

  /* Accel and Gyro data are deliverd. So result should also deliverd. */

  TEST_ASSERT_EQUAL(true, is_called);
  sleep(1);
}

/****************************************************************************
 * name: test_ForDummy2AsAsynchronusInput
 ****************************************************************************/

void test_ForDummy2AsAsynchronusInput(void)
{
  int i;
  mossfw_onedata_t accel;
  mossfw_onedata_t gyro;

  avoid_id = pthread_self();
  mossfw_debug_init();

  result2_idx = 0;
  is_called = true;
  is_called2 = false;
  for (i = 0; i < MEM_BLKLEN * 10; i++)
    {
      accel.xyzs.x = i;
      accel.xyzs.y = i + 1;
      accel.xyzs.z = i + 2;

      gyro.xyzs.x = i * 10;
      gyro.xyzs.y = i * 20;
      gyro.xyzs.z = i * 30;
      mossfw_deliver_data(accel_out, &accel);
      mossfw_deliver_data(gyro_out, &gyro);
    }

  sleep(1);
  TEST_ASSERT_EQUAL(true, is_called2);
}

void test_async(void)
{
  pthread_t thread;
  int err;
  unsigned long atn;
  unsigned long acn;
  int deadlock = 0;

  /* test runs in thead to detect deadlock */
  err = pthread_create(&thread, NULL, async_thread, NULL);
  TEST_ASSERT(!err);
  while (!deadlock && async_thread_num < TEST_ASYNC_LOOPNUM && async_callback_num < TEST_ASYNC_LOOPNUM)
    {
      atn = async_thread_num;
      acn = async_callback_num;
      sleep(1);
      deadlock = (atn == async_thread_num && acn == async_callback_num);
      printf("Progress: %ld/%ld\n", async_thread_num, TEST_ASYNC_LOOPNUM);
    }

  if (atn == TEST_ASYNC_LOOPNUM && acn == TEST_ASYNC_LOOPNUM)
    {
      err = pthread_join(thread, NULL);
      TEST_ASSERT(!err);
    }
  else
    {
      (void)pthread_cancel(thread);
    }
  TEST_ASSERT_EQUAL(TEST_ASYNC_LOOPNUM, async_thread_num);
  TEST_ASSERT_EQUAL(TEST_ASYNC_LOOPNUM, async_callback_num);
}

void test_stopasyncdeadlock(void)
{
    int num = 100000;
    int i;
    for (i = 0; i < num; i++) {
        mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 1);
        TEST_ASSERT(op != NULL);
        mossfw_callback_op_delete(op);
    }
}

void test_mossfw_input_create_001(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_MASK;
uint32_t type2 =
    MOSSFW_DATA_TYPE_MASK |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mallocerr = -1;
(void) type0;
(void) type1;
(void) type2;



mossfw_input_t *input =
    mossfw_input_create(type0, 
    1);



TEST_ASSERT(input != NULL);
mossfw_input_delete(input);
mallocerr = -1;


}

void test_mossfw_input_create_002(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_MASK;
uint32_t type2 =
    MOSSFW_DATA_TYPE_MASK |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mallocerr = -1;
(void) type0;
(void) type1;
(void) type2;



mossfw_input_t *input =
    mossfw_input_create(type2, 
    1);



TEST_ASSERT(input == NULL);
mossfw_input_delete(input);
mallocerr = -1;


}

void test_mossfw_input_create_003(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_MASK;
uint32_t type2 =
    MOSSFW_DATA_TYPE_MASK |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mallocerr = -1;
(void) type0;
(void) type1;
(void) type2;



mossfw_input_t *input =
    mossfw_input_create(type1, 
    1);



TEST_ASSERT(input == NULL);
mossfw_input_delete(input);
mallocerr = -1;


}

void test_mossfw_input_create_004(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_MASK;
uint32_t type2 =
    MOSSFW_DATA_TYPE_MASK |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mallocerr = -1;
(void) type0;
(void) type1;
(void) type2;



mossfw_input_t *input =
    mossfw_input_create(type0, 
    0);



TEST_ASSERT(input == NULL);
mossfw_input_delete(input);
mallocerr = -1;


}

void test_mossfw_input_create_005(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_MASK;
uint32_t type2 =
    MOSSFW_DATA_TYPE_MASK |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mallocerr = 0;
(void) type0;
(void) type1;
(void) type2;



mossfw_input_t *input =
    mossfw_input_create(type0, 
    1);



TEST_ASSERT(input == NULL);
mossfw_input_delete(input);
mallocerr = -1;


}

void test_mossfw_input_create_006(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_MASK;
uint32_t type2 =
    MOSSFW_DATA_TYPE_MASK |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mallocerr = 0;
(void) type0;
(void) type1;
(void) type2;



mossfw_input_t *input =
    mossfw_input_create(type2, 
    1);



TEST_ASSERT(input == NULL);
mossfw_input_delete(input);
mallocerr = -1;


}

void test_mossfw_input_create_007(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_MASK;
uint32_t type2 =
    MOSSFW_DATA_TYPE_MASK |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mallocerr = 0;
(void) type0;
(void) type1;
(void) type2;



mossfw_input_t *input =
    mossfw_input_create(type1, 
    0);



TEST_ASSERT(input == NULL);
mossfw_input_delete(input);
mallocerr = -1;


}

void test_mossfw_input_create_008(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_MASK;
uint32_t type2 =
    MOSSFW_DATA_TYPE_MASK |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mallocerr = -1;
(void) type0;
(void) type1;
(void) type2;



mossfw_input_t *input =
    mossfw_input_create(type2, 
    0);



TEST_ASSERT(input == NULL);
mossfw_input_delete(input);
mallocerr = -1;


}

void test_mossfw_input_delete_001(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int inputparam = 1;
int datatype = 1;
mossfw_input_t *input = NULL;
mossfw_allocator_t *allocator = NULL;
int size = sizeof(mossfw_data_v2i32_t);
mossfw_data_t *data = NULL;
mossfw_output_t *output = NULL;
mossfw_callback_op_t *op = NULL;
if (inputparam) {
    if (datatype == 0) {
        input = mossfw_input_create(single, 1);
    } else if (datatype == 1) {
        input = mossfw_input_create(array, 1);
    } else if (datatype == 2) {
        input = mossfw_input_create(array, 1);
        TEST_ASSERT(input != NULL);
        output = mossfw_output_create(array);
        TEST_ASSERT(output != NULL);
        op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
        TEST_ASSERT(op != NULL);
        int waiterr = mossfw_set_waitcondition(input, 2 * size, op);
        TEST_ASSERT(waiterr == OK);
        int err = mossfw_bind_inout(output, input, ~0);
        TEST_ASSERT(err == OK);
        allocator = mossfw_fixedmem_create(size, 1);
        TEST_ASSERT(allocator != NULL);
        mossfw_data_t *data = mossfw_data_alloc(allocator, size, 1);
        TEST_ASSERT(data != NULL);
        err = mossfw_deliver_dataarray(output, data);
        TEST_ASSERT(err == OK);
        mossfw_data_free(data);
    } else if (datatype == -1) {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->ringbuff.single = NULL;
    } else {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->type = input->type | MOSSFW_DATA_TYPEARRAY_MASK;
    }
}
(void) single;
(void) array;
(void) data;



mossfw_input_delete(input);



mossfw_output_delete(output);
mossfw_callback_op_delete(op);
if (allocator) {
    int err = mossfw_fixedmem_delete(allocator);
    TEST_ASSERT(err == 0);
}


}

void test_mossfw_input_delete_002(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int inputparam = 1;
int datatype = 0;
mossfw_input_t *input = NULL;
mossfw_allocator_t *allocator = NULL;
int size = sizeof(mossfw_data_v2i32_t);
mossfw_data_t *data = NULL;
mossfw_output_t *output = NULL;
mossfw_callback_op_t *op = NULL;
if (inputparam) {
    if (datatype == 0) {
        input = mossfw_input_create(single, 1);
    } else if (datatype == 1) {
        input = mossfw_input_create(array, 1);
    } else if (datatype == 2) {
        input = mossfw_input_create(array, 1);
        TEST_ASSERT(input != NULL);
        output = mossfw_output_create(array);
        TEST_ASSERT(output != NULL);
        op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
        TEST_ASSERT(op != NULL);
        int waiterr = mossfw_set_waitcondition(input, 2 * size, op);
        TEST_ASSERT(waiterr == OK);
        int err = mossfw_bind_inout(output, input, ~0);
        TEST_ASSERT(err == OK);
        allocator = mossfw_fixedmem_create(size, 1);
        TEST_ASSERT(allocator != NULL);
        mossfw_data_t *data = mossfw_data_alloc(allocator, size, 1);
        TEST_ASSERT(data != NULL);
        err = mossfw_deliver_dataarray(output, data);
        TEST_ASSERT(err == OK);
        mossfw_data_free(data);
    } else if (datatype == -1) {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->ringbuff.single = NULL;
    } else {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->type = input->type | MOSSFW_DATA_TYPEARRAY_MASK;
    }
}
(void) single;
(void) array;
(void) data;



mossfw_input_delete(input);



mossfw_output_delete(output);
mossfw_callback_op_delete(op);
if (allocator) {
    int err = mossfw_fixedmem_delete(allocator);
    TEST_ASSERT(err == 0);
}


}

void test_mossfw_input_delete_003(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int inputparam = 1;
int datatype = 2;
mossfw_input_t *input = NULL;
mossfw_allocator_t *allocator = NULL;
int size = sizeof(mossfw_data_v2i32_t);
mossfw_data_t *data = NULL;
mossfw_output_t *output = NULL;
mossfw_callback_op_t *op = NULL;
if (inputparam) {
    if (datatype == 0) {
        input = mossfw_input_create(single, 1);
    } else if (datatype == 1) {
        input = mossfw_input_create(array, 1);
    } else if (datatype == 2) {
        input = mossfw_input_create(array, 1);
        TEST_ASSERT(input != NULL);
        output = mossfw_output_create(array);
        TEST_ASSERT(output != NULL);
        op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
        TEST_ASSERT(op != NULL);
        int waiterr = mossfw_set_waitcondition(input, 2 * size, op);
        TEST_ASSERT(waiterr == OK);
        int err = mossfw_bind_inout(output, input, ~0);
        TEST_ASSERT(err == OK);
        allocator = mossfw_fixedmem_create(size, 1);
        TEST_ASSERT(allocator != NULL);
        mossfw_data_t *data = mossfw_data_alloc(allocator, size, 1);
        TEST_ASSERT(data != NULL);
        err = mossfw_deliver_dataarray(output, data);
        TEST_ASSERT(err == OK);
        mossfw_data_free(data);
    } else if (datatype == -1) {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->ringbuff.single = NULL;
    } else {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->type = input->type | MOSSFW_DATA_TYPEARRAY_MASK;
    }
}
(void) single;
(void) array;
(void) data;



mossfw_input_delete(input);



mossfw_output_delete(output);
mossfw_callback_op_delete(op);
if (allocator) {
    int err = mossfw_fixedmem_delete(allocator);
    TEST_ASSERT(err == 0);
}


}

void test_mossfw_input_delete_004(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int inputparam = 0;
int datatype = 1;
mossfw_input_t *input = NULL;
mossfw_allocator_t *allocator = NULL;
int size = sizeof(mossfw_data_v2i32_t);
mossfw_data_t *data = NULL;
mossfw_output_t *output = NULL;
mossfw_callback_op_t *op = NULL;
if (inputparam) {
    if (datatype == 0) {
        input = mossfw_input_create(single, 1);
    } else if (datatype == 1) {
        input = mossfw_input_create(array, 1);
    } else if (datatype == 2) {
        input = mossfw_input_create(array, 1);
        TEST_ASSERT(input != NULL);
        output = mossfw_output_create(array);
        TEST_ASSERT(output != NULL);
        op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
        TEST_ASSERT(op != NULL);
        int waiterr = mossfw_set_waitcondition(input, 2 * size, op);
        TEST_ASSERT(waiterr == OK);
        int err = mossfw_bind_inout(output, input, ~0);
        TEST_ASSERT(err == OK);
        allocator = mossfw_fixedmem_create(size, 1);
        TEST_ASSERT(allocator != NULL);
        mossfw_data_t *data = mossfw_data_alloc(allocator, size, 1);
        TEST_ASSERT(data != NULL);
        err = mossfw_deliver_dataarray(output, data);
        TEST_ASSERT(err == OK);
        mossfw_data_free(data);
    } else if (datatype == -1) {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->ringbuff.single = NULL;
    } else {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->type = input->type | MOSSFW_DATA_TYPEARRAY_MASK;
    }
}
(void) single;
(void) array;
(void) data;



mossfw_input_delete(input);



mossfw_output_delete(output);
mossfw_callback_op_delete(op);
if (allocator) {
    int err = mossfw_fixedmem_delete(allocator);
    TEST_ASSERT(err == 0);
}


}

void test_mossfw_input_delete_005(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int inputparam = 0;
int datatype = 0;
mossfw_input_t *input = NULL;
mossfw_allocator_t *allocator = NULL;
int size = sizeof(mossfw_data_v2i32_t);
mossfw_data_t *data = NULL;
mossfw_output_t *output = NULL;
mossfw_callback_op_t *op = NULL;
if (inputparam) {
    if (datatype == 0) {
        input = mossfw_input_create(single, 1);
    } else if (datatype == 1) {
        input = mossfw_input_create(array, 1);
    } else if (datatype == 2) {
        input = mossfw_input_create(array, 1);
        TEST_ASSERT(input != NULL);
        output = mossfw_output_create(array);
        TEST_ASSERT(output != NULL);
        op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
        TEST_ASSERT(op != NULL);
        int waiterr = mossfw_set_waitcondition(input, 2 * size, op);
        TEST_ASSERT(waiterr == OK);
        int err = mossfw_bind_inout(output, input, ~0);
        TEST_ASSERT(err == OK);
        allocator = mossfw_fixedmem_create(size, 1);
        TEST_ASSERT(allocator != NULL);
        mossfw_data_t *data = mossfw_data_alloc(allocator, size, 1);
        TEST_ASSERT(data != NULL);
        err = mossfw_deliver_dataarray(output, data);
        TEST_ASSERT(err == OK);
        mossfw_data_free(data);
    } else if (datatype == -1) {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->ringbuff.single = NULL;
    } else {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->type = input->type | MOSSFW_DATA_TYPEARRAY_MASK;
    }
}
(void) single;
(void) array;
(void) data;



mossfw_input_delete(input);



mossfw_output_delete(output);
mossfw_callback_op_delete(op);
if (allocator) {
    int err = mossfw_fixedmem_delete(allocator);
    TEST_ASSERT(err == 0);
}


}

void test_mossfw_input_delete_006(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int inputparam = 0;
int datatype = 2;
mossfw_input_t *input = NULL;
mossfw_allocator_t *allocator = NULL;
int size = sizeof(mossfw_data_v2i32_t);
mossfw_data_t *data = NULL;
mossfw_output_t *output = NULL;
mossfw_callback_op_t *op = NULL;
if (inputparam) {
    if (datatype == 0) {
        input = mossfw_input_create(single, 1);
    } else if (datatype == 1) {
        input = mossfw_input_create(array, 1);
    } else if (datatype == 2) {
        input = mossfw_input_create(array, 1);
        TEST_ASSERT(input != NULL);
        output = mossfw_output_create(array);
        TEST_ASSERT(output != NULL);
        op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
        TEST_ASSERT(op != NULL);
        int waiterr = mossfw_set_waitcondition(input, 2 * size, op);
        TEST_ASSERT(waiterr == OK);
        int err = mossfw_bind_inout(output, input, ~0);
        TEST_ASSERT(err == OK);
        allocator = mossfw_fixedmem_create(size, 1);
        TEST_ASSERT(allocator != NULL);
        mossfw_data_t *data = mossfw_data_alloc(allocator, size, 1);
        TEST_ASSERT(data != NULL);
        err = mossfw_deliver_dataarray(output, data);
        TEST_ASSERT(err == OK);
        mossfw_data_free(data);
    } else if (datatype == -1) {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->ringbuff.single = NULL;
    } else {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->type = input->type | MOSSFW_DATA_TYPEARRAY_MASK;
    }
}
(void) single;
(void) array;
(void) data;



mossfw_input_delete(input);



mossfw_output_delete(output);
mossfw_callback_op_delete(op);
if (allocator) {
    int err = mossfw_fixedmem_delete(allocator);
    TEST_ASSERT(err == 0);
}


}

void test_mossfw_input_delete_007(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int inputparam = 1;
int datatype = -2;
mossfw_input_t *input = NULL;
mossfw_allocator_t *allocator = NULL;
int size = sizeof(mossfw_data_v2i32_t);
mossfw_data_t *data = NULL;
mossfw_output_t *output = NULL;
mossfw_callback_op_t *op = NULL;
if (inputparam) {
    if (datatype == 0) {
        input = mossfw_input_create(single, 1);
    } else if (datatype == 1) {
        input = mossfw_input_create(array, 1);
    } else if (datatype == 2) {
        input = mossfw_input_create(array, 1);
        TEST_ASSERT(input != NULL);
        output = mossfw_output_create(array);
        TEST_ASSERT(output != NULL);
        op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
        TEST_ASSERT(op != NULL);
        int waiterr = mossfw_set_waitcondition(input, 2 * size, op);
        TEST_ASSERT(waiterr == OK);
        int err = mossfw_bind_inout(output, input, ~0);
        TEST_ASSERT(err == OK);
        allocator = mossfw_fixedmem_create(size, 1);
        TEST_ASSERT(allocator != NULL);
        mossfw_data_t *data = mossfw_data_alloc(allocator, size, 1);
        TEST_ASSERT(data != NULL);
        err = mossfw_deliver_dataarray(output, data);
        TEST_ASSERT(err == OK);
        mossfw_data_free(data);
    } else if (datatype == -1) {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->ringbuff.single = NULL;
    } else {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->type = input->type | MOSSFW_DATA_TYPEARRAY_MASK;
    }
}
(void) single;
(void) array;
(void) data;



mossfw_input_delete(input);



mossfw_output_delete(output);
mossfw_callback_op_delete(op);
if (allocator) {
    int err = mossfw_fixedmem_delete(allocator);
    TEST_ASSERT(err == 0);
}


}

void test_mossfw_input_delete_008(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int inputparam = 1;
int datatype = -1;
mossfw_input_t *input = NULL;
mossfw_allocator_t *allocator = NULL;
int size = sizeof(mossfw_data_v2i32_t);
mossfw_data_t *data = NULL;
mossfw_output_t *output = NULL;
mossfw_callback_op_t *op = NULL;
if (inputparam) {
    if (datatype == 0) {
        input = mossfw_input_create(single, 1);
    } else if (datatype == 1) {
        input = mossfw_input_create(array, 1);
    } else if (datatype == 2) {
        input = mossfw_input_create(array, 1);
        TEST_ASSERT(input != NULL);
        output = mossfw_output_create(array);
        TEST_ASSERT(output != NULL);
        op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
        TEST_ASSERT(op != NULL);
        int waiterr = mossfw_set_waitcondition(input, 2 * size, op);
        TEST_ASSERT(waiterr == OK);
        int err = mossfw_bind_inout(output, input, ~0);
        TEST_ASSERT(err == OK);
        allocator = mossfw_fixedmem_create(size, 1);
        TEST_ASSERT(allocator != NULL);
        mossfw_data_t *data = mossfw_data_alloc(allocator, size, 1);
        TEST_ASSERT(data != NULL);
        err = mossfw_deliver_dataarray(output, data);
        TEST_ASSERT(err == OK);
        mossfw_data_free(data);
    } else if (datatype == -1) {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->ringbuff.single = NULL;
    } else {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->type = input->type | MOSSFW_DATA_TYPEARRAY_MASK;
    }
}
(void) single;
(void) array;
(void) data;



mossfw_input_delete(input);



mossfw_output_delete(output);
mossfw_callback_op_delete(op);
if (allocator) {
    int err = mossfw_fixedmem_delete(allocator);
    TEST_ASSERT(err == 0);
}


}

void test_mossfw_input_delete_009(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int inputparam = 0;
int datatype = -2;
mossfw_input_t *input = NULL;
mossfw_allocator_t *allocator = NULL;
int size = sizeof(mossfw_data_v2i32_t);
mossfw_data_t *data = NULL;
mossfw_output_t *output = NULL;
mossfw_callback_op_t *op = NULL;
if (inputparam) {
    if (datatype == 0) {
        input = mossfw_input_create(single, 1);
    } else if (datatype == 1) {
        input = mossfw_input_create(array, 1);
    } else if (datatype == 2) {
        input = mossfw_input_create(array, 1);
        TEST_ASSERT(input != NULL);
        output = mossfw_output_create(array);
        TEST_ASSERT(output != NULL);
        op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
        TEST_ASSERT(op != NULL);
        int waiterr = mossfw_set_waitcondition(input, 2 * size, op);
        TEST_ASSERT(waiterr == OK);
        int err = mossfw_bind_inout(output, input, ~0);
        TEST_ASSERT(err == OK);
        allocator = mossfw_fixedmem_create(size, 1);
        TEST_ASSERT(allocator != NULL);
        mossfw_data_t *data = mossfw_data_alloc(allocator, size, 1);
        TEST_ASSERT(data != NULL);
        err = mossfw_deliver_dataarray(output, data);
        TEST_ASSERT(err == OK);
        mossfw_data_free(data);
    } else if (datatype == -1) {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->ringbuff.single = NULL;
    } else {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->type = input->type | MOSSFW_DATA_TYPEARRAY_MASK;
    }
}
(void) single;
(void) array;
(void) data;



mossfw_input_delete(input);



mossfw_output_delete(output);
mossfw_callback_op_delete(op);
if (allocator) {
    int err = mossfw_fixedmem_delete(allocator);
    TEST_ASSERT(err == 0);
}


}

void test_mossfw_input_delete_010(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int inputparam = 0;
int datatype = -1;
mossfw_input_t *input = NULL;
mossfw_allocator_t *allocator = NULL;
int size = sizeof(mossfw_data_v2i32_t);
mossfw_data_t *data = NULL;
mossfw_output_t *output = NULL;
mossfw_callback_op_t *op = NULL;
if (inputparam) {
    if (datatype == 0) {
        input = mossfw_input_create(single, 1);
    } else if (datatype == 1) {
        input = mossfw_input_create(array, 1);
    } else if (datatype == 2) {
        input = mossfw_input_create(array, 1);
        TEST_ASSERT(input != NULL);
        output = mossfw_output_create(array);
        TEST_ASSERT(output != NULL);
        op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
        TEST_ASSERT(op != NULL);
        int waiterr = mossfw_set_waitcondition(input, 2 * size, op);
        TEST_ASSERT(waiterr == OK);
        int err = mossfw_bind_inout(output, input, ~0);
        TEST_ASSERT(err == OK);
        allocator = mossfw_fixedmem_create(size, 1);
        TEST_ASSERT(allocator != NULL);
        mossfw_data_t *data = mossfw_data_alloc(allocator, size, 1);
        TEST_ASSERT(data != NULL);
        err = mossfw_deliver_dataarray(output, data);
        TEST_ASSERT(err == OK);
        mossfw_data_free(data);
    } else if (datatype == -1) {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->ringbuff.single = NULL;
    } else {
        input = mossfw_input_create(single, 1);
        TEST_ASSERT(input != NULL);
        mossfw_ringbuff_delete(input->ringbuff.single);
        input->type = input->type | MOSSFW_DATA_TYPEARRAY_MASK;
    }
}
(void) single;
(void) array;
(void) data;



mossfw_input_delete(input);



mossfw_output_delete(output);
mossfw_callback_op_delete(op);
if (allocator) {
    int err = mossfw_fixedmem_delete(allocator);
    TEST_ASSERT(err == 0);
}


}

void test_mossfw_output_create_001(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mallocerr = -1;



mossfw_output_t *output =
    mossfw_output_create(type);



TEST_ASSERT(output != NULL);
mossfw_output_delete(output);
mallocerr = -1;


}

void test_mossfw_output_create_002(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mallocerr = 0;



mossfw_output_t *output =
    mossfw_output_create(type);



TEST_ASSERT(output == NULL);
mossfw_output_delete(output);
mallocerr = -1;


}

void test_mossfw_bind_inout_001(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 3;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = 0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == OK);
TEST_ASSERT(err1 == OK);
TEST_ASSERT(err2 == OK);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_002(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 3;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = ~0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == OK);
TEST_ASSERT(err1 == OK);
TEST_ASSERT(err2 == OK);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_003(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 1;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = 0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == OK);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_004(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 1;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = ~0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == OK);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_005(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 3;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = 0u;
mossfw_output_t *output = NULL;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EINVAL);
TEST_ASSERT(err1 == OK);
TEST_ASSERT(err2 == OK);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_006(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 3;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = ~0u;
mossfw_output_t *output = NULL;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EINVAL);
TEST_ASSERT(err1 == OK);
TEST_ASSERT(err2 == OK);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_007(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 1;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = 0u;
mossfw_output_t *output = NULL;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EINVAL);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_008(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 1;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = ~0u;
mossfw_output_t *output = NULL;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EINVAL);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_009(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = -1;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = 0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EALREADY);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_010(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = -1;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = ~0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EALREADY);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_011(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 0;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = 0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EINVAL);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_012(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 0;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = ~0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EINVAL);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_013(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 3;
mossfw_output_t *out = mossfw_output_create(type1);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = 0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == OK);
TEST_ASSERT(err1 == -EIO);
TEST_ASSERT(err2 == -EIO);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_014(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 3;
mossfw_output_t *out = mossfw_output_create(type1);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = ~0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EIO);
TEST_ASSERT(err1 == -EIO);
TEST_ASSERT(err2 == -EIO);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_015(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 1;
mossfw_output_t *out = mossfw_output_create(type1);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = 0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == OK);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_016(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 1;
mossfw_output_t *out = mossfw_output_create(type1);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = ~0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EIO);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_017(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = -1;
mossfw_output_t *out = mossfw_output_create(type1);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = 0u;
mossfw_output_t *output = NULL;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EINVAL);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_018(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 0;
mossfw_output_t *out = mossfw_output_create(type0);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = ~0u;
mossfw_output_t *output = NULL;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EINVAL);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_bind_inout_019(void)
{

uint32_t type0 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t type1 =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_GYRO | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type0, 1);
mossfw_input_t *in1 = mossfw_input_create(type0, 1);
mossfw_input_t *in2 = mossfw_input_create(type0, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
int innum = 0;
mossfw_output_t *out = mossfw_output_create(type1);
TEST_ASSERT(out != NULL);
(void)type1;
mossfw_input_t *inparam0 = ((innum == 0) ? NULL : in0);
int err1 = -1;
int err2 = -1;
uint32_t mask = 0u;
mossfw_output_t *output = out;



int err = 
    mossfw_bind_inout(output, inparam0, mask);
if (innum == -1 && err == OK) {
    err = mossfw_bind_inout(output, inparam0, mask);
}
if (1 < innum) {
    err1 = mossfw_bind_inout(out, in1, ~0u);
}
if (2 < innum) {
    err2 = mossfw_bind_inout(out, in2, ~0u);
}



TEST_ASSERT(err == -EINVAL);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);


}

void test_mossfw_unbind_inout_001(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V8 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
mossfw_input_t *in2 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
int err0 = mossfw_bind_inout(out, in0, ~0u);
int err1 = mossfw_bind_inout(out, in1, ~0u);
TEST_ASSERT(err0 == OK);
TEST_ASSERT(err1 == OK);







int err =
mossfw_unbind_inout(out,
                    in0);









TEST_ASSERT(err == 0);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);




}

void test_mossfw_unbind_inout_002(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V8 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
mossfw_input_t *in2 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
int err0 = mossfw_bind_inout(out, in0, ~0u);
int err1 = mossfw_bind_inout(out, in1, ~0u);
TEST_ASSERT(err0 == OK);
TEST_ASSERT(err1 == OK);







int err =
mossfw_unbind_inout(out,
                    in1);









TEST_ASSERT(err == 0);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);




}

void test_mossfw_unbind_inout_003(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V8 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
mossfw_input_t *in2 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
int err0 = mossfw_bind_inout(out, in0, ~0u);
int err1 = mossfw_bind_inout(out, in1, ~0u);
TEST_ASSERT(err0 == OK);
TEST_ASSERT(err1 == OK);







int err =
mossfw_unbind_inout(NULL,
                    in0);









TEST_ASSERT(err == -EINVAL);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);




}

void test_mossfw_unbind_inout_004(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V8 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
mossfw_input_t *in2 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
int err0 = mossfw_bind_inout(out, in0, ~0u);
int err1 = mossfw_bind_inout(out, in1, ~0u);
TEST_ASSERT(err0 == OK);
TEST_ASSERT(err1 == OK);







int err =
mossfw_unbind_inout(NULL,
                    in1);









TEST_ASSERT(err == -EINVAL);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);




}

void test_mossfw_unbind_inout_005(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V8 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
mossfw_input_t *in2 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
int err0 = mossfw_bind_inout(out, in0, ~0u);
int err1 = mossfw_bind_inout(out, in1, ~0u);
TEST_ASSERT(err0 == OK);
TEST_ASSERT(err1 == OK);







int err =
mossfw_unbind_inout(out,
                    NULL);









TEST_ASSERT(err == -EINVAL);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);




}

void test_mossfw_unbind_inout_006(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V8 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
mossfw_input_t *in2 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
int err0 = mossfw_bind_inout(out, in0, ~0u);
int err1 = mossfw_bind_inout(out, in1, ~0u);
TEST_ASSERT(err0 == OK);
TEST_ASSERT(err1 == OK);







int err =
mossfw_unbind_inout(out,
                    in2);









TEST_ASSERT(err == -EINVAL);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);




}

void test_mossfw_unbind_inout_007(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V8 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
mossfw_input_t *in2 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
int err0 = mossfw_bind_inout(out, in0, ~0u);
int err1 = mossfw_bind_inout(out, in1, ~0u);
TEST_ASSERT(err0 == OK);
TEST_ASSERT(err1 == OK);







int err =
mossfw_unbind_inout(NULL,
                    in2);









TEST_ASSERT(err == -EINVAL);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);




}

void test_mossfw_unbind_inout_008(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V8 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
mossfw_input_t *in2 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
TEST_ASSERT(in1 != NULL);
TEST_ASSERT(in2 != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
int err0 = mossfw_bind_inout(out, in0, ~0u);
int err1 = mossfw_bind_inout(out, in1, ~0u);
TEST_ASSERT(err0 == OK);
TEST_ASSERT(err1 == OK);







int err =
mossfw_unbind_inout(NULL,
                    NULL);









TEST_ASSERT(err == -EINVAL);
mossfw_output_delete(out);
mossfw_input_delete(in2);
mossfw_input_delete(in1);
mossfw_input_delete(in0);




}

void test_mossfw_callback_op_create_001(void)
{

mallocerr = -1;
pthread_createerr = 0;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb,
                              0,
                              0);



TEST_ASSERT(op != NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_002(void)
{

mallocerr = -1;
pthread_createerr = 0;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb,
                              0,
                              1);



TEST_ASSERT(op != NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_003(void)
{

mallocerr = -1;
pthread_createerr = 0;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(NULL,
                              0,
                              0);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_004(void)
{

mallocerr = -1;
pthread_createerr = 0;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(NULL,
                              0,
                              1);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_005(void)
{

mallocerr = 0;
pthread_createerr = 0;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb,
                              0,
                              0);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_006(void)
{

mallocerr = 1;
pthread_createerr = 0;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb,
                              0,
                              0);



TEST_ASSERT(op != NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_007(void)
{

mallocerr = 0;
pthread_createerr = 0;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb,
                              0,
                              1);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_008(void)
{

mallocerr = 1;
pthread_createerr = 0;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb,
                              0,
                              1);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_009(void)
{

mallocerr = -1;
pthread_createerr = 1;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb,
                              0,
                              0);



TEST_ASSERT(op != NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_010(void)
{

mallocerr = -1;
pthread_createerr = 1;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb,
                              0,
                              1);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_011(void)
{

mallocerr = 0;
pthread_createerr = 1;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(NULL,
                              0,
                              1);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_012(void)
{

mallocerr = 1;
pthread_createerr = 1;



mossfw_callback_op_t *op = 
    mossfw_callback_op_create(NULL,
                              0,
                              0);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
mallocerr = -1;
pthread_createerr = 0;


}

void test_mossfw_callback_op_create_attr_001(void)
{

pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
struct sched_param sched;
int errsched = pthread_attr_getschedparam(&attr, &sched);
TEST_ASSERT(errsched == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
if (sched.sched_priority == 0) {
    sched.sched_priority = 1;
}



mossfw_callback_op_t *op = 
    mossfw_callback_op_create_attr(test_app_result1_cb,
                                  0,
                                  0,
                                  sched.sched_priority,
                                  -1);



TEST_ASSERT(op != NULL);
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);


}

void test_mossfw_callback_op_create_attr_002(void)
{

pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
struct sched_param sched;
int errsched = pthread_attr_getschedparam(&attr, &sched);
TEST_ASSERT(errsched == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
if (sched.sched_priority == 0) {
    sched.sched_priority = 1;
}



mossfw_callback_op_t *op = 
    mossfw_callback_op_create_attr(test_app_result1_cb,
                                  0,
                                  1,
                                  sched.sched_priority,
                                  stacksize);



TEST_ASSERT(op != NULL);
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);


}

void test_mossfw_callback_op_create_attr_003(void)
{

pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
struct sched_param sched;
int errsched = pthread_attr_getschedparam(&attr, &sched);
TEST_ASSERT(errsched == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
if (sched.sched_priority == 0) {
    sched.sched_priority = 1;
}



mossfw_callback_op_t *op = 
    mossfw_callback_op_create_attr(test_app_result1_cb,
                                  0,
                                  1,
                                  -1,
                                  -1);



TEST_ASSERT(op != NULL);
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);


}

void test_mossfw_callback_op_create_attr_004(void)
{

pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
struct sched_param sched;
int errsched = pthread_attr_getschedparam(&attr, &sched);
TEST_ASSERT(errsched == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
if (sched.sched_priority == 0) {
    sched.sched_priority = 1;
}



mossfw_callback_op_t *op = 
    mossfw_callback_op_create_attr(test_app_result1_cb,
                                  0,
                                  0,
                                  -1,
                                  stacksize);



TEST_ASSERT(op != NULL);
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);


}

void test_mossfw_callback_op_create_attr_005(void)
{

pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
struct sched_param sched;
int errsched = pthread_attr_getschedparam(&attr, &sched);
TEST_ASSERT(errsched == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
if (sched.sched_priority == 0) {
    sched.sched_priority = 1;
}



mossfw_callback_op_t *op = 
    mossfw_callback_op_create_attr(NULL,
                                  0,
                                  0,
                                  sched.sched_priority,
                                  -1);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);


}

void test_mossfw_callback_op_create_attr_006(void)
{

pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
struct sched_param sched;
int errsched = pthread_attr_getschedparam(&attr, &sched);
TEST_ASSERT(errsched == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
if (sched.sched_priority == 0) {
    sched.sched_priority = 1;
}



mossfw_callback_op_t *op = 
    mossfw_callback_op_create_attr(NULL,
                                  0,
                                  1,
                                  sched.sched_priority,
                                  stacksize);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);


}

void test_mossfw_callback_op_create_attr_007(void)
{

pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
struct sched_param sched;
int errsched = pthread_attr_getschedparam(&attr, &sched);
TEST_ASSERT(errsched == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
if (sched.sched_priority == 0) {
    sched.sched_priority = 1;
}



mossfw_callback_op_t *op = 
    mossfw_callback_op_create_attr(NULL,
                                  0,
                                  1,
                                  -1,
                                  -1);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);


}

void test_mossfw_callback_op_create_attr_008(void)
{

pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
struct sched_param sched;
int errsched = pthread_attr_getschedparam(&attr, &sched);
TEST_ASSERT(errsched == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
if (sched.sched_priority == 0) {
    sched.sched_priority = 1;
}



mossfw_callback_op_t *op = 
    mossfw_callback_op_create_attr(NULL,
                                  0,
                                  0,
                                  -1,
                                  stacksize);



TEST_ASSERT(op == NULL);
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);


}

void test_mossfw_set_waitcondition_001(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
mossfw_input_t *in2 =
    mossfw_input_create(type, 1);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
int size = sizeof(mossfw_data_v1s_t);
(void)size;
int innum = 2;
int paramsize = size;
mossfw_callback_op_t *paramop = op;
mossfw_input_t *paramin0 = 0 < innum ? in0 : NULL;
int err1 = -1;
int err2 = -1;




int err0 =
    mossfw_set_waitcondition(paramin0, paramsize, paramop);
if (1 < innum) {
    err1 = mossfw_set_waitcondition(in1, paramsize, paramop);
    err2 = mossfw_set_waitcondition(in2, paramsize, paramop);
}



TEST_ASSERT(err0 == OK);
TEST_ASSERT(err1 == OK);
TEST_ASSERT(err2 == OK);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
mossfw_input_delete(in2);


}

void test_mossfw_set_waitcondition_002(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
mossfw_input_t *in2 =
    mossfw_input_create(type, 1);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
int size = sizeof(mossfw_data_v1s_t);
(void)size;
int innum = 1;
int paramsize = size;
mossfw_callback_op_t *paramop = op;
mossfw_input_t *paramin0 = 0 < innum ? in0 : NULL;
int err1 = -1;
int err2 = -1;




int err0 =
    mossfw_set_waitcondition(paramin0, paramsize, paramop);
if (1 < innum) {
    err1 = mossfw_set_waitcondition(in1, paramsize, paramop);
    err2 = mossfw_set_waitcondition(in2, paramsize, paramop);
}



TEST_ASSERT(err0 == OK);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
mossfw_input_delete(in2);


}

void test_mossfw_set_waitcondition_003(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
mossfw_input_t *in2 =
    mossfw_input_create(type, 1);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
int size = sizeof(mossfw_data_v1s_t);
(void)size;
int innum = 0;
int paramsize = size;
mossfw_callback_op_t *paramop = op;
mossfw_input_t *paramin0 = 0 < innum ? in0 : NULL;
int err1 = -1;
int err2 = -1;




int err0 =
    mossfw_set_waitcondition(paramin0, paramsize, paramop);
if (1 < innum) {
    err1 = mossfw_set_waitcondition(in1, paramsize, paramop);
    err2 = mossfw_set_waitcondition(in2, paramsize, paramop);
}



TEST_ASSERT(err0 == -EINVAL);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
mossfw_input_delete(in2);


}

void test_mossfw_set_waitcondition_004(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
mossfw_input_t *in2 =
    mossfw_input_create(type, 1);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
int size = sizeof(mossfw_data_v1s_t);
(void)size;
int innum = 2;
int paramsize = 0;
mossfw_callback_op_t *paramop = op;
mossfw_input_t *paramin0 = 0 < innum ? in0 : NULL;
int err1 = -1;
int err2 = -1;




int err0 =
    mossfw_set_waitcondition(paramin0, paramsize, paramop);
if (1 < innum) {
    err1 = mossfw_set_waitcondition(in1, paramsize, paramop);
    err2 = mossfw_set_waitcondition(in2, paramsize, paramop);
}



TEST_ASSERT(err0 == -EINVAL);
TEST_ASSERT(err1 == -EINVAL);
TEST_ASSERT(err2 == -EINVAL);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
mossfw_input_delete(in2);


}

void test_mossfw_set_waitcondition_005(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
mossfw_input_t *in2 =
    mossfw_input_create(type, 1);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
int size = sizeof(mossfw_data_v1s_t);
(void)size;
int innum = 1;
int paramsize = 0;
mossfw_callback_op_t *paramop = op;
mossfw_input_t *paramin0 = 0 < innum ? in0 : NULL;
int err1 = -1;
int err2 = -1;




int err0 =
    mossfw_set_waitcondition(paramin0, paramsize, paramop);
if (1 < innum) {
    err1 = mossfw_set_waitcondition(in1, paramsize, paramop);
    err2 = mossfw_set_waitcondition(in2, paramsize, paramop);
}



TEST_ASSERT(err0 == -EINVAL);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
mossfw_input_delete(in2);


}

void test_mossfw_set_waitcondition_006(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
mossfw_input_t *in2 =
    mossfw_input_create(type, 1);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
int size = sizeof(mossfw_data_v1s_t);
(void)size;
int innum = 2;
int paramsize = size;
mossfw_callback_op_t *paramop = NULL;
mossfw_input_t *paramin0 = 0 < innum ? in0 : NULL;
int err1 = -1;
int err2 = -1;




int err0 =
    mossfw_set_waitcondition(paramin0, paramsize, paramop);
if (1 < innum) {
    err1 = mossfw_set_waitcondition(in1, paramsize, paramop);
    err2 = mossfw_set_waitcondition(in2, paramsize, paramop);
}



TEST_ASSERT(err0 == -EINVAL);
TEST_ASSERT(err1 == -EINVAL);
TEST_ASSERT(err2 == -EINVAL);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
mossfw_input_delete(in2);


}

void test_mossfw_set_waitcondition_007(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
mossfw_input_t *in2 =
    mossfw_input_create(type, 1);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
int size = sizeof(mossfw_data_v1s_t);
(void)size;
int innum = 1;
int paramsize = size;
mossfw_callback_op_t *paramop = NULL;
mossfw_input_t *paramin0 = 0 < innum ? in0 : NULL;
int err1 = -1;
int err2 = -1;




int err0 =
    mossfw_set_waitcondition(paramin0, paramsize, paramop);
if (1 < innum) {
    err1 = mossfw_set_waitcondition(in1, paramsize, paramop);
    err2 = mossfw_set_waitcondition(in2, paramsize, paramop);
}



TEST_ASSERT(err0 == -EINVAL);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
mossfw_input_delete(in2);


}

void test_mossfw_set_waitcondition_008(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
mossfw_input_t *in2 =
    mossfw_input_create(type, 1);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
int size = sizeof(mossfw_data_v1s_t);
(void)size;
int innum = 0;
int paramsize = 0;
mossfw_callback_op_t *paramop = NULL;
mossfw_input_t *paramin0 = 0 < innum ? in0 : NULL;
int err1 = -1;
int err2 = -1;




int err0 =
    mossfw_set_waitcondition(paramin0, paramsize, paramop);
if (1 < innum) {
    err1 = mossfw_set_waitcondition(in1, paramsize, paramop);
    err2 = mossfw_set_waitcondition(in2, paramsize, paramop);
}



TEST_ASSERT(err0 == -EINVAL);
TEST_ASSERT(err1 == -1);
TEST_ASSERT(err2 == -1);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
mossfw_input_delete(in2);


}

void test_mossfw_unset_waitcondition_001(void)
{

uint32_t v1s =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL;
uint32_t single = v1s |
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array = v1s |
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = single;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_input_t *input = in1;
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
mossfw_callback_op_t *op0 = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op0 != NULL);
mossfw_callback_op_t *callback_op = op;
int size = sizeof(mossfw_data_v1s_t);
int err0 =
    mossfw_set_waitcondition(in0, size, op);
TEST_ASSERT(err0 == OK);
int err1 =
    mossfw_set_waitcondition(in1, size, op);
TEST_ASSERT(err1 == OK);



int err =
    mossfw_unset_waitcondition(input, callback_op);



TEST_ASSERT(err == OK);
mossfw_callback_op_delete(op0);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
(void)single;
(void)array;


}

void test_mossfw_unset_waitcondition_002(void)
{

uint32_t v1s =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL;
uint32_t single = v1s |
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array = v1s |
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = single;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_input_t *input = in0;
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
mossfw_callback_op_t *op0 = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op0 != NULL);
mossfw_callback_op_t *callback_op = op0;
int size = sizeof(mossfw_data_v1s_t);
int err0 =
    mossfw_set_waitcondition(in0, size, op);
TEST_ASSERT(err0 == OK);
int err1 =
    mossfw_set_waitcondition(in1, size, op);
TEST_ASSERT(err1 == OK);



int err =
    mossfw_unset_waitcondition(input, callback_op);



TEST_ASSERT(err == OK);
mossfw_callback_op_delete(op0);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
(void)single;
(void)array;


}

void test_mossfw_unset_waitcondition_003(void)
{

uint32_t v1s =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL;
uint32_t single = v1s |
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array = v1s |
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_input_t *input = in0;
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
mossfw_callback_op_t *op0 = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op0 != NULL);
mossfw_callback_op_t *callback_op = op;
int size = sizeof(mossfw_data_v1s_t);
int err0 =
    mossfw_set_waitcondition(in0, size, op);
TEST_ASSERT(err0 == OK);
int err1 =
    mossfw_set_waitcondition(in1, size, op);
TEST_ASSERT(err1 == OK);



int err =
    mossfw_unset_waitcondition(input, callback_op);



TEST_ASSERT(err == OK);
mossfw_callback_op_delete(op0);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
(void)single;
(void)array;


}

void test_mossfw_unset_waitcondition_004(void)
{

uint32_t v1s =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL;
uint32_t single = v1s |
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array = v1s |
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_input_t *input = in1;
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
mossfw_callback_op_t *op0 = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op0 != NULL);
mossfw_callback_op_t *callback_op = op0;
int size = sizeof(mossfw_data_v1s_t);
int err0 =
    mossfw_set_waitcondition(in0, size, op);
TEST_ASSERT(err0 == OK);
int err1 =
    mossfw_set_waitcondition(in1, size, op);
TEST_ASSERT(err1 == OK);



int err =
    mossfw_unset_waitcondition(input, callback_op);



TEST_ASSERT(err == OK);
mossfw_callback_op_delete(op0);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
(void)single;
(void)array;


}

void test_mossfw_unset_waitcondition_005(void)
{

uint32_t v1s =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL;
uint32_t single = v1s |
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array = v1s |
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = single;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_input_t *input = NULL;
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
mossfw_callback_op_t *op0 = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op0 != NULL);
mossfw_callback_op_t *callback_op = op;
int size = sizeof(mossfw_data_v1s_t);
int err0 =
    mossfw_set_waitcondition(in0, size, op);
TEST_ASSERT(err0 == OK);
int err1 =
    mossfw_set_waitcondition(in1, size, op);
TEST_ASSERT(err1 == OK);



int err =
    mossfw_unset_waitcondition(input, callback_op);



TEST_ASSERT(err == -EINVAL);
mossfw_callback_op_delete(op0);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
(void)single;
(void)array;


}

void test_mossfw_unset_waitcondition_006(void)
{

uint32_t v1s =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL;
uint32_t single = v1s |
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array = v1s |
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = single;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_input_t *input = NULL;
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
mossfw_callback_op_t *op0 = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op0 != NULL);
mossfw_callback_op_t *callback_op = op0;
int size = sizeof(mossfw_data_v1s_t);
int err0 =
    mossfw_set_waitcondition(in0, size, op);
TEST_ASSERT(err0 == OK);
int err1 =
    mossfw_set_waitcondition(in1, size, op);
TEST_ASSERT(err1 == OK);



int err =
    mossfw_unset_waitcondition(input, callback_op);



TEST_ASSERT(err == -EINVAL);
mossfw_callback_op_delete(op0);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
(void)single;
(void)array;


}

void test_mossfw_unset_waitcondition_007(void)
{

uint32_t v1s =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL;
uint32_t single = v1s |
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array = v1s |
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_input_t *input = NULL;
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
mossfw_callback_op_t *op0 = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op0 != NULL);
mossfw_callback_op_t *callback_op = op;
int size = sizeof(mossfw_data_v1s_t);
int err0 =
    mossfw_set_waitcondition(in0, size, op);
TEST_ASSERT(err0 == OK);
int err1 =
    mossfw_set_waitcondition(in1, size, op);
TEST_ASSERT(err1 == OK);



int err =
    mossfw_unset_waitcondition(input, callback_op);



TEST_ASSERT(err == -EINVAL);
mossfw_callback_op_delete(op0);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
(void)single;
(void)array;


}

void test_mossfw_unset_waitcondition_008(void)
{

uint32_t v1s =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL;
uint32_t single = v1s |
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array = v1s |
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_input_t *input = NULL;
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
mossfw_callback_op_t *op0 = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op0 != NULL);
mossfw_callback_op_t *callback_op = op0;
int size = sizeof(mossfw_data_v1s_t);
int err0 =
    mossfw_set_waitcondition(in0, size, op);
TEST_ASSERT(err0 == OK);
int err1 =
    mossfw_set_waitcondition(in1, size, op);
TEST_ASSERT(err1 == OK);



int err =
    mossfw_unset_waitcondition(input, callback_op);



TEST_ASSERT(err == -EINVAL);
mossfw_callback_op_delete(op0);
mossfw_callback_op_delete(op);
mossfw_input_delete(in0);
mossfw_input_delete(in1);
(void)single;
(void)array;


}

void test_mossfw_update_waitsize_001(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPEARRAY_SINGLE |
    MOSSFW_DATA_TYPENAME_ACCEL;
int size = sizeof(mossfw_data_v1s_t);
mossfw_input_t *in =
    mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int err0 =
    mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);



int err =
    mossfw_update_waitsize(in, 2 * size);



TEST_ASSERT(err == size);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_update_waitsize_002(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_SHORT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPEARRAY_SINGLE |
    MOSSFW_DATA_TYPENAME_ACCEL;
int size = sizeof(mossfw_data_v1s_t);
mossfw_input_t *in =
    mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 =
    mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);



int err =
    mossfw_update_waitsize(in, 2 * size);



TEST_ASSERT(err == size);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_001(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (0) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = out;
mossfw_onedata_t *dataparam = &data;
if (0) {
    operate = op->operate;
    op->operate = NULL;
}
if (0) {
    inop = in->op;
    in->op = NULL;
}
if (0 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == OK);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_002(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (0) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = NULL;
mossfw_onedata_t *dataparam = &data;
if (0) {
    operate = op->operate;
    op->operate = NULL;
}
if (0) {
    inop = in->op;
    in->op = NULL;
}
if (0 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == -EINVAL);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_003(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (0) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = out;
mossfw_onedata_t *dataparam = NULL;
if (0) {
    operate = op->operate;
    op->operate = NULL;
}
if (0) {
    inop = in->op;
    in->op = NULL;
}
if (0 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == -EINVAL);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_004(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = array;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (0) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = out;
mossfw_onedata_t *dataparam = &data;
if (0) {
    operate = op->operate;
    op->operate = NULL;
}
if (0) {
    inop = in->op;
    in->op = NULL;
}
if (0 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == -EIO);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_005(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (0) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = out;
mossfw_onedata_t *dataparam = &data;
if (1) {
    operate = op->operate;
    op->operate = NULL;
}
if (0) {
    inop = in->op;
    in->op = NULL;
}
if (0 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == OK);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_006(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (1) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = out;
mossfw_onedata_t *dataparam = &data;
if (0) {
    operate = op->operate;
    op->operate = NULL;
}
if (0) {
    inop = in->op;
    in->op = NULL;
}
if (0 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == OK);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_007(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (0) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = out;
mossfw_onedata_t *dataparam = &data;
if (0) {
    operate = op->operate;
    op->operate = NULL;
}
if (1) {
    inop = in->op;
    in->op = NULL;
}
if (0 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == OK);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_008(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (0) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = out;
mossfw_onedata_t *dataparam = &data;
if (0) {
    operate = op->operate;
    op->operate = NULL;
}
if (0) {
    inop = in->op;
    in->op = NULL;
}
if (1 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == -EAGAIN);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_009(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = array;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (1) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = NULL;
mossfw_onedata_t *dataparam = &data;
if (1) {
    operate = op->operate;
    op->operate = NULL;
}
if (0) {
    inop = in->op;
    in->op = NULL;
}
if (1 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == -EINVAL);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_010(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (0) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = out;
mossfw_onedata_t *dataparam = NULL;
if (0) {
    operate = op->operate;
    op->operate = NULL;
}
if (1) {
    inop = in->op;
    in->op = NULL;
}
if (0 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == -EINVAL);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_011(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (0) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = NULL;
mossfw_onedata_t *dataparam = NULL;
if (1) {
    operate = op->operate;
    op->operate = NULL;
}
if (1) {
    inop = in->op;
    in->op = NULL;
}
if (1 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == -EINVAL);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_012(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = array;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (1) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = NULL;
mossfw_onedata_t *dataparam = NULL;
if (0) {
    operate = op->operate;
    op->operate = NULL;
}
if (1) {
    inop = in->op;
    in->op = NULL;
}
if (0 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == -EINVAL);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_013(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (1) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = out;
mossfw_onedata_t *dataparam = NULL;
if (0) {
    operate = op->operate;
    op->operate = NULL;
}
if (0) {
    inop = in->op;
    in->op = NULL;
}
if (1 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == -EINVAL);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_data_014(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v3c_t);
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
(void)single;
(void)array;
(void)data.xyzc.x;
(void)data.xyzc.y;
(void)data.xyzc.z;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
mossfw_operator_t operate = NULL;
mossfw_input_t *input = NULL;
mossfw_callback_op_t *inop = NULL;
if (1) {
    input = op->input;
    op->input = NULL;
}
mossfw_output_t *outparam = out;
mossfw_onedata_t *dataparam = &data;
if (1) {
    operate = op->operate;
    op->operate = NULL;
}
if (1) {
    inop = in->op;
    in->op = NULL;
}
if (0 && in->op != NULL) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}



int err =
    mossfw_deliver_data(outparam,
                        dataparam);



TEST_ASSERT(err == OK);
if (operate && type == single && outparam != NULL && dataparam != NULL) {
    sleep(1);
}
if (input != NULL) {
    op->input = input;
}
if (operate != NULL) {
    op->operate = operate;
}
if (inop != NULL) {
    in->op = inop;
}

mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliver_dataarray_001(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_output_t *out =
    mossfw_output_create(type);
int size = sizeof(mossfw_data_qf_t);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *data =
    mossfw_data_alloc(allocator, size, 1);
data->data.qf[0].x = 0;
data->data.qf[0].y = 0;
data->data.qf[0].z = 0;
data->data.qf[0].w = 0;
(void)single;
(void)array;
(void)data->data.qf[0].x;
(void)data->data.qf[0].y;
(void)data->data.qf[0].z;
(void)data->data.qf[0].w;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
if (0) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
mossfw_callback_op_t *inop = NULL;
if (0) {
    inop = in->op;
    in->op = NULL;
}



int err =
    mossfw_deliver_dataarray(out,
                             data);




TEST_ASSERT(err == OK);
if (inop != NULL) {
    in->op = inop;
}
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);
mossfw_data_free(data);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);


}

void test_mossfw_deliver_dataarray_002(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_output_t *out =
    mossfw_output_create(type);
int size = sizeof(mossfw_data_qf_t);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *data =
    mossfw_data_alloc(allocator, size, 1);
data->data.qf[0].x = 0;
data->data.qf[0].y = 0;
data->data.qf[0].z = 0;
data->data.qf[0].w = 0;
(void)single;
(void)array;
(void)data->data.qf[0].x;
(void)data->data.qf[0].y;
(void)data->data.qf[0].z;
(void)data->data.qf[0].w;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
if (0) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
mossfw_callback_op_t *inop = NULL;
if (0) {
    inop = in->op;
    in->op = NULL;
}



int err =
    mossfw_deliver_dataarray(NULL,
                             data);




TEST_ASSERT(err == -EINVAL);
if (inop != NULL) {
    in->op = inop;
}
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);
mossfw_data_free(data);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);


}

void test_mossfw_deliver_dataarray_003(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_output_t *out =
    mossfw_output_create(type);
int size = sizeof(mossfw_data_qf_t);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *data =
    mossfw_data_alloc(allocator, size, 1);
data->data.qf[0].x = 0;
data->data.qf[0].y = 0;
data->data.qf[0].z = 0;
data->data.qf[0].w = 0;
(void)single;
(void)array;
(void)data->data.qf[0].x;
(void)data->data.qf[0].y;
(void)data->data.qf[0].z;
(void)data->data.qf[0].w;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
if (0) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
mossfw_callback_op_t *inop = NULL;
if (0) {
    inop = in->op;
    in->op = NULL;
}



int err =
    mossfw_deliver_dataarray(out,
                             NULL);




TEST_ASSERT(err == -EINVAL);
if (inop != NULL) {
    in->op = inop;
}
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);
mossfw_data_free(data);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);


}

void test_mossfw_deliver_dataarray_004(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
int size = sizeof(mossfw_data_qf_t);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *data =
    mossfw_data_alloc(allocator, size, 1);
data->data.qf[0].x = 0;
data->data.qf[0].y = 0;
data->data.qf[0].z = 0;
data->data.qf[0].w = 0;
(void)single;
(void)array;
(void)data->data.qf[0].x;
(void)data->data.qf[0].y;
(void)data->data.qf[0].z;
(void)data->data.qf[0].w;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
if (0) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
mossfw_callback_op_t *inop = NULL;
if (0) {
    inop = in->op;
    in->op = NULL;
}



int err =
    mossfw_deliver_dataarray(out,
                             data);




TEST_ASSERT(err == -EIO);
if (inop != NULL) {
    in->op = inop;
}
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);
mossfw_data_free(data);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);


}

void test_mossfw_deliver_dataarray_005(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_output_t *out =
    mossfw_output_create(type);
int size = sizeof(mossfw_data_qf_t);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *data =
    mossfw_data_alloc(allocator, size, 1);
data->data.qf[0].x = 0;
data->data.qf[0].y = 0;
data->data.qf[0].z = 0;
data->data.qf[0].w = 0;
(void)single;
(void)array;
(void)data->data.qf[0].x;
(void)data->data.qf[0].y;
(void)data->data.qf[0].z;
(void)data->data.qf[0].w;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
if (0) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
mossfw_callback_op_t *inop = NULL;
if (1) {
    inop = in->op;
    in->op = NULL;
}



int err =
    mossfw_deliver_dataarray(out,
                             data);




TEST_ASSERT(err == OK);
if (inop != NULL) {
    in->op = inop;
}
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);
mossfw_data_free(data);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);


}

void test_mossfw_deliver_dataarray_006(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_output_t *out =
    mossfw_output_create(type);
int size = sizeof(mossfw_data_qf_t);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *data =
    mossfw_data_alloc(allocator, size, 1);
data->data.qf[0].x = 0;
data->data.qf[0].y = 0;
data->data.qf[0].z = 0;
data->data.qf[0].w = 0;
(void)single;
(void)array;
(void)data->data.qf[0].x;
(void)data->data.qf[0].y;
(void)data->data.qf[0].z;
(void)data->data.qf[0].w;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
if (1) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
mossfw_callback_op_t *inop = NULL;
if (0) {
    inop = in->op;
    in->op = NULL;
}



int err =
    mossfw_deliver_dataarray(out,
                             data);




TEST_ASSERT(err == -EAGAIN);
if (inop != NULL) {
    in->op = inop;
}
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);
mossfw_data_free(data);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);


}

void test_mossfw_deliver_dataarray_007(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_output_t *out =
    mossfw_output_create(type);
int size = sizeof(mossfw_data_qf_t);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *data =
    mossfw_data_alloc(allocator, size, 1);
data->data.qf[0].x = 0;
data->data.qf[0].y = 0;
data->data.qf[0].z = 0;
data->data.qf[0].w = 0;
(void)single;
(void)array;
(void)data->data.qf[0].x;
(void)data->data.qf[0].y;
(void)data->data.qf[0].z;
(void)data->data.qf[0].w;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
if (1) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
mossfw_callback_op_t *inop = NULL;
if (1) {
    inop = in->op;
    in->op = NULL;
}



int err =
    mossfw_deliver_dataarray(NULL,
                             NULL);




TEST_ASSERT(err == -EINVAL);
if (inop != NULL) {
    in->op = inop;
}
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);
mossfw_data_free(data);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);


}

void test_mossfw_deliver_dataarray_008(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
int size = sizeof(mossfw_data_qf_t);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *data =
    mossfw_data_alloc(allocator, size, 1);
data->data.qf[0].x = 0;
data->data.qf[0].y = 0;
data->data.qf[0].z = 0;
data->data.qf[0].w = 0;
(void)single;
(void)array;
(void)data->data.qf[0].x;
(void)data->data.qf[0].y;
(void)data->data.qf[0].z;
(void)data->data.qf[0].w;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
if (1) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
mossfw_callback_op_t *inop = NULL;
if (1) {
    inop = in->op;
    in->op = NULL;
}



int err =
    mossfw_deliver_dataarray(out,
                             data);




TEST_ASSERT(err == -EIO);
if (inop != NULL) {
    in->op = inop;
}
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);
mossfw_data_free(data);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);


}

void test_mossfw_deliver_dataarray_009(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_output_t *out =
    mossfw_output_create(type);
int size = sizeof(mossfw_data_qf_t);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *data =
    mossfw_data_alloc(allocator, size, 1);
data->data.qf[0].x = 0;
data->data.qf[0].y = 0;
data->data.qf[0].z = 0;
data->data.qf[0].w = 0;
(void)single;
(void)array;
(void)data->data.qf[0].x;
(void)data->data.qf[0].y;
(void)data->data.qf[0].z;
(void)data->data.qf[0].w;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
if (1) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
mossfw_callback_op_t *inop = NULL;
if (0) {
    inop = in->op;
    in->op = NULL;
}



int err =
    mossfw_deliver_dataarray(NULL,
                             data);




TEST_ASSERT(err == -EINVAL);
if (inop != NULL) {
    in->op = inop;
}
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);
mossfw_data_free(data);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);


}

void test_mossfw_deliver_dataarray_010(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = array;
mossfw_output_t *out =
    mossfw_output_create(type);
int size = sizeof(mossfw_data_qf_t);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *data =
    mossfw_data_alloc(allocator, size, 1);
data->data.qf[0].x = 0;
data->data.qf[0].y = 0;
data->data.qf[0].z = 0;
data->data.qf[0].w = 0;
(void)single;
(void)array;
(void)data->data.qf[0].x;
(void)data->data.qf[0].y;
(void)data->data.qf[0].z;
(void)data->data.qf[0].w;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
if (0) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
mossfw_callback_op_t *inop = NULL;
if (1) {
    inop = in->op;
    in->op = NULL;
}



int err =
    mossfw_deliver_dataarray(out,
                             NULL);




TEST_ASSERT(err == -EINVAL);
if (inop != NULL) {
    in->op = inop;
}
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);
mossfw_data_free(data);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);


}

void test_mossfw_deliver_dataarray_011(void)
{

uint32_t single =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t array =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_Q | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
uint32_t type = single;
mossfw_output_t *out =
    mossfw_output_create(type);
int size = sizeof(mossfw_data_qf_t);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *data =
    mossfw_data_alloc(allocator, size, 1);
data->data.qf[0].x = 0;
data->data.qf[0].y = 0;
data->data.qf[0].z = 0;
data->data.qf[0].w = 0;
(void)single;
(void)array;
(void)data->data.qf[0].x;
(void)data->data.qf[0].y;
(void)data->data.qf[0].z;
(void)data->data.qf[0].w;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in);
int binderr = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(binderr == OK);
mossfw_callback_op_t *op =
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
int err0 = mossfw_set_waitcondition(in, size, op);
TEST_ASSERT(err0 == OK);
if (0) {
    int val = mossfw_update_waitsize(in, -1);
    TEST_ASSERT(val == size);
}
mossfw_callback_op_t *inop = NULL;
if (0) {
    inop = in->op;
    in->op = NULL;
}



int err =
    mossfw_deliver_dataarray(NULL,
                             NULL);




TEST_ASSERT(err == -EINVAL);
if (inop != NULL) {
    in->op = inop;
}
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);
mossfw_data_free(data);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);


}

void test_mossfw_get_delivereddata_num_001(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
int datasize = sizeof(mossfw_data_v3c_t);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * datasize, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
int errd = mossfw_deliver_data(out, &data);
TEST_ASSERT(errd == OK);





int num =
    mossfw_get_delivereddata_num(in);




int size = sizeof(mossfw_data_v3c_t);
(void)size;
TEST_ASSERT(num == size);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_num_002(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
int datasize = sizeof(mossfw_data_v3c_t);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * datasize, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t data;
data.xyzc.x = 0;
data.xyzc.y = 0;
data.xyzc.z = 0;
int errd = mossfw_deliver_data(out, &data);
TEST_ASSERT(errd == OK);





int num =
    mossfw_get_delivereddata_num(NULL);




int size = sizeof(mossfw_data_v3c_t);
(void)size;
TEST_ASSERT(num < 0);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_single_001(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 1;
int size = sizeof(mossfw_data_v2c_t);
uint32_t type = (datatype < 0 ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyc[0].x = 0;
idataarray->data.xyc[0].y = 0;
idataarray->data_bytes = size;
if (datatype != 0) {
    if (type == typesingle) {
        int errd = mossfw_deliver_data(out, &idatasingle);
        TEST_ASSERT(errd == OK);
    } else {
        int errd = mossfw_deliver_dataarray(out, idataarray);
        TEST_ASSERT(errd == OK);
    }
}
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;



int num =
    mossfw_get_delivereddata_single(in,
                                    &odata);



TEST_ASSERT(num == size);
if (0 < num) {
    TEST_ASSERT(odata.xyc.x == idatasingle.xyc.x);
    TEST_ASSERT(odata.xyc.y == idatasingle.xyc.y);
}
if (type == typearray && datatype != 0) {
    int used = 0;
    mossfw_data_t *odataarray =
        mossfw_get_delivereddata_array(in, size, &used);
    TEST_ASSERT(odataarray != NULL);
    TEST_ASSERT(used == 0);
    mossfw_data_free(odataarray);
}
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_single_002(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 1;
int size = sizeof(mossfw_data_v2c_t);
uint32_t type = (datatype < 0 ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyc[0].x = 0;
idataarray->data.xyc[0].y = 0;
idataarray->data_bytes = size;
if (datatype != 0) {
    if (type == typesingle) {
        int errd = mossfw_deliver_data(out, &idatasingle);
        TEST_ASSERT(errd == OK);
    } else {
        int errd = mossfw_deliver_dataarray(out, idataarray);
        TEST_ASSERT(errd == OK);
    }
}
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;



int num =
    mossfw_get_delivereddata_single(NULL,
                                    &odata);



TEST_ASSERT(num < 0);
if (0 < num) {
    TEST_ASSERT(odata.xyc.x == idatasingle.xyc.x);
    TEST_ASSERT(odata.xyc.y == idatasingle.xyc.y);
}
if (type == typearray && datatype != 0) {
    int used = 0;
    mossfw_data_t *odataarray =
        mossfw_get_delivereddata_array(in, size, &used);
    TEST_ASSERT(odataarray != NULL);
    TEST_ASSERT(used == 0);
    mossfw_data_free(odataarray);
}
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_single_003(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 1;
int size = sizeof(mossfw_data_v2c_t);
uint32_t type = (datatype < 0 ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyc[0].x = 0;
idataarray->data.xyc[0].y = 0;
idataarray->data_bytes = size;
if (datatype != 0) {
    if (type == typesingle) {
        int errd = mossfw_deliver_data(out, &idatasingle);
        TEST_ASSERT(errd == OK);
    } else {
        int errd = mossfw_deliver_dataarray(out, idataarray);
        TEST_ASSERT(errd == OK);
    }
}
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;



int num =
    mossfw_get_delivereddata_single(in,
                                    NULL);



TEST_ASSERT(num < 0);
if (0 < num) {
    TEST_ASSERT(odata.xyc.x == idatasingle.xyc.x);
    TEST_ASSERT(odata.xyc.y == idatasingle.xyc.y);
}
if (type == typearray && datatype != 0) {
    int used = 0;
    mossfw_data_t *odataarray =
        mossfw_get_delivereddata_array(in, size, &used);
    TEST_ASSERT(odataarray != NULL);
    TEST_ASSERT(used == 0);
    mossfw_data_free(odataarray);
}
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_single_004(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = -1;
int size = sizeof(mossfw_data_v2c_t);
uint32_t type = (datatype < 0 ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyc[0].x = 0;
idataarray->data.xyc[0].y = 0;
idataarray->data_bytes = size;
if (datatype != 0) {
    if (type == typesingle) {
        int errd = mossfw_deliver_data(out, &idatasingle);
        TEST_ASSERT(errd == OK);
    } else {
        int errd = mossfw_deliver_dataarray(out, idataarray);
        TEST_ASSERT(errd == OK);
    }
}
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;



int num =
    mossfw_get_delivereddata_single(in,
                                    &odata);



TEST_ASSERT(num < 0);
if (0 < num) {
    TEST_ASSERT(odata.xyc.x == idatasingle.xyc.x);
    TEST_ASSERT(odata.xyc.y == idatasingle.xyc.y);
}
if (type == typearray && datatype != 0) {
    int used = 0;
    mossfw_data_t *odataarray =
        mossfw_get_delivereddata_array(in, size, &used);
    TEST_ASSERT(odataarray != NULL);
    TEST_ASSERT(used == 0);
    mossfw_data_free(odataarray);
}
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_single_005(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 0;
int size = sizeof(mossfw_data_v2c_t);
uint32_t type = (datatype < 0 ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyc[0].x = 0;
idataarray->data.xyc[0].y = 0;
idataarray->data_bytes = size;
if (datatype != 0) {
    if (type == typesingle) {
        int errd = mossfw_deliver_data(out, &idatasingle);
        TEST_ASSERT(errd == OK);
    } else {
        int errd = mossfw_deliver_dataarray(out, idataarray);
        TEST_ASSERT(errd == OK);
    }
}
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;



int num =
    mossfw_get_delivereddata_single(in,
                                    &odata);



TEST_ASSERT(num == 0);
if (0 < num) {
    TEST_ASSERT(odata.xyc.x == idatasingle.xyc.x);
    TEST_ASSERT(odata.xyc.y == idatasingle.xyc.y);
}
if (type == typearray && datatype != 0) {
    int used = 0;
    mossfw_data_t *odataarray =
        mossfw_get_delivereddata_array(in, size, &used);
    TEST_ASSERT(odataarray != NULL);
    TEST_ASSERT(used == 0);
    mossfw_data_free(odataarray);
}
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_single_006(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 0;
int size = sizeof(mossfw_data_v2c_t);
uint32_t type = (datatype < 0 ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyc[0].x = 0;
idataarray->data.xyc[0].y = 0;
idataarray->data_bytes = size;
if (datatype != 0) {
    if (type == typesingle) {
        int errd = mossfw_deliver_data(out, &idatasingle);
        TEST_ASSERT(errd == OK);
    } else {
        int errd = mossfw_deliver_dataarray(out, idataarray);
        TEST_ASSERT(errd == OK);
    }
}
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;



int num =
    mossfw_get_delivereddata_single(NULL,
                                    NULL);



TEST_ASSERT(num < 0);
if (0 < num) {
    TEST_ASSERT(odata.xyc.x == idatasingle.xyc.x);
    TEST_ASSERT(odata.xyc.y == idatasingle.xyc.y);
}
if (type == typearray && datatype != 0) {
    int used = 0;
    mossfw_data_t *odataarray =
        mossfw_get_delivereddata_array(in, size, &used);
    TEST_ASSERT(odataarray != NULL);
    TEST_ASSERT(used == 0);
    mossfw_data_free(odataarray);
}
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_single_007(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = -1;
int size = sizeof(mossfw_data_v2c_t);
uint32_t type = (datatype < 0 ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyc[0].x = 0;
idataarray->data.xyc[0].y = 0;
idataarray->data_bytes = size;
if (datatype != 0) {
    if (type == typesingle) {
        int errd = mossfw_deliver_data(out, &idatasingle);
        TEST_ASSERT(errd == OK);
    } else {
        int errd = mossfw_deliver_dataarray(out, idataarray);
        TEST_ASSERT(errd == OK);
    }
}
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;



int num =
    mossfw_get_delivereddata_single(NULL,
                                    &odata);



TEST_ASSERT(num < 0);
if (0 < num) {
    TEST_ASSERT(odata.xyc.x == idatasingle.xyc.x);
    TEST_ASSERT(odata.xyc.y == idatasingle.xyc.y);
}
if (type == typearray && datatype != 0) {
    int used = 0;
    mossfw_data_t *odataarray =
        mossfw_get_delivereddata_array(in, size, &used);
    TEST_ASSERT(odataarray != NULL);
    TEST_ASSERT(used == 0);
    mossfw_data_free(odataarray);
}
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_single_008(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = -1;
int size = sizeof(mossfw_data_v2c_t);
uint32_t type = (datatype < 0 ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyc[0].x = 0;
idataarray->data.xyc[0].y = 0;
idataarray->data_bytes = size;
if (datatype != 0) {
    if (type == typesingle) {
        int errd = mossfw_deliver_data(out, &idatasingle);
        TEST_ASSERT(errd == OK);
    } else {
        int errd = mossfw_deliver_dataarray(out, idataarray);
        TEST_ASSERT(errd == OK);
    }
}
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;



int num =
    mossfw_get_delivereddata_single(in,
                                    NULL);



TEST_ASSERT(num < 0);
if (0 < num) {
    TEST_ASSERT(odata.xyc.x == idatasingle.xyc.x);
    TEST_ASSERT(odata.xyc.y == idatasingle.xyc.y);
}
if (type == typearray && datatype != 0) {
    int used = 0;
    mossfw_data_t *odataarray =
        mossfw_get_delivereddata_array(in, size, &used);
    TEST_ASSERT(odataarray != NULL);
    TEST_ASSERT(used == 0);
    mossfw_data_free(odataarray);
}
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_array_001(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 1;
int size = sizeof(mossfw_data_v1c_t);
uint32_t type = (datatype ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xc.x = 9;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xc[0].x = 0;
idataarray->data_bytes = size;
if (type == typesingle) {
    int errd = mossfw_deliver_data(out, &idatasingle);
    TEST_ASSERT(errd == OK);
} else {
    int errd = mossfw_deliver_dataarray(out, idataarray);
    TEST_ASSERT(errd == OK);
}
int used = 0;



mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in,
                                   size,
                                   &used);



TEST_ASSERT(odata != NULL);
if (odata != NULL) {
    TEST_ASSERT(odata->data.xc == idataarray->data.xc);
    TEST_ASSERT(used == 0);
} else if (datatype == 1) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_array_002(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 1;
int size = sizeof(mossfw_data_v1c_t);
uint32_t type = (datatype ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xc.x = 9;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xc[0].x = 0;
idataarray->data_bytes = size;
if (type == typesingle) {
    int errd = mossfw_deliver_data(out, &idatasingle);
    TEST_ASSERT(errd == OK);
} else {
    int errd = mossfw_deliver_dataarray(out, idataarray);
    TEST_ASSERT(errd == OK);
}
int used = 0;



mossfw_data_t *odata =
    mossfw_get_delivereddata_array(NULL,
                                   size,
                                   &used);



TEST_ASSERT(odata == NULL);
if (odata != NULL) {
    TEST_ASSERT(odata->data.xc == idataarray->data.xc);
    TEST_ASSERT(used == 0);
} else if (datatype == 1) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_array_003(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 1;
int size = sizeof(mossfw_data_v1c_t);
uint32_t type = (datatype ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xc.x = 9;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xc[0].x = 0;
idataarray->data_bytes = size;
if (type == typesingle) {
    int errd = mossfw_deliver_data(out, &idatasingle);
    TEST_ASSERT(errd == OK);
} else {
    int errd = mossfw_deliver_dataarray(out, idataarray);
    TEST_ASSERT(errd == OK);
}
int used = 0;



mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in,
                                   (size + 1),
                                   &used);



TEST_ASSERT(odata == NULL);
if (odata != NULL) {
    TEST_ASSERT(odata->data.xc == idataarray->data.xc);
    TEST_ASSERT(used == 0);
} else if (datatype == 1) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_array_004(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 1;
int size = sizeof(mossfw_data_v1c_t);
uint32_t type = (datatype ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xc.x = 9;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xc[0].x = 0;
idataarray->data_bytes = size;
if (type == typesingle) {
    int errd = mossfw_deliver_data(out, &idatasingle);
    TEST_ASSERT(errd == OK);
} else {
    int errd = mossfw_deliver_dataarray(out, idataarray);
    TEST_ASSERT(errd == OK);
}
int used = 0;



mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in,
                                   size,
                                   NULL);



TEST_ASSERT(odata != NULL);
if (odata != NULL) {
    TEST_ASSERT(odata->data.xc == idataarray->data.xc);
    TEST_ASSERT(used == 0);
} else if (datatype == 1) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_array_005(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 0;
int size = sizeof(mossfw_data_v1c_t);
uint32_t type = (datatype ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xc.x = 9;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xc[0].x = 0;
idataarray->data_bytes = size;
if (type == typesingle) {
    int errd = mossfw_deliver_data(out, &idatasingle);
    TEST_ASSERT(errd == OK);
} else {
    int errd = mossfw_deliver_dataarray(out, idataarray);
    TEST_ASSERT(errd == OK);
}
int used = 0;



mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in,
                                   size,
                                   &used);



TEST_ASSERT(odata == NULL);
if (odata != NULL) {
    TEST_ASSERT(odata->data.xc == idataarray->data.xc);
    TEST_ASSERT(used == 0);
} else if (datatype == 1) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_array_006(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 0;
int size = sizeof(mossfw_data_v1c_t);
uint32_t type = (datatype ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xc.x = 9;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xc[0].x = 0;
idataarray->data_bytes = size;
if (type == typesingle) {
    int errd = mossfw_deliver_data(out, &idatasingle);
    TEST_ASSERT(errd == OK);
} else {
    int errd = mossfw_deliver_dataarray(out, idataarray);
    TEST_ASSERT(errd == OK);
}
int used = 0;



mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in,
                                   size,
                                   NULL);



TEST_ASSERT(odata == NULL);
if (odata != NULL) {
    TEST_ASSERT(odata->data.xc == idataarray->data.xc);
    TEST_ASSERT(used == 0);
} else if (datatype == 1) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_array_007(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 1;
int size = sizeof(mossfw_data_v1c_t);
uint32_t type = (datatype ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xc.x = 9;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xc[0].x = 0;
idataarray->data_bytes = size;
if (type == typesingle) {
    int errd = mossfw_deliver_data(out, &idatasingle);
    TEST_ASSERT(errd == OK);
} else {
    int errd = mossfw_deliver_dataarray(out, idataarray);
    TEST_ASSERT(errd == OK);
}
int used = 0;



mossfw_data_t *odata =
    mossfw_get_delivereddata_array(NULL,
                                   (size + 1),
                                   &used);



TEST_ASSERT(odata == NULL);
if (odata != NULL) {
    TEST_ASSERT(odata->data.xc == idataarray->data.xc);
    TEST_ASSERT(used == 0);
} else if (datatype == 1) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_array_008(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 0;
int size = sizeof(mossfw_data_v1c_t);
uint32_t type = (datatype ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xc.x = 9;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xc[0].x = 0;
idataarray->data_bytes = size;
if (type == typesingle) {
    int errd = mossfw_deliver_data(out, &idatasingle);
    TEST_ASSERT(errd == OK);
} else {
    int errd = mossfw_deliver_dataarray(out, idataarray);
    TEST_ASSERT(errd == OK);
}
int used = 0;



mossfw_data_t *odata =
    mossfw_get_delivereddata_array(NULL,
                                   (size + 1),
                                   NULL);



TEST_ASSERT(odata == NULL);
if (odata != NULL) {
    TEST_ASSERT(odata->data.xc == idataarray->data.xc);
    TEST_ASSERT(used == 0);
} else if (datatype == 1) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_array_009(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 0;
int size = sizeof(mossfw_data_v1c_t);
uint32_t type = (datatype ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xc.x = 9;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xc[0].x = 0;
idataarray->data_bytes = size;
if (type == typesingle) {
    int errd = mossfw_deliver_data(out, &idatasingle);
    TEST_ASSERT(errd == OK);
} else {
    int errd = mossfw_deliver_dataarray(out, idataarray);
    TEST_ASSERT(errd == OK);
}
int used = 0;



mossfw_data_t *odata =
    mossfw_get_delivereddata_array(NULL,
                                   size,
                                   &used);



TEST_ASSERT(odata == NULL);
if (odata != NULL) {
    TEST_ASSERT(odata->data.xc == idataarray->data.xc);
    TEST_ASSERT(used == 0);
} else if (datatype == 1) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_get_delivereddata_array_010(void)
{

uint32_t typesingle =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
uint32_t typearray =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int datatype = 1;
int size = sizeof(mossfw_data_v1c_t);
uint32_t type = (datatype ? typearray : typesingle);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xc.x = 9;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xc[0].x = 0;
idataarray->data_bytes = size;
if (type == typesingle) {
    int errd = mossfw_deliver_data(out, &idatasingle);
    TEST_ASSERT(errd == OK);
} else {
    int errd = mossfw_deliver_dataarray(out, idataarray);
    TEST_ASSERT(errd == OK);
}
int used = 0;



mossfw_data_t *odata =
    mossfw_get_delivereddata_array(NULL,
                                   size,
                                   NULL);



TEST_ASSERT(odata == NULL);
if (odata != NULL) {
    TEST_ASSERT(odata->data.xc == idataarray->data.xc);
    TEST_ASSERT(used == 0);
} else if (datatype == 1) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliverback_dataarray_001(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v2f_t);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyf[0].x = 0.1;
idataarray->data.xyf[0].y = -0.1;
idataarray->data_bytes = size;
int errd = mossfw_deliver_dataarray(out, idataarray);
TEST_ASSERT(errd == OK);
int used = 0;
mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in, size, &used);




bool normal =
     mossfw_deliverback_dataarray(in,
                                  odata,
                                  0);



TEST_ASSERT(normal == true);
if (normal) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliverback_dataarray_002(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v2f_t);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyf[0].x = 0.1;
idataarray->data.xyf[0].y = -0.1;
idataarray->data_bytes = size;
int errd = mossfw_deliver_dataarray(out, idataarray);
TEST_ASSERT(errd == OK);
int used = 0;
mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in, size, &used);




bool normal =
     mossfw_deliverback_dataarray(NULL,
                                  odata,
                                  0);



TEST_ASSERT(normal == false);
if (normal) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliverback_dataarray_003(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v2f_t);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyf[0].x = 0.1;
idataarray->data.xyf[0].y = -0.1;
idataarray->data_bytes = size;
int errd = mossfw_deliver_dataarray(out, idataarray);
TEST_ASSERT(errd == OK);
int used = 0;
mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in, size, &used);




bool normal =
     mossfw_deliverback_dataarray(in,
                                  NULL,
                                  0);



TEST_ASSERT(normal == false);
if (normal) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliverback_dataarray_004(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v2f_t);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyf[0].x = 0.1;
idataarray->data.xyf[0].y = -0.1;
idataarray->data_bytes = size;
int errd = mossfw_deliver_dataarray(out, idataarray);
TEST_ASSERT(errd == OK);
int used = 0;
mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in, size, &used);




bool normal =
     mossfw_deliverback_dataarray(in,
                                  odata,
                                  sizeof(mossfw_data_v2f_t));



TEST_ASSERT(normal == false);
if (normal) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliverback_dataarray_005(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v2f_t);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyf[0].x = 0.1;
idataarray->data.xyf[0].y = -0.1;
idataarray->data_bytes = size;
int errd = mossfw_deliver_dataarray(out, idataarray);
TEST_ASSERT(errd == OK);
int used = 0;
mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in, size, &used);




bool normal =
     mossfw_deliverback_dataarray(NULL,
                                  odata,
                                  sizeof(mossfw_data_v2f_t));



TEST_ASSERT(normal == false);
if (normal) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliverback_dataarray_006(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v2f_t);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyf[0].x = 0.1;
idataarray->data.xyf[0].y = -0.1;
idataarray->data_bytes = size;
int errd = mossfw_deliver_dataarray(out, idataarray);
TEST_ASSERT(errd == OK);
int used = 0;
mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in, size, &used);




bool normal =
     mossfw_deliverback_dataarray(in,
                                  NULL,
                                  sizeof(mossfw_data_v2f_t));



TEST_ASSERT(normal == false);
if (normal) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_deliverback_dataarray_007(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_ARRAY;
int size = sizeof(mossfw_data_v2f_t);
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int waiterr = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(waiterr == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
mossfw_data_t *idataarray =
    mossfw_data_alloc(allocator, size, 1);
idataarray->data.xyf[0].x = 0.1;
idataarray->data.xyf[0].y = -0.1;
idataarray->data_bytes = size;
int errd = mossfw_deliver_dataarray(out, idataarray);
TEST_ASSERT(errd == OK);
int used = 0;
mossfw_data_t *odata =
    mossfw_get_delivereddata_array(in, size, &used);




bool normal =
     mossfw_deliverback_dataarray(NULL,
                                  NULL,
                                  0);



TEST_ASSERT(normal == false);
if (normal) {
    mossfw_data_t *data =
        mossfw_get_delivereddata_array(in, size, NULL);
    TEST_ASSERT(data != NULL);
    mossfw_data_free(data);
}
mossfw_data_free(odata);
mossfw_data_free(idataarray);
int ferr = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(ferr == OK);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_output_ismultibinded_001(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
int outnum = 0;
mossfw_output_t *out = NULL;
if (!(outnum < 0)) {
    out = mossfw_output_create(type);
    TEST_ASSERT(out != NULL);
}
if (0 < outnum) {
    int err = mossfw_bind_inout(out, in0, ~0u);
    TEST_ASSERT(err == OK);
}
if (1 < outnum) {
    int err = mossfw_bind_inout(out, in1, ~0u);
    TEST_ASSERT(err == OK);
}



bool multibinded =
    mossfw_output_ismultibinded(out);



TEST_ASSERT(multibinded == false);
mossfw_output_delete(out);
mossfw_input_delete(in0);
mossfw_input_delete(in1);


}

void test_mossfw_output_ismultibinded_002(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
int outnum = 2;
mossfw_output_t *out = NULL;
if (!(outnum < 0)) {
    out = mossfw_output_create(type);
    TEST_ASSERT(out != NULL);
}
if (0 < outnum) {
    int err = mossfw_bind_inout(out, in0, ~0u);
    TEST_ASSERT(err == OK);
}
if (1 < outnum) {
    int err = mossfw_bind_inout(out, in1, ~0u);
    TEST_ASSERT(err == OK);
}



bool multibinded =
    mossfw_output_ismultibinded(out);



TEST_ASSERT(multibinded == true);
mossfw_output_delete(out);
mossfw_input_delete(in0);
mossfw_input_delete(in1);


}

void test_mossfw_output_ismultibinded_003(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
int outnum = 1;
mossfw_output_t *out = NULL;
if (!(outnum < 0)) {
    out = mossfw_output_create(type);
    TEST_ASSERT(out != NULL);
}
if (0 < outnum) {
    int err = mossfw_bind_inout(out, in0, ~0u);
    TEST_ASSERT(err == OK);
}
if (1 < outnum) {
    int err = mossfw_bind_inout(out, in1, ~0u);
    TEST_ASSERT(err == OK);
}



bool multibinded =
    mossfw_output_ismultibinded(out);



TEST_ASSERT(multibinded == false);
mossfw_output_delete(out);
mossfw_input_delete(in0);
mossfw_input_delete(in1);


}

void test_mossfw_output_ismultibinded_004(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_FLOAT |
    MOSSFW_DATA_TYPEGRP_V1 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 = mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 = mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
int outnum = -1;
mossfw_output_t *out = NULL;
if (!(outnum < 0)) {
    out = mossfw_output_create(type);
    TEST_ASSERT(out != NULL);
}
if (0 < outnum) {
    int err = mossfw_bind_inout(out, in0, ~0u);
    TEST_ASSERT(err == OK);
}
if (1 < outnum) {
    int err = mossfw_bind_inout(out, in1, ~0u);
    TEST_ASSERT(err == OK);
}



bool multibinded =
    mossfw_output_ismultibinded(out);



TEST_ASSERT(multibinded == false);
mossfw_output_delete(out);
mossfw_input_delete(in0);
mossfw_input_delete(in1);


}

void test_is_enoughdata_001(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
int size = sizeof(mossfw_data_v2c_t);
int waitdatasize = size;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int err = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(err == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
in->wait_datasize = waitdatasize == -1 ? waitdatasize : in->wait_datasize;
int errd = mossfw_deliver_data(out, &idatasingle);
TEST_ASSERT(errd == OK);
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;
in->wait_datasize = waitdatasize;



bool enough = is_enoughdata(in);



TEST_ASSERT(enough == true);
in->wait_datasize = 2 * size;
int num = mossfw_get_delivereddata_single(in, &odata);
TEST_ASSERT(num == size);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_is_enoughdata_002(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
int size = sizeof(mossfw_data_v2c_t);
int waitdatasize = size;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int err = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(err == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
in->wait_datasize = waitdatasize == -1 ? waitdatasize : in->wait_datasize;
int errd = mossfw_deliver_data(out, &idatasingle);
TEST_ASSERT(errd == OK);
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;
in->wait_datasize = waitdatasize;



bool enough = is_enoughdata(NULL);



TEST_ASSERT(enough == false);
in->wait_datasize = 2 * size;
int num = mossfw_get_delivereddata_single(in, &odata);
TEST_ASSERT(num == size);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_is_enoughdata_003(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
int size = sizeof(mossfw_data_v2c_t);
int waitdatasize = -1;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int err = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(err == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
in->wait_datasize = waitdatasize == -1 ? waitdatasize : in->wait_datasize;
int errd = mossfw_deliver_data(out, &idatasingle);
TEST_ASSERT(errd == OK);
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;
in->wait_datasize = waitdatasize;



bool enough = is_enoughdata(in);



TEST_ASSERT(enough == false);
in->wait_datasize = 2 * size;
int num = mossfw_get_delivereddata_single(in, &odata);
TEST_ASSERT(num == size);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_is_enoughdata_004(void)
{

uint32_t type =
    MOSSFW_DATA_TYPE_CHAR |
    MOSSFW_DATA_TYPEGRP_V2 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
int size = sizeof(mossfw_data_v2c_t);
int waitdatasize = -1;
mossfw_input_t *in = mossfw_input_create(type, 1);
TEST_ASSERT(in != NULL);
mossfw_output_t *out = mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 0);
TEST_ASSERT(op != NULL);
int err = mossfw_set_waitcondition(in, 2 * size, op);
TEST_ASSERT(err == OK);
int errb = mossfw_bind_inout(out, in, ~0u);
TEST_ASSERT(errb == OK);
mossfw_onedata_t idatasingle;
idatasingle.xyc.x = 9;
idatasingle.xyc.y = 8;
in->wait_datasize = waitdatasize == -1 ? waitdatasize : in->wait_datasize;
int errd = mossfw_deliver_data(out, &idatasingle);
TEST_ASSERT(errd == OK);
mossfw_onedata_t odata;
odata.xyc.x = 0;
odata.xyc.y = 0;
in->wait_datasize = waitdatasize;



bool enough = is_enoughdata(NULL);



TEST_ASSERT(enough == false);
in->wait_datasize = 2 * size;
int num = mossfw_get_delivereddata_single(in, &odata);
TEST_ASSERT(num == size);
mossfw_output_delete(out);
mossfw_callback_op_delete(op);
mossfw_input_delete(in);


}

void test_mossfw_start_callback_op_001(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = async;
op->stack_sz = -1;
op->prio = -1;



int err = mossfw_start_callback_op(op);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_002(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = async;
op->stack_sz = -1;
op->prio = priority;



int err = mossfw_start_callback_op(op);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_003(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = async;
op->stack_sz = stacksize;
op->prio = -1;



int err = mossfw_start_callback_op(op);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_004(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = async;
op->stack_sz = stacksize;
op->prio = priority;



int err = mossfw_start_callback_op(op);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_005(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = async;
op->stack_sz = -1;
op->prio = -1;



int err = mossfw_start_callback_op(NULL);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_006(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = async;
op->stack_sz = -1;
op->prio = priority;



int err = mossfw_start_callback_op(NULL);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_007(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = async;
op->stack_sz = stacksize;
op->prio = -1;



int err = mossfw_start_callback_op(NULL);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_008(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = async;
op->stack_sz = stacksize;
op->prio = priority;



int err = mossfw_start_callback_op(NULL);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_009(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = NULL;
op->stack_sz = -1;
op->prio = -1;



int err = mossfw_start_callback_op(op);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_010(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = NULL;
op->stack_sz = -1;
op->prio = priority;



int err = mossfw_start_callback_op(op);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_011(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = NULL;
op->stack_sz = stacksize;
op->prio = -1;



int err = mossfw_start_callback_op(op);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_012(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = NULL;
op->stack_sz = stacksize;
op->prio = priority;



int err = mossfw_start_callback_op(op);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_start_callback_op_013(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_stop_callback_op(op);
mossfw_async_op_t *async = op->async;
int priority = 1;
pthread_attr_t attr;
int erratr = pthread_attr_init(&attr);
TEST_ASSERT(erratr == 0);
size_t stacksize = 0;
int errstack = pthread_attr_getstacksize(&attr, &stacksize);
TEST_ASSERT(errstack == 0);
op->async = NULL;
op->stack_sz = stacksize;
op->prio = -1;



int err = mossfw_start_callback_op(NULL);



TEST_ASSERT(err == OK);
op->async = async;
mossfw_callback_op_delete(op);
int errdestroy = pthread_attr_destroy(&attr);
TEST_ASSERT(errdestroy == 0);
(void)priority;
(void)stacksize;


}

void test_mossfw_stop_callback_op_001(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_async_op_t *async = op->async;
op->async = async;



mossfw_stop_callback_op(op);



op->async = async;
mossfw_callback_op_delete(op);


}

void test_mossfw_stop_callback_op_002(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_async_op_t *async = op->async;
op->async = async;



mossfw_stop_callback_op(NULL);



op->async = async;
mossfw_callback_op_delete(op);


}

void test_mossfw_stop_callback_op_003(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_async_op_t *async = op->async;
op->async = NULL;



mossfw_stop_callback_op(op);



op->async = async;
mossfw_callback_op_delete(op);


}

void test_mossfw_stop_callback_op_004(void)
{

mossfw_callback_op_t *op = 
    mossfw_callback_op_create(test_app_result1_cb, 0, 1);
TEST_ASSERT(op != NULL);
mossfw_async_op_t *async = op->async;
op->async = NULL;



mossfw_stop_callback_op(NULL);



op->async = async;
mossfw_callback_op_delete(op);


}

void test_mossfw_get_fanout_001(void)
{

int num = 1;
uint32_t type =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_output_t *output = out;
int err0 = 
    mossfw_bind_inout(out, in0, 0);
TEST_ASSERT(err0 == OK);
if (1 < num) {
    int err1 = 
        mossfw_bind_inout(out, in1, 0);
    TEST_ASSERT(err1 == OK);
}



int ret = mossfw_get_fanout(output);



TEST_ASSERT(ret == 1);
mossfw_output_delete(out);
mossfw_input_delete(in0);
mossfw_input_delete(in1);


}

void test_mossfw_get_fanout_002(void)
{

int num = 2;
uint32_t type =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_output_t *output = out;
int err0 = 
    mossfw_bind_inout(out, in0, 0);
TEST_ASSERT(err0 == OK);
if (1 < num) {
    int err1 = 
        mossfw_bind_inout(out, in1, 0);
    TEST_ASSERT(err1 == OK);
}



int ret = mossfw_get_fanout(output);



TEST_ASSERT(ret == 2);
mossfw_output_delete(out);
mossfw_input_delete(in0);
mossfw_input_delete(in1);


}

void test_mossfw_get_fanout_003(void)
{

int num = 1;
uint32_t type =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_output_t *output = NULL;
int err0 = 
    mossfw_bind_inout(out, in0, 0);
TEST_ASSERT(err0 == OK);
if (1 < num) {
    int err1 = 
        mossfw_bind_inout(out, in1, 0);
    TEST_ASSERT(err1 == OK);
}



int ret = mossfw_get_fanout(output);



TEST_ASSERT(ret == 0);
mossfw_output_delete(out);
mossfw_input_delete(in0);
mossfw_input_delete(in1);


}

void test_mossfw_get_fanout_004(void)
{

int num = 2;
uint32_t type =
    MOSSFW_DATA_TYPE_INT32 |
    MOSSFW_DATA_TYPEGRP_V3 | 
    MOSSFW_DATA_TYPENAME_ACCEL | 
    MOSSFW_DATA_TYPEARRAY_SINGLE;
mossfw_input_t *in0 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in0 != NULL);
mossfw_input_t *in1 =
    mossfw_input_create(type, 1);
TEST_ASSERT(in1 != NULL);
mossfw_output_t *out =
    mossfw_output_create(type);
TEST_ASSERT(out != NULL);
mossfw_output_t *output = NULL;
int err0 = 
    mossfw_bind_inout(out, in0, 0);
TEST_ASSERT(err0 == OK);
if (1 < num) {
    int err1 = 
        mossfw_bind_inout(out, in1, 0);
    TEST_ASSERT(err1 == OK);
}



int ret = mossfw_get_fanout(output);



TEST_ASSERT(ret == 0);
mossfw_output_delete(out);
mossfw_input_delete(in0);
mossfw_input_delete(in1);


}

