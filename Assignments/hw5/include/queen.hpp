#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "./critter.hpp"
#include "./cell.hpp"
#include "./ant.hpp"

/*
    * Queen class
    * 
    * This class represents a queen in the simulation.
    * 
    * The queen class is a subclass of the Ant class.
    * They can have cataclyphis
    * 
*/
class Queen : public Ant
{
public:
    Queen(Grid *grid, int x, int y);
    virtual void die();
    virtual void move();
    virtual void breed();
    virtual void mate();
    bool has_mated() const;
    virtual string print() const;
    void set_cataglyphis();
    bool can_reproduce_without_mating() const;

private:
    int time_since_moved;
    int time_since_breed;
    bool has_mated_flag;
    bool can_reproduce_without_mating_flag;
};

#endif
