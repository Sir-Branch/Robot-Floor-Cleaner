
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <math.h>
#include <allegro5/display.h>
#include "simul_management.h"
#include "input_manage_verification.h"
#include "grafic_management.h"
#include "allegro_start_shutdown.h"


static floor_t * create_floor(unsigned int w, unsigned int h);
static void destroy_floor(floor_t *floor_data);
static void dirtyfloor(bool *floor,unsigned int w, unsigned int h);

static robot_t *create_initialize_robots(unsigned int robotcount,unsigned int floor_width,unsigned int floor_height);
static double random_angle(unsigned int range);
static double random_cord(unsigned int range);

static void detect_robot_crash(robot_t *robot,floor_t *floor);
static simul_t *create_simul(unsigned int robotcount,unsigned int floor_width,unsigned int floor_height,bool mode);
static void destroy_simul(simul_t *simul);
static int is_floor_clean(bool * array,const unsigned int w, const unsigned int h);
static void update_robots(const simul_t*simulation,const double move_rate);



/*
 * La funcion crea un piso, alloca el tamanio(no tengo enie D: ) necesario, y luego crea el arreglo en si de las baldosas.
 * De producirse un error libera cualquier cosa que se haya creado evitando memory leaks.
 */

floor_t * create_floor(unsigned int w, unsigned int h)
{
	bool * tempfloor;
	floor_t * created_floor=(floor_t*) malloc(sizeof(floor_t));

	if(created_floor!=NULL)//! NULL pointer
	{
		created_floor->width=w;//asignamos ancho y alto
		created_floor->height=h;

		tempfloor=(bool*)malloc(w*h*sizeof(bool));

		if(tempfloor!=NULL) 
		{
			dirtyfloor(tempfloor,w,h);
			created_floor->floor_array=tempfloor;
		}
		else
		{
			free(created_floor);
			created_floor=NULL;
		}
	}
	
	return created_floor;
}

int is_floor_clean(bool * array,const unsigned int w, const unsigned int h)
{
	int result=CLEAN_FLOOR;
	int tile_num;
	for(tile_num=0;tile_num<w*h;tile_num++)
		if(array[tile_num]==DIRTY_FLOOR)
		{
			result=DIRTY_FLOOR;
			break;
		}
	return result;
}


//Destruye el piso, osea que libera el arreglo al que apunta y el mismo puntero al piso
void destroy_floor(floor_t *floor_data)
{
	free(floor_data->floor_array);
	free(floor_data);
}

/*
 * Ensucia el piso, recibe un puntero al piso y el largo y ancho.
 */
void dirtyfloor(bool *floor,unsigned int w, unsigned int h)
{
	int tile_count;
	for(tile_count=0;tile_count<w*h;tile_count++)
		floor[tile_count]=DIRTY_FLOOR;

}


/*
 * Esta funcion crea e inicializa robots con valores aleatorios para eso toma el ancho y el alto del piso 
 * que seran empleados para calcular las coordenadas aleatorias.
 * De producirse un error devuelve un NULL.
 */
robot_t *create_initialize_robots(unsigned int robotcount,unsigned int floor_width,unsigned int floor_height)
{
	int rand_count;
	robot_t *robot_array=(robot_t*) malloc(sizeof(robot_t)*robotcount);
	if(robot_array!=NULL)
		for(rand_count=0;rand_count<robotcount;rand_count++)
		{
			robot_array[rand_count].angle=random_angle(ANGLE_RANGE);
			robot_array[rand_count].position.x=random_cord(floor_width);
			robot_array[rand_count].position.y=random_cord(floor_height);
		}
		
	return robot_array;
}


/*
 * Actualiza todas las posiciones de los robots, detecta si alguno se choco y limpia todas las baldosas.
 * 
 */
void update_robots(const simul_t*simulation,const double move_rate)
{
	unsigned int number_robots=simulation->robotcount;
	int robot_loop_count;
	
	for(robot_loop_count=0; robot_loop_count<number_robots; robot_loop_count++)
	{
		simulation->robots[robot_loop_count].position.x+=move_rate*sin(RADIAN(simulation->robots[robot_loop_count].angle));
		simulation->robots[robot_loop_count].position.y-=move_rate*cos(RADIAN(simulation->robots[robot_loop_count].angle));
		detect_robot_crash(&simulation->robots[robot_loop_count],simulation->piso);
	}
	
}



