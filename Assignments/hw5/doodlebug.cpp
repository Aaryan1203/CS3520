#include "include/doodlebug.hpp"
#include "include/grid.hpp"
#include "include/ant.hpp"
#include <iostream>

Doodlebug::Doodlebug(Grid *grid, int x, int y) : Critter(grid, x, y)
{
    time_since_last_eat = 0;
    time_since_last_breed = 0;
}

void Doodlebug::die()
{
    if (time_since_last_eat >= 20)
    {
        grid->get_cell(x, y)->remove_critter();
        delete this;
    };
}

void Doodlebug::move()
{
    
}

void Doodlebug::breed()
{
    
}

string Doodlebug::print() const
{
    return "X";
}