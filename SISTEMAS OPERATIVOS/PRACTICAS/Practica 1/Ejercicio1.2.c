/* 1) PROCESOS. Cree dos programas en C (pida el número de procesos totales N por la entrada estándar del sistema.
A) Cree un abanico de procesos como el que se refleja en la figura.
B) Lo mismo pero recrando lo que representa la segunda figura.
Cada proceso hiujo mostrará por salida estándar un mensaje incluyendo su PID y el de su padre, y finalizará su ejecución*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(void){

	pid_t pid;
	int i, n, chilpid, status;
	
	printf("Número de procesos\n");
	scanf("%d", &n);
	
	printf("Proceso padre absoluto %d\n", getpid());
	
	
	for(i=0; i<n; i++){
		pid=fork();
		
		if(pid==0){
			printf("Proceso hijo numero %d: %d;  padre: %d\n", i, getpid(), getppid());
		}
		else{
			chilpid=wait(&status);
				if(chilpid>0){
					if(WIFEXITED(status)){
						printf("Chil %d exited, status= %d\n", chilpid, WEXITSTATUS(status));
					}
					else if(WIFSIGNALED(status)){
						printf("Child %d Killed (signal %d)\n", chilpid, WTERMSIG(status));
					}
					else if(WIFSTOPPED(status)){
						printf("Child %d stopped (signal %d)\n", chilpid, WSTOPSIG(status));
					}
				}
		exit(EXIT_SUCCESS);
		}
	}
}		
