#include "tld.h"

#include "particle_alloc.h"
#include "particle_op.h"

#include "grid.h"

#define  WORLD_IMPORT
#include "world.h"


int world_alloc(parameters *param, struct world **world)
{
        struct world* w = NULL;

        MMALLOC(w, sizeof(struct world));
        w->param = param;
        w->g = NULL;
        w->l = NULL;
        w->r = 5.0f;
        w->screenWidth = 1400;
        w->screenHeight = 790;



        RUN(p_list_alloc(&w->l, 10000));

        RUN(grid_alloc(&w->g, w->screenHeight, w->screenWidth, 25));

        /* LOG_MSG("%d n", w->l->n); */
        *world = w;
        return OK;
ERROR:
        return FAIL;
}

void world_free(struct world *w)
{
        if(w){
                MFREE(w);
        }
}
