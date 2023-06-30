#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <vector>
#include "juego.hpp"
#define TAM 10
void gameover(struct jug_enlazados j){
	printf("ENTRA GAME_OVER\n");
	char mensaje[100];
	if(j.turno==j.jug1){
		strcpy(mensaje,j.usuario1);
		strcat(mensaje," ha perdido\n");
		send(j.jug1,mensaje,strlen(mensaje),0);
		bzero(mensaje,sizeof(mensaje));
		strcpy(mensaje,j.usuario2);
		strcat(mensaje," ha ganado\n");
		send(j.jug2,mensaje,strlen(mensaje),0);
		bzero(mensaje,sizeof(mensaje));
	}
	else{
		strcpy(mensaje,j.usuario2);
		strcat(mensaje," ha perdido\n");
		send(j.jug2,mensaje,strlen(mensaje),0);
		bzero(mensaje,sizeof(mensaje));
		strcpy(mensaje,j.usuario1);
		strcat(mensaje," ha ganado\n");
		send(j.jug1,mensaje,strlen(mensaje),0);
		bzero(mensaje,sizeof(mensaje));
	}
	
	
}

int max(int a, int b){
	if(a<b){
		return b;
	}
	else{
		return a;
	}
}

int min(int a, int b){
	if(a<b){
		return a;
	}
	else{
	return b;
	}
}

std::vector<std::vector<std::string> > rellenar_tablero(){
	std::vector< std::vector<std::string> > matriz(10,std::vector<std::string>(10,"0"));
	std::string asterisco="*";
	
	srand(time(NULL));
	for (int mina=0; mina<20; mina++){
		int f,c;
		do{
			f=rand()%10;
			c=rand()%10;
			
		}while(matriz[f][c]==asterisco);
		matriz[f][c]='*';
		
		for(int f2=max(0,f-1);f2<min(TAM,f+2);f2++){
			for(int c2=max(0,c-1);c2<min(TAM,c+2);c2++){
				if(matriz[f2][c2]!=asterisco){
					
					int numero=atoi(matriz[f2][c2].c_str());
					numero++;
					matriz[f2][c2]=std::to_string(numero);
					
				}
			}
		}
	
	}
return matriz;
}

int buscar_usuario(char *usuario){

	char nombre1[100], passwd1[100];
	FILE *f;
	
	if((f=fopen("Lista_usuarios.txt","r"))==NULL){
		
		return 0;
	}
	
	else{
		while ((fscanf(f, "%s %s", nombre1, passwd1))!=EOF){
		
			if(strcmp(usuario,nombre1)==0){
				fclose(f);
				return 1;
			}
		}
	}
	fclose(f);
	return 0;
}

void salirCliente(int socket, fd_set * readfds, int * numClientes, int arrayClientes[]){
  
    char buffer[250];
    int j;
    
    close(socket);
    FD_CLR(socket,readfds);
    
    //Re-estructurar el array de clientes
    for (j = 0; j < (*numClientes) - 1; j++)
        if (arrayClientes[j] == socket)
            break;
    for (; j < (*numClientes) - 1; j++)
        (arrayClientes[j] = arrayClientes[j+1]);
    
    (*numClientes)--;
    
    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"Desconexión del cliente: %d\n",socket);
    
    for(j=0; j<(*numClientes); j++)
        if(arrayClientes[j] != socket)
            send(arrayClientes[j],buffer,strlen(buffer),0);
            bzero(buffer,sizeof(buffer));


}

void manejador (int signum){
    printf("\nSe ha recibido la señal sigint\n");
    signal(SIGINT,manejador);
    
    //Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor
}

void escribirFichero(char *nombre, char *passwd){

	FILE *f;
	if((f=fopen("Lista_usuarios.txt","a+"))==NULL){
		printf("ERROR AL ABRIR EL FICHERO\n");
		exit(-1);
	}
	else{
		
		fprintf(f,"%s %s\n", nombre,passwd);
		
	}
	fclose(f);
}

