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
#include <stdlib.h>
#include <assert.h>
#include "mossfw/mossfw_component.h"
#include "mossfw/sensorlib.h"
#include "component.h"

void component_delete(struct component_s *com)
{
  size_t i;

  if (com != NULL)
    {
      for (i = 0; i < com->op_num; i++)
        {
          mossfw_callback_op_delete(*(com->op + i));
        }
      for (i = 0; i < com->in_num; i++)
        {
          mossfw_input_delete(*(com->in + i));
        }
      for (i = 0; i < com->out_num; i++)
        {
          mossfw_output_delete(*(com->out + i));
        }
      free(com->in);
      free(com->out);
      free(com->op);
      com->in    = NULL;
      com->out   = NULL;
      com->op    = NULL;
      com->in_num    = 0;
      com->out_num   = 0;
      com->op_num    = 0;
    }
}
