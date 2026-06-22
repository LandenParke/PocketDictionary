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
#include "PCUnit.h"
#include <float.h>
#include <math.h>
#include "mossfw/sensorlib.h"
#include "mossfw/mossdsp.h"
#ifdef UNITTEST
#include <setjmp.h>

static jmp_buf g_testCaseEnv;
#endif

#ifdef CONFIG_ARCH_CHIP_CXD3277
uint32_t cxd3277_systimer_getcntval(void);
static uint32_t timerval = 0;
#endif

static void beginsystimer(void)
{
#ifdef CONFIG_ARCH_CHIP_CXD3277
    timerval = cxd3277_systimer_getcntval();
#endif
}

static void endsystimer(const char *output_name)
{
#ifdef CONFIG_ARCH_CHIP_CXD3277
    uint32_t v;
    v = cxd3277_systimer_getcntval();
    printf("cxd3277 systimer %s, %u, %u\n", output_name, timerval, v);
#endif
    (void)output_name;
}


static void TestMossdspResampling_mossdsp_interpolatei_001(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatei(INT16_MIN,
                    0,
                    &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == -16384);



beginsystimer();

ret = mossdsp_interpolatei(INT16_MIN,
                    0,
                    &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatei(INT16_MIN,
                    0,
                    &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatei_002(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatei(INT16_MIN,
                    INT16_MAX,
                    &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == -3641);



beginsystimer();

ret = mossdsp_interpolatei(INT16_MIN,
                    INT16_MAX,
                    &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatei(INT16_MIN,
                    INT16_MAX,
                    &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatei_003(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatei(INT16_MIN,
                    INT16_MIN,
                    &param0);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == INT16_MIN);



beginsystimer();

ret = mossdsp_interpolatei(INT16_MIN,
                    INT16_MIN,
                    &param0);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatei(INT16_MIN,
                    INT16_MIN,
                    &param0);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatei_004(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatei(0,
                    0,
                    &param0);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);



beginsystimer();

ret = mossdsp_interpolatei(0,
                    0,
                    &param0);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatei(0,
                    0,
                    &param0);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatei_005(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatei(0,
                    INT16_MAX,
                    &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 16384);



beginsystimer();

ret = mossdsp_interpolatei(0,
                    INT16_MAX,
                    &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatei(0,
                    INT16_MAX,
                    &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatei_006(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    INT16_MIN,
                    &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 3640);



beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    INT16_MIN,
                    &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    INT16_MIN,
                    &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatei_007(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    0,
                    &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 18204);



beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    0,
                    &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    0,
                    &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatei_008(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    INT16_MIN,
                    &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == -1);



beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    INT16_MIN,
                    &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    INT16_MIN,
                    &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatei_009(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    INT16_MAX,
                    &param0);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == INT16_MAX);



beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    INT16_MAX,
                    &param0);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatei(INT16_MAX,
                    INT16_MAX,
                    &param0);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatei_010(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatei(0,
                    INT16_MIN,
                    &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == -14564);



beginsystimer();

ret = mossdsp_interpolatei(0,
                    INT16_MIN,
                    &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatei(0,
                    INT16_MIN,
                    &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatei_011(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatei(INT16_MAX,
                    INT16_MIN,
                    &dt0);


}

PCU_ASSERT(ret == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatei_012(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatei(INT16_MIN,
                    INT16_MAX,
                    NULL);


}

PCU_ASSERT(ret == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatei_013(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatei(INT16_MAX,
                    0,
                    NULL);


}

PCU_ASSERT(ret == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatei_014(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatei(0,
                    INT16_MAX,
                    &dt0);


}

PCU_ASSERT(ret == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatei_015(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatei(INT16_MAX,
                    INT16_MAX,
                    &dt0);


}

PCU_ASSERT(ret == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatei_016(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatei(INT16_MIN,
                    INT16_MIN,
                    NULL);


}

PCU_ASSERT(ret == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatei_017(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatei(0,
                    0,
                    &dt0);


}

PCU_ASSERT(ret == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatei_018(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatei(INT16_MIN,
                    0,
                    &dt0);


}

PCU_ASSERT(ret == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatei_019(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int16_t ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatei(0,
                    INT16_MIN,
                    NULL);


}

PCU_ASSERT(ret == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_001(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatef(1,
                    1,
                    &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(((1) - epsilon < ret && ret < (1) + epsilon) || ((1) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (1) && FLT_MAX < ret) || (!((1) < 1 || 0 < (1)) && !(ret < 1 || 0 < ret)));



beginsystimer();

ret = mossdsp_interpolatef(1,
                    1,
                    &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatef(1,
                    1,
                    &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatef_002(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatef(0,
                    0,
                    &param0);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_MIN;
PCU_ASSERT(((0) - epsilon < ret && ret < (0) + epsilon) || ((0) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0) && FLT_MAX < ret) || (!((0) < 1 || 0 < (0)) && !(ret < 1 || 0 < ret)));



beginsystimer();

ret = mossdsp_interpolatef(0,
                    0,
                    &param0);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatef(0,
                    0,
                    &param0);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatef_003(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatef(1,
                    0,
                    &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(((5.0f / 9.0f) - epsilon < ret && ret < (5.0f / 9.0f) + epsilon) || ((5.0f / 9.0f) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (5.0f / 9.0f) && FLT_MAX < ret) || (!((5.0f / 9.0f) < 1 || 0 < (5.0f / 9.0f)) && !(ret < 1 || 0 < ret)));



beginsystimer();

ret = mossdsp_interpolatef(1,
                    0,
                    &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatef(1,
                    0,
                    &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatef_004(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatef(0,
                    1,
                    &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(((4.0f / 9.0f) - epsilon < ret && ret < (4.0f / 9.0f) + epsilon) || ((4.0f / 9.0f) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (4.0f / 9.0f) && FLT_MAX < ret) || (!((4.0f / 9.0f) < 1 || 0 < (4.0f / 9.0f)) && !(ret < 1 || 0 < ret)));



beginsystimer();

ret = mossdsp_interpolatef(0,
                    1,
                    &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatef(0,
                    1,
                    &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatef_005(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatef(1,
                    1,
                    &param0);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(((1) - epsilon < ret && ret < (1) + epsilon) || ((1) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (1) && FLT_MAX < ret) || (!((1) < 1 || 0 < (1)) && !(ret < 1 || 0 < ret)));



beginsystimer();

ret = mossdsp_interpolatef(1,
                    1,
                    &param0);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatef(1,
                    1,
                    &param0);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatef_006(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatef(0,
                    0,
                    &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_MIN;
PCU_ASSERT(((0) - epsilon < ret && ret < (0) + epsilon) || ((0) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0) && FLT_MAX < ret) || (!((0) < 1 || 0 < (0)) && !(ret < 1 || 0 < ret)));



beginsystimer();

ret = mossdsp_interpolatef(0,
                    0,
                    &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatef(0,
                    0,
                    &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatef_007(void)
{

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatef(1,
                    1,
                    &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(((1) - epsilon < ret && ret < (1) + epsilon) || ((1) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (1) && FLT_MAX < ret) || (!((1) < 1 || 0 < (1)) && !(ret < 1 || 0 < ret)));



beginsystimer();

ret = mossdsp_interpolatef(1,
                    1,
                    &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatef(1,
                    1,
                    &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatef_008(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(FLT_MAX,
                    0,
                    &param1);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_009(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(FLT_MAX,
                    1,
                    &parammax);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_010(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(FLT_MAX,
                    1,
                    &param1);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_011(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(FLT_MAX,
                    1,
                    &param0);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_012(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(FLT_MAX,
                    0,
                    &parammax);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_013(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(FLT_MAX,
                    0,
                    &param0);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_014(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(1,
                    FLT_MAX,
                    &param1);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_015(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(0,
                    FLT_MAX,
                    &param1);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_016(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(1,
                    FLT_MAX,
                    &param0);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_017(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(1,
                    FLT_MAX,
                    &parammax);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_018(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(0,
                    FLT_MAX,
                    &param0);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_019(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(0,
                    FLT_MAX,
                    &parammax);


}

epsilon = 0;
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < ret && ret < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < ret) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_020(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(1,
                    0,
                    NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(((0) - epsilon < ret && ret < (0) + epsilon) || ((0) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0) && FLT_MAX < ret) || (!((0) < 1 || 0 < (0)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_021(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(0,
                    0,
                    &dt0);


}

epsilon = 0;
PCU_ASSERT(((0.0f / 0.0f) - epsilon < ret && ret < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < ret) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_022(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(0,
                    1,
                    NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(((0) - epsilon < ret && ret < (0) + epsilon) || ((0) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0) && FLT_MAX < ret) || (!((0) < 1 || 0 < (0)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_023(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(1,
                    1,
                    &dt0);


}

epsilon = 0;
PCU_ASSERT(((0.0f / 0.0f) - epsilon < ret && ret < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < ret) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_024(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(0,
                    1,
                    &dt0);


}

epsilon = 0;
PCU_ASSERT(((0.0f / 0.0f) - epsilon < ret && ret < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < ret) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_025(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(1,
                    0,
                    &dt0);


}

epsilon = 0;
PCU_ASSERT(((0.0f / 0.0f) - epsilon < ret && ret < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < ret) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_026(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(FLT_MAX,
                    1,
                    NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(((0) - epsilon < ret && ret < (0) + epsilon) || ((0) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0) && FLT_MAX < ret) || (!((0) < 1 || 0 < (0)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_027(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(FLT_MAX,
                    FLT_MAX,
                    &dt0);


}

epsilon = 0;
PCU_ASSERT(((0.0f / 0.0f) - epsilon < ret && ret < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < ret) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_028(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(0,
                    0,
                    NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(((0) - epsilon < ret && ret < (0) + epsilon) || ((0) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0) && FLT_MAX < ret) || (!((0) < 1 || 0 < (0)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_029(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(1,
                    FLT_MAX,
                    NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(((0) - epsilon < ret && ret < (0) + epsilon) || ((0) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0) && FLT_MAX < ret) || (!((0) < 1 || 0 < (0)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatef_030(void)
{
#ifdef UNITTEST

struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
float epsilon;
float ret;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatef(1,
                    1,
                    NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(((0) - epsilon < ret && ret < (0) + epsilon) || ((0) < -FLT_MAX && ret < -FLT_MAX) || (FLT_MAX < (0) && FLT_MAX < ret) || (!((0) < 1 || 0 < (0)) && !(ret < 1 || 0 < ret)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_001(void)
{

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1max,
                      &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.x == INT16_MIN);
PCU_ASSERT(out.y == 0);
PCU_ASSERT(out.z == INT16_MAX);



beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1max,
                      &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1max,
                      &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3i_002(void)
{

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1,
                      &param0);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.x == 0);
PCU_ASSERT(out.y == -3641);
PCU_ASSERT(out.z == 0);



beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1,
                      &param0);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1,
                      &param0);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3i_003(void)
{

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1,
                      &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.x == -18204);
PCU_ASSERT(out.y == 14563);
PCU_ASSERT(out.z == 18204);



beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1,
                      &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1,
                      &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3i_004(void)
{

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1max,
                      &param0);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.x == INT16_MIN);
PCU_ASSERT(out.y == 0);
PCU_ASSERT(out.z == INT16_MAX);



beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1max,
                      &param0);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1max,
                      &param0);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3i_005(void)
{

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1,
                      &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.x == -16384);
PCU_ASSERT(out.y == 16384);
PCU_ASSERT(out.z == 16384);



beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1,
                      &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1,
                      &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3i_006(void)
{

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1max,
                      &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.x == -16384);
PCU_ASSERT(out.y == -16384);
PCU_ASSERT(out.z == 16384);



beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1max,
                      &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1max,
                      &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3i_007(void)
{

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1,
                      &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.x == 0);
PCU_ASSERT(out.y == -3641);
PCU_ASSERT(out.z == 0);



beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1,
                      &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1,
                      &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3i_008(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      &in0max,
                      &in1max,
                      &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_009(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      &in0,
                      &in1,
                      &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_010(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      &in0max,
                      &in1,
                      &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_011(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      &in0max,
                      &in1max,
                      &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_012(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      &in0max,
                      &in1,
                      &parammax);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_013(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      &in0,
                      &in1max,
                      &parammax);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_014(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      &in0,
                      &in1,
                      &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_015(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      NULL,
                      &in1,
                      &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_016(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      NULL,
                      &in1max,
                      &parammax);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_017(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      NULL,
                      &in1max,
                      &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_018(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      NULL,
                      &in1,
                      &parammax);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_019(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      NULL,
                      &in1,
                      &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_020(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      NULL,
                      &in1max,
                      &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_021(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      NULL,
                      &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_022(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      NULL,
                      &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_023(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      NULL,
                      &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_024(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      NULL,
                      &parammax);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_025(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      NULL,
                      &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_026(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      NULL,
                      &parammax);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_027(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1,
                      NULL);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_028(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1,
                      &dt0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_029(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1max,
                      NULL);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_030(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1max,
                      &dt0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_031(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0,
                      &in1max,
                      &dt0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_032(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      &in0max,
                      &in1max,
                      &parammax);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_033(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      &in0,
                      &in1,
                      NULL);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_034(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      NULL,
                      NULL,
                      &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_035(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      NULL,
                      NULL,
                      &dt0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_036(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      NULL,
                      NULL,
                      NULL);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_037(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      NULL,
                      &in1max,
                      &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_038(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      &in0,
                      &in1max,
                      &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_039(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      &in0max,
                      &in1,
                      &dt0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_040(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(NULL, 
                      &in0max,
                      &in1,
                      &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3i_041(void)
{
#ifdef UNITTEST

mossfw_data_v3s_t out = {.x = -1, .y = -1, .z = -1};
mossfw_data_v3s_t in0 = {.x = 0, .y = INT16_MIN, .z = 0};
mossfw_data_v3s_t in0max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
mossfw_data_v3s_t in1 = {.x = 0, .y = INT16_MAX, .z = 0};
mossfw_data_v3s_t in1max = {.x = INT16_MIN, .y = 0, .z = INT16_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3i(&out, 
                      NULL,
                      &in1max,
                      NULL);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_001(void)
{

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      &in1,
                      &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((0.5f) - epsilon < out.x && out.x < (0.5f) + epsilon) || ((0.5f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.5f) && FLT_MAX < out.x) || (!((0.5f) < 1 || 0 < (0.5f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((-0.5f) - epsilon < out.y && out.y < (-0.5f) + epsilon) || ((-0.5f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (-0.5f) && FLT_MAX < out.y) || (!((-0.5f) < 1 || 0 < (-0.5f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < out.z && out.z < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < out.z) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      &in1,
                      &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      &in1,
                      &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3f_002(void)
{

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      &in1,
                      &param0);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((4.0f / 9.0f) - epsilon < out.x && out.x < (4.0f / 9.0f) + epsilon) || ((4.0f / 9.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (4.0f / 9.0f) && FLT_MAX < out.x) || (!((4.0f / 9.0f) < 1 || 0 < (4.0f / 9.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((-4.0f / 9.0f) - epsilon < out.y && out.y < (-4.0f / 9.0f) + epsilon) || ((-4.0f / 9.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (-4.0f / 9.0f) && FLT_MAX < out.y) || (!((-4.0f / 9.0f) < 1 || 0 < (-4.0f / 9.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < out.z && out.z < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < out.z) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      &in1,
                      &param0);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      &in1,
                      &param0);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3f_003(void)
{

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      &in1,
                      &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((4.0f / 9.0f) - epsilon < out.x && out.x < (4.0f / 9.0f) + epsilon) || ((4.0f / 9.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (4.0f / 9.0f) && FLT_MAX < out.x) || (!((4.0f / 9.0f) < 1 || 0 < (4.0f / 9.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((-4.0f / 9.0f) - epsilon < out.y && out.y < (-4.0f / 9.0f) + epsilon) || ((-4.0f / 9.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (-4.0f / 9.0f) && FLT_MAX < out.y) || (!((-4.0f / 9.0f) < 1 || 0 < (-4.0f / 9.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < out.z && out.z < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < out.z) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      &in1,
                      &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      &in1,
                      &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3f_004(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(NULL, 
                      &in0,
                      &in1,
                      &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_005(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(NULL, 
                      &in0,
                      &in1,
                      &param0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_006(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(NULL, 
                      &in0,
                      &in1,
                      &param1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_007(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      NULL,
                      &in1,
                      &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_008(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      NULL,
                      &in1,
                      &param0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_009(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      NULL,
                      &in1,
                      &param1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_010(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      NULL,
                      &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_011(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      NULL,
                      &param0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_012(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      NULL,
                      &param1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_013(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      &in1,
                      NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_014(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      &in0,
                      &in1,
                      &dt0);


}

epsilon = 0;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((0.0f / 0.0f) - epsilon < out.x && out.x < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < out.x) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f / 0.0f) - epsilon < out.y && out.y < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < out.y) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f / 0.0f) - epsilon < out.z && out.z < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < out.z) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_015(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(NULL, 
                      NULL,
                      &in1,
                      &param1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_016(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      NULL,
                      NULL,
                      &dt0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_017(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(NULL, 
                      NULL,
                      NULL,
                      &param0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_018(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(NULL, 
                      &in0,
                      NULL,
                      NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_019(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(NULL, 
                      &in0,
                      &in1,
                      &dt0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_020(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      NULL,
                      NULL,
                      &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_021(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      NULL,
                      &in1,
                      NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3f_022(void)
{
#ifdef UNITTEST

mossfw_data_v3f_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3f_t in0 = {.x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3f_t in1 = {.x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0xfffffff7, .t = 0xfffffffb, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0xfffffffc, .t = 0, .t1 = 5
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 2, .t = 1, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;
(void)parammax;
(void)dt0;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3f(&out, 
                      NULL,
                      NULL,
                      &param0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_001(void)
{

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       &in1,
                       &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == 65535);
PCU_ASSERT(out.x == -2);
PCU_ASSERT(out.y == 32765);
PCU_ASSERT(out.z == 2);



beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       &in1,
                       &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       &in1,
                       &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_002(void)
{

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0,
                       &in1,
                       &param0);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(out.x == 0);
PCU_ASSERT(out.y == 3640);
PCU_ASSERT(out.z == 0);



beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0,
                       &in1,
                       &param0);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0,
                       &in1,
                       &param0);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_003(void)
{

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0,
                       &in1max,
                       &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == 65535);
PCU_ASSERT(out.x == -26214);
PCU_ASSERT(out.y == -6554);
PCU_ASSERT(out.z == 26214);



beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0,
                       &in1max,
                       &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0,
                       &in1max,
                       &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_004(void)
{

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       &in1max,
                       &param0);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(out.x == INT16_MIN);
PCU_ASSERT(out.y == 0);
PCU_ASSERT(out.z == INT16_MAX);



beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       &in1max,
                       &param0);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       &in1max,
                       &param0);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_005(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       &in0max,
                       &in1,
                       &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_006(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       &in0,
                       &in1,
                       &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_007(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       &in0,
                       &in1max,
                       &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_008(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       &in0max,
                       &in1max,
                       &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_009(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &innull,
                       &in1,
                       &param1);


}

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == 65535);
PCU_ASSERT(out.x == 0);
PCU_ASSERT(out.y == 32765);
PCU_ASSERT(out.z == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_010(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       NULL,
                       &in1,
                       &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_011(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       NULL,
                       &in1max,
                       &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_012(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &innull,
                       &in1max,
                       &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_013(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       NULL,
                       &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_014(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &in0,
                       NULL,
                       &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_015(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &in0,
                       &innull,
                       &param1);


}

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == 65535);
PCU_ASSERT(out.x == 0);
PCU_ASSERT(out.y == -6554);
PCU_ASSERT(out.z == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_016(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       &innull,
                       &param0);


}

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(out.x == 0);
PCU_ASSERT(out.y == 0);
PCU_ASSERT(out.z == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_017(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       &in1,
                       &param0);


}

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(out.x == -2);
PCU_ASSERT(out.y == 32765);
PCU_ASSERT(out.z == 2);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_018(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &in0,
                       &in1,
                       NULL);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_019(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &in0,
                       &in1max,
                       &param0);


}

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(out.x == INT16_MIN);
PCU_ASSERT(out.y == 0);
PCU_ASSERT(out.z == INT16_MAX);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_020(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       &in1max,
                       NULL);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_021(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       &innull,
                       &in1,
                       &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_022(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &in0,
                       &innull,
                       &param0);


}

PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(out.x == 0);
PCU_ASSERT(out.y == 0);
PCU_ASSERT(out.z == 0);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_023(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       &in0max,
                       &in1max,
                       &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_024(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       NULL,
                       &in1,
                       &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_025(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       NULL,
                       &innull,
                       &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_026(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       &in0,
                       NULL,
                       &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_027(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &innull,
                       &innull,
                       NULL);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_028(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       &in0,
                       &in1max,
                       NULL);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_029(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       NULL,
                       &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_030(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       &in0,
                       &in1,
                       &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_031(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       NULL,
                       NULL,
                       NULL);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_032(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &in0max,
                       &in1,
                       NULL);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_033(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       &innull,
                       &in1max,
                       &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_034(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       &innull,
                       NULL,
                       &param1);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_035(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(&out, 
                       NULL,
                       &in1max,
                       &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3ti_036(void)
{
#ifdef UNITTEST

mossfw_data_v3ts_t out =    {.t = 1, .x = -1, .y = -1, .z = -1};
mossfw_data_v3ts_t in0 =    {.t = 0xfffb, .x = 0,         .y = INT16_MIN, .z = 0        };
mossfw_data_v3ts_t in0max = {.t = 1,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t in1 =    {.t = 4,      .x = 0,         .y = INT16_MAX, .z = 0        };
mossfw_data_v3ts_t in1max = {.t = 0,      .x = INT16_MIN, .y = 0,         .z = INT16_MAX};
mossfw_data_v3ts_t innull = {.t = 0, .x = 0, .y = 0, .z = 0};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0xffff, .t1 = 0
};
int16_t ret;
(void)in0;
(void)in0max;
(void)in1;
(void)in1max;
(void)innull;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3ti(NULL, 
                       &innull,
                       &innull,
                       &param0);


}

PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 1);
PCU_ASSERT(out.x == -1);
PCU_ASSERT(out.y == -1);
PCU_ASSERT(out.z == -1);


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_001(void)
{

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3tf(&out, 
                       &in0,
                       &in1,
                       &param1);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((5.0f / 9.0f) - epsilon < out.x && out.x < (5.0f / 9.0f) + epsilon) || ((5.0f / 9.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (5.0f / 9.0f) && FLT_MAX < out.x) || (!((5.0f / 9.0f) < 1 || 0 < (5.0f / 9.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((-5.0f / 9.0f) - epsilon < out.y && out.y < (-5.0f / 9.0f) + epsilon) || ((-5.0f / 9.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (-5.0f / 9.0f) && FLT_MAX < out.y) || (!((-5.0f / 9.0f) < 1 || 0 < (-5.0f / 9.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < out.z && out.z < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < out.z) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolatev3tf(&out, 
                       &in0,
                       &in1,
                       &param1);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3tf(&out, 
                       &in0,
                       &in1,
                       &param1);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_002(void)
{

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolatev3tf(&out, 
                       &in0,
                       &in1,
                       &param0);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((4.0f / 9.0f) - epsilon < out.x && out.x < (4.0f / 9.0f) + epsilon) || ((4.0f / 9.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (4.0f / 9.0f) && FLT_MAX < out.x) || (!((4.0f / 9.0f) < 1 || 0 < (4.0f / 9.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((-4.0f / 9.0f) - epsilon < out.y && out.y < (-4.0f / 9.0f) + epsilon) || ((-4.0f / 9.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (-4.0f / 9.0f) && FLT_MAX < out.y) || (!((-4.0f / 9.0f) < 1 || 0 < (-4.0f / 9.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((FLT_MAX + FLT_MAX) - epsilon < out.z && out.z < (FLT_MAX + FLT_MAX) + epsilon) || ((FLT_MAX + FLT_MAX) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (FLT_MAX + FLT_MAX) && FLT_MAX < out.z) || (!((FLT_MAX + FLT_MAX) < 1 || 0 < (FLT_MAX + FLT_MAX)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolatev3tf(&out, 
                       &in0,
                       &in1,
                       &param0);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolatev3tf(&out, 
                       &in0,
                       &in1,
                       &param0);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_003(void)
{
#ifdef UNITTEST

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3tf(NULL, 
                       &in0,
                       &in1,
                       &param1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_004(void)
{
#ifdef UNITTEST

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3tf(NULL, 
                       &in0,
                       &in1,
                       &param0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_005(void)
{
#ifdef UNITTEST

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3tf(&out, 
                       NULL,
                       &in1,
                       &param1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_006(void)
{
#ifdef UNITTEST

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3tf(&out, 
                       NULL,
                       &in1,
                       &param0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_007(void)
{
#ifdef UNITTEST

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3tf(&out, 
                       &in0,
                       NULL,
                       &param1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_008(void)
{
#ifdef UNITTEST

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3tf(&out, 
                       &in0,
                       NULL,
                       &param0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_009(void)
{
#ifdef UNITTEST

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3tf(&out, 
                       &in0,
                       &in1,
                       NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_010(void)
{
#ifdef UNITTEST

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3tf(NULL, 
                       NULL,
                       &in1,
                       &param0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_011(void)
{
#ifdef UNITTEST

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3tf(NULL, 
                       NULL,
                       NULL,
                       NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolatev3tf_012(void)
{
#ifdef UNITTEST

mossfw_data_v3tf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_v3tf_t in0 = {.t = 0xfffffffb, .x = 0.0f, .y =  0.0f, .z = FLT_MAX};
mossfw_data_v3tf_t in1 = {.t = 4, .x = 1.0f, .y = -1.0f, .z = FLT_MAX};
struct mossdsp_interpolate_param_s param0 = {
    .t0 = 0, .t = 0xffffffff, .t1 = 0
};
struct mossdsp_interpolate_param_s param1 = {
    .t0 = 0, .t = 0, .t1 = 0
};
int ret;
float epsilon;
(void)in0;
(void)in1;
(void)param0;
(void)param1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolatev3tf(&out, 
                       NULL,
                       NULL,
                       &param1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_001(void)
{

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in0n,
                     &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((expn0.w) - epsilon < out.w && out.w < (expn0.w) + epsilon) || ((expn0.w) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (expn0.w) && FLT_MAX < out.w) || (!((expn0.w) < 1 || 0 < (expn0.w)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((expn0.x) - epsilon < out.x && out.x < (expn0.x) + epsilon) || ((expn0.x) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (expn0.x) && FLT_MAX < out.x) || (!((expn0.x) < 1 || 0 < (expn0.x)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((expn0.y) - epsilon < out.y && out.y < (expn0.y) + epsilon) || ((expn0.y) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (expn0.y) && FLT_MAX < out.y) || (!((expn0.y) < 1 || 0 < (expn0.y)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((expn0.z) - epsilon < out.z && out.z < (expn0.z) + epsilon) || ((expn0.z) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (expn0.z) && FLT_MAX < out.z) || (!((expn0.z) < 1 || 0 < (expn0.z)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in0n,
                     &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in0n,
                     &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolateqf_002(void)
{

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in0n,
                     &param);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((expn1.w) - epsilon < out.w && out.w < (expn1.w) + epsilon) || ((expn1.w) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (expn1.w) && FLT_MAX < out.w) || (!((expn1.w) < 1 || 0 < (expn1.w)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((expn1.x) - epsilon < out.x && out.x < (expn1.x) + epsilon) || ((expn1.x) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (expn1.x) && FLT_MAX < out.x) || (!((expn1.x) < 1 || 0 < (expn1.x)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((expn1.y) - epsilon < out.y && out.y < (expn1.y) + epsilon) || ((expn1.y) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (expn1.y) && FLT_MAX < out.y) || (!((expn1.y) < 1 || 0 < (expn1.y)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((expn1.z) - epsilon < out.z && out.z < (expn1.z) + epsilon) || ((expn1.z) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (expn1.z) && FLT_MAX < out.z) || (!((expn1.z) < 1 || 0 < (expn1.z)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in0n,
                     &param);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in0n,
                     &param);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolateqf_003(void)
{

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in1,
                     &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((exp0.w) - epsilon < out.w && out.w < (exp0.w) + epsilon) || ((exp0.w) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (exp0.w) && FLT_MAX < out.w) || (!((exp0.w) < 1 || 0 < (exp0.w)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((exp0.x) - epsilon < out.x && out.x < (exp0.x) + epsilon) || ((exp0.x) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (exp0.x) && FLT_MAX < out.x) || (!((exp0.x) < 1 || 0 < (exp0.x)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((exp0.y) - epsilon < out.y && out.y < (exp0.y) + epsilon) || ((exp0.y) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (exp0.y) && FLT_MAX < out.y) || (!((exp0.y) < 1 || 0 < (exp0.y)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((exp0.z) - epsilon < out.z && out.z < (exp0.z) + epsilon) || ((exp0.z) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (exp0.z) && FLT_MAX < out.z) || (!((exp0.z) < 1 || 0 < (exp0.z)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in1,
                     &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in1,
                     &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolateqf_004(void)
{

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in1,
                     &param);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((exp1.w) - epsilon < out.w && out.w < (exp1.w) + epsilon) || ((exp1.w) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (exp1.w) && FLT_MAX < out.w) || (!((exp1.w) < 1 || 0 < (exp1.w)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((exp1.x) - epsilon < out.x && out.x < (exp1.x) + epsilon) || ((exp1.x) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (exp1.x) && FLT_MAX < out.x) || (!((exp1.x) < 1 || 0 < (exp1.x)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((exp1.y) - epsilon < out.y && out.y < (exp1.y) + epsilon) || ((exp1.y) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (exp1.y) && FLT_MAX < out.y) || (!((exp1.y) < 1 || 0 < (exp1.y)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((exp1.z) - epsilon < out.z && out.z < (exp1.z) + epsilon) || ((exp1.z) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (exp1.z) && FLT_MAX < out.z) || (!((exp1.z) < 1 || 0 < (exp1.z)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in1,
                     &param);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in1,
                     &param);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolateqf_005(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(NULL, 
                     &in0,
                     &in0n,
                     &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_006(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(NULL, 
                     &in0,
                     &in0n,
                     &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_007(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(NULL, 
                     &in0,
                     &in1,
                     &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_008(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(NULL, 
                     &in0,
                     &in1,
                     &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_009(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     NULL,
                     &in0n,
                     &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_010(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     NULL,
                     &in0n,
                     &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_011(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     NULL,
                     &in1,
                     &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_012(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     NULL,
                     &in1,
                     &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_013(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     NULL,
                     &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_014(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     NULL,
                     &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_015(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in0n,
                     NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_016(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in0n,
                     &dt0);


}

epsilon = 0;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((0.0f / 0.0f) - epsilon < out.w && out.w < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < out.w) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f / 0.0f) - epsilon < out.x && out.x < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < out.x) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f / 0.0f) - epsilon < out.y && out.y < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < out.y) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f / 0.0f) - epsilon < out.z && out.z < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < out.z) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_017(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in1,
                     NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_018(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     &in1,
                     &dt0);


}

epsilon = 0;
PCU_ASSERT(ret == 0);
PCU_ASSERT(((0.0f / 0.0f) - epsilon < out.w && out.w < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < out.w) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f / 0.0f) - epsilon < out.x && out.x < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < out.x) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f / 0.0f) - epsilon < out.y && out.y < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < out.y) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f / 0.0f) - epsilon < out.z && out.z < (0.0f / 0.0f) + epsilon) || ((0.0f / 0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f / 0.0f) && FLT_MAX < out.z) || (!((0.0f / 0.0f) < 1 || 0 < (0.0f / 0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_019(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(NULL, 
                     &in0,
                     NULL,
                     &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_020(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     NULL,
                     &in0n,
                     &dt0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_021(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     NULL,
                     NULL,
                     &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_022(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(NULL, 
                     NULL,
                     &in1,
                     &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_023(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     &in0,
                     NULL,
                     NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_024(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(NULL, 
                     NULL,
                     &in1,
                     NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_025(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(&out, 
                     NULL,
                     &in0n,
                     NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqf_026(void)
{
#ifdef UNITTEST

mossfw_data_qf_t out = {.x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qf_t in0 = {
    .w =                cos(acos(-1.0) * 0.125),
    .x = 0.25         * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125)
};
mossfw_data_qf_t in1 = {
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qf_t in0n = {
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0xfffffffc, .t = 0xfffffffd, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 1, .t = 0, .t1 = 0xffffffff
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qf_t exp0 = {
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qf_t exp1 = {
    .w =                  cos(acos(-1.0) * 0.1875),
    .x = 0.25          * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qf_t expn0;
mossfw_data_qf_t expn1;
float ret;
float epsilon;
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqf(NULL, 
                     NULL,
                     NULL,
                     &dt0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_001(void)
{

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in0n,
                      &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == expn0.t);
PCU_ASSERT(((expn0.w) - epsilon < out.w && out.w < (expn0.w) + epsilon) || ((expn0.w) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (expn0.w) && FLT_MAX < out.w) || (!((expn0.w) < 1 || 0 < (expn0.w)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((expn0.x) - epsilon < out.x && out.x < (expn0.x) + epsilon) || ((expn0.x) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (expn0.x) && FLT_MAX < out.x) || (!((expn0.x) < 1 || 0 < (expn0.x)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((expn0.y) - epsilon < out.y && out.y < (expn0.y) + epsilon) || ((expn0.y) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (expn0.y) && FLT_MAX < out.y) || (!((expn0.y) < 1 || 0 < (expn0.y)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((expn0.z) - epsilon < out.z && out.z < (expn0.z) + epsilon) || ((expn0.z) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (expn0.z) && FLT_MAX < out.z) || (!((expn0.z) < 1 || 0 < (expn0.z)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in0n,
                      &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in0n,
                      &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolateqtf_002(void)
{

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in0n,
                      &param);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == expn1.t);
PCU_ASSERT(((expn1.w) - epsilon < out.w && out.w < (expn1.w) + epsilon) || ((expn1.w) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (expn1.w) && FLT_MAX < out.w) || (!((expn1.w) < 1 || 0 < (expn1.w)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((expn1.x) - epsilon < out.x && out.x < (expn1.x) + epsilon) || ((expn1.x) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (expn1.x) && FLT_MAX < out.x) || (!((expn1.x) < 1 || 0 < (expn1.x)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((expn1.y) - epsilon < out.y && out.y < (expn1.y) + epsilon) || ((expn1.y) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (expn1.y) && FLT_MAX < out.y) || (!((expn1.y) < 1 || 0 < (expn1.y)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((expn1.z) - epsilon < out.z && out.z < (expn1.z) + epsilon) || ((expn1.z) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (expn1.z) && FLT_MAX < out.z) || (!((expn1.z) < 1 || 0 < (expn1.z)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in0n,
                      &param);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in0n,
                      &param);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolateqtf_003(void)
{

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in1,
                      &parammax);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == exp0.t);
PCU_ASSERT(((exp0.w) - epsilon < out.w && out.w < (exp0.w) + epsilon) || ((exp0.w) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (exp0.w) && FLT_MAX < out.w) || (!((exp0.w) < 1 || 0 < (exp0.w)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((exp0.x) - epsilon < out.x && out.x < (exp0.x) + epsilon) || ((exp0.x) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (exp0.x) && FLT_MAX < out.x) || (!((exp0.x) < 1 || 0 < (exp0.x)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((exp0.y) - epsilon < out.y && out.y < (exp0.y) + epsilon) || ((exp0.y) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (exp0.y) && FLT_MAX < out.y) || (!((exp0.y) < 1 || 0 < (exp0.y)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((exp0.z) - epsilon < out.z && out.z < (exp0.z) + epsilon) || ((exp0.z) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (exp0.z) && FLT_MAX < out.z) || (!((exp0.z) < 1 || 0 < (exp0.z)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in1,
                      &parammax);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in1,
                      &parammax);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolateqtf_004(void)
{

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in1,
                      &param);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(out.t == exp1.t);
PCU_ASSERT(((exp1.w) - epsilon < out.w && out.w < (exp1.w) + epsilon) || ((exp1.w) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (exp1.w) && FLT_MAX < out.w) || (!((exp1.w) < 1 || 0 < (exp1.w)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((exp1.x) - epsilon < out.x && out.x < (exp1.x) + epsilon) || ((exp1.x) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (exp1.x) && FLT_MAX < out.x) || (!((exp1.x) < 1 || 0 < (exp1.x)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((exp1.y) - epsilon < out.y && out.y < (exp1.y) + epsilon) || ((exp1.y) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (exp1.y) && FLT_MAX < out.y) || (!((exp1.y) < 1 || 0 < (exp1.y)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((exp1.z) - epsilon < out.z && out.z < (exp1.z) + epsilon) || ((exp1.z) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (exp1.z) && FLT_MAX < out.z) || (!((exp1.z) < 1 || 0 < (exp1.z)) && !(out.z < 1 || 0 < out.z)));



beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in1,
                      &param);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in1,
                      &param);


endsystimer(__func__);
}

static void TestMossdspResampling_mossdsp_interpolateqtf_005(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(NULL, 
                      &in0,
                      &in0n,
                      &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_006(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(NULL, 
                      &in0,
                      &in0n,
                      &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_007(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(NULL, 
                      &in0,
                      &in1,
                      &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_008(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(NULL, 
                      &in0,
                      &in1,
                      &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_009(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(&out, 
                      NULL,
                      &in0n,
                      &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_010(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(&out, 
                      NULL,
                      &in0n,
                      &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_011(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(&out, 
                      NULL,
                      &in1,
                      &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_012(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(&out, 
                      NULL,
                      &in1,
                      &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_013(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      NULL,
                      &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_014(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      NULL,
                      &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_015(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in0n,
                      NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_016(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(&out, 
                      &in0,
                      &in1,
                      NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_017(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(&out, 
                      NULL,
                      &in1,
                      NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_018(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(NULL, 
                      &in0,
                      NULL,
                      &parammax);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_019(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(NULL, 
                      NULL,
                      &in0n,
                      &param);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}

static void TestMossdspResampling_mossdsp_interpolateqtf_020(void)
{
#ifdef UNITTEST

mossfw_data_qtf_t out = {.t = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f};
mossfw_data_qtf_t in0 = {
    .t = 2,
    .w = cos(acos(-1.0) * 0.125),
    .x = 0.25 * sin(acos(-1.0) * 0.125),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.125)
};
mossfw_data_qtf_t in1 = {
    .t = 0xfffffffe,
    .w = cos(acos(-1.0) * 0.375),
    .x = 0.25 * sin(acos(-1.0) * 0.375),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.375),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.375)
};
mossfw_data_qtf_t in0n = {
    .t = 0xfffffffe,
    .w =                cos(acos(-1.0) * 0.125 + 0.3),
    .x = 0.25         * sin(acos(-1.0) * 0.125 + 0.3),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.125 + 0.3),
    .z = sqrt(0.75)   * sin(acos(-1.0) * 0.125 + 0.3)
};
struct mossdsp_interpolate_param_s param = {
    .t0 = 0, .t = 1073741825, .t1 = 0
};
struct mossdsp_interpolate_param_s parammax = {
    .t0 = 0, .t = 0, .t1 = 0
};
struct mossdsp_interpolate_param_s dt0 = {
    .t0 = 0, .t = 0, .t1 = 0
};
mossfw_data_qtf_t exp0 = {
    .t = 0,
    .w = sqrt(0.5),
    .x = sqrt(0.03125),
    .y = sqrt(0.09375),
    .z = sqrt(0.375)
};
mossfw_data_qtf_t exp1 = {
    .t = 1073741825,
    .w = cos(acos(-1.0) * 0.1875),
    .x = 0.25 * sin(acos(-1.0) * 0.1875),
    .y = sqrt(0.1875) * sin(acos(-1.0) * 0.1875),
    .z = sqrt(0.75) * sin(acos(-1.0) * 0.1875)
};
mossfw_data_qtf_t expn0;
mossfw_data_qtf_t expn1;
float ret;
float epsilon;
expn0.t = 0,
expn0.w = (in0.w + in0n.w) * 0.5;
expn0.x = (in0.x + in0n.x) * 0.5;
expn0.y = (in0.y + in0n.y) * 0.5;
expn0.z = (in0.z + in0n.z) * 0.5;
expn1.t = 1073741825,
expn1.w = 0.75 * in0.w + 0.25 * in0n.w;
expn1.x = 0.75 * in0.x + 0.25 * in0n.x;
expn1.y = 0.75 * in0.y + 0.25 * in0n.y;
expn1.z = 0.75 * in0.z + 0.25 * in0n.z;
(void)in1;
(void)param;
(void)parammax;
(void)dt0;
(void)exp0;
(void)exp1;
(void)expn0;
(void)expn1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_interpolateqtf(NULL, 
                      NULL,
                      NULL,
                      NULL);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(out.t == 0);
PCU_ASSERT(((0.0f) - epsilon < out.w && out.w < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.w < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.w) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.w < 1 || 0 < out.w)));
PCU_ASSERT(((0.0f) - epsilon < out.x && out.x < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.x < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.x) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.x < 1 || 0 < out.x)));
PCU_ASSERT(((0.0f) - epsilon < out.y && out.y < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.y < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.y) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.y < 1 || 0 < out.y)));
PCU_ASSERT(((0.0f) - epsilon < out.z && out.z < (0.0f) + epsilon) || ((0.0f) < -FLT_MAX && out.z < -FLT_MAX) || (FLT_MAX < (0.0f) && FLT_MAX < out.z) || (!((0.0f) < 1 || 0 < (0.0f)) && !(out.z < 1 || 0 < out.z)));


#endif
}


PCU_Suite* TestMossdspResampling(void)
{
    static PCU_Test tests[] = {

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_001", .test = TestMossdspResampling_mossdsp_interpolatei_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_002", .test = TestMossdspResampling_mossdsp_interpolatei_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_003", .test = TestMossdspResampling_mossdsp_interpolatei_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_004", .test = TestMossdspResampling_mossdsp_interpolatei_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_005", .test = TestMossdspResampling_mossdsp_interpolatei_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_006", .test = TestMossdspResampling_mossdsp_interpolatei_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_007", .test = TestMossdspResampling_mossdsp_interpolatei_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_008", .test = TestMossdspResampling_mossdsp_interpolatei_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_009", .test = TestMossdspResampling_mossdsp_interpolatei_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_010", .test = TestMossdspResampling_mossdsp_interpolatei_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_011", .test = TestMossdspResampling_mossdsp_interpolatei_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_012", .test = TestMossdspResampling_mossdsp_interpolatei_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_013", .test = TestMossdspResampling_mossdsp_interpolatei_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_014", .test = TestMossdspResampling_mossdsp_interpolatei_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_015", .test = TestMossdspResampling_mossdsp_interpolatei_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_016", .test = TestMossdspResampling_mossdsp_interpolatei_016, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_017", .test = TestMossdspResampling_mossdsp_interpolatei_017, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_018", .test = TestMossdspResampling_mossdsp_interpolatei_018, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatei_019", .test = TestMossdspResampling_mossdsp_interpolatei_019, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_001", .test = TestMossdspResampling_mossdsp_interpolatef_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_002", .test = TestMossdspResampling_mossdsp_interpolatef_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_003", .test = TestMossdspResampling_mossdsp_interpolatef_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_004", .test = TestMossdspResampling_mossdsp_interpolatef_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_005", .test = TestMossdspResampling_mossdsp_interpolatef_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_006", .test = TestMossdspResampling_mossdsp_interpolatef_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_007", .test = TestMossdspResampling_mossdsp_interpolatef_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_008", .test = TestMossdspResampling_mossdsp_interpolatef_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_009", .test = TestMossdspResampling_mossdsp_interpolatef_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_010", .test = TestMossdspResampling_mossdsp_interpolatef_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_011", .test = TestMossdspResampling_mossdsp_interpolatef_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_012", .test = TestMossdspResampling_mossdsp_interpolatef_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_013", .test = TestMossdspResampling_mossdsp_interpolatef_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_014", .test = TestMossdspResampling_mossdsp_interpolatef_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_015", .test = TestMossdspResampling_mossdsp_interpolatef_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_016", .test = TestMossdspResampling_mossdsp_interpolatef_016, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_017", .test = TestMossdspResampling_mossdsp_interpolatef_017, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_018", .test = TestMossdspResampling_mossdsp_interpolatef_018, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_019", .test = TestMossdspResampling_mossdsp_interpolatef_019, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_020", .test = TestMossdspResampling_mossdsp_interpolatef_020, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_021", .test = TestMossdspResampling_mossdsp_interpolatef_021, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_022", .test = TestMossdspResampling_mossdsp_interpolatef_022, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_023", .test = TestMossdspResampling_mossdsp_interpolatef_023, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_024", .test = TestMossdspResampling_mossdsp_interpolatef_024, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_025", .test = TestMossdspResampling_mossdsp_interpolatef_025, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_026", .test = TestMossdspResampling_mossdsp_interpolatef_026, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_027", .test = TestMossdspResampling_mossdsp_interpolatef_027, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_028", .test = TestMossdspResampling_mossdsp_interpolatef_028, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_029", .test = TestMossdspResampling_mossdsp_interpolatef_029, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatef_030", .test = TestMossdspResampling_mossdsp_interpolatef_030, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_001", .test = TestMossdspResampling_mossdsp_interpolatev3i_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_002", .test = TestMossdspResampling_mossdsp_interpolatev3i_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_003", .test = TestMossdspResampling_mossdsp_interpolatev3i_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_004", .test = TestMossdspResampling_mossdsp_interpolatev3i_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_005", .test = TestMossdspResampling_mossdsp_interpolatev3i_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_006", .test = TestMossdspResampling_mossdsp_interpolatev3i_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_007", .test = TestMossdspResampling_mossdsp_interpolatev3i_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_008", .test = TestMossdspResampling_mossdsp_interpolatev3i_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_009", .test = TestMossdspResampling_mossdsp_interpolatev3i_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_010", .test = TestMossdspResampling_mossdsp_interpolatev3i_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_011", .test = TestMossdspResampling_mossdsp_interpolatev3i_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_012", .test = TestMossdspResampling_mossdsp_interpolatev3i_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_013", .test = TestMossdspResampling_mossdsp_interpolatev3i_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_014", .test = TestMossdspResampling_mossdsp_interpolatev3i_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_015", .test = TestMossdspResampling_mossdsp_interpolatev3i_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_016", .test = TestMossdspResampling_mossdsp_interpolatev3i_016, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_017", .test = TestMossdspResampling_mossdsp_interpolatev3i_017, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_018", .test = TestMossdspResampling_mossdsp_interpolatev3i_018, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_019", .test = TestMossdspResampling_mossdsp_interpolatev3i_019, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_020", .test = TestMossdspResampling_mossdsp_interpolatev3i_020, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_021", .test = TestMossdspResampling_mossdsp_interpolatev3i_021, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_022", .test = TestMossdspResampling_mossdsp_interpolatev3i_022, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_023", .test = TestMossdspResampling_mossdsp_interpolatev3i_023, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_024", .test = TestMossdspResampling_mossdsp_interpolatev3i_024, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_025", .test = TestMossdspResampling_mossdsp_interpolatev3i_025, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_026", .test = TestMossdspResampling_mossdsp_interpolatev3i_026, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_027", .test = TestMossdspResampling_mossdsp_interpolatev3i_027, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_028", .test = TestMossdspResampling_mossdsp_interpolatev3i_028, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_029", .test = TestMossdspResampling_mossdsp_interpolatev3i_029, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_030", .test = TestMossdspResampling_mossdsp_interpolatev3i_030, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_031", .test = TestMossdspResampling_mossdsp_interpolatev3i_031, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_032", .test = TestMossdspResampling_mossdsp_interpolatev3i_032, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_033", .test = TestMossdspResampling_mossdsp_interpolatev3i_033, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_034", .test = TestMossdspResampling_mossdsp_interpolatev3i_034, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_035", .test = TestMossdspResampling_mossdsp_interpolatev3i_035, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_036", .test = TestMossdspResampling_mossdsp_interpolatev3i_036, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_037", .test = TestMossdspResampling_mossdsp_interpolatev3i_037, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_038", .test = TestMossdspResampling_mossdsp_interpolatev3i_038, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_039", .test = TestMossdspResampling_mossdsp_interpolatev3i_039, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_040", .test = TestMossdspResampling_mossdsp_interpolatev3i_040, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3i_041", .test = TestMossdspResampling_mossdsp_interpolatev3i_041, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_001", .test = TestMossdspResampling_mossdsp_interpolatev3f_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_002", .test = TestMossdspResampling_mossdsp_interpolatev3f_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_003", .test = TestMossdspResampling_mossdsp_interpolatev3f_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_004", .test = TestMossdspResampling_mossdsp_interpolatev3f_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_005", .test = TestMossdspResampling_mossdsp_interpolatev3f_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_006", .test = TestMossdspResampling_mossdsp_interpolatev3f_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_007", .test = TestMossdspResampling_mossdsp_interpolatev3f_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_008", .test = TestMossdspResampling_mossdsp_interpolatev3f_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_009", .test = TestMossdspResampling_mossdsp_interpolatev3f_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_010", .test = TestMossdspResampling_mossdsp_interpolatev3f_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_011", .test = TestMossdspResampling_mossdsp_interpolatev3f_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_012", .test = TestMossdspResampling_mossdsp_interpolatev3f_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_013", .test = TestMossdspResampling_mossdsp_interpolatev3f_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_014", .test = TestMossdspResampling_mossdsp_interpolatev3f_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_015", .test = TestMossdspResampling_mossdsp_interpolatev3f_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_016", .test = TestMossdspResampling_mossdsp_interpolatev3f_016, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_017", .test = TestMossdspResampling_mossdsp_interpolatev3f_017, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_018", .test = TestMossdspResampling_mossdsp_interpolatev3f_018, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_019", .test = TestMossdspResampling_mossdsp_interpolatev3f_019, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_020", .test = TestMossdspResampling_mossdsp_interpolatev3f_020, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_021", .test = TestMossdspResampling_mossdsp_interpolatev3f_021, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3f_022", .test = TestMossdspResampling_mossdsp_interpolatev3f_022, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_001", .test = TestMossdspResampling_mossdsp_interpolatev3ti_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_002", .test = TestMossdspResampling_mossdsp_interpolatev3ti_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_003", .test = TestMossdspResampling_mossdsp_interpolatev3ti_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_004", .test = TestMossdspResampling_mossdsp_interpolatev3ti_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_005", .test = TestMossdspResampling_mossdsp_interpolatev3ti_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_006", .test = TestMossdspResampling_mossdsp_interpolatev3ti_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_007", .test = TestMossdspResampling_mossdsp_interpolatev3ti_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_008", .test = TestMossdspResampling_mossdsp_interpolatev3ti_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_009", .test = TestMossdspResampling_mossdsp_interpolatev3ti_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_010", .test = TestMossdspResampling_mossdsp_interpolatev3ti_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_011", .test = TestMossdspResampling_mossdsp_interpolatev3ti_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_012", .test = TestMossdspResampling_mossdsp_interpolatev3ti_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_013", .test = TestMossdspResampling_mossdsp_interpolatev3ti_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_014", .test = TestMossdspResampling_mossdsp_interpolatev3ti_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_015", .test = TestMossdspResampling_mossdsp_interpolatev3ti_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_016", .test = TestMossdspResampling_mossdsp_interpolatev3ti_016, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_017", .test = TestMossdspResampling_mossdsp_interpolatev3ti_017, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_018", .test = TestMossdspResampling_mossdsp_interpolatev3ti_018, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_019", .test = TestMossdspResampling_mossdsp_interpolatev3ti_019, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_020", .test = TestMossdspResampling_mossdsp_interpolatev3ti_020, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_021", .test = TestMossdspResampling_mossdsp_interpolatev3ti_021, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_022", .test = TestMossdspResampling_mossdsp_interpolatev3ti_022, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_023", .test = TestMossdspResampling_mossdsp_interpolatev3ti_023, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_024", .test = TestMossdspResampling_mossdsp_interpolatev3ti_024, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_025", .test = TestMossdspResampling_mossdsp_interpolatev3ti_025, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_026", .test = TestMossdspResampling_mossdsp_interpolatev3ti_026, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_027", .test = TestMossdspResampling_mossdsp_interpolatev3ti_027, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_028", .test = TestMossdspResampling_mossdsp_interpolatev3ti_028, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_029", .test = TestMossdspResampling_mossdsp_interpolatev3ti_029, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_030", .test = TestMossdspResampling_mossdsp_interpolatev3ti_030, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_031", .test = TestMossdspResampling_mossdsp_interpolatev3ti_031, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_032", .test = TestMossdspResampling_mossdsp_interpolatev3ti_032, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_033", .test = TestMossdspResampling_mossdsp_interpolatev3ti_033, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_034", .test = TestMossdspResampling_mossdsp_interpolatev3ti_034, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_035", .test = TestMossdspResampling_mossdsp_interpolatev3ti_035, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3ti_036", .test = TestMossdspResampling_mossdsp_interpolatev3ti_036, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_001", .test = TestMossdspResampling_mossdsp_interpolatev3tf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_002", .test = TestMossdspResampling_mossdsp_interpolatev3tf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_003", .test = TestMossdspResampling_mossdsp_interpolatev3tf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_004", .test = TestMossdspResampling_mossdsp_interpolatev3tf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_005", .test = TestMossdspResampling_mossdsp_interpolatev3tf_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_006", .test = TestMossdspResampling_mossdsp_interpolatev3tf_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_007", .test = TestMossdspResampling_mossdsp_interpolatev3tf_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_008", .test = TestMossdspResampling_mossdsp_interpolatev3tf_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_009", .test = TestMossdspResampling_mossdsp_interpolatev3tf_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_010", .test = TestMossdspResampling_mossdsp_interpolatev3tf_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_011", .test = TestMossdspResampling_mossdsp_interpolatev3tf_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolatev3tf_012", .test = TestMossdspResampling_mossdsp_interpolatev3tf_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_001", .test = TestMossdspResampling_mossdsp_interpolateqf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_002", .test = TestMossdspResampling_mossdsp_interpolateqf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_003", .test = TestMossdspResampling_mossdsp_interpolateqf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_004", .test = TestMossdspResampling_mossdsp_interpolateqf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_005", .test = TestMossdspResampling_mossdsp_interpolateqf_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_006", .test = TestMossdspResampling_mossdsp_interpolateqf_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_007", .test = TestMossdspResampling_mossdsp_interpolateqf_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_008", .test = TestMossdspResampling_mossdsp_interpolateqf_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_009", .test = TestMossdspResampling_mossdsp_interpolateqf_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_010", .test = TestMossdspResampling_mossdsp_interpolateqf_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_011", .test = TestMossdspResampling_mossdsp_interpolateqf_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_012", .test = TestMossdspResampling_mossdsp_interpolateqf_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_013", .test = TestMossdspResampling_mossdsp_interpolateqf_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_014", .test = TestMossdspResampling_mossdsp_interpolateqf_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_015", .test = TestMossdspResampling_mossdsp_interpolateqf_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_016", .test = TestMossdspResampling_mossdsp_interpolateqf_016, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_017", .test = TestMossdspResampling_mossdsp_interpolateqf_017, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_018", .test = TestMossdspResampling_mossdsp_interpolateqf_018, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_019", .test = TestMossdspResampling_mossdsp_interpolateqf_019, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_020", .test = TestMossdspResampling_mossdsp_interpolateqf_020, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_021", .test = TestMossdspResampling_mossdsp_interpolateqf_021, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_022", .test = TestMossdspResampling_mossdsp_interpolateqf_022, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_023", .test = TestMossdspResampling_mossdsp_interpolateqf_023, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_024", .test = TestMossdspResampling_mossdsp_interpolateqf_024, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_025", .test = TestMossdspResampling_mossdsp_interpolateqf_025, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqf_026", .test = TestMossdspResampling_mossdsp_interpolateqf_026, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_001", .test = TestMossdspResampling_mossdsp_interpolateqtf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_002", .test = TestMossdspResampling_mossdsp_interpolateqtf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_003", .test = TestMossdspResampling_mossdsp_interpolateqtf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_004", .test = TestMossdspResampling_mossdsp_interpolateqtf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_005", .test = TestMossdspResampling_mossdsp_interpolateqtf_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_006", .test = TestMossdspResampling_mossdsp_interpolateqtf_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_007", .test = TestMossdspResampling_mossdsp_interpolateqtf_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_008", .test = TestMossdspResampling_mossdsp_interpolateqtf_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_009", .test = TestMossdspResampling_mossdsp_interpolateqtf_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_010", .test = TestMossdspResampling_mossdsp_interpolateqtf_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_011", .test = TestMossdspResampling_mossdsp_interpolateqtf_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_012", .test = TestMossdspResampling_mossdsp_interpolateqtf_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_013", .test = TestMossdspResampling_mossdsp_interpolateqtf_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_014", .test = TestMossdspResampling_mossdsp_interpolateqtf_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_015", .test = TestMossdspResampling_mossdsp_interpolateqtf_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_016", .test = TestMossdspResampling_mossdsp_interpolateqtf_016, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_017", .test = TestMossdspResampling_mossdsp_interpolateqtf_017, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_018", .test = TestMossdspResampling_mossdsp_interpolateqtf_018, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_019", .test = TestMossdspResampling_mossdsp_interpolateqtf_019, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspResampling_mossdsp_interpolateqtf_020", .test = TestMossdspResampling_mossdsp_interpolateqtf_020, .ntimes = 1},
#endif

    };
    static PCU_Suite suite = {
        .name = "TestMossdspResampling",
        .tests = tests,
        .ntests = sizeof(tests) / sizeof(tests[0]),
        .setup = (void *)0, .teardown = (void *)0, .initialize = (void *)0, .cleanup = (void *)0
    };
    return &suite;
}
