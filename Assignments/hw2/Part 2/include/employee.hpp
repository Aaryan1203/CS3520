#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "./seat.hpp"

void employee_login(Seat[][6], int);
void show_employee_options(Seat[][6], int, string);
void print_manifest(string filename, bool = false);
void reorder_manifest(vector<Seat>);

#endif