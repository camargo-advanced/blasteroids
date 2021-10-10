//
//  spaceship.c
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/7/18.
//  Copyright © 2018 Marcelo Camargo. All rights reserved.
//
#include "spaceship.h"

Spaceship * create_ship(int screen_w, int screen_h, float elapsed_time)
{
	Spaceship *s = (Spaceship *) malloc(sizeof(Spaceship));

	s->x = screen_w / 2.0f;
	s->y = screen_h / 2.0f;
    
    /* setup asteroid wireframe data */
    Wireframe * w = create_wireframe();
    add_point(w, 0.0f, -5.0f);  add_point(w, 3.0f, 4.0f);
    add_point(w, 1.5f, 2.0f);   add_point(w, -1.5f, 2.0f);
    add_point(w, -3.0f, 4.0f);
    s->wireframe = w;

    Wireframe * w_pp = create_wireframe();
    add_point(w_pp, 1.0f, 2.0f);
    add_point(w_pp, 0.0f, 5.0f);
    add_point(w_pp, -1.0f, 2.0f);
    s->wireframe_pp = w_pp;

    s->size = 5.0;
	s->v_dx = 0.0f;
	s->v_dy = 0.0f;
    s->da_const = 150.0f;
    s->speeding_up = false;
	s->angle = 0.0f;
	float r = 0.0f, g = 1.0f, b = 0.0f, a = 0.7f;
	s->color = al_map_rgba_f(r*a , g*a , b*a , a);
    s->screen_w = screen_w;
    s->screen_h = screen_h;
    s->elapsed_time = elapsed_time;
    s->shielded = false;

	return s;
}

void shield_ship(Spaceship* s)
{
    s->shielded = true;
}

void unshield_ship(Spaceship* s)
{
    s->shielded = false;
}

void reset_ship(Spaceship* s)
{
    s->x = s->screen_w / 2.0f;
    s->y = s->screen_h / 2.0f;
    s->v_dx = 0.0f;
    s->v_dy = 0.0f;
    s->angle = 0.0f;
    s->speeding_up = false;
}

void destroy_ship(Spaceship* s)
{
    destroy_wireframe(s->wireframe);
    destroy_wireframe(s->wireframe_pp);
	free(s);
}

void update_ship(Spaceship * s)
{
	s->x += s->v_dx * s->elapsed_time;
	s->y += s->v_dy * s->elapsed_time;
	wrap_coordinates(&s->x, &s->y, s->screen_w, s->screen_h);
    
    /* deacelerate ship */
    if (!s->speeding_up) {
        decelerate_ship(s);
    }
}

void draw_ship(Spaceship* s) 
{
	draw_wireframe_model(s->wireframe, s->size, s->x, s->y, s->angle, &s->color);
    if (s->speeding_up)
    {
        draw_wireframe_model(s->wireframe_pp, s->size, s->x, s->y, s->angle, &s->color);
        s->speeding_up = false;
    }
}

void turn_left_ship(Spaceship *s) 
{
	s->angle -= 3.0f * s->elapsed_time;
}

void turn_right_ship(Spaceship *s) 
{
	s->angle += 3.0f * s->elapsed_time;
}

void accelerate_ship(Spaceship *s) 
{
	s->v_dx += sinf(s->angle) * s->da_const * s->elapsed_time;
	s->v_dy += -cosf(s->angle) * s->da_const * s->elapsed_time;
    s->speeding_up = true;
}

void decelerate_ship(Spaceship *s) 
{
    /* calculate magnitude */
    float magnitude = sqrtf(s->v_dx*s->v_dx + s->v_dy*s->v_dy);
    
    if (magnitude > 0) {
        /* sin(angle) = dx / magnitude  */
        float sin_angle = s->v_dx / magnitude;
        
        /* angle = sin^-1 (angle) */
        float angle = asin(sin_angle);
        
        /* adjust angle acording to quadrant */
        if (s->v_dy>0) angle = PI - angle;

        /* now reduce magnitude by a rate */
        magnitude -= s->da_const * s->elapsed_time;
        
        /* now recalculate velocity vector components */
        s->v_dx = sinf(angle) * magnitude;
        s->v_dy = -cosf(angle) * magnitude;
    }
}

int get_ship_orientation(Spaceship * s, float * x, float * y, float * angle)
{
    *x = s->x;
    *y = s->y;
    *angle = s->angle;
    return 0;
}
