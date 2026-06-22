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
#############################################################################/
DIR=../../..
FRAMEWORK=$(DIR)/src/mossfw
SENSORLIBSRC=$(DIR)/src/mossfw

FRAMEWORKOBJ=mossfw_component.o \
             mossfw_memoryallocator.o \
             mossfw_ringbuff.o \
             mossfw_ringbuffary.o \
             mossfw_debug.o \
             mossfw_lock.o \

SENSORLIBOBJ= mosscalib.o \
              mossdsp_integral.o \
              mossdsp_rot.o \
              mossdsp_axis.o \
              mossdsp_resampling.o \
              mossdsp_filter.o \

CSRCS = sar/sar.c sar/adjustgyro.c sar/average.c sar/transformaxismatrix.c sar/transformaxisquaternion.c sar/decimate.c \
    sar/testestimatorcomponent.c sar/multiplyqf.c sar/transformquaternion.c sar/sarresult.c sar/sarsource.c \
    component.c \
    uc/uc.c uc/calibrationacc.c uc/calculatetiltangle.c uc/calculatetiltgravity.c uc/ucsource.c uc/ucresult.c \
    eis/eis.c eis/eissource.c eis/eiscalibration.c eis/lpf.c eis/transform.c eis/adjustline.c eis/selector.c \
    eis/transformaxes.c eis/dcoffset.c eis/averageacc.c eis/stableacc.c eis/estimateposeacc.c \
    eis/complementaryfilter.c eis/axisseparation.c eis/viewpoint.c eis/poseresample.c eis/eissink.c eis/outputdata.c \
    eis/eisallocator.c \
    attitude/attitude_averageacc.c attitude/attitude_complementaryfilter.c attitude/attitude_eiscalibration.c \
    attitude/attitude_estimateposeacc.c attitude/attitude_lpf.c attitude/attitude_outputdata.c attitude/attitude_stableacc.c \
    attitude/attitude_transform.c attitude/attitude.c attitude/attituderesult.c attitude/attitudesource.c \
    attitude_error/attitude_error_averageacc.c attitude_error/attitude_error_complementaryfilter.c attitude_error/attitude_error_eiscalibration.c \
    attitude_error/attitude_error_estimateposeacc.c attitude_error/attitude_error_lpf.c attitude_error/attitude_error_outputdata.c attitude_error/attitude_error_stableacc.c \
    attitude_error/attitude_error_transform.c attitude_error/attitude_error.c attitude_error/attitude_error_result.c attitude_error/attitude_error_source.c \
    uc_error/uc_error.c uc_error/calibrationacc_error.c uc_error/calculatetiltangle_error.c uc_error/calculatetiltgravity_error.c \
    uc_error/ucsource_error.c uc_error/ucresult_error.c \
    eis_error/eis_error.c eis_error/eissource_error.c eis_error/eiscalibration_error.c eis_error/lpf_error.c eis_error/transform_error.c \
    eis_error/adjustline_error.c eis_error/selector_error.c eis_error/transformaxes_error.c eis_error/dcoffset_error.c eis_error/averageacc_error.c \
    eis_error/stableacc_error.c eis_error/estimateposeacc_error.c eis_error/complementaryfilter_error.c eis_error/axisseparation_error.c \
    eis_error/viewpoint_error.c eis_error/poseresample_error.c eis_error/eissink_error.c eis_error/outputdata_error.c eis_error/eisallocator_error.c 
CXXSRCS = sar/testestimator_frameworkjointest.cpp  sar/testestimatorif.cpp
MAINSRC = main.c

OBJ = $(MAINSRC:.c=.o) $(CSRCS:.c=.o) $(CXXSRCS:.cpp=.o) $(FRAMEWORKOBJ) $(SENSORLIBOBJ)

CFLAGS=-I ../../../include -I. -I uc -I sar -g -fdiagnostics-color=always -DERROR=-1 -DOK=0
#-MMD -O2 -mfma
CXXFLAGS := $(CFLAGS)
LDFLAGS=-lpthread

all: jointest
	./jointest

jointest : $(OBJ)
	$(CXX) -g -o $@ $(OBJ) $(LDFLAGS)

mossfw_component.o : $(FRAMEWORK)/mossfw_component.c
	$(CC) $(CFLAGS) -c -o $@ $(FRAMEWORK)/mossfw_component.c

mossfw_memoryallocator.o : $(FRAMEWORK)/mossfw_memoryallocator.c
	$(CC) $(CFLAGS) -c -o $@ $(FRAMEWORK)/mossfw_memoryallocator.c

mossfw_ringbuff.o : $(FRAMEWORK)/mossfw_ringbuff.c
	$(CC) $(CFLAGS) -c -o $@ $(FRAMEWORK)/mossfw_ringbuff.c

mossfw_lock.o : $(FRAMEWORK)/mossfw_lock.c
	$(CC) $(CFLAGS) -c -o $@ $(FRAMEWORK)/mossfw_lock.c

mossfw_ringbuffary.o : $(FRAMEWORK)/mossfw_ringbuffary.c
	$(CC) $(CFLAGS) -c -o $@ $(FRAMEWORK)/mossfw_ringbuffary.c

mossfw_debug.o : $(FRAMEWORK)/mossfw_debug.c
	$(CC) $(CFLAGS) -c -o $@ $(FRAMEWORK)/mossfw_debug.c

mosscalib.o : $(SENSORLIBSRC)/mosscalib.c
	$(CC) $(CFLAGS) -c -o $@ $(SENSORLIBSRC)/mosscalib.c

mossdsp_integral.o : $(SENSORLIBSRC)/mossdsp_integral.c
	$(CC) $(CFLAGS) -c -o $@ $(SENSORLIBSRC)/mossdsp_integral.c

mossdsp_rot.o : $(SENSORLIBSRC)/mossdsp_rot.c
	$(CC) $(CFLAGS) -c -o $@ $(SENSORLIBSRC)/mossdsp_rot.c

mossdsp_axis.o : $(SENSORLIBSRC)/mossdsp_axis.c
	$(CC) $(CFLAGS) -c -o $@ $(SENSORLIBSRC)/mossdsp_axis.c

mossdsp_resampling.o : $(SENSORLIBSRC)/mossdsp_resampling.c
	$(CC) $(CFLAGS) -c -o $@ $(SENSORLIBSRC)/mossdsp_resampling.c

mossdsp_filter.o : $(SENSORLIBSRC)/mossdsp_filter.c
	$(CC) $(CFLAGS) -c -o $@ $(SENSORLIBSRC)/mossdsp_filter.c

dep: $(CSRCS) $(CXXSRCS)
	$(CC) -MM $(CFLAGS) $(CSRCS) > Make.dep
	$(CXX) -MM $(CXXFLAGS) $(CXXSRCS) >> Make.dep

clean :
	$(RM) jointest
	$(RM) $(OBJ)

include Make.dep
