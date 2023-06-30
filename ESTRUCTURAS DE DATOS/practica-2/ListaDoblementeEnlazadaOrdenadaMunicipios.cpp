/*!
	\file   ListaDoblementeEnlazadaOrdenadaMunicipios.cpp
	\brief  Clase de una lista doblemente enlazada y ordenada de Municipios
	\author  Antonio Ariza García	
	\date    08-04-2018
	\version 1.0
*/

// Para comprobar las pre y post-condiciones
#include <cassert>

#include "ListaDoblementeEnlazadaOrdenadaMunicipios.hpp"
#include "NodoMunicipioInterfaz.hpp"
#include "Municipio.hpp"


int ed::ListaDoblementeEnlazadaOrdenadaMunicipios::nItems()const{
	
	if(this->isEmpty() == true){
		return 0;
	}
	
	NodoDoblementeEnlazadoMunicipio *aux= getHead();
	int contador=0;
	
	while(aux!=NULL){
		
		contador++;
		aux=aux->getNext();

	}
	
	return contador;
}


bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::isFirstItem()const{
		
			#ifndef NDEBUG
				assert(isEmpty()==false);
			#endif
		
		if(getCurrent() == getHead() and getCurrent()!=NULL){
			return true;
		}
		else{
			return false;	
		}
}


bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::isLastItem()const{

		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif
	
	NodoDoblementeEnlazadoMunicipio *aux = getCurrent();
	
	if( aux->getNext() == NULL){
		return true;
	}
	else{
		return false;
	}
}


ed::Municipio const & ed::ListaDoblementeEnlazadaOrdenadaMunicipios::getPreviousItem()const{

		#ifndef NDEBUG
			assert(isEmpty()==false);
			assert(isFirstItem()==false);
		#endif
	
	return this->_current->getPrevious()->getItem();
	
}


ed::Municipio const & ed::ListaDoblementeEnlazadaOrdenadaMunicipios::getNextItem()const{

		#ifndef NDEBUG
			assert(isEmpty()==false);
			assert(isLastItem()==false);
		#endif
		
	return this->_current->getNext()->getItem();	
}


ed::Municipio const & ed::ListaDoblementeEnlazadaOrdenadaMunicipios::getCurrentItem()const{

		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif
	
	return this->getCurrent()->getItem();	
}

//MODIFICADORES 
void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoHead(){

		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif
	
	this->_current = this->getHead();
		
		#ifndef NDEBUG
			assert(isFirstItem()==true);
		#endif
}
	

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoLast(){

		#ifndef NDEBUG
			assert(isEmpty()==false);
		#endif
	
	NodoDoblementeEnlazadoMunicipio *aux=getHead();
	
	while(aux->getNext()!=NULL){
		
		aux=aux->getNext();
	}
	
	this->_current = aux;
	
	
		#ifndef NDEBUG
		assert(isLastItem()==true);
		#endif
}

void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoPrevious(){
		
		#ifndef NDEBUG
			assert(isEmpty()==false);
			assert(isFirstItem()==false);
		#endif
	
	NodoDoblementeEnlazadoMunicipio *aux= getCurrent();

	this->_current = aux->getPrevious();
}


void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::gotoNext(){
	
		#ifndef NDEBUG
			assert(isEmpty()==false);
			assert(isLastItem()==false);
		#endif

	NodoDoblementeEnlazadoMunicipio *aux= getCurrent();
	
	this->_current = aux->getNext();
}


bool ed::ListaDoblementeEnlazadaOrdenadaMunicipios::find(Municipio const & item){

	//Lista vacía
	if(isEmpty()==true){
		
		return false;
	}
	
	NodoDoblementeEnlazadoMunicipio *aux=getHead();
	
	//std::cout << "FIND" << std::endl;

	while(aux->getItem() < item and isLastItem()!=true){
		
		if(aux->getItem()==item){	//Encontramos el municipio
			setCurrent(aux);		//Dejamos el cursor en el Municipio
			
			#ifndef NDEBUG
				assert(getCurrentItem()==item);
			#endif
			return true;
		}
		//std::cout << "Current: " << getCurrentItem() << std::endl;
		gotoNext(); //cursor a siguiente nodo
	}
	
	//si salimos poque estamos en el ultimo nodo
	//comprobamos que Municipio que buscamos no está en el ultimo nodo
	if(aux->getItem() == item){
		//std::cout << "Current: " << getCurrentItem() << std::endl;
		setCurrent(aux);	//Dejamos el cursor en el municipio
			#ifndef NDEBUG
				assert(getCurrentItem()==item);
			#endif
				
		return true;
	}
	
	
	
	//Si salimos porque Municipio > item, cursor a nodo siguiente
	setCurrent(aux);	//Dejamos cursor en nodo >
	
	//std::cout << "Current: " << getCurrentItem() << std::endl;
		#ifndef NDEBUG
			//assert((getCurrentItem() > item) or (isLastItem()==true));
		#endif
		
	
	//std::cout << "FIND SALIENDO: FALSE" << std::endl;
	
	return false;
}


