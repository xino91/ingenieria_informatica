/*!
	\file    Vertice.hpp
	\brief   Se define el TAD Vertice.
	\author  Antonio Ariza García
	\date    04-05-2018
*/

#ifndef _VERTICE_HPP
#define _VERTICE_HPP


#include <cassert>
#include "punto2D.hpp"
#include "macros.hpp"



/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed
{

//!  Definición de la clase Vertice
class Vertice{
	//! \name Atributos privados de la clase Vertice
	private:

		int _etiqueta;	//!< etiqueta del vertice 
		ed::Punto2D _punto;		//!< Punto del Vertice

	//! \name métodos públicos de la clase Vertice
	public:
	
	//! \name Observadores: funciones de consulta de la clase Vertice
/*! 
	\brief   Función que devuelve la etiqueta del vertice
	\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
	\note    Función inline y redefinida de la clase padre VerticeInterfaz
	\return  Valor del atributo que representa la etiqueta del vertice de tipo string
	\pre     Ninguna
	\post    Ninguna
	\sa      getCoorX(), getCoorY()
*/
	inline int getEtiqueta()const {
		
		return _etiqueta;
	}

	
/*!
	\brief	  Función que devuelve la coordenada x del vertice
	\attention  Se utiliza el modificador const en la definicion de la función para poder definir el constructor de copia y el operador de asignación "="
	\note 	  Funcion inline
	\return	  Valor del atributo que representa a un punto de tipo Punto2D
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getEtiqueta()
*/
	inline ed::Punto2D getPunto() const {
		return _punto;
	}

	/*****************************************************************/
	
	//!	 \name 	Funciones modificadores de la clase vertice

/*!
	\brief 	Función que modifica el atributo etiqueta de la clase vertice
	\note 	Función inline y redefinida de la clase padre VerticeInterfaz
	\param    nombre: de tipo string, representa el nuevo nombre del atributo etiqueta
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	getEtiqueta() == nombre
	\sa 		getEtiqueta(), setCoorX(), setCoorY()
*/
	inline void setEtiqueta(int nombre){
	
		this->_etiqueta = nombre;
		
			#ifndef NDEBUG
				assert(getEtiqueta() == nombre);
			#endif
	}


/*!
	\brief 	Función que modifica el atributo punto de la clase vertice
	\note 	Función inline y redefinida de la clase padre VerticeInterfaz
	\param    punto: de tipo punto2D, representa el nuevo valor del punto
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	getPunto() == punto
	\sa 		setEtiqueta(), getPunto()
*/
	inline void setPunto(ed::Punto2D punto){
	
		this->_punto = punto;
		
			#ifndef NDEBUG
				assert(getPunto() == punto);
			#endif
	}

	/******************************************************************/
	
	//!	\name   Operadores de la clase Vertice

/*! 
	\brief     Operador de asignación: operador que "copia" un vertice en otro vertice
	\attention Se sobrecarga el operador de asignación "="
	\note      Función inline
	\warning   Se requiere que las funciones de acceso get tengan el modificar const
	\param     objeto de la clase Vertice pasado como referencia constante
	\pre       El objeto es distinto del objeto actual
	\post      getEtiqueta() == objeto.getEtiqueta() and getPunto() == objeto.getPunto()
	\sa        setEtiqueta(), getPunto(), getEtiqueta(), setPunto()
*/
	inline Vertice & operator=(Vertice const & objeto){
		
		// Se comprueba que no sean el mismo objeto
		if (this != &objeto) 
		{
			this->setEtiqueta(objeto.getEtiqueta());
			this->setPunto(objeto.getPunto());

			#ifndef NDEBUG
	  		// Se comprueba la postcondición
			assert(this->getEtiqueta() == objeto.getEtiqueta());
			assert(this->getPunto() == objeto.getPunto());
			#endif //NDEBUG
		}

		return *this;
	}

/*! 
	\brief     Operador de igualdad: compara si dos vertices son iguales
	\attention Se sobrecarga el operador de asignación "=="
	\note      Función inline
	\param     objeto: vertice pasada como referencia constante
	\pre       Ninguna
	\post      Ninguna
	\sa        setEtiqueta(), getPunto(), getEtiqueta(), setPunto()
*/
	inline bool operator==(Vertice const & objeto){
		
		bool valor;
	   
		valor = (this->getEtiqueta() == objeto.getEtiqueta() and
			    this->getPunto() == objeto.getPunto() );
         		    
             #ifndef NDEBUG
	  		// Se comprueba la postcondición
			assert(valor == (this->getEtiqueta() == objeto.getEtiqueta() and
			    			  this->getPunto() == objeto.getPunto()));
			#endif //NDEBUG
		return valor;
	}
	


}; // Fin de la definición de la clase Vertice

	//! \name Funciones externas de la clase Vertice: sobrecarga de los operadores de flujo
	
	// Sobrecarga del operador de salida
/*!
  	\brief     Sobrecarga del operador de salida o escritura "<<"
	\param     stream Flujo de entrada
	\param     vertice: de tipo Vertice pasada como referencia
	\pre       Ninguna
	\post      Ninguna
	\sa        operator>>()
*/
	std::ostream &operator<<(std::ostream &stream, Vertice const &vertice);

		/********************************************************************/
		// Sobrecarga del operador de entrada
/*!
  	\brief     Sobrecarga del operador de entrada o lectura ">>"
	\param     stream Flujo de entrada
	\param     vertice: de tipo Vertice pasada como referencia
	\pre       Ninguna
	\post      Ninguna
	\sa        operator>>()
*/
	std::istream &operator>>(std::istream &stream, Vertice &vertice);


}  // \brief Fin de namespace ed.

//  _VERTICE_HPP_
#endif
