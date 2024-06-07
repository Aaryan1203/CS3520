#ifndef QUEEN_HPP
#define QUEEN_HPP

#include "critter.hpp"
#include "cell.hpp"

class Queen : public Critter
{
public:
    Queen() : Critter('Q') {}
};

#endif
