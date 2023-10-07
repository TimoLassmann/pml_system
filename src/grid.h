#ifndef GRID_H
#define GRID_H

#include <stdint.h>

#ifdef GRID_IMPORT
#define EXTERN
#else
#define EXTERN extern
#endif


typedef struct grid_cell {
        uint32_t* id;
        int n;
        int n_alloc;
} grid_cell;

typedef struct grid {
        grid_cell*** cells;
        float h;
        float w;
        float cell_size;
        int n_row;
        int n_col;
} grid;


EXTERN  int grid_alloc(grid **g, float h, float w, float cell_size);
EXTERN void grid_free(grid *n);
#undef GRID_IMPORT
#undef EXTERN


#endif
