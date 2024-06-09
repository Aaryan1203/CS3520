#ifndef CELL_HPP
#define CELL_HPP

#include <vector>
#include <iostream>
#include "./critter.hpp"
#include "./grid.hpp"

using namespace std;

class Critter;

class Cell
{
private:
    Critter *critter;
    int x, y;

public:
    Cell(int new_x, int new_y);
    bool is_empty() const;
    void set_critter(Critter *new_critter);
    void remove_critter();
    Critter *get_critter() const;
    int get_x() const;
    int get_y() const;
    void draw_cell() const;
    vector<Cell *> get_eight_neighboring(Grid &grid) const;
    vector<Cell *> get_sixteen_neighboring(Grid &grid) const;
};

#endif