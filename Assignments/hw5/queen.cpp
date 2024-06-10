#include "include/queen.hpp"
#include "include/ant.hpp"
#include "include/grid.hpp"
#include "include/worker.hpp"
#include "include/male.hpp"
#include <random>

Queen::Queen(Grid *grid, int x, int y) : Ant(grid, x, y)
{
    time_since_moved = 0;
    time_since_breed = 0;
    has_mated_flag = false;
    can_reproduce_without_mating_flag = false;
}

string Queen::print() const
{
    return "Q";
}
void Queen::die()
{
    if (time_since_breed >= 90)
    {
        grid->get_cell(x, y)->remove_critter();
        delete this;
    }
}

void Queen::move()
{
    if (has_mated_flag && time_since_breed < 30)
    {
        // Queen doesn't move until it breeds after mating
        time_since_breed++;
        return;
    }

    Ant::move();
}

void Queen::breed()
{
    if ((has_mated_flag && time_since_breed >= 30) || can_reproduce_without_mating_flag)
    {
        // Check for empty cells in the 16-neighborhood
        vector<Cell *> neighbors = grid->get_cell(x, y)->get_sixteen_neighboring(*grid);
        std::cout << "Queen breeding at (" << x << ", " << y << ")" << std::endl;

        int babies_born = 0;
        for (Cell *neighbor : neighbors)
        {
            if (neighbor->is_empty())
            {
                int random_value = rand() % 10000;
                std::cout << "Placing ant at (" << neighbor->get_x() << ", " << neighbor->get_y() << ")" << std::endl;

                if (random_value < 8000) // 60-80% chance to produce a worker ant
                {
                    neighbor->set_critter(new Worker(grid, neighbor->get_x(), neighbor->get_y()));
                }
                else if (random_value < 9800) // 20-40% chance to produce a male ant
                {
                    neighbor->set_critter(new Male(grid, neighbor->get_x(), neighbor->get_y()));
                }
                else if (random_value < 9900) // less than 1% chance to produce a queen ant
                {
                    neighbor->set_critter(new Queen(grid, neighbor->get_x(), neighbor->get_y()));
                }
                else if (random_value < 9950) // less than 0.05% chance to produce a cataglyphis
                {
                    Queen *new_queen = new Queen(grid, neighbor->get_x(), neighbor->get_y());
                    new_queen->set_cataglyphis();
                    neighbor->set_critter(new_queen);
                }

                babies_born++;
                if (babies_born >= 10)
                {
                    break;
                }
            }
        }

        time_since_breed = 0;
        has_mated_flag = false;
    }
}

void Queen::set_cataglyphis()
{
    can_reproduce_without_mating_flag = true;
}

void Queen::mate()
{
    has_mated_flag = true;
    time_since_breed = 0;
}

bool Queen::has_mated() const
{
    return has_mated_flag;
}

bool Queen::can_reproduce_without_mating() const
{
    return can_reproduce_without_mating_flag;
}
