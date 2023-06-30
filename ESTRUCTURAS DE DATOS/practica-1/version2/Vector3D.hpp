/*! 
   \file Vector3D.hpp
   \brief Fichero de definición de la clase Vector3D: vector libre de tres dimensiones
*/

#ifndef _VECTOR3D_HPP_
#define _VECTOR3D_HPP_

// Entrada y salida 
#include <iostream>

// Para usar abs
#include <cmath>

// Para controlar las pre y post condiciones mediante asertos
#include <cassert>

//STL vector
#include <vector>
//#include <stdlib.h>  //abs


// Para la sobrecarga de los operadores de flujo: << y >>
using std::istream;
using std::ostream;

#define COTA_ERROR   1.0e-6 //!< Cota de error para la comparación números reales


// Se incluye la clase Vector3D dentro del espacio de nombre de la asigantura: ed
namespace ed {

//!  Definición de la clase Vector3D:  \f$ \vec{v} = (v_1, v_2, v_3) = v_1 \vec{i} + v_2 \vec{j} + v_3 \vec{k} \f$ 
class Vector3D
{
  //! \name Atributos privados de la clase Vector3D
   private: 

	double _v1;
	double _v2;
	double _v3;

   //! \name Funciones o métodos públicos de la clase Vector3D
   public:
	//! \Nombre Constructores de la clase Vector3D
	
	/*!
	\brief 	  Contructor "vacío" que crea un Vector3D inicializando cada componente a cero
	\attention  Función sobrecargada
	\note 	  Funcion inline
	\pre		  Ninguna
	\post 	  Cada uno de los observadores a de ser 0.0 para comprobar que se ha ejecutado correctamente
	\sa		  set1, set2, set3
	*/
	Vector3D(){
		
		this->set1(0.0);
		this->set2(0.0);
		this->set3(0.0);
		
			#ifndef NDEBUG
			assert((this->get1()==0.0) and (this->get2()==0.0) and (this->get3()==0.0));
			#endif
	}
	
	/*!
	\brief 	  Constructor parametrizado que crea un Vector3D a partir de las coordenadas recibidas(parametros)
	\attention  Función sobrecarga
	\note 	  Funcion inline
	\param v1	  coordenada x del vector3D
	\param v2	  coordenada y del vector3D
	\param v3   coordenada z del vector3D
	\pre 	  Ninguna
	\post 	  Cada uno de los observadores a de ser iguales a los parametros v1,v2,v3 recibidos
	\sa	 	  set1, set2, set3
	*/
	Vector3D(double v1, double v2, double v3){
		
		
		this->set1(v1);
		this->set2(v2);
		this->set3(v3);
		
			#ifndef NDEBUG
			assert((std::abs(this->get1()-v1)<COTA_ERROR)
			  and  (std::abs(this->get2()-v2)<COTA_ERROR)
			  and  (std::abs(this->get3()-v3)<COTA_ERROR));
			#endif
	}
	
	/*!
	\brief 	  "Contructor de copia" que crea un Vector3D a partir de otro Vector3D
	\attention  Función sobrecargada
	\note 	  Función inline
	\param	  Vector3D utilizado para copiar los valores al nuevo Vector3D
	\post	  Los observadores del Vector3D utilizado como parametro y los observadores del nuevo Vector3D debe ser iguales
	*/	
	Vector3D(Vector3D const &v){
		
		this->set1(v.get1());
		this->set2(v.get2());
		this->set3(v.get3());
		
			#ifndef NDEBUG
			assert((std::abs(this->get1()-v.get1())<COTA_ERROR)
			  and  (std::abs(this->get2()-v.get2())<COTA_ERROR)
			  and  (std::abs(this->get3()-v.get3())<COTA_ERROR));
			 #endif
	}


	//! \name Observadores: funciones de consulta de Vector3D

