#include <vector>
#include <memory>
#include <iostream>
#include "include/cell.hpp"
#include "include/critter.hpp"
#include "include/grid.hpp"

Grid::Grid(int width, int height)
{
    this->width = width;
    this->height = height;
    board = vector<vector<Cell *> >(width, vector<Cell *>(height, nullptr));

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            board[x][y] = new Cell(x, y);
        }
    }
}

Grid::~Grid()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            delete board[x][y];
        }
    }
}

Cell *Grid::get_cell(int x, int y)
{
    return board[x][y];
}

void Grid::set_cell(int x, int y, Cell *cell)
{
    board[x][y] = cell;
}

int Grid::get_width() const
{
    return width;
}

int Grid::get_height() const
{
    return height;
}

void Grid::draw_grid(int time_elapsed) const
{
    cout << "Time: " << time_elapsed << endl;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            board[x][y]->draw_cell();
        }
        cout << endl;
    }
}

void Grid::update()
{
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            Critter *critter = board[x][y]->get_critter();
            if (critter)
            {
                critter->move();
                critter->breed();
                critter->die();
            }
        }
    }
}