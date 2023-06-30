/*!
	\file MonticuloMediciones.cpp
	\brief Fichero que contiene el código de las funciones de la clase MonticuloMediciones.
	\author Antonio Ariza García
	\date 07-05-2018
*/

//#include <vector>

#include <cassert>

#include "Medicion.hpp"

#include "MonticuloMediciones.hpp"

////////////////////////////////////////////////////////////////////

// Métodos privados de la clase MonticuloMediciones

void ed::MonticuloMediciones::shiftUp(int i){
	
	if(i>=1 and i<size()){
	
		#ifndef NDEBUG
			assert((i>0) and (i<size()));
		#endif
	
	int pos = i;
	ed::Medicion aux;
	
		//Mientras que mi pos sea mayor que su padre, intercambiamos, si mi pos es la cima no hacemos nada
		while(this->getElement(pos).getPrecipitacion() > getElement(getParent(pos)).getPrecipitacion()){
			
			if(pos>=1){
				aux = getElement(pos);
				setElement(pos, getElement(getParent(pos)));
				setElement(getParent(pos), aux);
				pos=getParent(pos);
			}
		}
	
		
		#ifndef NDEBUG
			//Si es la CIMA
			if(top() == getElement(pos)){
				//Tiene hijo derecho comprobamos el assert
				if(getRightChild(pos)<size()){
					assert(getElement(pos).getPrecipitacion() >= getElement(getRightChild(pos)).getPrecipitacion());
				} //Tiene hijo izquierdo comprobamos el assert
				else if (getLeftChild(pos)<size()){
					assert(getElement(pos).getPrecipitacion() >= getElement(getLeftChild(pos)).getPrecipitacion());
				}
			}
			//Si no es la cima el elemento es menor o igual que su padre
			else{
				assert(getElement(pos).getPrecipitacion() <= getElement(getParent(pos)).getPrecipitacion());
			}	
			
		#endif
	}
}
	

void ed::MonticuloMediciones::shiftDown(int i){

	if( i>=0 and i<size()){
			
			#ifndef NDEBUG
				assert((i>=0) and (i<size()));
			#endif
			
		int pos = i;
		ed::Medicion aux;
			
			do{	
			
			//Si tiene hijo izquiedo y tiene hijo derecho
			if((getLeftChild(pos)<size() and getRightChild(pos)<size())){
			
				//Si cualquiera de mis hijos es mayor que mi pos hay que intercambiar
				if((getElement(getLeftChild(pos)).getPrecipitacion() > getElement(pos).getPrecipitacion()) or (getElement(getRightChild(pos)).getPrecipitacion() > getElement(pos).getPrecipitacion())){			
				
					//Comprobamos cual de los dos es mayor e intercambiamos
					if(getElement(getLeftChild(pos)).getPrecipitacion() > getElement(getRightChild(pos)).getPrecipitacion()){
					
						//Intercambiamos con hijo izquierdo
						aux = getElement(pos);
						setElement(pos, getElement(getLeftChild(pos)));
						setElement(getLeftChild(pos), aux);
						pos=getLeftChild(pos);
					}
					else {
						//Intercambiamos con hijo derecho
						aux = getElement(pos);
						setElement(pos, getElement(getRightChild(pos)));
						setElement(getRightChild(pos), aux);
						pos=getRightChild(pos);
					}
				}
				else{
					return;
				}
			}
			else{
			//Si no tiene dos hijos comprobamos si tiene hijo izquierdo
				if(getLeftChild(pos)<size()){
					//SI TIENE HIJO IZQUIERDO
					//Comprobamos si el hijo es mayor que el padre
					if(getElement(getLeftChild(pos)).getPrecipitacion() > getElement(pos).getPrecipitacion()){
					
						aux = getElement(pos);
						setElement(pos, getElement(getLeftChild(pos)));
						setElement(getLeftChild(pos), aux);
						pos=getLeftChild(pos);
					}
				}
			}
				
			}while(ordenado() == false);
			
		#ifndef NDEBUG
			//Si es la CIMA
			if(top() == getElement(pos)){
				//Tiene hijo derecho comprobamos el assert
				if(getRightChild(pos)<size()){
					assert(getElement(pos).getPrecipitacion() >= getElement(getRightChild(pos)).getPrecipitacion());
				} //Tiene hijo izquierdo comprobamos el assert
				else if (getLeftChild(pos)<size()){
					assert(getElement(pos).getPrecipitacion() >= getElement(getLeftChild(pos)).getPrecipitacion());
				}
			}
			//Si no es la cima el elemento es menor o igual que su padre
			else{
				assert(getElement(pos).getPrecipitacion() <= getElement(getParent(pos)).getPrecipitacion());
			}	
			
		#endif
			
	}
		//Meter poscondicion//Meter poscondicion//Meter poscondicion//Meter poscondicion//Meter poscondicion
}

bool ed::MonticuloMediciones::has(ed::Medicion medicion)const{

	for(int i=0; i < size(); i++){
		if(getElement(i).getFecha() == medicion.getFecha() and getElement(i).getPrecipitacion() == medicion.getPrecipitacion()){
			return true;
		}
	}
	return false;
}	

////////////////////////////////////////////////////////////////////////////////////7

// Métodos públicos de la clase MonticuloMediciones

void ed::MonticuloMediciones::insert(ed::Medicion medicion){

	_vector.push_back(medicion);
	shiftUp(size()-1);
	
		#ifndef NDEBUG
			assert(isEmpty() == false);
			assert(has(medicion) == true);
		#endif
}


void ed::MonticuloMediciones::remove(){

		#ifndef NDEBUG
			assert(isEmpty() == false);
		#endif
			
	_vector[0] = getElement(size()-1);
	_vector.pop_back();
	shiftDown(0);
	
}


