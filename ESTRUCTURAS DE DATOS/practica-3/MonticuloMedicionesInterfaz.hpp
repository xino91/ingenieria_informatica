/*!
	\file MonticuloMedicionesInterfaz.hpp
	\brief Se define la interfaz del TAD MonticuloMediciones.
	\author 
	\date  
*/

#ifndef _MONTICULO_MEDICIONES_INTERFAZ_HPP
#define _MONTICULO_MEDICIONES_INTERFAZ_HPP

#include "Medicion.hpp"

/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed
{

	/*!	
  		\class MonticuloMedicionesInterfaz 
  		\brief Definición de la clase abstracta MonticuloMedicionesInterfaz
		\n     Montículo de mediciones de precipitaciones por días
	*/
	class MonticuloMedicionesInterfaz
	{
		public: 

			//!	\name Observadores públicos
			
		/*!
			\brief	Devuelve verdadero si no tienes mediciones; falso en caso contrario
			\note	Función virtual pura que deberá ser redefinada en la clase heredera
			\note	Función de tipo const, no puede modificar al objeto actual
			\return	true, si no tiene mediciones, falso en caso contrario
			\sa 		top(), insert(), remove()
		*/
		virtual bool isEmpty() const = 0; 
		
		/*********************************************************/
		/*!
			\brief	Devuelve la cima del montículo
			\note 	Funcion virtual pura que deberá ser redefinida en la clase heredera
			\note	Función de tipo const, no puede modificar al objeto actual
			\return 	Devuelve una medición, que será la cima del montículo
			\pre	 	isEmtpy() == false
			\post	Ninguna
			\sa 	 	isEmpty(), remove(), insert()
		*/
		virtual ed::Medicion top() const = 0;
		
		/////////////////////////////////////////////////////////////////////
		
			//! name Modificadores públicos
		/*!
			\brief 	Inserta una nueva Medición en el montículo
			\note 	Función virtual pura que deberá ser redefinida en la clase heredera
			\param    medicion: de tipo Medicion, representa la medicion nueva a insertar
			\return   Nada, es de tipo void
			\pre		Ninguna
			\post 	isEmpty() ==false
			\sa 		top(), isEmpty(), remove()
		*/
		virtual void insert(ed::Medicion medicion) =0;
		
		/*************************************************************************/
		/*!
			\brief 	Borra la medición que ocupa la cima
			\note 	Función virtual pura que deberá ser redefinida en la clase heredera
			\return 	Nada, es de tipo void
			\pre		isEmpty() == false
			\post	Ninguna
			\		insert(), isEmpty(), top()
		*/
		virtual void remove() =0;

	}; // Clase MonticuloMedicionesInterfaz

} // Espacio de nombres ed

#endif //  _MONTICULO_MEDICIONES_INTERFAZ_HPP
