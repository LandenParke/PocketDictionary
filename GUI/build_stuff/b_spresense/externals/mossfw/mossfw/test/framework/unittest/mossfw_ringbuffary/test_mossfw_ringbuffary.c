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
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>

#include "mossfw/mossfw_debug.h"
#include "mossfw/mossfw_data.h"
#include "mossfw/mossfw_memoryallocator.h"
#include "mossfw/mossfw_ringbuffary.h"
#include "unity.h"
#include "mossfw_ringbuffary.c"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define POOL1_BLKLEN  (16)
#define POOL1_BLKNUM  (64)

/****************************************************************************
 * Private Deta Types
 ****************************************************************************/

/****************************************************************************
 * Private Deta
 ****************************************************************************/

static mossfw_allocator_t *allocator;
static mossfw_ringbuffarray_t *ringbuff;
static char msg[256];
static mossfw_ringbuffarray_t *ringbuff_dummy;
static mossfw_data_t *sensdat2;
extern int err_ringbuffarray_malloc_pettern;
extern int err_ringbuffarray_wait_pettern;
extern mossfw_ringbuffarray_t *err_ringbuffarray_buff;

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: setUp
 ****************************************************************************/

void setUp(void)
{
  mossfw_debug_init();
  allocator = mossfw_fixedmem_create(
                      sizeof(mossfw_data_v3i32_t) * POOL1_BLKLEN,
                      POOL1_BLKNUM);
  ringbuff = mossfw_ringbuffarray_create(POOL1_BLKNUM);
}

/****************************************************************************
 * name: tearDown
 ****************************************************************************/

void tearDown(void)
{
  mossfw_fixedmem_delete(allocator);
  mossfw_ringbuffarray_delete(ringbuff);
}

/****************************************************************************
 * name: test_DefautTestAndThroughOne
 ****************************************************************************/

void test_DefautTestAndThroughOne(void)
{
  mossfw_data_t *sensdat1;
  mossfw_data_t *sensdat2;

  TEST_ASSERT_NOT_EQUAL(NULL, ringbuff->top);
  TEST_ASSERT_EQUAL(NULL, ringbuff->stored);
  TEST_ASSERT_EQUAL(POOL1_BLKNUM, ringbuff->total_depth);
  TEST_ASSERT_EQUAL(0, ringbuff->stored_num);
  TEST_ASSERT_EQUAL(0, ringbuff->stored_bytes);

  TEST_ASSERT_EQUAL(true, mossfw_ringbuffarray_isempty(ringbuff));
  TEST_ASSERT_EQUAL(false, mossfw_ringbuffarray_isfull(ringbuff));

  /* Simple allocate sensor data block */

  sensdat1 = mossfw_data_alloc(allocator,
                      sizeof(mossfw_data_v3i32_t) * POOL1_BLKLEN, true);
  TEST_ASSERT_EQUAL(0, sensdat1->data_bytes);

  /* Set fake data */

  sensdat1->data_bytes = sizeof(mossfw_data_v3i32_t) * POOL1_BLKLEN;

  mossfw_ringbuffarray_setdata(ringbuff, sensdat1, true);

  /* Noe reference count of the data is increased. */

  TEST_ASSERT_EQUAL(2, sensdat1->refcnt);

  /* Check ringbuffer status */

  TEST_ASSERT_EQUAL(1, ringbuff->stored_num);
  TEST_ASSERT_EQUAL((sizeof(mossfw_data_v3i32_t) * POOL1_BLKLEN),
                    ringbuff->stored_bytes);

  TEST_ASSERT_EQUAL(false, mossfw_ringbuffarray_isempty(ringbuff));
  TEST_ASSERT_EQUAL(false, mossfw_ringbuffarray_isfull(ringbuff));
  TEST_ASSERT_EQUAL(1, mossfw_ringbuffarray_storednum(ringbuff));
  TEST_ASSERT_EQUAL((sizeof(mossfw_data_v3i32_t) * POOL1_BLKLEN),
                    mossfw_ringbuffarray_storedbytes(ringbuff));

  /* Free the data makes decrease reference counter */

  mossfw_data_free(sensdat1);
  TEST_ASSERT_EQUAL(1, sensdat1->refcnt);

  /* Get the data from ring buffer */

  sensdat2 = mossfw_ringbuffarray_getdata(ringbuff, NULL, true);
  TEST_ASSERT_EQUAL(1, sensdat1->refcnt);

  TEST_ASSERT_EQUAL(0, ringbuff->stored_num);
  TEST_ASSERT_EQUAL(0, ringbuff->stored_bytes);

  TEST_ASSERT_EQUAL(true, mossfw_ringbuffarray_isempty(ringbuff));
  TEST_ASSERT_EQUAL(false, mossfw_ringbuffarray_isfull(ringbuff));
  TEST_ASSERT_EQUAL(0, mossfw_ringbuffarray_storednum(ringbuff));
  TEST_ASSERT_EQUAL(0, mossfw_ringbuffarray_storedbytes(ringbuff));

  mossfw_data_free(sensdat2);
}

