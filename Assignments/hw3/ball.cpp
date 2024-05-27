/* ball.cpp ---
 *
 * Filename: ball.cpp
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

#include <cstdlib>
#include <cstdbool>
#include <ncurses.h>
#include "obstacle.hpp"
#include "ball.hpp"
#include "zone.hpp"

void moveBall(ball_t *b)
{
    b->upper_left_x += b->speed_x;
    b->upper_left_y += b->speed_y;
}

void score_goal(ball_t *b, zone_t *z, slider_t *player_one, slider_t *player_two, int goal_width, int &seconds_left, int game_size, int &total_time)
{

    int start = z->upper_left_x + ((z->width - goal_width) / 2);
    int end = start + goal_width;

    // Draw the goal area
    attron(COLOR_PAIR(2)); // Turn on color pair 2 (yellow foreground)
    for (int i = start; i <= end; ++i) {
        mvprintw(z->upper_left_y, i, "#"); // Top goal
        mvprintw(z->upper_left_y + z->height, i, "#"); // Bottom goal
    }
    attroff(COLOR_PAIR(2)); // Turn off color pair 2

    // Check if the ball is above the highest y coordinate and in between the goal.
    if (b->upper_left_y <= z->upper_left_y && b->upper_left_x >= start && b->upper_left_x <= end)
    {
        (player_one->game_score)++;
        new_round(player_one, player_two, b, z, false, seconds_left, total_time);
    }
    // Check if the ball is below the lowest y coordinate and in between the goal.
    if (b->upper_left_y >= z->upper_left_y + z->height && b->upper_left_x >= start && b->upper_left_x <= end)
    {
        (player_two->game_score)++;
        new_round(player_one, player_two, b, z, false, seconds_left, total_time);
    }

    if (player_one->game_score + player_two->game_score == game_size)
    {
        // reset the game score after each game
        new_round(player_one, player_two, b, z, true, seconds_left, total_time);
    }
}

bool checkCollisionSlider(slider_t *s, ball_t *b, int slider_size)
{
    double next_x_ball = b->upper_left_x + b->speed_x;
    double next_y_ball = b->upper_left_y + b->speed_y;

    int x;
    for (x = 0; x < slider_size; x++)
    {
        // Check for collision with player two's slider (top slider)
        if (b->speed_y < 0 && s->player_number == 2)
        {
            if (s->upper_left_y >= next_y_ball - 1 &&
                s->upper_left_y <= b->upper_left_y &&
                s->upper_left_x + x >= next_x_ball - 0.5 && 
                s->upper_left_x + x <= next_x_ball + 0.5)
            {
                b->speed_y *= -1; 
                return true;
            }
        }
        // Check for collision with player one's slider (bottom slider)
        else if (b->speed_y > 0 && s->player_number == 1)
        {
            if (s->upper_left_y <= next_y_ball + 1 &&
                s->upper_left_y >= b->upper_left_y &&
                s->upper_left_x + x >= next_x_ball - 0.5 && 
                s->upper_left_x + x <= next_x_ball + 0.5)
            {
                b->speed_y *= -1;
                return true;
            }
        }
    }
    return false;
}

bool checkCollisionWithZone(ball_t *b, zone_t *z, int goal_width)
{
    double next_x_ball = b->upper_left_x + b->speed_x;
    double next_y_ball = b->upper_left_y + b->speed_y;

    int start = z->upper_left_x + (z->width - goal_width) / 2;
    int end = start + goal_width;

    // Check collision with left and right walls
    if (next_x_ball <= z->upper_left_x || next_x_ball >= z->upper_left_x + z->width)
    {
        b->speed_x *= -1;
        // Correct the position to ensure the ball doesn't go beyond the wall
        if (next_x_ball <= z->upper_left_x) {
            b->upper_left_x = z->upper_left_x + 1;
        } else {
            b->upper_left_x = z->upper_left_x + z->width - 1;
        }
        return true;
    }

    // Check collision with top and bottom walls excluding the goal area
    if ((next_y_ball <= z->upper_left_y && (next_x_ball < start || next_x_ball > end)) ||
        (next_y_ball >= z->upper_left_y + z->height && (next_x_ball < start || next_x_ball > end)))
    {
        b->speed_y *= -1;
        // Correct the position to ensure the ball doesn't go beyond the wall
        if (next_y_ball <= z->upper_left_y) {
            b->upper_left_y = z->upper_left_y + 1;
        } else {
            b->upper_left_y = z->upper_left_y + z->height - 1;
        }
        return true;
    }

    return false;
}

bool checkCollisionWithObstacle(ball_t *b, obstacle_t *o) {
    // checks for collisions with the obstacles
    if (b->upper_left_x >= o->upper_left_x && b->upper_left_x <= o->upper_left_x + o->width &&
            b->upper_left_y >= o->upper_left_y && b->upper_left_y <= o->upper_left_y + o->height) {
        b->speed_x *= -1;
        b->speed_y *= -1;
        return true;
    }
    return false;
}

ball_t *init_ball(int upper_left_x, int upper_left_y, zone_t *z)
{
    ball_t *b;
    b = (ball_t *)malloc(sizeof(ball_t));
    b->draw_char = 'O';
    b->upper_left_x = upper_left_x;
    b->upper_left_y = upper_left_y;
    b->color[0] = 0;
    b->color[1] = 0;
    b->color[2] = 0;
    b->speed_x = 1.0;
    b->speed_y = 1.0;

    return (b);
}

void draw_ball(ball_t *b)
{
    attron(COLOR_PAIR(1));
    mvprintw(b->upper_left_y, b->upper_left_x, "%c", b->draw_char);
    attroff(COLOR_PAIR(1));
}

void undraw_ball(ball_t *b)
{
    mvprintw(b->upper_left_y, b->upper_left_x, " ", b->draw_char);
}
