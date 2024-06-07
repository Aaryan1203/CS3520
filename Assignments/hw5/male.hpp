#ifndef MALE_HPP
#define MALE_HPP

#include "critter.hpp"
#include "cell.hpp"

class Male : public Critter
{
public:
    Male(int startX, int startY) : Critter('m') {}
};

#endif