/****************************************************************************
 * name: test_FIFOBehavior
 ****************************************************************************/

void test_FIFOBehavior(void)
{
  int i;
  int total_data;
  int total_num;
  mossfw_data_t *sensdat;

  sensdat = mossfw_data_alloc(allocator,
                     sizeof(mossfw_data_v3i32_t) * POOL1_BLKLEN, true);

  total_data = 0;
  for (i = 0; sensdat; i++)
    {
      sensdat->data_bytes = 100 + i;
      sensdat->data.xyzi32[0].x = i;
      sensdat->data.xyzi32[0].y = i + 1;
      sensdat->data.xyzi32[0].z = i + 2;
      total_data += sensdat->data_bytes;

      mossfw_ringbuffarray_setdata(ringbuff, sensdat, true);
      mossfw_data_free(sensdat);
      sprintf(msg, "IDX=%d", i);
      TEST_ASSERT_EQUAL_MESSAGE(total_data, mossfw_ringbuffarray_storedbytes(ringbuff), msg);

      sensdat = mossfw_data_alloc(allocator,
                        sizeof(mossfw_data_v3i32_t) * POOL1_BLKLEN, true);
    }

  total_num = i;
  TEST_ASSERT_EQUAL(total_num, mossfw_ringbuffarray_storednum(ringbuff));
  TEST_ASSERT_EQUAL(total_data, mossfw_ringbuffarray_storedbytes(ringbuff));
  TEST_ASSERT_EQUAL(false, mossfw_ringbuffarray_isempty(ringbuff));
  TEST_ASSERT_EQUAL(true, mossfw_ringbuffarray_isfull(ringbuff));

  sensdat = mossfw_ringbuffarray_getdata(ringbuff, NULL, true);

  for (i = 0; sensdat; i++)
    {
      TEST_ASSERT_EQUAL(100 + i, sensdat->data_bytes);
      TEST_ASSERT_EQUAL(i + 0, sensdat->data.xyzi32[0].x);
      TEST_ASSERT_EQUAL(i + 1, sensdat->data.xyzi32[0].y);
      TEST_ASSERT_EQUAL(i + 2, sensdat->data.xyzi32[0].z);
      TEST_ASSERT_EQUAL(1, sensdat->refcnt);

      total_num--;
      total_data -= sensdat->data_bytes;

      TEST_ASSERT_EQUAL(total_num, mossfw_ringbuffarray_storednum(ringbuff));
      TEST_ASSERT_EQUAL(total_data, mossfw_ringbuffarray_storedbytes(ringbuff));

      mossfw_data_free(sensdat);

      TEST_ASSERT_EQUAL(false, mossfw_ringbuffarray_isfull(ringbuff));
      if (total_data)
        {
          TEST_ASSERT_EQUAL(false, mossfw_ringbuffarray_isempty(ringbuff));
        }
      else
        {
          TEST_ASSERT_EQUAL(true, mossfw_ringbuffarray_isempty(ringbuff));
        }

      sensdat = mossfw_ringbuffarray_getdata(ringbuff, NULL, true);
    }
}

