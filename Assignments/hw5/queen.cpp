#include "include/queen.hpp"
#include "include/ant.hpp"
#include "include/grid.hpp"

Queen::Queen(Grid *grid, int x, int y) : Ant(grid, x, y)
{
    time_since_moved = 0;
    time_since_breed = 0;
}

string Queen::print() const
{
    return "Q";
}
void Queen::die()
{
    if (time_since_moved >= 5 || time_since_breed >= 90)
    {
        grid->get_cell(x, y)->remove_critter();
        delete this;
    }
}