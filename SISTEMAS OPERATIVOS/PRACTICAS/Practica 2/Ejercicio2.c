/* Implemente un programa que cree un número N de hebras. Cada hebra creará 2 números 
aleatroios y guardará su suma en una variable para ello, que será devuelta a la hebra llamadora
(la que invocó pthread_create()). La hebra principal ira recogiendo los valores devueltos por 
las N hebras y los irá sumando en una variable no global cuyo resultado mostrará al final
por pantalla. Para ver que los resultados finales son los que usted espera, muestre los
números que va creando cada hevra y su suman de forma que pueda comparar esas sumas parciales
con la suma final de todos los números creador por todas las hebras. Utilice macros
definidas y comprobación de errores en sus programas (errno y comprobación de valores devueltos
en cada llamada), será valorado en el examen fincal de la asignatura)*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


void *hebragenera( int* sumaparcial);


int main(void){
	
	int sumaparcial=0, i, n=0, sumatotal=0;
	
	
	printf("Introduzca el número de hebras que desea crear\n");
	scanf("%d", &n);
	
	pthread_t thd[n];
	for(i=0; i<n; i++){
	
	pthread_create(&thd[i], NULL, (void*) hebragenera, &sumaparcial);
	pthread_join(thd[i], NULL);
	sumatotal=sumatotal + sumaparcial;
	}
	
	printf("Suma: %d\n", sumatotal);

}

void *hebragenera( int* sumaparcial){

	int x=0;
	srand(time(NULL));
	*sumaparcial=0;
	for(int j=0; j<2; j++){
		
		x=(rand()%20)+1;
		printf("El número generado es: %d\n", x);
		*sumaparcial=*sumaparcial+x;
		sleep(1);
	}
	
	printf("La suma parcial es: %d\n", *sumaparcial);
}
