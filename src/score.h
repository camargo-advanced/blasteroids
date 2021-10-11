//
//  score.h
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/7/18.
//
#ifndef score_h
#define score_h

#include <math.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "utils.h"
#include "spaceship.h"

#define NUM_LIVES 3

typedef struct Score Score;
struct Score
{
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
    float screen_w;
    float screen_h;
    Spaceship *ship;   /* spaceship object */
    int lives;
    int score;
    bool game_over;
    bool ranking;
};

Score * create_score(float screen_w, float screen_h);
void update_score(Score * p, int variation);
void update_lives(Score * p, int variation);
void draw_score(Score * p, bool shielded);
void destroy_score(Score * p);
void reset_score(Score *p);
void reset_lives(Score * p);
void game_is_over(Score * p);
void update_ranking(Score * p, bool b);

#endif /* score_h */
