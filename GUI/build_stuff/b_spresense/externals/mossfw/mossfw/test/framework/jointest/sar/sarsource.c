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
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "component.h"
#include "sarsource.h"
#include "sar.h"

#define SARSOURCE_ACC_OUTPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPENAME_ACCEL + \
                                  MOSSFW_DATA_TYPEARRAY_SINGLE)
#define SARSOURCE_GYR_OUTPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPENAME_GYRO + \
                                  MOSSFW_DATA_TYPEARRAY_SINGLE)
#define SARSOURCE_MAG_OUTPUTTYPE (MOSSFW_DATA_TYPE_SHORT + \
                                  MOSSFW_DATA_TYPEGRP_V3 + \
                                  MOSSFW_DATA_TYPEARRAY_SINGLE)

static mossfw_onedata_t gyr[] = {
  {.v3s = {.x = -1652, .y = 1289, .z = -39}},
  {.v3s = {.x = 352, .y = -1699, .z = -1118}}, 
  {.v3s = {.x = 2221, .y = -873, .z = 65}},
  {.v3s = {.x = -28, .y = 569, .z = -713}},
  {.v3s = {.x = -265, .y = 312, .z = 1046}},
  {.v3s = {.x = -615, .y = 451, .z = -191}},
  {.v3s = {.x = 2015, -554, -419}},
  {.v3s = {.x = -142, .y = 20, .z = -185}}
};

static mossfw_onedata_t mag[] = {
  {.v3s = {.x = -7045, .y = 5504, .z = -2339}},
  {.v3s = {.x = -6919, .y = 5638, .z = -2079}},
  {.v3s = {.x = -7128, .y = 5590, .z = -2188}},
  {.v3s = {.x = -6937, .y = 5696, .z = -2078}}
};

