#ifndef __RANDON_GRAPH_ALGORITHM_HPP__
#define __RANDON_GRAPH_ALGORITHM_HPP__

#include <stack>
#include <utility>
#include <valarray>

#include "graph.hpp"
#include "graph_utils.hpp"




/**
 * @brief Create a new graph from the old graph by selecting the edges whose weight is greter than 200.
 * @arg[in] g is a weighted graph.
 * @arg[out] newGraph is the new graph.
 * @pre the weigths meet the triangular inequality: d(u,v) <= d(u,k) + d(k,v) for all u!=v!=k.
 */
template <class T>
bool
deep_travel_wgraph(WGraph<T> & g)
{
    //This algorithm travel the graph from the first node
    //std::vector< typename WGraph<T>::EdgeRef > edges;
    std::vector<bool> visited(g.capacity()); //This vector is used to check if the node has been visited.
    std::vector<size_t> currentPath;
    std::vector< std::vector <size_t> > allPaths;
    for(size_t i = 0; i < g.capacity(); i++) //All the nodes are marked as not visited
    	visited[i] = false; 


    g.goto_first_node();

    deep_travel(g, g.current_node()->item(), visited, currentPath, allPaths);
    for(unsigned int i = 0; i < allPaths.size(); i++)
    {
    	std::cout << " Path " << i << ": ";
    	for(unsigned int j = 0; j < g.capacity(); j++)
    		std::cout << allPaths[i][j] << ", ";
    	std::cout << std::endl;
    }

    return true;
}

template <class T>
void
deep_travel(WGraph<T>  &g, const T keyNode, std::vector<bool> visited, std::vector<size_t> currentPath,  std::vector< std::vector <size_t> > &allPaths) 
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



#endif //__RANDON_GRAPH_ALGORITHM_HPP__
