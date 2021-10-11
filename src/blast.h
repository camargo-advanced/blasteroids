//
//  blast.h
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/3/18.
//
#ifndef blast_h
#define blast_h

#include <math.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "utils.h"
#include "wireframe.h"

typedef struct Blast_Config Blast_Config;
struct Blast_Config
{
    Wireframe * wireframe;
    int screen_w;
    int screen_h;
    float v_magnitude;  // magnitude of velocity vector
    float elapsed_time;
    ALLEGRO_COLOR color;
    float size;
};

typedef struct Blast Blast;
struct Blast
{
    Blast_Config * config;
    float x;                // x coordinate
    float y;                // y coordinate
    float v_dx;             // velocity vector - component x
    float v_dy;             // velocity vector - component y
    float angle;
    bool dead;
    Blast *next;
};

typedef struct Blasts Blasts;
struct Blasts
{
    Blast_Config config;
    Blast * head;
};

Blasts * create_blasts(int screen_w, int screen_h, float elapsed_time);
void add_blast(Blasts * blasts, unsigned short int x, unsigned short int y, float angle);
void destroy_blasts(Blasts * blasts);
void update_blasts(Blasts * blasts);
void draw_blasts(Blasts * blasts);

#endif /* blast_h */
