#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>


int main(){
	
	//Cola de servidor 
	mqd_t mq_server;
	//atributos de la cola
	struct mq_attr attr;
	//buffer para intercambiar mensajes
	char buffer[1025];
	//Flag que indica cuando hay que parar
	int must_stop = 0;
	//Inicializa los atributos de la cola
	attr.mq_maxmsg = 10;	//Máximos número de mensajes
	attr.mq_msgsize = 1024;	//Máximo tamaño de un mensaje
	
	//Crea la cola de mensajes del servidor, la cola "/nuevacola"
	mq_server = mq_open("/nuevacola", O_CREAT | O_RDONLY, 0644, &attr);
	if(mq_server == -1){
		perror("Error al abrir la cola del servidor\n");
		exit(-1);
	}
	
	do{
		//Numero de bytes leidos
		ssize_t bytes_read;
		//Recibir el mensaje
		bytes_read = mq_receive(mq_server , buffer, 1024, NULL);
		//Comprobar que la recepcion de mensajes es correcta
		if(bytes_read < 0){
			perror("Error al recibir el mensaje");
			exit(-1);
		}
		//Cerrar la cadena
		buffer[bytes_read] = '\0';
	
		//Comprobar el fin del bucle
		if (strncmp(buffer, "exit", strlen("exit"))==0)
			must_stop = 1;
		else{
			printf("Recibido el mensaje: %s\n", buffer);	
		}
	} while (must_stop == 0); //Itera hasta que llegue el mensaje de salida
	
	//Cierra la cola del servidor
	if(mq_close(mq_server) == -1){
		perror("Error al cerrar la cola del servidor\n");
		exit(-1);
	}
	
	// Eliminar la cola del servidor
	if(mq_unlink("/nuevacola") == (mqd_t)-1)
	{
		perror("Error al eliminar la cola del servidor");
		exit(-1);
	}

	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