void test_BackToRingbuffer(void)
{
  int used;
  mossfw_data_t *sensdat1;
  mossfw_data_t *sensdat2;

  sensdat1 = mossfw_data_alloc(allocator, sizeof(mossfw_data_v3i32_t) * POOL1_BLKLEN, true);
  sensdat1->data_bytes = 100;
  mossfw_ringbuffarray_setdata(ringbuff, sensdat1, true);
  mossfw_data_free(sensdat1);
  TEST_ASSERT_EQUAL(1, mossfw_ringbuffarray_storednum(ringbuff));
  TEST_ASSERT_EQUAL(100, mossfw_ringbuffarray_storedbytes(ringbuff));

  sensdat2 = mossfw_data_alloc(allocator, sizeof(mossfw_data_v3i32_t) * POOL1_BLKLEN, true);
  sensdat2->data_bytes = 100;
  mossfw_ringbuffarray_setdata(ringbuff, sensdat2, true);
  mossfw_data_free(sensdat2);
  TEST_ASSERT_EQUAL(2, mossfw_ringbuffarray_storednum(ringbuff));
  TEST_ASSERT_EQUAL(200, mossfw_ringbuffarray_storedbytes(ringbuff));

  sensdat2 = mossfw_ringbuffarray_getdata(ringbuff, &used, true);
  TEST_ASSERT_EQUAL(sensdat1, sensdat2);
  TEST_ASSERT_EQUAL(0, used);
  TEST_ASSERT_EQUAL(1, mossfw_ringbuffarray_storednum(ringbuff));
  TEST_ASSERT_EQUAL(100, mossfw_ringbuffarray_storedbytes(ringbuff));

  TEST_ASSERT_EQUAL(true, mossfw_ringbuffarray_backdatarest(ringbuff, sensdat2, 10, true));
  mossfw_data_free(sensdat2);
  TEST_ASSERT_EQUAL(2, mossfw_ringbuffarray_storednum(ringbuff));
  TEST_ASSERT_EQUAL(190, mossfw_ringbuffarray_storedbytes(ringbuff));

  sensdat2 = mossfw_ringbuffarray_getdata(ringbuff, &used, true);
  TEST_ASSERT_EQUAL(sensdat1, sensdat2);
  TEST_ASSERT_EQUAL(10, used);
  mossfw_data_free(sensdat2);
  TEST_ASSERT_EQUAL(1, mossfw_ringbuffarray_storednum(ringbuff));
  TEST_ASSERT_EQUAL(100, mossfw_ringbuffarray_storedbytes(ringbuff));

  sensdat2 = mossfw_ringbuffarray_getdata(ringbuff, &used, true);
  TEST_ASSERT_NOT_EQUAL(sensdat1, sensdat2);
  TEST_ASSERT_EQUAL(0, used);
  mossfw_data_free(sensdat2);
  TEST_ASSERT_EQUAL(0, mossfw_ringbuffarray_storednum(ringbuff));
  TEST_ASSERT_EQUAL(0, mossfw_ringbuffarray_storedbytes(ringbuff));
}

void test_ErrorCreate(void)
{
  err_ringbuffarray_malloc_pettern = 1;
  ringbuff_dummy = mossfw_ringbuffarray_create(POOL1_BLKNUM);
  err_ringbuffarray_malloc_pettern = 2;
  ringbuff_dummy = mossfw_ringbuffarray_create(POOL1_BLKNUM);
  err_ringbuffarray_malloc_pettern = 0;
  ringbuff_dummy = mossfw_ringbuffarray_create(POOL1_BLKNUM);
}

void test_ErrorSetdata(void)
{
  sensdat2 = mossfw_data_alloc(allocator, sizeof(mossfw_data_v3i32_t) * POOL1_BLKLEN, true);
  sensdat2->data_bytes = 100;

  mossfw_ringbuffarray_setdata(NULL, sensdat2, true);
  ringbuff_dummy->total_depth = 0;
  ringbuff_dummy->stored_num = 0;
  mossfw_ringbuffarray_setdata(ringbuff_dummy, sensdat2, true);

  err_ringbuffarray_wait_pettern = 1;
  ringbuff_dummy->total_depth = POOL1_BLKNUM;
  ringbuff_dummy->stored_num = POOL1_BLKNUM;
  err_ringbuffarray_buff = ringbuff_dummy;
  mossfw_ringbuffarray_setdata(ringbuff_dummy, sensdat2, false);
}

