// getopt() 
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int aflag = 0;
	int bflag = 0;
	char *cvalue = NULL;
	int index;
	int c; 		//Para los distintos casos
		
	 /* IMPORTANTE:
     Las variables optind, optarg, opterr y optopt son variables externas incluidas en <unistd.h> */
	
	/*opterr: si le damos un valor igual 0, indica que no imprimira por stderr 
	ningún mensaje de error (por defecto o con valor 1, si lo hará)*/
	opterr=1;
	
	// getopt obtiene el siguiente arguemento en la lista de argumentos que se le pasan al programa
	// Normalmente los argumentos son los pasados a la función main al comienzo de nuestro programa (argc y argv)
	// getopt va iterando, y devuelve -1 si ya hemos consultado toda la linea de argumentos.
     // Sino, devuelve el caracter de opción encontrado para caracteres validos 
     // o devuelve ? si el caracter no es valido segun la cadena especificada.
	while(( c = getopt(argc, argv, "abc:d:"))!=-1){
	
		
	   // Podemos observar qué pasa con las variables externas que va gestionando
        //   getopt() durante las sucesivas llamadas. 
        //   - optind Indice del siguiente elemento a procesar del vector argv[]
        //   - optarg recoge el valor del argumento obligario de una opcion.
        //   - optopt recoge el valor de la opcion cuando es desconocida (?) o INCOMPLETA respecto a las opciones indicadas. 
		switch(c){
			
			case 'a':
				aflag = 1; //Bandera que indica que la opción -a se ha pasado por línea de argumentos
				break;
			
			case 'b':
				bflag = 1; //Bandera que indica que la opción -b se ha pasado por línea de argumentos
				break;
			
			case 'c':
				cvalue = optarg;  //En optarg se guarda el valor de argumento obligatorio que requiere c
				break;
			
			case '?':
				if(optopt == 'c')
					fprintf(stderr, "La opción %c requiere un argumento, valor de opterr = %d\n", opterr);
				
				else if (isprint (optopt)) //Se mira si el caracter es imprimible
		          	fprintf (stderr, "Opción desconocida \"-%c\". Valor de opterr = %d\n", optopt, opterr);
		     	else //Caracter no imprimible o especial
		             fprintf (stderr, "Caracter `\\x%x'. Valor de opterr = %d\n", optopt, opterr);
		          return 1;  //Finaliza el programa  
		     
		     default:
		     	abort();
		}
		printf("optind: %d, optarg: %s, optopt: %c, opterr: %d\n", optind, optarg, optopt, opterr);
		}
		
	for (index = optind; index < argc; index++)
        printf ("Argumento \"%s\" de la línea de comandos que NO es una opción.\n", argv[index]);
       
     		   
				

		
		             
		             
		             
		             
		             
		             
		             
		             
		             
		             
		             
		             
		             
		             
		             
			
		
