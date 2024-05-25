/* slider.cpp ---
 *
 * Filename: slider.cpp
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
#include "slider.hpp"
#include <ncurses.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>

// This intializes the properties of the slider
const slider_t slider_types[2] = {
    // Player Two
    {"top",
     {{1, 1, 1, 1}},
     0,
     0,
     '%',
     {0, 0, 0}},
    // Player One
    {"bottom",
     {{1, 1, 1, 1}},
     0,
     0,
     '+',
     {0, 0, 0}},
};

// Changes the location of the slider
void moveSlider(slider_t *s, int x, int y)
{
  // Adjusted so the slider is moved based on its relative location, not the absolute location
  s->upper_left_x += x;
  s->upper_left_y += y;
}

// Intializes the slider
slider_t *init_slider(int initial_x, int initial_y, char type, int size)
{
  slider_t *s = (slider_t *)malloc(sizeof(slider_t));
  if (type == 'T')
  {
    memcpy(s, &slider_types[0], sizeof(slider_t));
  }
  else
  {
    memcpy(s, &slider_types[1], sizeof(slider_t));
  }
  s->series_score = 0;
  s->game_score = 0;
  s->total_score = 0;
  s->upper_left_x = initial_x;
  s->upper_left_y = initial_y;
  s->size = size;
  return s;
}

// Renders the slider on the screen

void draw_slider(slider_t *s)
{
  for (int x = 0; x < s->size; ++x)
  {
    mvprintw(s->upper_left_y, s->upper_left_x + x, "%c", s->draw_char);
  }
}

// Replaces the slider with blank spaces
void undraw_slider(slider_t *s)
{
  for (int x = 0; x < s->size; ++x)
  {
    mvprintw(s->upper_left_y, s->upper_left_x + x, " ");
  }
}

void check_borders(slider_t *player_one, slider_t *player_two, int zone_width, int zone_height, int center_line)
{
  // ensuring sliders are within bounds and don't cross the center line
  if (player_one->upper_left_x - 12 < 0)
    player_one->upper_left_x = 12;
  if (player_one->upper_left_x + 5 > zone_width)
    player_one->upper_left_x = zone_width - 5;
  if (player_one->upper_left_y < center_line)
    player_one->upper_left_y = center_line;
  if (player_one->upper_left_y > zone_height)
    player_one->upper_left_y = zone_height;

  if (player_two->upper_left_x - 12 < 0)
      player_two->upper_left_x = 12;
  if (player_two->upper_left_x + 5 > zone_width)
      player_two->upper_left_x = zone_width - 5;
  if (player_two->upper_left_y < 0)
      player_two->upper_left_y = 0;
  if (player_two->upper_left_y > center_line)
      player_two->upper_left_y = center_line;
}
