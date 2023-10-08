#include "tld.h"

#include "particle_struct.h"
#include <raylib.h>
#include <raymath.h>
#define GRID_IMPORT
#include "grid.h"

static inline Vector2  wrap_dist(Vector2 p1, Vector2 p2, float  w, float  h);
 int grid_cell_alloc(grid_cell **grid);
 int grid_cell_resize(grid_cell *n);
void grid_cell_free(grid_cell *n);


int update_n(grid *g, particle *p,p_list *l)
{
        float  givenRadius = 25.0;
        float closeR  = 5.0 * 1.3;

        int x = (int) p->position.x / g->cell_size;
        int y = (int) p->position.y / g->cell_size;

        Vector2 normalRight = {p->speed.y, -p->speed.x};

        TLD_START_TIMER
        int leftCount = 0;
        int rightCount = 0;
        int c_count = 0;
        for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                        int idx_x = x + i;
                        if(idx_x >= g->n_col){
                                idx_x = 0;
                        }else if(idx_x < 0){
                                idx_x = g->n_col - 1;
                        }
                        int idx_y = y + j;
                        if(idx_y >= g->n_row){
                                idx_y = 0;
                        }else if(idx_y < 0){
                                idx_y = g->n_row - 1;
                        }


                        uint32_t* ids = g->cells[idx_x][idx_y]->id;
                        int n = g->cells[idx_x][idx_y]->n;
                        /* LOG_MSG("%d %d -> %d %d n=%d", x,y, idx_x,idx_y, n); */
                        for(int c = 0; c < n;c++){
                                /* LOG_MSG("%d %d", ids[c], p->id); */
                                if(ids[c] != p->id){
                                        particle o = l->particles[ids[c]];
                                        Vector2 vectorToB = wrap_dist(o.position, p->position, g->w,g->h);//
                                        if (Vector2Length(vectorToB) <= closeR){
                                                c_count++;
                                        }
                                        if (Vector2Length(vectorToB) <= givenRadius) {

                                                // Check the side of B relative to A
                                                float dotProduct = normalRight.x * vectorToB.x + normalRight.y * vectorToB.y;

                                                if (dotProduct > 0) {
                                                        rightCount++;
                                                } else if (dotProduct < 0) {
                                                        leftCount++;
                                                }
                                        }
                                }
                        }

                        /* t += g->cells[idx_x][idx_y]->n; */


                        /* if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE) { */
                        /*         Cell* cell = &grid[newX][newY]; */
                        /*         for (int k = 0; k < cell->count; k++) { */
                        /*                 Point q = cell->points[k]; */
                        /*                 double dist = sqrt((q.x - p.x) * (q.x - p.x) + (q.y - p.y) * (q.y - p.y)); */
                        /*                 if (dist <= distance) { */
                        /*                         // Do something with point q (e.g., store it, process it, etc.) */
                        /*                 } */
                        /*         } */
                        /* } */
                }
        }
        /* LOG_MSG("Fast: L:%5d R:%5d", leftCount, rightCount); */
        /* TLD_END_TIMER */
        /*         TLD_START_TIMER */
        /* leftCount = 0 ; */
        /* rightCount = 0; */
        /* for(int i = 0; i < l->n;i++){ */
        /*         if(i != p->id){ */
        /*                 particle o = l->particles[i]; */

        /*                 /\* fload d = wrap_dist(o.position, p.position, w,h); *\/ */

        /*                 Vector2 vectorToB = wrap_dist(o.position, p->position, g->w,g->h);// */
        /*                 //{p.position.x - o.position.x ,p.position.y - o.position.y}; */

        /*                 // Check if B is within the radius of A */
        /*                 if (Vector2Length(vectorToB) <= closeR){ */
        /*                         c_count++; */
        /*                 } */
        /*                 if (Vector2Length(vectorToB) <= givenRadius) { */

        /*                         // Check the side of B relative to A */
        /*                         float dotProduct = normalRight.x * vectorToB.x + normalRight.y * vectorToB.y; */

        /*                         if (dotProduct > 0) { */
        /*                                 rightCount++; */
        /*                         } else if (dotProduct < 0) { */
        /*                                 leftCount++; */
        /*                         } */
        /*                 } */
        /*         } */
        /* } */
        /* LOG_MSG("Slow: L:%5d R:%5d", leftCount, rightCount); */
        /* TLD_END_TIMER */
        int neighbors = leftCount + rightCount;

        float alpha = 180.0;
        float beta = 17.0;
        float sign = 0.0;
        if(rightCount < leftCount){
                sign = -1.0;
        }else if(rightCount == leftCount){
                sign = 0.0;
        }else{
                sign = 1.0;
        }
        float delta = alpha + beta * (float) neighbors * sign;

        float angleInRadians =delta * PI / 180.0f;
        float rotatedX = p->speed.x * cosf(angleInRadians) - p->speed.y * sinf(angleInRadians);
        float rotatedY = p->speed.x * sinf(angleInRadians) + p->speed.y * cosf(angleInRadians);


        if(c_count > 15){
                p->color = MAGENTA;

        }else if(neighbors >13  && neighbors <= 15){
                p->color = BROWN;
        }else if(neighbors > 15 && neighbors <= 35){
                p->color =  BLUE;
        }else if( neighbors > 35){
                p->color = YELLOW;// (Color){255, 255, 0, 255 };
        }else{
                p->color = GREEN;//GREE(Color){0, 255, 0, 255 };
        }

        p->speed.x = rotatedX;
        p->speed.y = rotatedY;

        /* LOG_MSG("Total: %d", t); */
        return OK;
