#include <stdio.h>
#include <stdlib.h> //exit, rand, srand
#include <unistd.h> //pipe, close, fork, usleep, read, write, getpid, getppid
#include <sys/wait.h> //wait
#include <errno.h> //Control de errores
#include <string.h> //strerror
#include <time.h> //Para la semilla del generador de aleatorios

int main(){
	pid_t flag, hijo;
	int status, numero;
	int fildes1[2];
	int fildes2[2];
	const int BSIZE = 100;
	char buf[BSIZE];
	ssize_t nbytes, nbytes2;
	char *es;
	
	if((status = pipe(fildes1)) == -1 ){
		perror("Error en pipe1\n");
		exit(EXIT_FAILURE);
	}
	if((status = pipe(fildes2)) == -1 ){
		perror("Error en pipe2\n");
		exit(EXIT_FAILURE);
	}
	
	hijo = fork();
	switch(hijo){
		
		case -1:
			perror("Error en fork caso 0\n");
			exit(EXIT_FAILURE);
		
		case 0:
		printf("[HIJO]: Mi PID es: %d, y el de mi padre es: %d\n", getpid(), getppid());
			//No necesita escribir en tuberia1
			if(close(fildes1[1]) == -1){
				perror("Error en close hijo\n");
				exit(EXIT_FAILURE);
			}
			//close(fildes2[0]); //No necesito leer en tuberia2
			
			//Leemos la tubería1
			if((nbytes = read(fildes1[0], &numero, sizeof(int))) == -1){
				perror("Error en read\n");
				exit(EXIT_FAILURE);
			}
			else if(nbytes == 0){ //read() no ha leido nada -> Se ha llegado a EOF -> El padre ha cerrado la tuberia
				printf("[HIJO]: Detecto que mi padre ha cerrado la tuberia1...\n"); 
			}
			else{
				printf("[HIJO]: Leyendo el numero %d por la tuberia1\n", numero);
				if(numero % 2 == 0){
					es = "PAR";
				}
				else{
					es = "IMPAR";
				}
				//Escribimos por la tuberia2
				if(write(fildes2[1], es, sizeof(char*)) == -1 ){
					perror("Error en write\n");
					exit(EXIT_FAILURE);
				}
				// El padre verá FEOF (por hacer close)
				if (close(fildes2[1]) == -1) {
					perror("Error en close"); 
					exit(EXIT_FAILURE);
				}
				else{
					printf("[HIJO]: enviando %s por la tuberia2\n", es);
				}
				
			}
			exit(EXIT_SUCCESS);
		
		
		default:
		printf("[PADRE]: Mi PID es: %d, y el de mi hijo es: %d\n", getpid(), hijo);
		sleep(1);
			printf("Introduzca un número entero\n");
			scanf("%d", &numero);
			
			//No necesita leer en tuberia1
			if(close(fildes1[0]) == -1){
				perror("Error en close\n");
				exit(EXIT_FAILURE);
			}
		//Escribimos en la tuberia1
			if(write(fildes1[1], &numero , sizeof(int)) == -1){
				perror("Error en write\n");
				exit(EXIT_FAILURE);
			}
			
			// El hijo verá FEOF (por hacer close)
			if (close(fildes1[1]) == -1) 
			{
				perror("Error en close"); 
				exit(EXIT_FAILURE);
			}
			else{
				printf("[PADRE]: enviando el numero %d por la tuberia1\n", numero);
			}
			
			//No necesita escribir en la tuberia2
			close(fildes2[1]);
			
		
			
			while ( (flag=wait(&status)) > 0 ){
			
			//Leemos la tubería2
			if((nbytes2 = read(fildes2[0], buf , sizeof(char*))) == -1){
				perror("Error en read\n");
				exit(EXIT_FAILURE);
			}
			else if(nbytes2 == 0){ //read() no ha leido nada -> Se ha llegado a EOF -> El padre ha cerrado la tuberia
				printf("[PADRE]: No leyo nada -> Se ha llegado a EOF...\n"); 
			}
			else{
				printf("[PADRE]: Leyendo %s de la tuberia2\n", buf);
			}
			close(fildes2[0]);
			if (WIFEXITED(status)) 
			{
				printf("[PADRE]: Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
			} else if (WIFSIGNALED(status)) {  //Para seniales como las de finalizar o matar
				printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
			} else if (WIFSTOPPED(status)) { //Para cuando se para un proceso. Al usar wait() en vez de waitpid() no nos sirve.
				printf("Proceso Padre, Hijo con PID %ld parado al recibir la señal %d\n", (long int)flag,WSTOPSIG(status));
			} else if (WIFCONTINUED(status)){ //Para cuando se reanuda un proceso parado. Al usar wait() en vez de waitpid() no nos sirve.
				printf("Proceso Padre, Hijo con PID %ld reanudado\n",(long int) flag);		  
			}	
		}
		if (flag==(pid_t)-1 && errno==ECHILD)
		{
			printf("[PADRE]: valor de errno = %d, definido como %s, no hay más hijos que esperar!\n", errno, strerror(errno));
		}
		else
		{
			printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal.\n");
			exit(EXIT_FAILURE);
		}
		
		exit(EXIT_SUCCESS);	
	}//switch		 
	
}
