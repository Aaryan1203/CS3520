#include <iostream>
#include "include/ant.hpp"
#include "include/grid.hpp"
#include "include/worker.hpp"

Worker::Worker(Grid* grid, int x, int y) : Ant(grid, x, y) {
    time_since_moved = 0;
}

string Worker::print() const {
    return "w";
}