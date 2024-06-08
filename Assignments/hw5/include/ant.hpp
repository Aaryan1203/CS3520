#ifndef ANT_HPP
#define ANT_HPP

#include <vector>
#include <string>
#include "./cell.hpp"
#include "./critter.hpp"

class Ant : public Critter
{
public:
    Ant(Grid *grid, int x, int y);
    virtual void move();
    virtual void breed();
    virtual void die();

protected:
    int time_since_moved;
};

#endif