	/*!
	\brief 	  Funcion que devuelve la coordenada x de un Vector3D
	\warning 	  Se utiliza el modificador const en la definicion de la funcion para poder definir el constructor de copia y el operador =
	\attention  Se utiliza modificador const
	\note 	  Funcion inline
	\return	  Un double que representa la Coordenada x, o coordenada v1 del Vector3D
	\*/
	inline double get1()const{return _v1;}
	
	
	/*!
	\brief 	  Funcion que devuelve la coordenada x de un Vector3D
	\warning 	  Se utiliza el modificador const en la definicion de la funcion para poder definir el constructor de copia y el operador =
	\attention  Se utiliza modificador const
	\note 	  Funcion inline
	\return	  Un double que representa la Coordenada x, o coordenada v1 del Vector3D
	*/
	inline double get2()const{return _v2;}
	
	
	/*!
	\brief 	  Funcion que devuelve la coordenada x de un Vector3D
	\warning 	  Se utiliza el modificador const en la definicion de la funcion para poder definir el constructor de copia y el operador =
	\attention  Se utiliza modificador const
	\note 	  Funcion inline
	\return	  Un double que representa la Coordenada x, o coordenada v1 del Vector3D
	*/
	inline double get3()const{return _v3;}
	
	
	/*!
	\brief 	 Calcula el modulo del Vector3D actual
	\warning	 Se utiliza el modificador const en la definición de la función
	\attention Se utiliza el modificador const en la definición de la función
	\note	 Función inline
	\return	 Un double que es el modulo del Vector3D, RAIZ CUADRADA ((v1*v1)+(v2*v2)+(v3*v3))
	\post 	 El valor devuelto debe ser ((v1*v1)+(v2*v2)+(v3*v3))
	\sa 	 	 get1(), get2(), get3() de la clase Vector3D
	*/
	double modulo()const;
	
	/*!
	\brief	 Calcula el producto escalar del vector actual y el vector pasado como parametro
	\warning 	 Se utiliza el modificador const en la definicion de la funcion
	\param 	 Recibe v pasado como referencia constante que es de tipo Vector3D 
	\return	 Producto escalar de dos vectores
	\pre	    	 Ninguna	
	\post	 Devuelve (get1()*v.get1()) + (get2()*v.get2()) + (get3()*v.get3())
	\sa 		 get1(), get2() get3() de la clase Vector3D
	*/
	double dotProduct(Vector3D const &v)const;
	
	/*!
	\brief 	 Calcula el angulo en radianes entre el Vector3D actual y el pasado como referencia const
	\warning 	 Se utiliza el modificador const en la definicion de la funcion
	\param	 Recibe un Vector3D pasado como referencia const
	\return 	 Un double, que representa el angulo entre dos Vectores3D
	\pre	  	 (modulo() * v.modulo())>0
	\post	 El valor devuelo = arcoseno (dotProdut / (modulo()*v.modulo()))
	\sa 		 modulo(), dotProdut() de la clase Vector3D
	*/
	double angulo(Vector3D const &v)const;
	
	/*!
	\brief 	 Calcula el angulo alfa del Vector3D actual
	\warning	 Se utiliza const en la definicion de la funcion
	\param	 Ninguno
	\return 	 angulo(Vector(1,0,0))
	\pre	 	 El modulo del vector actual debe ser mayr que 0
	\post 	 El valor devuelto debe ser igual al angulo (vector(1,0,0))
	\sa		 angulo() de la Clase Vector3D
	*/
	double alfa()const;
	
	/*!
	\brief 	 Calcula el angulo beta del Vector3D actual
	\warning	 Se utiliza const en la definicion de la funcion
	\param	 Ninguno
	\return 	 angulo(Vector(0,1,0))
	\pre	 	 El modulo del vector actual debe ser mayr que 0
	\post 	 El valor devuelto debe ser igual al angulo (vector(0,1,0))
	\sa		 angulo() de la Clase Vector3D
	*/
	double beta()const;
	
	
	/*!
	\brief 	 Calcula el angulo beta del Vector3D actual
	\warning	 Se utiliza const en la definicion de la funcion
	\param	 Ninguno
	\return 	 angulo(Vector(0,0,1))
	\pre	 	 El modulo del vector actual debe ser mayr que 0
	\post 	 El valor devuelto debe ser igual al angulo (vector(0,0,1))
	\sa		 angulo() de la Clase Vector3D
	*/
	double gamma()const;
	
	
	/*!
	\brief 	 Calcula el producto vectorial de dos vectores
	\warning	 Se utiliza el modificacor const en la definicion de la funcion
	\param 	 Recibe v que es de tipo Vector3D y es pasado por referencia const
	\return	 Vector3D que es el producto vectoria de dos vectores
	\pre		 Los vectores u y v no son paralelos entre sí, ni nulos. this->angulo(v)>0, this->modulo()>0, v.modulo()>0
	\post 	 (dotProduct(valordevuelto)==0) and (v.dotProduct(valordevuelto)==0)
	*/
	ed::Vector3D crossProduct(Vector3D const &v)const;
	
	
	/*!
	\brief 	 Calculo el producto mixto de varios vectores de tipo Vector3D
	\warning 	 Se utiliza el modificador const en la definicion de la funcion
	\note	 Primero se calcula el producto vectorial de los vectores pasados como referencia y despues se calcula el producto escalar de dicho resultado.
	\param 	 v de tipo Vector3D pasado como referencia const
	\param 	 w de tipo Vector3D pasado como referencia const
	\return 	 Devuelve el resultado de calcular el producto escalar del vector actual con el obtenido al calcular el producto vectorial de otros dos vectores dotProduct(v.crossProduct(w))
	\pre 	 Ninguna
	\post 	 valordevuelo == dotProduct(v.crossProduct(w))
	\sa 	 	 dotProduct() y crossProduct()
	*/
	double productoMixto(Vector3D const &v, Vector3D const &w)const;
	


