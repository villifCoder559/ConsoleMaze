
// Checks if _ANIMALS IF DECLARED
#ifndef _Move_
  
// Defines _ANIMALS_ if above
// conditions fails
#define _Move_

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
    Move(direction dir, int x, int y);
    ~Move();
};
#endif