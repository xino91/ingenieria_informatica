/*!	
	\file    Provincia.hpp
	\brief   Definición de la clase Provincia
	\author  Antonio Ariza García	
	\date    08-04-2018
	\version 
*/

#ifndef _PROVINCIA_HPP_
#define _PROVINCIA_HPP_

// Para comprobar las pre y post condiciones
#include <cassert>

#include <string>


#include "ListaDoblementeEnlazadaOrdenadaMunicipios.hpp"


// DEBES COMPLETAR O MODIFICAR EL CÓDIGO DE LA CLASE Provincia

// DEBES COMPLETAR LOS COMENTARIOS DE DOXYGEN

// IMPORTANTE
// Se incluyen los prototipos de las funciones virtuales que hay que redefinir
// Hay que incluir los prototipos de las demás funciones


/*!	
	\namespace ed
	\brief Espacio de nombres para la Provincia Estructuras de Datos

*/
namespace ed{
/*!	

  \class Provincia
  \brief Definición de la clase Provincia

*/
class Provincia
{
	//!	\name Métodos públicos de la clase Provincia

	private:
		std::string      _nombre;     //!<  \brief Nombre de la Provincia
		int              _codigo;	  //!<  \brief Código de la Provincia

	  	ed::ListaDoblementeEnlazadaOrdenadaMunicipios _listaMunicipios; //!<  \brief Lista de municipios de la Provincia


	/////////////////////////////////////////////////////////////////////

	//!	\name  Métodos públicos de la clase Provincia

  public: 

	//!	\name Constructor
/*! 
	\brief     Constructor parametrizado con valores por defecto
	\attention Función sobrecargada        
	\note      Función inline
	\param     nombre: de tipo string, valor por defecto ""
	\param     codigo: de tipo int, valor por defecto 0
	\pre       Ninguna
	\post      Ninguna
	\sa        getNombre(), getCodigo(), hayMunicipios()
*/
	inline Provincia(std::string nombre="", int codigo=0){
		
			_nombre=nombre;
			_codigo=codigo;
			
			
				#ifndef NDEBUG
					assert(getNombre() == nombre);
					assert(getCodigo() == codigo);
					assert(hayMunicipios() == false);
				#endif
	}
	

	/////////////////////////////////////////////////////////////////////

	//!	\name Observadores
/*! 
	\brief   Función que devuelve el nombre de la Provincia
	\attention Se utiliza el modificador const en la definición de la función
	\note    Función inline
	\return  string: Nombre del municipio
	\pre     Ninguna
	\post    Ninguna
*/	
	inline std::string getNombre()const{return _nombre;};
	
	/**************************************************************************/
/*! 
	\brief   Función que devuelve el codigo de la Provincia
	\attention Se utiliza el modificador const en la definición de la función
	\note    Función inline
	\return  int: Codigo del municipio
	\pre     Ninguna
	\post    Ninguna
*/
	inline int getCodigo()const{return _codigo;};

	
	/***************************************************************************/
/*! 
	\brief   Función que devuelve si una provincia tiene Municipios
	\attention Se utiliza el modificador const en la definición de la función
	\note    Función inline
	\return  bool: true si hay Muncicipios, false en otro caso
	\pre     Ninguna
	\post    Ninguna
	\sa      isEmpty()
*/
	inline bool hayMunicipios()const {
		if(_listaMunicipios.isEmpty()){
			return false;
		}
		else{
			return true;
		}
	}

	/*****************************************************************************/
/*! 
	\brief   Función que devuelve el numero de Municipios que hay
	\attention Se utiliza el modificador const en la definición de la función
	\note    Función inline
	\return  int: Número de Municipios en la Provincia
	\pre     Ninguna
	\post    Ninguna
	\sa 	    nItems()
*/		
	inline int getNumeroMunicipios()const {return _listaMunicipios.nItems();}
	
	/*****************************************************************************/
/*! 
	\brief   Función que indica si el municipio con el nombre indicado pertenece a la provincia
	\return  bool: true si existe, false en otro caso
	\pre     Ninguna
	\post    Ninguna
	\sa 	    isEmpty(), gotoHead(), getCurrentItem(), gotoNext(), isLastItem(), getNombre(), 
*/
	bool existeMunicipio(std::string nombre);
	
	/********************************************************************************/
/*! 
	\brief   Función que devuelve el municipio con el nombre indicado
	\return  Municipio: municipio con el nombre indicado
	\pre     existeMunicipio == true
	\post    Ninguna
	\sa 	    existeMunicipio(), getCurrentItem()
*/
	Municipio getMunicipio(std::string nombre);
	
	/*********************************************************************************/
/*! 
	\brief   Función que devuelve el numero total de Hombres de la provincia
	\return  int: Número de total de hombres 
	\pre     Ninguna
	\post    Ninguna
	\sa 	    gotoHead(), isLastItem(), getCurrentItem(), getHombres(), gotoNext()
*/
	int getTotalHombres();
	
