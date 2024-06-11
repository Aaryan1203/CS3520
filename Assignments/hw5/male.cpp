#include <iostream>
#include "include/ant.hpp"
#include "include/grid.hpp"
#include "include/male.hpp"

// Constructor for the Male ant
Male::Male(Grid* grid, int x, int y) : Ant(grid, x, y) {
    time_since_moved = 0;
}

// Prints a male ant
string Male::print() const {
    return "o";
}