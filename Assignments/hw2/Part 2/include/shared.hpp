#ifndef SHARED_H
#define SHARED_H

#include "./seat.hpp"

void display_seating_map(Seat[][6], int);
vector<Seat> read_manifest(string filename);
void change_or_cancel(Seat [][6], int);
void handle_seat_change(Seat[][6], int, Seat*);
void handle_seat_cancellation(Seat*);
void save_manifest(Seat[][6], int, string);
Seat* find_seat(Seat[][6], int, const string&);

#endif