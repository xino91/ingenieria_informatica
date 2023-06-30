// Fichero: Grafo.cpp

// Ficheros de cabecera
#include <iostream>
#include <cmath>
#include <iomanip>	//setprecision
#include "macros.hpp"

#include "Grafo.hpp"


float ed::Grafo::distanciaEuclidea(ed::Vertice const &u, ed::Vertice const &v){

	float distancia;
	
	distancia = sqrt( pow((u.getPunto().getX() - v.getPunto().getX()),2) + pow((u.getPunto().getY() - v.getPunto().getY()),2) );
	
	return distancia;
} 


void ed::Grafo::rellenaMatriz(){
	
		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif
			
	int i,j;
	
	//Redimensionamos el vector de vectores a los vertices tengamos
	_matriz.resize(getVertices());
	
	for(i=0; i<getVertices(); i++){
		//Redimensionamos el vector a los vertices que tengamos, tendremos un vector que contiene vectores de tam "getVertices"
		//Cada _matriz[i] será una fila de nuestra matriz
		_matriz[i].resize(getVertices());
	
		for(j=0; j<getVertices(); j++){
			//Calculamos la distancia Euclidea de entre todos los vertices, esto se hace porque es un grafo completo
			double distancia = distanciaEuclidea(_vectorVertices[i], _vectorVertices[j]);
			_matriz[i][j] = distancia; //La matriz contiene la distancia entre los vertices
		}
	}
}

void ed::Grafo::mostrarMatrizAdyacencia()const{
	
	int i,j;
	
	for(i=0; i < getVertices(); i++){
		
		for(j=0; j < getVertices(); j++){
		
			std::cout << _matriz[i][j] << "	";
		}
	std::cout << std::endl;
	}
}

void ed::Grafo::rellenarVectorLados(){
	
	//Rellenamos el vector de lados recorriendo la matriz de adyacencia
	
	for(int i=0; i < getVertices(); i++){
		
		//Recorremos la diagonal inferior de la matriz, ya que es simetrica por tanto G(u,v) = G(v,u)
		for(int j=i; j < getVertices(); j++){
			
			//Si es distinto de cero indica que los vertices están conectados
			if(_matriz[i][j] != 0 ){
				//Añadimos los vertices al lado
				this->addLado(_vectorVertices[i], _vectorVertices[j]);
			}
		}
	}

}

void ed::Grafo::mostrarVectorLados()const{
	
	for(int i=0; i<getLados(); i++){
		
		std::cout << _vectorLados[i] << std::endl;
	}
}


void ed::Grafo::ordenarVectorLados(){
	
	ed::Lado aux;
	
	//Ordenación burbuja
	for(int i=0; i<getLados()-1; i++){
		
		for(int j=i+1; j<getLados(); j++){
			
			if(_vectorLados[i].getDistancia() > _vectorLados[j].getDistancia()){
				
				//Intercambiamos
				aux = _vectorLados[j];
				_vectorLados[j]= _vectorLados[i];
				_vectorLados[i]= aux;
			}
		}
	}
}
		
		
void ed::Grafo::mostrarGrafo()const{

	std::cout << std::endl;
	
	//std::cout << CLEAR_SCREEN;
	
	std::cout << BIBLUE << "VECTOR DE VERTICES" << RESET << std::endl << std::endl;
	
	for(int i=0; i<getVertices(); i++){
		
		std::cout << _vectorVertices[i] << std::endl;
	}
	
	std::cout << std::endl;
	std::cout << BIGREEN << "Enter" << RESET << " para continuar" << std::endl;
	std::cin.ignore();
	
	std::cout << BIBLUE << "MATRIZ DE ADYACENCIA" << RESET << std::endl << std::endl;
	
	std::cout << std::setprecision(3);
	
	
	for(int i=0; i<getVertices(); i++){
		
		for(int j=0; j<getVertices(); j++){
			
			if((_matriz[i][j] == 0) and (i!=j) ){
				std::cout << "-"<<"	";
			}
			else{
				std::cout << "(" << _matriz[i][j] << ")" << "	";
			}
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	
	if(getLados()!=0){
	
		std::cout << std::endl;
		std::cout << BIGREEN << "Enter" << RESET << " para continuar" << std::endl;
		std::cin.ignore();
	
	
		std::cout << BIBLUE << "VECTOR DE LADOS" << RESET << std::endl;
	
		for(int i=0; i<getLados(); i++){
		
			std::cout << _vectorLados[i] << std::endl;
		}
	}
	
}
			






