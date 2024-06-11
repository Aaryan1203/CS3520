#include <vector>
#include "include/cell.hpp"
#include "include/critter.hpp"
using namespace std;

// Critter constructor
Critter::Critter(Grid *grid, int x, int y)
{
    this->grid = grid;
    this->x = x;
    this->y = y;
}

// Determines if the critter has moved
bool Critter::has_moved() const
{
    return moved;
};

// Sets the critter's moved status
void Critter::set_moved(bool moved)
{
    this->moved = moved;
};
