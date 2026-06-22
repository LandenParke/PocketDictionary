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
#include <string.h>
#include <stdlib.h>
#include "mossfw/mossfw_ringbuff.h"
#include "unity.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define check_buffer(exp_full, exp_empty, \
                     exp_ridx, exp_widx, \
                     exp_store, msg) \
{ \
  int tmp_idx = strlen(msg); \
  sprintf(&msg[tmp_idx], " ReadIdxValue"); \
  TEST_ASSERT_EQUAL_MESSAGE((exp_ridx) * ARIGNED_SIZE, buff->ridx, msg); \
  sprintf(&msg[tmp_idx], " WriteIdxValue"); \
  TEST_ASSERT_EQUAL_MESSAGE((exp_widx) * ARIGNED_SIZE, buff->widx, msg); \
  sprintf(&msg[tmp_idx], " Stored size"); \
  TEST_ASSERT_EQUAL_MESSAGE((exp_store), \
                            mossfw_ringbuff_storednum(buff), msg); \
  sprintf(&msg[tmp_idx], " Is Full ?"); \
  TEST_ASSERT_EQUAL_MESSAGE((exp_full), mossfw_ringbuff_isfull(buff), msg); \
  sprintf(&msg[tmp_idx], " Is Empty ?"); \
  TEST_ASSERT_EQUAL_MESSAGE((exp_empty), mossfw_ringbuff_isempty(buff), msg); \
  msg[tmp_idx] = '\0'; /* Just clean up additional message */ \
}

/****************************************************************************
 * Private Deta Types
 ****************************************************************************/

struct xyz_s
{
  short x;
  short y;
  short z;
};

#define ARIGNED_SIZE  (sizeof(struct xyz_s))
#define DEPTH (16)

/****************************************************************************
 * Private Deta
 ****************************************************************************/

static mossfw_ringbuffer_t *buff = NULL;
static char msg_buff[256];
extern int err_ringbuff_malloc_pettern;
extern int err_ringbuff_wait_pettern;
extern mossfw_ringbuffer_t *err_ringbuff_buff;

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * name: dump_buffer
 ****************************************************************************/

