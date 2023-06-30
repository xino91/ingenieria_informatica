/*!
	\file    ListaDoblementeEnlazadaOrdenadaMunicipios.hpp
	\brief   Clase de una lista doblemente enlazada y ordenada de Municipios
	\author  Antonio Ariza García
	\date    08-04-2018
	\version 1.0
*/

#ifndef __ListaDoblementeEnlazadaOrdenadaMunicipios_HPP__
#define __ListaDoblementeEnlazadaOrdenadaMunicipios_HPP__

// Para comprobar las pre y post-condiciones
#include <cassert>

#include "ListaOrdenadaMunicipiosInterfaz.hpp"

#include "NodoDoblementeEnlazadoMunicipio.hpp"
#include "macros.hpp"

#include "Municipio.hpp"

/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos

*/ 
namespace ed {
 
/*!	
  \class ListaDoblementeEnlazadaOrdenadaMunicipios 
  \brief Definición de la clase ListaDoblementeEnlazadaOrdenadaMunicipios
  \n Lista doblemente enlazada de nodos de municipios ordenados alfabéticamente de forma ascendente 
*/
  class ListaDoblementeEnlazadaOrdenadaMunicipios: public ed::ListaOrdenadaMunicipiosInterfaz
  {
	//! \name  Atributos y métodos privados 

	private:
		ed::NodoDoblementeEnlazadoMunicipio *_head;    //!< \brief puntero al primer nodo de la lista
		ed::NodoDoblementeEnlazadoMunicipio *_current; //!< \brief puntero al nodo current de la lista

    //! \name Observadores privados 

	/****************************************************************/
/*!
	\brief  Método privado que permite conocer el puntero a la cabeza de mi lista
	\note   Función inline
	\return Devuelve un puntero con la direccion de la cabeza de la lista
	\pre    isEmpty()==false
	\post   Ninguna
*/
    inline ed::NodoDoblementeEnlazadoMunicipio * getHead() const
	{
		
			#ifndef NDEBUG
				assert(isEmpty()==false);
			#endif	
			
		return this->_head;
		
	}
	
	/***************************************************************/
/*!
	\brief  Método privado que permite conocer el puntero a la cabeza de mi lista
	\note   Función inline
	\return Devuelve un puntero con la direccion de la cabeza de la lista
	\pre    isEmpty()==false
	\post   Ninguna
*/
	inline ed::NodoDoblementeEnlazadoMunicipio * getCurrent() const
	{
		
			#ifndef NDEBUG
				assert(isEmpty()==false);
			#endif	
			
		return this->_current;
	}

    //! \name Modificadores privados 
    /******************************************************************/
/*!
	\brief  Método privado que permite modificar la cabeza de la lista
	\note   Función inline
	\param  head: Puntero a un NodoDoblementeEnlazadoMunicipio
	\pre    Ninguna
	\post   getHead() == head
	\return Nada, es de tipo void
*/
	inline void setHead(ed::NodoDoblementeEnlazadoMunicipio *head) 
	{
		this->_head = head;

		#ifndef NDEBUG
			// Se comprueba la postcondición
			assert(this->_head == head);
		#endif //NDEBUG		 
	}

	/*****************************************************************/
/*!
	\brief  Método privado que permite modificar el cursor de la lista
	\note   Función inline
	\param  current: Puntero a un NodoDoblementeEnlazadoMunicipio
	\pre    Ninguna
	\post   getCurrent() == current
	\return Nada, es de tipo void
*/
    inline void setCurrent(ed::NodoDoblementeEnlazadoMunicipio *current) 
	{
		this->_current = current;

		#ifndef NDEBUG
			// Se comprueba la postcondición
			assert(this->_current == current);
		#endif //NDEBUG		
	}


	//! \name  Métodos públicos

	public:

	//! \name Constructores

