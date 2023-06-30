/*! 
   \file Vector3D.cpp
   \brief Fichero que contiene el código de las funciones de la clase Vector3D
*/


// Ficheros de cabecera
#include <iostream>

// Para usar sqrt, acos
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>
#include <cerrno>	//errno
#include <cstring>	//stderror
#include <cstdio>	//perror

#include "Vector3D.hpp"

// OBSERVADORES
double ed::Vector3D::modulo()const{
	
	
	double modulo;
	
	modulo=sqrt((get1()*get1())+(get2()*get2())+(get3()*get3()));
	
	
		#ifndef NDEBUG
		assert(std::abs(modulo-(sqrt(get1()*get1()
		                            +get2()*get2()
		                            +get3()*get3())))<COTA_ERROR);
		#endif
	
	return modulo;
}

double ed::Vector3D::dotProduct(Vector3D const &v)const{

	double producto;
		producto=(this->get1()*v.get1())+(this->get2()*v.get2())+(this->get3()*v.get3());
		
		#ifndef NDEBUG
		assert(std::abs(producto- ((this->get1()*v.get1())
		                     	 +(this->get2()*v.get2())
		                          +(this->get3()*v.get3())))<COTA_ERROR);
		#endif
		
	return producto;
}



double ed::Vector3D::angulo(Vector3D const &v)const{
	
	double valor;
	double angulo;
			//Precondicion
			#ifndef NDEBUG
			assert((this->modulo() * v.modulo())>0);
			#endif
		
		valor=((dotProduct(v))/(this->modulo()*v.modulo()));
		
		//Para no sobrepasar el dominio del arcocoseno
		if(valor>1){
			valor=1;
		}
		else if(valor < -1){
			valor= -1;
		}
		
		angulo=acos(valor);
		
		if(errno==33){
			perror("Error funcion acos");
			std::cout<<std::endl;
		}
		
		angulo=acos(valor);
		
		
			#ifndef NDEBUG 
			assert(std::abs(angulo - acos(valor))<COTA_ERROR);
			#endif
	return angulo;
}


double ed::Vector3D::alfa()const{
	
	double alfa;
	
	Vector3D v(1,0,0);
	
		alfa=angulo(v);
	
		#ifndef NDEBUG
		assert(alfa==angulo(v));
		#endif
	return alfa;
}
	
	
double ed::Vector3D::beta()const{
	
	double beta;
	
	beta=angulo(Vector3D(0,1,0));
	
		#ifndef NDEBUG
		assert(beta==angulo(Vector3D(0,1,0)));
		#endif
	return beta;
}


double ed::Vector3D::gamma()const{

	double gamma;
	
	Vector3D v(0,0,1);
	
	gamma=angulo(v);
	
		#ifndef NDEBUG
		assert(gamma==angulo(v));
		#endif
	return gamma;
}


ed::Vector3D ed::Vector3D::crossProduct(ed::Vector3D const &v)const{
	
	
	#ifndef NDEBUG
	assert( (this->angulo(v)>0.0) and (this->modulo()>0.0) and (v.modulo()>0.0) );
	#endif
	
	double w1= ((get2()*v.get3())-(get3()*v.get2()));
	double w2= ((-get1()*v.get3())+(get3()*v.get1()));
	double w3= ((get1()*v.get2())-(get2()*v.get1()));
	
	Vector3D w(w1,w2,w3);
	
		#ifndef NDEBUG
		assert(std::abs(dotProduct(w))<COTA_ERROR);
		assert(std::abs(v.dotProduct(w))<COTA_ERROR);
		assert(std::abs(w.modulo()-(modulo()*v.modulo()*sin(angulo(v))))<COTA_ERROR);
		#endif
	
	return w;
}
	
	
double ed::Vector3D::productoMixto(Vector3D const &v, Vector3D const &w)const{

	double res;
	
	res=dotProduct(v.crossProduct(w));
	
		#ifndef NDEBUG
		
		assert((std::abs(v.modulo()-0)>COTA_ERROR)
		  and  (std::abs(w.modulo()-0)>COTA_ERROR)
		  and  (v.angulo(w)>0));
		 
		assert((std::abs(res-(dotProduct(v.crossProduct(w)))))<COTA_ERROR);
		#endif
	return res;
}
// COMPLETAR


////////////////////////////////////////////////////////////////

// MODIFICADORES
void ed::Vector3D::sumConst(double const &k){

	#ifndef NDEBUG
	Vector3D old;
		old.set1(this->get1());
		old.set2(this->get2());
		old.set3(this->get3());
		//Vector3D old(*this);
	#endif
	
	set1(this->get1()+k);
	set2(this->get2()+k);
	set3(this->get3()+k);
	
		#ifndef NDEBUG
		assert((std::abs(this->get1()-(old.get1()+k))<COTA_ERROR) 
		  and  (std::abs(this->get1()-(old.get1()+k))<COTA_ERROR)
		  and  (std::abs(this->get1()-(old.get1()+k))<COTA_ERROR));    
		#endif
}

