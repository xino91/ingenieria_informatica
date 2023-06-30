/* 4) Implemente un programa donde se creen dos hijos. Uno de ellos que abra la calculadora de Linux en gnome (gnome-calculator) y el otro que abra un editor de textos con N Ficheros pasados como argumentos (recuerde hacer que el padre espere a los hijos). La invocación sería 
"./miPrograma gnome-calculator gedit fichero1.txt fichero2.txt ficheroN.txt". Implemente cada
hijo en una función (tenga cuidado con el uso de punteros y argumentos.) */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void abrirCalculadora (char *calculadora);
void abrirFicheros( char *nombre, char **dir);

int main(int argc, char **argv){

	pid_t pid;
	int i, chilpid, status, n;
	
	printf("Número de ficheros para abrir:\n");
	scanf("%d", &n);
	
	printf("%s", argv[0]);
	
	
	if(argc==n+3){
		for(i=0; i<n+2; i++){
			pid=fork();
			
			if(pid==0){
				if(i==0){
					abrirCalculadora(argv[1]);
				}			
				if(i>=1){
					abrirFicheros(argv[i+1], &argv[i+1]);
				}
			}
		
		while((chilpid= wait(&status))>0){
			
			if(WIFEXITED(status)){
				printf("Child %d exited, Status %d.\n", chilpid, WEXITSTATUS(status));
			}
			else if(WIFSIGNALED(status)){
				printf("Chil %d Killed, Status %d.\n", chilpid, WTERMSIG(status));
			}
			else if(WIFSTOPPED(status)){
				printf("Chil %d stopped. Status %d.\n", chilpid, WSTOPSIG(status));
			}
		}
		
		
		if(chilpid==-1 && errno==ECHILD){
			printf("No hay más hijos que esperar\n");
		}
		else{
			perror("Error en la invocación de wait o la llamada ha sido interrumpida por una señal.");
			
			exit(EXIT_FAILURE);
		}
		
		}
		
	}
	else{
		printf("ERROR. Vuelva a ejecutar el programa. Numero de argumentos erroneo.\n\n");
		exit(EXIT_FAILURE);
	}
}


void abrirCalculadora( char *calculadora){
	
	execlp(calculadora,calculadora,NULL);
	return;
}

void abrirFicheros(char *nombre, char **dir){

	execvp(nombre, dir);
	return;
}
	