/*
 * Revisa las 8 posibilidades de choque del robot y asi devuelve un angulo que sirva
 *	Seguramente haya una forma mucho mas eficiente y entendible de revisar esto. Pero todavimos no vimos algoritmos
 * 
 * Ademas de detectar y corregir el robot si el mismo se choco con una esquina, limpia la baldosa donde el mismo quedo
 * 
 * 0 grados norte
 * 90 este
 * 180 sur
 * 270 oeste 
 * 
 *  _ _ _ _ _ _ _ _ _ _ _ _ _ _        _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
 * | Esquina izquierda necesita			Esquina derecha necesita	|
 * | entre 90-180 grados				entre 180 y 270 grados		|
 * |																|
 * |																|
 * |																|
 * |																|
 * |																|
 * |																|
 * |																|				
 * | Esquina izquierda inferior			Esquina derecha necesita	|
 * | necesita entre 0-90 grados			entre 270-0 grados			|
 * |																|
 * |_ _ _ _ _ _ _ _ _ _ _ _ _ _			_ _ _ _ _ _ _ _ _ _ _ _ _ _ |															|
 * 
 * 
 */
void detect_robot_crash(robot_t *robot,floor_t *floor)
{
	
	unsigned int floor_width=floor->width;
	unsigned int floor_height=floor->height;
	
	if(robot->position.x>0 && robot->position.x<floor_width-EPSILON && robot->position.y>0 && robot->position.y<(floor_height-EPSILON) )
	{
		;//Hace mas eficiente el codigo evitamos revisar las demas condiciones ya que va a ser menos las veces donde choque que las que no.
	}
	else if( robot->position.x>floor_width-EPSILON && robot->position.y>(floor_height))//Si se excedio de la esquina de abajo a la derecha
	{
		robot->position.x=floor_width-EPSILON ;//casteo a double automatico
		robot->position.y=floor_height-EPSILON ;//casteo a double automatico
		robot->angle=random_angle(90)+270;
	}
	else if( robot->position.x>floor_width && robot->position.y<0  )//Si se excedio de la esquina de arriba a la derecha
	{
		robot->position.x=floor_width-EPSILON ;//casteo a double automatico
		robot->position.y=0;//casteo a double automatico
		robot->angle=random_angle(90)+180;

	}
	else if( robot->position.x<0 && robot->position.y<0 )//Se paso de la esquina arriba izquierda
	{
		robot->position.x=0;//casteo a double automatico
		robot->position.y=0;//casteo a double automatico
		robot->angle=random_angle(90)+90;

	}
	else if(robot->position.x<0 && robot->position.y>(floor_height) )//Si se paso de la esquina de abajo a la izquierda
	{
		robot->position.x=0;//casteo a double automatico
		robot->position.y=floor_height-EPSILON ;//casteo a double automatico
		robot->angle=random_angle(90);

	}
	else if(robot->position.x>floor_width-EPSILON )
	{
		robot->position.x=floor_width-EPSILON ;//casteo a double automatico
		robot->angle=random_angle(180)+180;

	}
	else if(robot->position.x<0)
	{
		robot->position.x=0;
		robot->angle=random_angle(180);
		
	}
	else if(robot->position.y>(floor_height-EPSILON))
	{
		robot->position.y=floor_height-EPSILON ;//casteo a double automatico
		robot->angle=random_angle(180)-90; //necesitamos entre 270-90
		if(robot->angle <0)
			robot->angle=ABS(robot->angle)+270;//
		
	}
	else if(robot->position.y<0)
	{
		robot->position.y=0;
		robot->angle=random_angle(180)+90; //necesitamos angulos entre 90-270
		
	}	
	
}

void clean_floors(robot_t *robot,floor_t *floor,unsigned int robot_count)
{
	unsigned int floor_width=floor->width;
	int robots_clean;
	
	for(robots_clean=0;robots_clean<robot_count;robots_clean++)
		floor->floor_array[ ((unsigned int)robot[robots_clean].position.y ) * floor_width +(unsigned int)robot[robots_clean].position.x ]=CLEAN_FLOOR;

}

//Genera un angulo aleatorio con una parte decimal, va desde 0-(ANGLE_RANGE-1)
double random_angle(unsigned int range){
	return ( rand()%range + (rand()%DECIMAL_RANGLE) /10.0 );
	
}

//Recibe un rango y con eso genero una coordenada aleatora con una parte decimal.
double random_cord(unsigned int range){
	return (  rand()%range +  (rand()%DECIMAL_RANGLE) /10.0 );
	
}


/*
 * 
 * Se ocupa de crear TODAS las condiciones iniciales para una correcta simulacion, todo realizado mediante funciones.
 * -Crea el piso y lo inicializa en sucia
 * -Crea los robots
 * -Setea el tick count en 0
 * En Caso de producirse un error en cualquiera de las creaciones devuelve un NULL.
 */
