#include <iostream>
#include "include/ant.hpp"
#include "include/grid.hpp"
#include "include/worker.hpp"

// Constructor for the Worker ant
Worker::Worker(Grid* grid, int x, int y) : Ant(grid, x, y) {
    time_since_moved = 0;
}

// Prints a worker ant
string Worker::print() const {
    return "w";
}