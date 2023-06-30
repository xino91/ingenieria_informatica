/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares para el programa principal de la práctica 4
  \author Antonio Ariza García
  \date   21-05-2018
*/


#include <iostream>
#include <fstream>
#include <string>
#include "Grafo.hpp"
#include "funcionesAuxiliares.hpp"


int ed::menu()
{
	int opcion;
	int posicion;

	// Se muestran las opciones del menú
	posicion=2;

	// Se borra la pantalla
	std::cout << CLEAR_SCREEN;

	PLACE(1,10);
	std::cout << BIBLUE;
	std::cout << "Programa principial | Opciones del menú";
	std::cout << RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[1] Cargar Vertices desde el fichero ";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[2] Mostrar Grafo por pantalla ";

	PLACE(posicion++,10);
	std::cout << "[3] Árbol abarcador de coste mínimo ";

	//////////////////////////////////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIRED << "[0] Salir";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIGREEN;
	std::cout << "Opción: ";
	std::cout << RESET;

	// Se lee el número de opción
	std::cin >> opcion;

    // Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();

	return opcion;
}




bool ed::cargarGrafoDeFichero(ed::Grafo & grafo){
	
	std::string nombreFichero;
	
	std::cout << BIBLUE << "Introduzca el nombre del fichero" << RESET << std::endl;
	std::getline(std::cin,nombreFichero);
	 	
 	std::ifstream fich(nombreFichero.c_str(), std::ios::in);
 	ed::Vertice vertice;
 	
 	if(grafo.isEmpty()==true){
 	
 	
 		if(fich.is_open()){
 		
 			while(fich >> vertice){
 			
 				//Añadimos el vertice al vector de Vertices
 				grafo.addVertice(vertice);
 			}
 		}
 		else{
 			std::cout << BIRED << "Error al abrir el fichero " << RESET << nombreFichero << std::endl;
 			return false;
 		}
 	
		fich.close();
	
		grafo.indice();
		//Calculamos las distancias entre todos los vertices y las almacenamos en el vector de lados
		grafo.rellenaMatriz();  //Rellenamos la matriz de adyacencia que nos servira para el vector de lados
		grafo.rellenarVectorLados(); //Rellenamos el vector de lados con ayuda de la matriz Adyacencias
		grafo.ordenarVectorLados();  //Ordenamos el vector de lados
	
		return true;
	}
	else{
		int opcion;
			std::cout << BIBLUE << "Indique qué desea hacer" << RESET << std::endl;
			std::cout << "[1] Borrar y cargar uno nuevo " << std::endl;
			std::cout << "[0] Salir" << std::endl  << std::endl;
			
			std::cout << BIGREEN;
			std::cout << "Opción: ";
			std::cout << RESET;
	
			// Se lee el número de opción
			std::cin >> opcion;
	
			// Se elimina el salto de línea del flujo de entrada
	    		std::cin.ignore();

			std::cout << std::endl;	
				
			switch(opcion)
			{
				case 1:
						grafo.removeAll();
						cargarGrafoDeFichero(grafo);
						return true;
						break;
	
				case 0:
					     break;
					     
				default:
						std::cout << BIRED << "Opción incorrecta:" << RESET << opcion << std::endl;
			}
	}
	return false;		
}


void ed::mostrarGrafo(ed::Grafo & grafo){
	
	std::cout << std::endl;
		
	if(grafo.isEmpty()==false){
		grafo.mostrarGrafo();
	}
	else{
		std::cout << BIRED << "El Grafo está Vacío " << RESET << std::endl;
	}		
}


