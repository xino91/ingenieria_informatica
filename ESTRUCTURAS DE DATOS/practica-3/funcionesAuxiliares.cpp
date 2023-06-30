/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares para el programa principal de la práctica 3
  \author Antonio Ariza García
  \date   05-05-2018
*/


#include <iostream>

#include <fstream>

#include <string>

#include "funcionesAuxiliares.hpp"

          
#include "MonticuloMediciones.hpp"

#include "Medicion.hpp"

#include "macros.hpp"

bool ed::cargarMonticuloDeFichero(std::string const & nombreFichero, ed::MonticuloMediciones & monticulo) 
{
 	
 	std::ifstream fich(nombreFichero.c_str(), std::ios::in);
 	Medicion m;
 	
 	if(fich.is_open()){
 		
 		while(fich >> m){
 			monticulo.insert(m);
 			//std::cout << m << " " << monticulo.size() << std::endl;
 		}
 	}
 	else{
 		std::cout << BIRED << "Error al abrir el fichero" << RESET << nombreFichero << std::endl;
 		return false;
 	}
 	
	fich.close();
	
	return true;
}


bool ed::grabarMonticuloEnFichero(std::string const & nombreFichero, 
							      ed::MonticuloMediciones const & monticulo)
{
  int i;
  
  std::ofstream fich(nombreFichero.c_str());
  
  if(fich.is_open()){
  	
  	
  	for(i=0; i < monticulo.size(); i++){
  	
  		fich << monticulo.getMedicion(i);
  		fich << std::endl;
  	}
  }
  else{
  	std::cout << BIRED << "Error al abrir el fichero " << RESET << nombreFichero << std::endl;
  	return false;
  }
  
  fich.close();
  
  return true;
}

 


