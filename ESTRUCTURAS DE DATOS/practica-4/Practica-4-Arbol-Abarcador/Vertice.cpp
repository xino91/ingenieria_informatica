// Fichero: Vertice.cpp

// Ficheros de cabecera
#include <iostream>

#include "Vertice.hpp"


namespace ed{
	
	// Sobrecarga del operador de salida
std::ostream &operator<<(std::ostream &stream, ed::Vertice const &vertice)
{
  	stream << "(";
  	stream << vertice.getEtiqueta();
  	stream << ")";
  	stream << " ";
  	stream << "(";
  	stream << vertice.getPunto();
  	stream << ")";
  	
  return stream;
}


// Sobrecarga del operador de entrada
std::istream &operator>>(std::istream &stream, ed::Vertice &vertice)
{

 	ed::Punto2D punto;
 	
	stream >> punto;
 	vertice.setPunto(punto);

 	 return stream;
}

}
