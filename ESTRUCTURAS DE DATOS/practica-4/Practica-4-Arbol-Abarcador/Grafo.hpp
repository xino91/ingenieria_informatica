/*!
	\file    Grafo.hpp
	\brief   Se define el TAD Grafo.
	\author  Antonio Ariza García
	\date    19-05-2018
*/

#ifndef _GRAFO_HPP
#define _GRAFO_HPP


#include <cassert>
#include <vector>
#include "punto2D.hpp"
#include "Vertice.hpp"
#include "Lado.hpp"
#include "macros.hpp"


/*!	
	\namespace ed
	\brief Espacio de nombres para la asignatura Estructuras de Datos
*/
namespace ed
{

//!  Definición de la clase Grafo
class Grafo
{
	//! \name Atributos privados de la clase Grafo
	private:

	std::vector < std::vector<double> > _matriz;		//!< Matriz de Adyacencias
	std::vector <Vertice> _vectorVertices;			//!< Vector de Vertices
	std::vector <Lado> 	  _vectorLados;			//!< Vector de Lados	
	std::vector <int> _padre;					//!< Vector que me hará falta para evitar ciclos en Kruskal
	int _cursorVertices;						//!< Cursor para Vertices
     int _cursorLados;							//!< Cursor para lados
     int _nVertices;							//!< Numero de Vértices
     int _nLados;								//!< Numero de Lados
     bool _dirigido;							//!< Es dirigido o no
     int _memoria;								//!< Memoria total de la matriz de adyacencia, numero de vertices para reserva memoria
		

	//! \name métodos públicos de la clase Grafo
	public:
	
	//! \name Constructores de la clase Grafo
/*!
	\brief     Constructor parametrizado con valores por defecto       
	\note      Función inline
	\warning   Los parámetros tienen valores por defecto
	\param 	 memoria: indica el numero de vertices para reservar memoria para la matriz adyacencias, de tipo int
	\param     dirigido: indica si el grafo es dirigido o no, de tipo bool
	\pre       Ninguna
	\post      Ninguna
*/
Grafo(int memoria=0, bool dirigido=false){

	if(memoria<0){
     	_memoria=0;
     }
		
		//Vector que contiene vectores
		_matriz.resize(memoria);
		for(int i=0; i<memoria; i++){
			//Vector que contendra las filas que haran de matriz
			//Siempre se creara una matriz n*n
			_matriz[i].resize(memoria);
		}
		
	_nVertices=0;
	_nLados=0;
	_memoria=memoria;
	_dirigido=dirigido;
}
	
	
	/**************************************************************************/
	
