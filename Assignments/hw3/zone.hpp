#ifndef ZONE_H
#define ZONE_H

#include <ctime>
#include "ball.hpp"
#include "slider.hpp"

typedef struct ball ball_t;

// This structure holds the properties of the zone such as position and dimesions
typedef struct zone
{
  int upper_left_x;
  int upper_left_y;
  int width;
  int height;
  char draw_char;
  char color[3];
} zone_t;

void undraw_zone(zone_t *z);
void draw_zone(zone_t *z);
zone_t *init_zone(int upper_left_x, int upper_left_y, int width, int height);
void new_round(slider_t *player_one, slider_t *player_two, ball_t *b, zone_t *z);
void show_time(time_t start_time, time_t &last_update_time, int &seconds_left, slider_t *player_one, slider_t *player_two_score);
void display_score(slider_t *player_one, slider_t *player_two);

#endif
