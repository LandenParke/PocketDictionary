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

#include "mossfw/mossfw_data.h"
#include "mossfw/mossfw_memoryallocator.h"
#include "unity.h"
#include "malloctest.h"
#include "mossfw_memoryallocator.c"

#define POOL1_BLKLEN  (8)
#define POOL2_BLKLEN  (16)
#define POOL1_BLKNUM  (32)
#define POOL2_BLKNUM  (64)

#define THREAD_NUM  (16)

/****************************************************************************
 * Private Deta Types
 ****************************************************************************/

/****************************************************************************
 * Private Deta
 ****************************************************************************/

static mossfw_allocator_t *fixedmempool1;
static mossfw_allocator_t *fixedmempool2;
static char msg[128];
static bool need_delete = true;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: access_worker
 ****************************************************************************/

static void *access_worker(void *arg)
{
  mossfw_data_t *sensdat = (mossfw_data_t *)arg;
  int sleep_sec;

  sleep_sec = rand() % 5;
  /* printf("Sleep in %d\n", sleep_sec); */
  sleep(sleep_sec);

  mossfw_data_free(sensdat);
  pthread_exit(0);

  return NULL;
}

/****************************************************************************
 * name: max_allocation_and_free
 ****************************************************************************/

static void max_allocation_and_free(void)
{
  int i;
  mossfw_data_t *sensdat1[POOL1_BLKNUM];
  mossfw_data_t *sensdat2[POOL2_BLKNUM];

  for (i = 0; i < POOL1_BLKNUM; i++)
    {
      sensdat1[i] = mossfw_data_alloc(fixedmempool1,
                      sizeof(mossfw_data_v3f_t) * POOL1_BLKLEN, true);
      sprintf(msg, "Pool1 alloc idx = %d ", i);
      TEST_ASSERT_NOT_EQUAL_MESSAGE(NULL, sensdat1[i], msg);
    }

  TEST_ASSERT_EQUAL_MESSAGE(NULL,
                mossfw_data_alloc(fixedmempool1,
                      sizeof(mossfw_data_v3f_t) * POOL1_BLKLEN, true),
                "Pool1 should empty.");

  for (i = 0; i < POOL2_BLKNUM; i++)
    {
      sensdat2[i] = mossfw_data_alloc(fixedmempool2,
                      sizeof(mossfw_data_v3i32_t) * POOL2_BLKLEN, true);
      sprintf(msg, "Pool2 alloc idx = %d ", i);
      TEST_ASSERT_NOT_EQUAL_MESSAGE(NULL, sensdat2[i], msg);
    }

  TEST_ASSERT_EQUAL_MESSAGE(NULL,
                mossfw_data_alloc(fixedmempool2,
                      sizeof(mossfw_data_v3f_t) * POOL2_BLKLEN, true),
                "Pool2 should empty.");

  for (i = 0; i < POOL1_BLKNUM; i++)
    {
      mossfw_data_free(sensdat1[i]);
    }

  for (i = 0; i < POOL2_BLKNUM; i++)
    {
      mossfw_data_free(sensdat2[i]);
    }
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * name: setUp
 ****************************************************************************/

void setUp(void)
{
  need_delete = true;

  fixedmempool1 = mossfw_fixedmem_create(
                      sizeof(mossfw_data_v3f_t) * POOL1_BLKLEN,
                      POOL1_BLKNUM);

  fixedmempool2 = mossfw_fixedmem_create(
                      sizeof(mossfw_data_v3i32_t) * POOL2_BLKLEN,
                      POOL2_BLKNUM);
}

/****************************************************************************
 * name: tearDown
 ****************************************************************************/

void tearDown(void)
{
  if (need_delete)
    {
      mossfw_fixedmem_delete(fixedmempool1);
      mossfw_fixedmem_delete(fixedmempool2);
    }
}

/****************************************************************************
 * name: test_SimpleAllocate
 ****************************************************************************/

void test_SimpleAllocate(void)
{
  mossfw_data_t *sensdat;

  /* Simple allocate sensor data block */

  sensdat = mossfw_data_alloc(fixedmempool1,
                      sizeof(mossfw_data_v3f_t) * POOL1_BLKLEN, true);
  TEST_ASSERT_NOT_EQUAL(NULL, sensdat);
  TEST_ASSERT_EQUAL(1, sensdat->refcnt);
  TEST_ASSERT_EQUAL(0, sensdat->data_bytes);
  mossfw_data_free(sensdat);

  sensdat = mossfw_data_alloc(fixedmempool2,
                      sizeof(mossfw_data_v3i32_t) * POOL2_BLKLEN, true);
  TEST_ASSERT_NOT_EQUAL(NULL, sensdat);
  TEST_ASSERT_EQUAL(1, sensdat->refcnt);
  TEST_ASSERT_EQUAL(0, sensdat->data_bytes);
  mossfw_data_free(sensdat);

  /* Simple allocate sensor data block with wrang size */

  sensdat = mossfw_data_alloc(fixedmempool1,
                      sizeof(mossfw_data_v3f_t) * POOL1_BLKLEN - 1, true);
  TEST_ASSERT_EQUAL(NULL, sensdat);
}

/****************************************************************************
 * name: test_MaxAllocation
 ****************************************************************************/

void test_MaxAllocation(void)
{
  TEST_MESSAGE("First max allocation");
  max_allocation_and_free();

  TEST_MESSAGE("Second max allocation");
  max_allocation_and_free();

  need_delete = false;
  TEST_ASSERT_EQUAL(OK, mossfw_fixedmem_delete(fixedmempool1));
  TEST_ASSERT_EQUAL(OK, mossfw_fixedmem_delete(fixedmempool2));
}

/****************************************************************************
 * name: test_RefferFromMultiThreads
 ****************************************************************************/

void test_ReferFromMultiThreads(void)
{
  pthread_t threads[THREAD_NUM];
  int i;
  mossfw_data_t *sensdat;

  sensdat = mossfw_data_alloc(fixedmempool2,
                      sizeof(mossfw_data_v3i32_t) * POOL2_BLKLEN, true);

  sensdat->data.xyzi32[0].x = 0;
  sensdat->data.xyzi32[0].y = 1;
  sensdat->data.xyzi32[0].z = 2;

  for (i = 0; i <THREAD_NUM; i++)
    {
      mossfw_data_refer(sensdat);
    }

  TEST_ASSERT_EQUAL(THREAD_NUM + 1, sensdat->refcnt);

  for (i = 0; i <THREAD_NUM; i++)
    {
      pthread_create(&threads[i], NULL, access_worker, (void *)sensdat);
    }

  printf("Waiting for finishing worker threads in 5 sec.\n");
  for (i = 0; i <THREAD_NUM; i++)
    {
      pthread_join(threads[i], NULL);
    }

  TEST_ASSERT_EQUAL(1, sensdat->refcnt);
  mossfw_data_free(sensdat);
}

void test_TypeMacroTest(void)
{
  int type = -1;

  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPE_MASK, MOSSFW_DATA_TYPE(type));
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPEGRP_MASK, MOSSFW_DATA_TYPEGRP(type));
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPENAME_MASK, MOSSFW_DATA_TYPENAME(type));
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPEARRAY_MASK, MOSSFW_DATA_TYPEARRAY(type));

  type = MOSSFW_DATA_TYPE_INT32;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPE_INT32, MOSSFW_DATA_TYPE(type));
  type = MOSSFW_DATA_TYPE_SHORT;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPE_SHORT, MOSSFW_DATA_TYPE(type));
  type = MOSSFW_DATA_TYPE_CHAR;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPE_CHAR, MOSSFW_DATA_TYPE(type));
  type = MOSSFW_DATA_TYPE_FLOAT;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPE_FLOAT, MOSSFW_DATA_TYPE(type));
  type = MOSSFW_DATA_TYPE_INT64;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPE_INT64, MOSSFW_DATA_TYPE(type));

  type = MOSSFW_DATA_TYPEGRP_V3;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPEGRP_V3, MOSSFW_DATA_TYPEGRP(type));
  type = MOSSFW_DATA_TYPEGRP_V2;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPEGRP_V2, MOSSFW_DATA_TYPEGRP(type));
  type = MOSSFW_DATA_TYPEGRP_V1;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPEGRP_V1, MOSSFW_DATA_TYPEGRP(type));

  type = MOSSFW_DATA_TYPENAME_ACCEL;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPENAME_ACCEL, MOSSFW_DATA_TYPENAME(type));
  type = MOSSFW_DATA_TYPENAME_GYRO;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPENAME_GYRO, MOSSFW_DATA_TYPENAME(type));
  type = MOSSFW_DATA_TYPENAME_GNSS;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPENAME_GNSS, MOSSFW_DATA_TYPENAME(type));
  type = MOSSFW_DATA_TYPENAME_BARO;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPENAME_BARO, MOSSFW_DATA_TYPENAME(type));
  type = MOSSFW_DATA_TYPENAME_TEMP;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPENAME_TEMP, MOSSFW_DATA_TYPENAME(type));

  type = MOSSFW_DATA_TYPEARRAY_SINGLE;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPEARRAY_SINGLE, MOSSFW_DATA_TYPEARRAY(type));
  type = MOSSFW_DATA_TYPEARRAY_ARRAY;
  TEST_ASSERT_EQUAL(MOSSFW_DATA_TYPEARRAY_ARRAY, MOSSFW_DATA_TYPEARRAY(type));
}


