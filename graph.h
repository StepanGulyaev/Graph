
#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>

class Graph
    {
    private:

        size_t size;
        std::vector<std::vector<int>> matrix;

        int flag = 0;

        int check_node_exist(int);
        void delete_loop(int);
        int check_way_exist(int,int);
        void print_ways(std::vector<std::vector<int>>);
        void find_simple_connects(int,int,std::vector<int> &way,std::vector<std::vector<int>> &ways);

    public:
        
        Graph();
        Graph(size_t);
        Graph(Graph*);

        ~Graph();

        
        void add_node(std::vector<int>);
        void fill_matrix();
        void print_matrix();
        void print_simple_connects();
    }; 


#endif 
