#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include "screens.hpp"
using namespace std;

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
}

void pause_screen()
{
    // save current screen content to a file
    scr_dump("pause_screen");
    clear();
    refresh();

    int zone_height, zone_width;
    initscr();
    noecho();

    getmaxyx(stdscr, zone_height, zone_width);

    char mesg[] = "The game is paused, press p to unpause the game";
    mvprintw(zone_height / 2, (zone_width - strlen(mesg)) / 2, "%s", mesg);

    // wait for the user to press 't' to exit the welcome screen
    while (true)
    {
        int ch = getch();
        if (ch == 'p' || ch == 'P')
        {
            break;
        }
    }

    clear();
    scr_restore("pause_screen_dump");
    refresh();

    // deleting the extra file
    remove("pause_screen");
}

void game_over_screen(int player_one_score, int player_two_score, int seconds_left)
{
    clear();
    refresh();

    int zone_height, zone_width;
    initscr();
    noecho();

    getmaxyx(stdscr, zone_height, zone_width);
    int elapsed_time = 120 - seconds_left;
    int minutes = elapsed_time / 60;
    int seconds = static_cast<int>(elapsed_time) % 60;

    char time_total[6];
    snprintf(time_total, sizeof(time_total), "%01d:%02d", minutes, seconds);

    string mesg1 = "The game is over! Player 1 scored " + to_string(player_one_score) + " points and Player 2 scored " + to_string(player_two_score) + " points";
    string mesg2 = "Player " + to_string(player_one_score == 7 ? 1 : 2) + " is the winner!";
    string mesg3 = "The game took " + string(time_total) + " to complete! Press q to exit the game";

    mvprintw(zone_height / 2 - 1, (zone_width - mesg1.length()) / 2, "%s", mesg1.c_str());
    mvprintw(zone_height / 2, (zone_width - mesg2.length()) / 2, "%s", mesg2.c_str());
    mvprintw(zone_height / 2 + 1, (zone_width - mesg3.length()) / 2, "%s", mesg3.c_str());

    // wait for the user to press 't' to exit the welcome screen
    while (true)
    {
        int ch = getch();
        if (ch == 'q' || ch == 'q')
        {
            clear();
            endwin();
            exit(0);
            break;
        }
    }
}

int select_slider_size_screen()
{
    int zone_height, zone_width;
    initscr();
    noecho();

    getmaxyx(stdscr, zone_height, zone_width);

    char mesg1[] = "Welcome to two player air hockey!";
    char mesg2[] = "Please enter the size of the slider you would like to use (4-7)";
    char error_msg[] = "Please enter a valid size (4-7)";

    mvprintw(zone_height / 2 - 2, (zone_width - strlen(mesg1)) / 2, "%s", mesg1);
    mvprintw(zone_height / 2 - 1, (zone_width - strlen(mesg2)) / 2, "%s", mesg2);

    int slider_size;
    while (true)
    {
        char input[3];
        // Clear the input area
        mvprintw(zone_height / 2, (zone_width - strlen(mesg2)) / 2, " ");
        // Move cursor to input position
        move(zone_height / 2, (zone_width - strlen(mesg2)) / 2);
        // Echo to show the user input
        echo();
        getstr(input);
        // Disable echo after input is entered
        noecho();
        slider_size = atoi(input);

        if (slider_size >= 4 && slider_size <= 7)
        {
            // clear the error message
            mvprintw(zone_height / 2 + 1, (zone_width - strlen(error_msg)) / 2, "                               ");
            mvprintw(zone_height / 2 + 1, (zone_width - strlen(mesg2)) / 2, "You selected slider size: %d", slider_size);
            refresh();
            break;
        }
        else
        {
            // Defining the error message to easily get the length
            mvprintw(zone_height / 2 + 1, (zone_width - strlen(error_msg)) / 2, "%s", error_msg);
            refresh();
        }
    }

    // Wait for a few seconds before clearing the screen so the user can view their selected size
    napms(500);
    clear();
    endwin();

    return slider_size;
}