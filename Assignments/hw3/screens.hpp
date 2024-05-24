#ifndef SCREENS_H
#define SCREENS_H
#include <string>
#include "slider.hpp"
using namespace std;
struct ScreenInput
{
    int slider_size;
    int goal_width;
};

void welcome_screen();
ScreenInput input_screen();
int prompt_input(char message[], ScreenInput *input_struct, string input_type, int input_min, int input_max);
void pause_screen();
void game_over_screen(slider_t *player_one, slider_t *player_two, int seconds_left);

#endif
