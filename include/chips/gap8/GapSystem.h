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

#ifndef __GAP_SYSTEM_H__
#define __GAP_SYSTEM_H__

#ifndef __EMUL__
//#include "rt/rt_api.h"
#else
#include <stdlib.h>
#endif

#ifdef __EMUL__
typedef void * rt_pointerT;
typedef unsigned int rt_dma_copy_t;
typedef unsigned int rt_hyperram_req_t;
#else
typedef unsigned int rt_pointerT;
#endif


/* Memory spaces */
#ifdef __EMUL__
#define L2_MEM
#define L1_CL_MEM
#else
#define L2_MEM		__attribute__((section(".heapl2ram")))
#define L1_CL_MEM 	__attribute__((section(".heapsram")))
#endif

/* Memory Allocation */
#ifdef __EMUL__

#define rt_alloc(__where, __size) malloc(__size)
#define gap_allocL1(x) malloc(x)
#define gap_allocL2(x) malloc(x)
#define gap_freeL1(x, y) free((x))
#define gap_free_L2(x, y) free((x))
#else
#define gap_allocL1(x)     rt_alloc( RT_ALLOC_CL_DATA, (x) )
#define gap_allocL2(x)     rt_alloc( RT_ALLOC_L2_CL_DATA, (x) )
#define gap_freeL1(x, y)   rt_free(RT_ALLOC_CL_DATA, (x), (y))
#define gap_freeL2(x, y)   rt_free(RT_ALLOC_L2_CL_DATA, (x), (y))
#endif

/* Cluster id, Core Id */
#ifdef __EMUL__

#define gap_coreid()                    0
#define gap_clusterid()                 0
#define gap_ncore()                     1
#define gap_ncorem1()                   1

#else

#define gap_coreid()			__builtin_pulp_CoreId()
#define gap_clusterid()			__builtin_pulp_ClusterId()
#define gap_ncore()			__builtin_pulp_CoreCount()
#if defined (__gap9__)
#define gap_ncorem1()			__builtin_pulp_CoreCount_m1()
#else
#define gap_coreidm1()			__builtin_pulp_CoreId()
#endif

#endif

/* System */
#ifdef __EMUL__

typedef struct{
    void (*cb)(void *);
    void * cb_arg;
} __event_cb;

static __event_cb * event_get(void (*callback)(void *), void *arg){
    __event_cb * event = (__event_cb*) malloc (sizeof(__event_cb));
    event->cb = callback;
    event->cb_arg = arg;
    return event;
}


static int Private_call(void (*fn)(void *), void * arg, __event_cb * event)
{
    fn(arg);
    if(event) event->cb(event->cb_arg);
    return 1;
}

#define rt_team_fork(__cores, __fn, __arg) Private_call(__fn, __arg, 0)
#define rt_cluster_call(a,b,__fn,__arg,c,d,e,f,g) Private_call(__fn, __arg, g)
#define rt_event_get(a,b,c) event_get(b,c)
#define rt_event_t __event_cb

//#define __CALL(Entry, Arg)	Entry((Arg))

#define gap_setupbarrier(BarN, CoreM)
#define gap_waitbarrier(BarN)

#define gap_fc_starttimer()
#define gap_fc_resethwtimer()
#define gap_fc_readhwtimer()    ((int) 0)

#define gap_cl_starttimer()
#define gap_cl_resethwtimer()
#define gap_cl_readhwtimer()    ((int) 0)

#define rt_event_sched_init(x)
#define rt_event_alloc(x,y) 0
#define rt_nb_pe() 1
#define rt_cluster_mount(a,b,c,d)
#define rt_event_execute(a,b)
#define rt_team_barrier()



#else

//All this stuff should not stay here!!!!!!!!!!!!!!!

//#include "pmsis.h"

#ifdef __PULP_OS__
    #include "rt/rt_api.h"
#elif defined __FREERTOS__
    #include "drivers/hyperbus.h"
    #include "pmsis_cluster/dma/cl_dma.h"
    #include "pmsis_cluster/drivers/delegate/hyperbus/hyperbus_cl_internal.h"
#endif

extern struct pi_device *hyperram;

#define __cl_hyper_copy(a,b,c,d,e,f) \
        pi_cl_hyper_copy((struct pi_device *) a, (uint32_t) b, (void *) c, d, f, (pi_cl_hyper_req_t *) e)

#define __cl_hyper_copy_2d(a,b,c,d,e,f,g,h) \
        pi_cl_hyper_copy_2d((struct pi_device *) a, (uint32_t) b, (void *) c, d, e, f, h, (pi_cl_hyper_req_t *) g)

#define __cl_hyper_copy_wait        pi_cl_hyper_read_wait

#define CL_HYPER_EXT2LOC 1
#define CL_HYPER_LOC2EXT 0

#ifdef __FREERTOS__
static inline void __cl_dma_memcpy(uint32_t ext, uint32_t loc, uint16_t size, cl_dma_dir_e dir, uint8_t merge, cl_dma_copy_t *copy)
{
    copy->dir = dir;
    copy->merge = merge;
    copy->size = size;
    copy->id = 0;
    copy->loc = loc;
    copy->ext = ext;
    copy->stride = 0;
    copy->length = 0;
    cl_dma_memcpy(copy);
}


