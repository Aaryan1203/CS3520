#include "include/doodlebug.hpp"
#include "include/worker.hpp"
#include "include/male.hpp"
#include "include/simulation.hpp"
#include "include/queen.hpp"
#include <thread>
#include <chrono>

Simulation::Simulation(int width, int height, int num_doodlebugs, int num_ants, int num_queens)
    : grid(width, height), time_elapsed(0)
{
    init_grid(num_doodlebugs, num_ants, num_queens);
}

void Simulation::run()
{
    while (!is_simulation_over())
    {
        grid.update();
        grid.draw_grid(time_elapsed);
        ++time_elapsed;

        this_thread::sleep_for(chrono::seconds(1));
    }
}

void Simulation::init_grid(int num_doodlebugs, int num_ants, int num_queens)
{

    for (int i = 0; i < num_doodlebugs; ++i)
    {
        bool empty = true;
        while (empty)
        {
            int x = rand() % grid.get_width();
            int y = rand() % grid.get_height();
            if (grid.get_cell(x, y)->is_empty())
            {
                grid.get_cell(x, y)->set_critter(new Doodlebug(&grid, x, y));
                empty = false;
                break;
            }
        }
    }
    for (int i = 0; i < num_ants; ++i)
    {
        bool empty = true;
        while (empty)
        {
            int x = rand() % grid.get_width();
            int y = rand() % grid.get_height();
            if (grid.get_cell(x, y)->is_empty())
            {
                grid.get_cell(x, y)->set_critter(new Worker(&grid, x, y));
                empty = false;
                break;
            }
        }
    }
    for (int i = 0; i < num_ants; ++i)
    {
        bool empty = true;
        while (empty)
        {
            int x = rand() % grid.get_width();
            int y = rand() % grid.get_height();
            if (grid.get_cell(x, y)->is_empty())
            {
                grid.get_cell(x, y)->set_critter(new Male(&grid, x, y));
                empty = false;
                break;
            }
        }
    }
    for (int i = 0; i < num_queens; ++i)
    {
        bool empty = true;
        while (empty)
        {
            int x = rand() % grid.get_width();
            int y = rand() % grid.get_height();
            if (grid.get_cell(x, y)->is_empty())
            {
                grid.get_cell(x, y)->set_critter(new Queen(&grid, x, y));
                empty = false;
                break;
            }
        }
    }
}

bool Simulation::is_simulation_over()
{
    if (time_elapsed >= 100)
    {
        return true;
    }
    return false;
}
