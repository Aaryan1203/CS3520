#ifndef WORKER_HPP
#define WORKER_HPP

#include "critter.hpp"
#include "cell.hpp"

class Worker : public Critter
{
public:
    Worker() : Critter('w') {}
};

#endif
