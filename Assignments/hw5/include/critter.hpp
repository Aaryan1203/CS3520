#ifndef CRITTER_HPP
#define CRITTER_HPP

#include <vector>
#include "./cell.hpp"
#include "./grid.hpp"

using namespace std;

class Critter
{
protected:
    int x, y;
    Grid *grid;

public:
    Critter(Grid *grid, int x, int y);
    virtual void move() = 0;
    virtual void breed() = 0;
    virtual void die() = 0;
    virtual string print() const = 0;
    virtual ~Critter() {}
};

#endif