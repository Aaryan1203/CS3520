#include <vector>
#include "include/cell.hpp"
#include "include/critter.hpp"
using namespace std;

Critter:: Critter(Grid *grid, int x, int y) {
    this->grid = grid;
    this->x = x;
    this->y = y;
}
