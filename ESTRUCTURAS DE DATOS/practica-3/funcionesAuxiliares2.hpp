/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal main.cpp de la práctica 3
  \author Antonio Ariza García	
  \date   08-04-2018
*/

#ifndef _FUNCIONESAUXILIARES2_HPP_
#define _FUNCIONESAUXILIARES2_HPP_

#include "MonticuloMediciones.hpp"


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
 	 
 	 
 	 
/*!
	\brief	 Comprueba si el monticulo esta vacío
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediciones
	\return    nada, de tipo void
	\sa	      cargarMonticulo(), grabarMonticulo(), consultarMonticulo()
*/
 	 void comprobarMonticulo(ed::MonticuloMediciones & monticulo);
 	 
 	 
/*!
	\brief	 Carga un monticulo desde un fichero
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediciones
	\return    nada, de tipo void
	\sa	      comprobarMonticulo(), grabarMonticulo(), consultarMonticulo()
*/
 	 void cargarMonticulo(ed::MonticuloMediciones & monticulo);
 	 
 	 
/*!
	\brief	 Graba un monticulo a un fichero
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediones
	\return    nada, de tipo void
	\sa	      comprobarMonticulo(), cargarMonticulo(), consultarMonticulo()
*/
 	 void grabarMonticulo(ed::MonticuloMediciones & monticulo);
 	 
/*!
	\brief 	 Consulta el tamaño y la cima del monticulo
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediones
	\return 	 Nada es de tipo void
	\sa 	 	 comprobarMonticulo(), cargarMonticulo(), grabarMonticulo()
*/
 	 void consultarMonticulo(ed::MonticuloMediciones & monticulo);
 	 
 	 
/*!
	\brief 	 Muestra todas las mediciones del monticulo
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediones
	\return 	 Nada es de tipo void
	\sa 		 comprobarMonticulo(), cargarMonticulo(), grabarMonticulo(), consultarMonticulo()
*/
 	 void mostrarMonticulo(ed::MonticuloMediciones & monticulo);
 	 
 	 
/*!
	\brief 	 Modifica la precipitacion de una medicion
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediones
	\return 	 Nada es de tipo void
	\sa 		 borrarTodoMonticulo(), consultarMonticulo(), consuñtarUnDia()
*/
 	 void modificarDatosMedicion(ed::MonticuloMediciones & monticulo);
 	 
 	 
/*!
	\brief 	 Borra todo el monticulo
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediones
	\return 	 Nada es de tipo void
	\sa 		 comprobarMonticulo(), cargarMonticulo(), grabarMonticulo(), consultarMonticulo()
*/
 	 void borrarTodoMonticulo(ed::MonticuloMediciones & monticulo);
 	 
 	 
/*!
	\brief 	 Muestra los datos de una medicion pedida por teclado
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediones
	\return 	 Nada es de tipo void
	\sa 		 comprobarMonticulo(), cargarMonticulo(), grabarMonticulo(), consultarMonticulo(), borrarTodoMonticulo()
*/
 	 void consultarUnDia(ed::MonticuloMediciones & monticulo);
 	 
/*!
	\brief 	 Inserta una Medicion en el monticulo
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediones
	\return 	 Nada es de tipo void
	\sa 		 comprobarMonticulo(), borrarCima(), grabarMonticulo(), consultarMonticulo(), modificarDatosMedicion()
*/
 	 void insertarMedicion(ed::MonticuloMediciones & monticulo);
 	 
/*!
	\brief 	 Borra la Cima del monticulo
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediones
	\return 	 Nada es de tipo void
	\sa 		 comprobarMonticulo(), insertaMedicion(), consultarMonticulo(), modificarDatosMedicion()
*/
 	 void borrarCima(ed::MonticuloMediciones & monticulo);
 	 
/*!
	\brief 	 Borra la Cima del monticulo
	\param 	 monticulo: Referencia a objeto de tipo MonticuloMediones
	\return 	 Nada es de tipo void
	\sa 		 comprobarMonticulo(), insertaMedicion(), consultarMonticulo(), modificarDatosMedicion()
*/
 	 void modificaCima(ed::MonticuloMediciones & monticulo);

/*!
	\brief 	Muestra las mediciones de un mes introducido por teclado
	\param	monticulo: Referencia a objeto de tipo MonticuloMediones
	\return 	Nada, es de tipo void
	\sa 	 	comprobarMonticulo(), insertaMedicion(), consultarMonticulo(), modificarDatosMedicion()
*/
	void mostrarMedicionesMes(ed::MonticuloMediciones & monticulo);
 	 
} //Fin del espacio de nombres

// Fin de _FUNCIONESAUXILIARES2_HPP_
#endif	 
 	 
 	 
 	 
 	 
 	 
 	 
 	 
 	 
 	 
 	 
 	 
  
  
  
