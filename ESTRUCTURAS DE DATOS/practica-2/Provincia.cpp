/*!	

	\file    Provincia.cpp
	\brief   Definición de la clase Provincia
	\author  Antonio Ariza García
	\date    08-04-2018
	\version 1.0

*/
//Para los flujos de entrada/salida en ficheros.
#include <fstream>  
#include <iostream>
#include <cstdlib>

// Para comprobar las pre y post condiciones
#include <cassert>

#include "Provincia.hpp"
#include "macros.hpp"


// DEBES CODIFICAR LAS FUNCIONES DE LA CLASE Provincia

///////////////////////////////////////////////////////////////////////////////

// OSBSERVADORES

bool ed::Provincia::existeMunicipio(std::string nombre){
	
	//std::cout << BIBLUE << "¿Existe Municipio?" << RESET << std::endl;
	//Comprobamos que la Lista no este vacía para no crear una violacion de segmento con el gotoHead
	if(_listaMunicipios.isEmpty()==false){
	
		this->_listaMunicipios.gotoHead();
	
		while(this->_listaMunicipios.getCurrentItem().getNombre()!=nombre and this->_listaMunicipios.isLastItem()==false){
	
			this->_listaMunicipios.gotoNext();
		}
		
			if(this->_listaMunicipios.getCurrentItem().getNombre()==nombre){
		
				//std::cout << BIGREEN <<"El Municipio " << RESET << nombre << BIGREEN <<" SI Existe" << RESET << std::endl;
				return true;
			}
			else{
				//std::cout << BIRED << "El Municipio " << RESET << nombre << BIRED <<" NO existe" << RESET << std::endl;
				return false;
			}
	}
	else{
		std::cout << BIRED << "No existe el municipio " << RESET << nombre << BIRED << ", La lista está Vacía" << std::endl;
		return false;
	} 
}


ed::Municipio ed::Provincia::getMunicipio(std::string nombre){


		#ifndef NDEBUG
			assert(existeMunicipio(nombre)==true);
		#endif
	
	existeMunicipio(nombre); //Dejamos el cursor en el municipio que buscamos
	
	return _listaMunicipios.getCurrentItem();
}


int ed::Provincia::getTotalHombres(){
	
	int totalhombres=0;
	
	this->_listaMunicipios.gotoHead();
	
		while(this->_listaMunicipios.isLastItem()==false){
		
			totalhombres += _listaMunicipios.getCurrentItem().getHombres();
			this->_listaMunicipios.gotoNext();
		}
		
		//Al salir nos quedará por comprobar el ultimo elemento ya que no entrará al bucle
		if(this->_listaMunicipios.isLastItem()==true){
			
			totalhombres = totalhombres + _listaMunicipios.getCurrentItem().getHombres();
		}
		
		return totalhombres;
}	


int ed::Provincia::getTotalMujeres(){

	int totalmujeres=0;
	
	this->_listaMunicipios.gotoHead();
	
		while(this->_listaMunicipios.isLastItem()==false){
		
			totalmujeres += _listaMunicipios.getCurrentItem().getMujeres();
			this->_listaMunicipios.gotoNext();
		}
		
		//Al salir nos quedará por comprobar el ultimo elemento ya que no entrará al bucle
		if(this->_listaMunicipios.isLastItem()==true){
			
			totalmujeres = totalmujeres + _listaMunicipios.getCurrentItem().getMujeres();
		}
		
		return totalmujeres;
}	

/////////////////////////////////////////////////////////////////////////////////////////

// MODIFICADORES

void ed::Provincia::insertarMunicipio(ed::Municipio const municipio){

			#ifndef NDEBUG
				assert(existeMunicipio(municipio.getNombre())==false);
				int numero= getNumeroMunicipios();
			#endif
		
		this->_listaMunicipios.insert(municipio);	
		
			#ifndef NDEBUG
				assert(existeMunicipio(municipio.getNombre()) == true);
				assert(getNumeroMunicipios() == numero +1);
			#endif
}


