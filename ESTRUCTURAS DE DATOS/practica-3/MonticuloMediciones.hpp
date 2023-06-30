/*!
	\file MonticuloMediciones.hpp
	\brief Se define el TAD MonticuloMediciones.
	\author Antonio Ariza García	
	\date  05-05-2018
*/

#ifndef _MONTICULO_MEDICIONES_HPP
#define _MONTICULO_MEDICIONES_HPP

#include <vector>

#include <cassert>

#include "macros.hpp"

#include "Medicion.hpp"

#include "MonticuloMedicionesInterfaz.hpp"

/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed
{

/*!	
  	\class MonticuloMediciones
  	\brief Definición de la clase MonticuloMediciones que hereda de la clase abstracta MonticuloMedionesInterfaz
	\n     Montículo de mediciones de precipitaciones de todos los días del año
*/

class MonticuloMediciones : public MonticuloMedicionesInterfaz
{
	private:

		//! \name Atributos privados de la clase MonticuloMediciones
		
		std::vector <ed::Medicion> _vector;  //!<  Vector de Mediciones de la STL
		
	/**********************************************************************/
	

		//! \name Métodos privados de la clase MonticuloMediciones
		
		/*!
			\brief	 Devuelve el elemento que ocupa la posición i del vector que almacena el montículo
			\note	 Funcion inline
			\note 	 Método privado no puede llamarse fuera de la clase
			\attention Funcíon de tipo const no puede modificar al objeto
			\param 	 i: de tipo entero, elemento a devolver
			\return	 Devuelve una Medicion que ocupa la pocición i
			\pre		 i>0 and i<size()
			\post	 Ninguna
			\sa 	 	 setElement()
		*/
		inline ed::Medicion getElement(int i)const { 
			
				#ifndef NDEBUG
					assert((i>=0) and (i<size()));
				#endif
				
			return _vector.at(i);
		}
		
		/*************************************************************/
		/*!
			\brief	 Modifica el elemento que ocupa la posicion i en el vector que almacena el montículo
			\note	 Funcion inline
			\note 	 Método privado no puede llamarse fuera de la clase
			\param 	 i: de tipo entero, elemento a modificar
			\param 	 medicion: de tipo Medicion
			\return	 Nada, es de tipo void
			\pre		 i>0 and i<size()
			\post	 getElement() == medicion
			\sa 	 	 getElement()
		*/
		inline void setElement(int i, ed::Medicion medicion){
		
				#ifndef NDEBUG
				//std::cout << "setelement i= " << i << std::endl;
					assert((i>=0) and (i<size()));
				#endif
				
			_vector[i] = medicion;
		
				#ifndef NDEBUG
					assert(getElement(i) == medicion);
				#endif
		}
		
		
		/****************************************************************/
		/*! 
			\brief	 Método privado devuelve el índice del hijo izquierdo del índice recibido
			\note	 Función inline
			\note 	 Método privado no puede llamarse fuera de la clase
			\attention Funcíon de tipo const no puede modificar al objeto
			\param 	 i: de tipo entero 
			\return 	 Devuele el índice del hijo izquierdo del índice recibido
			\pre		 i>=0
			\post 	 valordevuelto == 2*i+1
			\sa 		 setElement(), getElement()
		*/
		inline int getLeftChild(int i)const {
		
				#ifndef NDEBUG
					assert(i>=0);
				#endif
			int valordevuelto = 2*i+1;		
			return valordevuelto;
				
				#ifndef NDEBUG
					assert(valordevuelto==2*i+1);
				#endif		
		}
		
		/*****************************************************************/
		/*!
			\brief 	  Método privado que devuelve el índice del hijo derecho del índice recibido
			\note	  Función inline
			\note 	  Método privado no puede llamarse fuera de la clase
			\attention  Función de tipo const no puede modificar al objeto
			\param 	  i: de tipo entero
			\return 	  Devuelve el índice del hijo derecho del índice recibido 
			\pre		  i>=0
			\post 	  valordevuelto == 2*i +2
			\sa 		  getLeftChild(), setElement(), getElement()
		*/
		inline int getRightChild(int i)const {
		
				#ifndef NDEBUG
					assert(i>=0);
				#endif
				
			int valordevuelto = 2*i+2;		
			return valordevuelto;
				
				#ifndef NDEBUG
					assert(valordevuelto==2*i+2);
				#endif
		}
		
		/*******************************************************************/
		/*!
			\brief 	  Método privado que devuelve el índice del padre del índice recibido
			\note 	  Función inline
			\note 	  método privado no puede llamarse fuera de la clase
			\attention  Función de tipo const no puede modificar al objeto
			\param      i: de tipo entero
			\return  	  Devuelve el índice del padre del índice recibido
			\pre		  i>=1
			\post	  valordevuelto == (i-1)/2
			\sa		  getRightChild(), getLeftChild(), getElement(), setElement()
		*/
		inline int getParent(int i)const{
			
			if(i>=1){
				
					#ifndef NDEBUG
						assert(i>=1);
					#endif
			
				int valordevuelto = (i-1)/2;	
					
				return valordevuelto;
			
				
				#ifndef NDEBUG
					assert(valordevuelto==(i-1)/2);
				#endif
			}
			else{
				return 0;
			}
		}
		
		/**********************************************************************/
		/*!
			\brief 	  Método privado, El elemento indicado por el índice es subido en el montículo hasta que se verifica la ordenación de máximos.
			\note 	  Función inline
			\note 	  método privado no puede llamarse fuera de la clase
			\param      i: de tipo entero
			\return  	  Nada, es de tipo void
			\pre		  i>=0 and i<size()
			\post	  Si no es la cima, el elemento actual es menor o igual que su padre
			\post 	  Si tiene hijo izquierdo, el elemento actual es mayor o igual que él y, ademas, si tiene hijo derecho, es mayor o igual que él.
			\sa		  getRightChild(), getLeftChild(), getElement(), setElement(), getParent()
		*/
		inline void shiftUp(int i);
		
		
		/**********************************************************************/
		/*!
			\brief 	  Método privado, El elemento indicado por el índice es bajado en el montículo hasta que se verifica la ordenación de máximos.
			\note 	  Función inline
			\note 	  método privado no puede llamarse fuera de la clase
			\param      i: de tipo entero
			\return  	  Nada, es de tipo void
			\pre		  i>=0 and i<size()
			\post	  Si no es la cima, el elemento actual es menor o igual que su padre
			\post 	  Si tiene hijo izquierdo, el elemento actual es mayor o igual que él y, además, si tiene hijo derecho, es mayor o igual que él.
			\sa		  getRightChild(), getLeftChild(), getElement(), setElement(), getParent()
		*/
		inline void shiftDown(int i);
		
		
		/************************************************************************/
		/*!
			\brief 	 Comprueba si la medicón está incluida en el montículo
			\note 	 Método privado no puede llamarse fuera de la clase
			\param     medicion: de tipo Medición
			\return 	 true, si la medición está incluida en el montículo, false en otro caso
			\pre		 Ninguna
			\post	 Ninguna
			\sa 		 getRightChild(), getLeftChild(), getElement(), setElement(), getParent()
		*/
		bool has(ed::Medicion medicion)const;
	  /////////////////////////////////////////////////////////////////////////////////////

	//! \name Métodos públicos de la clase MonticuloMediciones
	public:

		//! \name Constructor
	/*! 
		\brief     Constructor sin arguemntos       
		\note      Función inline
		\pre       Ninguna
		\post      isEmpty() == true
		\sa        isEmpty()
	*/
		inline MonticuloMediciones(){
			
				#ifndef NDEBUG
					assert(isEmpty() == true);
				#endif	
				
			_vector.resize(0);
		}


		//! \name Observadores

		// COMPLETAR EL CÓDIGO E INCLUIR LOS COMENTARIOS DE DOXYGEN
		/*!
			\brief	 Método público comprueba si nuestro vector esta vacío
			\note 	 Función inline
			\return    true, si está vació, false en otro caso
			\pre		 Ninguna
			\post 	 valordevuelto == (size() == 0)
			\sa 		 size(), top()
		*/
		inline bool isEmpty()const {
			
			bool variable;
			
			if(_vector.size() == 0){	
				variable = true;
				return true;
			}
			else{
			variable = false;
				return false;
			}
			
				#ifndef NDEBUG
					assert((variable) == ((size())==0));
				#endif
		}
		
		/*************************************************************************/
		/*!
			\brief 	Método público que devuelve el número de mediciones del montículo
			\note 	Función inline
			\return   Un entero, número de mediciones del montículo
			\pre	     Ninguna
			\post 	Ninguna	
			\sa 	 	isEmpty(), top()
		*/
		inline int size()const {return _vector.size();}
		
		/*************************************************************************/
		/*!
			\brief 	Método público que devuelve la cima del montículo
			\note 	Función inline
			\return   Medición: Devuelve la cima del montículo
			\pre	 	isEmpty() == fasle
			\post 	valordevuelto == getElement(0)
		*/
		inline ed::Medicion top()const{
	
				#ifndef NDEBUG
					assert(isEmpty()==false);
				#endif
					
			ed::Medicion m = _vector.at(0);
			
				#ifndef NDEBUG
					assert(m==getElement(0));
				#endif
			return m;
		}

		
		////////////////////////////////////////////////////////////

		//! \name Operaciones de modificación

		/*!
			\brief 	 Método Modificador público, inserta una nueva medición en el montículo
			\return 	 Nada, es de tipo void
			\pre	      Nada, es de tipo void
			\post	 isEmpty() == false
			\post 	 has(medicion) == true
			\sa 		 remove(), removeAll()
		*/
		void insert(ed::Medicion medicion);
		
		/***********************************************************************/
		/*!
			\brief 	Método modificador público, borra la medición que ocupa la cima
			\return   Nada, es de tipo void
			\pre	 	isEmpty() == false
			\post 	Ninguna
			\sa 		insert(), removeAll()
		*/
		void remove();
		
		/*********************************************************************/
		/*!
			\brief 	Método modificador público, borrar todas las mediciones del montículo
			\return   Nada, es de tipo void
			\pre	 	Ninguna
			\post 	isEmpty() == true
			\sa 		insert(), remove()
		*/
		void removeAll();
		
		/***********************************************************************/
		/*!
			\brief 	Método modificador público, Modifica la medición que ocupa la cima y actualiza el montículo para que está ordenado
			\return   Nada, es de tipo void
			\pre		isEmpty() == false
			\post 	has(medicion) == true
			\sa		insert(), remove()
		*/
		void modify(ed::Medicion & medicion);

		//! \name Operadores públicos
   		
   		/***********************************************************************/
   		/*! 
			\brief     Operador de asignación: operador que "copia" , Devuelve el montículo actual que ha sido modificado con las mediciones del montículo "m" 
			\attention Se sobrecarga el operador de asignación "="
			\note      Función inline
			\warning   -----------
			\param     m: de tipo MonticuloMediciones
			\pre		 Los montículos actual y "m" no son el mismo objeto	
			\post	 Ninguna
			\sa        --------------------------
		*/
		inline ed::MonticuloMediciones & operator=(ed::MonticuloMediciones const & m){
		
			// Se comprueba que no sean el mismo objeto
			if (this != & m) 
			{
				for(int i=0; i < size(); i++){
					this->insert(m.getElement(i));
				}
		 	}
		 	return *this;
 		}	
 		
 		/*********************************************************************/
 		/*
 			\brief	  Operador de distinción: Comprueba si dos monticulos son distintos
 			\attention  Se sobrecarga el operador de asignacion !=
 			\note	  Función inline
 			\param  	  m: de tipo MonticuloMediciones
 			\pre	 	  Ninguna
 			\post	  Ninguna
 			\sa 		  operator=
 		*/
 		inline bool operator!=(ed::MonticuloMediciones const & m){
 		
 			int i;
 			for(i=0; i<size(); i++){
 				if(getElement(i) != m.getElement(i)){
 					return true;
 				}
 			}
 			
 			return false;
 		}
		
		/****************************************************************************/
		//! \name Función de escritura
		/*!
			\brief	 Escribe las mediciones tal y como están almacenadas en el vector que representa el montículo
			\pre	 	 Ninguna
			\post 	 Ninguna
		*/
		void print();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//FUNCIONES MIAS PROPIAS
		//! \name Funciones Propias, observadores y modificadores y otras
		/*****************************************************************************/
		/*!
			\brief	 Devuelve el elemento que ocupa la posición i del vector que almacena el montículo
			\note	 Funcion inline
			\note	 Función que llama a getElement()
			\attention Funcíon de tipo const no puede modificar al objeto
			\param 	 i: de tipo entero, elemento a devolver
			\return	 Devuelve una Medicion que ocupa la pocición i
			\pre		 i>0 and i<size()
			\post	 Ninguna
			\sa 	 	 setElement(), setMedicion
		*/	
		inline ed::Medicion getMedicion(int i)const {
			
			return this->getElement(i);
		}
		
		/***************************************************************************/
		/*!
			\brief	 Modifica el elemento que ocupa la posicion i en el vector que almacena el montículo
			\note	 Funcion inline
			\note 	 Método que llama a setElement()
			\param 	 i: de tipo entero, elemento a modificar
			\param 	 m: de tipo Medicion
			\return	 Nada, es de tipo void
			\pre		 i>0 and i<size()
			\post	 getElement() == medicion
			\sa 	 	 getElement(), setElement()
		*/
		inline void setMedicion(int i, ed::Medicion m){
		
			this->setElement(i,m);
		}
		
		/***************************************************************************/
		/*!
			\brief	 Método público que busca una Medicion por su fecha
			\note 	 Solo comprueba la fecha de la medicion no la precipitacion
			\param 	 fecha: de tipo Fecha
			\return	 i: de tipo entero, que indica la posicion donde ha sido encontrado
			\return    -1: si la medicion no ha sido encontrada
			\pre		 Ninguna
		*/
		int buscarMedicion(ed::Fecha fecha);
		
		/***************************************************************************/
		/*!
			\brief	 Método público que comprueba si el monticulo cumple la ordenación de máximos
			\return	 true, si el monticulo cumple la ordenación de máximos, false en otro caso
			\pre		 isEmpty() == false
		*/
		bool ordenado();
		
		/**************************************************************************/
		/*!
			\brief 	 Método público que modifica la Precipitacion de una Medicion
			\param 	 i: la Medicion a modificar
			\param 	 fecha: de tipo Fecha que indicara la Medicion a modificar
			\pre 	 Ninguna	
			\post 	 Ninguna
		*/
		bool modifica(int i, ed::Fecha fecha);
		
		/***************************************************************************/
		/*!
			\brief 	 Muestra todas la Mediciones de un mes
			\note 	 El mes deberá ser indicado con un numero entero
			\warning   No se permiten cadenas de texto
			\param 	 m: de tipo entero, mes a consultar
			\pre	  	 m>0 and m < 12 
			\post 	 Ninguna
		*/
		void mostrarMes(int m);
		

}; // Clase MonticuloMediciones

} // Espacio de nombres ed


#endif // _MONTICULO_MEDICIONES_HPP