void test_mossfw_fixedmem_create_001(void)
{

mallocerr = -1;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1,
                           2);



TEST_ASSERT(allocator != NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_002(void)
{

mallocerr = -1;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(0,
                           2);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_003(void)
{

mallocerr = -1;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1,
                           0);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_004(void)
{

mallocerr = 3;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1,
                           2);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_005(void)
{

mallocerr = 0;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1,
                           2);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_006(void)
{

mallocerr = 2;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1,
                           2);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_007(void)
{

mallocerr = 1;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1,
                           2);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_008(void)
{

mallocerr = 1;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(0,
                           2);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_009(void)
{

mallocerr = 1;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1,
                           0);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_010(void)
{

mallocerr = -1;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(0,
                           0);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_011(void)
{

mallocerr = 3;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(0,
                           0);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_012(void)
{

mallocerr = 2;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(0,
                           2);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_013(void)
{

mallocerr = 0;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(0,
                           0);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_create_014(void)
{

mallocerr = 2;



















mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1,
                           0);



TEST_ASSERT(allocator == NULL);
mossfw_fixedmem_delete(allocator);
mallocerr = -1;


}

void test_mossfw_fixedmem_delete_001(void)
{

mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1, 1);
TEST_ASSERT(allocator != NULL);
int privnull = 0;
if (privnull) {
    free(((mossfw_fixed_mempool_t *)(allocator->priv))->free);
    free(allocator->priv);
    allocator->priv = NULL;
}
mossfw_allocator_t *allocatorparam = allocator;













int err = mossfw_fixedmem_delete(allocatorparam);





TEST_ASSERT(err == OK);
if (allocatorparam == NULL) {
    int err1 = mossfw_fixedmem_delete(allocator);
    if (privnull) {
        TEST_ASSERT(err1 == ERROR);
    } else {
        TEST_ASSERT(err1 == OK);
    }
}


}

void test_mossfw_fixedmem_delete_002(void)
{

mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1, 1);
TEST_ASSERT(allocator != NULL);
int privnull = 0;
if (privnull) {
    free(((mossfw_fixed_mempool_t *)(allocator->priv))->free);
    free(allocator->priv);
    allocator->priv = NULL;
}
mossfw_allocator_t *allocatorparam = NULL;













int err = mossfw_fixedmem_delete(allocatorparam);





TEST_ASSERT(err == ERROR);
if (allocatorparam == NULL) {
    int err1 = mossfw_fixedmem_delete(allocator);
    if (privnull) {
        TEST_ASSERT(err1 == ERROR);
    } else {
        TEST_ASSERT(err1 == OK);
    }
}


}

void test_mossfw_fixedmem_delete_003(void)
{

mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1, 1);
TEST_ASSERT(allocator != NULL);
int privnull = 1;
if (privnull) {
    free(((mossfw_fixed_mempool_t *)(allocator->priv))->free);
    free(allocator->priv);
    allocator->priv = NULL;
}
mossfw_allocator_t *allocatorparam = allocator;













int err = mossfw_fixedmem_delete(allocatorparam);





TEST_ASSERT(err == ERROR);
if (allocatorparam == NULL) {
    int err1 = mossfw_fixedmem_delete(allocator);
    if (privnull) {
        TEST_ASSERT(err1 == ERROR);
    } else {
        TEST_ASSERT(err1 == OK);
    }
}


}

void test_mossfw_fixedmem_delete_004(void)
{

mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1, 1);
TEST_ASSERT(allocator != NULL);
int privnull = 1;
if (privnull) {
    free(((mossfw_fixed_mempool_t *)(allocator->priv))->free);
    free(allocator->priv);
    allocator->priv = NULL;
}
mossfw_allocator_t *allocatorparam = NULL;













int err = mossfw_fixedmem_delete(allocatorparam);





TEST_ASSERT(err == ERROR);
if (allocatorparam == NULL) {
    int err1 = mossfw_fixedmem_delete(allocator);
    if (privnull) {
        TEST_ASSERT(err1 == ERROR);
    } else {
        TEST_ASSERT(err1 == OK);
    }
}


}

void test_mossfw_sensordata_alloc_001(void)
{

mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1, 1);
TEST_ASSERT(allocator != NULL);
mossfw_allocator_t *allocatorparam = allocator;













mossfw_data_t *buf = mossfw_data_alloc(allocatorparam, 1, 1);





TEST_ASSERT(buf != NULL);
mossfw_data_free(buf);
int errdel = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(errdel == OK);








}

void test_mossfw_sensordata_alloc_002(void)
{

mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1, 1);
TEST_ASSERT(allocator != NULL);
mossfw_allocator_t *allocatorparam = NULL;













mossfw_data_t *buf = mossfw_data_alloc(allocatorparam, 1, 1);





TEST_ASSERT(buf == NULL);
mossfw_data_free(buf);
int errdel = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(errdel == OK);








}

