#ifndef WORLD_H
#define WORLD_H

#include "param.h"
#include "particle_struct.h"
#include "grid.h"
#ifdef WORLD_IMPORT
#define EXTERN
#else
#define EXTERN extern
#endif

struct world {
        parameters* param;
        p_list* l;
        grid* g;
        float r;
        int screenWidth;
        int screenHeight;
};

EXTERN int world_alloc(parameters* param, struct world** world);
EXTERN void world_free(struct world* w);

#undef WORLD_IMPORT
#undef EXTERN


#endif
