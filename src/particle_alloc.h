#ifndef PARTICLE_ALLOC_H
#define PARTICLE_ALLOC_H


#include "particle_struct.h"

#ifdef PARTICLE_ALLOC_IMPORT
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int p_list_alloc(p_list **list, int size);
EXTERN void p_list_free(p_list *l);

#undef PARTICLE_ALLOC_IMPORT
#undef EXTERN


#endif
