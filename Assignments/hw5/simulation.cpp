#include "include/doodlebug.hpp"
#include "include/worker.hpp"
#include "include/male.hpp"
#include "include/simulation.hpp"
#include "include/queen.hpp"
#include <thread>
#include <chrono>

// Constructor for the Simulation
Simulation::Simulation(int width, int height, int num_doodlebugs, int num_ants, int num_queens)
    : grid(width, height), time_elapsed(0)
{
    init_grid(num_doodlebugs, num_ants, num_queens);
}

// Runs the simulation
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

// Initializes the grid with the given number of doodlebugs, ants, and queens
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

// Checks if the simulation is over
bool Simulation::is_simulation_over() {
    // check if there are no more doodlebugs or no more ants
    bool no_doodlebugs = true;
    bool no_ants = true;

    // iterate through the grid and check for the presence of doodlebugs and ants
    for (int x = 0; x < grid.get_width(); ++x) {
        for (int y = 0; y < grid.get_height(); ++y) {
            Critter* critter = grid.get_cell(x, y)->get_critter();
            if (critter) {
                if (dynamic_cast<Doodlebug*>(critter)) {
                    no_doodlebugs = false;
                }
                if (dynamic_cast<Ant*>(critter)) {
                    no_ants = false;
                }
                if (!no_doodlebugs && !no_ants) {
                    return false;
                }
            }
        }
    }

    // if either species is completely gone, the simulation is over
    if (no_doodlebugs) {
        cout << "All doodlebugs have died. Game ended in  " << (time_elapsed - 1) << " seconds." << endl;
    }
    if (no_ants) {
        cout << "All ants have died. Game evded in  " << (time_elapsed - 1) << " seconds." << endl;
    }
    return no_doodlebugs || no_ants;
}