static mossfw_onedata_t acc[] = {
  {.v3s = {.x = 958,  .y = 675,   .z = -1849}},
  {.v3s = {.x = 2753, .y = 2018,  .z = -5562}},
  {.v3s = {.x = 3416, .y = 2565,  .z = -7082}},
  {.v3s = {.x = 3495, .y = 2517,  .z = -6206}},
  {.v3s = {.x = 4083, .y = 2830,  .z = -5446}},
  {.v3s = {.x = 4316, .y = 3177,  .z = -5651}},
  {.v3s = {.x = 4339, .y = 3454,  .z = -6165}},
  {.v3s = {.x = 4544, .y = 3677,  .z = -5860}},
  {.v3s = {.x = 4541, .y = 3653,  .z = -5283}},
  {.v3s = {.x = 4487, .y = 3817,  .z = -5280}},
  {.v3s = {.x = 4658, .y = 4266,  .z = -5826}},
  {.v3s = {.x = 5102, .y = 4449,  .z = -5853}},
  {.v3s = {.x = 5884, .y = 4665,  .z = -4677}},
  {.v3s = {.x = 6252, .y = 5009,  .z = -3738}},
  {.v3s = {.x = 5231, .y = 4753,  .z = -3780}},
  {.v3s = {.x = 3925, .y = 4291,  .z = -3496}},
  {.v3s = {.x = 4192, .y = 4385,  .z = -2468}},
  {.v3s = {.x = 5033, .y = 4642,  .z = -1520}},
  {.v3s = {.x = 5650, .y = 5045,  .z = -1125}},
  {.v3s = {.x = 5893, .y = 5334,  .z = -1165}},
  {.v3s = {.x = 5260, .y = 5191,  .z = -1365}},
  {.v3s = {.x = 4907, .y = 5054,  .z = -916}},
  {.v3s = {.x = 5262, .y = 5140,  .z = -222}},
  {.v3s = {.x = 5624, .y = 5365,  .z = -629}},
  {.v3s = {.x = 5729, .y = 5498,  .z = -1494}},
  {.v3s = {.x = 5761, .y = 5614,  .z = -1599}},
  {.v3s = {.x = 5890, .y = 5531,  .z = -569}},
  {.v3s = {.x = 5882, .y = 5282,  .z = 388}},
  {.v3s = {.x = 5204, .y = 4959,  .z = 119}},
  {.v3s = {.x = 4516, .y = 4934,  .z = -1332}},
  {.v3s = {.x = 4973, .y = 5595,  .z = -2934}},
  {.v3s = {.x = 6164, .y = 6245,  .z = -3133}},

  {.v3s = {.x = 6185, .y = 5966,  .z = -2392}},
  {.v3s = {.x = 4916, .y = 5187,  .z = -2248}},
  {.v3s = {.x = 3782, .y = 4751,  .z = -3006}},
  {.v3s = {.x = 3460, .y = 4815,  .z = -3930}},
  {.v3s = {.x = 4188, .y = 5348,  .z = -4485}},
  {.v3s = {.x = 4978, .y = 5873,  .z = -4764}},
  {.v3s = {.x = 4729, .y = 5714,  .z = -4890}},
  {.v3s = {.x = 3820, .y = 4839,  .z = -4660}},
  {.v3s = {.x = 3230, .y = 4196,  .z = -4646}},
  {.v3s = {.x = 2642, .y = 4068,  .z = -5528}},
  {.v3s = {.x = 2142, .y = 4072,  .z = -6536}},
  {.v3s = {.x = 2531, .y = 4172,  .z = -6718}},
  {.v3s = {.x = 2944, .y = 4219,  .z = -6658}},
  {.v3s = {.x = 2826, .y = 3946,  .z = -6765}},
  {.v3s = {.x = 2535, .y = 3455,  .z = -6672}},
  {.v3s = {.x = 1584, .y = 2779,  .z = -6473}},
  {.v3s = {.x = 799,  .y = 2337,  .z = -6714}},
  {.v3s = {.x = 1405, .y = 2522,  .z = -7343}},
  {.v3s = {.x = 1401, .y = 2514,  .z = -8171}},
  {.v3s = {.x = 83,   .y = 1880,  .z = -8843}},
  {.v3s = {.x = -435, .y = 1381,  .z = -8871}},
  {.v3s = {.x = 212,  .y = 1469,  .z = -8579}},
  {.v3s = {.x = 430,  .y = 1387,  .z = -8109}},
  {.v3s = {.x = 70,   .y = 1006,  .z = -7817}},
  {.v3s = {.x = -352, .y = 678,   .z = -7977}},
  {.v3s = {.x = -603, .y = 524,   .z = -8332}},
  {.v3s = {.x = -160, .y = 828,   .z = -8649}},
  {.v3s = {.x = 158,  .y = 872,   .z = -8596}},
  {.v3s = {.x = 37,   .y = 539,   .z = -8321}},
  {.v3s = {.x = -30,  .y = 636,   .z = -8548}},
  {.v3s = {.x = 165,  .y = 1057,  .z = -9278}},
  {.v3s = {.x = 140,  .y = 979,   .z = -9566}},

  {.v3s = {.x = -508, .y = 295,   .z = -9260}},
  {.v3s = {.x = -1044, .y = -303,  .z = -8806}},
  {.v3s = {.x = -782, .y = -95,   .z = -8627}},
  {.v3s = {.x = 67,   .y = 538,   .z = -8560}},
  {.v3s = {.x = 834,  .y = 779,   .z = -8205}},
  {.v3s = {.x = 1446,  .y = 999,   .z = -8330}},
  {.v3s = {.x = 1870, .y = 1138,  .z = -8710}},
  {.v3s = {.x = 1766, .y = 924,   .z = -8266}},
  {.v3s = {.x = 1401, .y = 661,   .z = -7322}},
  {.v3s = {.x = 1337,  .y = 768,   .z = -7016}},
  {.v3s = {.x = 1578, .y = 1144,  .z = -7382}},
  {.v3s = {.x = 2117, .y = 1150,  .z = -7362}},
  {.v3s = {.x = 2934, .y = 1033,  .z = -6853}},
  {.v3s = {.x = 3699,  .y = 1249,  .z = -6780}},
  {.v3s = {.x = 4119, .y = 1587,  .z = -7186}},
  {.v3s = {.x = 3867, .y = 1525,  .z = -7325}},
  {.v3s = {.x = 3787, .y = 1384,  .z = -7173}},
  {.v3s = {.x = 4271,  .y = 1644,  .z = -6840}},
  {.v3s = {.x = 4388, .y = 1611,  .z = -6312}},
  {.v3s = {.x = 4273, .y = 1357,  .z = -6379}},
  {.v3s = {.x = 4295, .y = 1438,  .z = -7057}},
  {.v3s = {.x = 4560,  .y = 1642,  .z = -7153}},
  {.v3s = {.x = 5112, .y = 1774,  .z = -6771}},
  {.v3s = {.x = 5453, .y = 1712,  .z = -6542}},
  {.v3s = {.x = 5365, .y = 1337,  .z = -6160}},
  {.v3s = {.x = 5325,  .y = 1280,  .z = -5849}},
  {.v3s = {.x = 5394, .y = 1616,  .z = -5889}},
  {.v3s = {.x = 5548, .y = 1725,  .z = -5789}},
  {.v3s = {.x = 5618, .y = 1732,  .z = -5830}},
  {.v3s = {.x = 5761,  .y = 1850,  .z = -5987}},
  {.v3s = {.x = 6048, .y = 1896,  .z = -5614}},
  {.v3s = {.x = 5850, .y = 1653,  .z = -4996}},

  {.v3s = {.x = 5290, .y = 1558,  .z = -4761}},
  {.v3s = {.x = 5065,  .y = 1919,  .z = -5038}},
  {.v3s = {.x = 5135, .y = 2244,  .z = -5390}},
  {.v3s = {.x = 5011, .y = 2316,  .z = -5544}},
  {.v3s = {.x = 4753, .y = 2431,  .z = -5706}},
  {.v3s = {.x = 4201,  .y = 2401,  .z = -6018}},
  {.v3s = {.x = 3600, .y = 2300,  .z = -6508}},
  {.v3s = {.x = 3459, .y = 2553,  .z = -7075}},
  {.v3s = {.x = 3270, .y = 2300,  .z = -7079}},
  {.v3s = {.x = 2686,  .y = 1384,  .z = -6915}},
  {.v3s = {.x = 2218, .y = 1172,  .z = -7357}},
  {.v3s = {.x = 2170, .y = 1561,  .z = -7802}},
  {.v3s = {.x = 2107, .y = 1419,  .z = -7985}},
  {.v3s = {.x = 1990,  .y = 907,   .z = -8022}},
  {.v3s = {.x = 1657, .y = 517,   .z = -7817}},
  {.v3s = {.x = 1096, .y = 79,    .z = -7260}},
  {.v3s = {.x = 1266, .y = -213,  .z = -6651}},
  {.v3s = {.x = 1940,  .y = -22,   .z = -6886}},
  {.v3s = {.x = 2197, .y = 162,   .z = -7889}},
  {.v3s = {.x = 1721, .y = -255,  .z = -8593}},
  {.v3s = {.x = 785,  .y = -1055, .z = -8757}},
  {.v3s = {.x =  514,  .y = -1481, .z = -8652}},
  {.v3s = {.x = 1244, .y = -1052, .z = -8753}},
  {.v3s = {.x = 2109, .y = -721,  .z = -9043}},
  {.v3s = {.x = 1577, .y = -870,  .z = -9531}},
  {.v3s = {.x =  766,  .y = -1416, .z = -8983}},
  {.v3s = {.x = 925,  .y = -1845, .z = -7983}},
  {.v3s = {.x = 1092, .y = -1580, .z = -7975}},
  {.v3s = {.x = 1223, .y = -1381, .z = -7986}},
  {.v3s = {.x = 1288,  .y = -1391, .z = -7991}},
  {.v3s = {.x = 1205, .y = -1396, .z = -8033}},
  {.v3s = {.x = 1137, .y = -1366, .z = -8058}}
};

