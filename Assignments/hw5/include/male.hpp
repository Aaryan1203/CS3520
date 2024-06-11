#ifndef MALE_HPP
#define MALE_HPP

#include "./critter.hpp"
#include "./cell.hpp"
#include "./ant.hpp"

/*
    Male class
    Each male ant has a time since it moved
    Each male can print itsekf
*/
class Male : public Ant
{
public:
    Male(Grid *grid, int x, int y);
    string print() const;
private:
    int time_since_moved;
};

#endif
