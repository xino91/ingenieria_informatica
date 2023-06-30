//EJERCICIO3 SERVIDOR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <mqueue.h>
#include <time.h>

int main(int argc, char *argv[]){
	
	int c;
	int option_index = 0;
	
	//Cola de mensajes
	mqd_t mq_mensajes;
	//Cola para mensajes del regex
	mqd_t mq_regex; 
	
	//Buffers para mensajes
	char buffer_mensajes[1025];
	char buffer_regex[50]; 
	
	//Atributos de las cola o colas
	struct mq_attr atributos;
	atributos.maxmsg  = 10;
	atributos.msgsize = 1024;
	
	//Flag para indicar cuando parar
	int must_stop = 0;
	
	
	
	//Estructura a utilizar por getoplong
	static struct long_options[] = {
	
		{"regex", required_argument, 0 , "r"}
		{"help" , no_argument, 	    0 , "h"}
		//Necesario para indicar el final de opciones
		{0,0,0,0}
	};
	
	while( (c = getop_long(argc, argv, "r:h", long_options, &option_index)) != -1){
		
		switch(c){
			
			case 'r':
				
			break;
			
			case 'h':
				printf("Uso del programa: ejercicio3-servidor.c [opciones]\n");
				printf("[OPCIONES]:\n");
				printf("-h, --help  -> Imprimir esta ayuda\n");
				printf("-r, --regex -> Expresión regular a utilizar\n"); 
			break;
		}
	}
