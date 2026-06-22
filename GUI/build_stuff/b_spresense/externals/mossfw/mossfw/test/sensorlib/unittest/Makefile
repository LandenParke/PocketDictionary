#############################################################################
#  Copyright 2023 Sony Semiconductor Solutions Corporation
#
#  Licensed to the Apache Software Foundation (ASF) under one or more
#  contributor license agreements.  See the NOTICE file distributed with
#  this work for additional information regarding copyright ownership.  The
#  ASF licenses this file to you under the Apache License, Version 2.0 (the
#  "License"); you may not use this file except in compliance with the
#  License.  You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
#  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
#  License for the specific language governing permissions and limitations
#  under the License.
#
##############################################################################
# target all (default): build unittest and execute unit test
# target cov: coverage report in lcov/

.SUFFIXES: .gcno

OBJ = PCUnit/PCUnit/PCUnit.o \
      PCUnit/PCUnit/PCU_Libc.o \
      PCUnit/PCUnit/PCU_Suite.o \
      PCUnit/PCUnit/PCU_Test.o \
      main.o \
      test_mosscalib.o \
      test_mossdsp_filter.o \
      test_mossdsp_integral.o \
      test_mossdsp_rot.o \
      test_mossdsp_axis.o \
      test_mossdsp_resampling.o \
      mossdsp_rot.o \
      mossdsp_integral.o \
      mossdsp_resampling.o

INCLUDE = -I ./PCUnit/PCUnit \
          -I ../../../include \
          -I ../../../src/mossfw

CFLAGS = $(INCLUDE) -DUNITTEST -Wall -Wextra -Werror
LDFLAGS = -lm --coverage

all: unittest
	./unittest

cov: lcov/index.html

unittest: $(OBJ)
	$(CC) $(INCLUDE) $(OBJ) $(LDFLAGS) -o $@

$(OBJ:.o=.gcda): $(OBJ:.o=.gcno) unittest
	./unittest

lcov/index.html: lcov.info
	genhtml -o lcov --branch-coverage -p C: lcov.info

lcov.info: $(OBJ:.o=.gcda)
	lcov -c -d . --rc lcov_branch_coverage=1 -o lcov.info

.c.gcno:
	$(CC) $(CFLAGS) --coverage -c -o $(<:.c=.o) $<

mossdsp_rot.o : ../../../src/mossfw/mossdsp_rot.c
	$(CC) -c -o $@ $(CFLAGS) ../../../src/mossfw/mossdsp_rot.c
mossdsp_integral.o : ../../../src/mossfw/mossdsp_integral.c
	$(CC) -c -o $@ $(CFLAGS) ../../../src/mossfw/mossdsp_integral.c
mossdsp_resampling.o : ../../../src/mossfw/mossdsp_resampling.c
	$(CC) -c -o $@ $(CFLAGS) ../../../src/mossfw/mossdsp_resampling.c
mossdsp_rot.gcno: ../../../src/mossfw/mossdsp_rot.c
	$(CC) -c -o $(@:.gcno=.o) $(CFLAGS) --coverage ../../../src/mossfw/mossdsp_rot.c
mossdsp_integral.gcno : ../../../src/mossfw/mossdsp_integral.c
	$(CC) -c -o $(@:.gcno=.o) $(CFLAGS) --coverage ../../../src/mossfw/mossdsp_integral.c
mossdsp_resampling.gcno : ../../../src/mossfw/mossdsp_resampling.c
	$(CC) -c -o $(@:.gcno=.o) $(CFLAGS) --coverage ../../../src/mossfw/mossdsp_resampling.c

clean:
	rm -f lcov.info
	rm -rf lcov
	rm -f $(OBJ:.o=.gcda)
	rm -f $(OBJ:.o=.gcno)
	rm -f unittest
	rm -f $(OBJ)
