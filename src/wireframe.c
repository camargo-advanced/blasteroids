//
//  wireframe.c
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/17/18.
//  Copyright © 2018 Marcelo Camargo. All rights reserved.
//
#include "wireframe.h"

Wireframe * create_wireframe()
{
    Wireframe * p = (Wireframe *) malloc(sizeof(Wireframe));
    p->head = NULL;
    return p;
}

void add_point(Wireframe * w, float x, float y)
{
    Point2 * new_point = create_point2(x, y);
    
    if (!w->head) {
        w->head = new_point;
    }
    else {
        /* move to the tail of the list */
        Point2 * p = w->head;
        for (; p->next; p=p->next);
        p->next = new_point;
    }
}

void draw_wireframe_model(Wireframe * wireframe, float size, \
                          float x, float y, float angle, ALLEGRO_COLOR *color)
{
    Wireframe * draw = create_wireframe();
    
    /* rotate and scale */
    for (Point2 * p=wireframe->head; p; p=p->next)
    {
        add_point(draw, size*p->x * cosf(angle) - size*p->y * sinf(angle), \
                  size*p->x * sinf(angle) + size*p->y * cosf(angle));
    }
    
    /* translate */
    for (Point2 * p=draw->head; p; p=p->next)
    {
        p->x += x;
        p->y += y;
    }

    /* draw wireframe */
    Point2 * p=draw->head;
    for (; p->next; p=p->next)
    {
        al_draw_line(p->x, p->y, p->next->x, p->next->y, *color, 3.0f);
    }
    al_draw_line(p->x, p->y, draw->head->x, draw->head->y, *color, 3.0f);
    
    destroy_wireframe(draw);
}

float calc_circle_diameter_of(Wireframe * wireframe)
{
    if (!wireframe) return 0;
    
    float x_max = 0;
    float y_max = 0;
    float x_min = FLT_MAX;
    float y_min = FLT_MAX;
    for (Point2 * p=wireframe->head; p; p=p->next)
    {
        /* find the max of x and y */
        if (p->x > x_max) x_max = p->x;
        if (p->y > y_max) y_max = p->y;

        /* find the min of x and y */
        if (p->x < x_min) x_min = p->x;
        if (p->y < y_min) y_min = p->y;
    }
    
    return fabs(x_max-x_min)>fabs(y_max-y_min) ?
        fabs(x_max-x_min) : fabs(y_max-y_min);
}

void destroy_wireframe(Wireframe * wireframe)
{
    Point2 * p = wireframe->head;
    for (Point2 * pf;p;)
    {
        pf = p;
        p = p->next;
        destroy_point(pf);
    }
    free(wireframe);
}
