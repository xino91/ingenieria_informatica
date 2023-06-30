/*! 
   \file Medicion.hpp
   \brief Fichero de la clase Medicion: medición de una estación meteorológica 
*/

#ifndef _MEDICION_HPP_
#define _MEDICION_HPP_

// Entrada y salida 
#include <iostream>
#include <cmath>

// Para controlar las precondiciones y postcondiciones mediante asertos
#include <cassert>

// Definición de la clase Fecha
#include "Fecha.hpp"


// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación de números reales


// Se incluye la clase Medicion dentro del espacio de nombres de la asigantura: ed
namespace ed {

//!  Definición de la clase Medicion 
class Medicion
{
  //! \name Atributos privados de la clase Medicion
   private: 

	Fecha _fecha;			//!< Fecha con formato dia,mes,año
	float _precipitacion;	//!< Medición de precipitación

   //! \name Funciones o métodos públicos de la clase Medicion
   public:

	//! \name Constructor de la clase Medicion
/*! 
	\brief     Constructor parametrizado con valores por defecto       
	\note      Función inline
	\param     fecha: valor por defecto (1,1,1)
	\param     precipitacion: valor por defecto 0.0
	\pre       Ninguna
	\post      getFecha() == fecha
	\post	 getPrecipitacion() == precipitacion
	\sa        getFecha(), getPrecipitacion()
*/
	inline Medicion(ed::Fecha fecha = Fecha(1,1,1), float precipitacion=0.0){
		
			_fecha = fecha;
			_precipitacion = precipitacion;
			
				#ifndef NDEBUG
					assert(this->getFecha() == fecha);
					assert(std::abs(this->getPrecipitacion() - precipitacion) < COTA_ERROR);
				#endif
	}	
	
	/****************************************************************/
/*!
	\brief	Constructor de copia, crea una medicion a partir de otra medición
	\note 	Función inline
	\warning  Se requiere que las funciones getFecha y getPrecipitaciones tengan el modificador const
	\param 	medicion: De tipo Medicion Pasada como referencia const
	\pre 	Ninguna
	\post 	getFecha() == medicion.getFecha()
	\post 	getPrecipitaciones() == medicion.getPrecipitaciones()
*/
	inline Medicion(Medicion const & medicion){
	
		this->setFecha(medicion.getFecha());
		this->setPrecipitacion(medicion.getPrecipitacion());
		
			#ifndef NDEBUG
				assert(this->getFecha() == medicion.getFecha());
				assert(std::abs(this->getPrecipitacion() - medicion.getPrecipitacion()) < COTA_ERROR);
			#endif
	}
	
	
	/**************************************************************************/
	/**************************************************************************/

	//! \name Observadores: funciones de consulta de la clase Medicion
	/*******************************************************************/
/*!
	\brief	  Observador publico de Fecha
	\note 	  Función inline
	\attention  Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
	\return     Devuelve valor del atributo que representa a fecha de tipo Fecha
	\sa 		  getPrecipitaciones()
*/
	inline Fecha getFecha()const {return _fecha;}
	
	/*******************************************************************/
/*!
	\brief	  Observador publico de Precipitacion
	\note 	  Función inline
	\attention  Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
	\return     Devuelve valor del atributo que representa a precipitacion de tipo float
	\sa 		  getFecha()
*/
	inline float getPrecipitacion()const {return _precipitacion;}


	//! \name Funciones de modificación de la clase Medición
	/*******************************************************************/
/*!
	\brief 	Función modificador público para la fecha
	\note 	Función inline
	\param 	fecha: de tipo Fecha, para asignar nueva fecha a la medición
	\return  Nada, es de tipo void
	\post	getFecha() == fecha
	\sa 		getFecha(), setPrecipitacion()
*/
	inline void setFecha(ed::Fecha fecha){
		_fecha = fecha;
		
		#ifndef NDEBUG
			assert(this->getFecha() == fecha);
		#endif	
	}
	