	//! \name Modificadores: funciones de modificación de Vector3D

	/*!
	\fn 	 	 inline void set1(double v)
	\brief 	 funcion que asigna un valor v1 a la coordenada "x" del Vector3D
	\note 	 Funcion inline
	\param	 v que representa el nuevo valor a asignar a la coordenada "x" del Vector3D
	\pre	 	 Ninguna
	\post	 get1()==v
	\sa 	  	 set1()
	*/
	inline void set1(double v){
	
		_v1=v;
		
			#ifndef NDEBUG
			assert((std::abs(this->get1()-v)<COTA_ERROR));
			#endif
	}
	
	
	/*!
	\fn 		 inline void set2(double v)
	\brief 	 funcion que asigna un valor v1 a la coordenada "y" del Vector3D
	\note 	 Funcion inline
	\param	 v que representa el nuevo valor a asignar a la coordenada "y" del Vector3D
	\pre	 	 Ninguna
	\post	 get2()==v
	\sa 	  	 set2()
	*/
	inline void set2(double v){
	
		_v2=v;
			
			#ifndef NDEBUG
			assert((std::abs(this->get2()-v)<COTA_ERROR));
			#endif
	}
	
	
	/*!
	\fn 		 inline void set3(double v)
	\brief 	 funcion que asigna un valor v1 a la coordenada "z" del Vector3D
	\note 	 Funcion inline
	\param	 v que representa el nuevo valor a asignar a la coordenada 2z" del Vector3D
	\pre	 	 Ninguna
	\post	 get3()==v
	\sa 	  	 set3()
	*/
	inline void set3(double v){
	
		_v3=v;
			
			#ifndef NDEBUG
			assert((std::abs(this->get3()-v)<COTA_ERROR));
			#endif
	}
	
	
	/*!
	\brief	  Modifica el vector sumando una constante a cada componente
	\attention  No se utiliza el modificador const
	\param	  k una constante de tipo double para sumarla a cada componente
	\return	  Nada es de tipo void
	\pre		  Ninguna
	\post	  Los observadores deben ser igual a los observadores anteriores + k
	\sa 		  set1(), set2(), set3(), get1(), get2(), get3()
	*/
	void sumConst(double const &k);
	
	
	/*!
	\brief 	  Modifica el vector3D sumando a cada componente el equivalente de otro Vector3D pasado como parametro
	\attention  No se utiliza el modificador const
	\param	  v que es de tipo Vector3D
	\return 	  Nada, es void
	\pre	 	  Ninguna
	\post	  Los observadores de cada componente del vector tienen que ser igual a los observadors anteriores mas la componente del vector pasado como parametro
	\sa		  set1(), set2(), set3(), get1(), get2(), get3()
	*/
	void sumVect(Vector3D const &v);
	
	
	/*!
	\brief	  Modifica el vector multiplicando una constante a cada componente
	\attention  No se utiliza el modificador const
	\param	  k Constante de tipo double utilizada para multiplicar cada componente del vectoe
	\return 	  Nada, es de tipo void
	\pre		  Ninguna
	\post	  Los observadores deben ser iguale a los observadores anteriores * k
	\sa 		  set1(), set2(), set3(), get1(), get2(), get3()
	*/
	void multConst(double const &k);
	
	
	/*!
	\brief 	  Modifica el vector multiplicando a cada componente la componente equivalente del vector pasado como parametro
	\attention  No se utiliza el modificador const
	\param 	  v que representa un vector de tipo Vector3D
	\return     Nada, es de tipo void
	\pre		  Ninguna
	\post       Los observadores de cada componente debe ser iguales a los observadores anteriores multiplicados por cada componente del Vector3D
	\sa 		  set1(), set2(), set3(), get1(), get2(), get3()
	*/
	void multVect(Vector3D const &v); 
	