void ed::Vector3D::sumVect(Vector3D const &v){

	#ifndef NDEBUG
	Vector3D old;
		old.set1(this->get1());
		old.set2(this->get2());
		old.set3(this->get3());
	#endif
	
	set1(get1()+v.get1());
	set2(get2()+v.get2());
	set3(get3()+v.get3());
	
		#ifndef NDEBUG
		assert((std::abs(this->get1()-(old.get1()+v.get1()))<COTA_ERROR)
		  and  (std::abs(this->get2()-(old.get2()+v.get2()))<COTA_ERROR) 
		  and  (std::abs(this->get3()-(old.get3()+v.get3()))<COTA_ERROR));
		#endif
}
	
void ed::Vector3D::multConst(double const &k){
	
	#ifndef NDEBUG
	Vector3D old;
		old.set1(this->get1());
		old.set2(this->get2());
		old.set3(this->get3());
	#endif
	
	set1(get1()*k);
	set2(get2()*k);
	set3(get3()*k);
	
		#ifndef NDEBUG
		assert((this->get1()==old.get1()*k) 
		   and (this->get2()==old.get2()*k) 
		   and (this->get3()==old.get3()*k));
		#endif
}

void ed::Vector3D::multVect(Vector3D const &v){

	#ifndef NDEBUG
	Vector3D old;
		old.set1(this->get1());
		old.set2(this->get2());
		old.set3(this->get3());
	#endif
	
	set1(this->get1()*v.get1());
	set2(this->get2()*v.get2());
	set3(this->get3()*v.get3());
	
		#ifndef NDEBUG
		assert((this->get1()==old.get1()*v.get1()) 
		   and (this->get2()==old.get2()*v.get2()) 
		   and (this->get3()==old.get3()*v.get3()));
		#endif
}
// COMPLETAR



////////////////////////////////////////////////////////////////////////////////

// OPERADORES
bool ed::Vector3D::operator== (Vector3D const &objeto) const{
	
	if((this->get1()!=objeto.get1()) or 
	   (this->get2()!=objeto.get2()) or 
	   (this->get3()!=objeto.get3())){
	
		#ifndef NDEBUG	
		assert((std::abs(this->get1()-objeto.get1())>COTA_ERROR) 
		    or (std::abs(this->get2()-objeto.get2())>COTA_ERROR) 
		    or (std::abs(this->get3()-objeto.get3())>COTA_ERROR));
		#endif
		
		return false;
	}
	else{
		#ifndef NDEBUG
		assert((std::abs(this->get1()-objeto.get1())<COTA_ERROR) 
		   and (std::abs(this->get2()-objeto.get2())<COTA_ERROR) 
		   and (std::abs(this->get3()-objeto.get3())<COTA_ERROR));
		#endif
		
		return true;
	}
}
			
ed::Vector3D & ed::Vector3D::operator= (Vector3D const &objeto){
	
	if(this !=&objeto){
		this->set1(objeto.get1());
		this->set2(objeto.get2());
		this->set3(objeto.get3());
	
		#ifndef NDEBUG
		assert((std::abs(this->get1()-objeto.get1())<COTA_ERROR)
		   and (std::abs(this->get2()-objeto.get2())<COTA_ERROR)
		   and (std::abs(this->get3()-objeto.get3())<COTA_ERROR));
		  #endif
		
	}
	return *this;
}

ed::Vector3D ed::Vector3D::operator + (Vector3D const &objeto)const{
	
	Vector3D aux;
	
	aux.set1(get1()+objeto.get1());
	aux.set2(get2()+objeto.get2());
	aux.set3(get3()+objeto.get3());
	
		#ifndef NDEBUG
		assert((std::abs(aux.get1()-(get1()+objeto.get1()))<COTA_ERROR)
		  and  (std::abs(aux.get2()-(get2()+objeto.get2()))<COTA_ERROR) 
		  and  (std::abs(aux.get3()-(get3()+objeto.get3()))<COTA_ERROR));
		#endif
		
	return aux;
}

ed::Vector3D ed::Vector3D::operator +()const{
	
	Vector3D aux;
	
	aux.set1(get1());
	aux.set2(get2());
	aux.set3(get3());
	
		#ifndef NDEBUG
		assert((std::abs(aux.get1()-get1())<COTA_ERROR)
		   and (std::abs(aux.get2()-get2())<COTA_ERROR)
		   and (std::abs(aux.get3()-get3())<COTA_ERROR));
		#endif
		
	return aux;
}

ed::Vector3D ed::Vector3D::operator- (Vector3D const &objeto)const{

	Vector3D aux;
	
	aux.set1(get1()-objeto.get1());
	aux.set2(get2()-objeto.get2());
	aux.set3(get3()-objeto.get3());
	
		#ifndef NDEBUG
		assert((std::abs(aux.get1()-(get1()-objeto.get1()))<COTA_ERROR) 
		   and (std::abs(aux.get2()-(get2()-objeto.get2()))<COTA_ERROR) 
		   and (std::abs(aux.get3()-(get3()-objeto.get3()))<COTA_ERROR));
		#endif
			
	return aux;
}

