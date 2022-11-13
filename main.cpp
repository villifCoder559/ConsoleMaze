#include "Maze.h"

int main()
{
    Maze *maze = new Maze(12); //Max 340
    // auto start = std::chrono::high_resolution_clock::now();
    maze->create_maze();
    maze->print_maze();
    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // std::cout<<"TIME_CREATION "<<duration.count()<<" microseconds"<<std::endl;
    // start = std::chrono::high_resolution_clock::now();
    maze->print_solution();
    std::cin.ignore();
    // end = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // std::cout<<"TIME_SOLUTION "<<duration.count()<< " microseconds"<<std::endl;
    delete maze;
    return 0;
}
