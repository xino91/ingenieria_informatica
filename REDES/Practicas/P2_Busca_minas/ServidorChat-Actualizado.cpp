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
#define MSG_SIZE 250
#define MAX_CLIENTS 4


/*
 * El servidor ofrece el servicio de un chat
 */





int main ( )
{
  struct identificacion iden;
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE];
	socklen_t from_len;
    fd_set readfds, auxfds;
    int salida;
    int arrayClientes[MAX_CLIENTS];
    int numClientes = 0;
    //contadores
    int i,j,k, conectado;
	int recibidos;
    char identificador[MSG_SIZE];
    
    std::vector <struct identificacion> vector_espera;
    std::vector <struct jug_enlazados> vector_jugando;
    std::vector <struct identificacion> vector_ide;
    
    int on, ret;
	char numero[100];
	char letra[100];
	char coma[100];
	char nombre[100];
	char passwd[100];
	char mensaje[500];
    
    
	/* --------------------------------------------------
		Se abre el socket 
	---------------------------------------------------*/
	//SOCK_STREAM indica que es un socket TCP, socket orientado a conexion
	//Garantiza toda la fiabilidad requerida para que la trasmision este libre de errores
  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if (sd == -1)
	{
		perror("No se puede abrir el socket cliente\n");
    		exit (1);	
	}
    
    // Activaremos una propiedad del socket que permitir· que otros
    // sockets puedan reutilizar cualquier puerto al que nos enlacemos.
    // Esto permitir· en protocolos como el TCP, poder ejecutar un
    // mismo programa varias veces seguidas y enlazarlo siempre al
    // mismo puerto. De lo contrario habrÌa que esperar a que el puerto
    // quedase disponible (TIME_WAIT en el caso de TCP)
    on=1;
    ret = setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));



	sockname.sin_family = AF_INET;
	sockname.sin_port = htons(2000);
	sockname.sin_addr.s_addr =  INADDR_ANY;

	//La funcion bind para indicar al SO que queremos atender un determinado servicio
	//de forma que cuando llegue un mensaje por ese servicio nos avise.
	if (bind (sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1)
	{
		perror("Error en la operación bind");
		exit(1);
	}
	

   	/*---------------------------------------------------------------------
		Del las peticiones que vamos a aceptar sólo necesitamos el 
		tamaño de su estructura, el resto de información (familia, puerto, 
		ip), nos la proporcionará el método que recibe las peticiones.
   	----------------------------------------------------------------------*/
		from_len = sizeof (from);


		if(listen(sd,1) == -1){
			perror("Error en la operación de listen");
			exit(1);
		}
    
    //Inicializar los conjuntos fd_set
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);
    
   	
    //Capturamos la señal SIGINT (Ctrl+c)
    signal(SIGINT,manejador);
    
	/*-----------------------------------------------------------------------
		El servidor acepta una petición
	------------------------------------------------------------------------ */
		while(1){
		
            /***********************************************************/
            //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)
            /**************************************************************/
            
            auxfds = readfds;
            
            //FD_SETSIZE fija el tamaño de las estructuras fd_set. Por defecto es 64
            salida = select(FD_SETSIZE,&auxfds,NULL,NULL,NULL);
            
            if(salida > 0){
                
                
                for(i=0; i<FD_SETSIZE; i++){
                    
                    //Buscamos el socket por el que se ha establecido la comunicación
                    if(FD_ISSET(i, &auxfds)) {
                        
                        if( i == sd){
                            
                            if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
                                perror("Error aceptando peticiones");
                            }
                            else
                            {
                                //Comprobamos el numero de clientes y el maximo
                                if(numClientes < MAX_CLIENTS){
                                    arrayClientes[numClientes] = new_sd;
                                    numClientes++;
                                    FD_SET(new_sd,&readfds);
                                
                                    strcpy(buffer, "+OK, Usuario Conectado\n");
                                
                                    send(new_sd,buffer,strlen(buffer),0);
                              		iden.socket=new_sd;
                            		iden.estado=0;
                            		strcpy(iden.usuario,"");
                            		vector_ide.push_back(iden);
                               
                                    for(j=0; j<vector_ide.size();j++){
                                    
                                        printf("vector_id_conectado:%d\n",vector_ide[j].socket);
                                    }
                                }
                                else
                                {
                                    bzero(buffer,sizeof(buffer));
                                    strcpy(buffer,"Demasiados clientes conectados\n");
                                    send(new_sd,buffer,strlen(buffer),0);
                                    close(new_sd);
                                }
                                
                            }
                            
                            
                        }
                        else if (i == 0){
                            //Se ha introducido información de teclado
                            bzero(buffer, sizeof(buffer));
                            fgets(buffer, sizeof(buffer),stdin);
                            
                            //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                            if(strcmp(buffer,"SALIR\n") == 0){
                             
                                for (j = 0; j < numClientes; j++){
                                    send(arrayClientes[j], "Desconexion servidor\n", strlen("Desconexion servidor\n"),0);
                                    close(arrayClientes[j]);
                                    FD_CLR(arrayClientes[j],&readfds);
                                }
                                    close(sd);
                                    exit(-1);
                                
                                
                            }
                            //Mensajes que se quieran mandar a los clientes (implementar)
                            
                        } 
                        else{
                            bzero(buffer,sizeof(buffer));
                            
                            recibidos = recv(i,buffer,sizeof(buffer),0);
                            
                            	
                            	
                            if(recibidos > 0){
                                printf("buffer linea 210%s\n", buffer);
                                if(strcmp(buffer,"SALIR\n") == 0){
                                    
                                    salirCliente(i,&readfds,&numClientes,arrayClientes);
                                    
                                }
			
/*-----------------------------------------------------------------
						REGISTRO DEL USUARIO
-------------------------------------------------------------------*/
					else if((strncmp(buffer,"REGISTRO -u",11)==0) && ((strstr(buffer,"-p"))!=NULL)){				
						
						sscanf(buffer, "%*s %*s %s %*s %s",nombre,passwd);
						
						if(buscar_usuario(nombre)==0){
							
							escribirFichero(nombre,passwd);
							strcpy(mensaje,"+OK, Usuario registrado con exito\n");
							send(i,mensaje,strlen(mensaje),0);
							bzero(mensaje,sizeof(mensaje));
							
						}
						else{
							strcpy(mensaje,"-Err, el usuario ya existe\n");
							send(i,mensaje,strlen(mensaje),0);
							bzero(mensaje,sizeof(mensaje));
						}
						
						 //bzero(buffer,sizeof(buffer));	
					}
/*-----------------------------------------------------------------
						LOGIN USUARIO
-------------------------------------------------------------------*/
					else if(strncmp(buffer, "USUARIO",7)==0){
					
						
						
						sscanf(buffer, "%*s %s", nombre);
						for(int j=0; j<vector_ide.size();j++){
							
							if(vector_ide[j].socket==i){
								
						
						
								if(buscar_usuario(nombre)==0){
									strcpy(mensaje,"-Err. Usuario Incorrecto\n");
									send(i,mensaje,strlen(mensaje),0);
									bzero(mensaje,sizeof(mensaje));
								}
								else{
									strcpy(mensaje,"+OK. Usuario Correcto\n");
									send(i,mensaje,strlen(mensaje),0);
									bzero(mensaje,sizeof(mensaje));
									strcpy(vector_ide[j].usuario,nombre);
									vector_ide[j].estado=1;
								}
							}
						}
						bzero(buffer,sizeof(buffer));
					}
					
/*-----------------------------------------------------------------
						LOGIN PASSWORD
-------------------------------------------------------------------*/	
				else if(strncmp("PASSWORD",buffer,8)==0){
					sscanf(buffer, "%*s %s", passwd);
					for(int j=0;j<vector_ide.size();j++){
						if(vector_ide[j].socket==i && vector_ide[j].estado==1){
						
							if(buscar_todo(vector_ide[j].usuario,passwd)==0){
									strcpy(mensaje,"-Err. Error en la validacion\n");
									send(i,mensaje,strlen(mensaje),0);
									bzero(mensaje,sizeof(mensaje));
							}
							else{
									strcpy(mensaje,"+OK. Usuario validado\n");
									send(i,mensaje,strlen(mensaje),0);
									bzero(mensaje,sizeof(mensaje));	
									vector_ide[j].estado=2;
							}
						}
					}
					bzero(buffer,sizeof(buffer));
				}
					

				
					/***************************************************************************************************************/
					
					else if((strcmp(buffer, "INICIAR PARTIDA\n"))==0){
					
						
						
							for(int j=0; j<vector_ide.size(); j++){
								if(vector_ide[j].socket==i && vector_ide[j].estado==2){
									vector_espera.push_back(vector_ide[j]);
						
						if(vector_espera.size()%2==0){
							
							struct jug_enlazados j;
							strcpy(j.usuario1,vector_espera[0].usuario);
							strcpy(j.usuario2,vector_espera[1].usuario);
							j.jug1=vector_espera[0].socket;
							j.jug2=vector_espera[1].socket;
							
							
							strcpy(mensaje, "La Partida va a comenzar\n");
							send(j.jug1,mensaje,strlen(mensaje),0);
							send(j.jug2,mensaje,strlen(mensaje),0);
							bzero(mensaje,sizeof(mensaje));
							
							
							vector_espera.erase(vector_espera.begin());
							vector_espera.erase(vector_espera.begin());
							j.tablero=rellenar_tablero();
							j.tablero_inicial=rellenar_tablero_inicial();
							j.turno=j.jug1;
							j.contador1=0;
							j.contador2=0;
							vector_jugando.push_back(j);
							for(int h=0;h<10;h++){
								for(int x=0;x<10;x++){
									std::cout<<j.tablero[h][x]<<" ";
									}
								std::cout<<std::endl;
								}
								
							
						}						
						else{
							strcpy(mensaje, "En cola de espera....\n");
							send(vector_ide[j].socket,mensaje, strlen(mensaje),0);
							bzero(mensaje,sizeof(mensaje));
						}
						
							
							for(int i=0; i<vector_jugando.size(); i++){
								std::cout << "Vector jugando" << std::endl;
								std::cout << vector_jugando[i].jug1 << std::endl;
								std::cout << vector_jugando[i].jug2 << std::endl;
							}
						}
					}
					bzero(buffer,sizeof(buffer));
						
				}
/*********************************************************************************************************************************
				DESCUBRIR LETRA,NUMERO
*********************************************************************************************************************************/

				else if(strncmp("DESCUBRIR",buffer,9)==0){
						
						
						for(int j=0; j<vector_jugando.size(); j++){
							if(vector_jugando[j].turno==i){
							if(vector_jugando[j].jug1==i or vector_jugando[j].jug2==i ){
								int columna;
								sscanf(buffer,"%*s %c%c%c",letra,coma,numero);
						
								if((isdigit(numero[0])) and (!isdigit(letra[0]))){
								columna=comprobar(letra,numero);
									if(columna==10){
									strcpy(mensaje, "-Err. Error en la coordenada\n");
									send(i,mensaje, strlen(mensaje),0);
									bzero(mensaje,sizeof(mensaje));}
									else{
									int fila=atoi( numero);
									if(descubrir(&vector_jugando[j],columna,fila)==0){
										
										for(int f=0; f<vector_ide.size(); f++){
											if(vector_ide[f].socket==vector_jugando[j].jug1 or vector_ide[f].socket==vector_jugando[j].jug2){
												printf("socket_ide:%d\n",vector_ide[f].socket);
												
												vector_ide[f].estado=2;
											}
										}
									vector_jugando.erase(vector_jugando.begin()+j);
									
									}
									else{
									for(int p=0;p<10;p++){
										for(int x=0;x<10;x++){
										if(p==0 && x==0){sprintf(mensaje,"%s ",vector_jugando[j].tablero_inicial[p][x].c_str());
										}
										else{
										strcat(mensaje,vector_jugando[j].tablero_inicial[p][x].c_str());
										strcat(mensaje," ");
										}
										
										}
									strcat(mensaje,"\n");	
									
									}
									send(vector_jugando[j].jug1,mensaje,strlen(mensaje),0);
									send(vector_jugando[j].jug2,mensaje,strlen(mensaje),0);
									bzero(mensaje,sizeof(mensaje));
									if(vector_jugando[j].turno==vector_jugando[j].jug1){
										vector_jugando[j].turno=vector_jugando[j].jug2;
									}
									else{
										vector_jugando[j].turno=vector_jugando[j].jug1;
									}
									}	
							
								}
								}
								else{
								strcpy(mensaje, "-Err. Error en la coordenada\n");
								send(i,mensaje, strlen(mensaje),0);
								bzero(mensaje,sizeof(mensaje));
								}
							}
							}
							else{
							strcpy(mensaje,"-Err. Es turno del rival");
							send(i,mensaje, strlen(mensaje),0);
							bzero(mensaje,sizeof(mensaje));
							}
						}
						bzero(buffer,sizeof(buffer));
					
					}
/******************************************************************************************************************
//					PONER BANDERA LETRA,NUMERO
/******************************************************************************************************************/
					else if(strncmp("PONER-BANDERA",buffer,13)==0){
						
						
						for(int j=0; j<vector_jugando.size(); j++){
							if(vector_jugando[j].turno==i){
							if(vector_jugando[j].jug1==i or vector_jugando[j].jug2==i ){
								int columna;
								sscanf(buffer,"%*s %c%c%c",letra,coma,numero);
						
								if((isdigit(numero[0])) and (!isdigit(letra[0]))){
								columna=comprobar(letra,numero);
									if(columna==10){
									strcpy(mensaje, "-Err. Error en la coordenada\n");
									send(i,mensaje, strlen(mensaje),0);
									bzero(mensaje,sizeof(mensaje));}
									else{
									int fila=atoi( numero);	
									if(poner_bandera(&vector_jugando[j],columna,fila)==0){
									
									
										for(int f=0; f<vector_ide.size(); f++){
											if(vector_ide[f].socket==vector_jugando[j].jug1 or vector_ide[f].socket==vector_jugando[j].jug2){
												vector_ide[f].estado=2;
											}
										}
									vector_jugando.erase(vector_jugando.begin()+j);
									}
									else{
									for(int p=0;p<10;p++){
										for(int x=0;x<10;x++){
										if(p==0 && x==0){sprintf(mensaje,"%s ",vector_jugando[j].tablero_inicial[p][x].c_str());
										}
										else{
										strcat(mensaje,vector_jugando[j].tablero_inicial[p][x].c_str());
										strcat(mensaje," ");
										}
										
										}
									strcat(mensaje,"\n");	
									
									}
									send(vector_jugando[j].jug1,mensaje,strlen(mensaje),0);
									send(vector_jugando[j].jug2,mensaje,strlen(mensaje),0);
									bzero(mensaje,sizeof(mensaje));
									if(vector_jugando[j].turno==vector_jugando[j].jug1){
										vector_jugando[j].turno=vector_jugando[j].jug2;
									}
									else{
										vector_jugando[j].turno=vector_jugando[j].jug1;
									}
									}	
									}
								}
								else{
								strcpy(mensaje, "-Err. Error en la coordenada\n");
								send(i,mensaje, strlen(mensaje),0);
								bzero(mensaje,sizeof(mensaje));
								}
							}
							}
							else{
							strcpy(mensaje,"-Err. Es turno del rival");
							send(i,mensaje, strlen(mensaje),0);
							bzero(mensaje,sizeof(mensaje));
							}
						}
						bzero(buffer,sizeof(buffer));
					}
									









//***********************************************************************************************************************
                                else{
                                    
                                   
                                    bzero(buffer,sizeof(buffer));
                                                                  
                                    

                                    
                                }
                                                                
                                
                            }
                            //Si el cliente introdujo ctrl+c
                            if(recibidos== 0)
                            {
                                printf("El socket %d, ha introducido ctrl+c\n", i);
                                //Eliminar ese socket
                                salirCliente(i,&readfds,&numClientes,arrayClientes);
                            }
                        }
                    }
                }
            }
		}

	close(sd);
	return 0;
	
}







/********************************************************************/




		
		






