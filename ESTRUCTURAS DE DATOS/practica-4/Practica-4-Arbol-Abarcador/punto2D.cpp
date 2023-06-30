// Fichero: Punto2D.cpp

// Ficheros de cabecera
#include <cmath>

#include "punto2D.hpp"

// Espacios de nombres utilizados
using namespace std;

/*
 Definiciones de las funciones lectura y escritura de la clase Punto2D
*/
 
void ed::Punto2D::escribirPunto2D()
{
  cout << "(" << getX() << ", " << getY() << ")" << endl; 
}

  
void ed::Punto2D::leerPunto2D()
{
  float x, y;

  cout << "\n Lectura de las coordenadas de un punto: P(x,y) " << endl;

  cout << " Abscisa: x --> ";
  cin >> x;

  cout << " Ordenada: y --> ";
  cin >> y;

  // Se asignan los valores leídos a los atributos del punto   
  setX(x);
  setY(y);
}

namespace ed{
	
std::ostream &operator<<(std::ostream & stream, Punto2D const & objeto)
{
  	stream << objeto.getX();
  	stream << " ";
  	stream << objeto.getY();
  
  	return stream;
}


// Sobrecarga del operador de entrada
std::istream &operator>>(std::istream & stream, Punto2D & objeto)
{

	// Se lee el vertice teniendo en cuenta el formato 0.0 0.0
  	std::string cadena;
  
 	std::getline(stream,cadena,' ');
  	objeto.setX(atof(cadena.c_str()));

 	std::getline(stream,cadena,'\n');
 	objeto.setY(atof(cadena.c_str()));

  	return stream;
}

} 
	


