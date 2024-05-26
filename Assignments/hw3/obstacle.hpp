#ifndef OBSTACLE_H
#define OBSTACLE_H

typedef struct obstacle
{
    int upper_left_x;
    int upper_left_y;
    int width;
    int height;
    char draw_char;
} obstacle_t;

obstacle_t *init_obstacle(int upper_left_x, int upper_left_y, int width, int height, char draw_char);
void draw_obstacle(obstacle_t *o);
void undraw_obstacle(obstacle_t *o);

#endif
