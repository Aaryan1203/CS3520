#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "./critter.hpp"
#include "./cell.hpp"
#include "./ant.hpp"

class Queen : public Ant
{
public:
    Queen(Grid *grid, int x, int y);
    virtual void die();
    virtual string print() const;
private:
    int time_since_moved;
    int time_since_breed;
};

#endif
