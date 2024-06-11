#include <vector>
#include <memory>
#include <iostream>
#include "include/cell.hpp"
#include "include/critter.hpp"
#include "include/grid.hpp"
#include "include/queen.hpp"
#include "include/male.hpp"
#include "include/doodlebug.hpp"

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
    // Mark all critters as not moved
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            Critter *critter = board[x][y]->get_critter();
            if (critter)
            {
                critter->set_moved(false);
            }
        }
    }

    // Move doodlebugs
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            Critter *critter = board[x][y]->get_critter();
            if (critter && dynamic_cast<Doodlebug *>(critter) && !critter->has_moved())
            {
                critter->move();
            }
        }
    }

    // Doodlebugs breed
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            Critter *critter = board[x][y]->get_critter();
            if (critter && dynamic_cast<Doodlebug *>(critter))
            {
                critter->breed();
            }
        }
    }

    // Doodlebugs die
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            Critter *critter = board[x][y]->get_critter();
            if (critter && dynamic_cast<Doodlebug *>(critter))
            {
                critter->die();
            }
        }
    }

    // Move ants
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            Critter *critter = board[x][y]->get_critter();
            if (critter && dynamic_cast<Ant *>(critter) && !critter->has_moved())
            {
                critter->move();
            }
        }
    }

    // Ants breed
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            Critter *critter = board[x][y]->get_critter();
            if (critter && dynamic_cast<Ant *>(critter))
            {
                critter->breed();
            }
        }
    }

    // Ants die
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            Critter *critter = board[x][y]->get_critter();
            if (critter && dynamic_cast<Ant *>(critter))
            {
                critter->die();
            }
        }
    }

    // Handle breeding and dying for queens
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            Cell *cell = get_cell(x, y);
            Critter *critter = cell->get_critter();
            if (critter != nullptr)
            {
                Queen *queen = dynamic_cast<Queen *>(critter);
                if (queen != nullptr)
                {
                    if (!queen->has_mated() && is_adjacent_to_male(x, y))
                    {
                        queen->mate();
                    }
                    if (queen->can_reproduce_without_mating())
                    {
                        queen->breed();
                    }
                }

                // Handle breeding and dying for all critters, including Doodlebugs
                critter->breed();
                critter->die();
            }
        }
    }
}


bool Grid::is_adjacent_to_male(int x, int y)
{
    vector<Cell *> neighbors = get_cell(x, y)->get_eight_neighboring(*this);
    for (Cell *neighbor : neighbors)
    {
        if (dynamic_cast<Male *>(neighbor->get_critter()) != nullptr)
        {
            return true;
        }
    }
    return false;
}
