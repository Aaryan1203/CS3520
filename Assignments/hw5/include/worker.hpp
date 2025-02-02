#ifndef WORKER_HPP
#define WORKER_HPP

#include "./critter.hpp"
#include "./cell.hpp"
#include "./ant.hpp"

/*
    Worker class
    Each worker ant has a time since it moved
    Each worker can print itself
*/
class Worker : public Ant
{
public:
    Worker(Grid *grid, int x, int y);
    string print() const;

private:
    int time_since_moved;
};

#endif
