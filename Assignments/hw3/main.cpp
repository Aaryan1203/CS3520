/* main.cpp ---
 *
 * Filename: main.cpp
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
#include <stdio.h>
#include <ctime>
#include <ncurses.h>
#include "air_hockey.hpp"
#include "screens.hpp"

int main()
{
    int size = select_slider_size_screen();
    welcome_screen();
    air_hockey(size);
    return 0;
}