ERROR:
        return FAIL;
}

static inline Vector2 wrap_dist(Vector2 p1, Vector2 p2, float  w, float  h)
{
        Vector2 d;

        float  dx = p2.x - p1.x;
        float dy = p2.y - p1.y;

        // Adjust for wrapping on x-axis
        if (fabs(dx) > w / 2.0) {
                dx = (dx > 0) ? dx - w : dx + w;
        }

        // Adjust for wrapping on y-axis
        if (fabs(dy) > h / 2.0) {
                dy = (dy > 0) ? dy - h : dy + h;
        }


        d.x = dx;
        d.y = dy;

        return d;//sqrtf(dx * dx + dy * dy);
}

int grid_add_particle(grid *g, particle *p)
{
        int x = (int) p->position.x / g->cell_size;
        int y = (int) p->position.y / g->cell_size;
        x = MACRO_MIN(x, g->n_col-1);
        y = MACRO_MIN(y, g->n_row-1);
        grid_cell* c = NULL;
        /* LOG_MSG("%d %d (%d %d)",x,y ,g->n_col,g->n_row); */
        c = g->cells[x][y];
        if(c->n == c->n_alloc){
                grid_cell_resize(c);
        }
        c->id[c->n] = p->id;
        c->n++;
        return OK;
}

int grid_print(grid *g)
{
        for(int i = 0; i < g->n_col;i++){
                for(int j = 0; j < g->n_row;j++){
                        fprintf(stdout,"%3d ",g->cells[i][j]->n);
                }
                fprintf(stdout,"\n");

        }
        fprintf(stdout,"\n");
        return OK;
ERROR:
        return FAIL;
}

int grid_clear(grid *g)
{
        for(int i = 0; i < g->n_col;i++){
                for(int j = 0; j < g->n_row;j++){
                        g->cells[i][j]->n = 0;
                }
        }
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
        float f2,f3;

        f2 = modff(h / cell_size, &f3);
        LOG_MSG("%f -> %f %f  %f",h / cell_size,f2 ,f3 , f3 + ceil(f2));
        n->n_row = f3 + ceil(f2);
        /* if(f2){ */
        /*          (int) ( h / cell_size) +1; */
        /* }else{ */

        /*         n->n_row = (int) ( h / cell_size); */
        /* } */
        f2 = modff(w / cell_size, &f3);
        LOG_MSG("%f -> %f %f %f",w / cell_size,f2 ,f3,f3 + ceil(f2) );
        n->n_col= f3 + ceil(f2);
        /* if(f2){ */
        /*         n->n_col = (int)( w / cell_size) + 1; */
        /* }else{ */
        /*         n->n_col = (int)( w / cell_size); */
        /* } */

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
