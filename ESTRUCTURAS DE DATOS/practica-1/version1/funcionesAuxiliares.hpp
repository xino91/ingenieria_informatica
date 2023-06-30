
/*!
  \file   funcionesAuxiliares.hpp
  \brief  Funciones auxiliares para el programa principal de la práctica 1
  \author Antonio Ariza García
  \date   2018-3-03
*/

#ifndef _FUNCIONESAUXILIARES_HPP_
#define _FUNCIONESAUXILIARES_HPP_

#include "Vector3D.hpp"


namespace ed
{
	/*! 
		\brief   Muestra el menú del programa principal 
		\return  Devuelve el número de opción elegido
	*/
	int menu();

	/*!
	\brief	 Realiza la lectura de vectores de tipo Vector3D a tráves de operadores y funciones
	\param 	 u: vector de tipo Vector3D pasado como referencia
	\param     v: vector de tipo Vector3D pasado como referencia
	\param     w: vector de tipo Vector3D pasado como referencia
	\return    nada, de tipo void
	\sa	      leerVectores(), operador >>
	*/
	void leerVectores(ed::Vector3D &u, ed::Vector3D &v, ed::Vector3D &w);

	
	/*!
	\brief 	 Realiza la escritura de vectores de tipo Vector3D a traves de operadores y funciones
	\param 	 u: vector de tipo Vector3D pasado como referencia const
	\param     v: vector de tipo Vector3D pasado como referencia const
	\param     w: vector de tipo Vector3D pasado como referencia const
	\return    nada, de tipo void
	\sa	      escribirVectores(), operador <<
	*/
	void escribirVectores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w);


	/*!
	\brief	 Realiza la prueba de los observadores de vectores de tipo Vector3D
	\param	 u: vector de tipo Vector3D pasado como referencia const
	\param     v: vector de tipo Vector3D pasado como referencia const
	\return    nada, es de tipo void
	\sa 	 	 alfa(), beta(), gamma(), modulo(), angulo(), get1(), get2(), get3(), escribirVector3D(), operador <<
	*/
	void observadoresDeVectores(ed::Vector3D const &u, ed::Vector3D const &v);

	/*!
	\brief 	 Permite modificar los datos de un vector de tipo Vector3D
	\param 	 u: vector de tipo Vector3D pasado como referencia
	\param     v: vector de tipo Vector3D pasado como referencia const
	\param 	 k: tipo double, constante utilizada para hacer operaciones con el Vector3D
	\return    Nada, es de tipo void
	\sa 	 	 sumConst(), sumVect(), multConst(), multVect(), operdador <<
	*/
	void modificarVector(ed::Vector3D &u, ed::Vector3D const &v, double k);

	
	/*!
	\brief 	Permite consultar los datos del producto escalar de dos vectores de tipo Vector3D
	\param    u: vector de tipo Vector3D pasado como referencia const
	\param    v  vector de tipo Vector3D pasado como referencia const
	\return   nada, es de tipo void
	\sa 		dotProduct(), operador << , operador *
	*/
	void mostrarProductoEscalar(ed::Vector3D const &u, ed::Vector3D const &v); 

	/*!
	\brief 	Permite consultar los datos del producto vectorial de dos vectores de tipo Vector3D
	\param	u: vector de tipo Vector3D pasado como referencia const
	\param    v: vector de tipo Vector3D pasado como referencia const
	\return   nada
	\sa       modulo(), crossProduct(), operador <<, operador ^
	*/
	void mostrarProductoVectorial(ed::Vector3D const &u, ed::Vector3D const &v);

	
	/*!
	\brief 	Permite consultar los datos del producto mixto de tres vectores de tipo Vector3D
	\param 	u: vector de tipo Vector3D pasado como referencia const
	\param 	v: vector de tipo Vector3D pasado como referencia const
	\param 	w: vector de tipo Vector3D pasado como referencia const
	\return   nada
	\sa 		modulo(), productoMixto(), operador <<, operador ^ 
	*/
	void mostrarProductoMixto(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D const &w);

	
	/*!
	\brief    Permite consultar los datos sobre los operadores con tres vectores de tipo Vectores3D
	\param    u: vector de tipo Vector3D pasado como referencia const
	\param    v: vector de tipo Vector3D pasado como referencia const
	\param 	w: vector de tipo Vector3D pasado como referencia const
	\param 	k: constante de tipo double, utilizada para hacer operaciones
	\return   nada 
	\sa 		operador ==, operador de asignacion =, operadores unarios + y -, operadores + y -, operador prefijo k *vector, operador sufijo vector * k
	*/
	void mostrarOperadores(ed::Vector3D const &u, ed::Vector3D const &v, ed::Vector3D &w,  double k);



} // Fin del espacio de nombre de la asignatura: ed

// Fin de _FUNCIONESAUXILIARES_HPP_
#endif

