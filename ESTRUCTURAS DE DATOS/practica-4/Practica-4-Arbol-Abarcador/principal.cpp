/*!
 \file     principal.cpp
 \author   Antonio Ariza García
 \date     21-05-2018
 \version  1.0
*/

/*!
	\mainpage Implementacion Árbol abarcador de coste mínimo de un grado no dirigido
	\author	Antonio Ariza García
	\date     30-05-2018
	\version  1.0
	\brief 	Programa principal de la practica 4 de Estructuras de Datos
*/

#include <iostream>

#include <string>

#include "Grafo.hpp"
#include "funcionesAuxiliares.hpp"
#include "macros.hpp"

/*! 
		\brief   Programa principal de la práctica 4: Arbol Abarcador de Coste Mínimo
		\return  int
*/

int main(){

	ed::Grafo grafo;

	int opcion;

	do{
		// Se elige la opción del menú
		opcion = ed::menu();		

		std::cout << CLEAR_SCREEN;
		PLACE(3,1);

		// Se ejecuta la opción del menú elegida
		switch(opcion)
		{
			case 0: 
					std::cout << INVERSE;
					std::cout << "Fin del programa" << std::endl;
					std::cout << RESET;
			break;

		   ///////////////////////////////////////////////////////////////////

			case 1: 
					std::cout << "[1] Cargar Vertices desde el fichero " << std::endl;
					ed::cargarGrafoDeFichero(grafo);
					break;

			//////////////////////////////////////////////////////////////////////////////
			case 2: 
					std::cout << "[2] Mostrar Grafo por pantalla " << std::endl;
					ed::mostrarGrafo(grafo);
					break;

			case 3: 
					std::cout << "[3] Árbol abarcador de coste mínimo " << std::endl;
					ed::arbolcosteminimo(grafo);
					break;

			//////////////////////////////////////////////////////////////////////////////
					
			//////////////////////////////////////////////////////////////////////////////
			default:
				std::cout << BIRED;
				std::cout << "Opción incorrecta ";
				std::cout << RESET;
				std::cout << "--> ";
			  	std::cout << ONIRED;
				std::cout << opcion << std::endl;
				std::cout << RESET;
     }
  
    if (opcion !=0)
    {
		PLACE(80,1);
		std::cout << RESET;
		std::cout << "Pulse ";
		std::cout << BIGREEN;
		std::cout << "ENTER";
		std::cout << RESET;
		std::cout << " para mostrar el ";
		std::cout << INVERSE;
		std::cout << "menú"; 
		std::cout << RESET;

		// Pausa
		std::cin.ignore();

		std::cout << CLEAR_SCREEN;
    }
	  }while(opcion!=0);

	return 0;
}