void test_ErrorGetdata(void)
{
  int used;

  mossfw_ringbuffarray_getdata(NULL, &used, true);
  err_ringbuffarray_wait_pettern = 2;
  ringbuff_dummy->stored = NULL;
  mossfw_ringbuffarray_getdata(ringbuff_dummy, &used, false);

  err_ringbuffarray_wait_pettern = 0;
}

void test_ErrorBackdatarest(void)
{
  mossfw_ringbuffarray_backdatarest(NULL, sensdat2, 10, true);

  ringbuff_dummy->usedidx = 0;
  sensdat2->data_bytes = 1;
  mossfw_ringbuffarray_backdatarest(ringbuff_dummy, sensdat2, 10, true);

  sensdat2->data_bytes = 11;
  ringbuff_dummy->usedidx = 1;
  mossfw_ringbuffarray_backdatarest(ringbuff_dummy, sensdat2, 10, true);

  ringbuff_dummy->total_depth = POOL1_BLKNUM;
  ringbuff_dummy->stored_num = POOL1_BLKNUM;
  ringbuff_dummy->usedidx = 0;
  mossfw_ringbuffarray_backdatarest(ringbuff_dummy, sensdat2, 9, true);

  err_ringbuffarray_wait_pettern = 1;
  ringbuff_dummy->stored = NULL;
  mossfw_ringbuffarray_backdatarest(ringbuff_dummy, sensdat2, 8, false);

  err_ringbuffarray_wait_pettern = 0;
}

void test_ErrorIsempty(void)
{
  TEST_ASSERT_EQUAL(true, mossfw_ringbuffarray_isempty(NULL));
}

void test_ErrorIsfull(void)
{
  TEST_ASSERT_EQUAL(false, mossfw_ringbuffarray_isfull(NULL));
}

void test_ErrorStorednum(void)
{
  TEST_ASSERT_EQUAL(0, mossfw_ringbuffarray_storednum(NULL));
}

void test_ErrorStoredbytes(void)
{
  TEST_ASSERT_EQUAL(0, mossfw_ringbuffarray_storedbytes(NULL));
}

void test_ErrorDelete(void)
{
  mossfw_ringbuffarray_delete(NULL);

  ringbuff = (mossfw_ringbuffarray_t *)malloc(sizeof(mossfw_ringbuffarray_t));
  ringbuff_dummy->stored = (mossfw_data_container_t *)ringbuff;
  ringbuff_dummy->stored->next = NULL;
  ringbuff_dummy->stored->data = NULL;
  mossfw_ringbuffarray_delete(ringbuff_dummy);
}

void test_find_free(void)
{
  int used = 0;
  (void)used;
  int size = sizeof(mossfw_data_v3i32_t);
  mossfw_allocator_t *allocator = mossfw_fixedmem_create(size, 1);
  TEST_ASSERT(allocator != NULL);
  mossfw_ringbuffarray_t *buf = mossfw_ringbuffarray_create(1);
  TEST_ASSERT(buf != NULL);
  mossfw_data_t *data0 = mossfw_data_alloc(allocator, size, true);
  TEST_ASSERT(data0 != NULL);
  data0->data_bytes = size;
  bool setnormal = mossfw_ringbuffarray_setdata(buf, data0, true);
  TEST_ASSERT(setnormal);

  mossfw_data_container_t *ctr = find_free(buf->top, buf->total_depth);
  TEST_ASSERT(ctr == NULL);

  mossfw_data_t *data1 = mossfw_ringbuffarray_getdata(buf, &used, true);
  TEST_ASSERT(data1 != NULL);
  mossfw_data_free(data1);
  mossfw_data_free(data0);
  mossfw_ringbuffarray_delete(buf);
  int delerr = mossfw_fixedmem_delete(allocator);
  TEST_ASSERT(delerr == OK);
}


