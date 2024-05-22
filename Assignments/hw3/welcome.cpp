#include <ncurses.h>
#include "include/welcome.hpp"
#include <string.h>

void welcome_screen()
{
    int zone_height, zone_width;
    initscr();
    noecho();

    getmaxyx(stdscr, zone_height, zone_width);

    char mesg1[] = "Welcome to two player air hockey!";
    char mesg2[] = "Player 1 will control their bottom slider using the arrow keys";
    char mesg3[] = "Player 2 will control their top slider using WASD.";
    char mesg4[] = "In order to win the game, one player must reach 10 points.";
    char mesg5[] = "Press 't' to start the game";
    char mesg6[] = "Have fun!";

    mvprintw(zone_height / 2 - 2, (zone_width - strlen(mesg1)) / 2, "%s", mesg1);
    mvprintw(zone_height / 2 - 1, (zone_width - strlen(mesg2)) / 2, "%s", mesg2);
    mvprintw(zone_height / 2, (zone_width - strlen(mesg3)) / 2, "%s", mesg3);
    mvprintw(zone_height / 2 + 1, (zone_width - strlen(mesg4)) / 2, "%s", mesg4);
    mvprintw(zone_height / 2 + 2, (zone_width - strlen(mesg5)) / 2, "%s", mesg5);
    mvprintw(zone_height / 2 + 3, (zone_width - strlen(mesg6)) / 2, "%s", mesg6);

    // wait for the user to press 't' to exit the welcome screen
    while (true)
    {
        int ch = getch();
        if (ch == 't' || ch == 'T')
        {
            break;
        }
    }

    // clear and end the ncurses window
    clear();
    endwin();
}