//
//  wireframe.h
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/17/18.
//  Copyright © 2018 Marcelo Camargo. All rights reserved.
//
#ifndef wireframe_h
#define wireframe_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include "point.h"

typedef struct Wireframe Wireframe;
struct Wireframe
{
    Point2 * head;
};

Wireframe * create_wireframe(void);
void add_point(Wireframe * w, float x, float y);
void draw_wireframe_model(Wireframe * wireframe, float size, \
                          float x, float y, float angle, ALLEGRO_COLOR *color);
float calc_circle_diameter_of(Wireframe * wireframe);
void destroy_wireframe(Wireframe * w);

#endif /* wireframe_h */