void ed::MonticuloMediciones::removeAll(){

	_vector.clear();
	
		#ifndef NDEBUG
			assert(isEmpty() == true);
		#endif
}

void ed::MonticuloMediciones::modify(ed::Medicion & medicion){

		#ifndef NDEBUG
			assert(isEmpty() == false);
		#endif
	
	this->setElement(0, medicion);
	
	if((getElement(0).getPrecipitacion() < getElement(getLeftChild(0)).getPrecipitacion()) or (getElement(0).getPrecipitacion() < getElement(getRightChild(0)).getPrecipitacion())){
		
		shiftDown(0);
	}
	
		#ifndef NDEBUG
			assert(has(medicion) == true);
		#endif
}



void ed::MonticuloMediciones::print(){
	/*
	for(int i=0; i<size(); i++){
		std::cout << getElement(i) << " Padre=" << getParent(i) << " " << "i=" << i << std::endl;	
	}*/
	char cad;
	for(int i=0; i<size(); i++){
		std::cout.width(2); std::cout << std::right << this->getElement(i).getFecha().getDia();
		std::cout << "-";
		std::cout.width(2); std::cout << std::right << this->getElement(i).getFecha().getMes();
		std::cout << "-";
		std::cout.width(2); std::cout << std::right << this->getElement(i).getFecha().getAgno();
		std::cout << " ";
		std::cout.width(6); std::cout << std::right << this->getElement(i).getPrecipitacion();
		std::cout << std::endl;
		
			if(i%20==0 and i>2){
				
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << RESET;
		std::cout << "Pulse "; std::cout << BIGREEN; 
						   std::cout << "ENTER";
		                       std::cout << RESET; 
		                       std::cout << " para mostrar más";
		                       
		std::cout << std::endl;
		
		std::cout << "Pulse "; std::cout << BIRED; 
						   std::cout << "Q";
		                       std::cout << RESET; 
		                       std::cout << " para Salir";
		                       
		std::cout << std::endl;
		std::cout << std::endl;  
		
		//Recogemos el siguiente caracter      
		cad=std::cin.get();
				if(cad=='q' or cad=='Q'){
					return;
				}
			}
	}
}


int ed::MonticuloMediciones::buscarMedicion(ed::Fecha fecha){

	for(int i=0; i < size(); i++){
		if(getElement(i).getFecha() == fecha){
			
			return i;
		}
	}
	return -1;		
}

/*************************************************************************/
bool ed::MonticuloMediciones::ordenado(){
	
	for(int i=0; i<size(); i++){
		
		ed::Medicion aux = _vector[i];
		
		//SI TIENE HIJO IZQUIERDO COMPROBAMOS 
		if(getLeftChild(i)<size()){
			//Si el hijo es mayor que yo return false
			if(aux.getPrecipitacion() < getElement(getLeftChild(i)).getPrecipitacion()){
				return false;
			}
		}
		
		//SI TIENE HIJO DERECHO COMPROBAMOS
		if(getRightChild(i)<size()){
			//Si el hijo es mayor que yo return false
			if(aux.getPrecipitacion() < getElement(getRightChild(i)).getPrecipitacion()){
				return false;
			}
		}
	}
	return true;
}/*******************************************************************************/

bool ed::MonticuloMediciones::modifica(int i, ed::Fecha fecha){

	ed::Medicion medicion;
	float pre;
	
	float ant_precipitacion = getElement(i).getPrecipitacion();
	
	std::cout << "Introduzca la precipitacion " << std::endl;
	std::cin>>pre;
	
	medicion.setPrecipitacion(pre);
	medicion.setFecha(fecha);
	
	setElement(i,medicion);
						
		if(ant_precipitacion > pre){
			shiftDown(i);
			return true;
		}
		else{
			shiftUp(i);
			return true;
		}
	return false;
}


void ed::MonticuloMediciones::mostrarMes(int m){
	std::cout << std::endl;
	std::string mes;	
	int cont=0;
	float preci=0.0;
		
	switch(m){
		case 1:  mes = "Enero"; 		break;
		case 2:  mes = "Febrero";	break;
		case 3:  mes = "Marzo";		break;
		case 4:  mes = "Abril";		break;
		case 5:  mes = "Mayo";		break;
		case 6:  mes = "Junio";		break;
		case 7:  mes = "Julio";		break;
		case 8:  mes = "Agosto";		break;
		case 9:  mes = "Septiembre"; 	break;
		case 10: mes = "Octubre";	break;
		case 11: mes = "Noviembre";	break;
		case 12: mes = "Diciembre"; 	break;
	}

	std::cout << BIYELLOW << "Mediciones " << mes << RESET << std::endl;
	
	for(int i=0; i<size(); i++){
		
		if(getElement(i).getFecha().getMes() == m){
			
			cont++;
			
			std::cout.width(2); std::cout << std::right << this->getElement(i).getFecha().getDia();
			std::cout << "-";
			std::cout.width(2); std::cout << std::right << this->getElement(i).getFecha().getMes();
			std::cout << "-";
			std::cout.width(2); std::cout << std::right << this->getElement(i).getFecha().getAgno();
			std::cout << " ";
			std::cout.width(6); std::cout << std::right << this->getElement(i).getPrecipitacion();
			std::cout << std::endl;
	
			preci = preci + this->getElement(i).getPrecipitacion();
		}
	}
	if(cont == 0){
		std::cout << std::endl;
		std::cout << BIRED << "No hay ninguna medición en " << RESET << mes << std::endl;
	}
	else{
		std::cout << std::endl;
		std::cout << BIYELLOW << "Total Precipitaciones de " << mes << ": " << RESET << preci << std::endl; 
	}
}











