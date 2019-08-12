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
typedef void * rt_pointerT;
#endif


#include "GapBuiltins.h"
#include "GapSystem.h"

#endif

