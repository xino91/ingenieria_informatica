/*!
	\file    Vertice.hpp
	\brief   Se define el TAD Vertice.
	\author  Antonio Ariza García
	\date    04-05-2018
*/
#ifndef _LADO_HPP
#define _LADO_HPP


#include <cassert>
#include "Vertice.hpp"
#include "macros.hpp"

/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed
{

//!  Definición de la clase Lado 
class Lado{
	//! \name Atributos privados de la clase Lado
	private:

		float _distancia;		//!< Distancia entre dos Vertice
		ed::Vertice _A;		//!< Vertice A
		ed::Vertice _B;		//!< Vertice B
		
	//! \name métodos públicos de la clase Vertice
	public:
	
	/**************************************************************************/
	
	//! \name Observadores: funciones de consulta de la clase Lado
/*! 
	\brief   Función que devuelve la distancia entre dos vertices
	\note    Función inline y redefinida de la clase padre LadoInterfaz
	\return  Valor del atributo que representa la distancia entre dos vertices
	\pre     Ninguna
	\post    Ninguna
	\sa      getVerticeB(), getVerticeA()
*/
	inline float getDistancia() const {
		
		return _distancia;
	}

	
/*!
	\brief	  Función que devuelve el Vertice A
	\note 	  Funcion inline
	\return	  Valor del atributo que representa al Vertice A 
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVerticeB()
*/
	inline ed::Vertice getVerticeA() const {
		return _A;
	}

	/*****************************************************************/
	

/*!
	\brief	  Función que devuelve el Vertice A
	\note 	  Funcion inline
	\return	  Valor del atributo que representa al Vertice A 
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVerticeB()
*/
	inline ed::Vertice getVerticeB() const {
		return _B;
	}
	

/*!
	\brief	  Función que comprueba que el Vertice este en el lado 
	\note 	  Funcion inline
	\return	  true si el vertice esta en el lado, false en otro caso
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVerticeB()
*/
	inline bool has(ed::Vertice const u) const {
		if(getVerticeA() == u || getVerticeB() == u){
			return true;
		}
		return false;	
	}

	
/*!
	\brief	  Función que devuelve el otro vertice 
	\note 	  Funcion inline
	\return	  El otro Vertice del pasado como parametro 
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVerticeB()
*/
	inline ed::Vertice otro(ed::Vertice const u) const {
			
			#ifndef NDEBUG
				assert(has(u));
			#endif
				
		if(getVerticeA() == u){	
				
				#ifndef NDEBUG
					assert(has(getVerticeB()));
					assert(otro(getVerticeB()) == u);
				#endif
				
			return _B;
		}
		else if(getVerticeB() == u){
			
				#ifndef NDEBUG
					assert(has(getVerticeA()));
					assert(otro(getVerticeA()) == u);
				#endif
				
			return _A;
		}	
	}

	/*********************************************************/
	
	//!	 \name 	Funciones modificadores de la clase vertice
	
/*!
	\brief 	Función que modifica el atributo distancia de la clase Lado
	\note 	Función inline y redefinida de la clase padre LadoInterfaz
	\param    distancia: de tipo float, representa el nuevo valor de a distancia entre dos puntos
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	getDistancia() == distancia
	\sa 		getDistancia(), getVerticeA(), getVerticeB()
*/
	inline void setDistancia(float distancia){
	
		this->_distancia = distancia;
		
			#ifndef NDEBUG
				assert(getDistancia() == distancia);
			#endif
	}


/*!
	\brief 	Función que modifica el atributo A de tipo Vertice de la clase Lado
	\note 	Función inline y redefinida de la clase padre LadoInterfaz
	\param    A: de tipo Vertice, que representa el nuevo valor del atributo
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	getVerticeA() == A
	\sa 		getDistancia(), getVerticeA(), getVerticeB()
*/
	inline void setVerticeA(ed::Vertice A){
	
		this->_A = A;
		
			#ifndef NDEBUG
				assert(getVerticeA() == A);
			#endif
	}

/*!
	\brief 	Función que modifica el atributo B de tipo Vertice de la clase Lado
	\note 	Función inline y redefinida de la clase padre LadoInterfaz
	\param    B: de tipo Vertice, que representa el nuevo valor del atributo 
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	getVerticeA() == A
	\sa 		getDistancia(), getVerticeA(), getVerticeB()
*/
	inline void setVerticeB(ed::Vertice B){
	
		this->_B = B;
		
			#ifndef NDEBUG
				assert(getVerticeB() == B);
			#endif
	}
		
		

	/******************************************************************/
	
	//!	\name   Operadores de la clase Vertice

/*! 
	\brief     Operador de asignación: operador que "copia" un Lado en otro Lado
	\attention Se sobrecarga el operador de asignación "="
	\note      Función inline
	\warning   Se requiere que las funciones de acceso get tengan el modificar const
	\param     objeto de la clase Lado pasado como referencia constante
	\pre       El objeto es distinto del objeto actual
	\post      getDistancia() == objeto.getDistancia() and getVerticeA() == objeto.getVerticeA() and getVerticeB() == objeto.getVerticeB()
	\sa        setDistancia(), getVerticeA(), getVerticeB(), getDistancia()
*/
	inline Lado & operator=(Lado const & objeto){
		
		// Se comprueba que no sean el mismo objeto
		if (this != &objeto) 
		{
			this->setDistancia(objeto.getDistancia());
			this->setVerticeA(objeto.getVerticeA());
			this->setVerticeB(objeto.getVerticeB());

			#ifndef NDEBUG
	  		// Se comprueba la postcondición
			assert(this->getDistancia() == objeto.getDistancia());
			assert(this->getVerticeA() == objeto.getVerticeA());
			assert(this->getVerticeB() == objeto.getVerticeB());
			#endif //NDEBUG
		}

		return *this;
	}

/*! 
	\brief     Operador de igualdad: compara si dos Lados son iguales
	\attention Se sobrecarga el operador de asignación "=="
	\note      Función inline
	\param     objeto: Lado pasada como referencia constante
	\pre       Ninguna
	\post      Ninguna
	\sa        
*/
	inline bool operator==(Lado const & objeto){
		
		bool valor;
	   
		valor = (this->getDistancia() == objeto.getDistancia() and
			    this->getVerticeA()  == objeto.getVerticeA()  and
			    this->getVerticeB()  == objeto.getVerticeB());
         		    
             #ifndef NDEBUG
	  		// Se comprueba la postcondición
			assert(valor == ((this->getDistancia() == objeto.getDistancia()) and
						  (this->getVerticeA()  == objeto.getVerticeA())  and
						  (this->getVerticeB()  == objeto.getVerticeB())));
			#endif //NDEBUG
		return valor;
	}
	
	


	
	
}; // Fin de la definición de la clase Punto2D

	//! \name Funciones externas de la clase Vertice: sobrecarga de los operadores de flujo
	
	// Sobrecarga del operador de salida
/*!
  	\brief     Sobrecarga del operador de salida o escritura "<<"
	\param     stream Flujo de entrada
	\param     lado: de tipo Lado pasada como referencia
	\pre       Ninguna
	\post      Ninguna
*/
	std::ostream &operator<<(std::ostream &stream, ed::Lado const &lado);
	
}  // \brief Fin de namespace ed.

//  _LADO_HPP_
#endif
