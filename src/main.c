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

static inline Vector2  wrap_dist(Vector2 p1, Vector2 p2, float  w, float  h);

int main(int argc, char *argv[])
{
        parameters* param = NULL;
        struct world* w = NULL;
        int density = 0;
        RUN(param_parse(argc, argv, &param));

        world_alloc(param, &w);

        InitWindow(w->screenWidth, w->screenHeight, "Alife: particle motion law");
        SetTargetFPS(60);

        density =(int) (( (float) w->screenWidth / 5.0) * ((float) w->screenHeight / 5.0) * w->param->density);
        RUN(p_list_add_random_particles(w->l,w->param->velocity,  density));
        /* LOG_MSG("Adding %d", density); */
        /* LOG_MSG("%d n", w->l->n); */

        /* exit(0); */
        int n_step = 0;
        int step_per_frame = 10;
        int paused = 0;
        // Main game loop
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
                // Update
                //----------------------------------------------------------------------------------
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                        p_list_add_random_particles_at_mouse(w->l,w->param->velocity, 10);
                        /* p_list_add_random_particles(l, 100); */
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

                // Update particles
                /* if(n_step % 10 == 0){ */
                if(!paused){
                        for(int i = 0; i < step_per_frame;i++){
                                grid_clear(w->g);
                                /* LOG_MSG("Adding: %d",l->n); */
                                for(int i = 0; i < w->l->n;i++){
                                        grid_add_particle(w->g, &w->l->particles[i] );
                                }

                                for(int i = 0; i < w->l->n;i++){
                                        update_n(w->g, &w->l->particles[i] ,w->l,w->param->alpha,w->param->beta);
                                }
                                /* p_list_update(l); */
                                p_list_update_speed(w->l);
                        }
                        n_step += step_per_frame;
                }
                //----------------------------------------------------------------------------------

                // Draw
                //----------------------------------------------------------------------------------
                BeginDrawing();

                ClearBackground(BLACK);

                for (int i = 0; i < w->l->n; i++){
                        DrawCircleV( w->l->particles[i].position, (float)1.0, w->l->particles[i].color);
                }
                /* Vector2 position; */
                /* position.x = 0; */
                /* position.y = 0; */
                /* DrawCircleV(position, (float)100.0, RED); */

                /* position.x = GetScreenWidth(); */
                /* position.y = GetScreenHeight(); */
                /* /\* LOG_MSG("Width : %f %f", ) *\/ */
                /* DrawCircleV(position, (float)100.0, RED); */

                /* DrawRectangle(0, 0, 400, 40, BLACK); */
                DrawText(TextFormat("Particles : %i", w->l->n), 120, 10, 20, GREEN);
                DrawText(TextFormat("Step : %i", n_step), 320, 10, 20, GREEN);
                DrawFPS(10, 10);

                EndDrawing();

                //----------------------------------------------------------------------------------
        }

        world_free(w);
        param_free(param);
        return EXIT_SUCCESS;
ERROR:
        return EXIT_FAILURE;
}
 /*        // Initialization */
/*         //-------------------------------------------------------------------------------------- */
/*         const int screenWidth = 1400; */
/*         const int screenHeight = 790; */
/*         int paused = 0; */
/*         /\* float ball_size = 2.0; *\/ */
/*         grid* g = NULL; */
/*         p_list* l = NULL; */

/*         InitWindow(screenWidth, screenHeight, "Alife: particle motion law"); */

/*         // Load bunny texture */
/*         /\* Texture2D texBunny = LoadTexture("../assets/test.png"); *\/ */
/*         p_list_alloc(&l, 10000); */


/*         SetTargetFPS(60);               // Set our game to run at 60 frames-per-second */

/*         int density =(int) (( (float) screenWidth / 5.0) * ((float) screenHeight / 5.0) * 0.06); */
/*         /\* LOG_MSG("%d p", density); *\/ */

/*         /\* exit(0); *\/ */
/*         p_list_add_random_particles(l, density); */

/*         grid_alloc(&g, screenHeight, screenWidth, 25); */