    /*! 
		\brief Construye una lista vacía
		\note  Función inline
		\post  isEmpty() == true
	*/
	inline ListaDoblementeEnlazadaOrdenadaMunicipios()
    {
		 this->_head = NULL;
		 this->_current = NULL;	  
		
			#ifndef NDEBUG
				assert(this->isEmpty()==true);
			#endif
	}
	
  
	//! \name Destructor 

/*! 
	\brief Destruye una lista liberando la memoria de sus nodos
	\note Función codificada en el fichero cpp
	\post isEmpty() == true
*/
	~ListaDoblementeEnlazadaOrdenadaMunicipios ()
     {
     	if(isEmpty() == true ){		 
		 	this->_head = NULL;
		 	this->_current = NULL;
		 }
		 else{
		 	std::cout << BIBLUE << "----Llamada a Dectructor de Lista----" << RESET << std::endl;
		 	removeAll();
		 	this->_head = NULL;
		 	this->_current = NULL;
		 }
		 
		 std::cout << BIBLUE << " ----Fin Dectructor de Lista----" << RESET << std::endl;
		 
		 	#ifndef NDEBUG
		  		assert(this->isEmpty()==true);
		  	#endif
     }


	//! \name Observadores públicos 

	/************************************************************************/
/*!
	\brief  Comprueba si la lista está vacía
	\note   Función inline
	\note   Función de tipo "const": no puede modificar al objeto actual
     \return true, si la lista está vacía; false, en caso contrario
*/
	inline bool isEmpty() const
	{
		if(this->_head==NULL){
			return true;
		}
		else{ 
			return false;
		}
	}

	/**********************************************************************/
/*!
	\brief  Devuelve el número de elementos o ítems de la lista
	\note   Función de tipo "const": no puede modificar al objeto actual
	\return Número entero que representa el número de elementos o ítems de la lista
*/
	int nItems()const;
	
	/***********************************************************************/
/*!
	\brief Comprueba si nuestro cursor está en el primer nodo de la lista
	\note Función de tipo "const": no puede modificar al objeto actual
	\pre    La lista no está vacía
	\return true, si el cursor está en el primer elemento, false en otro caso
*/
	bool isFirstItem()const;

	/************************************************************************/
/*!
	\brief  Comprueba si el cursor entá en el último nodo de la lista
	\note   Función de tipo "const": no puede modificar al objeto actual
	\pre    La lista no está vacía
	\return true, si el cursor está en el último nodo, false es otro caso
*/ 
	bool isLastItem()const;
	
	/************************************************************************/
/*!
	\brief  Método que obtiene el Municipio del nodo donde este situado el cursor
	\note   Función de tipo "const": no puede modificar al objeto actual
	\pre    La lista no está vacía
	\return  Devuelve una referencia constante a un Municipio
*/
	Municipio const & getCurrentItem()const;
	
	/************************************************************************/
/*!
	\brief  Método que obtiene el Municipio situado en el nodo anterior de nuestro cursor
	\note   Función de tipo "const": no puede modificar al objeto actual
	\pre    La lista no está vacía
	\pre    No es el primer elemento
	\return  Devuelve una referencia constante a un Municipio
*/
	Municipio const & getPreviousItem()const;
	
	/************************************************************************/
/*!
	\brief  Método que obtiene el Municipio situado en el nodo siguiente de nuestro cursor
	\note   Función de tipo "const": no puede modificar al objeto actual
	\pre    La lista no está vacía
	\pre    No es el último elemento
	\return  Devuelve una referencia constante a un Municipio
*/
	Municipio const & getNextItem()const;
	
	
    //! \name Modificadores públicos

	/**************************************************************************/
/*!
	\brief	Método público modificador, nos permite mover el cursor a la cabeza
	\note 	Asegurar que la lista no esta vacía
	\pre 	La lista no está vacía
	\post	Es el primer elemento
	\return   Nada, es de tipo void
	\sa		gotoLast(), gotoPrevious(), gotoNext()
*/
	void gotoHead();
	
