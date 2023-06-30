/* 3) Generar una serie de procesos cuyas relaciones familiares sigan el esquema siguiente:
Cuando nace un proceso, crea los hijos que le corresponda crear, duerme cinco segundos para descansar del esfuerzo procreador, espera por la muerte y va sumando los códigos de retorno de 
sus hijos. Al resultado de la suma le suma, a su vez, la última cifra de su PID. Al acabar, el
proceso devuelve un código de retorno igual a la suma previamente calculada. De este modo, el
padre de todos los procesos conocerá la suma de la últimas cifras del PID de todos sus 
descendientes, includio él mismo. Tomanado como ejemplo los PIDs de la figura anterior, la 
salida será al estilo siguiente:
	-SOy el primer hijo (pid=27) y mi suma es: 7
	-Soy el primer nieto (pid=40) y mi suma es: 0
	-Soy el bisnieto (pid=59) y mi suma es: 9
	-Soy el segundo nieto (pid=41) y mi suma es: 10
	-SOy el segundo hijo (pid=31) y mi suma es: 11
	-Soy el padre (pid=3) y mi suma es: 21*/
	
#include <sys/types.h>		//Para estructura pid_t
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>			//Para fork()


int main(void){

	pid_t pid;
	int i, chilpid, status, suma=0;
	
	pid=fork();
	
	if(pid==0){
		suma=suma + getpid()%10;
		printf("Soy el primer hijo (pid=%d) y mi suma es %d\n", getpid(), suma);
		exit(suma);
	}
	
		sleep(5);
		
		pid=fork();
		
		if(pid==0){	//Segundo hijo
		
		pid=fork();
			if(pid==0){
				suma=suma + getpid()%10;
				printf("Soy el primer nieto (pid=%d) y mi suma es %d\n", getpid(), suma);
				exit(suma);
			}
		sleep(5);  //sleep segundo hijo
		
		pid=fork();
			if(pid==0){
				pid=fork();
				
				if(pid==0){
					suma=suma + getpid()%10;
					printf("Soy el bisnieto (pid=%d) y mi suma es %d\n", getpid(), suma);
					exit(suma);
				}
				
				sleep(5);  //Sleep segundo nieto
				chilpid=wait(&status);
				suma=suma + getpid()%10 + WEXITSTATUS(status);
				printf("Soy el segundo nieto (pid=%d) y mi suma es %d\n", getpid(), suma);
				exit(suma);
		     }
		
		sleep(5);
		
		while(wait(&status)!=-1){
		
			suma=suma + WEXITSTATUS(status);
		}
		
		suma= suma + getpid()%10;
		printf("Soy el segundo hijo (pid=%d) y mi suma es %d\n", getpid(), suma);
		exit(suma);
		}
		
		sleep(5);
		
		while(wait(&status)!=-1){
		
			suma=suma + WEXITSTATUS(status);
		}
		
		suma=suma + getpid()%10;
		printf("Soy el padre (pid=%d) y mi suma es %d\n", getpid(), suma);
}
		
		
		
		
