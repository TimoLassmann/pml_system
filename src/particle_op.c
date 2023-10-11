#include "tld.h"

#include <raylib.h>
#include <raymath.h>

#define PARTICLE_OP_IMPORT
#include "particle_op.h"

int p_list_add_random_particles(p_list* l ,float velocity, int n)
{
        ASSERT(l != NULL,"No list of particles");
        if(l->n == l->n_alloc){
                LOG_MSG("Limit of points reached (%d)", l->n_alloc);
        }
        for(int i = 0; i < n;i++){
                /* particle point = l->particles[l->n]; */

                l->particles[l->n].direction.x = (float)GetRandomValue(-250, 250);
                l->particles[l->n].direction.y = (float)GetRandomValue(-250, 250);

                l->particles[l->n].direction = Vector2Normalize(l->particles[l->n].direction);
                /* int half_x = GetScreenWidth()/2; */
                /* int half_y = (GetScreenHeight()-40)/2 + 40; */
                /* l->particles[l->n].position.x = (float)GetRandomValue(-1,1) + half_x;//GetMousePosition(); */
                /* l->particles[l->n].position.y = (float)GetRandomValue(-1,1) + half_y;//GetMousePosition(); */
                l->particles[l->n].position.x = (float)GetRandomValue(0,GetScreenWidth());
                l->particles[l->n].position.y = (float)GetRandomValue(0,GetScreenHeight()-40) + 40.0;//GetMousePosition();
                /* LOG_MSG("%d : %f %f",i,l->particles[l->n].position.x,l->particles[l->n].position.y ); */
                l->particles[l->n].speed.x = (float)l->particles[l->n].direction.x * velocity * 5.0;
                l->particles[l->n].speed.y = (float)l->particles[l->n].direction.y * velocity * 5.0;
                l->particles[l->n].id = l->n;
                /* l->particles[l->n] = point; */
                /* LOG_MSG("Added %f %f", l->particles[l->n].position.x, l->particles[l->n].position.y); */
                l->n++;
                if(l->n == l->n_alloc){
                        break;
                }

        }
        return OK;
ERROR:
        return FAIL;
}

int p_list_add_random_particles_at_mouse(p_list* l ,float velocity, int n)
{
        ASSERT(l != NULL,"No list of particles");
        if(l->n == l->n_alloc){
                LOG_MSG("Limit of points reached (%d)", l->n_alloc);
        }
        for(int i = 0; i < n;i++){
                /* particle point = l->particles[l->n]; */
                l->particles[l->n].direction.x = (float)GetRandomValue(-250, 250);
                l->particles[l->n].direction.y = (float)GetRandomValue(-250, 250);
                /* if(i == 0){ */
                /*         LOG_MSG("%d %d", l->particles[l->n].direction.x ,l->particles[l->n].direction.y ); */
                /* } */
                l->particles[l->n].direction = Vector2Normalize(l->particles[l->n].direction);
                l->particles[l->n].position = GetMousePosition();
                /* l->particles[l->n].position.y = GetRandomValue(0,GetScreenHeight());//GetMousePosition(); */
                l->particles[l->n].speed.x = (float)l->particles[l->n].direction.x * 0.67*5.0;
                l->particles[l->n].speed.y = (float)l->particles[l->n].direction.y * 0.67*5.0;
                l->particles[l->n].id = l->n;

                /* l->particles[l->n] = point; */
                /* LOG_MSG("Added %f %f", l->particles[l->n].position.x, l->particles[l->n].position.y); */
                l->n++;
                if(l->n == l->n_alloc){
                        break;
                }

        }
        return OK;
ERROR:
        return FAIL;
}
