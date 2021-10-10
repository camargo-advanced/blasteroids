//
//  utils.h
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/7/18.
//  Copyright © 2018 Marcelo Camargo. All rights reserved.
//
#ifndef utils_h
#define utils_h

#include <math.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>


void wrap_coordinates(float *x, float *y, int screen_w, int screen_h);
bool is_point_in_circle(float p_x, float p_y, float c_x, float c_y, float radius);

#endif