	//! \name Observadores: funciones de consulta de la clase Grafo

/*! 
	\brief   Función que devuelve si el grafo está vacío
	\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
	\note    Función inline y redefinida de la clase padre GrafoInterfaz
	\return  true si el grafo no tiene vertice, false en otro caso
	\pre     Ninguna
	\post    valor devuelto == (size() == 0)
	\sa      getVertices(), getLados(), esDirigido(), Adyacente()
*/	
	inline bool isEmpty(){
		
		bool valor;
		if(_nVertices == 0 and _nLados == 0){
			valor = true;
		}
		else{
			valor = false;
		}
		
			#ifndef NDEBUG
				assert( (valor == (_vectorVertices.size() == 0)) );
			#endif 
		
		return valor;
	}

/*! 
	\brief   Función que devuelve el numero de Vertices del grafo
	\attention Se utiliza el modificador const en la definición de la función para poder definir el constructor de copia y el operador de asignacion "="
	\note    Función inline y redefinida de la clase padre GrafoInterfaz
	\return  int: Valor del atributo que representa al numero de Vertices del grafo
	\pre     Ninguna
	\post    Ninguna
	\sa      getLados()
*/
	inline int getVertices()const {return _nVertices;}

	
/*!
	\brief	  Función que devuelve el numero de Lados del grafo
	\attention  Se utiliza el modificador const en la definicion de la función para poder definir el constructor de copia y el operador de asignación "="
	\note 	  Funcion inline
	\return	  int: Valor del atributo que representa al numero de Lados
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), isEmpty()
*/
	inline int getLados() const {return _nLados;}
	
/*!
	\brief	  Función que devuelve la matriz 
	\attention  Se utiliza el modificador const 
	\note 	  Funcion inline
	\return	  std::vector < std::vector<double> >
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), isEmpty()
*/
	inline std::vector < std::vector<double> > getMatriz() const {return _matriz;} 
	/*************************************************************************/

	
/*!
	\brief	  Función que devuelve el vector de Vertices
	\attention  Se utiliza el modificador const 
	\note 	  Funcion inline
	\return	  atributo privado que corresponde con vector de Vertices de tipo Vertice
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), isEmpty()
*/	
	inline std::vector <Vertice> getVectorVertices() const {return _vectorVertices;}
	
	
/*!
	\brief	  Función que devuelve el vector de lados
	\attention  Se utiliza el modificador const 
	\note 	  Funcion inline
	\return	  atributo que corresponde con el vector de lados de tipo Lado
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), isEmpty()
*/
	inline std::vector <Lado> getVectorLados() const {return _vectorLados;};
	
	
/*!
	\brief	  Función que devuelve el vector de padre
	\attention  Se utiliza el modificador const 
	\note 	  Funcion inline
	\return	  atributo que corresponde con el vector de padre de tipo int
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), getLado(), getVertice()
*/
	inline std::vector <int> getPadre() const {return _padre;}
	
	
/*!
	\brief	  Función que devuelve un vertice
	\attention  Se utiliza el modificador const 
	\note 	  Funcion inline
	\param	  i: de tipo int que corresponde con el vertice a devolver del vector de Vertices
	\return	  Un vertice correspondiente con [i]
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), isEmpty()
*/	
	inline ed::Vertice getVertice(int i) const {return _vectorVertices.at(i);}
	
	
/*!
	\brief	  Función que devuelve un lado
	\attention  Se utiliza el modificador const 
	\note 	  Funcion inline
	\param	  i: de tipo int que corresponde con el lado a devolver del vector de Lados
	\return	  Un Lado correspondiente con [i]
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), isEmpty()
*/	
	inline ed::Lado getLado(int i) const {return _vectorLados.at(i);}
		
	
/*!
	\brief	  Función que devuelve un dato de la matriz
	\attention  Se utiliza el modificador const 
	\note 	  Funcion inline
	\param	  i: de tipo int que corresponde con fila
	\param 	  j: de tipo int que corresponde con columna
	\return	  Un vertice correspondiente con [i]
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), getLado(), getVertice()
*/	
	inline double getDatoMatriz(int i, int j) const {return _matriz[i][j];}
	

/*!
	\brief	  Función que devuelve si un grafo es dirigido o es no dirigido
	\attention  Se utiliza el modificador const, no puede modificar el atributo
	\note 	  Funcion inline
	\return	  true si el grafo es dirigido , false en otro caso
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados()
*/
	inline bool esDirigido() const {
		if(_dirigido == true){
			return true;
		}
		return false;
	}	


/*!
	\brief	  Función que devuelve si dos Vertices son adyacentes
	\attention  Se utiliza el modificador const
	\note 	  Funcion inline
	\param 	  u: de tipo Vertice
	\param 	  v: de tipo Vertice
	\return	  true si los Vertices son adyacentes, false en otro caso
	\pre 	  has(u) and has(v)
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), isEmpty()
*/
	inline bool Adyacente(ed::Vertice const u, ed::Vertice const v){
		
			#ifndef NDEBUG
				assert(has(u) == true);
				assert(has(v) == true);
			#endif
			
		for(int i=0; i<getLados(); i++){
			
			if((_vectorLados[i].getVerticeA() == u) || (_vectorLados[i].getVerticeA() == v)){
				
				if(_vectorLados[i].getVerticeA() == u){
					
					if(_vectorLados[i].getVerticeB() == v){
						
						return true;
					}
				}
			else{
				if(_vectorLados[i].getVerticeB() == u){
	
					return true;
				}
					
			}
			}
		}	
		return false;
	}
	
					
/*!
	\brief	  Función que comprueba si el cursor apunta a un Vertice
	\attention  Se utiliza el modificador const
	\note 	  Funcion inline
	\return	  true si el cursor apunta a un vertice
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), isEmpty()
*/					
	inline bool hasCurrentVertice(){
	
		if(_cursorVertices>=0 and _cursorVertices < _nVertices){
		
			return true;
		}
		else{
		
			return false;
		}
	}
		

/*!
	\brief	  Función que devuelve el Vertice apuntado por el current
	\attention  Se utiliza el modificador const
	\note 	  Funcion inline
	\return	  Vertice apuntado por el current
	\pre 	  hasCurrentVertice() == true
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), isEmpty(), hasCurrentVertice()
*/					
	inline ed::Vertice CurrentVertice(){
		
			#ifndef NDEBUG
				assert(hasCurrentVertice() == true);
			#endif
	
		return _vectorVertices.at(_cursorVertices);

}			
		

/*!
	\brief	  Función que comprueba si el cursor apunta a un Lado
	\attention  Se utiliza el modificador const
	\note 	  Funcion inline
	\return	  true si el cursor apunta a un Lado
	\pre 	  Ninguna
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), isEmpty(), hasCurrentVertice()
*/					
	inline bool hasCurrentLado(){
	
		if(_cursorLados>=0 and _cursorLados < _nVertices){
		
			return true;
		}
		else{
		
			return false;
		}
	}
		

/*!
	\brief	  Función que devuelve el Lado apuntado por el cursor de lado
	\attention  Se utiliza el modificador const
	\note 	  Funcion inline
	\return	  Lado apuntado por el current
	\pre 	  hasCurrentLado() == true
	\post 	  Ninguna 
	\sa 	 	  getVertices(), getLados(), esDirigido(), isEmpty(), hasCurrentVertice(), hasCurrentLado()
*/					
	inline ed::Lado CurrentLado(){
		
			#ifndef NDEBUG
				assert(hasCurrentLado() == true);
			#endif
	
		return _vectorLados.at(_cursorLados);

	}


