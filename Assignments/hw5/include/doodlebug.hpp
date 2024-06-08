#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP

#include "./critter.hpp"
#include "./cell.hpp"
#include <string>

class Doodlebug : public Critter {
    public:
        Doodlebug(Grid* grid, int x, int y);
        virtual void move();
        virtual void breed();
        virtual void die();
        virtual string print() const;
    private:
        int time_since_last_eat;
        int time_since_last_breed;
        int direction;
};

#endif