int buscar_todo(char *nombre, char *passw){

	char nombre1[100], passwd1[100];
	FILE *f;
	
	if((f=fopen("Lista_usuarios.txt","r"))==NULL){
		printf("Error al abrir el fichero\n");
		exit(-1);
	}
	
	else{
		while ((fscanf(f, "%s %s", nombre1, passwd1))!=EOF){
			
			if((strcmp(nombre,nombre1)==0) && (strcmp(passw,passwd1))==0){
					
					fclose(f);
					return 1;
				
				
			}
		}
	}
	fclose(f);
	return 0;
}
std::vector<std::vector<std::string> > rellenar_tablero_inicial(){


	std::vector< std::vector<std::string> >matriz(10,std::vector<std::string>(10,"-"));
	return matriz;
}
int comprobar(char letra[100], char numero[100]){
		int coordenada=10;
		if(strcmp(letra,"A") or strcmp(letra,"B") or strcmp(letra,"C") or strcmp(letra,"D") or strcmp(letra,"E") or strcmp(letra,"F") or strcmp(letra,"G") or strcmp(letra,"H") or strcmp(letra,"I") or strcmp(letra,"J")){
			switch (letra[0]){
				case 'A':
					coordenada=0;
					break;
				case 'B':
					coordenada=1;
					break;
				case 'C':
					coordenada=2;
					break;
				case 'D':
					coordenada=3;
					break;
				case 'E':
					coordenada=4;
					break;
				case 'F':
					coordenada=5;
					break;
				case 'G':
					coordenada=6;
					break;
				case 'H':
					coordenada=7;
					break;
				case 'I':
					coordenada=8;
					break;
				case 'J':
					coordenada=9;
					break;
				
				}
			}
			
		return coordenada;
	}
					
int descubrir(struct jug_enlazados* j,int columna,int fila){
			
		if(j->tablero[fila][columna]=="*"){
			gameover(*j);
			return 0;
		
		}
		else{		
			if(j->tablero_inicial[fila][columna]=="-"){
				j->tablero_inicial[fila][columna]=j->tablero[fila][columna];
				if(j->tablero[fila][columna]=="0"){
				for(int f2=max(0,fila-1);f2<min(TAM,fila+2);f2++){
					for(int c2=max(0,columna-1);c2<min(TAM,columna+2);c2++){
						descubrir(j,c2,f2);
					}
				}
				}
			}
		}
	return 1;
	}
int poner_bandera(struct jug_enlazados* j,int columna,int fila){

	if(j->turno==j->jug1){
		if(j->tablero_inicial[fila][columna]=="-"){
			j->tablero_inicial[fila][columna]="A";
		
		}
			else{
			j->tablero_inicial[fila][columna]="AB";
			}
		j->contador1+=1;
		}
	
	else{
		if(j->tablero_inicial[fila][columna]=="-"){
			j->tablero_inicial[fila][columna]="B";
		}
			else{
			j->tablero_inicial[fila][columna]="AB";
			}
		j->contador2+=1;
		}
	
	if(j->contador1==10 or j->contador2==10){
		comprobar(*j);
		return 0;
		
	}
	return 1;
}
void comprobar(struct jug_enlazados j){
	int contador1_1=0;
	int contador2_2=0;
	
	char mensaje[100];
	if(j.contador1==10){
		for(int i=0;i<10;i++){
			for(int x=0;x<10;x++){
				if(j.tablero_inicial[i][x]=="A" or j.tablero_inicial[i][x]=="AB"){
					if(j.tablero[i][x]!="*"){
						gameover(j);
						
					}
					else{contador1_1+=1;}
				}
			}
		}
		if(contador1_1=10){
		strcpy(mensaje,j.usuario2);
		strcat(mensaje," ha perdido\n");
		send(j.jug2,mensaje,strlen(mensaje),0);
		bzero(mensaje,sizeof(mensaje));
		strcpy(mensaje,j.usuario1);
		strcat(mensaje," ha ganado\n");
		send(j.jug1,mensaje,strlen(mensaje),0);
		bzero(mensaje,sizeof(mensaje));
		}
			
	}
	if(j.contador2==10){
		for(int i=0;i<10;i++){
			for(int x=0;x<10;x++){
				if(j.tablero_inicial[i][x]=="B" or j.tablero_inicial[i][x]=="AB"){
					if(j.tablero[i][x]!="*"){
						gameover(j);
						
					}
					else{contador2_2+=1;}
				}
			}
		}
		if(contador2_2=10){
		strcpy(mensaje,j.usuario1);
		strcat(mensaje," ha perdido\n");
		send(j.jug1,mensaje,strlen(mensaje),0);
		bzero(mensaje,sizeof(mensaje));
		strcpy(mensaje,j.usuario2);
		strcat(mensaje," ha ganado\n");
		send(j.jug2,mensaje,strlen(mensaje),0);
		bzero(mensaje,sizeof(mensaje));
		}
			
	}


}
						
					
