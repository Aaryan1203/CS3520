#ifndef SLIDER_H
#define SLIDER_H

/*
 * @struct slider
 * @brief This structure holds the slider properties.
 */
typedef struct slider
{
  char type_str[7];  /**< The type of the slider */
  char piece[1][7];  /**< The piece of the slider */
  int upper_left_x;  /**< The x-coordinate of the upper left corner of the slider */
  int upper_left_y;  /**< The y-coordinate of the upper left corner of the slider */
  char draw_char;    /**< The character used to draw the slider */
  char color[3];     /**< The color of the slider */
  int size;          /**< The size of the slider */
  int series_score;  /**< The series score */
  int game_score;    /**< The game score */
  int total_score;   /**< The total score */
  int player_number; /**< The player number */
} slider_t;

/*
 * @brief This function initializes the slider.
 *
 * @param initial_x: The x-coordinate of the upper left corner of the slider.
 * @param initial_y: The y-coordinate of the upper left corner of the slider.
 * @param type: The type of the slider.
 * @param size: The size of the slider.
 * @param player_number: The player number.
 */
slider_t *init_slider(int initial_x, int initial_y, char type, int size, int player_number);

/*
 * @brief This function draws the slider onto the screen.
 *
 * @param s: The slider to draw.
 *
 * @return void
 */
void draw_slider(slider_t *s);

/*
 * @brief This function undraws the slider from the screen.
 *
 * @param s: The slider to undraw.
 *
 * @return void
 */
void undraw_slider(slider_t *s);

/*
 * @brief This function moves the slider.
 *
 * @param s: The slider to move (player one or player two).
 * @param x: The x-coordinate to move the slider to.
 * @param y: The y-coordinate to move the slider to.
 *
 * @return void
 */
void moveSlider(slider_t *s, int x, int y);

/*
 * @brief This function checks if the slider collides with the zone.
 *
 * @param s: The slider.
 * @param zone_width: The width of the zone.
 * @param zone_height: The height of the zone.
 * @param center_line: The center line of the zone.
 *
 * @return void
 */
void check_borders(slider_t *player_one, slider_t *player_two, int zone_width, int zone_height, int center_line);

#endif
