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
class TestEstimator {
    public:
        TestEstimator(float b, float f=50.0f , float a=0.0f, float g=0.0f, bool ag=false, float bvi=100.0f);
        void initialize(float (&a)[3]);
        void update(float (&imu)[9], long t = 0);
        void get(float (&q)[4]);
        
    private:
        unsigned int getq_count;
        unsigned int update_count;
};
