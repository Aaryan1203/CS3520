#include "obstacle.hpp"
#include "ball.hpp" 
#include <ncurses.h>
#include <stdlib.h>

obstacle_t *init_obstacle(int upper_left_x, int upper_left_y, int width, int height, char draw_char) {
    obstacle_t *obstacle = (obstacle_t *)malloc(sizeof(obstacle_t));
    obstacle->upper_left_x = upper_left_x;
    obstacle->upper_left_y = upper_left_y;
    obstacle->width = width;
    obstacle->height = height;
    obstacle->draw_char = draw_char;
    return obstacle;
}

void draw_obstacle(obstacle_t *o) {
    for (int i = 0; i < o->height; ++i) {
        for (int j = 0; j < o->width; ++j) {
            attron(COLOR_PAIR(4));
            mvprintw(o->upper_left_y + i, o->upper_left_x + j, "%c", o->draw_char);
            attroff(COLOR_PAIR(4));
        }
    }
}

void undraw_obstacle(obstacle_t *o) {
    for (int i = 0; i < o->height; ++i) {
        for (int j = 0; j < o->width; ++j) {
            mvprintw(o->upper_left_y + i, o->upper_left_x + j, " ");
        }
    }
}
