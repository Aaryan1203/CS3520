#include "include/ant.hpp"
#include <iostream>
#include "include/critter.hpp"

Ant::Ant(Grid *grid, int x, int y) : Critter(grid, x, y)
{
    time_since_moved = 0;
}

void Ant::move()
{

}

void Ant::breed()
{
}

void Ant::die()
{
    if (time_since_moved >= 5)
    {
        grid->get_cell(x, y)->remove_critter();
        delete this;
    }
}