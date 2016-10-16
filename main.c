/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: r2d2
 *
 * Created on March 24, 2016, 1:56 PM
 */

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include "simul_management.h"
#include "main_parsing_eda.h"
#include "input_manage_verification.h"
#include "allegro_start_shutdown.h"
/*
 * 
 */
#define STARTUP_ERROR -1
#define STARTUP_SUCCESS 0

int startup_program(int argc, char** argv,pCallback parser_callback, user_input_t *user_data);

int main(int argc, char** argv) {

	int program_status=STARTUP_SUCCESS;
	user_input_t user_data;
	initialize_user_input(&user_data);
	ALLEGRO_DISPLAY *display;
	if(startup_program(argc,argv,&get_simulation_info,&user_data)==STARTUP_ERROR){
		fprintf(stderr,"Unable to startup program :O \n");
		program_status=STARTUP_ERROR;
		
	}
	else if( !(display=create_display()) ){
		printf("Unable to create display\n");
		allegro_shut_down();
		program_status=AL_STARTUP_ERROR;
	}
	else
	{
		ALLEGRO_SAMPLE *background_music=loadPlayMusic();
		simulate_mode(&user_data,display);
		al_destroy_display(display);
		stopMusic(background_music);
		printf("Shutting down allegro\n");
		allegro_shut_down();
			
	}
	return 0;
}



int startup_program(int argc, char** argv,pCallback parser_callback, user_input_t *user_data)
{
	int program_status=STARTUP_SUCCESS;

	if(allegro_startup()==AL_STARTUP_ERROR){
		fprintf(stderr,"Unable to startup allegro D: \n");
		program_status=STARTUP_ERROR;
	}
	else if(parseCmdLine(argc,argv,parser_callback,user_data)==PARSING_ERROR){
		fprintf(stderr,"Error parsing input, invalid user input '''⌐(ಠ۾ಠ)¬''' \n");
		program_status=STARTUP_ERROR;
	}
	else if(validate_simulation_info(user_data)==NOT_VALID_INPUT){
		fprintf(stderr,"Error parsing input, not valid values in input (✖╭╮✖) \n");
		program_status=STARTUP_ERROR;
	}
	
	srand(time(NULL));
	
	return program_status;
}


