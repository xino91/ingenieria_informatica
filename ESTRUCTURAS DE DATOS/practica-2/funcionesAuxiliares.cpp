/*!
  \file   funcionesAuxiliares.cpp
  \brief  Código de las funciones auxiliares del programa principal de la provincia
  \author Antonio Ariza García
  \date   08-04-2018
*/

#include <iostream>
#include <string>  

// Para usar atoi
#include <stdlib.h>

#include "Provincia.hpp"

#include "Municipio.hpp"


#include "funcionesAuxiliares.hpp"


#include "macros.hpp"

int ed::menu()
{
	int opcion;
	int posicion;

	// Se muestran las opciones del menú
	posicion=2;

	// Se borra la pantalla
	std::cout << CLEAR_SCREEN;

	PLACE(1,10);
	std::cout << BIBLUE;
	std::cout << "Programa principial | Opciones del menú";
	std::cout << RESET;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout <<  "[1] Comprobar si la provincia tiene municipios";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[2] Cargar la provincia desde un fichero";

	PLACE(posicion++,10);
	std::cout << "[3] Grabar la provincia en un fichero";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;
 
	PLACE(posicion++,10);
	std::cout << "[4] Consultar datos de la provincia";

	PLACE(posicion++,10);
	std::cout <<  "[5] Mostrar municipios de la provincia";

	PLACE(posicion++,10);
	std::cout << "[6] Modificar datos de la provincia: código o nombre";

	PLACE(posicion++,10);
	std::cout << "[7] Borrar todos los municipios de una provincia";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << "[8] Consultar un municipio";

	PLACE(posicion++,10);
	std::cout << "[9] Insertar un municipio";

	PLACE(posicion++,10);
	std::cout << "[10] Borrar un municipio";
	
	////////////////////////////////////////////////////////////////////////////////
	posicion++;
	
	PLACE(posicion++,10);
	std::cout << "[11] Comparar el número de habitantes entre dos Municipios" << std::endl;

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIRED << "[0] Salir";

	//////////////////////////////////////////////////////////////////////////////
	posicion++;

	PLACE(posicion++,10);
	std::cout << BIGREEN;
	std::cout << "Opción: ";
	std::cout << RESET;

	// Se lee el número de opción
	std::cin >> opcion;

    // Se elimina el salto de línea del flujo de entrada
    std::cin.ignore();

	return opcion;
}


//////////////////////////////////////////////////////////////////////////////

void ed::comprobarProvinciaVacia(ed::Provincia &provincia)
{
	std::cout<<std::endl;
	
		if(provincia.hayMunicipios()){
			std::cout<<  BIGREEN <<"La provincia TIENE MUNICIPIOS"<<std::endl;
		}
		else{	
			std::cout<< BIRED <<"La provincia NO TIENE MUNICIPIOS"<<std::endl;
		}
	return;
}

//////////////////////////////////////////////////////////////////////////////

void ed::cargarProvincia(ed::Provincia &provincia)
{
	 std::cout << std::endl;
	 std::string nombre;
	 std::cout << BIBLUE << "Introduzca el nombre de la provincia" << RESET << std::endl;
	 getline(std::cin, nombre);
	 
	 
	 
	 if(provincia.hayMunicipios()==false){
		if(provincia.cargarFichero(nombre)==true){
			std::cout<< BIGREEN <<"Fichero cargado correctamente"<<std::endl;
			return;
		}
		else{
			std::cout<< BIRED <<"Error al cargar  Provincia desde el Fichero"<< std::endl;
			return;
		}
	}
	else{
	
		int opcion;
		
			std::cout << BIBLUE << "Ya hay una Provincia Cargada" << RESET << std::endl;
			std::cout << BIYELLOW  << "Nombre de la provincia: "  << RESET 
				 	 << provincia.getNombre() << std::endl; 
			std::cout << BIYELLOW << "Código de la provincia: " << RESET
				 	 << provincia.getCodigo() << std::endl  << std::endl;
		
		do{
			std::cout << BIBLUE << "Indique qué desea hacer" << RESET << std::endl;
			std::cout << "[1] Borrar y cargar una nueva " << std::endl;
			std::cout << "[0] Salir" << std::endl  << std::endl;
			
			std::cout << BIGREEN;
			std::cout << "Opción: ";
			std::cout << RESET;
	
			// Se lee el número de opción
			std::cin >> opcion;
	
			// Se elimina el salto de línea del flujo de entrada
	    		std::cin.ignore();

			std::cout << std::endl;	
				
			switch(opcion)
			{
				case 1:
							borrarTodosLosMunicipiosDeProvincia(provincia);
							if(provincia.cargarFichero(nombre)==true){
								std::cout<< BIGREEN <<"Fichero cargado correctamente"<<std::endl;
								return;
							}
							else{
								std::cout<< BIRED <<"Error al cargar  Provincia desde el Fichero"<< std::endl;
							}
						break;
	
				case 0:
					     break;
					     
				default:
						std::cout << BIRED << "Opción incorrecta:" << RESET << opcion << std::endl;
			}
		}while (opcion!=0);

	}
		
		return;
}


