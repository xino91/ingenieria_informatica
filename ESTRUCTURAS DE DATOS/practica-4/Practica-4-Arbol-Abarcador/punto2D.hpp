/*! \par Fichero: Punto2D.hpp
   Punto2D representa la clase punto del plano euclídeo definida mediante template (plantilla)
*/
#ifndef _PUNTO2D_HPP_
#define _PUNTO2D_HPP_

// Facilita la entrada y salida 
#include <iostream>
#include <stdlib.h>
#include <cassert>

// 
using std::ostream;
using std::istream;

/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/

namespace ed {

//!  Definición de la clase Punto2D
class Punto2D 
{
  //! \name Atributos privados de la clase Punto2D
   private: 
     float _x; //!< abscisa del Punto2D 
	float _y; //!< ordenada del Punto2D 


   //! \name Funciones o métodos públicos de la clase Punto2D
   public:

	//! \name CONSTRUCTORES
	/*! 
		\brief     Constructor que crea un Punto2D a partir de sus coordenadas x e y
		\attention Función sobrecargada        
	 	\note      Los parámetros tienen valores por defecto
		\param     x de tipo float, valor por defecto 0
		\param     y de tipo float, valor por defecto 0
		\pre       Los valores de x e y deben ser del tipo float
		\post      Los atributos de la clase Punto2D deben tener los valores x e y, respectivamente
		\sa setX(), setY()
	*/
	inline Punto2D(float x=0, float y=0)
	{
		setX(x);
		setY(y);
			
			#ifndef NDEBUG
				assert(getX() == x and getY() ==y);
			#endif
	}

	/*! 
		\brief     Constructor de "copia" que crea un Punto2D a partir de otro Punto2D
		\attention Función sobrecargada        
		\param     q de tipo Punto2D pasado como referencia constante
		\pre       El Punto2D q debe existir
		\post      Los valores de los atributos de la clase actual deben ser iguales a los del objeto q
		\sa        getX(), getY(), setX(), setY()
	*/
	inline Punto2D(Punto2D const &q)
	{
		setX(q.getX());
		setY(q.getY());
			
			#ifndef NDEBUG
				assert(getX() == q.getX() and getY() == q.getY());
			#endif
	}

	//! \name OBSERVADORES

	/*! 
		\brief  Devuelve la coordenadas "x" de un Punto2D
		\return componente "x" del Punto2D (tipo float)
		\pre    El Punto2D debe existir
		\post   Ninguna
		\sa     getY()
	*/
	inline float getX()const
	{
		return _x;
	}
	/*! 
		\brief  Devuelve la coordenadas "y" de un Punto2D
		\return componente "y" del Punto2D (tipo float)
		\pre    El Punto2D debe existir
		\post   Ninguna
		\sa     getX()
	*/
	inline float getY()const
	{
		return _y;

	}


	//! \name MODIFICADORES

	/*! 
		\brief Asigna un valor "v" a la coordenada "x" de un Punto2D
		\param v nuevo valor de la cordenada "x" del Punto2D
		\pre   El Punto2D debe existir
		\post  El valor del atributo _x debe ser v
		\sa    setY()
	*/
	inline void setX(float v)
	{
		_x = v;
			
			#ifndef NDEBUG
				assert(this->getX() == v);
			#endif
	}


	/*! 
		\brief Asigna un valor "v" a la coordenada "y" de un Punto2D
		\param v nuevo valor de la cordenada "y" del Punto2D
		\pre   El Punto2D debe existir
		\post  El valor del atributo _y debe ser v
		\sa    setX()
	*/
	inline void setY(float v)
	{
		_y = v;
			
			#ifndef NDEBUG
				assert(this->getY() == v);
			#endif
	}


         //! \name OPERADORES
   
	/*! 
		\brief     Operador que "copia" un Punto2D en otro Punto2D
		\attention Se sobrecarga el operador de asignación "="
		\param     q Punto2D que se va a copiar en el punto actual
		\pre       El Punto2D q debe existir
		\post      Ninguna
		\sa        getX(), getY(), setX(), setY()
	*/
	inline Punto2D & operator=(Punto2D const &q)
	{
		setX(q.getX());
		setY(q.getY());

			#ifndef NDEBUG
				assert(this->getX() == q.getX());
				assert(this->getY() == q.getY());
			#endif
			
		return *this;
	}
	
	/*! 
	\brief     Operador de igualdad: compara si dos puntos son iguales
	\attention Se sobrecarga el operador de asignación "=="
	\note      Función inline
	\param     objeto: vertice pasada como referencia constante
	\pre       Ninguna
	\post      Ninguna
	\sa        getX(), getY(), setX(), setY()
	*/
	inline bool operator==(Punto2D const & objeto){
		
		bool valor;
	   
		valor = (this->getX() == objeto.getX() and
			    this->getY() == objeto.getY());
         		    
             #ifndef NDEBUG
	  		// Se comprueba la postcondición
			assert(valor == (this->getX() == objeto.getX() and
			    			  this->getY() == objeto.getY()));
			#endif //NDEBUG
		return valor;
	}
	
	
	//! \name Funciones lectura y escritura de la clase Punto2D

	/*! 
		\brief   Asigna a un Punto2D las coordenadas "x" e "y" leídas desde el teclado
		\pre     El Punto2D debe existir
		\post    Ninguna
		\warning Se deben teclear números del tipo float
		\sa      setX(), setY()
	*/
	void leerPunto2D();


	/*! 
		\brief Escribe por pantalla las coordenadas de un Punto2D de la forma (x,y)
		\pre   El Punto2D debe tener valores asignados a sus coordenadas
		\post  Ninguna
		\sa    getX(), getY()
	*/
	void escribirPunto2D();
	
		
	

	
  
}; // Fin de la definición de la clase Punto2D

	//! \name Funciones externas de la clase Punto2D: sobrecarga de los operadores de flujo	
	
	// Sobrecarga del operador de salida
/*!
  	\brief     Sobrecarga del operador de salida o escritura "<<"
	\param     stream Flujo de salida
	\param     objeto: de tipo Punto2D pasada como referencia
	\pre       Ninguna
	\post      Ninguna
	\sa        operator>>()
*/
	std::ostream &operator<<(std::ostream & stream, Punto2D const & objeto);
	
	/********************************************************************/
	// Sobrecarga del operador de entrada
/*!
  	\brief     Sobrecarga del operador de entrada o lectura ">>"
	\param     stream Flujo de entrada
	\param     objeto: de tipo Punto2D pasada como referencia
	\pre       Ninguna
	\post      Ninguna
	\sa        operator<<()
*/
	std::istream &operator>>(std::istream & stream, Punto2D & objeto);



} // \brief Fin de namespace ed.


//  _PUNTO2D_HPP_
#endif 
