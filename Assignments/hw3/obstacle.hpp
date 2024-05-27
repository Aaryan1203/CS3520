#ifndef OBSTACLE_H
#define OBSTACLE_H

/*
 * @struct obstacle
 * @brief This structure holds the obstacle properties.
 */
typedef struct obstacle {
    int upper_left_x; /**< The x-coordinate of the upper left corner of the obstacle */
    int upper_left_y; /**< The y-coordinate of the upper left corner of the obstacle */
    int width;        /**< The width of the obstacle */
    int height;       /**< The height of the obstacle */
    char draw_char;   /**< The character used to draw the obstacle */
} obstacle_t;

/*
 * @brief This function initializes the obstacle.
 *
 * @param upper_left_x: The x-coordinate of the upper left corner of the obstacle.
 * @param upper_left_y: The y-coordinate of the upper left corner of the obstacle.
 * @param width: The width of the obstacle.
 * @param height: The height of the obstacle.
 * @param draw_char: The character to draw the obstacle with.
 *
 * @return obstacle_t*: The obstacle.
 */
obstacle_t *init_obstacle(int upper_left_x, int upper_left_y, int width, int height, char draw_char);

/*
 * @brief This function draws the obstacle onto the screen.
 *
 * @param o: The obstacle to draw.
 *
 * @return void
 */
void draw_obstacle(obstacle_t *o);

/*
 * @brief This function undraws the obstacle from the screen.
 *
 * @param o: The obstacle to undraw.
 *
 * @return void
 */
void undraw_obstacle(obstacle_t *o);

#endif 
