/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 2
  \author Antonio Ariza García	
  \date   08-04-2018
*/

#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

#include "Provincia.hpp"

/*!	
	\namespace ed
	\brief Espacio de nombres para la Provincia Estructuras de Datos

*/
namespace ed
{

	/*! 
		\brief   Muestra el menú del programa principal 
		\return  Devuelve el número de opción elegido
	*/
  int menu();

	///////////////////////////////////////////////////////////////////////
	/*!
	\brief	 Comprueba si la Provincia está Vacía o tiene 1 Municipio o más
	\param 	 provincia: Referencia a objeto de tipo Provincia
	\return    nada, de tipo void
	\sa	      hayMunicipios()
	*/
	void comprobarProvinciaVacia(ed::Provincia & provincia);

	///////////////////////////////////////////////////////////////////////
	/*!
	\brief	 Carga una Provincia desde un fichero de texto
	\param 	 provincia: Referencia a objeto de tipo Provincia
	\return    nada, de tipo void
	\sa	      hayMunicipios(), cargarFichero()
	*/
	void cargarProvincia(ed::Provincia & provincia);

	////////////////////////////////////////////////////////////////////////
	/*!
	\brief	 Graba una Provincia a un fichero de texto
	\param 	 provincia: Referencia a objeto de tipo Provincia
	\return    nada, de tipo void
	\sa	      hayMunicipios(), grabarFichero()
	*/
	void grabarProvincia(ed::Provincia & provincia);

	///////////////////////////////////////////////////////////////////
	/*!
	\brief	 Consulta todos los datos de una Provincia, Numero Municipios, hombres, mujeres..
	\param 	 provincia: Referencia a objeto de tipo Provincia
	\return    nada, de tipo void
	\sa	      getNombre(), getCodigo(), hayMunicipios(), getNumeroMunicipios(), getTotalHombres(), getTotalMujeres(), getTotalHabitantes()
	*/
	void consultarDatosDeProvincia(ed::Provincia & provincia);

	////////////////////////////////////////////////////////////////////
	/*!
	\brief	 Muestra por pantalla todos los Municipios de la Provincia 
	\param 	 provincia: Referencia a objeto de tipo Provincia
	\return    nada, de tipo void
	\sa	      hayMunicipios(), escribirMunicipios()
	*/
	void mostrarMunicipiosDeProvincia(ed::Provincia & provincia);

	///////////////////////////////////////////////////////////////////
	/*!
	\brief	 Permite modificar el nombre o/y el Codigo de la Provincia 
	\param 	 provincia: Referencia a objeto de tipo Provincia
	\return    nada, de tipo void
	\sa	      getNombre(), getCodigo(), setNombre(), setCodigo()
	*/
	void modificarDatosDeProvincia(ed::Provincia & provincia);

	/////////////////////////////////////////////////////////////////////
	/*!
	\brief	 Borra todos los Municipios de la Provincia 
	\param 	 provincia: Referencia a objeto de tipo Provincia
	\return    nada, de tipo void
	\sa	      hayMunicipios(), borrarTodosLosMunicipios()
	*/
	void borrarTodosLosMunicipiosDeProvincia(ed::Provincia & provincia);


	///////////////////////////////////////////////////////////////////
	/*!
	\brief	 Permite consultar los datos de un Municipio, debemos insertar su nombre
	\param 	 provincia: Referencia a objeto de tipo Provincia
	\return    nada, de tipo void
	\sa	      existeMunicipio(), getMunicipio(), escribirMunicipio()
	*/
	void consultarMunicipioDeProvincia(ed::Provincia & provincia);

	/////////////////////////////////////////////////////////////////////////
	/*!
	\brief	 Permite insertar un Municipio en la Provincia, rellenamos sus datos por teclado
	\param 	 provincia: Referencia a objeto de tipo Provincia
	\return    nada, de tipo void
	\sa	      setNombre(), setCodigoPostal(), setHombres(), setMujeres(), insertarMunicipio()
	*/
	void insertarMunicipioEnProvincia(ed::Provincia & provincia);
	
	//////////////////////////////////////////////////////////////////////////
	/*!
	\brief	 Permite borrar un Municipio de la Provincia, buscamos por su nombre
	\param 	 provincia: Referencia a objeto de tipo Provincia
	\return    nada, de tipo void
	\sa	      hayMunicipios(), borrarMunicipio()
	*/
	void borrarMunicipioDeProvincia(ed::Provincia & provincia);
	
	//////////////////////////////////////////////////////////////////////////////
	/*!
	\brief	Permite saber que Municipio tiene mas Habitantes de dos que insertamos por teclado
	\param 	provincia: Referencia a objeto de tipo Provincia
	\return	Nada, es de tipo void
	\sa 		
	*/
	void compararHabitantesMunicipios(ed::Provincia & provincia);


} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif

