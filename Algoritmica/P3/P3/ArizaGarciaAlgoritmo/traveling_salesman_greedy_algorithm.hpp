#ifndef __TRAVELING_SALESMAN_GREEDY_ALGORITHM__
#define __TRAVELING_SALESMAN_GREEDY_ALGORITHM__

#include <stack>
#include <utility>
#include <valarray>

#include "graph.hpp"
#include "graph_utils.hpp"
#include <vector>
template <class T>
bool nodovacio(WGraph<T> newGraph){
	int contador = 0;
	fold_wgraph(std::cout, newGraph);
	newGraph.goto_first_node();
	
	for(size_t n=0; n<newGraph.size(); n++){
		newGraph.goto_first_edge();
		contador = 0;
		while(newGraph.has_current_edge()){
			contador += 1;
			newGraph.goto_next_edge();
		}
		if(contador == 0){
				return true;
			}
		newGraph.goto_next_node();
	}
	return false;
}


template <class T>
void traveling_salesman_greedy(WGraph<T> & g, WGraph<T> & newGraph){
	
	typename WGraph<T>::NodeRef u,v, u_aux, v_aux;
	typename WGraph<T>::EdgeRef edge;
	std::vector< std::vector <float> > matriz (g.size(), std::vector<float> (g.size(),0));

	g.goto_first_node();
	g.goto_first_edge();
	float weight = g.current_edge()->item();
	int lados = 0;
	std::vector<int> visited(g.size(), 0);
	int cierre, cierre2;
	
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
		
		matriz[u_aux->label()][v_aux->label()] = weight; //Guardamos los valores para no volver a seleccionarlos
		matriz[v_aux->label()][u_aux->label()] = weight;
		
		if(lados == g.size()-1){
			newGraph.set_weight(newGraph.find(u_aux->item()), newGraph.find(v_aux->item()), weight);
			lados++;
		}
		if(lados >= 1 and lados < g.size()-1){
			if(nodovacio(newGraph)==true and ((u_aux->label() == cierre and v_aux->label() != cierre2) or (v_aux->label() == cierre and u_aux->label() != cierre2)
								    and (u_aux->label() == cierre2 and v_aux->label() != cierre) or (v_aux->label() == cierre2 and u_aux->label() != cierre)) ){
			}
			else{
				newGraph.set_weight(newGraph.find(u_aux->item()), newGraph.find(v_aux->item()), weight);
				visited[u_aux->label()] = visited[u_aux->label()]+1;
				visited[v_aux->label()] = visited[v_aux->label()]+1;
				lados++;
			}
		}
		if(lados == 0){
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
