#include "include/ant.hpp"
#include <iostream>
#include "include/critter.hpp"

Ant::Ant(Grid *grid, int x, int y) : Critter(grid, x, y)
{
    time_since_moved = 0;
}

void Ant::move()
{
    // This part handles trying to move to a position that is out of bounds
    const int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    int original_x = x;
    int original_y = y;

    int random_index = rand() % 8;

    // Calculate new position based on random direction
    int new_x = x + directions[random_index][0];
    int new_y = y + directions[random_index][1];

    // Reflective bounce logic
    if (new_x < 0 || new_x >= grid->get_width() || new_y < 0 || new_y >= grid->get_height())
    {
        // Reflect off the walls
        if (new_x < 0)
            new_x = -new_x;
        if (new_x >= grid->get_width())
            new_x = 2 * grid->get_width() - new_x - 2;
        if (new_y < 0)
            new_y = -new_y;
        if (new_y >= grid->get_height())
            new_y = 2 * grid->get_height() - new_y - 2;

        // If the reflected position is still out of bounds, reset time_since_moved and return
        if (new_x < 0 || new_x >= grid->get_width() || new_y < 0 || new_y >= grid->get_height())
        {
            time_since_moved = 0;
            return;
        }
    }

    // Move to the new position if it's within bounds and the cell is empty
    Cell *target_cell = grid->get_cell(new_x, new_y);
    if (target_cell->is_empty())
    {
        target_cell->set_critter(this);
        grid->get_cell(x, y)->remove_critter();
        x = new_x;
        y = new_y;
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
    return;
}

void Ant::die()
{
    if (time_since_moved >= 5)
    {
        grid->get_cell(x, y)->remove_critter();
        delete this;
    }
}