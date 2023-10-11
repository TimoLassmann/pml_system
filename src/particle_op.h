#ifndef PARTICLE_OP_H
#define PARTICLE_OP_H

#include "particle_struct.h"

#ifdef PARTICLE_OP_IMPORT
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int p_list_add_random_particles(p_list* l ,float velocity, int n);
EXTERN int p_list_add_random_particles_at_mouse(p_list *l, float velocity,int n);

#undef PARTICLE_OP_IMPORT
#undef EXTERN


#endif
