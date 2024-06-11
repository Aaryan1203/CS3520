#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "./critter.hpp"
#include "./cell.hpp"
#include <string>

/*
    * Doodlebug class
    * 
    * This class represents a doodlebug in the simulation.
    * 
    * The doodlebug class is a subclass of the Critter class.
    * 
    * The doodlebug class has the following attributes:
    * 
    * time_since_last_eat: an integer representing the number of time steps since the doodlebug last ate
    * time_since_last_breed: an integer representing the number of time steps since the doodlebug last bred
    * current_direction: an integer representing the current direction the doodlebug is moving
    * 
    * The doodlebug class has the following methods:
    * 
    * move: moves the doodlebug to an adjacent cell
    * breed: creates a new doodlebug in an adjacent cell
    * die: removes the doodlebug from the grid
    *
*/
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
    int current_direction;             
    static const int directions[8][2]; 
};

#endif
