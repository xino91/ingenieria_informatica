/*Implemente un programa que cree dos hebras. Cada hebra ejecutará una función a la que se le
pasará como parámetro una cadena, concretamente a la primera hebra se le pasará la cadena "hola
" y a la segunda "mundo". La función que debe ejecutar ambas debe imprimir carácter a carácter
cadena recibida, haciendo un sleep(1) entre cada impresión de caracter. Observese resultados*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


void * leeCadena(char *nombreCadena);

int main(void){


	pthread_t thd1, thd2;  	//Declaración de dos hebras, hilos o procesos ligeros.No creacion
	
	char cadena1[50]= "Hola";
	char cadena2[50]= "Mundo";
	
	pthread_create(&thd1, NULL, (void*) leeCadena, &cadena1);
	pthread_create(&thd2, NULL, (void*) leeCadena, &cadena2);
	
	pthread_join(thd1,NULL);
	pthread_join(thd2, NULL);
	printf("Han finalizado los thread\n");
	exit(EXIT_SUCCESS);
	
		
	
return 0;
}


void * leeCadena(char *nombreCadena){
	
	for(int i=0; i<strlen(nombreCadena); i++){
		
		printf("%c\n", nombreCadena[i]);
		sleep(1);
	}
}	

	
