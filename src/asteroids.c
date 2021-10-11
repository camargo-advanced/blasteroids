//
//  asteroids.c
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/16/18.
//
#include "asteroids.h"

static float calculate_random_angle()
{
    return (float)(random() % 360) * (2.0f * PI) / 360.0f;
}

static Asteroid * create_asteroid(Asteroid_Config * config)
{
    Asteroid * p = (Asteroid *) malloc(sizeof(Asteroid));
    
    /* initialize asteroid  */
    p->config = config;
    p->x = random() % config->screen_w;
    p->y = random() % config->screen_h;
    p->angle = calculate_random_angle();
    p->v_dx = sinf(p->angle) * config->v_magnitude;
    p->v_dy = -cosf(p->angle) * config->v_magnitude;
    p->self_rotation_angle = calculate_random_angle();
    p->radius = calc_circle_diameter_of(config->wireframe) * config->size / 2; 
    p->size = config->size;
    p->times_hit = 0;
    p->dead = false;
    
    /* there is nothing to point to */
    p->next = NULL;
    
    /* return asteroid object */
    return p;
}

Asteroids * create_asteroids(int n, int screen_w, int screen_h, float elapsed_time)
{
    Asteroids * p = (Asteroids *) malloc(sizeof(Asteroids));

    /* setup asteroid configuration data */
    Wireframe * w = create_wireframe();
    add_point(w, -20.0f, 20.0f);  add_point(w, -25.0f, 5.0f);   add_point(w, -25.0f, -10.0f);
    add_point(w, -5.0f, -10.0f);  add_point(w, -10.0f, -20.0f); add_point(w, 5.0f, -20.0f);
    add_point(w, 20.0f, -10.0f);  add_point(w, 20.0f, -5.0f);   add_point(w, 0.0f, 0.0f);
    add_point(w, 20.0f, 10.0f);   add_point(w, 10.0f, 20.0f);   add_point(w, 0.0f, 15.0f);
    p->config.wireframe = w;
    
    p->config.screen_w = screen_w;
    p->config.screen_h = screen_h;
    p->config.v_magnitude = 90.0f;
    p->config.v_dw = 0.3f;

    p->config.elapsed_time = elapsed_time;

    float r = 1.0f, g = 1.0f, b = 1.0f, a = 0.7f;
    p->config.color = al_map_rgba_f(r*a, g*a, b*a, a);
    
    /* object scale */
    p->config.size = 3;
    
    /* create asteroids linked list */
    p->head = NULL;
    Asteroid * current_asteroid = NULL;
    for (int i=0; i<n; i++)
    {
        Asteroid * new_asteroid = create_asteroid(&p->config);
        if (!p->head) {
            p->head = new_asteroid;
            current_asteroid = p->head;
        }
        else {
            current_asteroid->next = new_asteroid;
            current_asteroid = current_asteroid->next;
        }
    }
    
    /* return asteroids object */
    return p;
}

void append_asteroids_list(Asteroids * asteroids, Asteroid * p1)
{
    Asteroid * p = asteroids->head;
    
    /* move to the tail of the list */
    for (; p->next; p = p->next);
    
    /* append the linked list at the tail */
    p->next = p1;
}

bool asteroid_hit(Asteroid * p)
{
    /* if asteriod has not been hit 3 times yes, reduce its size */
    if (++p->times_hit < 3)
    {
        p->size /= 2;
        p->radius /= 2;
        return true; /* returns true if asteroid still lives */
    }
    else /* otherwise kill it */
        p->dead = true;
    
    return false; /* returns false meaning asteroid is dead */
}

void asteroid_randomize_orientation(Asteroid * p)
{
    /* ramdomize angle  - generate unit vector */
    p->angle = calculate_random_angle();
    
    /* calculate current velocity vector magnitude = square root of Vxˆ2 + Vy^2 + */
    float magnitude = sqrtf(p->v_dx*p->v_dx + p->v_dy*p->v_dy);
    
    /* update velocity vectors to reflect new angle at at original speed */
    p->v_dx = sinf(p->angle) * magnitude;
    p->v_dy = -cosf(p->angle) * magnitude;
}

Asteroid * clone_asteroid(Asteroid * p)
{
    Asteroid * new_p = (Asteroid *) malloc(sizeof(Asteroid));
    *new_p = *p;
    new_p->next = NULL;
    return new_p;
}

static void destroy_asteroid(Asteroid* p)
{
    free(p);
}

static void clean_up_asteroids(Asteroids * asteroids)
{
    Asteroid * p = asteroids->head, * prev = NULL;
    while (p)
    {
        if (p->dead)
        {
            if (prev == NULL) {
                asteroids->head = p->next;
                destroy_asteroid(p);
                p = asteroids->head;
            } else {
                prev->next = p->next;
                destroy_asteroid(p);
                p = prev->next;
            }
        } else {
            prev = p;
            p = p->next;
        }
    }
}

void update_asteroids(Asteroids * asteroids)
{
    for (Asteroid * p=asteroids->head; p; p=p->next)
    {
        p->self_rotation_angle += p->config->v_dw * p->config->elapsed_time;
        p->x += p->v_dx * p->config->elapsed_time;
        p->y += p->v_dy * p->config->elapsed_time;
        wrap_coordinates(&p->x, &p->y, p->config->screen_w, p->config->screen_h);
    }
    clean_up_asteroids(asteroids);
}

void speed_up_asteriod(Asteroid * p, float rate)
{
    /* multiplying the dx and dy components also multiplies the magnitude by the same rate */
    p->v_dx *= rate;
    p->v_dy *= rate;
}

void draw_asteroids(Asteroids * asteroids)
{
    for (Asteroid * p=asteroids->head; p; p=p->next)
    {
        draw_wireframe_model(p->config->wireframe, \
                             p->size, p->x, p->y, p->self_rotation_angle, &p->config->color);
    }
}

void destroy_asteroids(Asteroids * asteroids)
{
    Asteroid * p = asteroids->head;
    for (Asteroid * pf;p;)
    {
        pf = p;
        p = p->next;
        destroy_asteroid(pf);
    }
    destroy_wireframe(asteroids->config.wireframe);
    free(asteroids);
}
