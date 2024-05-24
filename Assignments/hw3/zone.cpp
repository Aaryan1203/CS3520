/* zone.cpp ---
 *
 * Filename: zone.cpp
 * Description:
 * Author: Adeel Bhutta
 * Maintainer:
 * Created: Wed May 15 2024
 * Last-Updated:
 *           By:
 *     Update #: 0
 * Keywords:
 * Compatibility:
 *
 */

/* Copyright (c) 2016 Adeel Bhutta
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */
#include "zone.hpp"
#include "slider.hpp"
#include "ball.hpp"
#include <ncurses.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <string>
#include "screens.hpp"
using namespace std;

// Initializes zone position and dimensions
zone_t *init_zone(int upper_left_x, int upper_left_y, int width, int height)
{
  zone_t *z;
  z = (zone_t *)malloc(sizeof(zone_t));
  z->upper_left_x = upper_left_x + 10; // added 10 to create some space on the left side of the zone to display messages
  z->upper_left_y = upper_left_y;
  z->width = width - 10;
  z->height = height;
  z->draw_char = '#';
  z->color[0] = 0;
  z->color[1] = 0;
  z->color[2] = 0;
  return (z);
}

// Renders zone on the screen
void draw_zone(zone_t *z)
{
  int row_counter, column_counter;

  // Draw the top side of the zone
  for (row_counter = z->upper_left_x; row_counter <= (z->upper_left_x + z->width); row_counter++)
  {
    mvprintw(z->upper_left_y, row_counter, "%c", z->draw_char);
  }

  // Draw left side of zone
  for (column_counter = z->upper_left_y; column_counter <= (z->upper_left_y + z->height); column_counter++)
  {
    mvprintw(column_counter, z->upper_left_x, "%c", z->draw_char);
  }

  // Draw right side of well
  for (column_counter = z->upper_left_y; column_counter <= (z->upper_left_y + z->height); column_counter++)
  {
    mvprintw(column_counter, (z->upper_left_x + z->width), "%c", z->draw_char);
  }

  // Draw Bottom of zone
  for (row_counter = z->upper_left_x; row_counter < (z->upper_left_x + z->width); row_counter++)
  {
    // printf("%d\n", row_counter);
    // printf("%d\n", z->upper_left_y + z->height);
    mvprintw((z->upper_left_y + z->height), row_counter, "%c", z->draw_char);
    // printf("*****\n");
  }
}

// Replaces the zone boundary with blank spaces
void undraw_zone(zone_t *z)
{
  int row_counter, column_counter;

  // Draw the top side of the zone
  for (row_counter = z->upper_left_x; row_counter <= (z->upper_left_x + z->width); row_counter++)
  {
    mvprintw(z->upper_left_y, row_counter, " ", z->draw_char);
  }

  // Draw left side of zone
  for (column_counter = z->upper_left_y; column_counter <= (z->upper_left_y + z->height); column_counter++)
  {
    mvprintw(column_counter, z->upper_left_x, " ", z->draw_char);
  }

  // Draw right side of well
  for (column_counter = z->upper_left_y; column_counter <= (z->upper_left_y + z->height); column_counter++)
  {
    mvprintw(column_counter, (z->upper_left_x + z->width), " ", z->draw_char);
  }

  // Draw Bottom of zone
  for (row_counter = z->upper_left_x; row_counter <= (z->upper_left_x + z->width); row_counter++)
  {
    mvprintw(z->upper_left_y + z->height, row_counter, " ", z->draw_char);
  }
}

void new_round(slider_t *bottom, slider_t *top, ball_t *b, zone_t *z)
{
  undraw_ball(b);
  undraw_slider(bottom);
  undraw_slider(top);

  // Reset the ball's position to the center of the zone
  b->upper_left_x = z->upper_left_x + z->width / 2;
  b->upper_left_y = z->upper_left_y + z->height / 2;

  // Reset the sliders to their starting positions
  top->upper_left_x = z->width / 2 + 5;
  top->upper_left_y = 5;

  bottom->upper_left_x = z->width / 2 + 5;
  bottom->upper_left_y = z->height - 5;

  // Clear the screen and redraw everything
  draw_zone(z);
  draw_slider(bottom);
  draw_slider(top);
  draw_ball(b);
  refresh();
}

void show_time(time_t start_time, time_t &last_update_time, int &seconds_left, slider_t *player_one, slider_t *player_two)
{
  time_t current_time = time(NULL);
  double elapsed_time = difftime(current_time, start_time);
  double time_since_last_update = difftime(current_time, last_update_time);

  // Update the timer every second
  if (time_since_last_update >= 1.0)
  {
    seconds_left--;
    int minutes = seconds_left / 60;
    int seconds = seconds_left % 60;
    mvprintw(7, 0, "Time left");
    mvprintw(8, 0, "%i:%02d", minutes, seconds);
    refresh();
    last_update_time = current_time;
  }

  if (seconds_left <= 0)
  {
    game_over_screen(player_one, player_two, seconds_left);
  }
}

void display_score(slider_t *player_one, slider_t *player_two)
{
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);

  string player_one_text = "Player 1: " + to_string(player_one->game_score);
  string player_two_text = "Player 2: " + to_string(player_two->game_score);

  // calculate the x positions for the two scores
  int player_one_x = max_x / 3 - player_one_text.length() / 2;
  int player_two_x = 2 * max_x / 3 - player_two_text.length() / 2;

  mvprintw(1, player_one_x, player_one_text.c_str());
  mvprintw(1, player_two_x, player_two_text.c_str());
}
