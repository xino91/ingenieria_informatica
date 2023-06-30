#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>
#include <valarray>

#include "city.hpp"
#include "graph.hpp"
#include "graph_utils.hpp"
#include "random_graph_algorithm.hpp"

int 
random_graph_algorithm();

int
main()
{
    int opt;

    do
    {
    	std::cout << " 1. Random graph algorithm." << std::endl;
    	std::cout << " 0. Exit." << std::endl;
    	std::cout << "Select an option: ";
    	std::cin >> opt;

    	switch (opt)
    	{
    		case 1:
    			random_graph_algorithm();
    			break;
    		case 0:
    			break;
    		default:
    			std::cout << "Incorrect option" << std::endl;
    	}

    }while (opt != 0);
}

int random_graph_algorithm()
{
	int exit_code = EXIT_SUCCESS;
    try
    {
        char file_name_graph[100];

        std::cout << "File of the graph: ";
        std::cin >> file_name_graph;

        std::ifstream input_file (file_name_graph);
        if (!input_file)
        {
            std::cerr << "Error: could not open input filename '" << file_name_graph << "'." << std::endl;
            return EXIT_FAILURE;
        }
        std::string type;
        input_file >> type;
        input_file.ignore();
        
        if(type == "CITY")
        {
            auto g = create_wgraph<City>(input_file);
            if (!g)
            {
                std::cerr << "Error: could not load a valid wgraph for cities." << std::endl;
                return EXIT_FAILURE;
            }
            WGraph<City> newGraph(g->capacity());
            create_random_wgraph_from_wgraph(*g, newGraph); //Creates a new random graph from the old graph
            fold_wgraph(std::cout, newGraph); //Shows the graph
        }
        else
        {
            std::cerr << "Error: unknown graph type." << std::endl;
            return EXIT_FAILURE;
        }
    }
    catch(std::runtime_error &e)
    {
        std::cerr << "Run time exception: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "Catched unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}

