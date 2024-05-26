#ifndef ZONE_H
#define ZONE_H

#include <ctime>
#include "ball.hpp"
#include "slider.hpp"
#include "obstacle.hpp"

typedef struct ball ball_t;
typedef struct obstacle obstacle_t;

enum DIFFICULTY
{
    EASY,
    MEDIUM,
    HARD
};

// This structure holds the properties of the zone such as position and dimesions
typedef struct zone
{
  int upper_left_x;
  int upper_left_y;
  int width;
  int height;
  char draw_char;
  char color[3];
  DIFFICULTY difficulty;
  obstacle_t *obstacles; 
  int num_obstacles;
} zone_t;

void undraw_zone(zone_t *z);
void draw_zone(zone_t *z);
zone_t *init_zone(int upper_left_x, int upper_left_y, int width, int height);
void new_round(slider_t *player_one, slider_t *player_two, ball_t *b, zone_t *z, bool next_level, int &seconds_left, int &total_time);
void show_time(time_t start_time, time_t &last_update_time, int &seconds_left, ball_t *b, zone_t *z, slider_t *player_one, slider_t *player_two, int &total_time);
void display_score(slider_t *player_one, slider_t *player_two, zone_t *z);
void init_obstacles(zone_t *z);
void clear_obstacles(zone_t *z);

#endif
