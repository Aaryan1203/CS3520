#ifndef PASSENGER_H
#define PASSENGER_H

#include "./seat.hpp"

void show_passenger_options(Seat[][6], int);
void choose_seat_random(Seat [][6], int);
void choose_seat_manual(Seat[][6], int, string = "", string = "");
void print_boarding_pass(Seat [][6], int);

#endif