//////////////////////////////////////////////////////////////////////////////////////

void ed::grabarProvincia(ed::Provincia  &provincia)
{

	if(provincia.hayMunicipios()==true){	
	
	std::string nombreFich;
	std::cout << std::endl;
	std::cout << BIYELLOW << "Introduzca el nombre del fichero" << RESET << std::endl;
	getline(std::cin,nombreFich);
	
	provincia.grabarFichero(nombreFich);
	}
	else{
		std::cout << BIRED << "No se puede grabarFichero, lista vacía" << RESET << std::endl;
	}
	return;
}

//////////////////////////////////////////////////////////////////////

void ed::consultarDatosDeProvincia(ed::Provincia &provincia)
{

	std::cout << std::endl;

	if(provincia.getNombre()=="" and provincia.getCodigo()==0){
		std::cout << BIRED << "La Provincia está vacía" << RESET << std::endl;
		return;
	}

	if(provincia.hayMunicipios()==true){
	
	std::cout << BIYELLOW << "Nombre: "			<< RESET 	<< provincia.getNombre() << std::endl;
	std::cout << BIYELLOW << "Codigo: "			<< RESET 	<< provincia.getCodigo() << std::endl;
	std::cout << BIBLUE   << "Numero de Municipios: " << RESET  << provincia.getNumeroMunicipios() << std::endl;
	std::cout << BIBLUE   << "Total de Hombres: "	<< RESET 	<< provincia.getTotalHombres() << std::endl;
	std::cout << BIBLUE   << "Total de Mujeres: "	<< RESET 	<< provincia.getTotalMujeres() << std::endl;
	std::cout << BIBLUE   << "Total de Habitantes: "	<< RESET 	<< provincia.getTotalHabitantes() << std::endl;
	
	}
	else{
		std::cout << std::endl;
		std::cout << BIYELLOW << "Provincia: " << RESET << provincia.getNombre() << std::endl;
		std::cout << BIYELLOW << "Codigo: " << RESET << provincia.getCodigo() << std::endl;
		std::cout << BIRED << "No se puede consultar datos, la Provincia esta Vacía" << RESET << std::endl;
	}
	return;
}


////////////////////////////////////////////////////////////////

void ed::mostrarMunicipiosDeProvincia(ed::Provincia & provincia)
{
	std::cout << std::endl;
	
	if(provincia.hayMunicipios() == true){
	
		provincia.escribirMunicipios();	
	}
	else{
		
		std::cout << std::endl;
		std::cout << BIRED << "La Provincia está Vacía" << RESET << std::endl;
	}
	return;
}


////////////////////////////////////////////////////////////////////////

