#ifndef ZONE_H
#define ZONE_H

#include <ctime>
#include "ball.hpp"
#include "slider.hpp"
#include "obstacle.hpp"

typedef struct ball ball_t;
typedef struct obstacle obstacle_t;

/*
 * @enum DIFFICULTY
 * @brief This enum represents the difficulty of the zone.
 */
enum DIFFICULTY
{
    EASY,   /**< Easy difficulty level */
    MEDIUM, /**< Medium difficulty level */
    HARD    /**< Hard difficulty level */
};

/**
 * @struct zone
 * @brief This structure holds the properties of the zone such as position and dimensions.
 */
typedef struct zone
{
    int upper_left_x;      /**< The x-coordinate of the upper left corner of the zone */
    int upper_left_y;      /**< The y-coordinate of the upper left corner of the zone */
    int width;             /**< The width of the zone */
    int height;            /**< The height of the zone */
    char draw_char;        /**< The character used to draw the zone */
    char color[3];         /**< The color of the zone */
    DIFFICULTY difficulty; /**< The difficulty level of the zone */
    obstacle_t *obstacles; /**< Pointer to the array of obstacles in the zone */
    int num_obstacles;     /**< The number of obstacles in the zone */
} zone_t;

/*
 * @brief This function undraws the zone from the screen.
 *
 * @param z: The zone to undraw.
 *
 * @return void
 */
void undraw_zone(zone_t *z);

/*
 * @brief This function draws the zone onto the screen.
 *
 * @param z: The zone to draw.
 *
 * @return void
 */
void draw_zone(zone_t *z);

/*
 * @brief This function initializes the zone.
 *
 * @param upper_left_x: The x-coordinate of the upper left corner of the zone.
 * @param upper_left_y: The y-coordinate of the upper left corner of the zone.
 * @param width: The width of the zone.
 * @param height: The height of the zone.
 *
 * @return zone_t*: The zone.
 */
zone_t *init_zone(int upper_left_x, int upper_left_y, int width, int height);

/*
 * @brief This function checks if the ball collides with the zone.
 *
 * @param b: The ball.
 * @param z: The zone.
 * @param goal_width: The width of the goal.
 *
 * @return bool: True if the ball collides with the zone, false otherwise.
 */
void new_round(slider_t *player_one, slider_t *player_two, ball_t *b, zone_t *z, bool next_level, int &seconds_left, int &total_time);

/*
 * @brief This function checks if the ball collides with the zone.
 *
 * @param b: The ball.
 * @param z: The zone.
 * @param goal_width: The width of the goal.
 *
 * @return bool: True if the ball collides with the zone, false otherwise.
 */
void show_time(time_t start_time, time_t &last_update_time, int &seconds_left, ball_t *b, zone_t *z, slider_t *player_one, slider_t *player_two, int &total_time);

/*
 * @brief This function checks if the ball collides with the zone.
 *
 * @param b: The ball.
 * @param z: The zone.
 * @param goal_width: The width of the goal.
 *
 * @return bool: True if the ball collides with the zone, false otherwise.
 */
void display_score(slider_t *player_one, slider_t *player_two, zone_t *z);

/*
 * @brief This function checks if the ball collides with the zone.
 *
 * @param b: The ball.
 * @param z: The zone.
 * @param goal_width: The width of the goal.
 *
 * @return bool: True if the ball collides with the zone, false otherwise.
 */
void init_obstacles(zone_t *z);

/*
 * @brief This function checks if the ball collides with the zone.
 *
 * @param b: The ball.
 * @param z: The zone.
 * @param goal_width: The width of the goal.
 *
 * @return bool: True if the ball collides with the zone, false otherwise.
 */
void clear_obstacles(zone_t *z);

#endif
