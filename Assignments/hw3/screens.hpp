#ifndef SCREENS_H
#define SCREENS_H
#include <string>
#include "slider.hpp"
using namespace std;

/*
 * @struct ScreenInput
 * @brief This structure holds the input screen properties.
 */
struct ScreenInput
{
    int slider_size; /**< The size of the slider */
    int goal_width;  /**< The width of the goal */
    int game_size;   /**< The size of the game */
};

/*
 * @brief This function displays the welcome screen.
 *
 * @return void
 */
void welcome_screen();

/*
 * @brief This function displays the input screen and prompts the user for inputs to determne the game settings.
 *
 * @return ScreenInput: The input screen.
 */
ScreenInput input_screen();

/*
 * @brief This function displays the input question and provides restrictions to the response.
 *
 * @param message: The message to display.
 * @param input_struct: The input struct to store the input.
 * @param input_type: The type of input.
 * @param input_min: The minimum input.
 * @param input_max: The maximum input.
 *
 * @return int: The valid input.
 */
int prompt_input(char message[], ScreenInput *input_struct, string input_type, int input_min, int input_max);

/*
 * @brief This function displays the pause screen.
 *
 * @return void
 */
void pause_screen();

/*
 * @brief This function displays the quit screen.
 *
 * @return void
 */
void quit_screen();

/*
 * @brief This function displays the game over screen.
 *
 * @param player_one: The first player (the top slider).
 * @param player_two: The second player (the bottom slider).
 * @param total_time: The total time of the game.
 *
 * @return void
 */
void game_over_screen(slider_t *player_one, slider_t *player_two, int total_time);

#endif
