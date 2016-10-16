#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "main_parsing_eda.h"
#include "input_manage_verification.h"



/*
 * La funcion inicializa la estructura de user_input_t donde se guardara todo
 * la data ingresada por linea de comando.
 * Principalmente inicializa los flags que seran empleados para evitar input repetido.
 */
void initialize_user_input(user_input_t* data)
{
	data->floor_height_f=false;
	data->floor_width_f=false;
	data->mode_f=false;
	data->num_robots_f=false;
}

int get_simulation_info(char *key,char* value,void *user_data)
{
	int status=CALLBCK_SUCCESS;
	unsigned int result;
	char *endptr=NULL;
	if(!key){//De pasarse un parametro seteamos un error, esto es opcional y se podria desactivar 
		status=CALLBCK_ERROR;
		fprintf(stderr,"Why would you pass a Parameter?? Check your input('%s') \n",value);
	}
	
	else if( !strcmp("height",key) || !strcmp("h",key) || !strcmp("alto",key ) )
	{
		result=strtoul(value,&endptr,0);
		if( ((user_input_t*)user_data)->floor_height_f  )
		{
			fprintf(stderr,"Error: Floor height already inputed\n");
			status=CALLBCK_ERROR;
		}
		else if(*endptr!='\0')
		{
			fprintf(stderr,"Error: Unable to convert value inputed to height. Check Your input(%s %s)\n",key,value);
			status=CALLBCK_ERROR;
		}
		else
		{
			((user_input_t*)user_data)->floor_height=result;
			((user_input_t*)user_data)->floor_height_f=true;
		}

	}
	else if( !strcmp("width",key) || !strcmp("w",key) || !strcmp("ancho",key ) )
	{
		result=strtoul(value,&endptr,0);
		if( ((user_input_t*)user_data)->floor_width_f  )
		{
			fprintf(stderr,"Error: Floor width already inputed\n" );
			status=CALLBCK_ERROR;
		}
		else if(*endptr!='\0')
		{
			fprintf(stderr,"Error: Unable to convert value inputed to width. Check Your input(%s %s)\n",key,value);
			status=CALLBCK_ERROR;
		}
		else
		{
			((user_input_t*)user_data)->floor_width=result;
			((user_input_t*)user_data)->floor_width_f=true;
		}
		
	}
	else if( !strcmp("robots",key) || !strcmp("n",key) || !strcmp("robot",key ) )
	{
		result=strtoul(value,&endptr,0);
		if( ((user_input_t*)user_data)->num_robots_f )
		{
			fprintf(stderr,"Error: Floor width already inputed\n" );
			status=CALLBCK_ERROR;
		}
		else if(*endptr!='\0')
		{
			fprintf(stderr,"Error: Unable to convert value inputed to robots. Check Your input(%s %s)\n",key,value);
			status=CALLBCK_ERROR;
		}
		else
		{
			((user_input_t*)user_data)->num_robots=result;
			((user_input_t*)user_data)->num_robots_f=true;
		}
	}
	else if( !strcmp("mode",key) || !strcmp("m",key)  )
	{
		result=strtoul(value,&endptr,0);
		if( ((user_input_t*)user_data)->mode_f )
		{
			fprintf(stderr,"Error: Mode already inputed\n" );
			status=CALLBCK_ERROR;
		}
		else if(*endptr!='\0')
		{
			fprintf(stderr,"Error: Unable to convert value inputed to mode. Check Your input(%s %s)\n",key,value);
			status=CALLBCK_ERROR;
		}
		else
		{
			((user_input_t*)user_data)->mode=result;
			((user_input_t*)user_data)->mode_f=true;
		}
	}
	else
	{
		fprintf(stderr,"Unknown key('%s') check your input",key);
		status=CALLBCK_ERROR;
	}
	
	return status;
	
}


int validate_simulation_info(user_input_t * user_input_data)
{
	int status=VALID_INPUT;
	if(!user_input_data->floor_height_f)
	{
		status=NOT_VALID_INPUT;
		fprintf(stderr,"ERROR: No floor height inputed\n ");
	}
	else if(!user_input_data->floor_width_f)
	{
		status=NOT_VALID_INPUT;
		fprintf(stderr,"ERROR: No floor width inputed\n ");
	}
	else if(!user_input_data->mode_f)
	{
		status=NOT_VALID_INPUT;
		fprintf(stderr,"ERROR: No mode inputed\n ");
	}
	else if(!user_input_data->num_robots_f)
	{
		status=NOT_VALID_INPUT;
		fprintf(stderr,"ERROR: No number of robots inputed\n ");
	}
		
	else if( !user_input_data->floor_height  || user_input_data->floor_height > MAX_FLOOR_HEIGHT){
		fprintf(stderr," Invalid range for floor height\n");
		status=NOT_VALID_INPUT;
	}
	else if( !user_input_data->floor_width  || user_input_data->floor_width > MAX_FLOOR_WIDTH ){
		fprintf(stderr," Invalid range for  floor width\n");
		status=NOT_VALID_INPUT;
	}
	else if( !user_input_data->num_robots  || user_input_data->num_robots > MAX_NUM_ROBOTS){
		fprintf(stderr," Invalid range for number of robots\n");
		status=NOT_VALID_INPUT;
	}
	else if(  user_input_data->mode >true ){//input debe ser tipo bool 0 o 1
		fprintf(stderr," Invalid input for mode Boolean input 0 or 1 \n");
		status=NOT_VALID_INPUT;
	}
	
	return status;
	
	
}
