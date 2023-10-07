#include "tld.h"

#include "particle_struct.h"

#define GRID_IMPORT
#include "grid.h"

 int grid_cell_alloc(grid_cell **grid);
 int grid_cell_resize(grid_cell *n);
void grid_cell_free(grid_cell *n);


/* void findNearbyPoints(Point p, double distance) { */
/*     int cellX = (int)(p.x / CELL_SIZE); */
/*     int cellY = (int)(p.y / CELL_SIZE); */

/*     for (int i = -1; i <= 1; i++) { */
/*         for (int j = -1; j <= 1; j++) { */
/*             int newX = cellX + i; */
/*             int newY = cellY + j; */

/*             if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE) { */
/*                 Cell* cell = &grid[newX][newY]; */
/*                 for (int k = 0; k < cell->count; k++) { */
/*                     Point q = cell->points[k]; */
/*                     double dist = sqrt((q.x - p.x) * (q.x - p.x) + (q.y - p.y) * (q.y - p.y)); */
/*                     if (dist <= distance) { */
/*                         // Do something with point q (e.g., store it, process it, etc.) */
/*                     } */
/*                 } */
/*             } */
/*         } */
/*     } */
/* } */
int grid_add_particle(grid *g, particle *p)
{
        int x = (int) p->position.x / g->cell_size;
        int y = (int) p->position.y / g->cell_size;
        grid_cell* c = NULL;
        c = g->cells[x][y];
        if(c->n == c->n_alloc){
                grid_cell_resize(c);
        }
        c->id[c->n] = p->id;
        c->n++;
        return OK;
}

int grid_alloc(grid **g, float h, float w, float cell_size)
{
        grid* n = NULL;

        MMALLOC(n, sizeof(grid));

        n->cells = NULL;
        n->h = h;
        n->w = w;
        n->cell_size = cell_size;
        n->n_col = 0;
        n->n_row = 0;

        n->n_row = (int) roundf( h / cell_size) + 1;
        n->n_col = (int) roundf( w / cell_size) + 1;

        MMALLOC(n->cells, sizeof(grid_cell**) * n->n_col);
        for(int i = 0; i < n->n_col;i++){
                n->cells[i] = NULL;
                MMALLOC(n->cells[i], sizeof(grid_cell*) * n->n_row);
                for(int j = 0; j < n->n_row;j++){
                        n->cells[i][j] = NULL;
                        grid_cell_alloc(&n->cells[i][j]);
                }
        }
        *g = n;
        return OK;
ERROR:
        return FAIL;
}

void grid_free(grid *n)
{
        if(n){
                for(int i = 0; i < n->n_col;i++){
                        for(int j = 0; j < n->n_row;j++){
                                grid_cell_free(n->cells[i][j]);
                        }
                        MFREE(n->cells[i]);
                }
                MFREE(n->cells);
                MFREE(n);
        }
}

int grid_cell_alloc(grid_cell **grid)
{

        grid_cell* n = NULL;
        MMALLOC(n, sizeof(grid_cell));
        n->id = NULL;
        n->n = 0;
        n->n_alloc = 256;
        MMALLOC(n->id, sizeof(uint32_t) * n->n_alloc);
        for(int i = 0; i < n->n_alloc;i++){
                n->id[i] = 0;
        }
        *grid = n;
        return OK;
ERROR:
        grid_cell_free(n);
        return FAIL;
}

int grid_cell_resize(grid_cell *n)
{
        int old_size = n->n_alloc;
        n->n_alloc = n->n_alloc + n->n_alloc / 2;

        MREALLOC(n->id, sizeof(uint32_t) * n->n_alloc);
        for(int i = old_size; i < n->n_alloc;i++){
                n->id[i] = 0;
        }
        return OK;
ERROR:
        grid_cell_free(n);
        return FAIL;
}

void grid_cell_free(grid_cell *n)
{
        if(n){
                if(n->id){
                        MFREE(n->id);
                }
                MFREE(n);
        }
}
