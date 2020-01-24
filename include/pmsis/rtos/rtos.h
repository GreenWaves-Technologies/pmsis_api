/*
 * Copyright (C) 2018 GreenWaves Technologies
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

#ifndef __PMSIS_OS_H__
#define __PMSIS_OS_H__

#include <stdint.h>
#include <stddef.h>

#include "pmsis/rtos/malloc/pmsis_malloc.h"
#include "pmsis/rtos/malloc/pmsis_l1_malloc.h"
#include "pmsis/rtos/malloc/pmsis_l2_malloc.h"
#if (defined(__GAP8__) && defined(__USE_TCDM_MALLOC__))
    #include "pmsis/rtos/malloc/pmsis_fc_tcdm_malloc.h"
#endif
#include "pmsis/rtos/os_frontend_api/os.h"
#include "pmsis/rtos/os_frontend_api/freq.h"
#include "pmsis/rtos/os_frontend_api/pmsis_time.h"
#include "pmsis/rtos/event_kernel/event_kernel.h"

#endif  /* __PMSIS_OS_H__ */
