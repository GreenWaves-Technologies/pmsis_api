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

#ifndef __PMSIS_TYPES__H__
#define __PMSIS_TYPES__H__

#include "inttypes.h"

/**
 * @ingroup PMSIS_OS
 */

/**
 * @defgroup PMSISTypes PMSIS common types
 */

/**
 * @addtogroup PMSISTypes
 * @{
 */

struct pmsis_device;

// device struct, it wont stay here
typedef struct pmsis_device {
    struct pmsis_device_api *api; // function pointers
    void *config; // driver conf: might be filled either using device tree or manually
    void *data; // driver data
} pmsis_device_t;


/**@{*/


/// @cond IMPLEM

struct pmsis_event_kernel_wrap;

typedef struct fc_task fc_task_t;
typedef struct fc_task mc_task_t;

typedef void (*callback_t)(void *arg);

typedef struct spinlock {
    int32_t *lock_ptr; // with test and set mask
    int32_t *release_ptr; // standard pointer
} spinlock_t;

typedef struct pmsis_device_config {
    const char *name; // to open, FIXME: device tree
    // initialize the device struct (api+ init data) using init_conf
    int (*init)(struct pmsis_device *device);
    const void *init_conf;
} pmsis_device_config_t;


typedef uint32_t (*device_rw_func)(struct pmsis_device *device, uintptr_t size,
        const void *addr, const void *buffer);

typedef uint32_t (*device_ioctl_func)(struct pmsis_device *device,
        uint32_t func_id,
        void *arg);

typedef uint32_t (*device_rw_func_async)(struct pmsis_device *device,
        uintptr_t size, const void *addr, const void *buffer, fc_task_t *async);

typedef uint32_t (*device_ioctl_func_async)(struct pmsis_device *device,
        uint32_t func_id, void *arg, fc_task_t *async);

typedef int (*open_func)(struct pmsis_device *device, void *conf);
typedef int (*close_func)(struct pmsis_device *device);

typedef int (*open_func_async)(struct pmsis_device *device, void *conf,
        fc_task_t *async);
typedef int (*close_func_async)(struct pmsis_device *device, fc_task_t *async);

// pmsis device minimal api: used for basic inheritance
typedef struct pmsis_device_api {
    int (*open)(struct pmsis_device *device, void *conf);
    int (*close)(struct pmsis_device *device);
    int (*open_async)(struct pmsis_device *device, void *conf, fc_task_t *async);
    int (*close_async)(struct pmsis_device *device, fc_task_t *async);
    uint32_t (*read)(struct pmsis_device *device,
            uintptr_t size, const void *addr, const void *buffer, fc_task_t *async);
    uint32_t (*write)(struct pmsis_device *device,
            uint32_t func_id, void *arg, fc_task_t *async);
    uint32_t (*ioctl)(struct pmsis_device *device, uint32_t func_id, void *arg);
    uint32_t (*ioctl_async)(struct pmsis_device *device,
            uint32_t func_id, void *arg, fc_task_t *async);
    void *specific_api;
} pmsis_device_api_t;

/** Task types **/
typedef void (*__pmsis_mutex_func)(void *mutex_object);

typedef struct pmsis_mutex {
    void *mutex_object;
    __pmsis_mutex_func take;
    __pmsis_mutex_func release;
} pmsis_mutex_t;

typedef struct pmsis_spinlock {
    uint32_t lock;
} pmsis_spinlock_t;

struct pmsis_event_kernel_wrap {
    void *__os_native_task;
    void (*event_kernel_main)(struct pmsis_event_kernel_wrap*);
    // real event kernel (might be just an api stub for pulpOS)
    void *priv;
};

enum fc_task_id {
    FC_TASK_CALLBACK_ID,
};

typedef struct fc_task{
    int8_t done;
    pmsis_mutex_t wait_on;
    int id;
    uintptr_t arg[4];
} fc_task_t;

/// @endcond

#endif
