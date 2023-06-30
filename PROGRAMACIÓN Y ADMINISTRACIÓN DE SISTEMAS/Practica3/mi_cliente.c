#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <mqueue.h>
#include <time.h>

int main(){

	// Cola del servidor
	mqd_t mq_server1;
	// Buffer para intercambiar mensajes
	char buffer[1024];
	
	// Abrir la cola del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen
	mq_server1 = mq_open("/nuevacola", O_WRONLY);
	if(mq_server1 == (mqd_t)-1 )
	{
     	perror("Error al abrir la cola del servidor");
     	exit(-1);
	}
	
	printf("Enviando mensajes al servidor (escribir \"exit\" para salir)\n");
	do{
		printf("> ");
		fflush(stdout);				//Limpia el buffer de salida
		memset(buffer, 0, 1024);			//Poner a 0 el buffer
		fgets(buffer, 1024, stdin);		//lee por teclado
		buffer[strlen(buffer)-1] = '\0'; 	// Descartar el salto de línea

		// Enviar y comprobar si el mensaje se manda
		if(mq_send(mq_server1, buffer, 1024, 0) != 0)
		{
			perror("Error al enviar el mensaje");
			exit(-1);
		}
	// Iterar hasta escribir el código de salida
	}while (strncmp(buffer, "exit", strlen("exit")));

	// Cerrar la cola del servidor
	if(mq_close(mq_server1) == (mqd_t)-1)
	{
		perror("Error al cerrar la cola del servidor");
		exit(-1);
	}
	return 0;
}
