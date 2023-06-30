/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 3
  \author 
  \date  
*/

#ifndef _FuncionesAuxiliares_HPP_
#define _FuncionesAuxiliares_HPP_

#include "MonticuloMediciones.hpp"

/*!	
	\namespace ed
	\brief Espacio de nombres para la Provincia Estructuras de Datos

*/

namespace ed
{

/*!
	\brief	 Carga el monticulo desde un fichero 
	\param     nombreFichero: Referencia al nombre del fichero de tipo string
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediciones
	\return    true, en caso de éxito, false en otro caso
	\sa	      grabarMonticuloEnFichero()
*/
	bool cargarMonticuloDeFichero(std::string const & nombreFichero, ed::MonticuloMediciones & monticulo); 

/*!
	\brief	 Grabado el monticulo desde un fichero 
	\param     nombreFichero: Referencia al nombre del fichero de tipo string
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediciones
	\return    true, en caso de éxito, false en otro caso
	\sa	      cargarMonticuloDeFichero()
*/
	bool grabarMonticuloEnFichero (std::string const & nombreFichero, ed::MonticuloMediciones const & monticulo); 


} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FuncionesAuxiliares_HPP_
#endif

