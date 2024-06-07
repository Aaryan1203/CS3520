#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <vector>
#include <memory>
#include <iostream>
#include "cell.hpp"
#include "critter.hpp"

class Grid
{
private:
    vector<vector<Cell>> board;
    vector<Critter> critters;
    int width;
    int height;
    vector<Cell> getNeighbors(Cell *cell, const vector<pair<int, int>> &directions) const;
    void initializeBoard()
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                board[y][x] = Cell(x, y);
            }
        }
    }

public:
    Grid() : width(100), height(100), board(100, vector<Cell>(100)) { initializeBoard(); }
    Grid(int width, int height) : width(width), height(height), board(height, vector<Cell>(width)) { initializeBoard(); }
    vector<vector<Cell>> &getBoard() { return board; }
    void drawGrid() const;
    void undrawGrid() const;
    vector<Cell> getEightNeighboring(Cell *cell) const;
    vector<Cell> getSixteenNeighboring(Cell *cell) const;
};

void Grid::drawGrid() const
{
    for (const auto &row : board)
    {
        for (const auto &cell : row)
        {
            cell.drawCell();
        }
    }
}

void Grid::undrawGrid() const
{
    for (const auto &row : board)
    {
        for (const auto &cell : row)
        {
            cell.undrawCell();
        }
    }
}

vector<Cell> Grid::getNeighbors(Cell *cell, const vector<pair<int, int>> &directions) const
{
    vector<Cell> neighbors;
    int x = cell->getX();
    int y = cell->getY();

    for (const auto &direction : directions)
    {
        int nx = x + direction.first;
        int ny = y + direction.second;

        // Check if the neighboring cell is within the grid bounds
        if (nx >= 0 && nx < width && ny >= 0 && ny < height)
        {
            neighbors.push_back(board[ny][nx]);
        }
    }

    return neighbors;
}

vector<Cell> Grid::getEightNeighboring(Cell *cell) const
{
    const vector<pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    return getNeighbors(cell, directions);
}

vector<Cell> Grid::getSixteenNeighboring(Cell *cell) const
{
    const vector<pair<int, int>> directions = {
        {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2}, {-1, -2}, {-1, 2}, {0, -2}, {0, 2}, {1, -2}, {1, 2}, {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}};
    return getNeighbors(cell, directions);
}

#endif