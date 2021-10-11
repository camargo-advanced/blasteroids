//
//  blasteroids.h
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/15/18.
//
#ifndef blasteroids_h
#define blasteroids_h

#include <time.h>
#include "spaceship.h"
#include "asteroids.h"
#include "blast.h"
#include "score.h"

#define FPS 60
#define SCREEN_W 1800
#define SCREEN_H 950
#define ELAPSED_TIME 1.0f / FPS

typedef struct Blasteroids Blasteroids;
struct Blasteroids
{
    Spaceship *ship;        /* spaceship object */
    Asteroids *asteroids;    /* linked list of asteroids */
    Blasts * blasts;         /* linked list of blasts */
    Score *score;           /* score object */
};

Blasteroids * create_blasteroids(void);
void destroy_blasteroids(Blasteroids * p);

#endif