void test_mossfw_ringbuffarray_getdata_001(void)
{

bool stop = true;
bool nonblock = true;
int block_sz = sizeof(int32_t);
int block_num = 1;
const int expected_value = 9;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk != NULL);
blk->data.v1i32[0].x = expected_value;
blk->data_bytes = block_sz;
bool errset = mossfw_ringbuffarray_setdata(buff, blk, 1);
TEST_ASSERT(errset == true);
mossfw_ringbuffarray_setstop(buff, stop);
int used;



mossfw_data_t *ret = mossfw_ringbuffarray_getdata(buff, &used, nonblock);



TEST_ASSERT(ret == NULL);
if (ret != NULL) {
    TEST_ASSERT(ret->data.v1i32[0].x == expected_value);
    mossfw_data_free(ret);
}
mossfw_data_free(blk);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

void test_mossfw_ringbuffarray_getdata_002(void)
{

bool stop = true;
bool nonblock = false;
int block_sz = sizeof(int32_t);
int block_num = 1;
const int expected_value = 9;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk != NULL);
blk->data.v1i32[0].x = expected_value;
blk->data_bytes = block_sz;
bool errset = mossfw_ringbuffarray_setdata(buff, blk, 1);
TEST_ASSERT(errset == true);
mossfw_ringbuffarray_setstop(buff, stop);
int used;



mossfw_data_t *ret = mossfw_ringbuffarray_getdata(buff, &used, nonblock);



TEST_ASSERT(ret == NULL);
if (ret != NULL) {
    TEST_ASSERT(ret->data.v1i32[0].x == expected_value);
    mossfw_data_free(ret);
}
mossfw_data_free(blk);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

void test_mossfw_ringbuffarray_getdata_003(void)
{

bool stop = false;
bool nonblock = true;
int block_sz = sizeof(int32_t);
int block_num = 1;
const int expected_value = 9;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk != NULL);
blk->data.v1i32[0].x = expected_value;
blk->data_bytes = block_sz;
bool errset = mossfw_ringbuffarray_setdata(buff, blk, 1);
TEST_ASSERT(errset == true);
mossfw_ringbuffarray_setstop(buff, stop);
int used;



mossfw_data_t *ret = mossfw_ringbuffarray_getdata(buff, &used, nonblock);



TEST_ASSERT(ret != NULL);
if (ret != NULL) {
    TEST_ASSERT(ret->data.v1i32[0].x == expected_value);
    mossfw_data_free(ret);
}
mossfw_data_free(blk);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

void test_mossfw_ringbuffarray_getdata_004(void)
{

bool stop = false;
bool nonblock = false;
int block_sz = sizeof(int32_t);
int block_num = 1;
const int expected_value = 9;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk != NULL);
blk->data.v1i32[0].x = expected_value;
blk->data_bytes = block_sz;
bool errset = mossfw_ringbuffarray_setdata(buff, blk, 1);
TEST_ASSERT(errset == true);
mossfw_ringbuffarray_setstop(buff, stop);
int used;



mossfw_data_t *ret = mossfw_ringbuffarray_getdata(buff, &used, nonblock);



TEST_ASSERT(ret != NULL);
if (ret != NULL) {
    TEST_ASSERT(ret->data.v1i32[0].x == expected_value);
    mossfw_data_free(ret);
}
mossfw_data_free(blk);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

void test_mossfw_ringbuff_setdata_001(void)
{

bool stop = true;
bool nonblock = true;
int block_sz = sizeof(int32_t);
int block_num = 1;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_ringbuffarray_setstop(buff, stop);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk != NULL);



bool err = mossfw_ringbuffarray_setdata(buff, blk, nonblock);



TEST_ASSERT(err == false);
mossfw_data_free(blk);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

void test_mossfw_ringbuff_setdata_002(void)
{

bool stop = true;
bool nonblock = false;
int block_sz = sizeof(int32_t);
int block_num = 1;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_ringbuffarray_setstop(buff, stop);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk != NULL);



bool err = mossfw_ringbuffarray_setdata(buff, blk, nonblock);