static mossfw_onedata_t *acc_data(size_t n)
{
  assert(n < sizeof acc / sizeof acc[0]);
  return &acc[n];
}

static mossfw_onedata_t *gyr_data(size_t n)
{
  assert(n < sizeof gyr / sizeof gyr[0]);
  return &gyr[n];
}

static mossfw_onedata_t *mag_data(size_t n)
{
  assert(n < sizeof mag / sizeof mag[0]);
  return &mag[n];
}

static size_t acc_data_num(void)
{
    return sizeof acc / sizeof acc[0];
}

static size_t gyr_data_num(void)
{
    return sizeof gyr / sizeof gyr[0];
}

static size_t mag_data_num(void)
{
    return sizeof mag / sizeof mag[0];
}

static int sarsource_operate_cb(struct mossfw_callback_op_s *in, unsigned long arg)
{
  int i;
  int j;
  int k;

  for (i = 0; i < mag_data_num(); i++)
    {
      for (j = 0; j < 2 && 2 * i + j < gyr_data_num(); j++)
        {
          size_t gidx = 2 * i + j;
          for (k = 0; k < 16 && 16 * gidx + k < acc_data_num(); k++)
            {
              mossfw_deliver_data(getsarpipeline()->sarsource.out[0], acc_data(16 * gidx + k));
            }
          mossfw_deliver_data(getsarpipeline()->sarsource.out[1], gyr_data(gidx));
        }
      mossfw_deliver_data(getsarpipeline()->sarsource.out[2], mag_data(i));
    }
}

void sarsource_create(struct component_s *com)
{
  if (com != NULL)
    {
      com->in_num  = 0;
      com->out_num = 3;
      com->op_num  = 1;
      com->in = NULL;
      com->out = malloc(com->out_num * sizeof(void *));
      com->op = malloc(com->op_num * sizeof(void *));
      com->out[SARSOURCECOMPONENT_ACC] = mossfw_output_create(SARSOURCE_ACC_OUTPUTTYPE);
      com->out[SARSOURCECOMPONENT_GYR] = mossfw_output_create(SARSOURCE_GYR_OUTPUTTYPE);
      com->out[SARSOURCECOMPONENT_MAG] = mossfw_output_create(SARSOURCE_MAG_OUTPUTTYPE);
      *com->op = mossfw_callback_op_create(sarsource_operate_cb, 0, false);
    }
}

void sarsource_delete(struct component_s *com)
{
    component_delete(com);
}
