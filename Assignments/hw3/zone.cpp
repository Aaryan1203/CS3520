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
  z->difficulty = EASY;
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

  // If the zone is in HARD, draw 3 obstacles in the middle of the zone, make them a random shape
  // if (z->difficulty == HARD)
  // {
  //
  // }
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

void new_round(slider_t *player_one, slider_t *player_two, ball_t *b, zone_t *z, bool next_level, int &seconds_left, int &total_time)
{
  undraw_ball(b);
  undraw_slider(player_one);
  undraw_slider(player_two);

  if (next_level)
  {
    if (player_one->game_score > player_two->game_score)
    {
      player_one->series_score++;
    }
    else
    {
      player_two->series_score++;
    }
    
    player_one->total_score += player_one->game_score;
    player_two->total_score += player_two->game_score;
    player_one->game_score = 0;
    player_two->game_score = 0;

    if (player_one->series_score + player_two->series_score == 3)
    {
      game_over_screen(player_one, player_two, total_time);
    }

    // Change the difficulty of the zone (EASY -> MEDIUM -> HARD)
    if (z->difficulty == EASY)
    {
      z->difficulty = MEDIUM;
      b->speed_x = 1.2;
      b->speed_y = -1.2;
      seconds_left = 120;
    }
    else if (z->difficulty == MEDIUM)
    {
      z->difficulty = HARD;
      b->speed_x = 1.44;
      b->speed_y = -1.44;
      seconds_left = 120;
    }
  }

  // Reset the ball's position to the center of the zone
  b->upper_left_x = z->upper_left_x + z->width / 2;
  b->upper_left_y = z->upper_left_y + z->height / 2;

  // Reset the sliders to their starting positions
  player_two->upper_left_x = z->width / 2 + 5;
  player_two->upper_left_y = 5;

  player_one->upper_left_x = z->width / 2 + 5;
  player_one->upper_left_y = z->height - 5;

  // Clear the screen and redraw everything
  draw_zone(z);
  draw_slider(player_one);
  draw_slider(player_two);
  draw_ball(b);
  refresh();
}

void show_time(time_t start_time, time_t &last_update_time, int &seconds_left, ball_t *b, zone_t *z, slider_t *player_one, slider_t *player_two, int &total_time)
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
    total_time++;
  }

  if (seconds_left <= 0)
  {
    new_round(player_one, player_two, b, z, true, seconds_left, total_time);
  }
}

// TODO: add the level difficulty
void display_score(slider_t *player_one, slider_t *player_two, zone_t *z)
{
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);

  string series_score = "Series: Player One: " + to_string(player_one->series_score) + " - " + "Player Two: " + to_string(player_two->series_score);
  string game_score = "Game Player One: " + to_string(player_one->game_score) + " - Player Two: " + to_string(player_two->game_score);
  string level = "Level: " + to_string(z->difficulty + 1);

  mvprintw(2, 12, series_score.c_str());
  mvprintw(3, 12, game_score.c_str());
  mvprintw(max_y - 2, 12, level.c_str());
}
