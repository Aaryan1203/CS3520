#include "include/doodlebug.hpp"
#include "include/grid.hpp"
#include "include/ant.hpp"
#include <iostream>

// Constructor for the doodlebug
Doodlebug::Doodlebug(Grid *grid, int x, int y) : Critter(grid, x, y)
{
    time_since_last_eat = 0;
    time_since_last_breed = 0;
    current_direction = 0;
}

// Kills the doodlebug if it has not eaten for 20 time units
void Doodlebug::die()
{
    if (time_since_last_eat >= 20)
    {
        grid->get_cell(x, y)->remove_critter();
        delete this;
    }
}

// Move the doodlebug to an adjacent cell
void Doodlebug::move()
{
    // Check for adjacent ants first and move to eat them if found
    int directions[8][2] = {
        {0, -1},
        {1, -1},
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1}};

    // First, try to find an ant to eat
    for (int i = 0; i < 8; ++i)
    {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        if (new_x >= 0 && new_x < grid->get_width() && new_y >= 0 && new_y < grid->get_height())
        {
            Critter *critter = grid->get_cell(new_x, new_y)->get_critter();
            if (critter && dynamic_cast<Ant *>(critter))
            {
                // 10% chance for the ant to evade the doodlebug
                if (rand() % 100 < 10)
                {
                    cout << "Ant at (" << new_x << ", " << new_y << ") evaded doodlebug at (" << x << ", " << y << ").\n";
                    continue;
                }

                delete critter;
                grid->get_cell(new_x, new_y)->set_critter(this);
                grid->get_cell(x, y)->remove_critter();
                x = new_x;
                y = new_y;
                time_since_last_breed++;
                time_since_last_eat = 0;
                moved = true; // Set moved flag after moving
                return;
            }
        }
    }

    // If no adjacent ants are found, move in the current direction
    int new_x = x + directions[current_direction][0];
    int new_y = y + directions[current_direction][1];

    // Bounce logic
    if (new_x < 0 || new_x >= grid->get_width() || new_y < 0 || new_y >= grid->get_height())
    {
        // Reflect the position
        if (new_x < 0)
            new_x = -new_x;
        if (new_x >= grid->get_width())
            new_x = 2 * (grid->get_width() - 1) - new_x;
        if (new_y < 0)
            new_y = -new_y;
        if (new_y >= grid->get_height())
            new_y = 2 * (grid->get_height() - 1) - new_y;

        // If the reflected position is still out of bounds, skip the move
        if (new_x < 0 || new_x >= grid->get_width() || new_y < 0 || new_y >= grid->get_height())
        {
            current_direction = (current_direction + 1) % 8;
            time_since_last_breed++;
            time_since_last_eat++;
            moved = true;
            return;
        }

        // Update the direction to continue the clockwise pattern after bouncing
        if (current_direction == 4)
        {
            current_direction = 1;
        }
        else if (current_direction == 5)
        {
            current_direction = 2;
        }
        else if (current_direction == 6)
        {
            current_direction = 3;
        }
        else if (current_direction == 7)
        {
            current_direction = 0;
        }
    }

    Critter *critter = grid->get_cell(new_x, new_y)->get_critter();
    if (critter == nullptr)
    {
        // Move to the new cell if empty
        grid->get_cell(new_x, new_y)->set_critter(this);
        grid->get_cell(x, y)->remove_critter();
        x = new_x;
        y = new_y;
    }

    // Change the direction clockwise for the next move
    current_direction = (current_direction + 1) % 8;

    // Increment time since last eat and breed counters
    time_since_last_eat++;
    time_since_last_breed++;

    // Set moved flag
    moved = true;
}

// Breed a new doodlebug if enough time has passed and an empty cell is available
void Doodlebug::breed()
{
    // Ensure at least 10 time units pass before breeding
    if (time_since_last_breed > 10)
    {
        if (rand() % 2 == 0) // 50% chance to breed
        {
            std::cout << "breeding" << std::endl;
            vector<Cell *> neighbors = grid->get_cell(x, y)->get_sixteen_neighboring(*grid);

            for (int i = 0; i < neighbors.size(); i++)
            {
                if (neighbors[i]->is_empty())
                {
                    Doodlebug *new_doodlebug = new Doodlebug(grid, neighbors[i]->get_x(), neighbors[i]->get_y());
                    neighbors[i]->set_critter(new_doodlebug);

                    time_since_last_breed = 0; // Reset breeding time after successful breed
                    return;
                }
            }
        }
        else
        {
            // If breeding does not occur, still reset the breeding timer
            time_since_last_breed = 0;
        }
    }
}

// Print the doodlebug as an 'X'
string Doodlebug::print() const
{
    return "X";
}