void ed::arbolcosteminimo(ed::Grafo & grafo){
	
	std::cout << std::endl;
	
	if(grafo.isEmpty()==false){
	int opcion;
	ed::Grafo solucion;
	
		
			std::cout << BIBLUE << "Indique qué algoritmo desea implementar" << RESET << std::endl << std::endl;
			std::cout << BIYELLOW << "[1] Algoritmo de Prim " << RESET << std::endl;
			std::cout << BIYELLOW << "[2] Algoritmo de Kruskal " << RESET << std::endl << std::endl;
			std::cout << BIRED    << "[0] Salir " << std::endl;
			
			std::cout << BIGREEN;
			std::cout << "Opción: ";
			std::cout << RESET;
	
			// Se lee el número de opción
			std::cin >> opcion;
	
			// Se elimina el salto de línea del flujo de entrada
	    		std::cin.ignore();

			std::cout << std::endl;	
				
			switch(opcion)
			{
				case 1:
						solucion = algoritmoPrim(grafo);
						solucion.mostrarGrafo();
						break;
				
				case 2: 	
				
						solucion = algoritmoKruskal(grafo);
						solucion.mostrarGrafo();
						break;
						
				case 0:
					     break;
					     
				default:
						std::cout << BIRED << "Opción incorrecta:" << RESET << opcion << std::endl;
			}
				
		return;
	}
	else{
		std::cout << BIRED << "El Grafo está Vacío " << RESET << std::endl;
	}
}		

ed::Grafo ed::algoritmoPrim(ed::Grafo &grafo){
	
	ed::Grafo grafo_prim(grafo.getVertices());	//Mi nuevo grafo a devolver que será no dirigido, invocación a constructor para la reserva de memoria
	float menorCoste = grafo.getDatoMatriz(0,0);	//Menor Coste de distancia guardada en mi matriz, en primer caso lo iguales al primer dato de la matriz
	std::vector<ed::Vertice> _U;  			//Vector U donde guardo los vertices conectados
	std::vector<ed::Vertice> _NU; 			//Vector N-U donde guardo el resto de los vertices que no estan en U
	int vertice1=0, vertice2 =0;  			//Guardo mi indice de mi vectores que corresponde al menor Coste
	int posicion = 0;  	 					//Guardo la posicion de mi vector N-U que debe eliminarse y meterse en U
	int total=0;
	
	
	//Como mi vector de Vertices es el mismo lo copiamos a nuestro nuevo grafo
	grafo_prim.setVectorVertices(grafo.getVectorVertices());
	
	//Inserto el primer vertice en mi vector de vertices Visitados
	_U.push_back(grafo.getVertice(0));
	
	//Inserto el resto de los vertices en N-U
	for(int i=1; i<grafo.getVertices(); i++){
	
		   _NU.push_back(grafo.getVertice(i));
	}
	
	while(_NU.size() != 0){	//No paramos hasta que mi Vector N-U esta vacio
		
		//Vamos a igualar menorCoste al mayor valor de la matriz
		/***********************************************************************************/
		for(int i=0; i<grafo.getVertices(); i++){
			
			for(int j=0; j<grafo.getVertices(); j++){
				
				if(grafo.getDatoMatriz(i,j)>menorCoste){
					
					menorCoste = grafo.getDatoMatriz(i,j);
				}
			}
		}
		/***************************************************************************************/
		
		for(int unsigned i=0; i<_U.size(); i++){
			
			for(int unsigned j=0; j<_NU.size(); j++){
				
				if(grafo.getDatoMatriz(_U[i].getEtiqueta(),_NU[j].getEtiqueta()) < menorCoste){
					//Guardo los dos vertices que corresponde con el menorCoste
					vertice1 = _U[i].getEtiqueta();
					vertice2 = _NU[j].getEtiqueta();
					//Modifico el valor de menorCoste con el nuevo valor
					menorCoste = grafo.getDatoMatriz(_U[i].getEtiqueta(),_NU[j].getEtiqueta());
					posicion = j;  //Guardo la posicion de mi Vertice a intercambiar de vector _NU a _U
				}
			}
		}
		
		//Sumo mi distancia total
		total += grafo.getDatoMatriz(vertice1,vertice2);
		
		//Intercambio Vertices de N-U a U
		_U.push_back(_NU[posicion]);
		_NU.erase(_NU.begin()+posicion);
		
	
		//Introducimos en mi grafo a devolver en su matriz distancia minima en cada ciclo
		grafo_prim.setDatoMatriz(vertice1, vertice2, grafo.getDatoMatriz(vertice1,vertice2));
		
		//Si el grafo es no dirigido tambien lo insertamos en la parte inferior de la matriz, ya que es simetrica
		if(!grafo.esDirigido()){
			grafo_prim.setDatoMatriz(vertice2, vertice1, grafo.getDatoMatriz(vertice1,vertice2));	
		}
		
	}
	
	std::cout << std::endl << std::endl;
	std::cout << BIYELLOW << "Distancia total: " << total << std::endl;
	
	return grafo_prim;
}