/*         /\* exit(0); *\/ */
/*         int n_step = 0; */
/*         int step_per_frame = 10; */
/*         // Main game loop */
/*         while (!WindowShouldClose())    // Detect window close button or ESC key */
/*         { */
/*                 // Update */
/*                 //---------------------------------------------------------------------------------- */
/*                 if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) */
/*                 { */
/*                         p_list_add_random_particles_at_mouse(l, 10); */
/*                         /\* p_list_add_random_particles(l, 100); *\/ */
/*                 } */

/*                 if(IsKeyPressed(KEY_SPACE)){ */
/*                         paused = !paused; */
/*                 } */
/*                 if(IsKeyPressed(KEY_LEFT)){ */
/*                         step_per_frame -= 2; */
/*                         step_per_frame = MACRO_MAX(1, step_per_frame); */
/*                 } */
/*                 if(IsKeyPressed(KEY_RIGHT)){ */
/*                         step_per_frame += 2; */
/*                         step_per_frame = MACRO_MIN(20, step_per_frame); */
/*                 } */

/*                 // Update particles */
/*                 /\* if(n_step % 10 == 0){ *\/ */
/*                 if(!paused){ */
/*                         for(int i = 0; i < step_per_frame;i++){ */
/*                                 grid_clear(g); */
/*                                 /\* LOG_MSG("Adding: %d",l->n); *\/ */
/*                                 for(int i = 0; i < l->n;i++){ */
/*                                         grid_add_particle(g, &l->particles[i] ); */
/*                                 } */

/*                                 for(int i = 0; i < l->n;i++){ */
/*                                         update_n(g, &l->particles[i] ,l); */
/*                                 } */
/*                                 /\* p_list_update(l); *\/ */
/*                                 p_list_update_speed(l); */
/*                         } */
/*                         n_step += step_per_frame; */
/*                 } */
/*                 //---------------------------------------------------------------------------------- */

/*                 // Draw */
/*                 //---------------------------------------------------------------------------------- */
/*                 BeginDrawing(); */

/*                 ClearBackground(BLACK); */

/*                 for (int i = 0; i < l->n; i++){ */
/*                         DrawCircleV( l->particles[i].position, (float)1.0, l->particles[i].color); */
/*                 } */
/*                 /\* Vector2 position; *\/ */
/*                 /\* position.x = 0; *\/ */
/*                 /\* position.y = 0; *\/ */
/*                 /\* DrawCircleV(position, (float)100.0, RED); *\/ */

/*                 /\* position.x = GetScreenWidth(); *\/ */
/*                 /\* position.y = GetScreenHeight(); *\/ */
/*                 /\* /\\* LOG_MSG("Width : %f %f", ) *\\/ *\/ */
/*                 /\* DrawCircleV(position, (float)100.0, RED); *\/ */

/*                 /\* DrawRectangle(0, 0, 400, 40, BLACK); *\/ */
/*                 DrawText(TextFormat("Particles : %i", l->n), 120, 10, 20, GREEN); */
/*                 DrawText(TextFormat("Step : %i", n_step), 320, 10, 20, GREEN); */
/*                 DrawFPS(10, 10); */

/*                 EndDrawing(); */

/*                 //---------------------------------------------------------------------------------- */
/*         } */

/*         /\* free(particles);              // Unload particles data array *\/ */
/*         p_list_free(l); */
/*         CloseWindow();              // Close window and OpenGL context */
/*         return 0; */
/* ERROR: */
/*         return FAIL; */
/* } */

/* int p_list_update(p_list *l) */
/* { */
/*         ASSERT(l != NULL,"No list!"); */
/*         float  givenRadius = 25.0; */
/*         float closeR  = 5.0 * 1.3; */

/*         float w = GetScreenWidth(); */
/*         float h = GetScreenHeight(); */
/*         /\* Nt,r=1.3 > 15 magenta *\/ */
/*         /\* LOG_MSG("Updating %d", l->n); *\/ */
/*         for(int p_id = 0; p_id < l->n;p_id++){ */
/*                 particle p = l->particles[p_id]; */

/*                 Vector2 normalRight = {p.speed.y, -p.speed.x}; */
/*                 int leftCount = 0; */
/*                 int rightCount = 0; */
/*                 int c_count = 0; */
/*                 for(int i = 0; i < l->n;i++){ */
/*                         if(i != p_id){ */
/*                                 particle o = l->particles[i]; */

/*                                 /\* fload d = wrap_dist(o.position, p.position, w,h); *\/ */

