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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern PCU_Suite* TestMosscalib(void);
extern PCU_Suite* TestMossdspFilter(void);
extern PCU_Suite* TestMossdspIntegral(void);
extern PCU_Suite* TestMossdspResampling(void);
extern PCU_Suite* TestMossdspRot(void);
extern PCU_Suite* TestMossdspAxis(void);

static const PCU_SuiteMethod suites[] = {
    TestMosscalib,
    TestMossdspFilter,
    TestMossdspIntegral,
    TestMossdspResampling,
    TestMossdspRot,
    TestMossdspAxis
};

int main(int argc, char *argv[])
{
    int verbose_flag = 0;
    int interactive_flag = 0;
    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            verbose_flag = 1;
        }
        if (strcmp(argv[i], "-i") == 0) {
            interactive_flag = 1;
        }
        if (strcmp(argv[i], "-h") == 0) {
            const char* binname = strrchr(argv[0], '\\');
            printf("\n");
            printf("%s [-i] [-v] [-h]\n", binname ? binname + 1 : argv[0]);
            printf("    -h:  show this message and exit\n");
            printf("    -i:  interactive mode\n");
            printf("    -v:  verbose mode\n");
            printf("\n");
            return 0;
        }
    }

    PCU_set_putchar(putchar);
    PCU_set_getchar(getchar);
    PCU_enable_color();
    PCU_set_verbose(verbose_flag);
    
    if (interactive_flag) {
        return PCU_console_run(suites, sizeof(suites) / sizeof(suites[0]));
    } else {
        return PCU_run(suites, sizeof(suites) / sizeof(suites[0]));
    }
}
