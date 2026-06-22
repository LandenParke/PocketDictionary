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


static void TestMossdspRot_5_mossdsp_transformqanglesf_001(void)
{
int num1 = 1;
int num4 = 4;

mossfw_data_v3f_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
};
mossfw_data_qf_t in[4];
int ret;
float epsilon;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;
(void)num1;
(void)num4;
(void)in;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_transformqanglesf(out,
                                          in,
                                          num4);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(1.0f - epsilon < out[0].y && out[0].y < 1.0f + epsilon);
PCU_ASSERT(0.5f - epsilon < out[0].z && out[0].z < 0.5f + epsilon);
PCU_ASSERT(1.0f - epsilon < out[1].x && out[1].x < 1.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(1.0f - epsilon < out[2].y && out[2].y < 1.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(1.0f - epsilon < out[3].z && out[3].z < 1.0f + epsilon);



beginsystimer();

ret = mossdsp_transformqanglesf(out,
                                          in,
                                          num4);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_transformqanglesf(out,
                                          in,
                                          num4);


endsystimer(__func__);
}

static void TestMossdspRot_5_mossdsp_transformqanglesf_002(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;

mossfw_data_v3f_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
};
mossfw_data_qf_t in[4];
int ret;
float epsilon;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglesf(out,
                                          in,
                                          num1);


}

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(1.0f - epsilon < out[0].y && out[0].y < 1.0f + epsilon);
PCU_ASSERT(0.5f - epsilon < out[0].z && out[0].z < 0.5f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_5_mossdsp_transformqanglesf_003(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;

mossfw_data_v3f_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
};
mossfw_data_qf_t in[4];
int ret;
float epsilon;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglesf(out,
                                          in,
                                          0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_5_mossdsp_transformqanglesf_004(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;

mossfw_data_v3f_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
};
mossfw_data_qf_t in[4];
int ret;
float epsilon;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglesf(out,
                                          in,
                                          0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_5_mossdsp_transformqanglesf_005(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;

mossfw_data_v3f_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
};
mossfw_data_qf_t in[4];
int ret;
float epsilon;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglesf(out,
                                          0,
                                          num4);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_5_mossdsp_transformqanglesf_006(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;

mossfw_data_v3f_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
};
mossfw_data_qf_t in[4];
int ret;
float epsilon;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglesf(out,
                                          0,
                                          num1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_5_mossdsp_transformqanglesf_007(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;

mossfw_data_v3f_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
};
mossfw_data_qf_t in[4];
int ret;
float epsilon;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglesf(0,
                                          in,
                                          num4);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_5_mossdsp_transformqanglesf_008(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;

mossfw_data_v3f_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
};
mossfw_data_qf_t in[4];
int ret;
float epsilon;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglesf(0,
                                          in,
                                          num1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_5_mossdsp_transformqanglesf_009(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;

mossfw_data_v3f_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
};
mossfw_data_qf_t in[4];
int ret;
float epsilon;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglesf(0,
                                          0,
                                          0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_5_mossdsp_transformqanglesf_010(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;

mossfw_data_v3f_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f},
};
mossfw_data_qf_t in[4];
int ret;
float epsilon;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglesf(0,
                                          0,
                                          0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_6_mossdsp_transformqanglestf_001(void)
{
int num1 = 1;
int num4 = 4;
mossfw_data_v3tf_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_qtf_t in[4];
float epsilon;
int ret;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_transformqanglestf(out,
                                           in,
                                           num4);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(1.0f - epsilon < out[0].y && out[0].y < 1.0f + epsilon);
PCU_ASSERT(0.5f - epsilon < out[0].z && out[0].z < 0.5f + epsilon);
PCU_ASSERT(out[0].t == 11);
PCU_ASSERT(1.0f - epsilon < out[1].x && out[1].x < 1.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(out[1].t == 12);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(1.0f - epsilon < out[2].y && out[2].y < 1.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(out[2].t == 13);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(1.0f - epsilon < out[3].z && out[3].z < 1.0f + epsilon);
PCU_ASSERT(out[3].t == 14);



beginsystimer();

ret = mossdsp_transformqanglestf(out,
                                           in,
                                           num4);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_transformqanglestf(out,
                                           in,
                                           num4);


endsystimer(__func__);
}

static void TestMossdspRot_6_mossdsp_transformqanglestf_002(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_v3tf_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_qtf_t in[4];
float epsilon;
int ret;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglestf(out,
                                           in,
                                           num1);


}

epsilon = FLT_EPSILON;
PCU_ASSERT(ret == 0);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(1.0f - epsilon < out[0].y && out[0].y < 1.0f + epsilon);
PCU_ASSERT(0.5f - epsilon < out[0].z && out[0].z < 0.5f + epsilon);
PCU_ASSERT(out[0].t == 11);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_6_mossdsp_transformqanglestf_003(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_v3tf_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_qtf_t in[4];
float epsilon;
int ret;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglestf(out,
                                           in,
                                           0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_6_mossdsp_transformqanglestf_004(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_v3tf_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_qtf_t in[4];
float epsilon;
int ret;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglestf(out,
                                           in,
                                           0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_6_mossdsp_transformqanglestf_005(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_v3tf_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_qtf_t in[4];
float epsilon;
int ret;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglestf(out,
                                           0,
                                           num4);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_6_mossdsp_transformqanglestf_006(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_v3tf_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_qtf_t in[4];
float epsilon;
int ret;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglestf(out,
                                           0,
                                           num1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_6_mossdsp_transformqanglestf_007(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_v3tf_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_qtf_t in[4];
float epsilon;
int ret;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglestf(0,
                                           in,
                                           num4);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_6_mossdsp_transformqanglestf_008(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_v3tf_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_qtf_t in[4];
float epsilon;
int ret;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglestf(0,
                                           in,
                                           num1);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_6_mossdsp_transformqanglestf_009(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_v3tf_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_qtf_t in[4];
float epsilon;
int ret;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglestf(0,
                                           0,
                                           0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_6_mossdsp_transformqanglestf_010(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_v3tf_t out[4] = {
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_qtf_t in[4];
float epsilon;
int ret;

/* (cos(1/2) + sin(1/2)k) * (cos(1/4) + sin(1/4)j) */
in[0].w = 0.850300643f;
in[0].x = -0.118611776f;
in[0].y = 0.464521358f;
in[0].z = 0.217117399f;
/* cos(1/2) + sin(1/2)i */
in[1].w = 0.877582561f;
in[1].x = 0.479425538f;
in[1].y = 0.0f;
in[1].z = 0.0f;
/* cos(1/2) + sin(1/2)j */
in[2].w = 0.877582561f;
in[2].x = 0.0f;
in[2].y = 0.479425538f;
in[2].z = 0.0f;
/* cos(1/2) + sin(1/2)k */
in[3].w = 0.877582561f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 0.479425538f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformqanglestf(0,
                                           0,
                                           0);


}

epsilon = FLT_MIN;
PCU_ASSERT(ret == -1);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_7_mossdsp_transformanglesf_001(void)
{
int num1 = 1;
int num4 = 4;
mossfw_data_qf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
mossfw_data_v3f_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;
(void)num1;
(void)num4;
(void)in;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_transformanglesf(out,
                               in,
                               num4);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT_EQUAL(ret,0);
PCU_ASSERT(0.8223631719f - epsilon < out[0].w && out[0].w < 0.8223631719f + epsilon);
PCU_ASSERT(0.0222600267f - epsilon < out[0].x && out[0].x < 0.0222600267f + epsilon);
PCU_ASSERT(0.4396797395f - epsilon < out[0].y && out[0].y < 0.4396797395f + epsilon);
PCU_ASSERT(0.3604234056f - epsilon < out[0].z && out[0].z < 0.3604234056f + epsilon);
PCU_ASSERT(0.8660254037f - epsilon < out[1].w && out[1].w < 0.8660254037f + epsilon);
PCU_ASSERT(0.5f - epsilon < out[1].x && out[1].x < 0.5f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.8660254037f - epsilon < out[2].w && out[2].w < 0.8660254037f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.5f - epsilon < out[2].y && out[2].y < 0.5f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.8660254037f - epsilon < out[3].w && out[3].w < 0.8660254037f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.5f - epsilon < out[3].z && out[3].z < 0.5f + epsilon);



beginsystimer();

ret = mossdsp_transformanglesf(out,
                               in,
                               num4);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_transformanglesf(out,
                               in,
                               num4);


endsystimer(__func__);
}

static void TestMossdspRot_7_mossdsp_transformanglesf_002(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
mossfw_data_v3f_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglesf(out,
                               in,
                               num1);


}

epsilon = FLT_EPSILON;
PCU_ASSERT_EQUAL(ret,0);
PCU_ASSERT(0.8223631719 - epsilon < out[0].w && out[0].w < 0.8223631719 + epsilon);
PCU_ASSERT(0.0222600267 - epsilon < out[0].x && out[0].x < 0.0222600267 + epsilon);
PCU_ASSERT(0.4396797395 - epsilon < out[0].y && out[0].y < 0.4396797395 + epsilon);
PCU_ASSERT(0.3604234056 - epsilon < out[0].z && out[0].z < 0.3604234056 + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_7_mossdsp_transformanglesf_003(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
mossfw_data_v3f_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglesf(out,
                               in,
                               0);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_7_mossdsp_transformanglesf_004(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
mossfw_data_v3f_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglesf(out,
                               in,
                               0);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_7_mossdsp_transformanglesf_005(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
mossfw_data_v3f_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglesf(out,
                               0,
                               num4);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_7_mossdsp_transformanglesf_006(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
mossfw_data_v3f_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglesf(out,
                               0,
                               num1);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_7_mossdsp_transformanglesf_007(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
mossfw_data_v3f_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglesf(0,
                               in,
                               num4);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_7_mossdsp_transformanglesf_008(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
mossfw_data_v3f_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglesf(0,
                               in,
                               num1);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_7_mossdsp_transformanglesf_009(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
mossfw_data_v3f_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglesf(0,
                               0,
                               0);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_7_mossdsp_transformanglesf_010(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
mossfw_data_v3f_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglesf(0,
                               0,
                               0);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);


#endif
}

static void TestMossdspRot_8_mossdsp_transformanglestf_001(void)
{
int num1 = 1;
int num4 = 4;
mossfw_data_qtf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_v3tf_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_transformanglestf(out,
                                in,
                                num4);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

epsilon = FLT_EPSILON;
PCU_ASSERT_EQUAL(ret,0);
PCU_ASSERT(0.8223631719f - epsilon < out[0].w && out[0].w < 0.8223631719f + epsilon);
PCU_ASSERT(0.0222600267f - epsilon < out[0].x && out[0].x < 0.0222600267f + epsilon);
PCU_ASSERT(0.4396797395f - epsilon < out[0].y && out[0].y < 0.4396797395f + epsilon);
PCU_ASSERT(0.3604234056f - epsilon < out[0].z && out[0].z < 0.3604234056f + epsilon);
PCU_ASSERT(0.8660254037f - epsilon < out[1].w && out[1].w < 0.8660254037f + epsilon);
PCU_ASSERT(0.5f - epsilon < out[1].x && out[1].x < 0.5f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.8660254037f - epsilon < out[2].w && out[2].w < 0.8660254037f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.5f - epsilon < out[2].y && out[2].y < 0.5f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.8660254037f - epsilon < out[3].w && out[3].w < 0.8660254037f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.5f - epsilon < out[3].z && out[3].z < 0.5f + epsilon);
PCU_ASSERT(out[0].t == 11);
PCU_ASSERT(out[1].t == 12);
PCU_ASSERT(out[2].t == 13);
PCU_ASSERT(out[3].t == 14);



beginsystimer();

ret = mossdsp_transformanglestf(out,
                                in,
                                num4);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_transformanglestf(out,
                                in,
                                num4);


endsystimer(__func__);
}

static void TestMossdspRot_8_mossdsp_transformanglestf_002(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qtf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_v3tf_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglestf(out,
                                in,
                                num1);


}

epsilon = FLT_EPSILON;
PCU_ASSERT_EQUAL(ret,0);
PCU_ASSERT(0.8223631719 - epsilon < out[0].w && out[0].w < 0.8223631719 + epsilon);
PCU_ASSERT(0.0222600267 - epsilon < out[0].x && out[0].x < 0.0222600267 + epsilon);
PCU_ASSERT(0.4396797395 - epsilon < out[0].y && out[0].y < 0.4396797395 + epsilon);
PCU_ASSERT(0.3604234056 - epsilon < out[0].z && out[0].z < 0.3604234056 + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 11);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_8_mossdsp_transformanglestf_003(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qtf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_v3tf_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglestf(out,
                                in,
                                0);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_8_mossdsp_transformanglestf_004(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qtf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_v3tf_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglestf(out,
                                in,
                                0);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_8_mossdsp_transformanglestf_005(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qtf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_v3tf_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglestf(out,
                                0,
                                num4);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_8_mossdsp_transformanglestf_006(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qtf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_v3tf_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglestf(out,
                                0,
                                num1);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_8_mossdsp_transformanglestf_007(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qtf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_v3tf_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglestf(0,
                                in,
                                num4);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_8_mossdsp_transformanglestf_008(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qtf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_v3tf_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglestf(0,
                                in,
                                num1);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_8_mossdsp_transformanglestf_009(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qtf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_v3tf_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglestf(0,
                                0,
                                0);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_8_mossdsp_transformanglestf_010(void)
{
#ifdef UNITTEST
int num1 = 1;
int num4 = 4;
mossfw_data_qtf_t out[4] = {
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0},
    {.w = 0.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f, .t = 0}
};
mossfw_data_v3tf_t in[4];
float epsilon;
int ret;

in[0].x = 0.5235987755f;
in[0].y = 0.7853981633f;
in[0].z = 1.0471975511f;
in[1].x = 1.0471975511f;
in[1].y = 0.0f;
in[1].z = 0.0f;
in[2].x = 0.0f;
in[2].y = 1.0471975511f;
in[2].z = 0.0f;
in[3].x = 0.0f;
in[3].y = 0.0f;
in[3].z = 1.0471975511f;

in[0].t = 11;
in[1].t = 12;
in[2].t = 13;
in[3].t = 14;
(void)num1;
(void)num4;
(void)in;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_transformanglestf(0,
                                0,
                                0);


}

epsilon = FLT_MIN;
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT(0.0f - epsilon < out[0].w && out[0].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].x && out[0].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].y && out[0].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[0].z && out[0].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].w && out[1].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].x && out[1].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].y && out[1].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[1].z && out[1].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].w && out[2].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].x && out[2].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].y && out[2].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[2].z && out[2].z < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].w && out[3].w < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].x && out[3].x < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].y && out[3].y < 0.0f + epsilon);
PCU_ASSERT(0.0f - epsilon < out[3].z && out[3].z < 0.0f + epsilon);
PCU_ASSERT(out[0].t == 0);
PCU_ASSERT(out[1].t == 0);
PCU_ASSERT(out[2].t == 0);
PCU_ASSERT(out[3].t == 0);


#endif
}

static void TestMossdspRot_9_mossdsp_transformqazimuthf_001(void)
{
int num = 1;
mossfw_data_v3f_t out;
mossfw_data_qf_t in;
mossfw_data_v3f_t expected;
int ret;
#define PI acosf(-1.0f)
mossfw_data_v3f_t *out_data = &out;
mossfw_data_qf_t *in_data = &in;
mossfw_data_qf_t initval[] = {
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
initval[0].w = cosf(-PI /  6.0f); // 60 ‹ãŒü‚«
initval[0].x = sinf(-PI /  6.0f);
initval[1].w = cosf( PI /  8.0f); // 45 ‹¼Œü‚«
initval[1].z = sinf( PI /  8.0f);
initval[2].w = cosf(- ( PI / 6.0f ) / 2.0f); // 0, 1 ‰ñ“]Œã‚Ì y Ž²‚ÌŽü‚è‚É ƒÆ‰ñ“]
initval[2].x = sinf(- ( PI / 6.0f ) / 2.0f) * cosf(PI / 3.0f) * -sinf(-PI / 4.0f);
initval[2].y = sinf(- ( PI / 6.0f ) / 2.0f) * cosf(PI / 3.0f) *  cosf(-PI / 4.0f);
initval[2].z = sinf(- ( PI / 6.0f ) / 2.0f) * sinf(PI / 3.0f);
initval[3].w = cosf(-PI / 24.0f);
initval[3].x = sinf(-PI / 24.0f) * cosf(PI / 24.0f) * -sinf(PI / 24.0f);
initval[3].y = sinf(-PI / 24.0f) * cosf(PI / 24.0f) *  cosf(PI / 24.0f);
initval[3].z = sinf(-PI / 24.0f) * sinf(PI / 24.0f);
mossdsp_multiplyqf(&initval[4], &initval[0], &initval[1], 1); // 0 -> 1
mossdsp_multiplyqf(&initval[5], &initval[4], &initval[2], 1); // 0 -> 1 -> 2
mossdsp_multiplyqf(&initval[6], &initval[5], &initval[3], 1); // 0 -> 1 -> 2 -> 3
initval[7].w   = initval[3].w;
initval[7].x   = -initval[3].x;
initval[7].y   = -initval[3].y;
initval[7].z   = -initval[3].z;
mossdsp_multiplyqf(&initval[8], &initval[6], &initval[7], 1);
in.w = initval[8].w;
in.x = initval[8].x;
in.y = initval[8].y;
in.z = initval[8].z;
out.x = 0;
out.y = 0;
out.z = 0;

float a12 = 0;
float a22 = 0;
float a31 = 0;
float a32 = 0;
float a33 = 0;

expected.x = ( PI / 4.0f);
expected.y = (-PI / 3.0f);
expected.z = asinf(cosf(PI / 3.0f) * sinf(PI / 6.0f));
(void)in;
(void)a12;
(void)a22;
(void)a31;
(void)a32;
(void)a33;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformqazimuthf(out_data,in_data,num);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_EQUAL(ret,0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);



beginsystimer();
ret = mossdsp_transformqazimuthf(out_data,in_data,num);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformqazimuthf(out_data,in_data,num);


endsystimer(__func__);
}

static void TestMossdspRot_9_mossdsp_transformqazimuthf_002(void)
{
#ifdef UNITTEST
int num = 1;
mossfw_data_v3f_t out;
mossfw_data_qf_t in;
mossfw_data_v3f_t expected;
int ret;
#define PI acosf(-1.0f)
mossfw_data_v3f_t *out_data = &out;
mossfw_data_qf_t *in_data = &in;
mossfw_data_qf_t initval[] = {
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
initval[0].w = cosf(-PI /  6.0f); // 60 ‹ãŒü‚«
initval[0].x = sinf(-PI /  6.0f);
initval[1].w = cosf( PI /  8.0f); // 45 ‹¼Œü‚«
initval[1].z = sinf( PI /  8.0f);
initval[2].w = cosf(- ( PI / 2.0f + PI / 6.0f ) / 2.0f); // 0, 1 ‰ñ“]Œã‚Ì y Ž²‚ÌŽü‚è‚É ƒÆ‰ñ“]
initval[2].x = sinf(- ( PI / 2.0f + PI / 6.0f ) / 2.0f) * cosf(PI / 3.0f) * -sinf(-PI / 4.0f);
initval[2].y = sinf(- ( PI / 2.0f + PI / 6.0f ) / 2.0f) * cosf(PI / 3.0f) *  cosf(-PI / 4.0f);
initval[2].z = sinf(- ( PI / 2.0f + PI / 6.0f ) / 2.0f) * sinf(PI / 3.0f);
initval[3].w = cosf(-PI / 24.0f);
initval[3].x = sinf(-PI / 24.0f) * cosf(PI / 24.0f) * -sinf(PI / 24.0f);
initval[3].y = sinf(-PI / 24.0f) * cosf(PI / 24.0f) *  cosf(PI / 24.0f);
initval[3].z = sinf(-PI / 24.0f) * sinf(PI / 24.0f);
mossdsp_multiplyqf(&initval[4], &initval[0], &initval[1], 1); // 0 -> 1
mossdsp_multiplyqf(&initval[5], &initval[4], &initval[2], 1); // 0 -> 1 -> 2
mossdsp_multiplyqf(&initval[6], &initval[5], &initval[3], 1); // 0 -> 1 -> 2 -> 3
initval[7].w   = initval[3].w;
initval[7].x   = -initval[3].x;
initval[7].y   = -initval[3].y;
initval[7].z   = -initval[3].z;
mossdsp_multiplyqf(&initval[8], &initval[6], &initval[7], 1);
in.w = initval[8].w;
in.x = initval[8].x;
in.y = initval[8].y;
in.z = initval[8].z;
out.x = 0;
out.y = 0;
out.z = 0;

float a12 = 0;
float a22 = 0;
float a31 = 0;
float a32 = 0;
float a33 = 0;

expected.x = ( PI / 4.0f);
expected.y = ( PI / 3.0f);
expected.z = -asinf(cosf(PI / 3.0f) * sinf(PI / 6.0f));
(void)in;
(void)a12;
(void)a22;
(void)a31;
(void)a32;
(void)a33;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformqazimuthf(out_data,in_data,num);


}
PCU_ASSERT_EQUAL(ret,0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);


#endif
}

static void TestMossdspRot_9_mossdsp_transformqazimuthf_003(void)
{
#ifdef UNITTEST
int num = 1;
mossfw_data_v3f_t out;
mossfw_data_qf_t in;
mossfw_data_v3f_t expected;
int ret;
#define PI acosf(-1.0f)
mossfw_data_v3f_t *out_data = 0;
mossfw_data_qf_t *in_data = &in;
mossfw_data_qf_t initval[] = {
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
initval[0].w = cosf(-PI /  6.0f); // 60 ‹ãŒü‚«
initval[0].x = sinf(-PI /  6.0f);
initval[1].w = cosf( PI /  8.0f); // 45 ‹¼Œü‚«
initval[1].z = sinf( PI /  8.0f);
initval[2].w = cosf(- ( 0 ) / 2.0f); // 0, 1 ‰ñ“]Œã‚Ì y Ž²‚ÌŽü‚è‚É ƒÆ‰ñ“]
initval[2].x = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) * -sinf(-PI / 4.0f);
initval[2].y = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) *  cosf(-PI / 4.0f);
initval[2].z = sinf(- ( 0 ) / 2.0f) * sinf(PI / 3.0f);
initval[3].w = cosf(-PI / 24.0f);
initval[3].x = sinf(-PI / 24.0f) * cosf(PI / 24.0f) * -sinf(PI / 24.0f);
initval[3].y = sinf(-PI / 24.0f) * cosf(PI / 24.0f) *  cosf(PI / 24.0f);
initval[3].z = sinf(-PI / 24.0f) * sinf(PI / 24.0f);
mossdsp_multiplyqf(&initval[4], &initval[0], &initval[1], 1); // 0 -> 1
mossdsp_multiplyqf(&initval[5], &initval[4], &initval[2], 1); // 0 -> 1 -> 2
mossdsp_multiplyqf(&initval[6], &initval[5], &initval[3], 1); // 0 -> 1 -> 2 -> 3
initval[7].w   = initval[3].w;
initval[7].x   = -initval[3].x;
initval[7].y   = -initval[3].y;
initval[7].z   = -initval[3].z;
mossdsp_multiplyqf(&initval[8], &initval[6], &initval[7], 1);
in.w = 1;
in.x = 2;
in.y = 3;
in.z = 4;
out.x = 0;
out.y = 0;
out.z = 0;

float a12 = 16;
float a22 = -10;
float a31 = 13;
float a32 = 22;
float a33 = 4;

expected.x = -1.01219701145133;
expected.y = 0.995082168985;
expected.z = -1.49402443552512;
(void)in;
(void)a12;
(void)a22;
(void)a31;
(void)a32;
(void)a33;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformqazimuthf(out_data,in_data,num);


}
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);


#endif
}

static void TestMossdspRot_9_mossdsp_transformqazimuthf_004(void)
{
#ifdef UNITTEST
int num = 1;
mossfw_data_v3f_t out;
mossfw_data_qf_t in;
mossfw_data_v3f_t expected;
int ret;
#define PI acosf(-1.0f)
mossfw_data_v3f_t *out_data = &out;
mossfw_data_qf_t *in_data = 0;
mossfw_data_qf_t initval[] = {
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
initval[0].w = cosf(-PI /  6.0f); // 60 ‹ãŒü‚«
initval[0].x = sinf(-PI /  6.0f);
initval[1].w = cosf( PI /  8.0f); // 45 ‹¼Œü‚«
initval[1].z = sinf( PI /  8.0f);
initval[2].w = cosf(- ( 0 ) / 2.0f); // 0, 1 ‰ñ“]Œã‚Ì y Ž²‚ÌŽü‚è‚É ƒÆ‰ñ“]
initval[2].x = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) * -sinf(-PI / 4.0f);
initval[2].y = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) *  cosf(-PI / 4.0f);
initval[2].z = sinf(- ( 0 ) / 2.0f) * sinf(PI / 3.0f);
initval[3].w = cosf(-PI / 24.0f);
initval[3].x = sinf(-PI / 24.0f) * cosf(PI / 24.0f) * -sinf(PI / 24.0f);
initval[3].y = sinf(-PI / 24.0f) * cosf(PI / 24.0f) *  cosf(PI / 24.0f);
initval[3].z = sinf(-PI / 24.0f) * sinf(PI / 24.0f);
mossdsp_multiplyqf(&initval[4], &initval[0], &initval[1], 1); // 0 -> 1
mossdsp_multiplyqf(&initval[5], &initval[4], &initval[2], 1); // 0 -> 1 -> 2
mossdsp_multiplyqf(&initval[6], &initval[5], &initval[3], 1); // 0 -> 1 -> 2 -> 3
initval[7].w   = initval[3].w;
initval[7].x   = -initval[3].x;
initval[7].y   = -initval[3].y;
initval[7].z   = -initval[3].z;
mossdsp_multiplyqf(&initval[8], &initval[6], &initval[7], 1);
in.w = 1;
in.x = 2;
in.y = 3;
in.z = 4;
out.x = 0;
out.y = 0;
out.z = 0;

float a12 = 16;
float a22 = -10;
float a31 = 13;
float a32 = 22;
float a33 = 4;

expected.x = -1.01219701145133;
expected.y = 0.995082168985;
expected.z = -1.49402443552512;
(void)in;
(void)a12;
(void)a22;
(void)a31;
(void)a32;
(void)a33;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformqazimuthf(out_data,in_data,num);


}
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);


#endif
}

static void TestMossdspRot_9_mossdsp_transformqazimuthf_005(void)
{
#ifdef UNITTEST
int num = 0;
mossfw_data_v3f_t out;
mossfw_data_qf_t in;
mossfw_data_v3f_t expected;
int ret;
#define PI acosf(-1.0f)
mossfw_data_v3f_t *out_data = &out;
mossfw_data_qf_t *in_data = &in;
mossfw_data_qf_t initval[] = {
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
initval[0].w = cosf(-PI /  6.0f); // 60 ‹ãŒü‚«
initval[0].x = sinf(-PI /  6.0f);
initval[1].w = cosf( PI /  8.0f); // 45 ‹¼Œü‚«
initval[1].z = sinf( PI /  8.0f);
initval[2].w = cosf(- ( 0 ) / 2.0f); // 0, 1 ‰ñ“]Œã‚Ì y Ž²‚ÌŽü‚è‚É ƒÆ‰ñ“]
initval[2].x = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) * -sinf(-PI / 4.0f);
initval[2].y = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) *  cosf(-PI / 4.0f);
initval[2].z = sinf(- ( 0 ) / 2.0f) * sinf(PI / 3.0f);
initval[3].w = cosf(-PI / 24.0f);
initval[3].x = sinf(-PI / 24.0f) * cosf(PI / 24.0f) * -sinf(PI / 24.0f);
initval[3].y = sinf(-PI / 24.0f) * cosf(PI / 24.0f) *  cosf(PI / 24.0f);
initval[3].z = sinf(-PI / 24.0f) * sinf(PI / 24.0f);
mossdsp_multiplyqf(&initval[4], &initval[0], &initval[1], 1); // 0 -> 1
mossdsp_multiplyqf(&initval[5], &initval[4], &initval[2], 1); // 0 -> 1 -> 2
mossdsp_multiplyqf(&initval[6], &initval[5], &initval[3], 1); // 0 -> 1 -> 2 -> 3
initval[7].w   = initval[3].w;
initval[7].x   = -initval[3].x;
initval[7].y   = -initval[3].y;
initval[7].z   = -initval[3].z;
mossdsp_multiplyqf(&initval[8], &initval[6], &initval[7], 1);
in.w = 1;
in.x = 2;
in.y = 3;
in.z = 4;
out.x = 0;
out.y = 0;
out.z = 0;

float a12 = 16;
float a22 = -10;
float a31 = 13;
float a32 = 22;
float a33 = 4;

expected.x = -1.01219701145133;
expected.y = 0.995082168985;
expected.z = -1.49402443552512;
(void)in;
(void)a12;
(void)a22;
(void)a31;
(void)a32;
(void)a33;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformqazimuthf(out_data,in_data,num);


}
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);


#endif
}

static void TestMossdspRot_10_mossdsp_transformqazimuthtf_001(void)
{
int num = 1;
mossfw_data_v3tf_t out;
mossfw_data_qtf_t in;
mossfw_data_v3tf_t expected;
int ret;
#define PI acosf(-1.0f)
mossfw_data_v3tf_t *out_data = &out;
mossfw_data_qtf_t *in_data = &in;
mossfw_data_qtf_t initval[] = {
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
initval[0].w = cosf(-PI /  6.0f); // 60 ‹ãŒü‚«
initval[0].x = sinf(-PI /  6.0f);
initval[1].w = cosf( PI /  8.0f); // 45 ‹¼Œü‚«
initval[1].z = sinf( PI /  8.0f);
initval[2].w = cosf(- ( PI / 6.0f ) / 2.0f); // 0, 1 ‰ñ“]Œã‚Ì y Ž²‚ÌŽü‚è‚É ƒÆ‰ñ“]
initval[2].x = sinf(- ( PI / 6.0f ) / 2.0f) * cosf(PI / 3.0f) * -sinf(-PI / 4.0f);
initval[2].y = sinf(- ( PI / 6.0f ) / 2.0f) * cosf(PI / 3.0f) *  cosf(-PI / 4.0f);
initval[2].z = sinf(- ( PI / 6.0f ) / 2.0f) * sinf(PI / 3.0f);
initval[3].w = cosf(-PI / 24.0f);
initval[3].x = sinf(-PI / 24.0f) * cosf(PI / 24.0f) * -sinf(PI / 24.0f);
initval[3].y = sinf(-PI / 24.0f) * cosf(PI / 24.0f) *  cosf(PI / 24.0f);
initval[3].z = sinf(-PI / 24.0f) * sinf(PI / 24.0f);
mossdsp_multiplyqtf(&initval[4], &initval[0], &initval[1], 1); // 0 -> 1
mossdsp_multiplyqtf(&initval[5], &initval[4], &initval[2], 1); // 0 -> 1 -> 2
mossdsp_multiplyqtf(&initval[6], &initval[5], &initval[3], 1); // 0 -> 1 -> 2 -> 3
initval[7].w   = initval[3].w;
initval[7].x   = -initval[3].x;
initval[7].y   = -initval[3].y;
initval[7].z   = -initval[3].z;
mossdsp_multiplyqtf(&initval[8], &initval[6], &initval[7], 1);
in.w = initval[8].w;
in.x = initval[8].x;
in.y = initval[8].y;
in.z = initval[8].z;
in.t = initval[8].t;
out.x = 0;
out.y = 0;
out.z = 0;
out.t = 0;

float a12 = 0;
float a22 = 0;
float a31 = 0;
float a32 = 0;
float a33 = 0;

expected.x = ( PI / 4.0f);
expected.y = (-PI / 3.0f);
expected.z = asinf(cosf(PI / 3.0f) * sinf(PI / 6.0f));
expected.t = 0;
(void)in;
(void)a12;
(void)a22;
(void)a31;
(void)a32;
(void)a33;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();
ret = mossdsp_transformqazimuthtf(out_data,in_data,num);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif
PCU_ASSERT_EQUAL(ret,0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);
PCU_ASSERT_EQUAL(expected.t , out.t);


beginsystimer();
ret = mossdsp_transformqazimuthtf(out_data,in_data,num);


endsystimer(__func__);
beginsystimer();
ret = mossdsp_transformqazimuthtf(out_data,in_data,num);


endsystimer(__func__);
}

static void TestMossdspRot_10_mossdsp_transformqazimuthtf_002(void)
{
#ifdef UNITTEST
int num = 1;
mossfw_data_v3tf_t out;
mossfw_data_qtf_t in;
mossfw_data_v3tf_t expected;
int ret;
#define PI acosf(-1.0f)
mossfw_data_v3tf_t *out_data = &out;
mossfw_data_qtf_t *in_data = &in;
mossfw_data_qtf_t initval[] = {
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
initval[0].w = cosf(-PI /  6.0f); // 60 ‹ãŒü‚«
initval[0].x = sinf(-PI /  6.0f);
initval[1].w = cosf( PI /  8.0f); // 45 ‹¼Œü‚«
initval[1].z = sinf( PI /  8.0f);
initval[2].w = cosf(- ( PI / 2.0f + PI / 6.0f ) / 2.0f); // 0, 1 ‰ñ“]Œã‚Ì y Ž²‚ÌŽü‚è‚É ƒÆ‰ñ“]
initval[2].x = sinf(- ( PI / 2.0f + PI / 6.0f ) / 2.0f) * cosf(PI / 3.0f) * -sinf(-PI / 4.0f);
initval[2].y = sinf(- ( PI / 2.0f + PI / 6.0f ) / 2.0f) * cosf(PI / 3.0f) *  cosf(-PI / 4.0f);
initval[2].z = sinf(- ( PI / 2.0f + PI / 6.0f ) / 2.0f) * sinf(PI / 3.0f);
initval[3].w = cosf(-PI / 24.0f);
initval[3].x = sinf(-PI / 24.0f) * cosf(PI / 24.0f) * -sinf(PI / 24.0f);
initval[3].y = sinf(-PI / 24.0f) * cosf(PI / 24.0f) *  cosf(PI / 24.0f);
initval[3].z = sinf(-PI / 24.0f) * sinf(PI / 24.0f);
mossdsp_multiplyqtf(&initval[4], &initval[0], &initval[1], 1); // 0 -> 1
mossdsp_multiplyqtf(&initval[5], &initval[4], &initval[2], 1); // 0 -> 1 -> 2
mossdsp_multiplyqtf(&initval[6], &initval[5], &initval[3], 1); // 0 -> 1 -> 2 -> 3
initval[7].w   = initval[3].w;
initval[7].x   = -initval[3].x;
initval[7].y   = -initval[3].y;
initval[7].z   = -initval[3].z;
mossdsp_multiplyqtf(&initval[8], &initval[6], &initval[7], 1);
in.w = initval[8].w;
in.x = initval[8].x;
in.y = initval[8].y;
in.z = initval[8].z;
in.t = initval[8].t;
out.x = 0;
out.y = 0;
out.z = 0;
out.t = 0;

float a12 = 0;
float a22 = 0;
float a31 = 0;
float a32 = 0;
float a33 = 0;

expected.x = ( PI / 4.0f);
expected.y = ( PI / 3.0f);
expected.z = -asinf(cosf(PI / 3.0f) * sinf(PI / 6.0f));
expected.t = 0;
(void)in;
(void)a12;
(void)a22;
(void)a31;
(void)a32;
(void)a33;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformqazimuthtf(out_data,in_data,num);


}
PCU_ASSERT_EQUAL(ret,0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 1);
PCU_ASSERT_EQUAL(expected.t , out.t);

#endif
}

static void TestMossdspRot_10_mossdsp_transformqazimuthtf_003(void)
{
#ifdef UNITTEST
int num = 1;
mossfw_data_v3tf_t out;
mossfw_data_qtf_t in;
mossfw_data_v3tf_t expected;
int ret;
#define PI acosf(-1.0f)
mossfw_data_v3tf_t *out_data = 0;
mossfw_data_qtf_t *in_data = &in;
mossfw_data_qtf_t initval[] = {
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
initval[0].w = cosf(-PI /  6.0f); // 60 ‹ãŒü‚«
initval[0].x = sinf(-PI /  6.0f);
initval[1].w = cosf( PI /  8.0f); // 45 ‹¼Œü‚«
initval[1].z = sinf( PI /  8.0f);
initval[2].w = cosf(- ( 0 ) / 2.0f); // 0, 1 ‰ñ“]Œã‚Ì y Ž²‚ÌŽü‚è‚É ƒÆ‰ñ“]
initval[2].x = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) * -sinf(-PI / 4.0f);
initval[2].y = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) *  cosf(-PI / 4.0f);
initval[2].z = sinf(- ( 0 ) / 2.0f) * sinf(PI / 3.0f);
initval[3].w = cosf(-PI / 24.0f);
initval[3].x = sinf(-PI / 24.0f) * cosf(PI / 24.0f) * -sinf(PI / 24.0f);
initval[3].y = sinf(-PI / 24.0f) * cosf(PI / 24.0f) *  cosf(PI / 24.0f);
initval[3].z = sinf(-PI / 24.0f) * sinf(PI / 24.0f);
mossdsp_multiplyqtf(&initval[4], &initval[0], &initval[1], 1); // 0 -> 1
mossdsp_multiplyqtf(&initval[5], &initval[4], &initval[2], 1); // 0 -> 1 -> 2
mossdsp_multiplyqtf(&initval[6], &initval[5], &initval[3], 1); // 0 -> 1 -> 2 -> 3
initval[7].w   = initval[3].w;
initval[7].x   = -initval[3].x;
initval[7].y   = -initval[3].y;
initval[7].z   = -initval[3].z;
mossdsp_multiplyqtf(&initval[8], &initval[6], &initval[7], 1);
in.w = 1;
in.x = 2;
in.y = 3;
in.z = 4;
in.t = 5;
out.x = 0;
out.y = 0;
out.z = 0;
out.t = 0;

float a12 = 16;
float a22 = -10;
float a31 = 13;
float a32 = 22;
float a33 = 4;

expected.x = -1.01219701145133;
expected.y = 0.995082168985;
expected.z = -1.49402443552512;
expected.t = 0;
(void)in;
(void)a12;
(void)a22;
(void)a31;
(void)a32;
(void)a33;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformqazimuthtf(out_data,in_data,num);


}
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.t , out.t);

#endif
}

static void TestMossdspRot_10_mossdsp_transformqazimuthtf_004(void)
{
#ifdef UNITTEST
int num = 1;
mossfw_data_v3tf_t out;
mossfw_data_qtf_t in;
mossfw_data_v3tf_t expected;
int ret;
#define PI acosf(-1.0f)
mossfw_data_v3tf_t *out_data = &out;
mossfw_data_qtf_t *in_data = 0;
mossfw_data_qtf_t initval[] = {
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
initval[0].w = cosf(-PI /  6.0f); // 60 ‹ãŒü‚«
initval[0].x = sinf(-PI /  6.0f);
initval[1].w = cosf( PI /  8.0f); // 45 ‹¼Œü‚«
initval[1].z = sinf( PI /  8.0f);
initval[2].w = cosf(- ( 0 ) / 2.0f); // 0, 1 ‰ñ“]Œã‚Ì y Ž²‚ÌŽü‚è‚É ƒÆ‰ñ“]
initval[2].x = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) * -sinf(-PI / 4.0f);
initval[2].y = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) *  cosf(-PI / 4.0f);
initval[2].z = sinf(- ( 0 ) / 2.0f) * sinf(PI / 3.0f);
initval[3].w = cosf(-PI / 24.0f);
initval[3].x = sinf(-PI / 24.0f) * cosf(PI / 24.0f) * -sinf(PI / 24.0f);
initval[3].y = sinf(-PI / 24.0f) * cosf(PI / 24.0f) *  cosf(PI / 24.0f);
initval[3].z = sinf(-PI / 24.0f) * sinf(PI / 24.0f);
mossdsp_multiplyqtf(&initval[4], &initval[0], &initval[1], 1); // 0 -> 1
mossdsp_multiplyqtf(&initval[5], &initval[4], &initval[2], 1); // 0 -> 1 -> 2
mossdsp_multiplyqtf(&initval[6], &initval[5], &initval[3], 1); // 0 -> 1 -> 2 -> 3
initval[7].w   = initval[3].w;
initval[7].x   = -initval[3].x;
initval[7].y   = -initval[3].y;
initval[7].z   = -initval[3].z;
mossdsp_multiplyqtf(&initval[8], &initval[6], &initval[7], 1);
in.w = 1;
in.x = 2;
in.y = 3;
in.z = 4;
in.t = 5;
out.x = 0;
out.y = 0;
out.z = 0;
out.t = 0;

float a12 = 16;
float a22 = -10;
float a31 = 13;
float a32 = 22;
float a33 = 4;

expected.x = -1.01219701145133;
expected.y = 0.995082168985;
expected.z = -1.49402443552512;
expected.t = 0;
(void)in;
(void)a12;
(void)a22;
(void)a31;
(void)a32;
(void)a33;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformqazimuthtf(out_data,in_data,num);


}
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.t , out.t);

#endif
}

static void TestMossdspRot_10_mossdsp_transformqazimuthtf_005(void)
{
#ifdef UNITTEST
int num = 0;
mossfw_data_v3tf_t out;
mossfw_data_qtf_t in;
mossfw_data_v3tf_t expected;
int ret;
#define PI acosf(-1.0f)
mossfw_data_v3tf_t *out_data = &out;
mossfw_data_qtf_t *in_data = &in;
mossfw_data_qtf_t initval[] = {
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f},
    {.t = 0, .w = 1.0f, .x = 0.0f, .y = 0.0f, .z = 0.0f}
};
initval[0].w = cosf(-PI /  6.0f); // 60 ‹ãŒü‚«
initval[0].x = sinf(-PI /  6.0f);
initval[1].w = cosf( PI /  8.0f); // 45 ‹¼Œü‚«
initval[1].z = sinf( PI /  8.0f);
initval[2].w = cosf(- ( 0 ) / 2.0f); // 0, 1 ‰ñ“]Œã‚Ì y Ž²‚ÌŽü‚è‚É ƒÆ‰ñ“]
initval[2].x = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) * -sinf(-PI / 4.0f);
initval[2].y = sinf(- ( 0 ) / 2.0f) * cosf(PI / 3.0f) *  cosf(-PI / 4.0f);
initval[2].z = sinf(- ( 0 ) / 2.0f) * sinf(PI / 3.0f);
initval[3].w = cosf(-PI / 24.0f);
initval[3].x = sinf(-PI / 24.0f) * cosf(PI / 24.0f) * -sinf(PI / 24.0f);
initval[3].y = sinf(-PI / 24.0f) * cosf(PI / 24.0f) *  cosf(PI / 24.0f);
initval[3].z = sinf(-PI / 24.0f) * sinf(PI / 24.0f);
mossdsp_multiplyqtf(&initval[4], &initval[0], &initval[1], 1); // 0 -> 1
mossdsp_multiplyqtf(&initval[5], &initval[4], &initval[2], 1); // 0 -> 1 -> 2
mossdsp_multiplyqtf(&initval[6], &initval[5], &initval[3], 1); // 0 -> 1 -> 2 -> 3
initval[7].w   = initval[3].w;
initval[7].x   = -initval[3].x;
initval[7].y   = -initval[3].y;
initval[7].z   = -initval[3].z;
mossdsp_multiplyqtf(&initval[8], &initval[6], &initval[7], 1);
in.w = 1;
in.x = 2;
in.y = 3;
in.z = 4;
in.t = 5;
out.x = 0;
out.y = 0;
out.z = 0;
out.t = 0;

float a12 = 16;
float a22 = -10;
float a31 = 13;
float a32 = 22;
float a33 = 4;

expected.x = -1.01219701145133;
expected.y = 0.995082168985;
expected.z = -1.49402443552512;
expected.t = 0;
(void)in;
(void)a12;
(void)a22;
(void)a31;
(void)a32;
(void)a33;


if (setjmp(g_testCaseEnv) == 0) {
ret = mossdsp_transformqazimuthtf(out_data,in_data,num);


}
PCU_ASSERT_EQUAL(ret,-1);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.x - 8.0f * fabsf(expected.x) * FLT_EPSILON < out.x && out.x < expected.x + 8.0f * fabsf(expected.x) * FLT_EPSILON, 0);
PCU_ASSERT_EQUAL(expected.t , out.t);

#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_001(void)
{

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = in0;
mossfw_data_qf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


endsystimer(__func__);
}

static void TestMossdspRot_mossdsp_multiplyqf_002(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = in0;
mossfw_data_qf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_003(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = 0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = in0;
mossfw_data_qf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_004(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qf_t *out_data = 0;
mossfw_data_qf_t *in0_data = in0;
mossfw_data_qf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_005(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qf_t *out_data = 0;
mossfw_data_qf_t *in0_data = in0;
mossfw_data_qf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_006(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = 0;
mossfw_data_qf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_007(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = 0;
mossfw_data_qf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_008(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = in0;
mossfw_data_qf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_009(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = in0;
mossfw_data_qf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_010(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = 0;
mossfw_data_qf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_011(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = 0;

mossfw_data_qf_t *out_data = 0;
mossfw_data_qf_t *in0_data = in0;
mossfw_data_qf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_012(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = 0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = 0;
mossfw_data_qf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_013(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qf_t *out_data = 0;
mossfw_data_qf_t *in0_data = 0;
mossfw_data_qf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqf_014(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = 0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = in0;
mossfw_data_qf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_001(void)
{

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;
mossfw_data_qtf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


endsystimer(__func__);
}

static void TestMossdspRot_mossdsp_multiplyqtf_002(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;
mossfw_data_qtf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_003(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = 0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;
mossfw_data_qtf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_004(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qtf_t *out_data = 0;
mossfw_data_qtf_t *in0_data = in0;
mossfw_data_qtf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_005(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qtf_t *out_data = 0;
mossfw_data_qtf_t *in0_data = in0;
mossfw_data_qtf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_006(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = 0;
mossfw_data_qtf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_007(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = 0;
mossfw_data_qtf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_008(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;
mossfw_data_qtf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_009(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;
mossfw_data_qtf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_010(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = 0;
mossfw_data_qtf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_011(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = 0;

mossfw_data_qtf_t *out_data = 0;
mossfw_data_qtf_t *in0_data = in0;
mossfw_data_qtf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_012(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = 0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = 0;
mossfw_data_qtf_t *in1_data = in1;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_013(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qtf_t *out_data = 0;
mossfw_data_qtf_t *in0_data = 0;
mossfw_data_qtf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_multiplyqtf_014(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = 0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;
mossfw_data_qtf_t *in1_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

in1[0].w = 20;
in1[0].x = 21;
in1[0].y = 22;
in1[0].z = 23;
in1[1].w = 24;
in1[1].x = 25;
in1[1].y = 26;
in1[1].z = 27;
in1[2].w = 28;
in1[2].x = 29;
in1[2].y = 30;
in1[2].z = 31;
in1[3].w = 32;
in1[3].x = 33;
in1[3].y = 34;
in1[3].z = 35;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = -226;
expected[0].x = 84;
expected[0].y = 160;
expected[0].z = 128;
expected[1].w = -482;
expected[1].x = 283;
expected[1].y = 384;
expected[1].z = 360;
expected[2].w = -802;
expected[2].x = 555;
expected[2].y = 672;
expected[2].z = 656;
expected[3].w = -1186;
expected[3].x = 891;
expected[3].y = 1024;
expected[3].z = 1016;




in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

in1[0].t = 211;
in1[1].t = 212;
in1[2].t = 213;
in1[3].t = 214;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_multiplyqtf(out_data,in0_data,in1_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_001(void)
{

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_conjugateqf(out_data,in0_data,num);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();

ret = mossdsp_conjugateqf(out_data,in0_data,num);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_conjugateqf(out_data,in0_data,num);


endsystimer(__func__);
}

static void TestMossdspRot_mossdsp_conjugateqf_002(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_003(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = 0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_004(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qf_t *out_data = 0;
mossfw_data_qf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_005(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qf_t *out_data = 0;
mossfw_data_qf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_006(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_007(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_008(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = 0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_009(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = 0;

mossfw_data_qf_t *out_data = 0;
mossfw_data_qf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_010(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_011(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = 0;

mossfw_data_qf_t *out_data = 0;
mossfw_data_qf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_012(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = 0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_013(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qf_t *out_data = 0;
mossfw_data_qf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqf_014(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qf_t out[4];
mossfw_data_qf_t in0[4];
mossfw_data_qf_t in1[4];
mossfw_data_qf_t expected[4];
int ret;
int num = 0;

mossfw_data_qf_t *out_data = out;
mossfw_data_qf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;

out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_001(void)
{

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


#ifdef UNITTEST
if (setjmp(g_testCaseEnv) == 0) {
#endif
beginsystimer();

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


endsystimer(__func__);
#ifdef UNITTEST
}
#endif

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),1);
PCU_ASSERT_EQUAL(ret,0);



beginsystimer();

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


endsystimer(__func__);
beginsystimer();

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


endsystimer(__func__);
}

static void TestMossdspRot_mossdsp_conjugateqtf_002(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_003(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = 0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_004(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qtf_t *out_data = 0;
mossfw_data_qtf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_005(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qtf_t *out_data = 0;
mossfw_data_qtf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_006(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_007(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_008(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_009(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),1);
PCU_ASSERT_EQUAL(ret,0);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_010(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_011(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = 0;

mossfw_data_qtf_t *out_data = 0;
mossfw_data_qtf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_012(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = 0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_013(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = num_1;

mossfw_data_qtf_t *out_data = 0;
mossfw_data_qtf_t *in0_data = 0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}

static void TestMossdspRot_mossdsp_conjugateqtf_014(void)
{
#ifdef UNITTEST

int num_0 = 1;
int num_1 = 4;
mossfw_data_qtf_t out[4];
mossfw_data_qtf_t in0[4];
mossfw_data_qtf_t in1[4];
mossfw_data_qtf_t expected[4];
int ret;
int num = 0;

mossfw_data_qtf_t *out_data = out;
mossfw_data_qtf_t *in0_data = in0;

in0[0].w = 2;
in0[0].x = 3;
in0[0].y = 4;
in0[0].z = 5;
in0[1].w = 6;
in0[1].x = 7;
in0[1].y = 8;
in0[1].z = 9;
in0[2].w = 10;
in0[2].x = 11;
in0[2].y = 12;
in0[2].z = 13;
in0[3].w = 14;
in0[3].x = 15;
in0[3].y = 16;
in0[3].z = 17;


out[0].w = 0;
out[0].x = 0;
out[0].y = 0;
out[0].z = 0;
out[1].w = 0;
out[1].x = 0;
out[1].y = 0;
out[1].z = 0;
out[2].w = 0;
out[2].x = 0;
out[2].y = 0;
out[2].z = 0;
out[3].w = 0;
out[3].x = 0;
out[3].y = 0;
out[3].z = 0;

expected[0].w = 2;
expected[0].x = -3;
expected[0].y = -4;
expected[0].z = -5;
expected[1].w = 6;
expected[1].x = -7;
expected[1].y = -8;
expected[1].z = -9;
expected[2].w = 10;
expected[2].x = -11;
expected[2].y = -12;
expected[2].z = -13;
expected[3].w = 14;
expected[3].x = -15;
expected[3].y = -16;
expected[3].z = -17;


in0[0].t = 111;
in0[1].t = 112;
in0[2].t = 113;
in0[3].t = 114;

out[0].t = 0;
out[1].t = 0;
out[2].t = 0;
out[3].t = 0;

expected[0].t = 111;
expected[1].t = 112;
expected[2].t = 113;
expected[3].t = 114;
(void)num_0;
(void)num_1;
(void)in0;
(void)in1;


if (setjmp(g_testCaseEnv) == 0) {

ret = mossdsp_conjugateqtf(out_data,in0_data,num);


}

PCU_ASSERT_MEMORY_EQUAL(&out,&expected,sizeof(mossfw_data_qtf_t),0);
PCU_ASSERT_EQUAL(ret,-1);


#endif
}


PCU_Suite* TestMossdspRot(void)
{
    static PCU_Test tests[] = {

#if 1
        {.name = "TestMossdspRot_5_mossdsp_transformqanglesf_001", .test = TestMossdspRot_5_mossdsp_transformqanglesf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_5_mossdsp_transformqanglesf_002", .test = TestMossdspRot_5_mossdsp_transformqanglesf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_5_mossdsp_transformqanglesf_003", .test = TestMossdspRot_5_mossdsp_transformqanglesf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_5_mossdsp_transformqanglesf_004", .test = TestMossdspRot_5_mossdsp_transformqanglesf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_5_mossdsp_transformqanglesf_005", .test = TestMossdspRot_5_mossdsp_transformqanglesf_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_5_mossdsp_transformqanglesf_006", .test = TestMossdspRot_5_mossdsp_transformqanglesf_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_5_mossdsp_transformqanglesf_007", .test = TestMossdspRot_5_mossdsp_transformqanglesf_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_5_mossdsp_transformqanglesf_008", .test = TestMossdspRot_5_mossdsp_transformqanglesf_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_5_mossdsp_transformqanglesf_009", .test = TestMossdspRot_5_mossdsp_transformqanglesf_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_5_mossdsp_transformqanglesf_010", .test = TestMossdspRot_5_mossdsp_transformqanglesf_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_6_mossdsp_transformqanglestf_001", .test = TestMossdspRot_6_mossdsp_transformqanglestf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_6_mossdsp_transformqanglestf_002", .test = TestMossdspRot_6_mossdsp_transformqanglestf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_6_mossdsp_transformqanglestf_003", .test = TestMossdspRot_6_mossdsp_transformqanglestf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_6_mossdsp_transformqanglestf_004", .test = TestMossdspRot_6_mossdsp_transformqanglestf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_6_mossdsp_transformqanglestf_005", .test = TestMossdspRot_6_mossdsp_transformqanglestf_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_6_mossdsp_transformqanglestf_006", .test = TestMossdspRot_6_mossdsp_transformqanglestf_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_6_mossdsp_transformqanglestf_007", .test = TestMossdspRot_6_mossdsp_transformqanglestf_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_6_mossdsp_transformqanglestf_008", .test = TestMossdspRot_6_mossdsp_transformqanglestf_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_6_mossdsp_transformqanglestf_009", .test = TestMossdspRot_6_mossdsp_transformqanglestf_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_6_mossdsp_transformqanglestf_010", .test = TestMossdspRot_6_mossdsp_transformqanglestf_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_7_mossdsp_transformanglesf_001", .test = TestMossdspRot_7_mossdsp_transformanglesf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_7_mossdsp_transformanglesf_002", .test = TestMossdspRot_7_mossdsp_transformanglesf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_7_mossdsp_transformanglesf_003", .test = TestMossdspRot_7_mossdsp_transformanglesf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_7_mossdsp_transformanglesf_004", .test = TestMossdspRot_7_mossdsp_transformanglesf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_7_mossdsp_transformanglesf_005", .test = TestMossdspRot_7_mossdsp_transformanglesf_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_7_mossdsp_transformanglesf_006", .test = TestMossdspRot_7_mossdsp_transformanglesf_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_7_mossdsp_transformanglesf_007", .test = TestMossdspRot_7_mossdsp_transformanglesf_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_7_mossdsp_transformanglesf_008", .test = TestMossdspRot_7_mossdsp_transformanglesf_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_7_mossdsp_transformanglesf_009", .test = TestMossdspRot_7_mossdsp_transformanglesf_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_7_mossdsp_transformanglesf_010", .test = TestMossdspRot_7_mossdsp_transformanglesf_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_8_mossdsp_transformanglestf_001", .test = TestMossdspRot_8_mossdsp_transformanglestf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_8_mossdsp_transformanglestf_002", .test = TestMossdspRot_8_mossdsp_transformanglestf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_8_mossdsp_transformanglestf_003", .test = TestMossdspRot_8_mossdsp_transformanglestf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_8_mossdsp_transformanglestf_004", .test = TestMossdspRot_8_mossdsp_transformanglestf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_8_mossdsp_transformanglestf_005", .test = TestMossdspRot_8_mossdsp_transformanglestf_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_8_mossdsp_transformanglestf_006", .test = TestMossdspRot_8_mossdsp_transformanglestf_006, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_8_mossdsp_transformanglestf_007", .test = TestMossdspRot_8_mossdsp_transformanglestf_007, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_8_mossdsp_transformanglestf_008", .test = TestMossdspRot_8_mossdsp_transformanglestf_008, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_8_mossdsp_transformanglestf_009", .test = TestMossdspRot_8_mossdsp_transformanglestf_009, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_8_mossdsp_transformanglestf_010", .test = TestMossdspRot_8_mossdsp_transformanglestf_010, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_9_mossdsp_transformqazimuthf_001", .test = TestMossdspRot_9_mossdsp_transformqazimuthf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_9_mossdsp_transformqazimuthf_002", .test = TestMossdspRot_9_mossdsp_transformqazimuthf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_9_mossdsp_transformqazimuthf_003", .test = TestMossdspRot_9_mossdsp_transformqazimuthf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_9_mossdsp_transformqazimuthf_004", .test = TestMossdspRot_9_mossdsp_transformqazimuthf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_9_mossdsp_transformqazimuthf_005", .test = TestMossdspRot_9_mossdsp_transformqazimuthf_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_10_mossdsp_transformqazimuthtf_001", .test = TestMossdspRot_10_mossdsp_transformqazimuthtf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_10_mossdsp_transformqazimuthtf_002", .test = TestMossdspRot_10_mossdsp_transformqazimuthtf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_10_mossdsp_transformqazimuthtf_003", .test = TestMossdspRot_10_mossdsp_transformqazimuthtf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_10_mossdsp_transformqazimuthtf_004", .test = TestMossdspRot_10_mossdsp_transformqazimuthtf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_10_mossdsp_transformqazimuthtf_005", .test = TestMossdspRot_10_mossdsp_transformqazimuthtf_005, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_multiplyqf_001", .test = TestMossdspRot_mossdsp_multiplyqf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_multiplyqf_002", .test = TestMossdspRot_mossdsp_multiplyqf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_multiplyqf_003", .test = TestMossdspRot_mossdsp_multiplyqf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_multiplyqf_004", .test = TestMossdspRot_mossdsp_multiplyqf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_multiplyqf_005", .test = TestMossdspRot_mossdsp_multiplyqf_005, .ntimes = 1},
#endif

#if 2
        {.name = "TestMossdspRot_mossdsp_multiplyqf_006", .test = TestMossdspRot_mossdsp_multiplyqf_006, .ntimes = 1},
#endif

#if 3
        {.name = "TestMossdspRot_mossdsp_multiplyqf_007", .test = TestMossdspRot_mossdsp_multiplyqf_007, .ntimes = 1},
#endif

#if 4
        {.name = "TestMossdspRot_mossdsp_multiplyqf_008", .test = TestMossdspRot_mossdsp_multiplyqf_008, .ntimes = 1},
#endif

#if 5
        {.name = "TestMossdspRot_mossdsp_multiplyqf_009", .test = TestMossdspRot_mossdsp_multiplyqf_009, .ntimes = 1},
#endif

#if 6
        {.name = "TestMossdspRot_mossdsp_multiplyqf_010", .test = TestMossdspRot_mossdsp_multiplyqf_010, .ntimes = 1},
#endif

#if 7
        {.name = "TestMossdspRot_mossdsp_multiplyqf_011", .test = TestMossdspRot_mossdsp_multiplyqf_011, .ntimes = 1},
#endif

#if 8
        {.name = "TestMossdspRot_mossdsp_multiplyqf_012", .test = TestMossdspRot_mossdsp_multiplyqf_012, .ntimes = 1},
#endif

#if 9
        {.name = "TestMossdspRot_mossdsp_multiplyqf_013", .test = TestMossdspRot_mossdsp_multiplyqf_013, .ntimes = 1},
#endif

#if 10
        {.name = "TestMossdspRot_mossdsp_multiplyqf_014", .test = TestMossdspRot_mossdsp_multiplyqf_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_001", .test = TestMossdspRot_mossdsp_multiplyqtf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_002", .test = TestMossdspRot_mossdsp_multiplyqtf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_003", .test = TestMossdspRot_mossdsp_multiplyqtf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_004", .test = TestMossdspRot_mossdsp_multiplyqtf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_005", .test = TestMossdspRot_mossdsp_multiplyqtf_005, .ntimes = 1},
#endif

#if 2
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_006", .test = TestMossdspRot_mossdsp_multiplyqtf_006, .ntimes = 1},
#endif

#if 3
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_007", .test = TestMossdspRot_mossdsp_multiplyqtf_007, .ntimes = 1},
#endif

#if 4
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_008", .test = TestMossdspRot_mossdsp_multiplyqtf_008, .ntimes = 1},
#endif

#if 5
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_009", .test = TestMossdspRot_mossdsp_multiplyqtf_009, .ntimes = 1},
#endif

#if 6
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_010", .test = TestMossdspRot_mossdsp_multiplyqtf_010, .ntimes = 1},
#endif

#if 7
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_011", .test = TestMossdspRot_mossdsp_multiplyqtf_011, .ntimes = 1},
#endif

#if 8
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_012", .test = TestMossdspRot_mossdsp_multiplyqtf_012, .ntimes = 1},
#endif

#if 9
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_013", .test = TestMossdspRot_mossdsp_multiplyqtf_013, .ntimes = 1},
#endif

#if 10
        {.name = "TestMossdspRot_mossdsp_multiplyqtf_014", .test = TestMossdspRot_mossdsp_multiplyqtf_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_conjugateqf_001", .test = TestMossdspRot_mossdsp_conjugateqf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_conjugateqf_002", .test = TestMossdspRot_mossdsp_conjugateqf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_conjugateqf_003", .test = TestMossdspRot_mossdsp_conjugateqf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_conjugateqf_004", .test = TestMossdspRot_mossdsp_conjugateqf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_conjugateqf_005", .test = TestMossdspRot_mossdsp_conjugateqf_005, .ntimes = 1},
#endif

#if 2
        {.name = "TestMossdspRot_mossdsp_conjugateqf_006", .test = TestMossdspRot_mossdsp_conjugateqf_006, .ntimes = 1},
#endif

#if 3
        {.name = "TestMossdspRot_mossdsp_conjugateqf_007", .test = TestMossdspRot_mossdsp_conjugateqf_007, .ntimes = 1},
#endif

#if 4
        {.name = "TestMossdspRot_mossdsp_conjugateqf_008", .test = TestMossdspRot_mossdsp_conjugateqf_008, .ntimes = 1},
#endif

#if 5
        {.name = "TestMossdspRot_mossdsp_conjugateqf_009", .test = TestMossdspRot_mossdsp_conjugateqf_009, .ntimes = 1},
#endif

#if 6
        {.name = "TestMossdspRot_mossdsp_conjugateqf_010", .test = TestMossdspRot_mossdsp_conjugateqf_010, .ntimes = 1},
#endif

#if 7
        {.name = "TestMossdspRot_mossdsp_conjugateqf_011", .test = TestMossdspRot_mossdsp_conjugateqf_011, .ntimes = 1},
#endif

#if 8
        {.name = "TestMossdspRot_mossdsp_conjugateqf_012", .test = TestMossdspRot_mossdsp_conjugateqf_012, .ntimes = 1},
#endif

#if 9
        {.name = "TestMossdspRot_mossdsp_conjugateqf_013", .test = TestMossdspRot_mossdsp_conjugateqf_013, .ntimes = 1},
#endif

#if 10
        {.name = "TestMossdspRot_mossdsp_conjugateqf_014", .test = TestMossdspRot_mossdsp_conjugateqf_014, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_001", .test = TestMossdspRot_mossdsp_conjugateqtf_001, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_002", .test = TestMossdspRot_mossdsp_conjugateqtf_002, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_003", .test = TestMossdspRot_mossdsp_conjugateqtf_003, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_004", .test = TestMossdspRot_mossdsp_conjugateqtf_004, .ntimes = 1},
#endif

#if 1
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_005", .test = TestMossdspRot_mossdsp_conjugateqtf_005, .ntimes = 1},
#endif

#if 2
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_006", .test = TestMossdspRot_mossdsp_conjugateqtf_006, .ntimes = 1},
#endif

#if 3
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_007", .test = TestMossdspRot_mossdsp_conjugateqtf_007, .ntimes = 1},
#endif

#if 4
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_008", .test = TestMossdspRot_mossdsp_conjugateqtf_008, .ntimes = 1},
#endif

#if 5
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_009", .test = TestMossdspRot_mossdsp_conjugateqtf_009, .ntimes = 1},
#endif

#if 6
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_010", .test = TestMossdspRot_mossdsp_conjugateqtf_010, .ntimes = 1},
#endif

#if 7
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_011", .test = TestMossdspRot_mossdsp_conjugateqtf_011, .ntimes = 1},
#endif

#if 8
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_012", .test = TestMossdspRot_mossdsp_conjugateqtf_012, .ntimes = 1},
#endif

#if 9
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_013", .test = TestMossdspRot_mossdsp_conjugateqtf_013, .ntimes = 1},
#endif

#if 10
        {.name = "TestMossdspRot_mossdsp_conjugateqtf_014", .test = TestMossdspRot_mossdsp_conjugateqtf_014, .ntimes = 1},
#endif

    };
    static PCU_Suite suite = {
        .name = "TestMossdspRot",
        .tests = tests,
        .ntests = sizeof(tests) / sizeof(tests[0]),
        .setup = (void *)0, .teardown = (void *)0, .initialize = (void *)0, .cleanup = (void *)0
    };
    return &suite;
}
