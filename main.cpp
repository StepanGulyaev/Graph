#include "graph.h"
#include <vector>
#include <iostream>
#include <stdexcept>

int main()
    {
    size_t size;
    std:: cout << "Enter size of graph: ";
    std:: cin >> size;

    Graph A(size);
    A.fill_matrix();
    A.print_matrix();
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    A.print_simple_connects();
    }