ed::Vector3D ed::Vector3D::operator - ()const{
	
	Vector3D aux;
	
	aux.set1(-get1());
	aux.set2(-get2());
	aux.set3(-get3());
	
		#ifndef NDEBUG
		assert((std::abs(aux.get1()+get1())<COTA_ERROR) 
		   and (std::abs(aux.get2()+get2())<COTA_ERROR) 
		   and (std::abs(aux.get3()+get3())<COTA_ERROR));
		#endif
	
	return aux;
}
	
	
ed::Vector3D ed::Vector3D::operator * (double k)const{

	Vector3D aux;
	
	aux.set1(get1()*k);
	aux.set2(get2()*k);
	aux.set3(get3()*k);
	
		#ifndef NDEBUG
		assert((std::abs(aux.get1()-get1()*k)<COTA_ERROR) 
		   and (std::abs(aux.get2()-get2()*k)<COTA_ERROR) 
		   and (std::abs(aux.get3()-get3()*k)<COTA_ERROR));
		#endif
	
	return aux;
}	

double ed::Vector3D::operator * (Vector3D const &objeto)const{
	
	double aux;
	
	aux= ((get1()*objeto.get1())+(get2()*objeto.get2())+(get3()*objeto.get3()));
	
		#ifndef NDEBUG
		assert((std::abs(aux-((get1()*objeto.get1())
		                +(get2()*objeto.get2())
		                +(get3()*objeto.get3())))<COTA_ERROR));
		#endif
		
	return aux;
}


ed::Vector3D ed::Vector3D::operator ^ (Vector3D const &objeto)const{
	
	double w1= ((get2()*objeto.get3())-(get3()*objeto.get2()));
	double w2= ((-get1()*objeto.get3())+(get3()*objeto.get1()));
	double w3= ((get1()*objeto.get2())-(get2()*objeto.get1()));
	
	Vector3D w(w1,w2,w3);
	
		#ifndef NDEBUG
		assert(dotProduct(w)==0);
		assert(objeto.dotProduct(w)==0);
		assert(std::abs(w.modulo()-(modulo()*objeto.modulo()*sin(angulo(objeto))))<COTA_ERROR);
		#endif
	
	return w;
}
// COMPLETAR



////////////////////////////////////////////////////////////////////////////////

// FUNCIONES DE LECTURA Y ESCRITURA
void ed::Vector3D::leerVector3D(){

	double v1,v2,v3;

	std::cout<<"Creando Vector v=(v1,v2,v3)"<<std::endl;
	std::cout<<"Introduzca la componente v1 del vector"<<std::endl;
	std::cin>>v1;
	std::cout<<"Introduzca la componente v2 del vector"<<std::endl;
	std::cin>>v2;
	std::cout<<"Introduzca la componente v3 del vector"<<std::endl;
	std::cin>>v3;
	
	this->set1(v1);
	this->set2(v2);
	this->set3(v3);
}

void ed::Vector3D::escribirVector3D()const{

	std::cout<<"("<<get1()<<","<<get2()<<","<<get3()<<")"<<std::endl;
}
// COMPLETAR


////////////////////////////////////////////////////////////////////////////////


// Se incluyen los operadores sobrecargados dentro del espacio de nombres de ed

namespace ed{


// Producto "por un" escalar (prefijo): k * v
ed::Vector3D & operator* (double k, ed::Vector3D const & objeto)
{
	ed::Vector3D *aux = new ed::Vector3D();
	
	aux->set1( k * objeto.get1());
	aux->set2( k * objeto.get2());
	aux->set3( k * objeto.get3());
	
		#ifndef NDEBUG
		assert((std::abs(aux->get1()-(objeto.get1()*k))<COTA_ERROR) 
		   and (std::abs(aux->get2()-(objeto.get2()*k))<COTA_ERROR) 
		   and (std::abs(aux->get3()-(objeto.get3()*k))<COTA_ERROR));
		#endif


	return *aux;
}


// Sobrecarga del operador de salida
// Se escriben por pantalla las coordenadas del vector 3D  de la forma (v1, v2, v3)
ostream &operator<<(ostream &stream, ed::Vector3D const &objeto)
{
	stream << "("<<objeto.Vector3D::get1() << "," <<objeto.Vector3D::get2() << ","
	       << objeto.Vector3D::get3() <<")" <<std::endl;

  return stream;
}

// Sobrecarga del operador de entrada
istream &operator>>(istream &stream, ed::Vector3D &objeto)
{
  double v1,v2,v3;
  
  stream>>v1;
  stream>>v2;
  stream>>v3;
  
  objeto.set1(v1);
  objeto.set2(v2);
  objeto.set3(v3);
  

  return stream;
} 

} // Fin del espacio de nombres ed
