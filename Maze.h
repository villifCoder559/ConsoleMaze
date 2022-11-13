#ifndef _Maze_
#define _Maze_

#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <iostream>
#include "Node.h"
#include "Move.h"

class Maze{
private: 
    unsigned short int DIM;
    Node *start;
    Node ***node_matrix;
    void DFS(Node *root, std::vector<Node *> *path, bool *found);
    std::vector<Node *> *get_solution_path();
    void print_recursive_graph(Node *node);
    bool add_node(Node *source, Node *new_node, direction d);
    std::vector<Move *> get_free_positions(Node *node);
    std::string **get_matrix_to_print();
    void print_maze_solution(bool **solution_matrix);
public:
    void create_maze();
    void print_graph();
    /*
    Print a maze where:
        _ S is "Start Maze"
        _ E is for "End Maze"
        _ # indicates the wall
        _ . indicates the path
    */
    void print_maze();
    void print_solution();
    Maze(int DIM);
    ~Maze();
};
#endif