TEST_ASSERT(err == false);
mossfw_data_free(blk);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

void test_mossfw_ringbuff_setdata_003(void)
{

bool stop = false;
bool nonblock = true;
int block_sz = sizeof(int32_t);
int block_num = 1;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_ringbuffarray_setstop(buff, stop);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk != NULL);



bool err = mossfw_ringbuffarray_setdata(buff, blk, nonblock);



TEST_ASSERT(err == true);
mossfw_data_free(blk);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

void test_mossfw_ringbuff_setdata_004(void)
{

bool stop = false;
bool nonblock = false;
int block_sz = sizeof(int32_t);
int block_num = 1;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_ringbuffarray_setstop(buff, stop);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk != NULL);



bool err = mossfw_ringbuffarray_setdata(buff, blk, nonblock);



TEST_ASSERT(err == true);
mossfw_data_free(blk);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

void test_mossfw_ringbuffarray_backdatare_001(void)
{

bool stop = true;
bool nonblock = true;
int block_sz = 2 * sizeof(int32_t);
int block_num = 2;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk0 = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk0 != NULL);
blk0->data.v1i32[0].x = 6;
blk0->data.v1i32[1].x = 7;
blk0->data_bytes = block_sz;
bool err0 = mossfw_ringbuffarray_setdata(buff, blk0, true);
TEST_ASSERT(err0 == true);
mossfw_data_t *blk1 = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk1 != NULL);
blk1->data.v1i32[0].x = 8;
blk1->data.v1i32[1].x = 9;
blk1->data_bytes = block_sz;
bool err1 = mossfw_ringbuffarray_setdata(buff, blk1, true);
TEST_ASSERT(err1 == true);
int used = 0;
mossfw_data_t *data = mossfw_ringbuffarray_getdata(buff, &used, true);
TEST_ASSERT(data != NULL);
TEST_ASSERT(used == 0);
TEST_ASSERT(data->data.v1i32[0].x == 6);
used = 1;
mossfw_ringbuffarray_setstop(buff, stop);



bool err = mossfw_ringbuffarray_backdatarest(buff, data, used, nonblock);



TEST_ASSERT(err == false);
mossfw_data_free(data);
data = mossfw_ringbuffarray_getdata(buff, &used, true);
if (stop) {
    TEST_ASSERT(data == NULL);
} else {
    TEST_ASSERT(data != NULL);
    TEST_ASSERT(used == 1);
    TEST_ASSERT(data->data.v1i32[1].x == 7);
}
mossfw_data_free(data);
mossfw_data_free(blk0);
mossfw_data_free(blk1);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

void test_mossfw_ringbuffarray_backdatare_002(void)
{

bool stop = true;
bool nonblock = false;
int block_sz = 2 * sizeof(int32_t);
int block_num = 2;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk0 = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk0 != NULL);
blk0->data.v1i32[0].x = 6;
blk0->data.v1i32[1].x = 7;
blk0->data_bytes = block_sz;
bool err0 = mossfw_ringbuffarray_setdata(buff, blk0, true);
TEST_ASSERT(err0 == true);
mossfw_data_t *blk1 = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk1 != NULL);
blk1->data.v1i32[0].x = 8;
blk1->data.v1i32[1].x = 9;
blk1->data_bytes = block_sz;
bool err1 = mossfw_ringbuffarray_setdata(buff, blk1, true);
TEST_ASSERT(err1 == true);
int used = 0;
mossfw_data_t *data = mossfw_ringbuffarray_getdata(buff, &used, true);
TEST_ASSERT(data != NULL);
TEST_ASSERT(used == 0);
TEST_ASSERT(data->data.v1i32[0].x == 6);
used = 1;
mossfw_ringbuffarray_setstop(buff, stop);



bool err = mossfw_ringbuffarray_backdatarest(buff, data, used, nonblock);



