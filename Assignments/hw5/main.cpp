#include <ncurses.h>
#include "cell.hpp"
#include "critter.hpp"
#include "grid.hpp"

int main()
{
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);    // Border color
    init_pair(2, COLOR_GREEN, COLOR_BLACK);  // Icon color

    Critter critter('C');
    Grid grid(10, 10);

    grid.drawGrid();
    getch(); // Wait for user input

    grid.undrawGrid();
    getch(); // Wait for user input

    endwin();
    return 0;
}
