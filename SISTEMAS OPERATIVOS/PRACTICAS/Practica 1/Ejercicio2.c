/* Se dice que un proceso está en el estado Zombie en Unix cuando, habiendo concluido su 
ejecución, está a la espera de que su padre efectúe un wait() para recoger su código de retorno
Para ver un proceso Zombie, implemente un programa que tenga un hijo que acabe inmediatamente
(por ejemplo que imprima su ID y termine). Deje dormir al padre mediante la función sleep()
durante 20 segundos y que luego acabe usando por ejemplo exit(EXIT_SUCCESS).
Ejecute el programa en segundo plano (usando &) y monitorice varias veces en otra terminal los
procesos con la orden se la shell "ps-a". Verá que en uno de ellos se indica que el proceso
hijo está Zombie o perdido mientras sigue ejecutándose el programa padre en la función sleep().
Cuando muere el padre, sin haber tomado el código de retorno del hijo mediante wait(), el hijo
es automaticamente heredado por el proceso init,  que se encarga de "exorcizarlo" y eliminarlo 
de sistema*/

#include <sys/types.h>  //Para la estructura pid_t
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>		//Para fork()
#include <errno.h>

int main(void){

	pid_t pid;
	int i, chilpid, status;
	
	pid=fork();
	
	if(pid==0){
		printf("Proceso hijo %d; padre= %d\n", getpid(), getppid());
		exit(EXIT_SUCCESS);
	}
	else{
		printf("Proceso %d\n", getpid());
		sleep(20);
		
		chilpid=wait(&status);
			if(chilpid>0){
				if(WIFEXITED(status)){
					printf("Child %d exited, status= %d\n", chilpid, WEXITSTATUS(status));
				}
				else if(WIFSIGNALED(status)){
					printf("Chil %d Killed (signal %d)\n", chilpid, WTERMSIG(status));
				}
				else if(WIFSTOPPED(status)){
					printf("Chil %d stopped (signal %d)\n", chilpid, WSTOPSIG(status));
				}
			}
	exit(EXIT_SUCCESS);
	}
}	