ed::Grafo ed::algoritmoKruskal(ed::Grafo &grafo){
	
	ed::Grafo grafo_kruskal(grafo.getVertices());	//Mi nuevo grafo a devolver que será no dirigido, invocación a constructor para la reserva de memoria
	
	//Como mi vector de Vertices es el mismo lo copiamos a nuestro nuevo grafo
	grafo_kruskal.setVectorVertices(grafo.getVectorVertices());
	
	//Vector de lados donde guardo mis lados de menor distancia y que no forman ciclos
	std::vector<ed::Lado> AACM;	
	double total=0;
	
	//Debemos rellenar nuestro vector de padre para evitar los ciclos
	grafo.rellenaPadre();
	
	
	//Recorremos mi vector de lados ya ordenado
	for(int i=0; i<grafo.getLados(); i++){   
		
		//Guardo mi etiquetas de los Vertices que representan tb su posicion en el vector
		int origen  = grafo.getLado(i).getVerticeA().getEtiqueta();
		int destino = grafo.getLado(i).getVerticeB().getEtiqueta();
		double distancia = grafo.getLado(i).getDistancia();		//Guardao la distancia entre dos Vertices
			
		if(!grafo.componenteConexa(origen,destino)){	//Evitamos los ciclos
			
			total += distancia;			//Variable que guarda la distancia total
			AACM.push_back(grafo.getLado(i));	//Si componente conexa es falso, guardamos el lado en mi vector de lados
			grafo.Union(origen,destino);		//Unimos dos vertices, como un arbol que nos servira para detectar los ciclos 
				
			std::cout<<std::endl;
		}
	}
	
	
	grafo_kruskal.setVectorLados(AACM);	//Modificamos mi vector de lados con los valores de AACM
	grafo_kruskal.setVertices(grafo.getVertices());	//Modificamos el numero de Vertices de mi grafo a devolver
	grafo_kruskal.setLados(AACM.size());			//Modificamos el numero de Lados de mi grafo a devolver
	grafo_kruskal.setPadre(grafo.getPadre());		//Modificamos el vector de padre de mi grafo a devolver
	grafo_kruskal.setDirigido(grafo.esDirigido());	//Modificamos el atributo dirigido de mi grafo a devolver
	
	//Inserto la matriz de mi grafo a devolver los valores que tengo en mi vector AACM de lados que contiene los lados con menor coste y algoritmo aplicado
	for(int i=0; i<grafo_kruskal.getLados(); i++){
		
		grafo_kruskal.setDatoMatriz(AACM[i].getVerticeA().getEtiqueta(), AACM[i].getVerticeB().getEtiqueta(), AACM[i].getDistancia());
		
		//Si el grafo es no dirigido tambien lo insertamos en la parte inferior de la matriz, ya que es simetrica
		if(!grafo_kruskal.esDirigido()){
			grafo_kruskal.setDatoMatriz(AACM[i].getVerticeB().getEtiqueta(), AACM[i].getVerticeA().getEtiqueta(), AACM[i].getDistancia());
		}
	}
	
	std::cout << std::endl;
	std::cout << BIYELLOW << "Distancia total: " << total << std::endl;
	
	return grafo_kruskal;
	
}



	
	

	



