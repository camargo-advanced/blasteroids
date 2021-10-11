//
//  blast.c
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/3/18.
//
#include "blast.h"

static Blast * create_blast(Blast_Config * config, unsigned short int x, unsigned short int y, float angle)
{
    Blast *p = (Blast *) malloc(sizeof(Blast));
    
    p->config = config;
    p->x = x;
    p->y = y;
    p->v_dx = sinf(angle) * config->v_magnitude;
    p->v_dy = -cosf(angle) * config->v_magnitude;
    p->angle = angle;
    p->dead = false;
    p->next = NULL;
    
    return p;
}

void add_blast(Blasts * blasts, unsigned short int x, unsigned short int y, float angle)
{
    Blast * new = create_blast(&blasts->config, x, y, angle);
    
    if (!blasts->head) {
        blasts->head = new;
    }
    else {
        Blast * p = blasts->head;
        for (; p->next; p = p->next);
        p->next = new;
    }
}

Blasts * create_blasts(int screen_w, int screen_h, float elapsed_time)
{
    Blasts * p = (Blasts *) malloc(sizeof(Blasts));
    
    /* setup blasts configuration data */
    Wireframe * w = create_wireframe();
    add_point(w, 0.5f, 0.0f);  add_point(w, -0.5f, -1.0f);
    add_point(w, 0.5f, -2.0f); add_point(w, -0.5f, -3.0f);
    p->config.wireframe = w;
    
    p->config.screen_w = screen_w;
    p->config.screen_h = screen_h;
    p->config.v_magnitude = 500.0f;
    p->config.elapsed_time = elapsed_time;
    
    float r = 1.0f, g = 1.0f, b = 1.0f, a = 0.7f;
    p->config.color = al_map_rgba_f(r*a, g*a, b*a, a);
    p->config.size = 1.0f;
    
    p->head = NULL;
    
    /* return blasts object */
    return p;
}

static void destroy_blast(Blast* p)
{
    free(p);
}

void destroy_blasts(Blasts * blasts)
{
    Blast * p = blasts->head;
    for (Blast * pf;p;)
    {
        pf = p;
        p = p->next;
        destroy_blast(pf);
    }
    destroy_wireframe(blasts->config.wireframe);
    free(blasts);
}

static bool in_screen_space(Blast * p) {
    if (p->x < 1.0f) return false;
    if (p->x >= p->config->screen_w - 1) return false;
    if (p->y < 1.0f) return false;
    if (p->y >= p->config->screen_w - 1) return false;
    return true;
}

static void clean_up_blasts(Blasts * blasts)
{
    Blast * p = blasts->head, * prev = NULL;
    while (p)
    {
        if (p->dead)
        {
            if (prev == NULL) {
                blasts->head = p->next;
                destroy_blast(p);
                p = blasts->head;
            } else {
                prev->next = p->next;
                destroy_blast(p);
                p = prev->next;
            }
        } else {
            prev = p;
            p = p->next;
        }
    }
}
                         
void update_blasts(Blasts * blasts)
{
    Blast * p = blasts->head;
    for (;p;p=p->next)
    {
        if (!p->dead)
        {
            p->x += p->v_dx * p->config->elapsed_time;
            p->y += p->v_dy * p->config->elapsed_time;
            if (!in_screen_space(p)) p->dead = true;
        }
    }
    clean_up_blasts(blasts);
}

void draw_blasts(Blasts * blasts)
{
    for (Blast * p=blasts->head;p;p=p->next)
    {
        draw_wireframe_model(p->config->wireframe, p->config->size, \
                             p->x, p->y, p->angle, &p->config->color);
    }
}