TEST_ASSERT(err == false);
mossfw_data_free(data);
data = mossfw_ringbuffarray_getdata(buff, &used, true);
if (stop) {
    TEST_ASSERT(data == NULL);
} else {
    TEST_ASSERT(data != NULL);
    TEST_ASSERT(used == 1);
    TEST_ASSERT(data->data.v1i32[1].x == 7);
}
mossfw_data_free(data);
mossfw_data_free(blk0);
mossfw_data_free(blk1);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

void test_mossfw_ringbuffarray_backdatare_003(void)
{

bool stop = false;
bool nonblock = true;
int block_sz = 2 * sizeof(int32_t);
int block_num = 2;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk0 = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk0 != NULL);
blk0->data.v1i32[0].x = 6;
blk0->data.v1i32[1].x = 7;
blk0->data_bytes = block_sz;
bool err0 = mossfw_ringbuffarray_setdata(buff, blk0, true);
TEST_ASSERT(err0 == true);
mossfw_data_t *blk1 = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk1 != NULL);
blk1->data.v1i32[0].x = 8;
blk1->data.v1i32[1].x = 9;
blk1->data_bytes = block_sz;
bool err1 = mossfw_ringbuffarray_setdata(buff, blk1, true);
TEST_ASSERT(err1 == true);
int used = 0;
mossfw_data_t *data = mossfw_ringbuffarray_getdata(buff, &used, true);
TEST_ASSERT(data != NULL);
TEST_ASSERT(used == 0);
TEST_ASSERT(data->data.v1i32[0].x == 6);
used = 1;
mossfw_ringbuffarray_setstop(buff, stop);



bool err = mossfw_ringbuffarray_backdatarest(buff, data, used, nonblock);



TEST_ASSERT(err == true);
mossfw_data_free(data);
data = mossfw_ringbuffarray_getdata(buff, &used, true);
if (stop) {
    TEST_ASSERT(data == NULL);
} else {
    TEST_ASSERT(data != NULL);
    TEST_ASSERT(used == 1);
    TEST_ASSERT(data->data.v1i32[1].x == 7);
}
mossfw_data_free(data);
mossfw_data_free(blk0);
mossfw_data_free(blk1);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

void test_mossfw_ringbuffarray_backdatare_004(void)
{

bool stop = false;
bool nonblock = false;
int block_sz = 2 * sizeof(int32_t);
int block_num = 2;
mossfw_ringbuffarray_t *buff =
    mossfw_ringbuffarray_create(block_num);
mossfw_allocator_t *allocator = mossfw_fixedmem_create(block_sz, block_num);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *blk0 = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk0 != NULL);
blk0->data.v1i32[0].x = 6;
blk0->data.v1i32[1].x = 7;
blk0->data_bytes = block_sz;
bool err0 = mossfw_ringbuffarray_setdata(buff, blk0, true);
TEST_ASSERT(err0 == true);
mossfw_data_t *blk1 = mossfw_data_alloc(allocator, block_sz, true);
TEST_ASSERT(blk1 != NULL);
blk1->data.v1i32[0].x = 8;
blk1->data.v1i32[1].x = 9;
blk1->data_bytes = block_sz;
bool err1 = mossfw_ringbuffarray_setdata(buff, blk1, true);
TEST_ASSERT(err1 == true);
int used = 0;
mossfw_data_t *data = mossfw_ringbuffarray_getdata(buff, &used, true);
TEST_ASSERT(data != NULL);
TEST_ASSERT(used == 0);
TEST_ASSERT(data->data.v1i32[0].x == 6);
used = 1;
mossfw_ringbuffarray_setstop(buff, stop);



bool err = mossfw_ringbuffarray_backdatarest(buff, data, used, nonblock);



TEST_ASSERT(err == true);
mossfw_data_free(data);
data = mossfw_ringbuffarray_getdata(buff, &used, true);
if (stop) {
    TEST_ASSERT(data == NULL);
} else {
    TEST_ASSERT(data != NULL);
    TEST_ASSERT(used == 1);
    TEST_ASSERT(data->data.v1i32[1].x == 7);
}
mossfw_data_free(data);
mossfw_data_free(blk0);
mossfw_data_free(blk1);
mossfw_ringbuffarray_delete(buff);
mossfw_fixedmem_delete(allocator);


}

