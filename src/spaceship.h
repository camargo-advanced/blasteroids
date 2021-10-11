//
//  spaceship.h
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/7/18.
//
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <math.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include "utils.h"
#include "wireframe.h"
#include "vector.h"

#define PI 3.141592f

typedef struct Spaceship Spaceship;
struct Spaceship
{
	float x;				// x coordinate
	float y;				// y coordinate
    Wireframe * wireframe;
    Wireframe * wireframe_pp;
    
    Vector2D velocity;
    Vector2D acceleration;
    
	float v_dx;				// velocity speed
	float v_dy;				// velocity speed
    float da_const;            /* aceleration */
    bool speeding_up;
	float size; 			// scale	
	float angle;
    float screen_w;
    float screen_h;
    float elapsed_time;
    bool shielded;          /* if spaceship is shielded  or not */
	ALLEGRO_COLOR color;
};

Spaceship * create_ship(int screen_w, int screen_h, float elapsed_time);
void reset_ship(Spaceship* s);
void destroy_ship(Spaceship* s);
void draw_ship(Spaceship* s);
void turn_left_ship(Spaceship *s);
void turn_right_ship(Spaceship *s);
void accelerate_ship(Spaceship *s);
void decelerate_ship(Spaceship *s);
void shield_ship(Spaceship* s);
void unshield_ship(Spaceship* s);
void update_ship(Spaceship * s);
int get_ship_orientation(Spaceship * s, float * x, float * y, float * angle);

#endif
