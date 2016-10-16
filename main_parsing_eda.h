#ifndef MAIN_PARSING_EDA_H
#define	MAIN_PARSING_EDA_H

	#define SIN_ARGUMENTOS 0
	#define CALLBCK_ERROR 0
	#define CALLBCK_SUCCESS 1
        #define PARSING_ERROR -1

        #define CLAVE_OPC	'-'

	enum errores{ERROR_CLAVE_VACIA=-1,ERROR_VALOR_VACIO=-1,ERROR_PARA=-1,ERROR_OPC=-1};
	//Decidimos dejar abierta la posibilidad de diferenciar entre los errores
	//Terminamos implementando el enum para distinguir en el main los errores producidos 

	typedef int (*pCallback) (char *, char*, void *); 
	//FUNCTION HEADERS 
	int parseCmdLine(int argc, char *argv[], pCallback p, void *userData); 
	//int parseCallback(char *key, char *value, void *userData); Lo logico es que cada usuario lo defina fuera de la lib como sucede con qsort,etc 



#endif

