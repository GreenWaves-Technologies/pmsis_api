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

#ifndef __PMSIS_L1_FC_MALLOC_H__
#define __PMSIS_L1_FC_MALLOC_H__

#include "pmsis/rtos/malloc/pmsis_malloc_internal.h"

#if !defined(__FC_MALLOC_NATIVE__) || (__FC_MALLOC_NATIVE__ == 0)

/**
* @ingroup groupRTOS
*/

/**
 * @defgroup MemAlloc Memory allocation
 *
 * This provides support for memory allocation.
 */

/**        
 * @addtogroup MemAlloc
 * @{        
 */

/**@{*/

/** \brief Allocate FC L1 memory.
 *
 * The allocated memory is 4-bytes aligned.
 * The caller has to provide back the size of the allocated chunk when freeing
 * it.
 * This will allocate in the closest memory for the FC, which can vary
 * depending on the chip. Check the chip-specific section for more information.
 *
 * \param size   The size in bytes of the memory to be allocated.
 * \return The allocated chunk or NULL if there was not enough memory available.
 */
void *pi_fc_l1_malloc(int size);

/** \brief Free FC L1 memory.
 *
 * \param chunk  The chunk to be freed.
 * \param size   The size in bytes of the memory to be freed.
 */
void pi_fc_l1_free(void *chunk, int size);

/** \brief Allocate FC L1 memory.
 *
 * The allocated memory is aligned on the specified number of bytes.
 * The caller has to provide back the size of the allocated chunk when freeing
 * it.
 *
 * \param size   The size in bytes of the memory to be allocated.
 * \param align  The alignment in bytes.
 * \return The allocated chunk or NULL if there was not enough memory available.
 */
void *pi_fc_l1_malloc_align(int size, int align);

//!@}

/**        
 * @} 
 */

#endif

#endif  /* __PMSIS_l1_fc_MALLOC_H__ */
