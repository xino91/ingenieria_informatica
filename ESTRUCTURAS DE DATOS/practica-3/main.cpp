/*!
 \file     main.cpp
 \author   Antonio Ariza García
 \date     07-05-2018
 \version  1.0
*/

/*!
	\mainpage Implementacion de un monticulo de mediciones de precpitaciones
	\author	Antonio Ariza García
	\date     07-05-2018
	\version  1.0
	\brief 	Programa principal de la practica 3 de Estructuras de Datos
*/

#include <iostream>

#include <string>

#include "funcionesAuxiliares2.hpp"
#include "funcionesAuxiliares.hpp"

#include "MonticuloMediciones.hpp"
#include "Medicion.hpp"

#include "macros.hpp"

/*! 
		\brief   Programa principal de la práctica 3: montículo de mediciones
		\return  int
*/

int main(){

	ed::MonticuloMediciones monticulo;

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
					std::cout << "[1] Comprobar si el monticulo tiene mediciones " << std::endl;
					ed::comprobarMonticulo(monticulo);
					break;

			//////////////////////////////////////////////////////////////////////////////
			case 2: 
					std::cout << "[2] Cargar monticulo desde un fichero " << std::endl;
					ed::cargarMonticulo(monticulo);
					break;

			case 3: 
					std::cout << "[3] Grabar monticulo ordenado a un fichero " << std::endl;
					ed::grabarMonticulo(monticulo);
					break;

			//////////////////////////////////////////////////////////////////////////////
			case 4: 
				  	std::cout << "[4] Consultar el tamaño y la cima del monticulo " << std::endl; 
					ed::consultarMonticulo(monticulo);
					break;

			case 5: 
				  	std::cout << "[5] Mostrar mediciones del monticulo " << std::endl; 
					ed::mostrarMonticulo(monticulo);
					break;


			//////////////////////////////////////////////////////////////////////////////
			case 6: 
					std::cout << "[6] Modificar la Medicion que Ocupa la Cima " << std::endl;
				  	ed::modificaCima(monticulo);
					break;


			case 7: 
					std::cout << "[7] Borrar todo el monticulo " << std::endl;
				 	ed::borrarTodoMonticulo(monticulo);
					break;

			//////////////////////////////////////////////////////////////////////////////
			case 8: 
					std::cout << "[8] Consultar Precipitacion de un Dia " << std::endl;
			    	     ed::consultarUnDia(monticulo);
					break;

			case 9: 
					std::cout << "[9] Insertar una Medicion " << std::endl;
				  	ed::insertarMedicion(monticulo);
					break;

			case 10: 
					std::cout << "[10] Borrar la Cima " << std::endl;
					ed::borrarCima(monticulo);
					break;
					
			case 11:  std::cout << "[11] Modifica una Medicion dada su Fecha" << std::endl;
					ed::modificarDatosMedicion(monticulo);
					break;
			
			case 12: 
					std::cout << "[12] Mostrar Precipitaciones de un Mes dado " << std::endl;
					ed::mostrarMedicionesMes(monticulo);
					break;
					
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