void ed::Provincia::borrarMunicipio(std::string nombre){

		#ifndef NDEBUG
			assert(existeMunicipio(nombre) == true);
			int numero= getNumeroMunicipios();
		#endif
	
	existeMunicipio(nombre);  //Dejamos el cursor en el municipio que queremos borrar
	this->_listaMunicipios.remove(); 			 //Eliminamos el municipio con ese nombre
	
		#ifndef NDEBUG
			assert(existeMunicipio(nombre) ==false);
			assert(getNumeroMunicipios() == numero -1);
		#endif

}

void ed::Provincia::borrarTodosLosMunicipios(){

	this->_listaMunicipios.removeAll();
	
		#ifndef NDEBUG
			assert(hayMunicipios() == false);
		#endif
}
	
	
	
	
	
	
	

///////////////////////////////////////////////////////////////////////////////////

// FUNCIÓN DE ESCRITURA

void ed::Provincia::escribirMunicipios(){

	std::cout << BIBLUE <<"Datos de la Provincia"<< RESET << std::endl;
	std::cout << BIYELLOW <<"Provincia: "<< RESET << this->getNombre()<<std::endl;
	std::cout << BIYELLOW <<"Codigo: "   << RESET << this->getCodigo()<<std::endl<<std::endl;

	if(_listaMunicipios.isEmpty()==false){
		this->_listaMunicipios.gotoHead();	
	
		std::cout << BIBLUE <<"\t\tDatos de los Municipios\t\t"<< RESET << std::endl;
		while(_listaMunicipios.isLastItem()!=true){
	
			this->_listaMunicipios.getCurrentItem().escribirMunicipio();
			this->_listaMunicipios.gotoNext();
		}
	
	//Salimos porque estamos en el ultimo elemento, pero debemos imprimirlo también
	this->_listaMunicipios.getCurrentItem().escribirMunicipio();
	}
	else{
		std::cout << BIBLUE <<"\t\tDatos de los Municipios\t\t"<< RESET << std::endl;
		std::cout << BIRED  <<"\t\tProvincia Vacía\t\t" << RESET << std::endl;
	}
}
		


/////////////////////////////////////////////////////////////////////////////////////////

// OPERACIONES CON FICHEROS

bool ed::Provincia::cargarFichero(std::string nombre){

	Municipio m;
	char linea[256];
	
	std::cout << nombre << std::endl;
	
	std::ifstream fich(nombre.c_str());
	
		if(fich.is_open()){
	
			fich.getline(linea,256,' ');
			this->setCodigo(atoi(linea));
				
			fich.getline(linea, 256,'\n');
			this->setNombre(linea);
			
			while(fich >> m)
			{
				std::cout << BIYELLOW << "Municipio a insertar --> " << RESET << m << std::endl;
				this->_listaMunicipios.insert(m);
			}
		
		}
		else{
			std::cout << BIRED <<"No se ha podido abrir el fichero"  << RESET <<std::endl;
			return false;
		}
		
	fich.close();
	return true;
}
	

bool ed::Provincia::grabarFichero(std::string nombre){

	Municipio m;
	std::ofstream fich(nombre.c_str());
	
	if(fich.is_open()){
		
		fich << getCodigo() << " " << getNombre() << std::endl;
		
		//Current al primer elemento
		_listaMunicipios.gotoHead();
		
		while(_listaMunicipios.isLastItem()!=true){

			fich << _listaMunicipios.getCurrentItem() << std::endl;
			std::cout << BIYELLOW << "Municipio grabado: " << RESET << _listaMunicipios.getCurrentItem() << std::endl;
			_listaMunicipios.gotoNext();
		}
		
		//Salimos pero tenemos que grabar el ultimo elemento
		std::cout << BIYELLOW << "Municipio grabado: " << RESET << _listaMunicipios.getCurrentItem() << std::endl;
		fich << _listaMunicipios.getCurrentItem() << std::endl;
	}
	else{
		std::cout << "ERROR al abrir el fichero"<<std::endl;
		return false;
	}
	
	fich.close();
	return true;
}
	
	
	