static inline void __cl_dma_memcpy_2d(uint32_t ext, uint32_t loc, uint16_t size, uint16_t stride, uint16_t length, cl_dma_dir_e dir, uint8_t merge, cl_dma_copy_t *copy)
{
    copy->dir = dir;
    copy->merge = merge;
    copy->size = size;
    copy->id = 0;
    copy->loc = loc;
    copy->ext = ext;
    copy->stride = stride;
    copy->length = length;
    cl_dma_memcpy_2d(copy);
}

#endif

//////////////////////////////////////////////

#define __CALL(Entry, Arg)

// #define rt_alloc(Space, Size)		malloc((Size))
// #define rt_alloc_align(Space, Size)	malloc((Size))
// #define rt_free(Space, Pointer, Size)	free((Pointer))

//This is not used anywehre
//#define gap_setupbarrier(BarN, CoreM)   eu_bar_setup(eu_bar_addr(BarN), CoreM)
#ifdef __PULP_OS__
    #define gap_waitbarrier(BarN)           rt_team_barrier(BarN) //eu_bar_trig_wait_clr(eu_bar_addr(BarN))
#elif  defined __FREERTOS__
    #define gap_waitbarrier(BarN)           CLUSTER_SynchBarrier()
#else //pmsis
    #define gap_waitbarrier(BarN)           cl_team_barrier(BarN) 
#endif


#define gap_fc_starttimer()             timer_start(timer_base_fc(0, 0))
#define gap_fc_resethwtimer()           timer_reset(timer_base_fc(0, 0))
#define gap_fc_readhwtimer()            timer_count_get(timer_base_fc(0, 0))
#define gap_cl_starttimer()             timer_start(timer_base_cl(0, 0, 1))
#define gap_cl_resethwtimer()           timer_reset(timer_base_cl(0, 0, 1))
#define gap_cl_readhwtimer()            timer_count_get(timer_base_cl(0, 0, 1))

#endif


/* Memcopy */
#ifdef __EMUL__

typedef struct {
    void (*callback)(void *);
} rt_event_sched_t;


#define RT_DMA_DIR_LOC2EXT 0
#define RT_DMA_DIR_EXT2LOC 1

/* Internal counter for debug purpose, track the amount of transfered data to/from L2/L3 */
unsigned int __L3_Read, __L3_Write, __L2_Read, __L2_Write;

static int Private_gap_dma_memcpy(rt_pointerT ext, rt_pointerT loc, unsigned short size, int ext2loc, int L3)

{
        int i;
        char *To   = (ext2loc==RT_DMA_DIR_EXT2LOC)?((char *) loc):((char *) ext);
        char *From = (ext2loc==RT_DMA_DIR_EXT2LOC)?((char *) ext):((char *) loc);

	if (ext2loc==RT_DMA_DIR_EXT2LOC) {
		if (L3) __L3_Read += size; else __L2_Read += size;
	} else {
		if (L3) __L3_Write += size; else __L2_Write += size;
	}

        for (i=0; i<size; i++) To[i] = From[i];
        return 1; 
}

static int Private_gap_dma_memcpy_2d(rt_pointerT ext, rt_pointerT loc, unsigned short size, unsigned int stride, unsigned short length, int ext2loc, int L3)

{
        int CopyIn = (ext2loc==RT_DMA_DIR_EXT2LOC);
        char *To   = CopyIn?((char *) loc):((char *) ext);
        char *From = CopyIn?((char *) ext):((char *) loc);
        int i, j, Chunk;

	if (ext2loc==RT_DMA_DIR_EXT2LOC) {
		if (L3) __L3_Read += size; else __L2_Read += size;
	} else {
		if (L3) __L3_Write += size; else __L2_Write += size;
	}
	for (Chunk=0; Chunk<size; Chunk+=length)  {
                for (i=0; i<length; i++) To[i] = From[i];
                if (CopyIn) {
			From += stride; To += length;
		} else {
			To += stride; From += length;
		}
        }
        return 1;
}

typedef int rt_hyperram_t ;
typedef int rt_hyperram_conf_t;

#define rt_hyperram_open(...) 1
#define rt_hyperram_conf_init(...) 1
#define rt_hyperram_close(...) 1

#define rt_dma_memcpy(ExtAddr, LocAddr, Size, Dir, Merge, Descr) Private_gap_dma_memcpy((ExtAddr), (LocAddr), (Size), (Dir), 0)
#define rt_dma_memcpy_2d(ExtAddr, LocAddr, Size, Stride, Length, Dir, Merge, Descr) Private_gap_dma_memcpy_2d((ExtAddr), (LocAddr), (Size), (Stride), (Length), (Dir), 0)
#define rt_dma_wait(Descr)

#define __rt_hyperram_cluster_copy(Dev, ExtAddr, LocAddr, Size, Descr, Dir) Private_gap_dma_memcpy((ExtAddr), (LocAddr), (Size), (Dir), 1)
#define __rt_hyperram_cluster_copy_2d(Dev, ExtAddr, LocAddr, Size, Stride, Length, Descr, Dir) Private_gap_dma_memcpy_2d((ExtAddr), (LocAddr), (Size), (Stride), (Length), (Dir), 1)
#define rt_hyperram_cluster_wait(Descr)
#endif


#endif

