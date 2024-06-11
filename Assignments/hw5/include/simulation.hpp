#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "./grid.hpp"

/*
    * Simulation class
    * Represents the simulation
    * Each simulation has a grid
    * Each simulation has a time elapsed
    * Each simulation can run
*/
class Simulation {
    public:
        Simulation(int width, int height, int num_doodlebugs, int num_ants, int num_queens);
        void run();
    private:
        void init_grid(int num_doodlebugs, int num_ants, int num_queens);
        bool is_simulation_over();

        Grid grid;
        int time_elapsed;
};

#endif