    //! \name Operadores de la clase
   
	/*!
	\brief	  Operador de asignacion, copia un Vector3D en otro Vector3D
	\attention  Se sobrecarga el operador de asignacion =
	\warning    Se requiere que las funciones de acceso tengan el modificador const
	\param	  Objeto de tipo Vector3D pasado como referencia const
	\return     Vector3D que es la copia de otro Vector3D
	\pre	  	  El Vector3D objeto debe ser diferente del vector actual
	\sa		  get1(), get2(), get3(), set1(), set2(), set3(), operator =
	*/
	Vector3D & operator=(Vector3D const &objeto);

	
	/*!
	\brief 	 Operador de igualdad, compara si un vector3D es igual a otro Vector3D componetne a componente
	\warning   Se utiliza el modificador const
	\attention Se sobrecarga el operador de asignacion "=="
	\param	 Objeto Vector3D pasado como referencia const
	\return    tipo bool, retorna true o false si los Vectores3D son iguales o no
	\pre	 	 Ninguna
	\post	 get1()==objeto.get1() and get2()==objeto.get2() and get3()==objeto.get3()
	\sa 		 get1(), get2() ,get3(), set1(), set2(), set3(), operator ==
	*/
	bool operator == (Vector3D const &objeto) const;

	
	/*!
	\brief	 Operador de suma binaria: operador que suma el vector actual con el pasado como parametro
	\warning   Se utiliza el modificar const en la definicion de la funcion
	\attention Se sobrecarga el operador +
	\param     Objeto que es de tipo Vector3d pasado como referencia const
	\return    Vector3D que es la suma del vector actual con el pasado como parametro
	\pre		 Ninguna
	\post      Valor devuelto get1() == get1()+objeto.get1() and valor devuelto get2()==get2()+objeto.get2() and valordevuelto get3()== get3()+objeto.get3()
	\sa 		 set1(), set2(), set3(), get1(), get2(), get3(), operator +
	*/
	Vector3D operator + (Vector3D const &objeto)const;
	
	
	/*!
	\brief	 Operador de suma unario, operador que es una copia del vector actual
	\warning   Se utiliza el modificador const en la definicion de la funcion
	\return    Vector3D
	\pre		 Ninguna
	\post 	 valordevuelto.get1() == get1() and valordevuelto.get2()==get2() and valordevuelto.get3()==get3()
	\sa 		 set1(), set2(), set3(), get1(), get2(), get3(), operador +
	*/
	Vector3D operator + ()const;
	
	
	/*!
	\brief 	 Operador de resta unario: operador que resta el vector actual con el pasado como parametro
	\warning 	 Se utiliza el modificar const en la deficion de la funcion
	\return    Vector3D que es la recta del actual con el pasado como parametro
	\pre 	 Ninguna
	\post 	 valordevuelto.get1()==get1() -objeto.get1() and valordevuelto.get2()== get2() -objeto.get2() and valordevuelto.get3()== get3() -objeto.get3()
	\sa 		 set1(), set2(), set3(), get1(), get2(), get3()
	*/
	Vector3D operator - (Vector3D const &objeto)const;
	
	
	/*!
	\brief 	 Operador de resta unario: operador que es el vector opuesto al actual
	\warning 	 Se utiliza el modificar const en la deficion de la funcion
	\return    Vector3D que es el opuesto al vector actual
	\pre 	 Ninguna
	\post 	 valordevuelto.get1()==-get1() and valordevuelto.get2()== -get2() and valordevuelto.get3()== -get3()
	\sa 		 set1(), set2(), set3(), get1(), get2(), get3()
	*/
	Vector3D operator - ()const;
	
	
	/*!
	\brief 	Operador producto escalar de dos vectores, operador que multiplica las componentes del vector actual con las componentes del vector pasado como parametro
	\warning  Se utiliza el modificador const en la definicion de la funcion
	\param 	objeto que es de tipo Vector3D pasado como referencia const
	\return   double que es el producto escalar de dos vectores3D
	\pre      Ninguna
	\post     valordevuelto == get1()*objeto.get1() + get2()*objeto.get2() + get3()*objeto.get3()
	\sa       set1(), set2(), set3(), get1(), get2(), get3(), operator ==
	*/
	double operator * (Vector3D const &objeto)const;
	
	
	/*!
	\brief    Operador producto por un real, operador que multiplica las componentes del Vector3D por una constante k
	\warning  Se utiliza el modificador const en la definicion de la funcion
	\param    k de tipo double pasado como referencia const
	\pre      Ninguna
	\post     valordevuelto.get1() == get1()*k and valordevuelto.get2() == get2()*k and valordevuelto.get3() == get3()*k
	\sa       set1(), set2(), set3(), get1(), get2(), get3()
	*/
	Vector3D operator * (double k)const;
	
	
	/*!
	\brief 	Operador de producto vectorial: operador que calcula el producto vectorial de dos Vectores
	\warning  Se utiliza el modificador const en la deficion de la funcion
	\param    v Vector3D pasado como referencia const
	\pre      this->angulo(objeto)>0, this.modulo > 0, objeto.modulo() >0
	\post     dotProduct(valordevuelto) == 0
	\post     objeto.dotProduct(valordevuelto) == 0
	\post     valordevuelto.modulo() == modulo() * objeto.modulo() * sin(angulo(objeto))
	\sa       get1(), get2(), get3(), dotProduct(), modulo()
	*/
	Vector3D operator ^ (Vector3D const &objeto)const;

