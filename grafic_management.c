#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "simul_management.h"
#include "allegro_start_shutdown.h"


static void DibujoRectangulo(bool*arreglodepiso,unsigned int largodepiso,unsigned int alturadepiso,unsigned int tamdisplayx,unsigned int tamdisplayy);
static void draw_robot (unsigned int tile_width_quantity, unsigned int tile_height_quantity, double x, double y);
static ALLEGRO_COLOR allegroRandomColor(void);

void DibujoRectangulo(bool*arreglodepiso,unsigned int largodepiso,unsigned int alturadepiso,unsigned int tamdisplayx,unsigned int tamdisplayy)
{
    unsigned int largobaldoza=tamdisplayx/largodepiso;
    unsigned int alturabaldoza=tamdisplayy/alturadepiso;
    
    int i,n;
    
    for(n=0;n<alturadepiso;n++)
        for(i=0;i<largodepiso;i++)
        {
            if(arreglodepiso[n*largodepiso+i]==0)    
               al_draw_filled_rectangle(i*largobaldoza,n*alturabaldoza,largobaldoza+i*largobaldoza,alturabaldoza+n*alturabaldoza,al_map_rgb(200,200,200));
            else
               al_draw_filled_rectangle(i*largobaldoza,n*alturabaldoza,largobaldoza+i*largobaldoza,alturabaldoza+n*alturabaldoza,al_map_rgb(255,255,255));
           
            al_draw_rectangle(i*largobaldoza,n*alturabaldoza,largobaldoza+i*largobaldoza,alturabaldoza+n*alturabaldoza,al_map_rgb(0,0,0),2.5);
        }
                       
        
}

/*
 * draw robot_dibuja los robots en el bitmap y se fija si el robot no va a quedar fuera de este,
 * si queda fuera, lo dibuja en el borde en el cual se pasa
 */
void draw_robot (unsigned int tile_width_quantity, unsigned int tile_height_quantity, double x, double y)
{
    unsigned int width = D_WIDTH/tile_width_quantity;
    unsigned int height = D_HEIGHT/tile_height_quantity;
    double radius = width<height?width/4.0:height/4.0;
    
    if (x*width < radius)
        x = radius/width; 
    else if (D_WIDTH - x*width < radius)
        x = (D_WIDTH - radius)/width;
    
    if(y*height < radius)
        y = radius/height; 
    else if(D_HEIGHT - y*height < radius) 
        y = (D_HEIGHT - radius)/height;
    
    al_draw_filled_circle (x*width, y*height, radius, al_map_rgb(0,0,0));
    al_draw_filled_circle (x*width, y*height, radius/1.5, al_map_rgb(75,68,68));
	
}


void draw_floor_robots(simul_t *simulation)
{
	int robot_counter;
	al_clear_to_color(al_map_rgb(0,0,0));
	DibujoRectangulo(simulation->piso->floor_array, simulation->piso->width, simulation->piso->height,D_WIDTH,D_HEIGHT );
	for(robot_counter=0;robot_counter<simulation->robotcount;robot_counter++)
		draw_robot(simulation->piso->width, simulation->piso->height,simulation->robots[robot_counter].position.x,
				simulation->robots[robot_counter].position.y );
	
}

#define BENDER "bender.png"
#define FONT 	"BebasNeue.otf"

int draw_graph(double *average_tick_array, unsigned int num_robots, double display_width, double display_high)
{
    ALLEGRO_BITMAP * bender=al_load_bitmap(BENDER);
    ALLEGRO_FONT *font=al_load_font(FONT, 20, 0);
   
	while(1)
		if(bender =al_load_bitmap(BENDER) )
		{
			if( font=al_load_font(FONT, 20, 0))
				break;
			else{
				fprintf(stderr,"Unable to load font\n");
				return -1;
			}
			
		}
		else{
			fprintf(stderr,"Unable to load bitmap\n");
			return -1;
		}
	 
           
    double line_width = 580.0; //ancho de la linea base del grafico (eje x, eje y)
    unsigned int temp,temp2;
    double calc_barr_position; //variable usada para calcular la posicion de las barras en el grafico. Depende del tamano
                               //del ancho de la linea y cantidad de robots.  
    double line_width_origin = display_width/13.; //origen de la linea base del grafico (x)
    double line_high_origin = display_high/1.05; //origen de la linea base del grafico (y)
    
    calc_barr_position= line_width/num_robots; //calculo para saber el ancho de las barras con respecto al tamano de la
                                               //linea base.
    //Dibujo de las barras, con respecto al eje x se va sumando el ancho calculado anteriormente.
    //con respecto al eje y, se toma el primer elemento del arreglo como el elemento con mas ticks y se le asigna la altura
    //maxima posible. Luego, con una regla de tres simple se le asigna la altura de la barra al resto de los elementos. 
	
	al_clear_to_color(al_map_rgb(0,0,0));
	
    for(temp=0,temp2=0;temp<num_robots;temp++,temp2+=calc_barr_position)   
       al_draw_filled_rectangle(line_width_origin+temp2, line_high_origin,line_width_origin+calc_barr_position+temp2 ,line_high_origin-((average_tick_array[temp]*line_width)/average_tick_array[0]),allegroRandomColor());
            
    //Dibujo las lineas del grafico (eje x, eje y), se le agrega un 10 para que los barras no esten al filo de la linea.
    al_draw_line(line_width_origin, line_high_origin, line_width_origin+line_width+10, line_high_origin,al_map_rgb(255,255,255),3);				
    al_draw_line(line_width_origin, line_high_origin, line_width_origin, line_high_origin-line_width-10,al_map_rgb(255,255,255),3);				
    
    //Nombres de los ejes
    al_draw_text(font,al_map_rgb(255,255,255),line_width_origin,line_high_origin,0,"Cantidad de robots");
    al_draw_text(font,al_map_rgb(255,255,255),line_width_origin-10,line_high_origin-line_width,ALLEGRO_ALIGN_RIGHT,"Ticks");

    //Texto a la derecha
    font = al_load_font("BebasNeue.otf", 30, 0);
    al_draw_textf(font,al_map_rgb(255,255,255),(display_width/1.5)+100,(display_high/5.)+50,0,"Numero de robots %d",(num_robots));
    al_draw_bitmap(bender,display_width/1.5,display_high/5.,0);
    
	al_flip_display();
  
	
	al_destroy_bitmap(bender);
	al_destroy_font(font);
}

ALLEGRO_COLOR allegroRandomColor(void)
{
	return al_map_rgb(rand()%256,rand()%256,rand()%256);	
}



