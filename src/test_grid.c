#include "tld.h"
#include "particle_struct.h"
#include "grid.h"

int main(int argc, char *argv[])
{
        struct rng_state* rng = NULL;
        grid* g = NULL;
        particle p;
        int h = 750;
        int w = 1000;
        RUN(init_rng(&rng, 0));


        grid_alloc(&g, h, w, 150.000);

        for(int i = 0; i < 1000000;i++){
                p.position.x = (float) (tl_random_double(rng)*(double) w);
                p.position.y = (float) (tl_random_double(rng)*(double) h);
                p.id = i;
                /* LOG_MSG("%f %f", p.position.x,p.position.y); */
                grid_add_particle(g, &p);
        }

        grid_print(g);

        p.position.x = (float) (tl_random_double(rng)*(double) w);
        p.position.y = (float) (tl_random_double(rng)*(double) h);
        p.id = 99;

        /* update_n(g, &p); */
        

        /* int x = (int) p->position.x / g->cell_size; */
        /* int y = (int) p->position.y / g->cell_size; */

        grid_free(g);

        free_rng(rng);

        return EXIT_SUCCESS;
ERROR:
        if(rng){
                free_rng(rng);
        }
        return EXIT_FAILURE;
}
