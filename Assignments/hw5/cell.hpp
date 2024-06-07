#ifndef CELL_HPP
#define CELL_HPP

#include <vector>
#include <iostream>
#include "critter.hpp"
#include "grid.hpp"

using namespace std;

class Cell
{
private:
    Critter *critter;
    int x, y;
    vector<Cell> getNeighbors(const vector<pair<int, int>> &directions, Grid &grid) const;

public:
    Cell() : critter(nullptr), x(0), y(0) {}
    Cell(int new_x, int new_y) : critter(nullptr), x(new_x), y(new_y) {}
    Cell(int x, int y, Critter *c) : critter(c), x(x), y(y)
    {
        if (critter != nullptr)
        {
            critter->setCurrentCell(this);
        }
    }

    bool isOccupied() const { return critter != nullptr; }
    void setCritter(Critter *new_critter);
    void removeCritter();
    Critter *getCritter() const { return critter; }
    int getX() const { return x; }
    int getY() const { return y; }
    void drawCell() const;
    vector<Cell> getEightNeighboring(Grid &grid) const;
    vector<Cell> getSixteenNeighboring(Grid &grid) const;
};

vector<Cell> Cell::getNeighbors(const vector<pair<int, int>> &directions, Grid &grid) const
{
    vector<Cell> neighbors;

    for (const auto &direction : directions)
    {
        int nx = x + direction.first;
        int ny = y + direction.second;

        // Check if the neighboring cell is within the grid bounds
        if (nx >= 0 && nx < grid.getWidth() && ny >= 0 && ny < grid.getHeight())
        {
            neighbors.push_back(grid.getBoard()[ny][nx]);
        }
    }

    return neighbors;
}

vector<Cell> Cell::getEightNeighboring(Grid &grid) const
{
    const vector<pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    return getNeighbors(directions, grid);
}

vector<Cell> Cell::getSixteenNeighboring(Grid &grid) const
{
    const vector<pair<int, int>> directions = {
        {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2}, {-1, -2}, {-1, 2}, {0, -2}, {0, 2}, {1, -2}, {1, 2}, {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}};
    return getNeighbors(directions, grid);
}

void Cell::drawCell() const
{
    if (critter != nullptr)
    {
        cout << "[" << critter->getIcon() << "]";
    }
    else
    {
        cout << "[ ]";
    }
}

void Cell::setCritter(Critter *new_critter)
{
    critter = new_critter;
    if (new_critter != nullptr)
    {
        new_critter->setCurrentCell(this);
    }
}
void Cell::removeCritter()
{
    if (critter != nullptr)
    {
        critter->setCurrentCell(nullptr);
    }
    critter = nullptr;
}

#endif