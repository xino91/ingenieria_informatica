/* 6) Use por ejemplo el ejercicio1 y cree unua variable global de tipo entero inicializada a 0
Haga que cada hijo aumente en uno el valor de esa variable global y que el padre imprima el resultado final. ¿Que ocurre?. Correcto, su valor no se modifica porque los hijos son procesos
nnuevos que no comparten memoria. Para ello, y concretamente en sistemas basados en UNIX y 
que siguen el estándar POSIX se utilizan métodos de comunicación entre procesos como son:
Memoria Compartida y semáforos.*/

#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


void *incremento(void *p);


int main(int argc, char **argv){
	
	int contador=0;
	int N=argv[1];
	int valor_devuelto=0;
	
	pthread_t hilos[N];
	
	
	for(i=0; i<N; i++){
		pthread_create(&hilos[i], NULL, (void*) incremento, &contador);
	}
	
	for(i=0; i<N; i++){
		pthread_join(hilos[i], (void**) &valor_devuelto);
	}
	
	printf("%d\n", valor_devuelto);
}



void *incremento(void *p){

	int contador =(int)p, i;
	
	for(i=0; i<100; i++){
		p++;
	}
	
	pthread_exit((void*)p);
}
	
