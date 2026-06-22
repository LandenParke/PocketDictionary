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
#include <assert.h>
#include <float.h>
#include <stdio.h>
#include "testestimator.h"

TestEstimator::TestEstimator(float b, float f, float a, float g, bool ag, float bvi)
{
    assert((100.0f / 3.0f) * (1.0f - FLT_EPSILON) < f && f < (100.0f / 3.0f) * (1.0f + FLT_EPSILON));
    assert(-FLT_MIN < b && b < FLT_MIN);
    assert(-FLT_MIN < a && a < FLT_MIN);
    assert(-FLT_MIN < g && g < FLT_MIN);
    assert(ag == 0);
    assert(100.0f * (1.0f - FLT_EPSILON) < bvi && bvi < 100.0f * (1.0f + FLT_EPSILON));
    getq_count = 0;
    update_count = 0;
}

void TestEstimator::initialize(float (&a)[3])
{
    assert(getq_count == 0);
    assert(update_count == 0);
    assert(1.146822571754456f    * (1.0f - FLT_EPSILON) < a[0] && a[0] <  1.146822571754456f    * (1.0f + FLT_EPSILON));
    assert(8.080430626869202e-1f * (1.0f - FLT_EPSILON) < a[1] && a[1] <  8.080430626869202e-1f * (1.0f + FLT_EPSILON));
    assert(-2.213439464569092f   * (1.0f + FLT_EPSILON) < a[2] && a[2] < -2.213439464569092f    * (1.0f - FLT_EPSILON));
}

