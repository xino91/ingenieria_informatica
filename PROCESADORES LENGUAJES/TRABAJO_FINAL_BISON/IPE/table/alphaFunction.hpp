/*! 
  \file alphaFunction.hpp
  \brief Prototypes of mathematical functions 
*/

#ifndef _ALPHAFUNCTION_HPP_
#define _ALPHAFUNCTION_HPP_

#include <string>

/*!	
	\brief   transforma en minuscula la cadena recibida
	\param	 x: valor de la cadena a convertir
	\return  result: cadena en minuscula
	
*/
std::string transforma(std::string x);
/*!	
	\brief   transforma en minuscula la cadena recibida
	\param	 x: valor de la cadena que debemos converitir
	\param   y: valor del tamaño de la cadena;
	\return  result: cadena en minuscula
	
*/
char* transforma(char* x, int y);



#endif
