#ifndef BALL_H
#define BALL_H

#include "zone.hpp"
#include "slider.hpp"

// Forward declarations
typedef struct zone zone_t;
typedef struct slider slider_t;

// ball_t holds all properties of the ball
typedef struct ball
{
  int upper_left_x;
  int upper_left_y;
  double speed_x;
  double speed_y;
  char draw_char;
  char color[3];
} ball_t;

ball_t *init_ball(int upper_left_x, int upper_left_y, zone_t *z);
void draw_ball(ball_t *b);
void undraw_ball(ball_t *b);
bool checkCollisionWithZone(ball_t *b, zone_t *z, int goal_width);
bool checkCollisionSlider(slider_t *s, ball_t *b, int slider_size);
void score_goal(ball_t *b, zone_t *z, slider_t *player_one, slider_t *player_two, int goal_width, int &seconds_left, int game_size, int &total_time);
void moveBall(ball_t *b);

#endif
