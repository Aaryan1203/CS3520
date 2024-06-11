#ifndef ANT_HPP
#define ANT_HPP

#include <vector>
#include <string>
#include "./cell.hpp"
#include "./critter.hpp"

/*
    * Ant class
    * 
    * This class represents an ant in the simulation.
    * 
    * The ant class is a subclass of the Critter class.
    * 
    * The ant class has the following attributes:
    * 
    * time_since_moved: an integer representing the number of time steps since the ant last moved
    * 
    * The ant class has the following methods:
    * 
    * move: moves the ant to an adjacent cell
    * breed: creates a new ant in an adjacent cell
    * die: removes the ant from the grid
    *
*/
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