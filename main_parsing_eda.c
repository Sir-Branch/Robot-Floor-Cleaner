#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "main_parsing_eda.h"

//Decidimos que no era un error llamar a un programa sin argumentos por lo tanto devuelve un 0 si no se encuentran argumentos 
/*
	La funcion parseCmdLine se ocupa de parsear la entrada por linea de commando via main
	y luego enviar la informacion a una funcion que es reciba para ser procesado.
	Separa los argumentos en Parametros y opciones que luego seran pasada a callback_func
	en conjunto con el userData.
		-Detecta keys vacias("-  ")
		-Opciones que no estan seguidas de value(osea se pone un value al final )
 	Ademas analiza lo devuelto por callback_func y corta en caso de que ser produzca un error(recibir un 0).
	parseCmdLine devuelve:
		-Un numero >=0 en caso de que no se produzca el error este es el numero de opciones y Parametros
		-Un -1 en caso de que se produzca un error

*/
int parseCmdLine(int argc, char *argv[], pCallback callback_func, void *userData)
{
	int cont_argum,cont_opciones_para=SIN_ARGUMENTOS; //cont_argum ira marcando el elemento de argv a analizar

	if(argc>1)//No es necesario pero aclara el codigo ya que de ser un 1 el for se corta solo.
		for(cont_argum=1;cont_argum<argc;cont_argum++,cont_opciones_para++)
			if(argv[cont_argum][0]==CLAVE_OPC)//Checkeamos si es una opcion o un argumento
			{
				if(argv[cont_argum][1]=='\0'){//si es solamente el '-' tiene un terminador despues
					cont_opciones_para=ERROR_CLAVE_VACIA;
					break;
				}
				else if(cont_argum+1==argc){//checkeamos que no sea una key/clave vacia osea que haya otro argumento despues
					cont_opciones_para=ERROR_VALOR_VACIO;
					break;
				}
				else{
					if(! (*callback_func)(&argv[cont_argum][1],argv[cont_argum+1],userData) ){//enviamos &argv[cont_argum][1] osea ignoramos/salteamos el '-'
						cont_opciones_para=ERROR_OPC;
						break;
					}
					cont_argum++;//como se trata de una opcion incrementramos ya que tomamos el key y el valor
				}
				
			}
			else //se podria usar un else if directamente, pero no queda tan claro el codigo desde nuestra punto de visto
				if(! (*callback_func)(NULL,argv[cont_argum],userData) ){
					cont_opciones_para=ERROR_PARA;
					break;
				}

	return cont_opciones_para;

}

