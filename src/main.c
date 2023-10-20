#include "tld.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

#include "world.h"

#include "param.h"
#include "particle_struct.h"
#include "particle_op.h"
#include "grid.h"

int p_list_update(p_list *l);
int p_list_update_speed(p_list *l);
/* int p_list_add_random_particles_at_mouse(p_list* l , int n); */
/* int p_list_add_random_particles(p_list* l , int n); */
/* int p_list_alloc(p_list **list, int size); */
/* void p_list_free(p_list *l); */

int update_particle(particle *particles, int n, int id);

/* static inline Vector2  wrap_dist(Vector2 p1, Vector2 p2, float  w, float  h); */

int main(int argc, char *argv[])
{
        parameters* param = NULL;
        struct world* w = NULL;
        int density = 0;
        RUN(param_parse(argc, argv, &param));
        if(param->help){
                param_free(param);
                return EXIT_SUCCESS;
        }

        RUN(world_alloc(param, &w));

        InitWindow(w->screenWidth, w->screenHeight, "Alife: particle motion law");
        SetTargetFPS(60);

        density =(int) (( (float) w->screenWidth / 5.0) * ((float) w->screenHeight / 5.0) * w->param->density);

        RUN(p_list_add_random_particles(w->l,w->param->velocity,  density));
        int n_step = 0;
        int step_per_frame = 10;
        int paused = 0;
        // Main game loop
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                        p_list_add_random_particles_at_mouse(w->l,w->param->velocity, 10);
                }

                if(IsKeyPressed(KEY_SPACE)){
                        paused = !paused;
                }
                if(IsKeyPressed(KEY_LEFT)){
                        step_per_frame -= 2;
                        step_per_frame = MACRO_MAX(1, step_per_frame);
                }
                if(IsKeyPressed(KEY_RIGHT)){
                        step_per_frame += 2;
                        step_per_frame = MACRO_MIN(20, step_per_frame);
                }
                if(!paused){
                        for(int i = 0; i < step_per_frame;i++){
                                grid_clear(w->g);
                                for(int i = 0; i < w->l->n;i++){
                                        grid_add_particle(w->g, &w->l->particles[i] );
                                }

                                for(int i = 0; i < w->l->n;i++){
                                        update_n(w->g, &w->l->particles[i] ,w->l,w->param->alpha,w->param->beta);
                                }
                                p_list_update_speed(w->l);
                        }
                        n_step += step_per_frame;
                }

                BeginDrawing();

                ClearBackground(BLACK);

                for (int i = 0; i < w->l->n; i++){
                        DrawCircleV( w->l->particles[i].position, (float)1.0, w->l->particles[i].color);
                }

                DrawText(TextFormat("Particles : %i", w->l->n), 120, 10, 20, GREEN);
                DrawText(TextFormat("Step : %i", n_step), 320, 10, 20, GREEN);
                /* DrawText(TextFormat("Keys: '>'/'<' increase/decrease speed 'space' pause.", n_step), 420, 10, 20, GREEN); */
                DrawFPS(10, 10);

                EndDrawing();
        }

        world_free(w);
        param_free(param);
        return EXIT_SUCCESS;
ERROR:
        if(w){
                world_free(w);
        }
        if(param){
                param_free(param);
        }
        return EXIT_FAILURE;
}

int p_list_update_speed(p_list *l)
{
        ASSERT(l != NULL,"No list!");

        for(int p_id = 0; p_id < l->n;p_id++){
                l->particles[p_id].n_pos.x = l->particles[p_id].position.x + l->particles[p_id].speed.x;
                l->particles[p_id].n_pos.y = l->particles[p_id].position.y + l->particles[p_id].speed.y;

                /* l->particles[p_id].position.x += l->particles[p_id].speed.x; */
                /* l->particles[p_id].position.y += l->particles[p_id].speed.y; */

                if(l->particles[p_id].n_pos.x > GetScreenWidth()){
                        l->particles[p_id].n_pos.x = l->particles[p_id].n_pos.x - (float)GetScreenWidth();
                }else if(l->particles[p_id].n_pos.x < 0.0){
                        l->particles[p_id].n_pos.x =  (float)GetScreenWidth() - fabsf(l->particles[p_id].n_pos.x);
                }

                if(l->particles[p_id].n_pos.y > GetScreenHeight()){
                        l->particles[p_id].n_pos.y = 40.0 + l->particles[p_id].n_pos.y - ((float)GetScreenHeight());

                }else if(l->particles[p_id].n_pos.y < 40.0){
                        l->particles[p_id].n_pos.y -= 40.0;
                        l->particles[p_id].n_pos.y =  (float)GetScreenHeight() - fabsf(l->particles[p_id].n_pos.y);
                }
        }
        for(int p_id = 0; p_id < l->n;p_id++){
                l->particles[p_id].position.x = l->particles[p_id].n_pos.x ;
                l->particles[p_id].position.y = l->particles[p_id].n_pos.y ;
        }

        return OK;
ERROR:
        return FAIL;
}


/* static inline Vector2 wrap_dist(Vector2 p1, Vector2 p2, float  w, float  h) */
/* { */
/*         Vector2 d; */

/*         float  dx = p2.x - p1.x; */
/*         float dy = p2.y - p1.y; */

/*         // Adjust for wrapping on x-axis */
/*         if (fabs(dx) > w / 2.0) { */
/*                 dx = (dx > 0) ? dx - w : dx + w; */
/*         } */

/*         // Adjust for wrapping on y-axis */
/*         if (fabs(dy) > h / 2.0) { */
/*                 dy = (dy > 0) ? dy - h : dy + h; */
/*         } */


/*         d.x = dx; */
/*         d.y = dy; */

/*         return d;//sqrtf(dx * dx + dy * dy); */
/* } */
