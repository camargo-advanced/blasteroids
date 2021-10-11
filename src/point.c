//
//  point.c
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/17/18.
//
#include "point.h"

Point2 * create_point2(float x, float y)
{
    Point2 * p = (Point2 *) malloc(sizeof(Point2));
    
    p->x = x;
    p->y = y;
    p->next = NULL;
    
    return p;
}

void destroy_point(Point2 * p)
{
    free(p);
}
