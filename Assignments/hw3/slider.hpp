#ifndef SLIDER_H
#define SLIDER_H

// Properties of the slider
// Properties of the slider
typedef struct slider
{
  char type_str[7];
  char piece[1][7];
  int upper_left_x;
  int upper_left_y;
  char draw_char;
  char color[3];
  int size;
} slider_t;

slider_t *init_slider (int initial_x, int initial_y, char type, int size);
void draw_slider(slider_t *s);
void undraw_slider(slider_t *s);
void moveSlider(slider_t *s, int x, int y);
void check_borders(slider_t *top, slider_t *bottom, int zone_width, int zone_height, int center_line);

#endif