/* 3) Implementar un programa para realizar la suma en forma paralela de los valores de un
vector de 10 números enteros que van de 0 a 9. Utilice una cantidad de hilos indicada como 
parámetro de entrada por la linea de argumentos y reparta la suma del vector entre ellos
(como considere oportuno). La suma debe ser el subtotal devuelto por cada hijo. Haga 
comprobación de errores en el programa.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char *argv[]){

	int v[10];
	int i;
	
	rellenaVector(v,10);
	
	
	
	
	
	

}

void rellenaVector(int *v, int tam){
//Esta funcion rellena un vector con numeros aleatorios del 0 al 9

	int i;
	
	for(i=0; i<tam; i++){
	
	srand(time(NULL));
	
	v
	
