

#ifndef SIMUL_MANAGEMENT_H
#define SIMUL_MANAGEMENT_H

    #include "input_manage_verification.h" 

	//Aunauqe ninguna de las funciones compartidas use estos tipos de datos es importante que esten los typedefs para el manejo grafico.
	typedef struct{ 
			double x,y; 
	}point_t;

	typedef struct
	{
			point_t position;
			double angle;
	}robot_t;

	typedef struct
	{
			unsigned int width;
			unsigned int height;
			bool * floor_array;
	}floor_t;

	typedef struct
	{
		   bool mode;
		   long unsigned int tickcount;
		   unsigned int robotcount;
		   robot_t *robots;
		   floor_t *piso;
	}simul_t;

    #define DIRTY_FLOOR 0
    #define CLEAN_FLOOR 1  

    #define ANGLE_RANGE 360
    #define DECIMAL_RANGLE 10	//0-10
    
    #define GRAFIC_SIMULATION 0
    #define INFO_SIMULATION	1
    
    #define NUM_SIMULATIONS 1000
    #define SIMULATION_ERROR -1
    #define SIMULATION_SUCESS 0

    #define MINIMUM_DIFFERENCE_TICKS 0.1

    #define EPSILON 0.010
    
    #define RADIAN(a) ( (a)/( 180.0/(double)M_PI) )
    #define ABS(x) ((x)<0?(-(x)):(x))
    
   
    int run_robot_grafic_simul(user_input_t * user_input,ALLEGRO_DISPLAY *display);
    int run_robot_stadist_simul(user_input_t * user_input,ALLEGRO_DISPLAY *display);
    void simulate_mode(user_input_t *user_input,ALLEGRO_DISPLAY *display);
#endif /* SIMUL_MANAGEMENT_H */

