#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "critter.hpp"
#include "cell.hpp"

class DoodleBug : public Critter
{
public:
    DoodleBug() : Critter('D') {}
};

#endif
