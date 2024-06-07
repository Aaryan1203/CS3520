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

    int getHeight() { return height; };
    int getWidth() { return width; };
    vector<vector<Cell>> &getBoard() { return board; }
    void drawGrid() const;
};

void Grid::drawGrid() const
{
    for (const auto &row : board)
    {
        for (const auto &cell : row)
        {
            cell.drawCell();
        }
        cout << endl;
    }
}

#endif