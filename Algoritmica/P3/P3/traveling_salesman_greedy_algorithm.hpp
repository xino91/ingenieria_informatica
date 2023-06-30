#ifndef __TRAVELING_SALESMAN_GREEDY_ALGORITHM__
#define __TRAVELING_SALESMAN_GREEDY_ALGORITHM__

#include <stack>
#include <utility>
#include <valarray>

#include "graph.hpp"
#include "graph_utils.hpp"
#include <vector>

template<class T> std::vector<size_t> adjacents(WGraph<T> newG, size_t nodo);
template<class T> void Calcular_Adyacentes(std::vector<size_t> const &adyacentes, std::vector<size_t> &AllAdyacentes);
bool comprobar_valor(std::vector<size_t> AllAdyacentes, size_t valor);

void printVector(std::vector<size_t> v){
	for(int i=0; i<v.size(); i++){
		std::cout << "Adyacentes["<<i<<"] = :" << v[i] << std::endl;
	}
}

template<class T>
std::vector<size_t> adjacents(WGraph<T> newG, size_t nodo)
   {
    	std::vector<size_t> adyacentes_return(2,std::numeric_limits<size_t>::max());
    	std::vector<size_t> adyacentes;
    	typename WGraph<T>::EdgeRef e;
    		
    	adyacentes = newG.adjacent(nodo);
    	for(size_t i=0; i<adyacentes.size(); i++){
    		if(adyacentes[i] < std::numeric_limits<size_t>::max()){
    			adyacentes_return[i] = adyacentes[i];
    		}
    	}
    	return adyacentes_return;
}

template<class T>
void Calcular_Adyacentes(WGraph<T> newG, size_t nodo, std::vector<size_t> &AllAdyacentes)
{
	std::vector<size_t> adyacentes;
	adyacentes = newG.adjacent(nodo);
	
	for(int i=0; i<adyacentes.size(); i++){
		if(comprobar_valor(AllAdyacentes, adyacentes[i]) == false){
			AllAdyacentes.push_back(adyacentes[i]);
		}
	}
}

template<class T>
bool ciclo(WGraph<T> newG, size_t u, size_t v, float weight){
	
	std::vector<size_t> adyacentes_main(2,std::numeric_limits<size_t>::max());
	std::vector<size_t> AllAdyacentes;

	newG.set_weight(newG.node(u), newG.node(v), weight);
	
	adyacentes_main = adjacents(newG, u);
		
	newG.set_weight(newG.node(u), newG.node(v), std::numeric_limits<float>::infinity()); //Borramos nodo insertado para evitar la vuelta hacia atrás
	newG.set_weight(newG.node(v), newG.node(u), std::numeric_limits<float>::infinity());
	
	if(adyacentes_main[1] < std::numeric_limits<size_t>::max()){ //Si un nodo tiene solo una lado, no abrá un ciclo
		Calcular_Adyacentes(newG, adyacentes_main[0], AllAdyacentes);
		for(int j=0; j<AllAdyacentes.size(); j++){
			Calcular_Adyacentes(newG, AllAdyacentes[j], AllAdyacentes);
		}
	}

	for(int i=0; i<AllAdyacentes.size(); i++){
		if(AllAdyacentes[i] == adyacentes_main[1]){
			return true;
		}
	}
	return false;
}

bool comprobar_valor(std::vector<size_t> AllAdyacentes, size_t valor){

	for(int i=0; i<AllAdyacentes.size(); i++){
		if(AllAdyacentes[i] == valor){
			return true;
		}
	}
	return false;
}

template <class T>
void traveling_salesman_greedy(WGraph<T> & g, WGraph<T> & newGraph){
	
	typename WGraph<T>::NodeRef u,v, u_aux, v_aux;
	typename WGraph<T>::EdgeRef edge;
	std::vector< std::vector <float> > matriz (g.size(), std::vector<float> (g.size(),0));
	std::vector<size_t> vector(2,0);
		
	
	g.goto_first_node();
	g.goto_first_edge();
	float weight, weight_aux = g.current_edge()->item();
	int lados = 0;
	std::vector<int> visited(g.size(), 0);
	int cierre, cierre2;
	int primero = 0;
	
    //All nodes are added
    for (size_t n=0;n<g.size();++n){
        newGraph.add_node(g.node(n)->item());
    }
    
     while(lados != g.size()){

	    	g.goto_first_node();
		weight = std::numeric_limits<float>::max();
		
		for(size_t n=0; n<g.size(); n++){
		
			g.goto_first_edge();
			
			u = g.current_node();
			v = g.current_edge()->second();
			
			while(g.has_current_edge()){
				edge = g.current_edge();	
				
				if(edge->item() < weight and visited[edge->first()->label()] != 2 and visited[edge->second()->label()] != 2 
					and matriz[edge->first()->label()][edge->second()->label()] == 0.0 and matriz[edge->second()->label()][edge->first()->label()] == 0.0 ){
						v_aux = edge->second();
						u_aux = edge->first();
						weight = edge->item();
				}
				g.goto_next_edge();
			}	
			g.goto_next_node();
		}
		
		matriz[u_aux->label()][v_aux->label()] = weight;
		matriz[v_aux->label()][u_aux->label()] = weight;
		
		if(lados == g.size()-1){ //ULTIMO NODO A INSERTAR
			newGraph.set_weight(newGraph.find(u_aux->item()), newGraph.find(v_aux->item()), weight);
			visited[u_aux->label()] = visited[u_aux->label()]+1;
			visited[v_aux->label()] = visited[v_aux->label()]+1;
			lados++;
		}
		if(lados >= 1 and lados < g.size()-1){
			if(ciclo(newGraph,u_aux->label(), v_aux->label(), weight)==false){
				newGraph.set_weight(newGraph.find(u_aux->item()), newGraph.find(v_aux->item()), weight);
				visited[u_aux->label()] = visited[u_aux->label()]+1;
				visited[v_aux->label()] = visited[v_aux->label()]+1;
				lados++;
			}
		}
		if(lados == 0){ //PRIMERO A INSERTAR
			cierre = u_aux->label();
			cierre2 = v_aux->label();
			newGraph.set_weight(newGraph.find(u_aux->item()), newGraph.find(v_aux->item()), weight);
			visited[u_aux->label()] = visited[u_aux->label()]+1;
			visited[v_aux->label()] = visited[v_aux->label()]+1;
			lados++;
		}
	}
}


#endif //__TRAVELING_SALESMAN_GREEDY_ALGORITHM__
