#ifndef CELL_HPP
#define CELL_HPP

#include <vector>
#include <memory>
#include <ncurses.h>
#include "critter.hpp"
using namespace std;

class Cell
{
private:
    Critter *critter;
    int x, y;

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
    void undrawCell() const;
};

void Cell::drawCell() const
{
    int border_color_pair = 1;
    int icon_color_pair = 2;
    int cell_height = 3;
    int cell_width = 5;

    // Draw the border of the cell
    attron(COLOR_PAIR(border_color_pair));
    mvprintw(y * cell_height, x * cell_width, "+---+");
    mvprintw(y * cell_height + 1, x * cell_width, "|   |");
    mvprintw(y * cell_height + 2, x * cell_width, "+---+");
    attroff(COLOR_PAIR(border_color_pair));

    // Draw the critter icon if the cell is occupied
    if (critter != nullptr)
    {
        attron(COLOR_PAIR(icon_color_pair));
        mvprintw(y * cell_height + 1, x * cell_width + 2, "%c", critter->getIcon());
        attroff(COLOR_PAIR(icon_color_pair));
    }
}

void Cell::undrawCell() const
{
    int cell_height = 3;
    int cell_width = 5;

    for (int i = 0; i < cell_height; ++i)
    {
        mvprintw(y * cell_height + i, x * cell_width, "     ");
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