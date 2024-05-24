#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include "screens.hpp"
#include "slider.hpp"
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
    char mesg5[] = "On the following page you will be asked to input some specifications for your game";
    char mesg6[] = "Press 't' to continue";
    char mesg7[] = "Have fun!";

    mvprintw(zone_height / 2 - 3, (zone_width - strlen(mesg1)) / 2, "%s", mesg1);
    mvprintw(zone_height / 2 - 2, (zone_width - strlen(mesg2)) / 2, "%s", mesg2);
    mvprintw(zone_height / 2 - 1, (zone_width - strlen(mesg3)) / 2, "%s", mesg3);
    mvprintw(zone_height / 2, (zone_width - strlen(mesg4)) / 2, "%s", mesg4);
    mvprintw(zone_height / 2 + 1, (zone_width - strlen(mesg5)) / 2, "%s", mesg5);
    mvprintw(zone_height / 2 + 2, (zone_width - strlen(mesg6)) / 2, "%s", mesg6);
    mvprintw(zone_height / 2 + 3, (zone_width - strlen(mesg7)) / 2, "%s", mesg7);

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

ScreenInput input_screen()
{
    int zone_height, zone_width;
    initscr();
    noecho();

    getmaxyx(stdscr, zone_height, zone_width);

    ScreenInput input_struct;
    char slider_prompt[] = "Please enter a size for the slider (4 - 7): ";
    input_struct.slider_size = prompt_input(slider_prompt, &input_struct, "slider_size", 4, 7);
    clear();
    refresh();
    int max_width = zone_width - 2;
    char goal_prompt[] = "Please enter a size for the goal (4 - 20)";
    input_struct.goal_width = prompt_input(goal_prompt, &input_struct, "goal_width", 4, 20);
    clear();
    refresh();
    char game_prompt[] = "Please enter the number of games per level (3 - 11)";
    input_struct.game_size = prompt_input(game_prompt, &input_struct, "game_size", 4, 20);
    clear();
    refresh();

    return input_struct;
}

int prompt_input(char message[], ScreenInput *input_struct, string input_type, int input_min, int input_max)
{
    int zone_height, zone_width;
    initscr();
    noecho();

    getmaxyx(stdscr, zone_height, zone_width);

    char welcome_message[] = "Welcome to two player air hockey!";
    char error_msg[] = "Please enter a valid size";
    char odd_error_msg[] = "Please enter an odd number";

    mvprintw(zone_height / 2 - 2, (zone_width - strlen(welcome_message)) / 2, "%s", welcome_message);
    mvprintw(zone_height / 2 - 1, (zone_width - strlen(message)) / 2, "%s", message);
    int *input_field;
    while (true)
    {
        char input_text[3];
        mvprintw(zone_height / 2, (zone_width - strlen(message)) / 2, " ");
        echo();
        getstr(input_text);
        noecho();
        if (input_type == "slider_size")
        {
            *input_field = input_struct->slider_size;
        }
        else if (input_type == "goal_width")
        {
            *input_field = input_struct->goal_width;
        }
        else if (input_type == "game_size")
        {
            *input_field = input_struct->game_size;
        }

        *input_field = atoi(input_text);

        if (*input_field >= input_min && *input_field <= input_max)
        {
            if (input_type == "game_size" && *input_field % 2 == 0)
            {
                // Display an error message if the number is not odd
                mvprintw(zone_height / 2 + 1, (zone_width - strlen(odd_error_msg)) / 2, "%s", odd_error_msg);
                refresh();
                continue;
            }

            // clear the error message
            mvprintw(zone_height / 2 + 1, (zone_width - strlen(error_msg)) / 2, "                               ");
            mvprintw(zone_height / 2 + 1, (zone_width - strlen(message)) / 2, "You selected slider size: %d", *input_field);
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
    return *input_field;
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

void game_over_screen(slider_t *player_one, slider_t *player_two, int seconds_left)
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

    string mesg1 = "The game is over! Player 1 scored " + to_string(player_one->game_score) + " points and Player 2 scored " + to_string(player_two->game_score) + " points";
    string mesg2 = "Player " + to_string(player_one->game_score == 7 ? 1 : 2) + " is the winner!";
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