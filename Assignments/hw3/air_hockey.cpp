/* air_hockey.cpp ---
 *
 * Filename: air_hockey.cpp
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
#include <ncurses.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <string>
#include "screens.hpp"
#include "key.hpp"
#include "ball.hpp"
#include "air_hockey.hpp"
#include "zone.hpp"

// Main Game function
void air_hockey(int slider_size)
{
  int zone_height, zone_width;
  struct timespec tim = {0, 200000000};
  struct timespec tim_ret;
  int arrow, c;
  int slider_x_speed = 4, slider_y_speed = 4;
  initscr();
  getmaxyx(stdscr, zone_height, zone_width);
  zone_height -= 1;
  zone_width -= 1;
  int player_one_score = 0;
  int player_two_score = 0;
  int center_line = zone_height / 2;
  int seconds_left = 120;
  zone_t *z = init_zone(0, 0, zone_width, zone_height);
  ball_t *b = init_ball(zone_width / 2, zone_height / 2, 1, 1);
  slider_t *top = init_slider(zone_width / 2, 5, 'T', slider_size);
  slider_t *bottom = init_slider(zone_width / 2, zone_height - 5, 'U', slider_size);
  draw_zone(z);
  draw_slider(top);
  draw_slider(bottom);
  draw_ball(b);
  refresh();
  nodelay(stdscr, TRUE); // Do not wait for characters using getch.
  noecho();
  time_t start_time = time(NULL);
  time_t last_update_time = start_time;

  while (1)
  {
    if ((arrow = read_escape(&c)) != NOCHAR)
    {
      switch (arrow)
      {

      // moving the bottom slider to the left
      case LEFT:
        mvprintw(1, 5, "L");
        undraw_slider(bottom);
        moveSlider(bottom, -slider_x_speed, 0);
        break;

      // moving the bottom slider to the right
      case RIGHT:
        mvprintw(1, 5, "R");
        undraw_slider(bottom);
        moveSlider(bottom, slider_x_speed, 0);
        break;

      // moving the bottom slider up
      case UP:
        mvprintw(1, 5, "U");
        undraw_slider(bottom);
        moveSlider(bottom, 0, -1);
        break;

      // moving the bottom slider down
      case DOWN:
        mvprintw(1, 5, "D");
        undraw_slider(bottom);
        moveSlider(bottom, 0, 1);
        break;

      // moving the top slider to the left
      case A:
        mvprintw(1, 5, "A");
        undraw_slider(top);
        moveSlider(top, -slider_x_speed, 0);
        break;

      // moving the top slider to the right
      case D:
        mvprintw(1, 5, "D");
        undraw_slider(top);
        moveSlider(top, slider_x_speed, 0);
        break;

      // moving the top slider up
      case W:
        mvprintw(1, 5, "W");
        undraw_slider(top);
        moveSlider(top, 0, -1);
        break;

      // moving the top slider down
      case S:
        mvprintw(1, 5, "S");
        undraw_slider(top);
        moveSlider(top, 0, 1);
        break;

      // pausing the game
      case P:
        pause_screen();
        break;

      // quitting the game
      case Q:
        clear();
        endwin();
        exit(0);
        break;

      default:
        mvprintw(1, 5, "%c", c);
        break;
      }
    }
    show_time(start_time, last_update_time, seconds_left, player_one_score, player_two_score);
    check_borders(top, bottom, zone_width, zone_height, center_line);
    display_score(&player_one_score, &player_two_score);

    // Undraw before moving elements
    undraw_ball(b);
    undraw_zone(z);

    // Move and draw elements
    moveBall(b);
    draw_zone(z);
    draw_slider(bottom);
    draw_slider(top);
    draw_ball(b);

    // Check collisions
    checkCollisionWithZone(b, z);
    score_goal(b, z, bottom, top, &player_one_score, &player_two_score);
    refresh();

    // Allow sliders to strike the puck only on their side of the center line
    if (b->upper_left_y >= center_line)
    {
      checkCollisionSlider(bottom, b, slider_size);
    }
    if (b->upper_left_y < center_line)
    {
      checkCollisionSlider(top, b, slider_size);
    }

    if (player_one_score == 7 || player_two_score == 7)
    {
      game_over_screen(player_one_score, player_two_score, seconds_left);
    }

    // usleep(200000);
    nanosleep(&tim, &tim_ret);
  }
}