	//! \name Funciones lectura y escritura de la clase Vector3D
	
	/*!
	\fn 		void leerVector3D();
	\brief    Asigna a un Vector3D las coordenadas x, y, z, leídas desde el teclado
	\warning  Se deben teclear números tipo double
	\pre      Ninguna
	\post     Los atributos get1(), get2(), get3() deben tener valores númericos
	\sa       set1(), set2(), set3()
	*/
	void leerVector3D();
	
	
	/*!
	\fn	   	void escribirVector3D();
	\brief    Escribe por pantalla las coordenadas de un vector3D de la forma (v1,v2,v3)
	\pre 	El Vector3D debe tener valores asignados a sus coordenadas
	\post     Ninguna
	\sa       get1(), get2(), get3()
	*/
	void escribirVector3D()const;
	

}; // Fin de la definición de la clase Vector3D


//////////////////////////////////////////////////////////////////////////////////////

//! \name Funciones que utilizan un objetos de la clase Vector3D, pero que no pertenecen a la clase Vector3D

	/*!
	\brief 	Operador por un real, operador que multiplica las componentes del vector pasado como parametro por la constante k
	\note	La funcion no es inline
	\param	k de tipo double
	\param    obejto de tipo Vector3D pasado como referencia const
	\pre 	Ninguna
	\post     valordevuelto.get1() == objeto.get1()*k and valordevuelto.get2() == objeto.get2() and valordevuelto.get3() == objeto.get3()
	\return   Vector3D 
	\sa 	     set1(), set2(), set3(), get1(), get2(), get3()
	*/
     Vector3D & operator* (double k, Vector3D const & objeto);
	

	/*!
	\fn		 istream &operator>> (istream &stream, Vector3D &objeto);
	\brief     Sobrecarga del operador de entrada o lectura >>
	\attention Función amiga de la clase Vector3D
	\param     stream flujo de entrada
	\param     objeto Vector3D al que se le van a asignar nuevos valores.
	\pre		 El vector3D objeto debe existir
	\post      El Vector objeto tiene asignado como coordenads los valores leidos desde el teclado
	\sa operator<<
	*/
     istream &operator>>(istream &stream, Vector3D &objeto);
 
	
	/*!
	\fn		 ostream &operator<< (ostream &stream, Vector3D const &objeto);
	\brief     Sobrecarga del operador de salida o escritura "<<"
	\attention Función amiga de la clase Vector3D
	\param     stream flujo de salida
	\param     objeto Vector3D al que se le van a escribir sus coordenadas por pantalla
	\pre		 El vector3D objeto debe existir
	\post      Se escriben por pantalla las coordenadas del Vector objeto de la forma (v1,v2,v3)
	\sa operator>>
	*/   
	ostream &operator<<(ostream &stream, Vector3D const &objeto);


} // \brief Fin de namespace ed.

//  _VECTOR3D_HPP_
#endif 
