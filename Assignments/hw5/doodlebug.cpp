#include "include/doodlebug.hpp"
#include "include/grid.hpp"
#include "include/ant.hpp"
#include <iostream>

const int Doodlebug::directions[8][2] = {
    {-1, 0}, 
    {-1, 1}, 
    {0, 1},  
    {1, 1},  
    {1, 0},  
    {1, -1}, 
    {0, -1}, 
    {-1, -1} 
};

Doodlebug::Doodlebug(Grid *grid, int x, int y) : Critter(grid, x, y)
{
    time_since_last_eat = 0;
    time_since_last_breed = 0;
    current_direction = 0;
}

void Doodlebug::die()
{
    if (time_since_last_eat >= 20)
    {
        grid->get_cell(x, y)->remove_critter();
        delete this;
    }
}

void Doodlebug::move()
{
    vector<Cell *> neighbors = grid->get_cell(x, y)->get_eight_neighboring(*grid);

    // Look for adjacent ants to eat
    for (Cell *neighbor : neighbors)
    {
        Critter *critter = neighbor->get_critter();
        if (critter && dynamic_cast<Ant *>(critter))
        {
            // Move to the cell and eat the ant
            neighbor->set_critter(this);
            grid->get_cell(x, y)->remove_critter();
            x = neighbor->get_x();
            y = neighbor->get_y();
            delete critter; // Eat the ant
            time_since_last_eat = 0;
            time_since_last_breed++;
            current_direction = (current_direction + 1) % 8; // Move to the next direction
            return;
        }
    }

    // No adjacent ants, move in the current direction
    int new_x = x + directions[current_direction][0];
    int new_y = y + directions[current_direction][1];

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
            time_since_last_eat++;
            time_since_last_breed++;
            current_direction = (current_direction + 1) % 8; // Change direction clockwise
            return;
        }
    }

    Cell *target_cell = grid->get_cell(new_x, new_y);
    if (target_cell->is_empty())
    {
        target_cell->set_critter(this);
        grid->get_cell(x, y)->remove_critter();
        x = new_x;
        y = new_y;
        // Only update direction after a successful move
        current_direction = (current_direction + 1) % 8; // Change direction clockwise
    }
    else
    {
        // Change direction even if the target cell is not empty
        current_direction = (current_direction + 1) % 8;
    }

    time_since_last_eat++;
    time_since_last_breed++;
}

void Doodlebug::breed()
{
    if (time_since_last_breed > 10)  // Ensure at least 10 time units pass before breeding
    {
        vector<Cell *> neighbors = grid->get_cell(x, y)->get_sixteen_neighboring(*grid);

        for (int i = 0; i < neighbors.size(); i++)
        {
            if (neighbors[i]->is_empty())
            {
                Doodlebug *new_doodlebug = new Doodlebug(grid, neighbors[i]->get_x(), neighbors[i]->get_y());
                neighbors[i]->set_critter(new_doodlebug);

                // Debug statement: Confirm the creation of a new Doodlebug
                std::cout << "Created new Doodlebug at (" << neighbors[i]->get_x() << ", " << neighbors[i]->get_y() << ")" << std::endl;

                time_since_last_breed = 0;  // Reset breeding time after successful breed
                return;
            }
        }
    }
}

string Doodlebug::print() const
{
    return "X";
}
