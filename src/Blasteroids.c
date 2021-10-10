//
//  Blasteroids.c
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/15/18.
//  Copyright © 2018 Marcelo Camargo. All rights reserved.
//
#include "blasteroids.h"

Blasteroids * create_blasteroids()
{
    Blasteroids * p = (Blasteroids *) malloc(sizeof(Blasteroids));
    p->ship = create_ship(SCREEN_W, SCREEN_H, ELAPSED_TIME);
    p->blasts = create_blasts(SCREEN_W, SCREEN_H, ELAPSED_TIME);
    p->asteroids = create_asteroids(9, SCREEN_W, SCREEN_H, ELAPSED_TIME);
    p->score = create_score(SCREEN_W, SCREEN_H);
    if (!p->ship || !p->asteroids || !p->score) {
        fprintf(stderr, "Could not load inicialize game.\n");
        return NULL;
    }
    return p;
}

void destroy_blasteroids(Blasteroids * p)
{
    if (p->ship) destroy_ship(p->ship);
    if(p->asteroids) destroy_asteroids(p->asteroids);
    if (p->blasts) destroy_blasts(p->blasts);
    if (p->score) destroy_score(p->score);
    free(p);
}