static void dump_buffer(bool en)
{
  int i;
  struct tmp_xyz_s
  {
    struct xyz_s dat;
    short  alignment_dummy;
  } *data;

  if (!en)
    {
      return ;
    }

  data = (struct tmp_xyz_s *)buff->buffer;

  for (i = 0; i < DEPTH; i++)
    {
      printf("[%d]: x=%d, y=%d, z=%d\n", i,
             data->dat.x, data->dat.y, data->dat.z);
      data++;
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
  buff = mossfw_ringbuff_create(sizeof(struct xyz_s), DEPTH);
}

/****************************************************************************
 * name: tearDown
 ****************************************************************************/

void tearDown(void)
{
  mossfw_ringbuff_delete(buff);
}

/****************************************************************************
 * name: test_Init_Param
 ****************************************************************************/

void test_Init_Param(void)
{
  /* Simple parameter check just after initialization */

  TEST_ASSERT_EQUAL(ARIGNED_SIZE,  buff->block_sz);
  TEST_ASSERT_EQUAL(ARIGNED_SIZE * DEPTH, buff->buff_len);
  TEST_ASSERT_EQUAL(0,  buff->ridx);
  TEST_ASSERT_EQUAL(0,  buff->widx);
  TEST_ASSERT_EQUAL(true,  buff->is_empty);
}

/****************************************************************************
 * name: test_Ringbuffer_Some_Cases
 ****************************************************************************/

void test_Ringbuffer_Some_Cases(void)
{
  int i;
  struct xyz_s dat;
  struct xyz_s *rdat;

  /* Test inject data into the ringbuffer until filled up */

  TEST_MESSAGE("Simple Increase to Full -> Decrease to Empty");
  TEST_ASSERT_EQUAL(true, mossfw_ringbuff_isempty(buff));
  TEST_ASSERT_EQUAL(false, mossfw_ringbuff_isfull(buff));

  for (i = 0; i < DEPTH; i++)
    {
      dat.x = i;
      dat.y = i + 1;
      dat.z = i + 2;

      sprintf(msg_buff, "Write Index=%d", i);
      TEST_ASSERT_EQUAL_MESSAGE(true,
                                mossfw_ringbuff_setdata(buff, &dat, true), msg_buff);
      check_buffer(i == (DEPTH - 1), false,
                   0, (i + 1) % DEPTH,
                   i + 1, msg_buff);
    }

  /*
   * Test to expect getting an error
   * when inject a data to the ringbuff
   * in filled up condition.
   */

  msg_buff[0] = '\0';
  TEST_ASSERT_EQUAL_MESSAGE(true, mossfw_ringbuff_isfull(buff), msg_buff);
  check_buffer(true, false, 0, 0, DEPTH, msg_buff);

  dump_buffer(false);

  /* Test pulling data from the ringbuff until empty. */

  for (i = 0; i <= DEPTH; i++)
    {
      sprintf(msg_buff, "Read Index=%d", i);
      if (i == DEPTH)
        {
          /*
           * Test to expect getting an error
           * as receiving NULL when pull a data
           * from the ringbuff in empty condition.
           */

          TEST_ASSERT_EQUAL_MESSAGE(true, mossfw_ringbuff_isempty(buff), msg_buff);
        }
      else
        {
          TEST_ASSERT_NOT_EQUAL_MESSAGE(NULL,
              rdat = (struct xyz_s *)mossfw_ringbuff_getdata(buff, true), msg_buff);
          TEST_ASSERT_EQUAL(i, rdat->x);
          TEST_ASSERT_EQUAL(i + 1, rdat->y);
          TEST_ASSERT_EQUAL(i + 2, rdat->z);

          mossfw_ringbuff_releaseblock(buff);
          check_buffer(false, i >= (DEPTH - 1),
                       (i + 1) % DEPTH, 0,
                       ((DEPTH - 1) - i), msg_buff);
        }
    }

  TEST_MESSAGE("Enqueue / Dequeue data after some data are stored.");

  for (i = 0; i < 5; i++)
    {
      dat.x = i + 30;
      dat.y = i + 31;
      dat.z = i + 32;

      TEST_ASSERT_EQUAL(true, mossfw_ringbuff_setdata(buff, &dat, true));
    }

  msg_buff[0] = '\0';
  check_buffer(false, false, 0, 5, 5, msg_buff);

  for (i = 5; i < 5 + (DEPTH * 2); i++)
    {
      dat.x = i + 30;
      dat.y = i + 31;
      dat.z = i + 32;

      sprintf(msg_buff, "Write / Read Index=%d", i);
      TEST_ASSERT_EQUAL_MESSAGE(true,
                                mossfw_ringbuff_setdata(buff, &dat, true), msg_buff);
      check_buffer(false, false,
                   (i - 5) % DEPTH, (i + 1) % DEPTH,
                   6, msg_buff);

      TEST_ASSERT_NOT_EQUAL_MESSAGE(NULL,
          rdat = (struct xyz_s *)mossfw_ringbuff_getdata(buff, true), msg_buff);
      TEST_ASSERT_EQUAL(i - 5 + 30, rdat->x);
      TEST_ASSERT_EQUAL(i - 5 + 31, rdat->y);
      TEST_ASSERT_EQUAL(i - 5 + 32, rdat->z);
      mossfw_ringbuff_releaseblock(buff);
      check_buffer(false, false,
                   (i - 4) % DEPTH, (i + 1) % DEPTH,
                   5, msg_buff);
    }
}

void test_ErrorCreate(void)
{
  /* mossfw_ringbuff_create NG pattern */
  TEST_ASSERT_EQUAL(NULL, mossfw_ringbuff_create(0, 0));
  TEST_ASSERT_EQUAL(NULL, mossfw_ringbuff_create(0, DEPTH));
  TEST_ASSERT_EQUAL(NULL, mossfw_ringbuff_create(sizeof(struct xyz_s), 0));

  err_ringbuff_malloc_pettern = 1; /* 1st malloc is NG, 2nd malloc is NG*/
  TEST_ASSERT_EQUAL(NULL, mossfw_ringbuff_create(sizeof(struct xyz_s), DEPTH));

  err_ringbuff_malloc_pettern = 2; /* 1st malloc is OK, 2nd malloc is NG*/
  TEST_ASSERT_EQUAL(NULL, mossfw_ringbuff_create(sizeof(struct xyz_s), DEPTH));

  err_ringbuff_malloc_pettern = 0;
}

void test_ErrorDelete(void)
{
  /* mossfw_ringbuff_delete NG pattern */
  buff = mossfw_ringbuff_create(sizeof(struct xyz_s), DEPTH);
  free(buff->buffer);

  buff->buffer = NULL;
  mossfw_ringbuff_delete(buff);

  buff = NULL;
  mossfw_ringbuff_delete(buff);

  mossfw_ringbuff_delete(NULL);
}

void test_ErrorGetdata(void)
{
  /* mossfw_ringbuff_getdata NG pattern */
  buff = mossfw_ringbuff_create(sizeof(struct xyz_s), DEPTH);
  err_ringbuff_buff = buff;
  buff->ridx = 0;
  buff->widx = 0;
  buff->is_empty = 1;
  err_ringbuff_wait_pettern = 1;
  mossfw_ringbuff_getdata(buff, false);

  buff->ridx = 0;
  buff->widx = 0;
  buff->is_empty = 1;
  err_ringbuff_wait_pettern = 0;
  mossfw_ringbuff_getdata(buff, true);

  err_ringbuff_wait_pettern = 0;

/*
  mossfw_ringbuff_getdata(NULL, true);
*/
}

void test_ErrorSetdata(void)
{
  struct xyz_s dat;

  /* mossfw_ringbuff_setdata NG pattern */
  buff->ridx = 0;
  buff->widx = 0;
  buff->is_empty = 0;
  TEST_ASSERT_EQUAL(false, mossfw_ringbuff_setdata(buff, &dat, true));

  err_ringbuff_wait_pettern = 2;
  TEST_ASSERT_EQUAL(true, mossfw_ringbuff_setdata(buff, &dat, false));

  err_ringbuff_wait_pettern = 0;
/*
  mossfw_ringbuff_setdata(NULL, &dat, false);
  mossfw_ringbuff_setdata(buff, NULL, false);
*/
}

void test_ErrorReleaseblock(void)
{
  /* mossfw_ringbuff_releaseblock NG pattern */
  buff->ridx = 0;
  buff->widx = 0;
  buff->is_empty = 1;
  mossfw_ringbuff_releaseblock(buff);

/*
  mossfw_ringbuff_releaseblock(NULL);
*/
}


void test_mossfw_ringbuff_getdata_001(void)
{

int block_sz = sizeof(int);
int block_num = 1;
const int expected_value = 9;
mossfw_ringbuffer_t *buff =
    mossfw_ringbuff_create(block_sz, block_num);
int *blk = malloc(sizeof(int));
TEST_ASSERT(blk != NULL);
*blk = expected_value;
bool errset = mossfw_ringbuff_setdata(buff, blk, 1);
TEST_ASSERT(errset == true);
bool nonblock = 1;
bool stop = true;
mossfw_ringbuff_setstop(buff, stop);




int *ret = mossfw_ringbuff_getdata(buff, nonblock);



TEST_ASSERT(ret == NULL);
if (ret != NULL) {
    TEST_ASSERT(*ret == expected_value);
}
free(blk);
mossfw_ringbuff_delete(buff);


}

void test_mossfw_ringbuff_getdata_002(void)
{

int block_sz = sizeof(int);
int block_num = 1;
const int expected_value = 9;
mossfw_ringbuffer_t *buff =
    mossfw_ringbuff_create(block_sz, block_num);
int *blk = malloc(sizeof(int));
TEST_ASSERT(blk != NULL);
*blk = expected_value;
bool errset = mossfw_ringbuff_setdata(buff, blk, 1);
TEST_ASSERT(errset == true);
bool nonblock = 0;
bool stop = true;
mossfw_ringbuff_setstop(buff, stop);




int *ret = mossfw_ringbuff_getdata(buff, nonblock);



TEST_ASSERT(ret == NULL);
if (ret != NULL) {
    TEST_ASSERT(*ret == expected_value);
}
free(blk);
mossfw_ringbuff_delete(buff);


}

void test_mossfw_ringbuff_getdata_003(void)
{

int block_sz = sizeof(int);
int block_num = 1;
const int expected_value = 9;
mossfw_ringbuffer_t *buff =
    mossfw_ringbuff_create(block_sz, block_num);
int *blk = malloc(sizeof(int));
TEST_ASSERT(blk != NULL);
*blk = expected_value;
bool errset = mossfw_ringbuff_setdata(buff, blk, 1);
TEST_ASSERT(errset == true);
bool nonblock = 1;
bool stop = false;
mossfw_ringbuff_setstop(buff, stop);




int *ret = mossfw_ringbuff_getdata(buff, nonblock);



TEST_ASSERT(ret != NULL);
if (ret != NULL) {
    TEST_ASSERT(*ret == expected_value);
}
free(blk);
mossfw_ringbuff_delete(buff);


}

void test_mossfw_ringbuff_getdata_004(void)
{

int block_sz = sizeof(int);
int block_num = 1;
const int expected_value = 9;
mossfw_ringbuffer_t *buff =
    mossfw_ringbuff_create(block_sz, block_num);
int *blk = malloc(sizeof(int));
TEST_ASSERT(blk != NULL);
*blk = expected_value;
bool errset = mossfw_ringbuff_setdata(buff, blk, 1);
TEST_ASSERT(errset == true);
bool nonblock = 0;
bool stop = false;
mossfw_ringbuff_setstop(buff, stop);




int *ret = mossfw_ringbuff_getdata(buff, nonblock);



TEST_ASSERT(ret != NULL);
if (ret != NULL) {
    TEST_ASSERT(*ret == expected_value);
}
free(blk);
mossfw_ringbuff_delete(buff);


}

void test_mossfw_ringbuff_setdata_001(void)
{

int block_sz = sizeof(int);
int block_num = 1;
bool nonblock = 1;
mossfw_ringbuffer_t *buff =
    mossfw_ringbuff_create(block_sz, block_num);
bool stop = true;
mossfw_ringbuff_setstop(buff, stop);
int *blk = malloc(sizeof(int));
TEST_ASSERT(blk != NULL);



bool err = mossfw_ringbuff_setdata(buff, blk, nonblock);



TEST_ASSERT(err == false);
free(blk);
mossfw_ringbuff_delete(buff);


}

void test_mossfw_ringbuff_setdata_002(void)
{

int block_sz = sizeof(int);
int block_num = 1;
bool nonblock = 0;
mossfw_ringbuffer_t *buff =
    mossfw_ringbuff_create(block_sz, block_num);
bool stop = true;
mossfw_ringbuff_setstop(buff, stop);
int *blk = malloc(sizeof(int));
TEST_ASSERT(blk != NULL);



bool err = mossfw_ringbuff_setdata(buff, blk, nonblock);



TEST_ASSERT(err == false);
free(blk);
mossfw_ringbuff_delete(buff);


}

void test_mossfw_ringbuff_setdata_003(void)
{

int block_sz = sizeof(int);
int block_num = 1;
bool nonblock = 1;
mossfw_ringbuffer_t *buff =
    mossfw_ringbuff_create(block_sz, block_num);
bool stop = false;
mossfw_ringbuff_setstop(buff, stop);
int *blk = malloc(sizeof(int));
TEST_ASSERT(blk != NULL);



bool err = mossfw_ringbuff_setdata(buff, blk, nonblock);



TEST_ASSERT(err == true);
free(blk);
mossfw_ringbuff_delete(buff);


}

void test_mossfw_ringbuff_setdata_004(void)
{

int block_sz = sizeof(int);
int block_num = 1;
bool nonblock = 0;
mossfw_ringbuffer_t *buff =
    mossfw_ringbuff_create(block_sz, block_num);
bool stop = false;
mossfw_ringbuff_setstop(buff, stop);
int *blk = malloc(sizeof(int));
TEST_ASSERT(blk != NULL);



bool err = mossfw_ringbuff_setdata(buff, blk, nonblock);



TEST_ASSERT(err == true);
free(blk);
mossfw_ringbuff_delete(buff);


}

