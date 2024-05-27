#include <ncurses.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "screens.hpp"
#include "key.hpp"
#include "ball.hpp"
#include "air_hockey.hpp"
#include "zone.hpp"

void air_hockey(int slider_size, int goal_size, int game_size)
{
    int zone_height, zone_width;
    struct timespec tim = {0, 200000000};
    struct timespec tim_ret;
    int arrow, c;
    int slider_x_speed = 4, slider_y_speed = 4;
    initscr();
    start_color();
    use_default_colors();
    // Ball color
    init_pair(1, COLOR_CYAN, -1);
    // Goal color
    init_pair(2, COLOR_BLUE, -1);
    // Slider color
    init_pair(3, COLOR_YELLOW, -1);
    // Obstacle color
    init_pair(4, COLOR_RED, -1);
    // Score color
    init_pair(5, COLOR_WHITE, -1);

    getmaxyx(stdscr, zone_height, zone_width);
    zone_height -= 1;
    zone_width -= 1;
    int center_line = zone_height / 2;
    int seconds_left = 120;
    zone_t *z = init_zone(0, 0, zone_width, zone_height);
    ball_t *b = init_ball(zone_width / 2, zone_height / 2, z);
    // Bottom
    slider_t *player_one = init_slider(zone_width / 2, zone_height - 5, 'U', slider_size, 1);
    // Top
    slider_t *player_two = init_slider(zone_width / 2, 5, 'T', slider_size, 2);
    draw_zone(z);
    draw_slider(player_two);
    draw_slider(player_one);
    draw_ball(b);
    refresh();
    // Do not wait for characters using getch
    nodelay(stdscr, TRUE); 
    noecho();
    time_t start_time = time(NULL);
    time_t last_update_time = start_time;
    int total_time = 0;

    while (1)
    {
        if ((arrow = read_escape(&c)) != NOCHAR)
        {
            switch (arrow)
            {
            // Moving the bottom slider to the left
            case LEFT:
                undraw_slider(player_one);
                moveSlider(player_one, -slider_x_speed, 0);
                break;
            // Moving the bottom slider to the right
            case RIGHT:
                undraw_slider(player_one);
                moveSlider(player_one, slider_x_speed, 0);
                break;
            // Moving the bottom slider up
            case UP:
                undraw_slider(player_one);
                moveSlider(player_one, 0, -1);
                break;
            // Moving the bottom slider down
            case DOWN:
                undraw_slider(player_one);
                moveSlider(player_one, 0, 1);
                break;
            // Moving the top slider to the left
            case A:
                undraw_slider(player_two);
                moveSlider(player_two, -slider_x_speed, 0);
                break;
            // Moving the top slider to the right
            case D:
                undraw_slider(player_two);
                moveSlider(player_two, slider_x_speed, 0);
                break;
            // Moving the top slider up
            case W:
                undraw_slider(player_two);
                moveSlider(player_two, 0, -1);
                break;
            // Moving the top slider down
            case S:
                undraw_slider(player_two);
                moveSlider(player_two, 0, 1);
                break;
            // Pausing the game
            case P:
                pause_screen();
                break;
            // Quitting the game
            case Q:
                quit_screen();
                break;
            default:
                mvprintw(1, 5, "%c", c);
                break;
            }
        }
        show_time(start_time, last_update_time, seconds_left, b, z, player_one, player_two, total_time);
        check_borders(player_one, player_two, zone_width, zone_height, center_line);
        display_score(player_one, player_two, z);

        // Undraw before moving elements
        undraw_ball(b);
        undraw_zone(z);

        // Move and draw elements
        moveBall(b);
        draw_zone(z);
        draw_slider(player_one);
        draw_slider(player_two);
        draw_ball(b);

        // Check collisions
        checkCollisionWithZone(b, z, goal_size);
        score_goal(b, z, player_one, player_two, goal_size, seconds_left, game_size, total_time);

        // Check collisions with obstacles if in HARD mode
        for (int i = 0; i < z->num_obstacles; i++) {
            checkCollisionWithObstacle(b, &z->obstacles[i]); 
        }

        refresh();
        checkCollisionSlider(player_one, b, slider_size);
        checkCollisionSlider(player_two, b, slider_size);

        // usleep(200000);
        nanosleep(&tim, &tim_ret);
    }
}
