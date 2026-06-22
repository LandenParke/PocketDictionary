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
#include "mossdsp_axis.c"
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


static void TestMossdspAxis_1_mossdsp_transformaxismv3i_001(void)
{
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = &param;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = &param;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = &param;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3s_t *out_data = 0;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = &param;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3s_t *out_data = 0;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = &param;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = 0;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = 0;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = 0;
struct sqmatrix3i_s  *param_data = 0;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
mossfw_data_v3s_t *out_data = 0;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = 0;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3s_t *out_data = 0;
mossfw_data_v3s_t *in_data = 0;
struct sqmatrix3i_s  *param_data = 0;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = 0;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 380;
expected_1[0].y = 434;
expected_1[0].z = 488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_015(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = &param_free;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 10000;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 50410;
expected_1[0].y = 614;
expected_1[0].z = 668;
expected_1[1].x = 0;
expected_1[1].y = 920;
expected_1[1].z = 1001;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_016(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = &param_free;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 10000;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 560;
expected_1[0].y = 50449;
expected_1[0].z = 668;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_1_mossdsp_transformaxismv3i_017(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3s_t out;
mossfw_data_v3s_t out_1[4];
mossfw_data_v3s_t in_0;
mossfw_data_v3s_t in[4];
mossfw_data_v3s_t expected;
mossfw_data_v3s_t expected_1[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3s_t *out_data = out_1;
mossfw_data_v3s_t *in_data = in;
struct sqmatrix3i_s  *param_data = &param_free;


in_0.x = 2;
in_0.y = 3;
in_0.z = 4;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out.x = 0;
out.y = 0;
out.z = 0;

out_1[0].x = 0;
out_1[0].y = 0;
out_1[0].z = 0;
out_1[1].x = 0;
out_1[1].y = 0;
out_1[1].z = 0;
out_1[2].x = 0;
out_1[2].y = 0;
out_1[2].z = 0;
out_1[3].x = 0;
out_1[3].y = 0;
out_1[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 10000;
param_free.z.y = 37;
param_free.z.z = 38;

expected.x = 191;
expected.y = 218;
expected.z = 245;

expected_1[0].x = 560;
expected_1[0].y = 614;
expected_1[0].z = 50488;
expected_1[1].x = 569;
expected_1[1].y = 650;
expected_1[1].z = 731;
expected_1[2].x = 758;
expected_1[2].y = 866;
expected_1[2].z = 974;
expected_1[3].x = 947;
expected_1[3].y = 1082;
expected_1[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)in_0;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3i(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_1[0],&expected_1[0],sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_001(void)
{
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3f_t *out_data = 0;
mossfw_data_v3f_t *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3f_t *out_data = 0;
mossfw_data_v3f_t *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = 0;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
mossfw_data_v3f_t *out_data = 0;
mossfw_data_v3f_t *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3f_t *out_data = 0;
mossfw_data_v3f_t *in_data = 0;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_2_mossdsp_transformaxismv3f_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_001(void)
{
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
struct vector3ia_s *out_data = out;
struct vector3ia_s *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3ia_s *out_data = out;
struct vector3ia_s *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
struct vector3ia_s *out_data = out;
struct vector3ia_s *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
struct vector3ia_s *out_data = 0;
struct vector3ia_s *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3ia_s *out_data = 0;
struct vector3ia_s *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
struct vector3ia_s *out_data = out;
struct vector3ia_s *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3ia_s *out_data = out;
struct vector3ia_s *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
struct vector3ia_s *out_data = out;
struct vector3ia_s *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3ia_s *out_data = out;
struct vector3ia_s *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3ia_s *out_data = out;
struct vector3ia_s *in_data = 0;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
struct vector3ia_s *out_data = 0;
struct vector3ia_s *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
struct vector3ia_s *out_data = out;
struct vector3ia_s *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
struct vector3ia_s *out_data = 0;
struct vector3ia_s *in_data = 0;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
struct vector3ia_s *out_data = out;
struct vector3ia_s *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_015(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3ia_s *out_data = &out[0];
struct vector3ia_s *in_data = &in[0];
struct sqmatrix3i_s  *param_data = &param_free;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 10000;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 50410;
expected_v[0].y = 614;
expected_v[0].z = 668;
expected_v[1].x = 0;
expected_v[1].y = 920;
expected_v[1].z = 1001;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_016(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3ia_s *out_data = &out[0];
struct vector3ia_s *in_data = &in[0];
struct sqmatrix3i_s  *param_data = &param_free;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 10000;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 560;
expected_v[0].y = 50449;
expected_v[0].z = 668;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_017(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3ia_s *out_data = &out[0];
struct vector3ia_s *in_data = &in[0];
struct sqmatrix3i_s  *param_data = &param_free;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 10000;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 560;
expected_v[0].y = 614;
expected_v[0].z = 50488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_3_mossdsp_transformaxismv3ia_018(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3ia_s out[4];
struct vector3ia_s in[4];
struct vector3ia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3ia_s *out_data = &out[0];
struct vector3ia_s *in_data = &in[0];
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3s_t out_v[4];
mossfw_data_v3s_t in_v[4];
mossfw_data_v3s_t expected_v[4];

in_v[0].x = -5;
in_v[0].y = -6;
in_v[0].z = -7;
in_v[1].x = -8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = -20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = -180;
expected_v[0].y = -434;
expected_v[0].z = -488;
expected_v[1].x = 569;
expected_v[1].y = 282;
expected_v[1].z = 315;
expected_v[2].x = 318;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 387;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3s_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_001(void)
{
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
struct vector3fa_s *out_data = 0;
struct vector3fa_s *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
struct vector3fa_s *out_data = 0;
struct vector3fa_s *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = 0;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
struct vector3fa_s *out_data = 0;
struct vector3fa_s *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
struct vector3fa_s *out_data = 0;
struct vector3fa_s *in_data = 0;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_4_mossdsp_transformaxismv3fa_015(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
struct vector3fa_s *out_data = &out[0];
struct vector3fa_s *in_data = &in[0];
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t expected_v[4];

in_v[0].x = -5;
in_v[0].y = -6;
in_v[0].z = -7;
in_v[1].x = -8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = -20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = -180;
expected_v[0].y = -434;
expected_v[0].z = -488;
expected_v[1].x = 569;
expected_v[1].y = 282;
expected_v[1].z = 315;
expected_v[2].x = 318;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 387;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_001(void)
{
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3ts_t  *out_data = 0;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3ts_t  *out_data = 0;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = 0;
struct sqmatrix3i_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
mossfw_data_v3ts_t  *out_data = 0;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3ts_t  *out_data = 0;
mossfw_data_v3ts_t  *in_data = 0;
struct sqmatrix3i_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_015(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = &param_free;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 10000;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 50410;
expected[0].y = 614;
expected[0].z = 668;
expected[1].x = 0;
expected[1].y = 920;
expected[1].z = 1001;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_016(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = &param_free;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 10000;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 560;
expected[0].y = 50449;
expected[0].z = 668;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_5_mosdsp_transformaxismv3ti_017(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3ts_t  out[4];
mossfw_data_v3ts_t  in[4];
mossfw_data_v3ts_t  expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3ts_t  *out_data = out;
mossfw_data_v3ts_t  *in_data = in;
struct sqmatrix3i_s  *param_data = &param_free;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 10000;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 560;
expected[0].y = 614;
expected[0].z = 50488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3ti(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3s_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_001(void)
{
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3tf_t *out_data = 0;
mossfw_data_v3tf_t *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3tf_t *out_data = 0;
mossfw_data_v3tf_t *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = 0;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
mossfw_data_v3tf_t *out_data = 0;
mossfw_data_v3tf_t *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
mossfw_data_v3tf_t *out_data = 0;
mossfw_data_v3tf_t *in_data = 0;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_6_mossdsp_transformaxismv3tf_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;

out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;

expected[0].x = 380;
expected[0].y = 434;
expected[0].z = 488;
expected[1].x = 569;
expected[1].y = 650;
expected[1].z = 731;
expected[2].x = 758;
expected[2].y = 866;
expected[2].z = 974;
expected[3].x = 947;
expected[3].y = 1082;
expected[3].z = 1217;

in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_001(void)
{
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
struct vector3tia_s *out_data = out;
struct vector3tia_s *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3tia_s *out_data = out;
struct vector3tia_s *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
struct vector3tia_s *out_data = out;
struct vector3tia_s *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
struct vector3tia_s *out_data = 0;
struct vector3tia_s *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3tia_s *out_data = 0;
struct vector3tia_s *in_data = in;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
struct vector3tia_s *out_data = out;
struct vector3tia_s *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3tia_s *out_data = out;
struct vector3tia_s *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
struct vector3tia_s *out_data = out;
struct vector3tia_s *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3tia_s *out_data = out;
struct vector3tia_s *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3tia_s *out_data = out;
struct vector3tia_s *in_data = 0;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
struct vector3tia_s *out_data = 0;
struct vector3tia_s *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
struct vector3tia_s *out_data = out;
struct vector3tia_s *in_data = 0;
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_1;
struct vector3tia_s *out_data = 0;
struct vector3tia_s *in_data = 0;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = 0;
struct vector3tia_s *out_data = out;
struct vector3tia_s *in_data = in;
struct sqmatrix3i_s  *param_data = 0;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_015(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3tia_s *out_data = &out[0];
struct vector3tia_s *in_data = &in[0];
struct sqmatrix3i_s  *param_data = &param_free;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 10000;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 50410;
expected_v[0].y = 614;
expected_v[0].z = 668;
expected_v[1].x = 0;
expected_v[1].y = 920;
expected_v[1].z = 1001;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_016(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3tia_s *out_data = &out[0];
struct vector3tia_s *in_data = &in[0];
struct sqmatrix3i_s  *param_data = &param_free;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 10000;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 560;
expected_v[0].y = 50449;
expected_v[0].z = 668;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_017(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3tia_s *out_data = &out[0];
struct vector3tia_s *in_data = &in[0];
struct sqmatrix3i_s  *param_data = &param_free;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 10000;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 560;
expected_v[0].y = 614;
expected_v[0].z = 50488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_7_mossdsp_transformaxismv3tia_018(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tia_s out[4];
struct vector3tia_s in[4];
struct vector3tia_s expected[4];
struct sqmatrix3i_s  param;
struct sqmatrix3i_s  param_free;
int ret;

int num = num_0;
struct vector3tia_s *out_data = &out[0];
struct vector3tia_s *in_data = &in[0];
struct sqmatrix3i_s  *param_data = &param;

mossfw_data_v3ts_t  out_v[4];
mossfw_data_v3ts_t  in_v[4];
mossfw_data_v3ts_t  expected_v[4];

in_v[0].x = -5;
in_v[0].y = -6;
in_v[0].z = -7;
in_v[1].x = -8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = -20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = -180;
expected_v[0].y = -434;
expected_v[0].z = -488;
expected_v[1].x = 569;
expected_v[1].y = 282;
expected_v[1].z = 315;
expected_v[2].x = 318;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 387;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;



in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tia(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3ts_t ),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_001(void)
{
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
struct vector3tfa_s *out_data = 0;
struct vector3tfa_s *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
struct vector3tfa_s *out_data = 0;
struct vector3tfa_s *in_data = in;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = 0;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
struct vector3tfa_s *out_data = 0;
struct vector3tfa_s *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = 0;
struct sqmatrix3f_s  *param_data = &param;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = num_1;
struct vector3tfa_s *out_data = 0;
struct vector3tfa_s *in_data = 0;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_8_mossdsp_transformaxismv3tfa_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
struct sqmatrix3f_s  param;
struct sqmatrix3f_s  param_free;
int ret;

int num = 0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
struct sqmatrix3f_s  *param_data = 0;

mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t expected_v[4];

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;

out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.x.x = 20;
param.x.y = 21;
param.x.z = 22;
param.y.x = 23;
param.y.y = 24;
param.y.z = 25;
param.z.x = 26;
param.z.y = 27;
param.z.z = 28;

param_free.x.x = 30;
param_free.x.y = 31;
param_free.x.z = 32;
param_free.y.x = 33;
param_free.y.y = 34;
param_free.y.z = 35;
param_free.z.x = 36;
param_free.z.y = 37;
param_free.z.z = 38;


expected_v[0].x = 380;
expected_v[0].y = 434;
expected_v[0].z = 488;
expected_v[1].x = 569;
expected_v[1].y = 650;
expected_v[1].z = 731;
expected_v[2].x = 758;
expected_v[2].y = 866;
expected_v[2].z = 974;
expected_v[3].x = 947;
expected_v[3].y = 1082;
expected_v[3].z = 1217;


in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;


out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x;
expected[0].y = &expected_v[0].y;
expected[0].z = &expected_v[0].z;
expected[1].x = &expected_v[1].x;
expected[1].y = &expected_v[1].y;
expected[1].z = &expected_v[1].z;
expected[2].x = &expected_v[2].x;
expected[2].y = &expected_v[2].y;
expected[2].z = &expected_v[2].z;
expected[3].x = &expected_v[3].x;
expected[3].y = &expected_v[3].y;
expected[3].z = &expected_v[3].z;
in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;
out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;
expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;
(void)param;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxismv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_001(void)
{
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = num_1;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = num_0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = 0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = num_1;
mossfw_data_v3f_t *out_data = 0;
mossfw_data_v3f_t *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = num_0;
mossfw_data_v3f_t *out_data = 0;
mossfw_data_v3f_t *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = num_1;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = num_0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = num_1;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = num_0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = num_0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = 0;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = 0;
mossfw_data_v3f_t *out_data = 0;
mossfw_data_v3f_t *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = 0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = num_1;
mossfw_data_v3f_t *out_data = 0;
mossfw_data_v3f_t *in_data = 0;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_9_mossdsp_transformaxisqv3f_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3f_t out[4];
mossfw_data_v3f_t in[4];
mossfw_data_v3f_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_k;
mossfw_data_qf_t  param_free;
int ret;

int num = 0;
mossfw_data_v3f_t *out_data = out;
mossfw_data_v3f_t *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_k.w = 21;
param_k.x = -22;
param_k.y = -23;
param_k.z = -24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x = param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y = param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x = param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y = param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x = param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y = param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x = param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y = param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;


expected[0].x = qx[0].x * param_k.w + qx[0].w * param_k.x + qx[0].y * param_k.z - qx[0].z * param_k.y;;
expected[0].y = qx[0].w * param_k.y + qx[0].y * param_k.w + qx[0].z * param_k.x - qx[0].x * param_k.z;;
expected[0].z = qx[0].w * param_k.z + qx[0].z * param_k.w + qx[0].x * param_k.y - qx[0].y * param_k.x;;
expected[1].x = qx[1].x * param_k.w + qx[1].w * param_k.x + qx[1].y * param_k.z - qx[1].z * param_k.y;;
expected[1].y = qx[1].w * param_k.y + qx[1].y * param_k.w + qx[1].z * param_k.x - qx[1].x * param_k.z;;
expected[1].z = qx[1].w * param_k.z + qx[1].z * param_k.w + qx[1].x * param_k.y - qx[1].y * param_k.x;;
expected[2].x = qx[2].x * param_k.w + qx[2].w * param_k.x + qx[2].y * param_k.z - qx[2].z * param_k.y;;
expected[2].y = qx[2].w * param_k.y + qx[2].y * param_k.w + qx[2].z * param_k.x - qx[2].x * param_k.z;;
expected[2].z = qx[2].w * param_k.z + qx[2].z * param_k.w + qx[2].x * param_k.y - qx[2].y * param_k.x;;
expected[3].x = qx[3].x * param_k.w + qx[3].w * param_k.x + qx[3].y * param_k.z - qx[3].z * param_k.y;;
expected[3].y = qx[3].w * param_k.y + qx[3].y * param_k.w + qx[3].z * param_k.x - qx[3].x * param_k.z;;
expected[3].z = qx[3].w * param_k.z + qx[3].z * param_k.w + qx[3].x * param_k.y - qx[3].y * param_k.x;;
(void)param_free;
(void)num_0;
(void)num_1;






if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3f(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_001(void)
{
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = num_1;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_10_transform_quaternion_vfa_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = num_0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = 0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = num_1;
struct vector3fa_s *out_data = 0;
struct vector3fa_s *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = num_0;
struct vector3fa_s *out_data = 0;
struct vector3fa_s *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = num_1;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = num_0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = num_1;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = num_0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = num_0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = 0;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = 0;
struct vector3fa_s *out_data = 0;
struct vector3fa_s *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = 0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = num_1;
struct vector3fa_s *out_data = 0;
struct vector3fa_s *in_data = 0;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_10_transform_quaternion_vfa_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3fa_s out[4];
struct vector3fa_s in[4];
struct vector3fa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3f_t in_v[4];
mossfw_data_v3f_t out_v[4];
mossfw_data_v3f_t expected_v[4];


int num = 0;
struct vector3fa_s *out_data = out;
struct vector3fa_s *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3fa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3f_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_001(void)
{
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = num_1;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = num_0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = 0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = num_1;
mossfw_data_v3tf_t *out_data = 0;
mossfw_data_v3tf_t *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = num_0;
mossfw_data_v3tf_t *out_data = 0;
mossfw_data_v3tf_t *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = num_1;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = num_0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = num_1;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = num_0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = num_0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = 0;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = 0;
mossfw_data_v3tf_t *out_data = 0;
mossfw_data_v3tf_t *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = 0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = num_1;
mossfw_data_v3tf_t *out_data = 0;
mossfw_data_v3tf_t *in_data = 0;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_11_transform_quaternion_v3tf_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
mossfw_data_v3tf_t out[4];
mossfw_data_v3tf_t in[4];
mossfw_data_v3tf_t expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

int num = 0;
mossfw_data_v3tf_t *out_data = out;
mossfw_data_v3tf_t *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in[0].x = 5;
in[0].y = 6;
in[0].z = 7;
in[1].x = 8;
in[1].y = 9;
in[1].z = 10;
in[2].x = 11;
in[2].y = 12;
in[2].z = 13;
in[3].x = 14;
in[3].y = 15;
in[3].z = 16;


out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in[0].x - param.y * in[0].y - param.z * in[0].z;;
qx[0].x =  param.w * in[0].x + param.y * in[0].z - param.z * in[0].y;;
qx[0].y =  param.w * in[0].y + param.z * in[0].x - param.x * in[0].z;;
qx[0].z =  param.w * in[0].z + param.x * in[0].y - param.y * in[0].x;;
qx[1].w = -param.x * in[1].x - param.y * in[1].y - param.z * in[1].z;;
qx[1].x =  param.w * in[1].x + param.y * in[1].z - param.z * in[1].y;;
qx[1].y =  param.w * in[1].y + param.z * in[1].x - param.x * in[1].z;;
qx[1].z =  param.w * in[1].z + param.x * in[1].y - param.y * in[1].x;;
qx[2].w = -param.x * in[2].x - param.y * in[2].y - param.z * in[2].z;;
qx[2].x =  param.w * in[2].x + param.y * in[2].z - param.z * in[2].y;;
qx[2].y =  param.w * in[2].y + param.z * in[2].x - param.x * in[2].z;;
qx[2].z =  param.w * in[2].z + param.x * in[2].y - param.y * in[2].x;;
qx[3].w = -param.x * in[3].x - param.y * in[3].y - param.z * in[3].z;;
qx[3].x =  param.w * in[3].x + param.y * in[3].z - param.z * in[3].y;;
qx[3].y =  param.w * in[3].y + param.z * in[3].x - param.x * in[3].z;;
qx[3].z =  param.w * in[3].z + param.x * in[3].y - param.y * in[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;
in[0].t = 111;
in[1].t = 112;
in[2].t = 113;
in[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;


expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)param_free;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tf(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_001(void)
{
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = num_1;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


endsystimer(__func__);
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_002(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = num_0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_003(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = 0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_004(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = num_1;
struct vector3tfa_s *out_data = 0;
struct vector3tfa_s *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_005(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = num_0;
struct vector3tfa_s *out_data = 0;
struct vector3tfa_s *in_data = in;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_006(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = num_1;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_007(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = num_0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_008(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = num_1;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_009(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = num_0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_010(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = num_0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = 0;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_011(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = 0;
struct vector3tfa_s *out_data = 0;
struct vector3tfa_s *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_012(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = 0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = 0;
mossfw_data_qf_t  *param_data = &param;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_013(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = num_1;
struct vector3tfa_s *out_data = 0;
struct vector3tfa_s *in_data = 0;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_12_transform_quaternion_v3tfa_014(void)
{
#ifdef UNITTEST
int num_0 = 1;
int num_1 = 4;
struct vector3tfa_s out[4];
struct vector3tfa_s in[4];
struct vector3tfa_s expected[4];
mossfw_data_qf_t  param;
mossfw_data_qf_t  param_free;
int ret;

mossfw_data_v3tf_t in_v[4];
mossfw_data_v3tf_t out_v[4];
mossfw_data_v3tf_t expected_v[4];


int num = 0;
struct vector3tfa_s *out_data = out;
struct vector3tfa_s *in_data = in;
mossfw_data_qf_t  *param_data = 0;

in_v[0].x = 5;
in_v[0].y = 6;
in_v[0].z = 7;
in_v[1].x = 8;
in_v[1].y = 9;
in_v[1].z = 10;
in_v[2].x = 11;
in_v[2].y = 12;
in_v[2].z = 13;
in_v[3].x = 14;
in_v[3].y = 15;
in_v[3].z = 16;




out_v[0].x = 0;
out_v[0].y = 0;
out_v[0].z = 0;
out_v[1].x = 0;
out_v[1].y = 0;
out_v[1].z = 0;
out_v[2].x = 0;
out_v[2].y = 0;
out_v[2].z = 0;
out_v[3].x = 0;
out_v[3].y = 0;
out_v[3].z = 0;

param.w = 21;
param.x = 22;
param.y = 23;
param.z = 24;

param_free.w = 31;
param_free.x = 32;
param_free.y = 33;
param_free.z = 34;


mossfw_data_qf_t  qx[4];

qx[0].w = -param.x * in_v[0].x - param.y * in_v[0].y - param.z * in_v[0].z;;
qx[0].x =  param.w * in_v[0].x + param.y * in_v[0].z - param.z * in_v[0].y;;
qx[0].y =  param.w * in_v[0].y + param.z * in_v[0].x - param.x * in_v[0].z;;
qx[0].z =  param.w * in_v[0].z + param.x * in_v[0].y - param.y * in_v[0].x;;
qx[1].w = -param.x * in_v[1].x - param.y * in_v[1].y - param.z * in_v[1].z;;
qx[1].x =  param.w * in_v[1].x + param.y * in_v[1].z - param.z * in_v[1].y;;
qx[1].y =  param.w * in_v[1].y + param.z * in_v[1].x - param.x * in_v[1].z;;
qx[1].z =  param.w * in_v[1].z + param.x * in_v[1].y - param.y * in_v[1].x;;
qx[2].w = -param.x * in_v[2].x - param.y * in_v[2].y - param.z * in_v[2].z;;
qx[2].x =  param.w * in_v[2].x + param.y * in_v[2].z - param.z * in_v[2].y;;
qx[2].y =  param.w * in_v[2].y + param.z * in_v[2].x - param.x * in_v[2].z;;
qx[2].z =  param.w * in_v[2].z + param.x * in_v[2].y - param.y * in_v[2].x;;
qx[3].w = -param.x * in_v[3].x - param.y * in_v[3].y - param.z * in_v[3].z;;
qx[3].x =  param.w * in_v[3].x + param.y * in_v[3].z - param.z * in_v[3].y;;
qx[3].y =  param.w * in_v[3].y + param.z * in_v[3].x - param.x * in_v[3].z;;
qx[3].z =  param.w * in_v[3].z + param.x * in_v[3].y - param.y * in_v[3].x;;

mossfw_data_qf_t  q;

q.w = 21;
q.x = -22;
q.y = -23;
q.z = -24;

expected_v[0].x = qx[0].x * q.w + qx[0].w * q.x + qx[0].y * q.z - qx[0].z * q.y;;
expected_v[0].y = qx[0].w * q.y + qx[0].y * q.w + qx[0].z * q.x - qx[0].x * q.z;;
expected_v[0].z = qx[0].w * q.z + qx[0].z * q.w + qx[0].x * q.y - qx[0].y * q.x;;
expected_v[1].x = qx[1].x * q.w + qx[1].w * q.x + qx[1].y * q.z - qx[1].z * q.y;;
expected_v[1].y = qx[1].w * q.y + qx[1].y * q.w + qx[1].z * q.x - qx[1].x * q.z;;
expected_v[1].z = qx[1].w * q.z + qx[1].z * q.w + qx[1].x * q.y - qx[1].y * q.x;;
expected_v[2].x = qx[2].x * q.w + qx[2].w * q.x + qx[2].y * q.z - qx[2].z * q.y;;
expected_v[2].y = qx[2].w * q.y + qx[2].y * q.w + qx[2].z * q.x - qx[2].x * q.z;;
expected_v[2].z = qx[2].w * q.z + qx[2].z * q.w + qx[2].x * q.y - qx[2].y * q.x;;
expected_v[3].x = qx[3].x * q.w + qx[3].w * q.x + qx[3].y * q.z - qx[3].z * q.y;;
expected_v[3].y = qx[3].w * q.y + qx[3].y * q.w + qx[3].z * q.x - qx[3].x * q.z;;
expected_v[3].z = qx[3].w * q.z + qx[3].z * q.w + qx[3].x * q.y - qx[3].y * q.x;;



in[0].x = &in_v[0].x;
in[0].y = &in_v[0].y;
in[0].z = &in_v[0].z;
in[1].x = &in_v[1].x;
in[1].y = &in_v[1].y;
in[1].z = &in_v[1].z;
in[2].x = &in_v[2].x;
in[2].y = &in_v[2].y;
in[2].z = &in_v[2].z;
in[3].x = &in_v[3].x;
in[3].y = &in_v[3].y;
in[3].z = &in_v[3].z;

out[0].x = &out_v[0].x;
out[0].y = &out_v[0].y;
out[0].z = &out_v[0].z;
out[1].x = &out_v[1].x;
out[1].y = &out_v[1].y;
out[1].z = &out_v[1].z;
out[2].x = &out_v[2].x;
out[2].y = &out_v[2].y;
out[2].z = &out_v[2].z;
out[3].x = &out_v[3].x;
out[3].y = &out_v[3].y;
out[3].z = &out_v[3].z;

expected[0].x = &expected_v[0].x ;
expected[0].y = &expected_v[0].y ;
expected[0].z = &expected_v[0].z ;
expected[1].x = &expected_v[1].x ;
expected[1].y = &expected_v[1].y ;
expected[1].z = &expected_v[1].z ;
expected[2].x = &expected_v[2].x ;
expected[2].y = &expected_v[2].y ;
expected[2].z = &expected_v[2].z ;
expected[3].x = &expected_v[3].x ;
expected[3].y = &expected_v[3].y ;
expected[3].z = &expected_v[3].z ;


in_v[0].t = 111;
in_v[1].t = 112;
in_v[2].t = 113;
in_v[3].t = 114;

in[0].t = &in_v[0].t;
in[1].t = &in_v[1].t;
in[2].t = &in_v[2].t;
in[3].t = &in_v[3].t;



out_v[0].t = 0;
out_v[1].t = 0;
out_v[2].t = 0;
out_v[3].t = 0;

out[0].t = &out_v[0].t;
out[1].t = &out_v[1].t;
out[2].t = &out_v[2].t;
out[3].t = &out_v[3].t;



expected_v[0].t = 111;
expected_v[1].t = 112;
expected_v[2].t = 113;
expected_v[3].t = 114;

expected[0].t = &expected_v[0].t;
expected[1].t = &expected_v[1].t;
expected[2].t = &expected_v[2].t;
expected[3].t = &expected_v[3].t;
(void)param_free;
(void)expected;
(void)in;
(void)out;
(void)num_0;
(void)num_1;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformaxisqv3tfa(out_data,in_data,num,param_data);


}
PCU_ASSERT_MEMORY_EQUAL(&out_v,&expected_v,sizeof(mossfw_data_v3tf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspAxis_overflowv3i_001(void)
{

struct transformaxis_v3i64_s in = {
    .x = 0,
    .y = 0,
    .z = 0
};
int b;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

b = overflowv3i(in);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT(b == 0);



beginsystimer();

b = overflowv3i(in);


endsystimer(__func__);
beginsystimer();

b = overflowv3i(in);


endsystimer(__func__);
}

static void TestMossdspAxis_overflowv3i_002(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = (int64_t)INT16_MAX + 1,
    .y = 0,
    .z = 0
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_003(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = (int64_t)INT16_MIN - 1,
    .y = 0,
    .z = 0
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_004(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = 0,
    .y = (int64_t)INT16_MAX + 1,
    .z = 0
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_005(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = 0,
    .y = (int64_t)INT16_MIN - 1,
    .z = 0
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_006(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = 0,
    .y = 0,
    .z = (int64_t)INT16_MAX + 1
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_007(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = 0,
    .y = 0,
    .z = (int64_t)INT16_MIN - 1
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_008(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = (int64_t)INT16_MAX + 1,
    .y = (int64_t)INT16_MAX + 1,
    .z = 0
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_009(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = (int64_t)INT16_MIN - 1,
    .y = (int64_t)INT16_MAX + 1,
    .z = (int64_t)INT16_MIN - 1
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_010(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = (int64_t)INT16_MAX + 1,
    .y = (int64_t)INT16_MIN - 1,
    .z = (int64_t)INT16_MAX + 1
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_011(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = (int64_t)INT16_MAX + 1,
    .y = 0,
    .z = (int64_t)INT16_MIN - 1
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_012(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = 0,
    .y = (int64_t)INT16_MIN - 1,
    .z = (int64_t)INT16_MIN - 1
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_013(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = (int64_t)INT16_MIN - 1,
    .y = (int64_t)INT16_MIN - 1,
    .z = (int64_t)INT16_MAX + 1
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}

static void TestMossdspAxis_overflowv3i_014(void)
{
#ifdef UNITTEST

struct transformaxis_v3i64_s in = {
    .x = 0,
    .y = (int64_t)INT16_MAX + 1,
    .z = (int64_t)INT16_MAX + 1
};
int b;


if (setjmp(g_testCaseEnv) == 0) {

b = overflowv3i(in);


}

PCU_ASSERT(b != 0);


#endif
}


PCU_Suite* TestMossdspAxis(void)
{
    static PCU_Test tests[] = {

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_001", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_002", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_003", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_004", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_005", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_006", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_007", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_008", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_009", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_010", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_011", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_012", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_013", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_014", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_015", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_016", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_016, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_1_mossdsp_transformaxismv3i_017", .test = TestMossdspAxis_1_mossdsp_transformaxismv3i_017, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_001", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_002", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_003", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_004", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_005", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_006", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_007", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_008", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_009", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_010", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_011", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_012", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_013", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_2_mossdsp_transformaxismv3f_014", .test = TestMossdspAxis_2_mossdsp_transformaxismv3f_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_001", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_002", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_003", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_004", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_005", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_006", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_007", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_008", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_009", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_010", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_011", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_012", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_013", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_014", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_015", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_016", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_016, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_017", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_017, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_3_mossdsp_transformaxismv3ia_018", .test = TestMossdspAxis_3_mossdsp_transformaxismv3ia_018, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_001", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_002", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_003", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_004", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_005", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_006", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_007", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_008", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_009", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_010", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_011", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_012", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_013", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_014", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_4_mossdsp_transformaxismv3fa_015", .test = TestMossdspAxis_4_mossdsp_transformaxismv3fa_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_001", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_002", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_003", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_004", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_005", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_006", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_007", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_008", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_009", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_010", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_011", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_012", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_013", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_014", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_015", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_016", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_016, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_5_mosdsp_transformaxismv3ti_017", .test = TestMossdspAxis_5_mosdsp_transformaxismv3ti_017, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_001", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_002", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_003", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_004", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_005", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_006", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_007", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_008", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_009", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_010", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_011", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_012", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_013", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_6_mossdsp_transformaxismv3tf_014", .test = TestMossdspAxis_6_mossdsp_transformaxismv3tf_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_001", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_002", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_003", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_004", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_005", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_006", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_007", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_008", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_009", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_010", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_011", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_012", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_013", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_014", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_015", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_015, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_016", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_016, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_017", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_017, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_7_mossdsp_transformaxismv3tia_018", .test = TestMossdspAxis_7_mossdsp_transformaxismv3tia_018, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_001", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_002", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_003", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_004", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_005", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_006", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_007", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_008", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_009", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_010", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_011", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_012", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_013", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_8_mossdsp_transformaxismv3tfa_014", .test = TestMossdspAxis_8_mossdsp_transformaxismv3tfa_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_001", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_002", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_003", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_004", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_005", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_006", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_007", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_008", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_009", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_010", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_011", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_012", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_013", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_9_mossdsp_transformaxisqv3f_014", .test = TestMossdspAxis_9_mossdsp_transformaxisqv3f_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_001", .test = TestMossdspAxis_10_transform_quaternion_vfa_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_002", .test = TestMossdspAxis_10_transform_quaternion_vfa_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_003", .test = TestMossdspAxis_10_transform_quaternion_vfa_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_004", .test = TestMossdspAxis_10_transform_quaternion_vfa_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_005", .test = TestMossdspAxis_10_transform_quaternion_vfa_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_006", .test = TestMossdspAxis_10_transform_quaternion_vfa_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_007", .test = TestMossdspAxis_10_transform_quaternion_vfa_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_008", .test = TestMossdspAxis_10_transform_quaternion_vfa_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_009", .test = TestMossdspAxis_10_transform_quaternion_vfa_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_010", .test = TestMossdspAxis_10_transform_quaternion_vfa_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_011", .test = TestMossdspAxis_10_transform_quaternion_vfa_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_012", .test = TestMossdspAxis_10_transform_quaternion_vfa_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_013", .test = TestMossdspAxis_10_transform_quaternion_vfa_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_10_transform_quaternion_vfa_014", .test = TestMossdspAxis_10_transform_quaternion_vfa_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_001", .test = TestMossdspAxis_11_transform_quaternion_v3tf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_002", .test = TestMossdspAxis_11_transform_quaternion_v3tf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_003", .test = TestMossdspAxis_11_transform_quaternion_v3tf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_004", .test = TestMossdspAxis_11_transform_quaternion_v3tf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_005", .test = TestMossdspAxis_11_transform_quaternion_v3tf_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_006", .test = TestMossdspAxis_11_transform_quaternion_v3tf_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_007", .test = TestMossdspAxis_11_transform_quaternion_v3tf_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_008", .test = TestMossdspAxis_11_transform_quaternion_v3tf_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_009", .test = TestMossdspAxis_11_transform_quaternion_v3tf_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_010", .test = TestMossdspAxis_11_transform_quaternion_v3tf_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_011", .test = TestMossdspAxis_11_transform_quaternion_v3tf_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_012", .test = TestMossdspAxis_11_transform_quaternion_v3tf_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_013", .test = TestMossdspAxis_11_transform_quaternion_v3tf_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_11_transform_quaternion_v3tf_014", .test = TestMossdspAxis_11_transform_quaternion_v3tf_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_001", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_002", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_003", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_004", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_005", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_006", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_007", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_008", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_009", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_010", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_011", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_012", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_013", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_12_transform_quaternion_v3tfa_014", .test = TestMossdspAxis_12_transform_quaternion_v3tfa_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_001", .test = TestMossdspAxis_overflowv3i_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_002", .test = TestMossdspAxis_overflowv3i_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_003", .test = TestMossdspAxis_overflowv3i_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_004", .test = TestMossdspAxis_overflowv3i_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_005", .test = TestMossdspAxis_overflowv3i_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_006", .test = TestMossdspAxis_overflowv3i_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_007", .test = TestMossdspAxis_overflowv3i_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_008", .test = TestMossdspAxis_overflowv3i_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_009", .test = TestMossdspAxis_overflowv3i_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_010", .test = TestMossdspAxis_overflowv3i_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_011", .test = TestMossdspAxis_overflowv3i_011, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_012", .test = TestMossdspAxis_overflowv3i_012, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_013", .test = TestMossdspAxis_overflowv3i_013, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspAxis_overflowv3i_014", .test = TestMossdspAxis_overflowv3i_014, .ntimes = 1},
#endif

    };
    static PCU_Suite suite = {
        .name = "TestMossdspAxis",
        .tests = tests,
        .ntests = sizeof(tests) / sizeof(tests[0]),
        .setup = (void *)0, .teardown = (void *)0, .initialize = (void *)0, .cleanup = (void *)0
    };
    return &suite;
}