/*                                 Vector2 vectorToB = wrap_dist(o.position, p.position, w,h);// */
/*                                 //{p.position.x - o.position.x ,p.position.y - o.position.y}; */

/*                                 // Check if B is within the radius of A */
/*                                 if (Vector2Length(vectorToB) <= closeR){ */
/*                                         c_count++; */
/*                                 } */
/*                                 if (Vector2Length(vectorToB) <= givenRadius) { */

/*                                         // Check the side of B relative to A */
/*                                         float dotProduct = normalRight.x * vectorToB.x + normalRight.y * vectorToB.y; */

/*                                         if (dotProduct > 0) { */
/*                                                 rightCount++; */
/*                                         } else if (dotProduct < 0) { */
/*                                                 leftCount++; */
/*                                         } */
/*                                 } */
/*                         } */
/*                 } */
/*                 int neighbors = leftCount + rightCount; */

/*                 float alpha = 180.0; */
/*                 float beta = 17.0; */
/*                 float sign = 0.0; */
/*                 if(rightCount < leftCount){ */
/*                         sign = -1.0; */
/*                 }else if(rightCount == leftCount){ */
/*                         sign = 0.0; */
/*                 }else{ */
/*                         sign = 1.0; */
/*                 } */
/*                 float delta = alpha + beta * (float) neighbors * sign; */

/*                 float angleInRadians =delta * PI / 180.0f; */
/*                 float rotatedX = l->particles[p_id].speed.x * cosf(angleInRadians) - l->particles[p_id].speed.y * sinf(angleInRadians); */
/*                 float rotatedY = l->particles[p_id].speed.x * sinf(angleInRadians) + l->particles[p_id].speed.y * cosf(angleInRadians); */


/*                 if(c_count > 15){ */
/*                         l->particles[p_id].color = MAGENTA; */

/*                 }else if(neighbors >13  && neighbors <= 15){ */
/*                         l->particles[p_id].color = BROWN; */
/*                 }else if(neighbors > 15 && neighbors <= 35){ */
/*                         l->particles[p_id].color =  BLUE; */
/*                 }else if( neighbors > 35){ */
/*                         l->particles[p_id].color = YELLOW;// (Color){255, 255, 0, 255 }; */

/*                 }else{ */
/*                         l->particles[p_id].color = GREEN;//GREE(Color){0, 255, 0, 255 }; */
/*                 } */

/*                 l->particles[p_id].speed.x = rotatedX; */
/*                 l->particles[p_id].speed.y = rotatedY; */


/*                 /\*l->particles[p_id].n_pos.x = l->particles[p_id].position.x + l->particles[p_id].speed.x; */
/*                 l->particles[p_id].n_pos.y = l->particles[p_id]. position.y + l->particles[p_id].speed.y; */


/*                 if(l->particles[p_id].n_pos.x > GetScreenWidth()){ */
/*                         l->particles[p_id].n_pos.x = l->particles[p_id].n_pos.x - (float)GetScreenWidth(); */

/*                 }else if(l->particles[p_id].n_pos.x < 0.0){ */
/*                         l->particles[p_id].n_pos.x =  (float)GetScreenWidth() - fabsf(l->particles[p_id].n_pos.x); */
/*                 } */

/*                 if(l->particles[p_id].n_pos.y > GetScreenHeight()){ */
/*                         l->particles[p_id].n_pos.y = 40.0 + l->particles[p_id].n_pos.y - ((float)GetScreenHeight()); */

/*                 }else if(l->particles[p_id].n_pos.y < 40.0){ */
/*                         l->particles[p_id].n_pos.y -= 40.0; */

/*                         l->particles[p_id].n_pos.y =  (float)GetScreenHeight() - fabsf(l->particles[p_id].n_pos.y); */
/*                         }*\/ */



/*         } */
/*         /\* for(int p_id = 0; p_id < l->n;p_id++){ *\/ */
/*         /\*         l->particles[p_id].position.x = l->particles[p_id].n_pos.x ; *\/ */
/*         /\*         l->particles[p_id].position.y = l->particles[p_id].n_pos.y ; *\/ */

/*         /\* } *\/ */

/*         return OK; */
/* ERROR: */
/*         return FAIL; */
/* } */

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
