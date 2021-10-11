//
//  point.h
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/17/18.
//
#ifndef point_h
#define point_h

#include <stdio.h>
#include <stdlib.h>

typedef struct Point2 Point2;
struct Point2
{
    float x, y;
    Point2 * next;
}; 

Point2 * create_point2(float x, float y);
void destroy_point(Point2 * p);

#endif /* point_h */
