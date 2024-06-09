#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <memory>
#include <iostream>
#include "./critter.hpp"
#include "./cell.hpp"
using namespace std;

class Cell;

class Grid
{
private:
    vector<vector<Cell *> > board;
    int width;
    int height;

public:
    Grid(int width, int height);
    ~Grid();
    void update();
    void draw_grid(int time_elapsed) const;
    Cell *get_cell(int x, int y);
    void set_cell(int x, int y, Cell *cell);
    int get_width() const;
    int get_height() const;
    bool is_adjacent_to_male(int x, int y);
};

#endif