/*
 * Copyright (C) 2018 ETH Zurich, University of Bologna and GreenWaves Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __GAP_H__
#define __GAP_H__

typedef   signed short v2s __attribute__((vector_size (4)));
typedef unsigned short v2u __attribute__((vector_size (4)));

typedef   signed char  v4s __attribute__((vector_size (4)));
typedef unsigned char  v4u __attribute__((vector_size (4)));

#ifndef __EMUL__
//typedef   float16    v2h  __attribute__((vector_size (4)));
//typedef   float16alt v2ah __attribute__((vector_size (4)));

//typedef float16    f16;
//typedef float16alt f16a;
#endif

#ifndef __EMUL__
//#include "rt/rt_api.h"
typedef unsigned int rt_pointerT;
#else
typedef char* rt_pointerT;
#endif


#include "GapBuiltins.h"
#include "GapSystem.h"

#endif

