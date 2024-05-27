#ifndef BALL_H
#define BALL_H

#include "slider.hpp"

typedef struct zone zone_t;
typedef struct slider slider_t;
typedef struct obstacle obstacle_t;

/*
 * @struct ball
 * @brief This structure holds the ball properties.
 */
typedef struct ball
{
  int upper_left_x; /**< The x-coordinate of the upper left corner of the ball */
  int upper_left_y; /**< The y-coordinate of the upper left corner of the ball */
  double speed_x;   /**< The speed of the ball in the x-direction */
  double speed_y;   /**< The speed of the ball in the y-direction */
  char draw_char;   /**< The character used to draw the ball */
  char color[3];    /**< The color of the ball */
} ball_t;

/*
 * @brief This function initializes the ball.
 *
 * @param upper_left_x: The x-coordinate of the upper left corner of the ball.
 * @param upper_left_y: The y-coordinate of the upper left corner of the ball.
 * @param z: The zone in which the ball is located.
 *
 * @return ball_t*: The ball.
 */
ball_t *init_ball(int upper_left_x, int upper_left_y, zone_t *z);

/*
 * @brief This function draws the ball onto the screen.
 *
 * @param b: The ball to draw.
 *
 * @return void
 */
void draw_ball(ball_t *b);

/*
 * @brief This function undraws the ball from the screen.
 *
 * @param b: The ball to undraw.
 *
 * @return void
 */
void undraw_ball(ball_t *b);

/*
 * @brief This function constantly checks if the ball collides with the zone.
 *
 * @param b: The ball.
 * @param z: The zone.
 * @param goal_width: The width of the goal.
 *
 * @return bool: True if the ball collides with the zone, false otherwise.
 */
bool checkCollisionWithZone(ball_t *b, zone_t *z, int goal_width);

/*
 * @brief This function constantly checks if the ball collides with the slider.
 *
 * @param s: The slider.
 * @param b: The ball.
 * @param slider_size: The size of the slider.
 *
 * @return bool: True if the ball collides with the slider, false otherwise.
 */
bool checkCollisionSlider(slider_t *s, ball_t *b, int slider_size);

/*
 * @brief This function constantly checks if the ball collides with the obstacle.
 *
 * @param b: The ball.
 * @param o: The obstacle.
 *
 * @return bool: True if the ball collides with the obstacle, false otherwise.
 */
bool checkCollisionWithObstacle(ball_t *b, obstacle_t *o); 

/*
 * @brief This function constantly checks if the ball collides with the goal.
 *
 * @param b: The ball.
 * @param z: The zone.
 * @param goal_width: The width of the goal.
 *
 * @return bool: True if the ball collides with the goal, false otherwise.
 */
void score_goal(ball_t *b, zone_t *z, slider_t *player_one, slider_t *player_two, int goal_width, int &seconds_left, int game_size, int &total_time);

/*
 * @brief This function moves the ball in the game.
 *
 * @param b: The ball.
 *
 * @return void
 */
void moveBall(ball_t *b);

#endif
