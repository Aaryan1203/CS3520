#include <iostream>
#include "include/ant.hpp"
#include "include/grid.hpp"
#include "include/male.hpp"

Male::Male(Grid* grid, int x, int y) : Ant(grid, x, y) {
    time_since_moved = 0;
}

string Male::print() const {
    return "o";
}