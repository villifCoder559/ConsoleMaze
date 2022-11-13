#include "Move.h"

Move::Move(direction dir, int x, int y)
{
    this->dir = dir;
    this->x = x;
    this->y = y;
}
Move::~Move() {}