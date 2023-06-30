/*! 
  \file alphaFunction.cpp
  \brief Code of alpha functions 
*/


#include <iostream>

#include <string>

#include "alphaFunction.hpp"

// errcheck
#include "../error/error.hpp"

std::string transforma(std::string x)
{
	std::string minuscula(x);



	for(unsigned i=0; i < minuscula.length(); i++){
		minuscula[i]= tolower(minuscula[i]);
						  	
						  }
//devolvemos la misma cadena pero en minuscula
 return minuscula;
 }
char* transforma(char* x, int y)
{
	char* minuscula=x;
	
	for(int i=0; i < y; i++){
		minuscula[i]= tolower(minuscula[i]);
						  	
						  }
//devolvemos la misma cadena pero en minuscula
 return minuscula;
 }







