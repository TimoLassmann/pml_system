#ifndef PARTICLE_STRUCT_H
#define PARTICLE_STRUCT_H

#include <raylib.h>
#include <stdint.h>

#ifdef PARTICLE_STRUCT_IMPORT
#define EXTERN
#else
#define EXTERN extern
#endif

typedef struct particle {
        Vector2 position;
        Vector2 n_pos;
        Vector2 speed;
        Vector2 direction;
        /* float angle; */
        Color color;
        uint32_t id;
} particle;

typedef struct p_list {
        particle *particles;
        int n;
        int n_alloc;
} p_list;


#undef PARTICLE_STRUCT_IMPORT
#undef EXTERN


#endif
