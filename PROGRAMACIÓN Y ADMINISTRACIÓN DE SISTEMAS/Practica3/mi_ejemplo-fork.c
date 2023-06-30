/*Ejemplo de la funcion fork*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(){

	int status;
	pid_t hijo, flag;
	//printf("Hijo: %d\n", hijo);
	//printf("Flag: %d\n", flag);
	//printf("Status: %d\n", status);
	
	hijo = fork();
	
	switch(hijo){
		
		case -1:
			printf("Soy el Padre %d, error al crear el hijo\n",getpid());
			exit(EXIT_FAILURE);
		
		case 0:
			printf("Soy el hijo, mi ID es: %d y el de mi padre es: %d\n", getpid(), getppid());
			exit(EXIT_SUCCESS);
		
		default:
			printf("Soy el padre: %d y el ID de mi hijo es: %d\n", getpid(), hijo);
	}
	
	/*Espera del padre a los hijos*/
	//Pruebe a sustituir wait() por waitpid()
	while ( (flag=waitpid(hijo,&status,WNOHANG)) == 0 ){
		
		if(WIFEXITED(status)){
			printf("\nHijo con PID %d, finalizado con éxito, estado: %d\n", flag, WEXITSTATUS(status));
		}
		else if(WIFSIGNALED(status)){
			printf("\nHijo con PID %d finalizado al recibir una señal, estado: %d\n", flag, WTERMSIG(status));
		}
		else if(WIFSTOPPED(status)){
			printf("\nHijo con PID %d parado al recibir una señal, estado: %d \n", flag, WSTOPSIG(status));
		}
		else if(WIFCONTINUED(status)){
			printf("\nHijo con PID %d reanudado\n", flag);
		}
	}
	if(flag == -1 && errno==ECHILD){
		printf("Proceso Padre, valor de errno: %d, definida como: %s\n", errno, strerror(errno));
	}
}	














