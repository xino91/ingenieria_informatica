/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares para el programa main.cpp de la practica 3
  \author Antonio Ariza García
  \date   30-04-2018
*/


#include <iostream>

#include <fstream>

#include <string>

#include "funcionesAuxiliares2.hpp"
#include "funcionesAuxiliares.hpp"
          
#include "MonticuloMediciones.hpp"

#include "Medicion.hpp"

#include "macros.hpp"

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
	std::cout << "[1] Comprobar si el monticulo tiene mediciones ";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[2] Cargar monticulo desde un fichero ";

	PLACE(posicion++,10);
	std::cout << "[3] Grabar monticulo ordenado a un fichero ";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;
 
	PLACE(posicion++,10);
	std::cout << "[4] Consultar el tamaño y la cima del monticulo ";

	PLACE(posicion++,10);
	std::cout << "[5] Mostrar mediciones del monticulo ";

	PLACE(posicion++,10);
	std::cout << "[6] Modificar la Medicion que Ocupa la Cima";

	PLACE(posicion++,10);
	std::cout << "[7] Borrar todo el monticulo ";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[8] Consultar Precipitacion de un Dia ";

	PLACE(posicion++,10);
	std::cout << "[9] Insertar una Medicion ";

	PLACE(posicion++,10);
	std::cout << "[10] Borrar la Cima ";
	
	PLACE(posicion++,10);
	std::cout << "[11] Modifica una Medicion dada su Fecha";
	
	
	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[12] Mostrar Precipitaciones de un Mes dado ";
	
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


//////////////////////////////////////////////////////////////////////////////

void ed::comprobarMonticulo(ed::MonticuloMediciones & monticulo)
{
	std::cout<<std::endl;
	
	if(monticulo.isEmpty()){
		std::cout << BIRED << "El monticulo está vacío " << RESET << std::endl;
	}
	else{
		std::cout << BIGREEN << "El monticulo tiene Mediciones " << RESET << std::endl;
	}
	return;
}

//////////////////////////////////////////////////////////////////////////////

void ed::cargarMonticulo(ed::MonticuloMediciones & monticulo)
{
	 std::cout << std::endl;
	 std::string nombreFichero;
	 std::cout << BIBLUE << "Introduzca el nombre del fichero" << RESET << std::endl;
	 getline(std::cin, nombreFichero);
	 
	 
	 
	if(monticulo.isEmpty() == true){
		if(cargarMonticuloDeFichero(nombreFichero, monticulo)){
			std::cout << BIGREEN << "Fichero cargado correctamente" << RESET << std::endl;
		}
		else{
			std::cout << BIRED << "Error al cargar el fichero en el Monticulo" << RESET << std::endl;
		}
	}
	else{
	
		int opcion;
		
			std::cout << BIBLUE << "Ya hay un Fichero cargado" << RESET << std::endl;
			
		
		do{
			std::cout << BIBLUE << "Indique qué desea hacer" << RESET << std::endl;
			std::cout << "[1] Borrar y cargar el introducido ->  " << RESET << nombreFichero << std::endl;
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
						monticulo.removeAll();
						if(cargarMonticuloDeFichero(nombreFichero, monticulo)){
							std::cout << BIGREEN << "Fichero cargado correctamente" << RESET << std::endl;
							return;
						}
						else{
							std::cout << BIRED << "Error al cargar el fichero en el Monticulo" << RESET << std::endl;
						}
						
						break;
	
				case 0:
					     break;
					     
				default:
						std::cout << BIRED << "Opción incorrecta:" << RESET << opcion << std::endl;
			}
		}while (opcion!=0);

	}
		
		return;
}

//////////////////////////////////////////////////////////////////////////////

void ed::grabarMonticulo(ed::MonticuloMediciones & monticulo){

	if(monticulo.isEmpty() == false){
		std::cout << std::endl;
	
		std::string nombreFichero;
	
		std::cout << BIBLUE << "Introduzca el nombre del Fichero para guardar el Monticulo ordenado" << RESET << std::endl;
		getline(std::cin, nombreFichero);
	
		
			if(grabarMonticuloEnFichero(nombreFichero, monticulo)){
				std::cout << BIGREEN << "Fichero grabado correctamente" << RESET << std::endl;
			}
			else{
				std::cout << BIRED << "Error al grabar el Monticulo en el Fichero " << RESET << "'" << nombreFichero << "'" << std::endl;
			}
	}
	else{
		std::cout << BIRED << "El Monticulo está vacío" << std::endl;
	}
	
}

//////////////////////////////////////////////////////////////////////////////

void ed::consultarMonticulo(ed::MonticuloMediciones & monticulo){
	
	std::cout << std::endl;
	
	if(monticulo.isEmpty() == false){
	
		std::cout << std::endl;
		std::cout << BIYELLOW << "Tamaño: " << RESET;  
							std::cout << monticulo.size() << std::endl;
		std::cout << BIYELLOW << "Cima: " << RESET;
							std::cout << monticulo.top();
		std::cout << std::endl;
	}
	else{
		std::cout << BIRED << "El monticulo está vacío" << RESET << std::endl;
	}
	
	return;
}

/////////////////////////////////////////////////////////////////////////////

void ed::mostrarMonticulo(ed::MonticuloMediciones & monticulo){

	std::cout << std::endl;
	
	if(monticulo.isEmpty() == false){
	
		monticulo.print();
		
	}
	else{
		std::cout << BIRED << "El monticulo está vacío" << RESET << std::endl;
	}	
	
	return;
}

//////////////////////////////////////////////////////////////////////////////

