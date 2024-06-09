#include "include/ant.hpp"
#include <iostream>
#include "include/critter.hpp"

Ant::Ant(Grid *grid, int x, int y) : Critter(grid, x, y)
{
    time_since_moved = 0;
}

void Ant::move()
{
    vector<Cell *> neighbors = grid->get_cell(x, y)->get_eight_neighboring(*grid);

    if (neighbors.empty())
    {
        time_since_moved++;
        return;
    }

    int random_index = rand() % neighbors.size();

    if (neighbors[random_index]->is_empty())
    {
        // if the cell is out of bounds, ensure it stays in the same place and reset time_since_moved
        Cell cell = *neighbors[random_index];
        if (cell.get_x() < 0 || cell.get_x() >= grid->get_width() || cell.get_y() < 0 || cell.get_y() >= grid->get_height())
        {
            time_since_moved = 0;
            return;
        }

        // move the ant to the new cell and update the time_since_moved
        neighbors[random_index]->set_critter(this);
        grid->get_cell(x, y)->remove_critter();
        x = neighbors[random_index]->get_x();
        y = neighbors[random_index]->get_y();
        time_since_moved = 0;
    }
    else
    {
        time_since_moved++;
    }
}

void Ant::breed()
{
    // normal ants can't breed
    // return;
}

void Ant::die()
{
    if (time_since_moved >= 5)
    {
        grid->get_cell(x, y)->remove_critter();
        delete this;
    }
}