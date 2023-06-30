/*Ejercicio1 - Implemente un programa que obtenga informacion sobre usuarios del sistema
(todos los campos de la estructura passwd) e informacion sobre los grupos del sistema
(GID y nombre del grupo mediante la estructura group) según opciones recibidas por linea de argumentos
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>	//Estructura de passwd
#include <grp.h>	//Estructura de grupo
#include <unistd.h>
#include <getopt.h>
#include <string.h>


int main(int argc, char *argv[]){
	int c;
	char *login;
	char *g;
	struct passwd *pw;
	struct group *gr;
	char *value;
	int uid;
	int gid;
	FILE *f=NULL;
	char nombre[100];
	int GID=0;
	char *usuario;
	
	int opcion=0;
	
	/* Estructura a utilizar por getoptlong */
	static struct option long_options[] =
	{
		/* Opciones que no van a actuar sobre un flag */
		/* "opcion", recibe o no un argumento, 0,
		   identificador de la opción */
		{"username",  required_argument, 0, 'u'},
		{"userid",    required_argument, 0, 'i'},
		{"groupname", required_argument, 0, 'g'},
		{"groupuid",  required_argument, 0, 'd'},
		{"allgroups", no_argument, 	   0, 's'},
		{"allinfo",   required_argument, 0, 'a'},
		{"bactive",   no_argument, 	   0, 'b'},
		{"help",      no_argument, 	   0, 'h'},
		/* Necesario para indicar el final de las opciones */
		{0, 0, 0, 0}
	};
	
	/* getopt_long guardará el índice de la opción en esta variable. */
	int option_index = 0;
	
	opterr = 1;
	while((c = getopt_long( argc, argv, "u:i:g:d:sa:bh", long_options, &option_index)) != -1){
		
		if( c == -1){
			break;
		}
		
			switch(c){
				/*case 0:
					printf("HOLA0\n");
				break;
				
				case ':':
					printf("HOLA\n");
				break;
				
				case '?':
					printf("HOLA?\n");
				break;*/
		///////////////////////////////////////////////////////////////////////////////////////////////////		
				case 'u': 
				//Informacion struct passwd con nombre usuario
				opcion=1;
					value = optarg;
					if((pw = getpwnam(value)) == NULL){
						fprintf(stderr,"Obtener información del usuario fallida.\n");
						exit(1);
					}
				
					printf("Nombre: %s\n", pw->pw_gecos);
					printf("Login: %s\n", pw->pw_name);
					printf("Password: %s\n", pw->pw_passwd);
					printf("UID: %d\n", pw->pw_uid);
					printf("Home: %s\n", pw->pw_dir);
					printf("Número de grupo principal: %d\n\n", pw->pw_gid);
				break;
		///////////////////////////////////////////////////////////////////////////////////////////////////	
				case 'i':
				//Informacion struct passwd con identificador usuario = UID
				opcion=1;
					uid = atoi(optarg);
					if((pw = getpwuid(uid)) == NULL){
						fprintf(stderr,"Obtener información del usuario fallida.\n");
						exit(1);
					}
				
					printf("Nombre: %s\n", pw->pw_gecos);
					printf("Login: %s\n", pw->pw_name);
					printf("Password: %s\n", pw->pw_passwd);
					printf("UID: %d\n", pw->pw_uid);
					printf("Home: %s\n", pw->pw_dir);
					printf("Número de grupo principal: %d\n\n", pw->pw_gid);
				break;
		////////////////////////////////////////////////////////////////////////////////////////////////////	
				case 'g':
				//Informacion struct group con nombre de grupo
				opcion=1;
					g = optarg;
					if((gr = getgrnam(g)) == NULL){
						fprintf(stderr,"Obtener información del grupo fallida.\n");
						exit(1);
					}
				
					printf("Nombre del grupo principal: %s\n", gr->gr_name);
					printf("Password: %s\n", gr->gr_passwd);
					printf("GID: %d\n" , gr->gr_gid);
				break;
		////////////////////////////////////////////////////////////////////////////////////////////////////
				case 'd':
				//Información struct group con identificar de grupo = GID
				opcion=1;
					gid = atoi(optarg);
					if((gr = getgrgid(gid)) == NULL){
						fprintf(stderr,"Obtener información del grupo fallida.\n");
						exit(1);
					}
				
					printf("Nombre del grupo principal: %s\n", gr->gr_name);
					printf("Password: %s\n", gr->gr_passwd);
					printf("GID: %d\n" , gr->gr_gid);
				break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////
				case 's':
				opcion = 1;
				//Muestra todos los grupos de sistema, junto con su identificador
					if((f=fopen("group","r"))==NULL){
          				printf("Error al abrir el fichero\n");
          				exit(-1);
     				}
     
    				  	while(fscanf(f, "%s  %d", nombre,&GID)!=EOF){
          				printf("Nombre Grupo: %s\n", nombre);
          				//printf("Identificador: %d\n", GID);
     				}
     				if(fclose(f)!=0){
         					printf("Error al cerrar el fichero\n");    //fclose devuelve un 0 si todo va bien y EOF si hay error
         					return 0;
     				}
     			
					
				break;
				
				case 'a':
				//Muestra struct passwd y struct group previo paso de un nombre usuario 
				opcion = 1;
					value = optarg;
					if((pw = getpwnam(value)) == NULL){
						fprintf(stderr,"Obtener información del usuario fallida.\n");
						exit(1);
					}
					printf("----INFORMACIÓN PASSWD----\n");
					printf("Nombre: %s\n", pw->pw_gecos);
					printf("Login: %s\n", pw->pw_name);
					printf("Password: %s\n", pw->pw_passwd);
					printf("UID: %d\n", pw->pw_uid);
					printf("Home: %s\n", pw->pw_dir);
					
					if((gr = getgrgid(pw->pw_gid)) == NULL){
						fprintf(stderr,"Obtener información del grupo fallida.\n");
						exit(1);
					}
				
					printf("----INFORMACIÓN GROUP----\n");
					printf("Nombre del grupo principal: %s\n", gr->gr_name);
					printf("Password: %s\n", gr->gr_passwd);
					printf("GID: %d\n\n" , gr->gr_gid);
				break;
				
				case 'b':
				//Deberá buscar e imprimir información del grupo del usuario actual
				//Recogemos el nombre usuario actual
				opcion=1;
					if((usuario = getenv("USER"))==NULL){
						fprintf(stderr,"Obtener USER fallido.\n");
						exit(1);
					}
					//Recogemos el grupo del usuario 
					else{
						if((pw = getpwnam(usuario))==NULL){
							fprintf(stderr,"Obtener información del usuario fallida.\n");
						exit(1);
						}
						else{
							if((gr = getgrgid(pw->pw_gid))==NULL){
								fprintf(stderr,"Obtener información del grupo fallida.\n");
								exit(1);
							}
							//Mostramos la información de grupo del usuario actual
							printf("\n----INFORMACIÓN GROUP----\n");
							printf("Nombre del grupo principal: %s\n", gr->gr_name);
							printf("GID: %d\n\n" , gr->gr_gid);
						}
					}
				break;
				
				case 'h':
				//Mostrará información sobre cada uno de los usos del programa
					printf("\n---INFORMACION SOBRE EJECUCION DEL PROGRAMA\n");
					printf("Opcion -u/--username: Recibe un parámetro obligatorio, que será el nombre de un usuario, del cual mostrará información de su estructura passwd\n");
					printf("Opcion -i/--useruid: Recibe un parámetro obligatroio, que será el identificador de un usuario, del cual mostrará información de su estructura group\n");
					printf("Opcion -g/--groupname: Recibe un parámetro obligatorio, que será el nombre de un grupo del sistema, mostrará información correspondiente a su estructura group\n");
					printf("Opcion -d/--groupuid: Recibe un parámetro obligatorio, que será el identificador de un grupo, del cual mostrará información correspondiente a su estructura group\n");
					printf("Opcion -s/--allgroups: No recibe parámetro, está opción mostrará todos los grupos de sistema, junto con su identificador\n");
					printf("Opcion -a/--allinfo: Recibe un parámetro obligatorio, que será el nombre de un usuario del sistema, mostrará información correspondiente a su estructura passwd y de group\n");
					printf("Opcion -b/--bactive: No recibe parámetro, imprimirá la información del grupo del usuario actual\n");
					printf("\nSi se invoca al programa sin ninguna opción mostrará información del usuario actual y del grupo principal, en Español o en Inglés\n");
					printf("Opcion -h/--h: Mostrará información sobre el uso del programa\n\n");
					
				break;
				
				
				
			}
	}//SI NO ENTRAMOS EN NINGUNA OPCION IMPRIMOS ESTO
	if(opcion == 0){
	
		char *idioma = getenv("LANG");
	 	//COMPROBAMOS IDIOMA 
    		if (strstr(idioma,"ES"))
    		{ //Mostramos en español
        		if((usuario = getenv("USER"))==NULL){
				fprintf(stderr,"Obtener USER fallido.\n");
				exit(1);
			}
			//Recogemos el grupo del usuario 
			else{
				if((pw = getpwnam(usuario))==NULL){
					fprintf(stderr,"Obtener información del usuario fallida.\n");
					exit(1);
				}
				else{
					printf("----INFORMACIÓN PASSWD----\n");
					printf("Nombre: %s\n", pw->pw_gecos);
					printf("Login: %s\n", pw->pw_name);
					printf("Password: %s\n", pw->pw_passwd);
					printf("UID: %d\n", pw->pw_uid);
					printf("Home: %s\n", pw->pw_dir);
					printf("Número de grupo principal: %d\n\n", pw->pw_gid);
				}
			}
    		}
    		else//Mostramos en Ingles
    		{
        		if((usuario = getenv("USER"))==NULL){
				fprintf(stderr,"Get of user name failed.\n");
				exit(1);
			}
			//Recogemos el grupo del usuario 
			else{
				if((pw = getpwnam(usuario))==NULL){
					fprintf(stderr,"Get of user information failed.\n");
					exit(1);
				}
				else{
					printf("----INFORMACIÓN PASSWD----\n");
					printf("Name: %s\n", pw->pw_gecos);
					printf("Login: %s\n", pw->pw_name);
					printf("Password: %s\n", pw->pw_passwd);
					printf("UID: %d\n", pw->pw_uid);
					printf("Home: %s\n", pw->pw_dir);
					printf("Main group number: %d\n\n", pw->pw_gid);
				}
			}
   		}
    
		
	}
}
				
				
				
				
				
				
				
				
				
				
				
				