void ed::modificarDatosDeProvincia(ed::Provincia &provincia)
{

std::cout << std::endl;

	int opcion, codigo;
	std::string nombre; 

	do{
		std::cout << BIYELLOW  << "Nombre de la provincia: "  << RESET 
				  << provincia.getNombre() << std::endl; 
		std::cout << BIYELLOW << "Código de la provincia: " << RESET
				  << provincia.getCodigo() << std::endl  << std::endl;

		std::cout << "Indique qué dato desea modificar: " << std::endl;
		std::cout << BIBLUE << "(1) Nombre " << std::endl;
		std::cout << BIBLUE << "(2) Código" << std::endl  << std::endl;
		std::cout << BIRED << "(0) Salir" << std::endl << std::endl  << std::endl;
		std::cout << BIGREEN;
		std::cout << "Opción: ";
		std::cout << RESET;

		// Se lee el número de opción
		std::cin >> opcion;

    	// Se elimina el salto de línea del flujo de entrada
	    std::cin.ignore();

		std::cout << std::endl;
			
		switch(opcion)
		{
			case 0: 
					// Fin de las modificaciones
					break;
			case 1:
					std::cout << BIGREEN;
					std::cout << "Nuevo nombre de la provincia: ";
					std::cout << RESET;
					std::getline(std::cin,nombre);
					provincia.setNombre(nombre);
					break;

			case 2:
					std::cout << BIGREEN;
					std::cout << "Nuevo código de la provincia: ";
					std::cout << RESET;
					std::cin >> codigo;
					provincia.setCodigo(codigo);
					break;
			default:
					std::cout << BIRED << "Opción incorrecta:" << RESET 
							  << opcion << std::endl;
		}
	}while (opcion != 0);

	return;
}


void ed::borrarTodosLosMunicipiosDeProvincia(ed::Provincia &provincia)
{
	std::cout << std::endl;

	provincia.borrarTodosLosMunicipios();
	
	if(provincia.hayMunicipios()==false){
		std::cout << BIGREEN << "Todos los Municipios borrados" << RESET << std::endl << std::endl;
	}
	else{
		std::cout << BIRED   << "Error al Borrar todos los Municipios" << std::endl << std::endl;
	}
	
	return;
}


void ed::consultarMunicipioDeProvincia(ed::Provincia &provincia)
{
	std::cout << std::endl;
	std::string nombre;
	
	std::cout << BIBLUE << "Introduzca el nombre del Municipio" << RESET << std::endl;
	std::cout << BIYELLOW << "Nombre: --> " << RESET;
	
	getline(std::cin, nombre);
	//Si la primera letra es minúscula la convertimos a mayúscula
	if(islower(nombre[0])!=0){
		nombre[0] = toupper(nombre[0]);
	}
	std::cout << BIYELLOW << "Buscando --> " << RESET << nombre << std::endl << std::endl;
	
		if(provincia.existeMunicipio(nombre)){
			std::cout << BIBLUE << "¿Existe Municipio?" << RESET << std::endl;
			std::cout << BIGREEN <<"El Municipio " << RESET << nombre << BIGREEN <<" SI Existe" << RESET << std::endl << std::endl;
			provincia.getMunicipio(nombre).escribirMunicipio();
		}
		else{
			std::cout << BIRED << "El Municipio " << RESET << nombre << BIRED <<" NO existe" << RESET << std::endl << std::endl;
		}
	return;
}