void ed::modificarDatosMedicion(ed::MonticuloMediciones & monticulo){
	
	if(monticulo.isEmpty() == false){
		int indice;
		std::cout << BIBLUE << "Modificando la Cima -> " << RESET << monticulo.top(); std::cout << std::endl;
		std::cout << BIBLUE << "Introduzca la Nueva Medición " << RESET << std::endl;
		ed::Fecha aux;
		
			if(aux.leerFecha() == false ){
				std::cout << BIRED << "La Fecha no es válida, no se pudo modificar " << RESET << std::endl << std::endl;
				//pausa
				std::cin.ignore();
			}
			else{
				if((indice=monticulo.buscarMedicion(aux))!= -1){
					
					//std::cout << indice << std::endl;
					monticulo.modifica(indice,aux);
					//pausa
					std::cin.ignore();
				}
				else{
					std::cout << BIRED << "La Medicion no ha sido encontrada, no se pudo modificar " << RESET << std::endl;
					//pausa
					std::cin.ignore();
				}
					
			}
	}
	else{
		std::cout << BIRED << "El monticulo esta vacío" << RESET << std::endl;
	}
	
	return;
}

///////////////////////////////////////////////////////////////////////
void ed::borrarTodoMonticulo(ed::MonticuloMediciones & monticulo){
	
	if(monticulo.isEmpty() == false){
		std::cout << std::endl; std::cout << BIGREEN << "Monticulo Borrado con éxito" << std::endl;
		monticulo.removeAll();
		
	}
	else{
		std::cout << BIRED << "El monticulo esta vacío" << RESET << std::endl;
	}
	return;
}

////////////////////////////////////////////////////////////////////////
void ed::consultarUnDia(ed::MonticuloMediciones & monticulo){

	if(monticulo.isEmpty() == false){
		
		int indice;
		Fecha f;
		std::cout << BIBLUE << "Introduzca la Fecha ha consultar" << RESET << std::endl;
		
		
		if(f.leerFecha()){
			
			if((indice=monticulo.buscarMedicion(f))!= -1){
				
				std::cout << BIYELLOW << "Medicion -> " << RESET;
				monticulo.getMedicion(indice).escribirMedicion();
				std::cout << std::endl;
				//pausa
				std::cin.ignore();
			}
			else{
				std::cout << BIRED << "Fecha no encontrada" << RESET << std::endl;
				std::cin.ignore();
			}	
		}
		else{
			std::cout << BIRED << "La fecha no es válida, " << RESET << std::endl;
			std::cin.ignore();
		}		
				
		
	}
	else{
		std::cout << BIRED << "El monticulo esta vacío" << RESET << std::endl;
	}

}


////////////////////////////////////////////////////////////////

void ed::insertarMedicion(ed::MonticuloMediciones & monticulo){

		ed::Medicion medicion;
		if(medicion.leerMedicion() == true){
			
			if(monticulo.buscarMedicion(medicion.getFecha()) == -1 ){
				monticulo.insert(medicion);
			
			std::cout << BIGREEN << "Insertado con éxito" << RESET << std::endl;
			std::cin.ignore();
			}
			else{
				std::cout << BIRED << "Esta Fecha ya existe, no se pudo insertar " << RESET << std::endl << std::endl;
				std::cin.ignore();
			}
		}
		else{
			std::cout << BIRED << "La fecha no es válida " << RESET << std::endl;
			std::cin.ignore();
		}
	return;
}

/////////////////////////////////////////////////////////////////////

void ed::borrarCima(ed::MonticuloMediciones & monticulo){

	if(monticulo.isEmpty() == false){
		
		if(monticulo.size() == 1 ){
			std::cout << BIGREEN << "Borrando el único elemento del montículo -> " << RESET << monticulo.top(); std::cout << std::endl;
			monticulo.removeAll();
		}
		else{
			std::cout << BIGREEN << "Borrando la Cima del montículo: " << RESET << monticulo.top(); std::cout << std::endl;
			monticulo.remove();
		}
	}
	else{
		std::cout << BIRED << "El monticulo esta vacío" << RESET << std::endl;
	}
	return;
}

////////////////////////////////////////////////////////////////////////

void ed::modificaCima(ed::MonticuloMediciones & monticulo){

	if(monticulo.isEmpty() == false){
		float precipitacion;
		ed::Medicion aux = monticulo.top();
		
		std::cout << std::endl;
		std::cout << BIBLUE << "Modificando la Cima -> " << RESET << monticulo.top(); std::cout << std::endl << std::endl;
		std::cout << BIBLUE << "Introduzca la Nueva Precipitacion " << RESET << std::endl;
		std::cin >> precipitacion;
		
		aux.setPrecipitacion(precipitacion);
		
		monticulo.modify(aux);
		
	}
	else{
		std::cout << BIRED << "El monticulo esta vacío" << RESET << std::endl;
	}
	return;

}

void ed::mostrarMedicionesMes(ed::MonticuloMediciones & monticulo){

	if(monticulo.isEmpty() == false){
		int mes;
		std::cout << BIBLUE << "Introduzca el mes a consultar, con un número entero" << RESET << std::endl;
		std::cin>>mes;
		if(mes<=0 or mes>12){
			
			std::cout << BIRED << "Inválido, este mes no existe" << RESET << std::endl;
			std::cin.ignore();
		}
		else{
			monticulo.mostrarMes(mes);
			std::cin.ignore();
		}
		
	}
	else{
		std::cout << BIRED << "El monticulo esta vacío" << RESET << std::endl;
	}
	return;

}



