	/******************************************************************/
/*!
	\brief 	Función modificador público para la fecha
	\note 	Función inline
	\param	precipitacion: de tipo float, para asignar nueva precipitacion de lluvia a la medicion
	\return	Nada, es de tipo void
	\post	getPrecipitacion() == precipitacion
	\sa	 	getPrecipitacion(), settFecha()
*/
	inline void setPrecipitacion(float precipitacion){
		_precipitacion = precipitacion;
		
		#ifndef NDEBUG
			assert(this->getPrecipitacion() == precipitacion);
		#endif
	}

	//! \name Operadores
   
	/******************************************************************/
/*!
	\brief	 Operador de igualdad que compara las fechas de dos mediciones
	\note 	 Función inline
	\attention Se sobrecarga el operador de igualdad ==
	\param  	 medicion: de tipo Medicion pasada como referancia const
	\return    true  si son iguales, false en otro caso
	\sa 	 	 Operador=, getFecha(), getPrecipitacion()
*/	
	inline bool operator==(ed::Medicion const & medicion){
		
		bool valordevuelto;
		
		valordevuelto = (this->getFecha() == medicion.getFecha());
			
			#ifndef NDEBUG
				assert(valordevuelto == (getFecha() == medicion.getFecha()));
			#endif
		
		return valordevuelto;
	}

	/*****************************************************************/
/*! 
	\brief     Operador de asignación: operador que "copia" la medicion actual con los atributos de otra medición
	\attention Se sobrecarga el operador de asignación "="
	\note      Función inline
	\warning   Se requiere que las funciones de acceso getFecha y getPrecipitaciones tengan modificador const
	\param     medicion: de tipo Medicion pasada como referencia const
	\pre 	 Ninguna
	\post      getFecha() == medicion.getFecha()
	\post	 getPrecipitacion() == medicion.getPrecipitacion()
	\sa        getFecha(), getPrecipitacion(), operador==
*/
	inline ed::Medicion & operator=(ed::Medicion const & medicion){

		if (this != & medicion){
			this->setFecha(medicion.getFecha());		
			this->setPrecipitacion(medicion.getPrecipitacion());
		}
		
			#ifndef NDEBUG
				assert(this->getFecha() == medicion.getFecha());
				assert(this->getPrecipitacion() == medicion.getPrecipitacion());
			#endif
			
		return *this;
	}

	inline bool operator!=(ed::Medicion const & m ){
		
		if( this->getFecha() != m.getFecha()){
			return true;
		}
		return false;
	}
		
	//! \name Funciones públicas de lectura y escritura de la clase Medicion
	/************************************************************************/
/*! 
	\brief   Lee desde el teclado una medición
	\warning Se deben teclear números
	\pre     Ninguna
	\post    Ninguna
	\sa      setFecha(), setPrecipitacion(), escribirMedicion()
*/
	bool leerMedicion();
	
	/*********************************************************************/
/*!
	\brief	Escribe una medición desde teclado
	\pre		Ninguna
	\post	Ninguna
	\sa 		leerMedicion();
*/
	void escribirMedicion();


}; // Fin de la definición de la clase Medicion


   //! \name Funciones externas de la clase Medicion: sobrecarga de los operadores de flujo
	
/*!
  	\brief     Sobrecarga del operador de salida o escritura "<<"
	\n 		 Se escribe la medicion por pantalla con el formato (d)d-(m)m--aaaa 0.0
	\param     stream Flujo de salida
	\param     medicion: de tipo Medicion pasada como referencia constante
	\pre       Ninguna
	\post      Ninguna
	\sa        operator>>()
*/
	ostream &operator<<(ostream &stream, ed::Medicion const &medicion);
	
	/********************************************************************/
/*!
  	\brief     Sobrecarga del operador de entrada o lectura ">>"
	\param     stream Flujo de entrada
	\param     medicion: de tipo medicion pasada como referencia
	\pre       Ninguna
	\post      Ninguna
	\sa        operator<<()
*/
	istream &operator>>(istream &stream, ed::Medicion &medicion);
	
	



} // \brief Fin de namespace ed.

//  _MEDICION_HPP_
#endif 
