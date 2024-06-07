#ifndef CRITTER_HPP
#define CRITTER_HPP

#include <vector>
#include "cell.hpp"

using namespace std;

class Cell; // Forward declaration of the Cell class

class Critter
{
protected:
    char icon;
    Cell *current_cell;

public:
    Critter(char icon) : icon(icon), current_cell(nullptr) {}
    virtual ~Critter() {}

    char getIcon() const { return icon; }
    Cell *getCurrentCell() const { return current_cell; }
    void setCurrentCell(Cell *cell) { current_cell = cell; }
};

#endif