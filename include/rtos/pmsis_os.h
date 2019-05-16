#ifndef __PMSIS_OS_H__

#include <stdint.h>
#include <stddef.h>
#include "pmsis.h"

#include "rtos/malloc/pmsis_malloc.h"
#include "rtos/malloc/pmsis_l1_malloc.h"
#include "rtos/malloc/pmsis_l2_malloc.h"
#ifdef __GAP8__
    #include "pmsis_fc_tcdm_malloc.h"
#endif
#include "rtos/os_frontend_api/pmsis_task.h"
#include "rtos/event_kernel/event_kernel.h"

#include "pmsis_backend_native_types.h"
#include "pmsis_backend_native_task_api.h"

/** Kickoff the system : Must be called in the main
 * Completely OS dependant might do anything from a function call to main task 
 * creation */
static inline int pmsis_kickoff(void *arg);

/** FC_CLUSTER_ID Definitions */
#if defined(__GAP8__)
#define FC_CLUSTER_ID                 32                /**< FC CLuster ID */
#elif defined(__GAP9__)
#define FC_CLUSTER_ID                 31                /**< FC CLuster ID */
#endif

/**
  \ingroup  CMSIS_Core_IDFunctionInterface
  \defgroup CMSIS_Core_IDFunctions ID Functions
  \brief    Functions that manage Cluster and Core ID.
  @{
 */

static inline uint32_t __native_core_id();

static inline uint32_t __native_cluster_id();

static inline uint32_t __native_is_fc();

static inline uint32_t __native_cluster_nb_cores();

#ifndef PMSIS_NO_INLINE_INCLUDE

/** Kickoff the system : Must be called in the main
 * Completely OS dependant might do anything from a function call to main task 
 * creation */
static inline int pmsis_kickoff(void *arg)
{
    return __os_native_kickoff(arg);
}

/**
  \ingroup  CMSIS_Core_IDFunctionInterface
  \defgroup CMSIS_Core_IDFunctions ID Functions
  \brief    Functions that manage Cluster and Core ID.
  @{
 */

static inline uint32_t __native_core_id() {
  int hart_id;
  asm volatile ("csrr %0, 0x014" : "=r" (hart_id) : );
  return hart_id & 0x1f;
}

static inline uint32_t __native_cluster_id() {
  int hart_id;
  asm volatile ("csrr %0, 0x014" : "=r" (hart_id) : );
  return (hart_id >> 5) & 0x3f;
}

static inline uint32_t __native_is_fc() {
  return ( __native_cluster_id() == FC_CLUSTER_ID);
}

static inline uint32_t __native_native_nb_cores() {
  return NBCORES;
}

#endif

#endif