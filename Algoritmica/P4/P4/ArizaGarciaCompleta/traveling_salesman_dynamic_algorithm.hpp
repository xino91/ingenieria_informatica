#ifndef __TRAVELING_SALESMAN_DYNAMIC_ALGORITHM_HPP__
#define __TRAVELING_SALESMAN_DYNAMIC_ALGORITHM_HPP__

#include <stack>
#include <utility>
#include <valarray>

#include "graph.hpp"
#include "graph_utils.hpp"

void todosCaminos(std::vector< std::vector <size_t> > allPaths){
	for(size_t i=0; i<allPaths.size(); i++){
		std::cout << " Path " << i << ": ";
		for(size_t j=0; j<allPaths[i].size(); j++){
			std::cout << allPaths[i][j] << ", ";
		}
		std::cout << std::endl;
	}
}

template <class T>
void traveling_salesman_dynamic(WGraph<T> & g, WGraph<T> & newGraph){

    std::vector<bool> visited(g.capacity());
    std::vector<size_t> currentPath;
    std::vector< std::vector <size_t> > allPaths;
    for(size_t i = 0; i < g.capacity(); i++) 
    	visited[i] = false; 
    	
    typename WGraph<T>::EdgeRef edge;

    g.goto_first_node();

    deep_travel(g, g.current_node()->item(), visited, currentPath, allPaths);
    //todosCaminos(allPaths);
    
    for(int i=0; i< g.size(); i++){
    		newGraph.add_node(g.node(i)->item());
    }
    
    int fila;
    float weight_aux = std::numeric_limits<float>::max();
    for(int i=0; i<allPaths.size(); i++){
    
    		float weight=0;

    		for(int j=0; j<g.capacity(); j++){

    			if(j == g.capacity()-1){ //Si es ultimo, enlaza con nodo 0
    				g.goto_edge(g.node(allPaths[i][j]), g.node(allPaths[i][0]));
    			}
    			else{
    				g.goto_edge(g.node(allPaths[i][j]), g.node(allPaths[i][j+1]));
    			}
    			edge = g.current_edge();
    			weight = weight + edge->item();
    		}
    		
    		if(weight_aux >= weight ){
    			weight_aux = weight;
    			fila= i;
    		}
    }

    for(int n=0; n<g.size(); ++n){
    		typename WGraph<T>::NodeRef u;
    		typename WGraph<T>::NodeRef v;
    		
    		if(n == g.size()-1){	//Si es ultimo, enlaza con primero
    			u = g.node(allPaths[fila][n]);
    			v = g.node(allPaths[fila][0]);
    		}
    		else{
    			 u= g.node(allPaths[fila][n]);
    			 v = g.node(allPaths[fila][n+1]);
    		}
    
    		g.goto_edge(u,v);
    		
    		edge = g.current_edge();
    		weight_aux = edge->item();
    		
    		newGraph.set_weight(newGraph.find(u->item()), newGraph.find(v->item()), weight_aux);
    }

}

template <class T>
void deep_travel(WGraph<T>  &g, const T keyNode, std::vector<bool> visited, std::vector<size_t> currentPath,  std::vector< std::vector <size_t> > &allPaths) 
{
	typename WGraph<T>::NodeRef u, v;
	typename WGraph<T>::EdgeRef e;
	
	u = g.find(keyNode); //KeyNode is searched in the graph
	visited[u->label()] = true; //The current node is marked as visited
    currentPath.push_back(u->label()); //The current node is added to current path.

    if (currentPath.size() == g.capacity()) //A new path has been found.
    	allPaths.push_back(currentPath); //The new path is saved in allPath
    	
	g.goto_first_edge();
	while (g.has_current_edge())
	{
		e = g.current_edge();
		v = e->other(u);
		if (not visited[v->label()])
		{
			//std::cout << " Llamada recursiva \n";
			deep_travel(g, v->item(), visited, currentPath, allPaths);
			g.goto_edge(u, v); //It is necessary for dont lose the current edge when all the recursive calls end.
		}
		g.goto_next_edge(); //Go te the next edge
	}
}

#endif //__TRAVELING_SALESMAN_DYNAMIC_ALGORITHM_HPP__
