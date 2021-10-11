//
//  asteroids.h
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/16/18. 
//
#ifndef asteroids_h
#define asteroids_h

#include <stdio.h>
#include <allegro5/allegro_color.h>
#include "utils.h"
#include "wireframe.h"

#define PI 3.141592f

typedef struct Asteroid_Config Asteroid_Config;
struct Asteroid_Config
{
    Wireframe * wireframe;
    int screen_w;
    int screen_h;
    float v_magnitude;      /* initial velocity vector magnitude */
    float v_dw;             /* angular velocity */
    float elapsed_time;
    ALLEGRO_COLOR color;
    float size;
};

typedef struct Asteroid Asteroid;
struct Asteroid
{
    Asteroid_Config * config;
    float x;                /* x coordinate */
    float y;                /* y coordinate */
    float v_dx;             /* velocity vector dx component */
    float v_dy;             /* velocity vector dy component */
    float angle;            /* asteroid direction */
    float self_rotation_angle;   /* rock self rotation angle */
    float radius;
    float size;             /* for scaling */
    unsigned int times_hit;
    bool dead;              /* if it is dead, it will be get removed from the linked list */
    Asteroid * next;
};

typedef struct Asteroids Asteroids;
struct Asteroids
{
    Asteroid_Config config;
    Asteroid * head;
};

Asteroids * create_asteroids(int n, int screen_w, int screen_h, float elapsed_time);
void append_asteroids_list(Asteroids * asteroids, Asteroid * p1);
bool asteroid_hit(Asteroid * p);
void asteroid_randomize_orientation(Asteroid * p);
Asteroid * clone_asteroid(Asteroid * p);
void update_asteroids(Asteroids * asteroids);
void speed_up_asteriod(Asteroid * p, float rate);
void draw_asteroids(Asteroids * asteroids);
void destroy_asteroids(Asteroids * asteroids);

#endif /* asteroids_h */
