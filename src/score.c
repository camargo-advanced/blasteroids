//
//  score.c
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/7/18.
//
#include "score.h"
#include "spaceship.h"

Score * create_score(float screen_w, float screen_h)
{
    Score * p = (Score *) malloc(sizeof(Score));
    
    p->font = al_load_ttf_font("../res/hyperspace-bold.otf", 90, 0);
    if (!p->font){
        fprintf(stderr, "Could not load font.\n");
        return NULL;
    }
    float r = 0.0f, g = 1.0f, b = 0.0f, a = 0.7f;
    p->color = al_map_rgba_f(r*a , g*a , b*a , a);

    p->ship = create_ship(0, 0, 0);
    
    reset_score(p);
    reset_lives(p);
    
    p->screen_w = screen_w;
    p->screen_h = screen_h;
    p->game_over = false;
    p->ranking = false;

    return p;
}

void reset_score(Score * p)
{
    p->score = 0;
}

void reset_lives(Score * p)
{
    p->lives = NUM_LIVES;
}

void update_lives(Score * p, int variation)
{
    p->lives += variation;
}

void update_score(Score * p, int variation)
{
    p->score += variation;
}

void game_is_over(Score * p)
{
    p->game_over = true;
}

void draw_score(Score * p, bool shielded)
{
    char label[50];
    sprintf(label, "%d", p->score);
    if (shielded) strcat(label, " *");
    al_draw_text(p->font, p->color, 30, 5, ALLEGRO_ALIGN_LEFT, label);
    
    /* draw lives */
    /* override position parameters */
    for (int i=0, x=50; i<p->lives; i++, x+=50)
    {
        p->ship->x = x;
        p->ship->y = 160;
        draw_ship(p->ship);
    }
    
    /* if game is over */
    if (p->game_over)
        al_draw_text(p->font, p->color, p->screen_w/2, (p->screen_h/2)-200, ALLEGRO_ALIGN_CENTER, "GAME OVER");
}

void destroy_score(Score * p)
{
    al_destroy_font(p->font);
    destroy_ship(p->ship);
    free(p);
}

void update_ranking(Score * p, bool b)
{
    p->ranking = b;
}


