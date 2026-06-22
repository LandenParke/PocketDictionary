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
#ifndef __OUTPUTDATA_ERROR_H
#define __OUTPUTDATA_ERROR_H

#include "mossfw/sensorlib.h"
#include "eis_error/resampleinfo_error.h"

extern mossfw_data_v3f_t acc_error_expected[];
extern mossfw_data_v3f_t gyr_error_expected[];
extern struct resampleinfo_s resampleinfo_error_expected[];
extern mossfw_data_qf_t rot_error_expected[];
size_t sizeof_acc_error_expected(void);
size_t sizeof_gyr_error_expected(void);
size_t sizeof_resampleinfo_error_expected(void);
size_t sizeof_rot_error_expected(void);

#endif /*__OUTPUTDATA_ERROR_H */ 
