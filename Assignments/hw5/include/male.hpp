#ifndef MALE_HPP
#define MALE_HPP

#include "./critter.hpp"
#include "./cell.hpp"
#include "./ant.hpp"

class Male : public Ant
{
public:
    Male(Grid *grid, int x, int y);
    string print() const;
private:
    int time_since_moved;
};

#endif
