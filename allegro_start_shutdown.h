/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   allegro_start_shutdown.h
 * Author: r2d2
 *
 * Created on February 18, 2016, 9:34 PM
 */

#ifndef ALLEGRO_START_SHUTDOWN_H
#define ALLEGRO_START_SHUTDOWN_H

    #include <allegro5/allegro_audio.h>
    #define AL_STARTUP_ERROR -1
    #define AL_STARTUP_SUCCESS 0

    #define BACKGROUND	"Penguin-campaign.png"
    #define BACKGROUND_WIDTH 1024
    #define BACKGROUND_HEIGHT 640

    #define ICON                    "bender-glorious-golden.png"
    #define BACKGROUND_MUSIC	"16-bit_Cha-La_Loop.wav"
    
    #define D_WIDTH 1000
    #define D_HEIGHT 680

    int allegro_startup(void);
    void allegro_shut_down(void);
    ALLEGRO_DISPLAY * create_display(void);
    void stopMusic(ALLEGRO_SAMPLE *music);
    ALLEGRO_SAMPLE * loadPlayMusic(void);

#endif /* ALLEGRO_START_SHUTDOWN_H */

