#ifndef _Node_
#define _Node_
#include <iostream>
#include "Move.h"

enum component
{
    wall = 0,
    street = 1,
    init = 2,
    end = 3
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

    Node(direction dir, int x, int y, component comp, Node *predecessor);
    void print();
    Node();
    ~Node();
};
#endif