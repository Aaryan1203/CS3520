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
  int speed_x;
  int speed_y;
  char draw_char;
  char color[3];
} ball_t;

ball_t *init_ball(int upper_left_x, int upper_left_y, int speed_x, int speed_y);
void draw_ball(ball_t *b);
void undraw_ball(ball_t *b);
bool checkCollisionWithZone(ball_t *b, zone_t *z);
bool checkCollisionSlider(slider_t *s, ball_t *b, int slider_size);
void score_goal(ball_t *b, zone_t *z, slider_t *bottom, slider_t *top, int *player_one_score, int *player_two_score);
void moveBall(ball_t *b);

#endif