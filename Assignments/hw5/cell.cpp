
#include <vector>
#include <iostream>
#include "include/critter.hpp"
#include "include/grid.hpp"
#include "include/cell.hpp"

Cell::Cell(int new_x, int new_y)
{
    this->x = new_x;
    this->y = new_y;
    critter = nullptr;
}

bool Cell::is_empty() const
{
    return critter == nullptr;
}

Critter *Cell::get_critter() const
{
    return critter;
}

void Cell::set_critter(Critter *new_critter)
{
    this->critter = new_critter;
}

void Cell::remove_critter()
{
    critter = nullptr;
}

int Cell::get_x() const
{
    return x;
};

int Cell::get_y() const
{
    return y;
};

void Cell::draw_cell() const
{
    if (critter != nullptr)
    {
        cout << "[" << critter->print() << "]";
    }
    else
    {
        cout << "[ ]";
    }
}

vector<Cell *> Cell::get_eight_neighboring(Grid &grid) const
{
    const int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    vector<Cell *> neighbors;

    for (const auto &direction : directions)
    {
        int nx = x + direction[0];
        int ny = y + direction[1];

        // Check if the neighboring cell is within the grid bounds
        if (nx >= 0 && nx < grid.get_width() && ny >= 0 && ny < grid.get_height())
        {
            neighbors.push_back(grid.get_cell(ny, nx));
        }
    }
    return neighbors;
}


vector<Cell *> Cell::get_sixteen_neighboring(Grid &grid) const
{
    const int directions[16][2] = {
        {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2}, {-1, -2}, {-1, 2}, {0, -2}, {0, 2}, {1, -2}, {1, 2}, {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}};
    vector<Cell *> neighbors;

    for (const auto &direction : directions)
    {
        int nx = x + direction[0];
        int ny = y + direction[1];

        // Check if the neighboring cell is within the grid bounds
        if (nx >= 0 && nx < grid.get_width() && ny >= 0 && ny < grid.get_height())
        {
            neighbors.push_back(grid.get_cell(ny, nx));
        }
    }
    return neighbors;
}