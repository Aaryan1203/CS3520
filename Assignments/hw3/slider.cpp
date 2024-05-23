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
    {"top",
     {{1, 1, 1, 1}},
     0,
     0,
     '%',
     {0, 0, 0}},
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

void check_borders(slider_t *top, slider_t *bottom, int zone_width, int zone_height, int center_line)
{
  // ensuring sliders are within bounds and don't cross the center line
  if (top->upper_left_x - 12 < 0)
    top->upper_left_x = 12;
  if (top->upper_left_x + 5 > zone_width)
    top->upper_left_x = zone_width - 5;
  if (top->upper_left_y < 0)
    top->upper_left_y = 0;
  if (top->upper_left_y > center_line)
    top->upper_left_y = center_line;

  if (bottom->upper_left_x - 12 < 0)
    bottom->upper_left_x = 12;
  if (bottom->upper_left_x + 5 > zone_width)
    bottom->upper_left_x = zone_width - 5;
  if (bottom->upper_left_y < center_line)
    bottom->upper_left_y = center_line;
  if (bottom->upper_left_y > zone_height)
    bottom->upper_left_y = zone_height;
}