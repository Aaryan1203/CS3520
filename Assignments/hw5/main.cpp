#include <ncurses.h>
#include "cell.hpp"
#include "critter.hpp"
#include "grid.hpp"

int main()
{
    Critter critter('C');
    Grid grid(10, 10);
    
    grid.drawGrid();

    endwin();
    return 0;
}