	/***************************************************************************/
/*!
	\brief	Método público modificador, nos permite mover el cursor al último elemento
	\note     Asegurar que la lista no está vacía
	\pre 	La lista no está vacía
	\post 	Es el último elemento 
	\return   Nada, es de tipo void
	\sa		gotoHead(), gotoPrevious(), gotoNext()
*/
	void gotoLast();
	
	/****************************************************************************/
/*!
	\brief	Método público modificador, coloca el cursor nodo anterior
	\note	Asegurarse que no estamos en el primer elemento
	\pre 	isEmpty == false , isFirtItem() == false
	\post 	Ninguna
	\return 	Nada, es de tipo void
	\sa		gotoHead(), gotoLast(), gotoNext()
*/
	void gotoPrevious();
	
	/*****************************************************************************/
/*!
	\brief	Método público modificador, coloca el cursor en el nodo siguiente
	\note 	Asegurarse que no está en el último nodo
	\pre 	isEmpty() == false , isLastItem() == false
	\post 	Ninguna
	\return 	Nada, es de tipo void
	\sa		gotoHead(), gotoLast(), gotoPrevious()
*/
	void gotoNext();
	
	/********************************************************************************/
/*!
	\brief  Coloca el cursor en el nodo que contiene al municipio en su campo informativo, si existe; si no existe coloca el cursor en el siguiente Municipio mayor que él, si todos son menores lo coloca en el último
	\param  item: municipio buscado; referencia constante de la clase Municipio 		
	\post   retVal==true implica que getCurrentItem() == item
	\post   retVal==false implica que getCurrentItem > item o isLastItem() == true
	\return true, si el municipio está en la lista; false, en caso contrario
	\sa	   getHead(), isEmpty(), getItem(), isLastItem(), getCurrentItem(), setCurrent(), gotoNext(),
   */ 
	bool find(ed::Municipio const & item);
	
	/*********************************************************************************/
/*!
	\brief Inserta un Municipio de forma ordenada por apellidos y nombre
	\param item: objeto de la clase Municipio que va a ser insertado; referencia constante de la clase Municipio
	\pre   find(item) == false
 	\post  getCurrentItem() == item
 	\post  nItems() == ols.nItems() +1
 	\return Nada, es de tipo void
	\sa    getHead(), isEmpty(), setHead(), setCurrent(), getCurrent(), getItem(), setPrevious(), setNext(), gotoHead(), isLastItem(), isFirstItem(), nItems(), getCurrentItem()
*/
	void insert(ed::Municipio const & item);
	
	/**********************************************************************************/
/*!
	\brief Borra el municipio indicado por el cursor
	\pre   La lista no está vacía: isEmpty()== false
	\post  El número de municipios se reduce en uno
	\n nItems()==old.nItems()-1
     \post  Si old.isFirstItem()==falso y  old.isLastItem()==falso entonces old.getPreviousItem()== getPreviousItem() y old.getNextItem()==getCurrentItem()
	\post  Si old.lastItem()==verdadero entonces isEmpty()==verdadero o old.getPreviousItem()==getCurrentItem() y isLastItem()==verdadero
	\post  Si old.isFirstItem()==verdadero entonces isEmpty()==verdadero o old.getNextItem()==getCurrentItem() y isFirstItem()==verdadero
	\sa    getHead(), isEmpty(), setHead(), setCurrent(), getCurrent(), getItem(), setPrevious(), setNext(), gotoHead(), isLastItem(), isFirstItem(), nItems()
*/
	void remove();
	
	/***********************************************************************************/
/*!
	\brief 	Borra todos los municipios de la lista
	\post	isEmpty() == verdadero
	\sa 		getHead(), setCurrent(), ,isEmpty(), remove()
*/
	void removeAll();

	

}; // Fin de la clase ListaDoblementeEnlazadaOrdenadaMunicipios
 
} //namespace ed
 
#endif // __ListaDoblementeEnlazadaOrdenadaMunicipios_HPP__