void ed::insertarMunicipioEnProvincia(ed::Provincia &provincia)
{

	
		std::cout << std::endl;
		std::string aux;
		int n;
		Municipio m;
		
		//-----------NOMBRE----------------
		std::cout << BIBLUE << "Introduzca el nombre del municipio: " << RESET << std::endl;
		std::cout << BIYELLOW << "Nombre: --> " << RESET;  
		getline(std::cin,aux);
		//Si la primera letra es minúscula la convertimos a mayúscula para que la inserte de forma ordenada
		if(islower(aux[0])!=0){
			aux[0] = toupper(aux[0]);
		}
		m.setNombre(aux);
		
		//-----------CODIGO POSTAL-----------
		std::cout << BIBLUE << "Introduzca el Codigo Postal del Municipio: " << RESET << std::endl;
		std::cout << BIYELLOW << "Codigo Postal --> " << RESET;
		std::cin >> n;
		m.setCodigoPostal(n);
		
		//-----------HOMBRES----------------
		std::cout << BIBLUE << "Introduzca el numero de Hombres del Municipio: " << RESET << std::endl;
		std::cout << BIYELLOW << "Numero Hombres --> " << RESET;
		std::cin >> n;
		m.setHombres(n);
		
		//-----------MUJERES----------------
		std::cout << BIBLUE << "Introduzca el numero de Mujeres del Municipio: " << RESET << std::endl;
		std::cout << BIYELLOW << "Numero Mujeres --> " << RESET;
		std::cin >> n;
		m.setMujeres(n);
		
			if (provincia.existeMunicipio(m.getNombre())==true){
				std::cout << BIRED << "Este Municipio YA EXISTE no se puede insertar" << RESET << std::endl;
				// Pausa
				std::cin.ignore();
			}
			else{
				provincia.insertarMunicipio(m); 
			}
		   
	return;
}

  


void ed::borrarMunicipioDeProvincia(ed::Provincia &provincia)
{
	std::cout << std::endl;
	
	if(provincia.hayMunicipios() == true){
	
		std::string nombre;
	
		std::cout << BIBLUE << "Introduzca el nombre del Municipio" << RESET << std::endl;
		std::cout << BIYELLOW << "Nombre --> " << RESET;
		getline(std::cin, nombre);
	
			if(provincia.existeMunicipio(nombre) == true){		
				provincia.borrarMunicipio(nombre);
			}
			else{
				std::cout << BIRED << "El Municipio " << RESET << nombre << BIRED <<" NO existe" << RESET << std::endl << std::endl;
			}
	}
	else{
		std::cout << BIRED << "La Provincia esta Vacía" << RESET << std::endl;
	}

	return;
}


void ed::compararHabitantesMunicipios(ed::Provincia & provincia){

	std::cout << std::endl;
	
	if(provincia.hayMunicipios() == true){
		
		std::string nombre1, nombre2;
		Municipio m1, m2;
		
		std::cout << BIBLUE << "Introduzca el nombre de dos Municipios" << RESET << std::endl;
		std::cout << BIYELLOW << "Municipio 1: --> " << RESET;
		getline(std::cin, nombre1);
		std::cout << BIYELLOW << "Municipio 2: --> " << RESET;
		getline(std::cin, nombre2);
		
		if(provincia.existeMunicipio(nombre1) == true and provincia.existeMunicipio(nombre2) == true ){
			//std::cout << BIBLUE << "Municipio 1: " << RESET << nombre1 << std::endl;
			//std::cout << BIBLUE << "Municipio 2: " << RESET << nombre2 << std::endl;
			//Guardamos Municipios
			m1=provincia.getMunicipio(nombre1);
			m2=provincia.getMunicipio(nombre2);
			
			if( nombre1 == nombre2){
				std::cout << BIRED << "No se puede comparar cual es mayor, son el mismo Municipio" << std::endl;
			}
			else{
			
				if (comparar(m1,m2) == true){
					std::cout << BIGREEN << "El Municipio " << RESET << m2.getNombre()
					          << BIGREEN << " tiene mas Habitantes que " << RESET << m1.getNombre() << std::endl;
				}
				else{
				
					if( m1.getHabitantes() == m2.getHabitantes()){
						std::cout << BIGREEN << "Tienen los mismos Habitantes " << RESET << std::endl;
					}
					else{ 
						std::cout << BIGREEN << "El Municipio " << RESET << m1.getNombre() 
						     << BIGREEN << " tiene mas Habitantes que " << RESET << m2.getNombre() << std::endl;
					}
				}
			}
		}
		else{
			
			std::cout << BIRED << "Alguno de los Municipios no existe, vuelva a intentarlo consideando las tildes y Mayúsculas" << RESET << std::endl;
		}
				
	}
	else{
		std::cout << BIRED << "No Podemos comparar Municipios, LA LISTA ESTA VACÍA" << RESET << std::endl;
	}	
		
}

	




