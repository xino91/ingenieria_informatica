/* 7) MEMORIA COMPARTIDA
Como se comentó en el apartado de introducción, los procesos a diferencia de los hilos, no comparten el mismo espacio de memoria, por lo que si queremos que accedan a las mismas variables en memoria, estos deben compartirla. Realice un programa que expanda N procesos
hijos. Cada hijo debe compartir una variable denominada contador, que debe estar inicializada
a cero. Esta variable debe ser incrementada por cada proceso 100 veces. Imprima la variable
una vez finalicen los hilos y analice el resultado obtenido. Un resultado previsible para 3
procesos seria 300, así ha sido? */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>	//Para estructura pid_t
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>		//Para fork()
#include <string.h>		//Para la funcion strerror()

#define CLAVE (key_t) 234
#define MAX 10

int main(){

	int n, i, j, estado, pid_aux, *suma, id_memoria;
	pid_t pid;
	
	printf("Introduzca nº de Hijos: \n");
	scanf("%d", &n);
	
	id_memoria= shmget (CLAVE, sizeof(int), 0777 | IPC_CREAT);
	
	if(id_memoria == -1){
		
		printf("No se pudo obtener un ID para memoria compartida. \n");
		exit(EXIT_FAILURE);
	}
	
	suma= (int*) shmat (id_memoria, 0, 0);
	
	if(suma== NULL){
		
		printf("No consigo Memoria Compartida\n");
		exit(EXIT_FAILURE);
	}
	
	*suma=0;
	
	for(i=0; i<n; i++){
		pid=fork();
		
		switch(pid){
		
			case -1: 
				printf("Hubo un error en fork().\n");
				exit(EXIT_FAILURE);
			case 0:
				printf("Hijo %d (PID: %ld). Incrementando...\n", i+1, (long)getpid());
				
				for(j=0; j<100; j++){
				
					(*suma)++;
				
				exit(EXIT_SUCCESS);
				}
		}
	}
	
	while((pid_aux= wait(&estado))>0){
	
		if(WIFEXITED(estado)){
			printf("\t--> El hijo con PID: %d acabo. Estado: %d\n", pid_aux, WEXITSTATUS(estado));
		}
		
		printf("\n No hay mas hijos que esperar. Suma %d. Saliendo....\n", *suma);
		
		shmdt(suma);
		shmctl(id_memoria, IPC_RMID, NULL);
	}
	
	printf("\n");
	
	return 0;
}	
				
				
				
				
