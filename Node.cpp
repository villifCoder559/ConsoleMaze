#include "Node.h"
Node::Node(direction dir, int x, int y, component comp, Node *predecessor)
{
    this->comp = comp;
    this->move = new Move(dir, x, y);
    this->predecessor = predecessor;
}
void Node::print()
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
Node::Node() {}
Node::~Node()
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