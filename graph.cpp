#include "graph.h"
#include <vector>
#include <iostream>
#include <stdexcept>


Graph:: Graph()
    {
    size = 0;
    matrix.resize(size);
    }

Graph:: Graph(size_t start_size)
    {
    size = start_size;
    matrix.resize(size);
    for (size_t i = 0; i < size; i++)
        {
        matrix[i].resize(size);
        }
    }

Graph:: Graph(Graph* graph_adress)
    {
    size = graph_adress->size;
    matrix.resize(size);
    for(size_t i = 0; i < size; i++)
        {
        matrix[i].resize(size);
        for(size_t j = 0; j < size; j++)
            {
            matrix[i][j] = graph_adress->matrix[i][j];
            }
        }
    }

Graph:: ~Graph()
    {
    for (size_t i; i < size; i++)
        {
        matrix[i].clear();
        }
    matrix.clear();
    }

int Graph:: check_node_exist(int node_number)
    {
    if (node_number > size-1)
        {
        throw std::runtime_error("Number of node[" + std::to_string(node_number) + "] bigger than matrix size[" + std::to_string(size) + "]!");
        return 0;
        }
    else 
        {
        return 1;
        }

    }

void Graph:: add_node(std::vector<int> new_node)
    {
    size++;
    matrix.resize(size);
    for (int i = 0; i < size; i++)
        {
        matrix[i].resize(size);
        matrix[i][size-1] = new_node[i];
        matrix[size-1][i] = new_node[i];
        }
    }

void Graph:: fill_matrix()
    {
    int smallest = 0;
    int biggest = 2;
    for (int i = 0; i < size; i++)
        {
        for (int j = 0; j < size; j++)
            {
            matrix[i][j] = smallest + rand() % (biggest - smallest);
            }
        }
    }

void Graph:: print_matrix()
    {
    std:: cout << "Matrix size: "<< matrix.size() << std:: endl;
    std:: cout<< std::endl;
    for (size_t i = 0; i < size; i++)
        {
        for (size_t j = 0; j < size; j++)
            {
            std:: cout << matrix[i][j];
            }
        std::cout<< std::endl;
        }
    }

void Graph:: print_ways(std::vector<std::vector<int>> ways)
    {
    for (size_t i = 0; i < ways.size(); i++)
        {
        for(size_t j = 0; j < ways[i].size(); j++)
            {
            if (j != ways[i].size()-1)
                {
                std::cout << ways[i][j] << " -> ";
                }
            else
                {
                std::cout << ways[i][j] << std::endl;
                }
            }
        }
    }

void Graph:: print_simple_connects()
    {
    for (int start_point = 0; start_point < size; start_point++)
        {
        for (int finish_point = 0; finish_point < size; finish_point++)
            {
            Graph copy_graph = new Graph(this);
            std::vector<int> way;
            std::vector<std::vector<int>>ways;
            copy_graph.find_simple_connects(start_point,finish_point,way,ways);
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "All ways from " << start_point << " to " << finish_point << " : " << std::endl;
            std::cout << std::endl;
            print_ways(ways);

            }
        }
    }


void Graph:: delete_loop(int start_point)
    {
    for (int finish_point = 0; finish_point < size; finish_point++)
        {
        if ( (matrix[finish_point][start_point] != 0) && ( (check_way_exist(start_point,finish_point)) ) )
            {
            matrix[finish_point][start_point] = 0;
            }
        }
    }

int Graph:: check_way_exist(int start_point,int finish_point) 
    {
    Graph copy_to_find = new Graph(this);
    std::vector<int> way_out_one;
    std::vector<std::vector<int>> ways_out;

    for (int i = 0; i < copy_to_find.size; i++)
        {
        for(int j = 0; j < copy_to_find.size; j++)
            {
            if (copy_to_find.matrix[i][j] != 0 )
                {
                way_out_one.push_back(j);
                }
            }
        ways_out.push_back(way_out_one);
        way_out_one.clear();
        }

    while (ways_out[start_point].size() > 0)
        {
        if (ways_out[start_point][0] == finish_point)
            {
            return 1;
            }
        else if (ways_out[start_point][0] == start_point)
            {
            ways_out[start_point].erase(ways_out[start_point].begin());
            }
        else 
            {
            while(ways_out[ways_out[start_point][0]].size() > 0)
                {
                ways_out[start_point].push_back(ways_out[ways_out[start_point][0]][0]);
                ways_out[ways_out[start_point][0]].erase(ways_out[ways_out[start_point][0]].begin());
                }
            ways_out[start_point].erase(ways_out[start_point].begin());
            }
        }
    return 0;
    }

void Graph:: find_simple_connects(int start_point,int finish_point,std::vector<int> &way,std::vector<std::vector<int>> &ways)
    {
    delete_loop(start_point);
    if (start_point == finish_point)
        {
        way.push_back(finish_point);
        ways.push_back(way);
        way.resize(way.size()-1);
        return;
        }
    else
        {
        if (check_way_exist(start_point,finish_point))
            {
            for (int i = 0; i < size; i++)
                {
                if ((matrix[start_point][i] != 0) && ( (check_way_exist(i,finish_point)) || (i == finish_point)))
                    {
                    way.push_back(start_point);
                    Graph copy = new Graph(this);
                    copy.find_simple_connects(i,finish_point,way,ways);
                    way.resize(way.size()-1);
                    }
                }
            }
        }
    }

