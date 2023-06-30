/*! 
   \file  Medicion.cpp
   \brief Fichero que contiene el código de las funciones de la clase Medicion
*/


// Ficheros de cabecera
#include <iostream>

// atoi, atof
#include <stdlib.h>

#include "Medicion.hpp"


// COMPLETAR

bool ed::Medicion::leerMedicion(){
	 //Lee una medición desde el teclado
	 Fecha fecha;
	 float precipitacion;
	 
	 //Llamamos a leerFecha
	 if(fecha.leerFecha() == false){
	 	return false;
	 }
	 
	 //Precipitacion
	 std::cout << "Introduzca una Precipitación" << std::endl;
	 std::cin >> precipitacion;
	 
	 this->setFecha(fecha);
	 this->setPrecipitacion(precipitacion);
	 
	 	 #ifndef NDEBUG
  			// Se comprueba la postcondición
  			assert(fecha.esCorrecta() == true);
 		 #endif //NDEBUG
 		 
 	return true; 
}


void ed::Medicion::escribirMedicion(){
	
	  std::cout << this->getFecha() << " "
            	  << this->getPrecipitacion() << std::endl;
	
}

////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{

// Sobrecarga del operador de salida
ostream &operator<<(ostream &stream, ed::Medicion const &medicion)
{
  
  	stream << medicion.getFecha();
  	stream << " ";
  	stream << medicion.getPrecipitacion();
  	
  return stream;
}

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, ed::Medicion &medicion)
{

	// Se lee la fecha teniendo en cuenta el formato: DD-MM-AAAA 0.0
 	std::string cadena;
 	Fecha fecha;
 	
	stream >> fecha;
 	medicion.setFecha(fecha);
	
	std::getline(stream,cadena,'\n');
	medicion.setPrecipitacion(atof(cadena.c_str()));

 	 return stream;
} 

} // Fin del espacio de nombres ed