void test_mossfw_sensordata_refer_001(void)
{

mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1, 1);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *mem =
    mossfw_data_alloc(allocator, 1, 1);
mossfw_data_t *memref = mem;











mossfw_data_refer(memref);





mossfw_data_free(mem);
mossfw_data_free(memref);
int errdel = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(errdel == OK);








}

void test_mossfw_sensordata_refer_002(void)
{

mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(1, 1);
TEST_ASSERT(allocator != NULL);
mossfw_data_t *mem =
    mossfw_data_alloc(allocator, 1, 1);
mossfw_data_t *memref = NULL;











mossfw_data_refer(memref);





mossfw_data_free(mem);
mossfw_data_free(memref);
int errdel = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(errdel == OK);








}

void test_mossfw_fixedsize_allocator_001(void)
{

int size = 2;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
TEST_ASSERT(allocator != NULL);
mossfw_allocator_t *allocatorparam = allocator;
(void)size;










int ret = mossfw_fixedsize_allocator(allocatorparam);






TEST_ASSERT(ret == size);
int errdel = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(errdel == OK);








}

void test_mossfw_fixedsize_allocator_002(void)
{

int size = 1;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
TEST_ASSERT(allocator != NULL);
mossfw_allocator_t *allocatorparam = allocator;
(void)size;










int ret = mossfw_fixedsize_allocator(allocatorparam);






TEST_ASSERT(ret == size);
int errdel = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(errdel == OK);








}

void test_mossfw_fixedsize_allocator_003(void)
{

int size = 2;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
TEST_ASSERT(allocator != NULL);
mossfw_allocator_t *allocatorparam = NULL;
(void)size;










int ret = mossfw_fixedsize_allocator(allocatorparam);






TEST_ASSERT(ret == -1);
int errdel = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(errdel == OK);








}

void test_mossfw_fixedsize_allocator_004(void)
{

int size = 1;
mossfw_allocator_t *allocator =
    mossfw_fixedmem_create(size, 1);
TEST_ASSERT(allocator != NULL);
mossfw_allocator_t *allocatorparam = NULL;
(void)size;










int ret = mossfw_fixedsize_allocator(allocatorparam);






TEST_ASSERT(ret == -1);
int errdel = mossfw_fixedmem_delete(allocator);
TEST_ASSERT(errdel == OK);








}