simul_t *create_simul(unsigned int robotcount,unsigned int floor_width,unsigned int floor_height,bool mode)
{
	simul_t *result=(simul_t *) malloc(sizeof(simul_t));
	
	if(result !=NULL)
	{
		robot_t *temp_robots;
		floor_t *temp_piso;

		if(temp_piso=create_floor(floor_width,floor_height))
		{
			if(temp_robots=create_initialize_robots(robotcount,floor_width,floor_height))
			{
				result->mode=mode;
				result->tickcount=0;
				result->robotcount=robotcount;
				result->robots=temp_robots;
				result->piso=temp_piso;
			}
			else
				destroy_floor(temp_piso);
		}
		else
		{
			free(result);
			result=NULL;
		}
		
	}
	
	return result;
}


void destroy_simul(simul_t *simul)
{
	
 	//destroy_floor(simul->piso);// Tira " free(): invalid next size (normal): 0x0000000000668fe0 "
	//free(simul->robots);//Y corta el programa algo que ver con estos frees pero no lo pudimos arreglo
	free(simul);
	
}


void simulate_mode(user_input_t *user_input,ALLEGRO_DISPLAY *display)
{
	switch(user_input->mode)
	{
		case GRAFIC_SIMULATION:
			run_robot_grafic_simul(user_input,display);
			break;
			
		case INFO_SIMULATION:
			run_robot_stadist_simul(user_input,display);
			break;
		
		default:
			//shouldn't reach this stage
			break;
	}
	
	
}

int run_robot_grafic_simul(user_input_t * user_input,ALLEGRO_DISPLAY *display)
{
	int simul_status=SIMULATION_SUCESS;
	simul_t *current_simulation=create_simul(user_input->num_robots,user_input->floor_width,user_input->floor_height,user_input->mode);
	
	if(!current_simulation)
	{
		fprintf(stderr,"Unable to allocate memory for simulation hahaha your RAM sucks!!\n");
		simul_status=SIMULATION_ERROR;		
	}
	else
	{
		do
		{
			draw_floor_robots(current_simulation);
			al_flip_display();
			update_robots(current_simulation,1);
			clean_floors(current_simulation->robots,current_simulation->piso,current_simulation->robotcount); 
			al_rest(0.1);

		}while(!is_floor_clean(current_simulation->piso->floor_array,current_simulation->piso->width,current_simulation->piso->height ));
		
		draw_floor_robots(current_simulation);
		al_flip_display();
		destroy_simul(current_simulation);
		
	}
	
		
	al_show_native_message_box(display, "Simulation Finished", "Living la vida loca", 
							"The simulation has finished press ok to exit.",NULL, 0);
	return simul_status;
	
}

int run_robot_stadist_simul(user_input_t * user_input,ALLEGRO_DISPLAY *display)
{
	int current_status=SIMULATION_SUCESS,robot_count,simulation_count;
	unsigned long int tick_count;
	double * average_tick_array =(double *)malloc(user_input->num_robots * sizeof(double) ) ;
	simul_t *current_simulation;

	if(!average_tick_array)
	{
		fprintf(stderr,"Unable to allocate memory for array of tick_counts hahaha your RAM sucks!!\n");
		return SIMULATION_ERROR;			
	}
	
	for(tick_count=0, robot_count=1; robot_count<=(user_input->num_robots) ;robot_count++,tick_count=0)
	{
		for(simulation_count=0;simulation_count<NUM_SIMULATIONS;simulation_count++)
		{
			current_simulation=create_simul(robot_count,user_input->floor_width,user_input->floor_height,user_input->mode);
			if(!current_simulation)
			{
				fprintf(stderr,"Unable to allocate memory for simulation hahaha your RAM sucks!!\n");
				current_status=SIMULATION_ERROR;
				break;			
			}
			do
			{
				update_robots(current_simulation,1.0);
				clean_floors(current_simulation->robots,current_simulation->piso,current_simulation->robotcount); 
				tick_count++;
			}while(!is_floor_clean(current_simulation->piso->floor_array,current_simulation->piso->width,current_simulation->piso->height ));
			destroy_simul(current_simulation);
			
		}
		average_tick_array[robot_count-1]= (double)tick_count/NUM_SIMULATIONS;
		printf("Average tick for #%d robots = %f\n",robot_count,average_tick_array[robot_count-1]);
		if(robot_count>1)
			if( (average_tick_array[robot_count-2]-average_tick_array[robot_count-1])<MINIMUM_DIFFERENCE_TICKS)
				break;//Si la diferencia entre agregar un robot es menor que la Minimum diference cortamos el programa
			
	}	


	draw_graph(average_tick_array,robot_count-1,D_WIDTH,D_HEIGHT);
	
	al_show_native_message_box(display, "Simulation Finished", "Living la vida loca", 
							"The simulation has finished press ok to exit.",NULL, 0);
	free(average_tick_array);
	
	return current_status;
}