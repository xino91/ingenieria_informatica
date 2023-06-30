/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 4
  \author Antonio Ariza García	
  \date   21/05/2018
*/

#ifndef _FuncionesAuxiliares_HPP_
#define _FuncionesAuxiliares_HPP_

#include "Grafo.hpp"
#include "macros.hpp"

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
	\brief	 Carga el grafo desde un fichero
	\param 	 grafo: Referencia a objeto de tipo Grafo
	\return    true, en caso de éxito, false en otro caso
	\sa	      arbolcosteminimo()
*/
	bool cargarGrafoDeFichero(ed::Grafo & grafo);
	
	
/*!
	\brief	 Muestra el grafo por pantalla, los vectores de Vertice y lado y la matriz adyacencias
	\param 	 grafo: Referencia a objeto de tipo Grafo
	\sa	   	 cargarGrafoDeFichero(), arbolcosteminimo()
*/
	void mostrarGrafo(ed::Grafo & grafo);

	
/*!
	\brief	 Funcion que muestra un submenú donde elegir que algoritmo ejecutar
	\param 	 grafo: Referencia a objeto de tipo Grafo
	\sa	   	 cargarGrafoDeFichero(), arbolcosteminimo()
*/	
	void arbolcosteminimo(ed::Grafo & grafo);

	
/*!
	\brief	 Funcion que calcula el algoritmo Prim sobre un grafo
	\param 	 grafo: Referencia a objeto de tipo Grafo
	\return    un Grafo con el algoritmo AACM ejecutado
	\sa	   	 cargarGrafoDeFichero(), arbolcosteminimo(), algoritmoKruskal
*/
	ed::Grafo algoritmoPrim(ed::Grafo &grafo);


/*!
	\brief	 Funcion que calcula el algoritmo Prim sobre un grafo
	\param 	 grafo: Referencia a objeto de tipo Grafo
	\return    un Grafo con el algoritmo AACM ejecutado
	\sa	   	 cargarGrafoDeFichero(), arbolcosteminimo(), algoritmoPrim()
*/	
	ed::Grafo algoritmoKruskal(ed::Grafo & grafo);
	

}	// Fin del espacio de nombre de la asignatura: ed


// Fin de _FuncionesAuxiliares_HPP_
#endif
