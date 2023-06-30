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
create_random_wgraph_from_wgraph(WGraph<T> & g, WGraph<T> & newGraph)
{
    
    //All nodes are added
    for (size_t n=0;n<g.size();++n)
    {
        newGraph.add_node(g.node(n)->item());
    }


    //std::vector< typename WGraph<T>::EdgeRef > edges;
    g.goto_first_node();
    while(g.has_current_node())
    {
        g.goto_first_edge();
        while(g.has_current_edge())
        {
            size_t u, v;
            if (g.current_edge()->item() > 200) //Only pairs
            {
                u = g.current_edge()->first()->label();
                v = g.current_edge()->second()->label();
                newGraph.set_weight(newGraph.node(u), newGraph.node(v), g.current_edge()->item()); //Add new edge
            }
            g.goto_next_edge();
        }
        g.goto_next_node();
    }  
    return true;
}


#endif //__RANDON_GRAPH_ALGORITHM_HPP__
