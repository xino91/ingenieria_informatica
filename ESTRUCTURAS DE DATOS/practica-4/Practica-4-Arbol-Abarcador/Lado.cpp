// Fichero: lado.cpp

// Ficheros de cabecera
#include <iostream>
#include "Lado.hpp"
#include "macros.hpp"

namespace ed{
	
	// Sobrecarga del operador de salida
std::ostream &operator<<(std::ostream &stream, ed::Lado const &lado)
{
  	std::cout << BIYELLOW << "Vertice A:" << RESET;
  	
  		stream << lado.getVerticeA();
  		stream << "  ";
  		
  	std::cout << BIYELLOW << "Vertice B:" << RESET;
  	
  		stream << lado.getVerticeB();	
  		stream << "	";
  		
  	std::cout << BIYELLOW << "Distancia: " << RESET;
  	
  		stream << lado.getDistancia();
  		std::cout << std::endl;
  	
  return stream;
}


}
