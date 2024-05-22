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
#include "include/air_hockey.hpp"
#include "include/welcome.hpp"

int main(){
    welcome_screen();
    air_hockey();
    return 0;
}
