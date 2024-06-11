#ifndef CRITTER_HPP
#define CRITTER_HPP

#include <vector>
#include "./cell.hpp"
#include "./grid.hpp"

using namespace std;

/*
    * Critter class
    * Represents a single critter in the grid
    * Each critter has x and y coordinates
    * Each critter can move
    * Each critter can breed
    * Each critter can die
    * Each critter can print itself
*/
class Critter
{
protected:
    int x, y;
    Grid *grid;
    bool moved;

public:
    Critter(Grid *grid, int x, int y);
    bool has_moved() const;
    void set_moved(bool moved);
    virtual void move() = 0;
    virtual void breed() = 0;
    virtual void die() = 0;
    virtual string print() const = 0;
    virtual ~Critter() {}
};

#endif