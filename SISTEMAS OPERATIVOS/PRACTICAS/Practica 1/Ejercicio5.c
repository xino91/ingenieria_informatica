/* 5) Cuando un proceso padre crea un hijo mediante fork(), los descriptores de ficheros que 
haya en el padre también los "hereda" el hijo. Implemente un programa en el que el padre y el
hijo (o si lo prefiere un padre y dos hijos) hagan varias escrituras en un fichero de texto, 
intercalando un sleep(1) entre escritura y escritura. Puede hacer que por ejemplo el padre 
escriba un tipo de caracteres(+++++) y el hijo (hijos) otros distintos(------). Al termino de 
la escritura (el padre debe esperar al hijo) cierre el fichero y visualícelo para ver si se ha 
creado correctamente. Use la linea de argumentos para proporcionar el nombre de fichero a su 
programa.*/
#include <sys/types.h>	//Para la estructura pid_t
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){

	pid_t pid;
	int i, flag, j, num, valor;
	
	FILE *fich;
	fich= fopen("Sig.txt", "w");
	num=atoi(argv[1]);
	
	if(argc>1){
	
		for(i=0; i<2; i++){
		
			pid=fork();
			
			if(pid==-1){
			
				perror("fork error");
				printf("Valor de errno= %d, definido como %s\n", errno, strerror(errno));
				exit(EXIT_FAILURE);
			}
			
			if(pid==0){
				if(i==0){
					for(j=0; j<num; j++){
						fprintf(fich, "+++++\n");
						sleep(1);
					}
				}
				if(i==1){
					for(j=0; j<num; j++){
						fprintf(fich, "------\n");
						sleep(1);
					}
				}
			}
			
			
		}while((flag= wait(&valor))>0){
			
			if(WIFEXITED(valor)){
				printf("Child exited, status= %d\n", WEXITSTATUS(valor));
			}
			else if(WIFSIGNALED(valor)){
				printf("Chil Killed (signal %d)\n", WTERMSIG(valor));
			}
			else if(WIFSTOPPED(valor)){
				printf("Chil stopped (signal %d)\n", WSTOPSIG(valor));
			}
		}
		
		if(flag==-1 && errno==ECHILD){
			printf("No hay más hijos que esperar\n");
		}
		else{
			perror("Error en la invocación de wait o la llamada ha sido interrumpida por una señal.");
			printf("Valor de errno=%d, definido como %s\n", errno, strerror(errno));
			exit(EXIT_FAILURE);
		}
		system("cat Sig.txt");
		
	}
	
	else{
		printf("ERROR. Vuelva a ejecutar el programa. Numero de argumentos erroneo.\n\n");
		printf("Escriba dos argumentos\n");
	}
}
			
			

