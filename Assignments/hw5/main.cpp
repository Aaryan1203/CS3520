#include <ncurses.h>
#include "include/cell.hpp"
#include "include/critter.hpp"
#include "include/grid.hpp"
#include "include/simulation.hpp"

int main()
{
    int width = 20;
    int height = 20;
    int num_doodlebugs = 10;
    int num_ants = 50;
    int num_queens = 10;

    Simulation simulation(width, height, num_doodlebugs, num_ants, num_queens);
    simulation.run();

    return 0;
}
