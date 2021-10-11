//
//  utils.c
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/7/18.
//
#include "utils.h"

void wrap_coordinates(float *x, float *y, int screen_w, int screen_h)
{
    if (*x < 0.0f) *x += screen_w;
    if (*x >= screen_w) *x -= screen_w;
    if (*y < 0.0f) *y += screen_h;
    if (*y >= screen_h) *y -= screen_h;
}

bool is_point_in_circle(float p_x, float p_y, float c_x, float c_y, float radius)
{
    /* calculate the discance between 2 points in 2D space */
    float d = sqrtf(powf(p_x - c_x, 2) + powf(p_y - c_y, 2));
    
    /* if discance is less than the radius, we assume the objects have colided */
    if (d <= radius)
        return true;
    return false;
}
