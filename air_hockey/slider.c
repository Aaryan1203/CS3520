#include<stdio.h>
#include <ncurses.h>
#include <time.h>
#include "slider.h"
#include <stdlib.h>
#include <string.h>
// This intializes the properties of the slider
const slider_t slider_types[2] = {
    {
        "top",
        {{1,1,1,1}}, 
        0,
        0,
        '%',
        {0,0,0}
    },
    {
        "bottom",
        {{1,1,1,1}}, 
        0,
        0,
        '+',
        {0,0,0}
    },
};

// Changes the location of the slider
void moveSlider(slider_t *s, int x, int y) {
    
    s->upper_left_x = x;
    s->upper_left_y = y;
}

// Intializes the slider
slider_t *init_slider (int initial_x, int initial_y, char type) {
  slider_t *s = malloc(sizeof(slider_t));
  if (type == 'T'){
      memcpy(s, &slider_types[0], sizeof(slider_t));
  }
  else
  {
      memcpy(s, &slider_types[1], sizeof(slider_t));
  }
  
  
  s->upper_left_x = initial_x;
  s->upper_left_y = initial_y;
  return(s);
}

// Renders the slider on the screen
void draw_slider(slider_t *s){
  int x,y;
  for (x=0;x<4;x++) {
    for (y=0;y<1;y++) {
      if (s->piece[y][x]) {
        mvprintw(s->upper_left_y+y,s->upper_left_x+x,"%c",s->draw_char);
      }
    }
  }

}

// Replaces the slider with blank spaces
void undraw_slider(slider_t *s){
  int x,y;
  for (x=0;x<4;x++) {
    for (y=0;y<1;y++) {
      if (s->piece[y][x]) {
        mvprintw(s->upper_left_y+y,s->upper_left_x+x," ",s->draw_char);
      }
    }
  }

}