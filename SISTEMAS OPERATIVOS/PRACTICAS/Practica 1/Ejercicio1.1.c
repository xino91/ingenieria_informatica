/* 1) PROCESOS. Cree dos programas en C (pida el número de procesos totales N por la entrada estándar del sistema.
A) Cree un abanico de procesos como el que se refleja en la figura.
B) Lo mismo pero recrando lo que representa la segunda figura.
Cada proceso hiujo mostrará por salida estándar un mensaje incluyendo su PID y el de su padre, y finalizará su ejecución con código de salida 0 (recuerde que esto es simplemente hacer un exit(0) o return(0)).*/

#include <sys/types.h>  //Para estructira pid_t
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   //Para fork()
#include <errno.h>


int main(void){
	pid_t pid;
	
	int i, x, chilpid, status;
	
	printf("Introduzca el número de procesos\n");
	scanf("%d", &x);
	
	printf("Proceso padre: %d\n", getpid());
	
	for(i=0; i<x; i++){
		pid=fork();
		if(pid==0){
			printf("Proceso hijo %d; padre= %d\n", getpid(), getppid());
			exit(EXIT_SUCCESS);
		}
	}
	
	for(i=0; i<x; i++){
		chilpid=wait(&status);
			if(chilpid>0){
				if(WIFEXITED(status)){
					printf("Child %d exited, status= %d\n", chilpid, WEXITSTATUS(status));
				}
				else if (WIFSIGNALED(status)){
					printf("Child %d Killed (signal %d)\n", chilpid, WTERMSIG(status));
				}
				else if (WIFSTOPPED(status)){
					printf("child %d stopped (signal %d)\n", chilpid, WSTOPSIG(status));
				}
			}
	}
}
