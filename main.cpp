#include <iostream>
#include <vector>
#include <omp.h>
#include <list>
#include <random>
#include <iostream>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
// Invert Start and End
enum component
{
    wall = 0,
    street = 1,
    init = 2,
    end = 3
};
enum direction
{
    first = -1,
    down = 0,
    left = 1,
    right = 2,
    up = 3,
};
class Move
{
public:
    direction dir;
    int x;
    int y;
    Move(direction dir, int x, int y)
    {
        this->dir = dir;
        this->x = x;
        this->y = y;
    }
    ~Move() {}
};
class Node
{
public:
    component comp;
    Move *move;
    Node *up = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *down = nullptr;
    Node *predecessor = nullptr;

public:
    Node(direction dir, int x, int y, component comp, Node *predecessor)
    {
        this->comp = comp;
        this->move = new Move(dir, x, y);
        this->predecessor = predecessor;
    }
    void print()
    {
        std::cout << "POS: " << move->x << ";" << move->y;
        if (left != nullptr)
            std::cout << " LEFT " << left->move->x << ";" << left->move->y;
        if (right != nullptr)
            std::cout << " RIGHT " << right->move->x << ";" << right->move->y;
        if (up != nullptr)
            std::cout << " UP " << up->move->x << ";" << up->move->y;
        if (down != nullptr)
            std::cout << " DOWN " << down->move->x << ";" << down->move->y;
        if (predecessor != nullptr)
            std::cout << " PARENT " << predecessor->move->x << ";" << predecessor->move->y;
        std::cout << std::endl;
    }
    Node() {}
    ~Node()
    {
        if (move)
            delete move;
        if (up)
            delete up;
        if (left)
            delete left;
        if (right)
            delete right;
        if (down)
            delete down;
        if (predecessor)
            delete predecessor;
    }
};
class Maze
{
private:
    unsigned short int DIM;
    Node *start;
    Node ***node_matrix;
    std::vector<Node *> *get_solution_path()
    {
        bool *found = new bool;
        std::vector<Node *> *path = new std::vector<Node *>();
        path->push_back(start);
        *found = false;
        DFS(start, path, found);
        delete found;
        return path;
    }
    void DFS(Node *root, std::vector<Node *> *path, bool *found)
    {
        if (root->comp == end)
        {
            (*found) = true;
        }
        else
        {
            if (root->up != nullptr && root->up != root->predecessor)
            {
                if (!(*found))
                {
                    path->push_back(root->up);
                    DFS(root->up, path, found);
                    if (!(*found))
                        path->pop_back();
                }
            }
            if (root->right != nullptr && root->right != root->predecessor)
            {
                if (!(*found))
                {
                    path->push_back(root->right);
                    DFS(root->right, path, found);
                    if (!(*found))
                        path->pop_back();
                }
            }
            if (root->down != nullptr && root->down != root->predecessor)
            {
                if (!(*found))
                {
                    path->push_back(root->down);
                    DFS(root->down, path, found);
                    if (!(*found))
                        path->pop_back();
                }
            }
            if (root->left != nullptr && root->left != root->predecessor)
            {
                if (!(*found))
                {
                    path->push_back(root->left);
                    DFS(root->left, path, found);
                    if (!(*found))
                        path->pop_back();
                }
            }
        }
    }
    void print_recursive_graph(Node *node)
    {
        std::cout << node->move->x << ";" << node->move->y << " ";
        if (node->predecessor == nullptr)
            std::cout << " P: START    ";
        else
            std::cout << " P:" << node->predecessor->move->x << ";" << node->predecessor->move->y << "    ";
        if (node->up != nullptr && node->up != node->predecessor)
            print_recursive_graph(node->up);
        if (node->right != nullptr && node->right != node->predecessor)
            print_recursive_graph(node->right);
        if (node->down != nullptr && node->down != node->predecessor)
            print_recursive_graph(node->down);
        if (node->left != nullptr && node->left != node->predecessor)
            print_recursive_graph(node->left);
    }
    bool add_node(Node *source, Node *new_node, direction d)
    {
        bool ok = true;
        switch (d)
        {
        case up:
            if (source->up != nullptr)
                ok = false;
            else
            {
                source->up = new_node;
                new_node->down = source;
            }
            break;
        case down:
            if (source->down != nullptr)
                ok = false;
            else
            {
                source->down = new_node;
                new_node->up = source;
            }
            break;
        case left:
            if (source->left != nullptr)
                ok = false;
            else
            {
                source->left = new_node;
                new_node->right = source;
            }
            break;
        case right:
            if (source->right != nullptr)
                ok = false;
            else
            {
                source->right = new_node;
                new_node->left = source;
            }
            break;
        }
        if (ok)
            node_matrix[new_node->move->x][new_node->move->y] = new_node;
        return ok;
    }
    std::vector<Move *> get_free_positions(Node *node)
    {
        std::vector<Move *> elements;
        int x = node->move->x;
        int y = node->move->y;
        if (x > 0 && !node_matrix[x - 1][y])
            elements.push_back(new Move(up, node->move->x - 1, node->move->y));
        if (x < DIM - 1 && !node_matrix[x + 1][y])
            elements.push_back(new Move(down, node->move->x + 1, node->move->y));
        if (y > 0 && !node_matrix[x][y - 1])
            elements.push_back(new Move(left, node->move->x, node->move->y - 1));
        if (y < DIM - 1 && !node_matrix[x][y + 1])
            elements.push_back(new Move(right, node->move->x, node->move->y + 1));
        return elements;
    }
    std::string **get_matrix_to_print()
    {
        int dim_maze = DIM * 2 + 1;
        std::string **matrix_to_print = new std::string *[dim_maze];
        for (int i = 0; i < dim_maze; i++)
        {
            matrix_to_print[i] = new std::string[dim_maze];
            for (int j = 0; j < dim_maze; j++)
                matrix_to_print[i][j] = "#";
        }
        matrix_to_print[1][0] = "E";
        matrix_to_print[DIM * 2 - 1][DIM * 2] = "S";
        for (int i = 0; i < DIM; i++)
        {
            for (int j = 0; j < DIM; j++)
            {
                Node *target = node_matrix[i][j];
                int row = 2 * i + 1;
                int col = 2 * j + 1;
                matrix_to_print[row][col] = ".";
                if (target->up != nullptr)
                    matrix_to_print[row - 1][col] = ".";
                if (target->down != nullptr)
                    matrix_to_print[row + 1][col] = ".";
                if (target->right != nullptr)
                    matrix_to_print[row][col + 1] = ".";
                if (target->left != nullptr)
                    matrix_to_print[row][col - 1] = ".";
            }
        }
        return matrix_to_print;
    }
    void print_maze_solution(bool **solution_matrix)
    {
        std::string **matrix = get_matrix_to_print();
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        std::cout << "SOLUTION" << std::endl;
        for (int i = 0; i < DIM * 2 + 1; i++)
        {
            for (int j = 0; j < DIM * 2 + 1; j++)
            {
                if (solution_matrix)
                {
                    if (solution_matrix[i][j])
                        SetConsoleTextAttribute(h, 17);
                    std::cout << matrix[i][j] << " ";
                    SetConsoleTextAttribute(h, 7);
                }
                else
                    std::cout << matrix[i][j] << " ";
            }
            std::cout << "" << std::endl;
        }
    }

public:

