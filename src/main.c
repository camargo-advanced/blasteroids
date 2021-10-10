//
//  main.c
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/16/18.
//  Copyright © 2018 Marcelo Camargo. All rights reserved.
//
// how to compile:
//gcc blasteroids.c asteroids.c blast.c main.c point.c score.c utils.c wireframe.c spaceship.c -o blaster -lallegro -lallegro_image -lallegro_color -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec -lm
//
#include "blasteroids.h"

enum MYKEYS
{
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};

int main(int argc, char **argv)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer_fps = NULL, *timer_unshield = NULL, *timer_reset_game = NULL;
    ALLEGRO_SAMPLE *sound_fire = NULL, *sound_bang = NULL, *sound_thrust = NULL, *sound_game_over = NULL, *sound_game_start = NULL;
    bool key[5] = { false, false, false, false, false };
    bool redraw = true;
    bool doexit = false;
    
    srand((unsigned) time(NULL));
    
    if(!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    
    al_init_primitives_addon();
    
    al_init_font_addon(); // initialize the font addon
    
    if (!al_init_ttf_addon()) {
        fprintf(stderr, "failed to initialize ttf addon!\n");
        return -1;
    }
    
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "failed to initialize audio codecs!\n");
        return -1;
    }
    
    if(!al_install_keyboard())
    {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }
    
    /* install audio files */
    if (!al_install_audio()){
        fprintf(stderr, "failed to install audio!\n");
        return -1;
    }
    if (!al_reserve_samples(5)){
        fprintf(stderr, "failed to reserve samples!\n");
        return -1;
    }
    sound_fire = al_load_sample("../res/fire.wav");
    if (!sound_fire){
        fprintf(stderr, "fire.wav not loaded!\n" );
        return -1;
    }
    sound_bang = al_load_sample("../res/bang.wav");
    if (!sound_bang){
        fprintf(stderr, "bang.wav not loaded!\n" );
        return -1;
    }
    sound_thrust = al_load_sample("../res/thrust.wav");
    if (!sound_thrust){
        fprintf(stderr, "thrust.wav not loaded!\n" );
        return -1;
    }
    sound_game_over = al_load_sample("../res/siren.wav");
    if (!sound_game_over){
        fprintf(stderr, "Siren1Loop.wav not loaded!\n" );
        return -1;
    }
    sound_game_start = al_load_sample("../res/beep.wav");
    if (!sound_game_start){
        fprintf(stderr, "Siren1Loop.wav not loaded!\n" );
        return -1;
    }

    timer_fps = al_create_timer(1.0 / FPS);
    if(!timer_fps)
    {
        fprintf(stderr, "failed to create timer_fps!\n");
        return -1;
    }

    timer_unshield = al_create_timer(5.0);
    if(!timer_unshield)
    {
        fprintf(stderr, "failed to create timer_fps!\n");
        return -1;
    }

    timer_reset_game = al_create_timer(5.0);
    if(!timer_reset_game)
    {
        fprintf(stderr, "failed to create timer_fps!\n");
        return -1;
    }

    //turning multisampling on
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
    
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer_fps);
        al_destroy_timer(timer_unshield);
        al_destroy_timer(timer_reset_game);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer_fps);
        al_destroy_timer(timer_unshield);
        al_destroy_timer(timer_reset_game);
        return -1;
    }
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer_fps));
    al_register_event_source(event_queue, al_get_timer_event_source(timer_unshield));
    al_register_event_source(event_queue, al_get_timer_event_source(timer_reset_game));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(timer_fps);
    
    /* creates the game object */
    Blasteroids * game = create_blasteroids();
    if (!game)
    {
        fprintf(stderr, "failed to create game object!\n");
        return -1;
    }
    
    /* the ship starts shielded */
    al_start_timer(timer_unshield);
    shield_ship(game->ship);
    al_stop_samples();
    al_play_sample(sound_game_start, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
    
    while(!doexit)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            if (ev.timer.source == timer_fps)
            {
                redraw = true;
                
                if(key[KEY_UP]) {
                    accelerate_ship(game->ship);
                    if (!game->score->game_over) al_play_sample(sound_thrust, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
                //if(key[KEY_DOWN]) decelerate_ship(game->ship);
                if(key[KEY_LEFT]) turn_left_ship(game->ship);
                if(key[KEY_RIGHT]) turn_right_ship(game->ship);

                if(key[KEY_SPACE]) {
                    key[KEY_SPACE] = false;
                    float x, y, angle;
                    get_ship_orientation(game->ship, &x, &y, &angle);
                    add_blast(game->blasts, x, y, angle);
                    if (!game->score->game_over) al_play_sample(sound_fire, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
            }
            else if (ev.timer.source == timer_unshield)
            {
                al_stop_timer(timer_unshield);
                unshield_ship(game->ship);
            }
            else if (ev.timer.source == timer_reset_game)
            {
                if (game->score->ranking) {
                    
                }
                else {
                    al_stop_timer(timer_reset_game);
                    destroy_blasteroids(game);
                    game = create_blasteroids();
                    shield_ship(game->ship);
                    al_start_timer(timer_unshield);
                    al_stop_samples();
                    al_play_sample(sound_game_start, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
            }
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true; break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true; break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true; break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true; break;
                case ALLEGRO_KEY_SPACE:
                    key[KEY_SPACE] = true; break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false; break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false; break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false; break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false; break;
                case ALLEGRO_KEY_SPACE:
                    key[KEY_SPACE] = false; break;
                case ALLEGRO_KEY_ESCAPE:
                    doexit = true; break;
            }
        }
        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            
            /* update objects */
            update_ship(game->ship);
            update_asteroids(game->asteroids);
            update_blasts(game->blasts);
            
            /* check if the ship colided to an asteriod */
            Asteroid * ap;
            for (ap=game->asteroids->head; !game->ship->shielded && ap; ap=ap->next)
                if (is_point_in_circle(game->ship->x, game->ship->y, ap->x, ap->y, ap->radius)) {
                    reset_ship(game->ship);
                    al_start_timer(timer_unshield);
                    shield_ship(game->ship);
                    update_lives(game->score, -1);
                    if (!game->score->game_over) {
                        al_stop_samples();
                        al_play_sample(sound_bang, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                    }
                    break;
                }
            
            /* game over */
            if (!game->score->game_over && game->score->lives == 0) {
                game_is_over(game->score);
                shield_ship(game->ship);
                al_start_timer(timer_reset_game);
                al_stop_samples();
                al_play_sample(sound_game_over, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
            
            /* check if the blast hit an asteriod */
            Asteroid * head_ap = NULL, * tail_ap = NULL;
            for (ap=game->asteroids->head; ap; ap=ap->next)
                for (Blast * bp=game->blasts->head; bp; bp=bp->next)
                    if (is_point_in_circle(bp->x, bp->y, ap->x, ap->y, ap->radius)) {
                        /* create 2 new asteroids heading to different directions */
                        if (asteroid_hit(ap)) {
                            Asteroid * ca = clone_asteroid(ap);
                            asteroid_randomize_orientation(ap);
                            speed_up_asteriod(ap, 1.5f);
                            asteroid_randomize_orientation(ca);
                            speed_up_asteriod(ca, 1.5f);
                            if (!head_ap) head_ap = ca;
                            if (!tail_ap)
                                tail_ap = ca;
                            else {
                                tail_ap->next = ca;
                                tail_ap = ca;
                            }
                        }
                        bp->dead = true; /* remove blast */
                        update_score(game->score, 100*ap->times_hit);
                        if (!game->score->game_over) {
                            al_stop_samples();
                            al_play_sample(sound_bang, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                        }
                        break;
                    }
            
            /* add new items to main asteroids structure */
            if (head_ap) append_asteroids_list(game->asteroids, head_ap);

            /* move to next phase */
            if (game->asteroids->head == NULL)
            {
                int score = game->score->score;     /* save current score */
                int lives = game->score->lives;     /* save current lives */
                destroy_blasteroids(game);
                game = create_blasteroids();
                update_score(game->score, score);                   /* restore score */
                update_lives(game->score, -game->score->lives);     /* restore lives */
                update_lives(game->score, lives);                   /* restore lives */
                al_stop_samples();
                al_play_sample(sound_game_start, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
            
            /* display objects */
            draw_ship(game->ship);
            draw_asteroids(game->asteroids);
            draw_blasts(game->blasts);
            draw_score(game->score, game->ship->shielded);
            
            al_flip_display();
        }
    }
    
    al_destroy_timer(timer_fps);
    al_destroy_timer(timer_unshield);
    al_destroy_timer(timer_reset_game);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_sample(sound_fire);
    al_destroy_sample(sound_bang);
    al_destroy_sample(sound_thrust);
    al_destroy_sample(sound_game_over);
    al_destroy_sample(sound_game_start);
    
    /* frees game object */
    destroy_blasteroids(game);
    
    return 0;
}
