#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "./critter.hpp"
#include "./cell.hpp"
#include <string>

class Doodlebug : public Critter
{
public:
    Doodlebug(Grid *grid, int x, int y);
    virtual void move();
    virtual void breed();
    virtual void die();
    virtual string print() const;

private:
    int time_since_last_eat;
    int time_since_last_breed;
    int current_direction;             // 0: North, 1: North-East, 2: East, ..., 7: North-West
    static const int directions[8][2]; // Clockwise directions
};

#endif