void TestEstimator::update(float (&imu)[9], long curr_time)
{
    assert(update_count < 4);
    if (update_count == 0) {
       assert( 3.804386615753174f    * (1.0f - FLT_EPSILON) < imu[0] && imu[0] <  3.804386615753174f    * (1.0f + FLT_EPSILON));
       assert( 5.758055210113525f    * (1.0f - FLT_EPSILON) < imu[1] && imu[1] <  5.758055210113525f    * (1.0f + FLT_EPSILON));
       assert(-5.222950935363770f    * (1.0f + FLT_EPSILON) < imu[2] && imu[2] < -5.222950935363770f    * (1.0f - FLT_EPSILON));
       assert( 1.196292042732239f    * (1.0f - FLT_EPSILON) < imu[3] && imu[3] <  1.196292042732239f    * (1.0f + FLT_EPSILON));
       assert( 3.739078044891357e-1  * (1.0f - FLT_EPSILON) < imu[4] && imu[4] <  3.739078044891357e-1  * (1.0f + FLT_EPSILON));
       assert( 1.806688547134399f    * (1.0f - FLT_EPSILON) < imu[5] && imu[5] <  1.806688547134399f    * (1.0f + FLT_EPSILON));
       assert( 2.569702148437500e+3f * (1.0f - FLT_EPSILON) < imu[6] && imu[6] <  2.569702148437500e+3f * (1.0f + FLT_EPSILON));
       assert(-7.739868164062500e+3f * (1.0f + FLT_EPSILON) < imu[7] && imu[7] < -7.739868164062500e+3f * (1.0f - FLT_EPSILON));
       assert(-6.046875000000000e+3f * (1.0f + FLT_EPSILON) < imu[8] && imu[8] < -6.046875000000000e+3f * (1.0f - FLT_EPSILON));
    } else if (update_count == 1) {
       assert( 8.008605003356934f    * (1.0f - FLT_EPSILON) < imu[0] && imu[0] <  8.008605003356934f    * (1.0f + FLT_EPSILON));
       assert( 2.237381458282471f    * (1.0f - FLT_EPSILON) < imu[1] && imu[1] <  2.237381458282471f    * (1.0f + FLT_EPSILON));
       assert(-3.515885114669800f    * (1.0f + FLT_EPSILON) < imu[2] && imu[2] < -3.515885114669800f    * (1.0f - FLT_EPSILON));
       assert( 7.648598551750183e-1f * (1.0f - FLT_EPSILON) < imu[3] && imu[3] <  7.648598551750183e-1f * (1.0f + FLT_EPSILON));
       assert(-3.089266829192638e-2f * (1.0f + FLT_EPSILON) < imu[4] && imu[4] < -3.089266829192638e-2f * (1.0f - FLT_EPSILON));
       assert(-6.093312501907349e-1f * (1.0f + FLT_EPSILON) < imu[5] && imu[5] < -6.093312501907349e-1f * (1.0f - FLT_EPSILON));
       assert( 2.284057617187500e+3f * (1.0f - FLT_EPSILON) < imu[6] && imu[6] <  2.284057617187500e+3f * (1.0f + FLT_EPSILON));
       assert(-7.601440429687500e+3f * (1.0f + FLT_EPSILON) < imu[7] && imu[7] < -7.601440429687500e+3f * (1.0f - FLT_EPSILON));
       assert(-6.194091796875000e+3f * (1.0f + FLT_EPSILON) < imu[8] && imu[8] < -6.194091796875000e+3f * (1.0f - FLT_EPSILON));

    } else if (update_count == 2) {
       assert( 8.465897560119629f    * (1.0f - FLT_EPSILON) < imu[0] && imu[0] <  8.465897560119629f    * (1.0f + FLT_EPSILON));
       assert( 3.955221176147461f    * (1.0f - FLT_EPSILON) < imu[1] && imu[1] <  3.955221176147461f    * (1.0f + FLT_EPSILON));
       assert(-1.460463047027588f    * (1.0f + FLT_EPSILON) < imu[2] && imu[2] < -1.460463047027588e+0f * (1.0f - FLT_EPSILON));
       assert( 2.087918370962143e-1f * (1.0f - FLT_EPSILON) < imu[3] && imu[3] <  2.087918370962143e-1f * (1.0f + FLT_EPSILON));
       assert(-6.562029123306274e-1f * (1.0f + FLT_EPSILON) < imu[4] && imu[4] < -6.562029123306274e-1f * (1.0f - FLT_EPSILON));
       assert(-4.836300611495972e-1f * (1.0f + FLT_EPSILON) < imu[5] && imu[5] < -4.836300611495972e-1f * (1.0f - FLT_EPSILON));
       assert( 2.403808593750000e+3f * (1.0f - FLT_EPSILON) < imu[6] && imu[6] <  2.403808593750000e+3f * (1.0f + FLT_EPSILON));
       assert(-7.831054687500000e+3f * (1.0f + FLT_EPSILON) < imu[7] && imu[7] < -7.831054687500000e+3f * (1.0f - FLT_EPSILON));
       assert(-6.141357421875000e+3f * (1.0f + FLT_EPSILON) < imu[8] && imu[8] < -6.141357421875000e+3f * (1.0f - FLT_EPSILON));
    } else if (update_count == 3) {
       assert( 8.904036521911621f    * (1.0f - FLT_EPSILON) < imu[0] && imu[0] <  8.904036521911621f    * (1.0f + FLT_EPSILON));
       assert( 2.794033288955688f    * (1.0f - FLT_EPSILON) < imu[1] && imu[1] <  2.794033288955688f    * (1.0f + FLT_EPSILON));
       assert(-4.177882075309753e-1f * (1.0f + FLT_EPSILON) < imu[2] && imu[2] < -4.177882075309753e-1f * (1.0f - FLT_EPSILON));
       assert( 2.024002522230148e-1f * (1.0f - FLT_EPSILON) < imu[3] && imu[3] <  2.024002522230148e-1f * (1.0f + FLT_EPSILON));
       assert(-1.523328125476837e-1f * (1.0f + FLT_EPSILON) < imu[4] && imu[4] < -1.523328125476837e-1f * (1.0f - FLT_EPSILON));
       assert(-2.450108341872692e-2f * (1.0f + FLT_EPSILON) < imu[5] && imu[5] < -2.450108341872692e-2f * (1.0f - FLT_EPSILON));
       assert( 2.282958984375000e+3f * (1.0f - FLT_EPSILON) < imu[6] && imu[6] <  2.282958984375000e+3f * (1.0f + FLT_EPSILON));
       assert(-7.621215820312500e+3f * (1.0f + FLT_EPSILON) < imu[7] && imu[7] < -7.621215820312500e+3f * (1.0f - FLT_EPSILON));
       assert(-6.257812500000000e+3f * (1.0f + FLT_EPSILON) < imu[8] && imu[8] < -6.257812500000000e+3f * (1.0f - FLT_EPSILON));
    }
    update_count = update_count + 1;
}

void TestEstimator::get(float (&Q)[4])
{
    if (getq_count == 0 && update_count == 2) {
        Q[0] =  1.281674355268478e-1f;
        Q[1] =  9.632248878479004e-1f;
        Q[2] = -9.576831012964249e-3f;
        Q[3] =  2.359643876552582e-1f;
    } else if (getq_count == 1 && update_count == 4) {
        Q[0] =  1.239004582166672e-1f;
        Q[1] =  9.668357968330383e-1f;
        Q[2] = -2.361268503591418e-3f;
        Q[3] =  2.233196347951889e-1f;
    } else {
        Q[0] = 0.0f;
        Q[1] = 0.0f;
        Q[2] = 0.0f;
        Q[3] = 0.0f;
    }
    getq_count = getq_count + 1;
    return;
}
