#ifndef JUEGO_HPP
#define JUEGO_HPP
struct jug_enlazados{
	int jug1;
	int jug2;
	int turno;
	std::vector< std::vector<std::string> > tablero;
	std::vector< std::vector<std::string> > tablero_inicial;
	int contador1;
	int contador2;
	char usuario1[100];
	char usuario2[100];
};

struct identificacion{
	int socket;
	int estado;
	char usuario[100];
};
int max(int a, int b);
int min(int a, int b);
std::vector<std::vector<std::string> > rellenar_tablero();
void manejador(int signum);
void salirCliente(int socket, fd_set * readfds, int * numClientes, int arrayClientes[]);
void escribirFichero(char *nombre, char *passwd);
int buscar_usuario(char *usuario);
int buscar_todo(char *nombre, char *passw);
std::vector< std::vector<std::string> > rellenar_tablero_inicial();
int comprobar(char letra[100], char numero[100]);
int descubrir(struct jug_enlazados* j,int columna,int fila);
int poner_bandera(struct jug_enlazados* j,int columna,int fila);
void gameover(struct jug_enlazados j);
void comprobar(struct jug_enlazados j);
#endif