void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::insert(Municipio const & item){
			
		#ifndef NDEBUG
			assert(find(item)==false);
			int nitems = nItems();
		#endif
	
	
	//Creamos nuestro nodo a insertar
	//NodoDoblementeEnlazadoMunicipio aux(item,NULL,NULL);
	NodoDoblementeEnlazadoMunicipio *aux = new NodoDoblementeEnlazadoMunicipio(item,NULL,NULL); 
	
	
	//Comprobamos si la lista esta vacia
	if(this->isEmpty()==true){
		std::cout<<"CASO 1: INSERT LISTA VACIA---"<<std::endl;  
		setHead(aux);
		setCurrent(aux);
	}
	else {
	
		this->gotoHead();
		
		if (this->getCurrent()->getItem() > item)
		{
			std::cout<<"CASO 2: INSERTANDO DELANTE CABEZA---"<<std::endl;  
			aux->setNext(this->getCurrent());
			aux->setPrevious(NULL);
			this->getCurrent()->setPrevious(aux);
			this->setHead(aux);
			this->setCurrent(aux);
		}
		else
		{
			
			while(this->getCurrent()->getItem() < item and isLastItem()==false)
			{
				this->gotoNext();
				
			}
			
			if(isLastItem()==true and this->getCurrent()->getItem() < item)
			{
				std::cout<<"CASO 3: INSERTANDO AL FINAL---"<<std::endl;
				this->getCurrent()->setNext(aux);
				aux->setPrevious(this->getCurrent());
				aux->setNext(NULL);
				this->setCurrent(aux);
				
			}
			else 
			{
				std::cout<<"CASO 4: INSERTANDO ENTRE DOS NODOS---"<<std::endl;
				NodoDoblementeEnlazadoMunicipio *ant=this->getCurrent()->getPrevious(); 
				
				getCurrent()->setPrevious(aux);
				ant->setNext(aux);
				aux->setNext(getCurrent());
				aux->setPrevious(ant);
				setCurrent(aux);
				std::cout << "Se ha inserta entre dos nodos---" << std::endl;
			}
		}
	}
	
			#ifndef NDEBUG
			
				assert(getCurrentItem() == item);
				assert(nItems() == nitems+1);
			#endif
	
}


void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::remove(){

		#ifndef NDEBUG
			assert(isEmpty()==false);
			int nitems = nItems();
			Municipio oldprevious;
			Municipio oldnext;
		#endif
	
 	NodoDoblementeEnlazadoMunicipio *aux=getHead();
	
	//Eliminamos el UNICO ELEMENTO que tb es la cabeza
	if(getCurrent() == getHead() and getCurrent()->getPrevious()==NULL and getCurrent()->getNext()==NULL){
			
		getCurrent()->~NodoDoblementeEnlazadoMunicipio();
		setHead(NULL);
		setCurrent(NULL);
		
		std::cout << "Borrando el único elemento de la lista" << std::endl;
		
			#ifndef NDEBUG
				assert(this->isEmpty()==true);
			#endif
	}
	else{
		//LA LISTA TIENE MAS DE UN NODO
		//Borramos entre nodos
		if(this->isFirstItem()==false and isLastItem()==false){
			
				#ifndef NDEBUG
					Municipio oldprevious = getPreviousItem();
					Municipio oldnext = getNextItem();
				#endif
				
			aux=getCurrent()->getNext();
			aux->setPrevious(getCurrent()->getPrevious());
			aux->getPrevious()->setNext(aux);
			getCurrent()->~NodoDoblementeEnlazadoMunicipio(); //Detructor
			setCurrent(aux);
			
			std::cout << "Borrando Entre nodos" << std::endl;
		
				#ifndef NDEBUG
					assert(oldprevious == getPreviousItem() and oldnext == getCurrentItem());
					assert(oldnext     == getCurrentItem());	  
				#endif
		}
		else {
			
			//Eliminamos el último elemento
			if(isLastItem()==true and getCurrent()->getPrevious()!=NULL){
			
					#ifndef NDEBUG
						Municipio oldprevious = getPreviousItem();
					#endif
					
				aux=getCurrent()->getPrevious();
				aux->setNext(NULL);
				getCurrent()->~NodoDoblementeEnlazadoMunicipio();  //Detructor
				setCurrent(aux);
			
				std::cout << "Eliminando el último elemento" << std::endl;
			
					#ifndef NDEBUG
						assert(oldprevious == getCurrentItem() and isLastItem()==true);
					#endif
			}
	
			//Eliminamos la cabeza de la lista
			if(getCurrent() == getHead() and isLastItem()==false){
		
					#ifndef NDEBUG
						Municipio oldnext = getNextItem();
					#endif
					
				aux=getCurrent()->getNext();
				aux->setPrevious(NULL);
				getCurrent()->~NodoDoblementeEnlazadoMunicipio(); //Dectructor
				setHead(aux);
				setCurrent(aux);
				
				std::cout << "Eliminamos la cabeza de la lista " << std::endl;
			
					#ifndef NDEBUG
						assert(oldnext == getCurrentItem() and isFirstItem() == true);
					#endif
			}
		}
	}

		#ifndef NDEBUG
			assert(nItems() == nitems-1);
		#endif
			
}


void ed::ListaDoblementeEnlazadaOrdenadaMunicipios::removeAll(){

	
	if(isEmpty() == false){
	
		this->setCurrent(getHead());
	
		while(_current!=NULL){		
			remove();
		}
	
		#ifndef NDEBUG
			assert(isEmpty() == true);
		#endif
	
	}
}
	

	
		
	
	
		
	



