	/**********************************************************************************/
/*! 
	\brief   Función que devuelve el numero total de Mujeres de la provincia
	\return  int: Número de total de mujeres 
	\pre     Ninguna
	\post    Ninguna
	\sa 	    gotoHead(), isLastItem(), getCurrentItem(), getHombres(), gotoNext()
*/
	int getTotalMujeres();
	
	/***********************************************************************************/
/*! 
	\brief   Función que devuelve el numero total de Habitantes de la Provincia
	\note    Función inline
	\return  int: Número total de Habitantes
	\pre     Ninguna
	\post    valordevuelto == getTotalHombres() + getTotalMujeres()
	\sa 	    
*/
	inline int getTotalHabitantes(){return getTotalHombres() + getTotalMujeres();}
	
	
	/////////////////////////////////////////////////////////////////////

	//!	\name Modificadores
	/***********************************************************************************/
/*! 
	\brief   Método que asigna un nuevo nombre a la Provincia
	\note    Función inline
	\param   nombre: Nombre para la provincia de tipo string
	\return  Nada, es de tipo void
	\pre     Ninguna
	\post    getNombre() == nombre
*/
	inline void setNombre(std::string nombre){
		_nombre=nombre;
		
			#ifndef NDEBUG
				assert(getNombre()==nombre);
			#endif
		}

	/**************************************************************************************/
/*! 
	\brief   Método que asigna un nuevo codigo a la Provincia
	\note    Función inline
	\param   numero: Codigo para la provincia de tipo int
	\return  Nada, es de tipo void
	\pre     Ninguna
	\post    getCodigo() == numero   
*/		
	inline void setCodigo(int numero){
		_codigo=numero;
	
			#ifndef NDEBUG
				assert(getCodigo()==numero);
			#endif
	}
	
	
	/**************************************************************************************/
/*! 
	\brief   Función que inserta un Municipio indicado por teclado en la Provincia de forma ordenada
	\param   municipio: de tipo Municipio const
	\return  Nada, es de tipo void
	\pre     existeMunicipio == falso
	\post    existeMunicipio == true 
	\post    getNumeroMunicipios() == old.getNumeroMuncipios + 1
	\sa 	    insert(), existeMunicipio(), getNumeroMunicipios()
*/
	void insertarMunicipio(ed::Municipio const municipio);
	
	/***************************************************************************/
/*! 
	\brief   Función que borra un Municipio indicado por teclado
	\param   nombre: de tipo string
	\return  Nada, es de tipo void
	\pre     existeMunicipio == true
	\post    existeMunicipio == false
	\post    getNumeroMunicipios() == old.getNumeroMuncipios - 1
	\sa 	    remove(), existeMunicipio(), getNumeroMunicipios()
*/
	void borrarMunicipio(std::string nombre);
	
	/***************************************************************************/
/*! 
	\brief   Función que borra todos los Municipios de la Provincia
	\return  Nada, es de tipo void
	\post    hayMunicipios == false 
	\sa 	    removeAll(), hayMunicipios
*/
	void borrarTodosLosMunicipios();
	
	
	/////////////////////////////////////////////////////////////////////

	//! \name Función de escritura de la clase Provincia

	/***********************************************************************/
/*!
	\brief	Función que imprime por pantalla nombre y codigo de la Provincia y todos los Municipios y sus datos
	\return   Nada, es de tipo void
	\sa	 	getNombre(), getCodigo(), isLastItem(), getCurrentItem(), gotoNext(), escribirMunicipio()
*/
	void escribirMunicipios();


	/////////////////////////////////////////////////////////////////////

	//! Operaciones con ficheros
	
	/********************************************************************/
/*! 
	\brief   Función que carga los datos de una Provincia desde un fichero
	\param   nombre: de tipo string, que es el nombre del fichero
	\return  Bool si se ha cargado correctamente, false en otro caso
	\pre     Ninguno
	\post    Ninguno
	\sa 	    setCodigo(), setNombre(), operador >>, insert()
*/
	bool cargarFichero(std::string nombre);
	
	/********************************************************************/
/*! 
	\brief   Función que graba los datos de una Provincia en un fichero
	\param   nombre: de tipo string, que es el nombre del fichero
	\return  Bool si se ha grabado correctamente, false en otro caso
	\pre     Ninguno
	\post    Ninguno
	\sa 	    getCodigo(), getNombre(), operador <<, getCurrentItem(), isLastItem(), gotoNext()
*/
	bool grabarFichero(std::string nombre);

}; //Fin de la clase  Provincia


} // Fin del espacio de nombres ed

#endif // _PROVINCIA_HPP_