    void create_maze()
    {
        // int seed=time(0);
        srand(time(0));
        // std::cout << "SEED: " << 1500 << std::endl;
        int tot_nodes = DIM * DIM;
        start = new Node(first, 0, 0, init, nullptr);
        node_matrix[0][0] = start;
        int count_elements = 1;
        Node *last = start;
        while (count_elements < tot_nodes)
        {
            std::vector<Move *> bucket = get_free_positions(last);
            if (bucket.size() != 0)
            {
                int rnd_pos = rand() % bucket.size();
                Node *new_node = new Node(bucket[rnd_pos]->dir, bucket[rnd_pos]->x, bucket[rnd_pos]->y, street, last);
                add_node(last, new_node, new_node->move->dir);
                count_elements++;
                last = new_node;
            }
            else
                last = last->predecessor;
        }
        node_matrix[DIM - 1][DIM - 1]->comp = end;
        last = nullptr;
        delete last;
    }
    void print_graph()
    {
        print_recursive_graph(start);
    }
    /*
    Print a maze where:
        _ S is "Start Maze"
        _ E is for "End Maze"
        _ # indicates the wall
        _ . indicates the path
    */
    void print_maze()
    {
        std::string **matrix = get_matrix_to_print();
        for (int i = 0; i < DIM * 2 + 1; i++)
        {
            for (int j = 0; j < DIM * 2 + 1; j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    void print_solution()
    {
        std::vector<Node *> *path = get_solution_path();
        bool **solution_matrix = new bool *[DIM * 2 + 1];
        for (int i = 0; i < DIM * 2 + 1; i++)
        {
            solution_matrix[i] = new bool[DIM * 2 + 1];
            for (int j = 0; j < DIM * 2 + 1; j++)
                solution_matrix[i][j] = false;
        }
        for (int i = 0; i < path->size(); i++)
        {
            int row = 2 * (*path)[i]->move->x + 1;
            int col = 2 * (*path)[i]->move->y + 1;
            solution_matrix[row][col] = true;
            if (i < path->size() - 1)
            {
                Node *next = (*path)[i + 1];
                int step_x = (*path)[i]->move->x - next->move->x;
                int step_y = (*path)[i]->move->y - next->move->y;
                if (step_x == 0)
                    solution_matrix[row][col - step_y] = true;
                else
                    solution_matrix[row - step_x][col] = true;
            }
        }
        print_maze_solution(solution_matrix);
        for (int i = 0; i < DIM * 2 + 1; i++)
            delete[] solution_matrix[i];
        delete[] solution_matrix;
        delete path;
    }
    Maze(int DIM)
    {
        this->DIM = DIM;
        this->node_matrix = new Node **[DIM];
        for (int i = 0; i < DIM; i++)
        {
            this->node_matrix[i] = new Node *[DIM];
            for (int j = 0; j < DIM; j++)
                node_matrix[i][j] = nullptr;
        }
    }
    ~Maze()
    {
        if (node_matrix)
            for (int i = 0; i < DIM; i++)
            {
                for (int j = 0; j < DIM; j++)
                {
                    delete node_matrix[i][j];
                }
                delete node_matrix[i];
            }
        if (start)
            delete start;
    }
};

int main()
{
    Maze *maze = new Maze(15); //Max 340
    // auto start = std::chrono::high_resolution_clock::now();
    maze->create_maze();
    maze->print_maze();
    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // std::cout<<"TIME_CREATION "<<duration.count()<<" microseconds"<<std::endl;
    // start = std::chrono::high_resolution_clock::now();
    maze->print_solution();
    // end = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // std::cout<<"TIME_SOLUTION "<<duration.count()<< " microseconds"<<std::endl;
    delete maze;
    return 0;
}