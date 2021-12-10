#include "graph.h"
#include <vector>
#include <iostream>
#include <stdexcept>

int main()
    {
    Graph A(4);
    A.fill_matrix();
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    //A.print_simple_connects();
    std::cout<< A.check_way_exist(3,1) <<std::endl;
    A.print_matrix();
    }