	/*****************************************************************/
	
	//!	 \name 	Funciones modificadores de la clase Grafo
	
/*!
	\brief 	Modificador del numero de Vertices del grafo
	\note 	Función inline
	\param    n: de tipo int que representa al numero de vertices
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	getVertices() == n
	\sa 		getVertices() , getLados(), esDirigido()
*/
	inline void setVertices(int n){
	
		_nVertices = n;
	
			#ifndef NDEBUG
				assert(getVertices() == n);
			#endif
	}


/*!
	\brief 	Modificador del numero de Lados del grafo
	\note 	Función inline
	\param    n: de tipo int que representa al numero de lados
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	getLados() == n
	\sa 		getVertices() , getLados(), esDirigido()
*/
	inline void setLados(int n){
	
		_nLados = n;
	
			#ifndef NDEBUG
				assert(getLados() == n);
			#endif
	}


/*!
	\brief 	Modificador del atributo dirigido de tipo bool
	\note 	Función inline
	\param    cadena: de tipo bool
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	esDirigido == cadena
	\sa 		getVertices() , getLados(), esDirigido()
*/
	inline void setDirigido(bool cadena){
	
		_dirigido = cadena;
		
			#ifndef NDEBUG
				assert(esDirigido() == cadena);
			#endif
	}
	

/*!
	\brief 	Modificador de atributo matriz
	\note 	Función inline
	\param    matriz: de tipo std::vector < std::vector<double> >
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	Ninguna
	\sa 		getVertices() , setVectorVertices(), setVectorLados()
*/
	inline void setMatriz(std::vector < std::vector<double> > matriz){
		_matriz = matriz;
		
	}


/*!
	\brief 	Modificador de atributo vectorVertices
	\note 	Función inline
	\param    vector: de tipo std::vector<Vertice>
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	Ninguna
	\sa 		getVertices() , setVectorLados()
*/
	inline void setVectorVertices(std::vector<Vertice> vector){
	
		
			_vectorVertices=vector;
		
	}


/*!
	\brief 	Modificador de atributo vectorlados 
	\note 	Función inline
	\param    vector: de tipo std::vector<Lado>
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	Ninguna
	\sa 		getVertices() , setVectorVertices()
*/
	inline void setVectorLados(std::vector<Lado> vector){
	
		for(int unsigned i=0; i<vector.size(); i++){
		
			_vectorLados.push_back(vector[i]);
		}
	}


/*!
	\brief 	Función que modifica un dato de la matriz
	\note 	Función inline
	\param    i: de tipo int corresponde a la fila
	\param 	j: de tipo int corresponde a la columna
	\param 	dato: de tipo double corresponde a la distancia euclidea entre los vertices
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	Ninguna
	\sa 		getVertices() , setVectorLados(), setVectorVertices(), setPadre()
*/
	inline void setDatoMatriz(int i, int j, double dato){
	
		_matriz[i][j] = dato;
	}


/*!
	\brief 	Función que modifica el atributo padre de tipo vector con otro vector recibido como parametro
	\note 	Función inline
	\param    padre: de tipo vector de int
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	Ninguna
	\sa 		getVertices() , setVectorLados(), setVectorVertices(), setDatoMatriz()
*/
	inline void setPadre(std::vector <int> padre){
	
		_padre = padre;
	}



/*!
	\brief 	Función que añade un nuevo Vertice al vector de Vertices de la clase grafo
	\note 	Función inline
	\param    vertice: de tipo Vertice, nuevo vertice a añadir en el grafo
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	hasCurrentVertice() == true and CurrentVertice().getVertice() == vertice
	\sa 		getVertices() , setVectorLados(), setVectorVertices(), setDatoMatriz()
*/
inline void addVertice(ed::Vertice const &vertice){
	
	_vectorVertices.push_back(vertice);
	
	//Modificamos el numero de Vertices
	setVertices(getVertices()+1);
	
}


/*!
	\brief 	Función que añade un nuevo Lado al vector de Lados de la clase grafo
	\note 	Función inline
	\param    u: de tipo Vertice
	\param	v: de tipo Vertice
	\return 	Nada, es de tipo void
	\pre 	Ninguna
	\post	Ninguna
	\sa 		getVertices() , setVectorLados(), setVectorVertices(), setDatoMatriz()
*/
inline void addLado(ed::Vertice const &u, ed::Vertice const &v){
	
	ed::Lado aux;
	aux.setVerticeA(u);
	aux.setVerticeB(v);
	
	//Calculamos la distancia euclidea entre los lados
	aux.setDistancia(distanciaEuclidea(u,v));
	
	//Insertamos lado en el vector de lados
	_vectorLados.push_back(aux);
	
	//Modificamos el numero de Lados
	setLados(getLados()+1);
}


/*! 
	\brief     Función que calcula la distancia euclidea entre dos vertices
	\attention Se utiliza el modificador const
	\note      Función inline
	\param     u: de tipo Vertice pasado como referencia const
	\param 	 v: de tipo Vertice pasado como referencia const
	\pre       Ninguna
	\post      valor devuelto = raizcuadrada ((x2-x1)^2 + (y2-y1)^2) 
	\sa        getnVertices(), getnLados()
*/
	float distanciaEuclidea(Vertice const & u, Vertice const & v);


/*! 
	\brief     Función que rellena la matriz de adyacencias 
	\note      Función inline
	\pre       Ninguna
	\post      Ninguna
	\sa        mostrarMatrizAdyacencia(), rellenarVectorLados(), mostrarVectorLados()
*/
	void rellenaMatriz();


/*! 
	\brief     Función que muestra por pantalla la matriz de adyacencias
	\attention Se utiliza el modificador const
	\note      Función inline
	\pre       Ninguna
	\post      Ninguna
	\sa        rellenaMatriz(), rellenarVectorLados(), mostrarVectorLados()
*/
	void mostrarMatrizAdyacencia() const;

	
/*! 
	\brief     Función que rellena el vector de lados mediante la matriz de adyacencia
	\note      Función inline
	\pre       Ninguna
	\post      Ninguna
	\sa        rellenaMatriz(), rellenarVectorLados(), mostrarVectorLados()
*/
	void rellenarVectorLados();
	

/*! 
	\brief     Función que muestra por pantalla el vector de lados
	\attention Se utiliza el modificador const
	\note      Función inline
	\pre       Ninguna
	\post      Ninguna
	\sa        rellenaMatriz(), rellenarVectorLados(), mostrarVectorLados(), ordenaVectorLados()
*/
	void mostrarVectorLados() const;
	

/*! 
	\brief     Función que ordena el Vector de lados utilizando la distancia, de menor a mayor
	\attention Se utiliza el modificador const
	\note      Función inline
	\pre       Ninguna
	\post      Ninguna
	\sa        rellenaMatriz(), rellenarVectorLados(), mostrarVectorLados(), ordenaVectorLados()
*/
	void ordenarVectorLados();
		

/*! 
	\brief     Función que imprime el vector vertices sin la etiqueta
	\attention Se utiliza el modificador const
	\note      Función inline
	\pre       Ninguna
	\post      Ninguna
	\sa        rellenaMatriz(), rellenarVectorLados(), mostrarVectorLados(), ordenaVectorLados()
*/	
	inline void print()const{
		
		int i;
		
		for(i=0; i<_nVertices; i++){
			
			_vectorVertices[i].getPunto().escribirPunto2D();
		}
	} 


/*! 
	\brief     Función que recorre todo el vector de Vertices para asignarle una etiqueta con su posicion en el vector [i]
	\attention Se utiliza el modificador const
	\note      Función inline
	\pre       Ninguna
	\post      Ninguna
	\sa        rellenaMatriz(), rellenarVectorLados(), mostrarVectorLados(), ordenaVectorLados()
*/	
	inline void indice(){
		for(int i=0; i<getVertices(); i++){
			_vectorVertices[i].setEtiqueta(i);
		}
	}
	
	
/*! 
	\brief     Operador de asignación: operador que "copia" un Lado en otro Lado
	\attention Se sobrecarga el operador de asignación "="
	\note      Función inline
	\warning   Se requiere que las funciones de acceso get tengan el modificar const
	\param     objeto de la clase Lado pasado como referencia constante
	\pre       El objeto es distinto del objeto actual
	\post      getDistancia() == objeto.getDistancia() and getVerticeA() == objeto.getVerticeA() and getVerticeB() == objeto.getVerticeB()
	\sa        setDistancia(), getVerticeA(), getVerticeB(), getDistancia()
*/
	inline Grafo & operator=(Grafo const & objeto){
		
		// Se comprueba que no sean el mismo objeto
		if (this != &objeto) 
		{
			this->setVectorVertices(objeto.getVectorVertices());
			this->setVectorLados(objeto.getVectorLados());
			this->setMatriz(objeto.getMatriz());
			this->setVertices(_vectorVertices.size());
			this->setLados(_vectorLados.size());
			this->setDirigido(objeto.esDirigido());
			

			#ifndef NDEBUG
	  		//Se comprueba la postcondición
				//assert(this->getVertices() == objeto.getVertices());
				//assert(this->getLados() == objeto.getLados());
				//assert(this->esDirigido() == objeto.esDirigido());
			#endif //NDEBUG
		}

		return *this;
	}
	

/*! 
	\brief     Función que imprime por pantalla tanto el vector de Vertices como la Matriz y el vector de Lados
	\note      Función inline
	\warning   Se requiere que las funciones de acceso get tengan el modificar const
	\pre       Ninguna
	\post      Ninguna
	\sa        setDistancia(), getVerticeA(), getVerticeB(), getDistancia()
*/	
	void mostrarGrafo()const ;


/*! 
	\brief     Función que rellena el vector de padres que utizamos para evitar ciclos en Kruskal
	\note      Función inline
	\pre       Ninguna
	\post      Ninguna
	\sa        setDistancia(), getVerticeA(), getVerticeB(), getDistancia()
*/	
	inline void rellenaPadre(){
		
		_padre.clear();
		
		for(int i=0; i<getVertices(); i++){
			_padre.push_back(i);
		}
	}
	

/*! 
	\brief     Función que comprueba si dos Vertices forman un ciclo
	\note      Función inline
	\warning   Se requiere que las funciones de acceso get tengan el modificar const
	\pre       isEmpty() == false
	\post      Ninguna
	\sa        setDistancia(), getVerticeA(), getVerticeB(), getDistancia()
*/
	inline bool componenteConexa(int origen, int destino){
		
			#ifndef NDEBUG
				assert(isEmpty() == false);
			#endif
			
		if((Buscar(origen)) == (Buscar(destino))){
			return true;
		}
		return false;
	}


/*! 
	\brief     Función que devuelve el padre de un Vertice
	\note      Función inline
	\warning   Se requiere que las funciones de acceso get tengan el modificar const
	\return	 int que indica el padre 
	\pre       Ninguna
	\post      Ninguna
	\sa        setDistancia(), getVerticeA(), getVerticeB(), getDistancia()
*/	
	inline int Buscar(int x){
		
		if( x == _padre[x]){
			return x;
		}
		else return Buscar(_padre[x]);
	}
	
	
/*! 
	\brief     Función que une dos vertices en el vector padre
	\note      Función inline
	\warning   Se requiere que las funciones de acceso get tengan el modificar const
	\pre       Ninguna
	\post      Ninguna
	\sa        setDistancia(), getVerticeA(), getVerticeB(), getDistancia()
*/	
	inline void Union(int origen, int destino){
		
		int raizOrigen = Buscar(origen);
		int raizDestino= Buscar(destino);
		
		_padre[raizOrigen] = raizDestino;
	}


/*! 
	\brief     Función que comprueba si un vertice esta en el vector de Vertices
	\note      Función inline
	\attention Se utiliza el modificador const
	\param 	 vertice de tipo Vertice, vertice a buscar en el vector
	\return 	 true en caso de encontrarlo, false en otro caso
	\pre       isEmpty() == false
	\post      Ninguna
	\sa        setDistancia(), getVerticeA(), getVerticeB(), getDistancia()
*/
	inline bool has(ed::Vertice const &vertice){
		
			#ifndef NDEBUG
				assert(isEmpty()==false);
			#endif
		
		for(int i=0; i<getVertices(); i++){
			
			if(_vectorVertices[i] == vertice){
				return true;
			}
		}
		return false;
	}


/*! 
	\brief     Función que vacia todo los vectores y y atributos a 0 del grafo
	\note      Función inline
	\pre       Ninguna
	\post      Ninguna
	\sa        setDistancia(), getVerticeA(), getVerticeB(), getDistancia()
*/	
	inline void removeAll(){
		
		_vectorVertices.clear();
		_vectorLados.clear();
		_padre.clear();
		_cursorVertices=0;					
     	_cursorLados=0;							
     	_nLados=0;	
     	_dirigido=false;					
     	_memoria=0;
     	
     		for(int i=0; i<_nVertices; i++){
     			_matriz[i].clear();
     		}
     	_matriz.clear();
     	_nVertices=0;
    }
					
	
}; // Fin de la definición de la clase Punto2D


}  // \brief Fin de namespace ed.

//  _PUNTO2DI_HPP_
#endif
