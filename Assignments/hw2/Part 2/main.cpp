#include <iostream>
#include <string>
#include <vector>
#include "./include/passenger.hpp"
#include "./include/employee.hpp"
#include "./include/seat.hpp"
#include "./include/shared.hpp"

using namespace std;

int main () {
    Seat all_seats[12][6];
    string letters = "ABDEFH";
    vector<Seat> seats_from_manifest = read_manifest("saved_manifest.txt");
 
    // populates the all_seats 2D array with its classes, seat numbers, and empty passengers
    for (int row = 0; row < 12; row++) {
        for (int col = 0; col < 6; col++) {
            Seat new_seat;
            new_seat.number = letters[col] + to_string(row + 1);
            new_seat.passenger = "";

            // checks if the seat has already been filled from the manifest and if so populates it
            for (Seat seat : seats_from_manifest) {
                if (seat.number == new_seat.number) {
                    new_seat.passenger = seat.passenger;
                    break;
                }
            }

            if (row == 0) {
                new_seat.level = "First Class";
            } else if (row >= 1 && row <= 3) {
                new_seat.level = "Business Class";
            } else {
                new_seat.level = "Economy Class";
            }
            all_seats[row][col] = new_seat;
        }
    }
    
    // prompts the user to login as an employee or a passenger
    int user_type;
    cout << "To log in, press 1 if you are a passenger or 2 if you are an employee." << endl;
    while (cin >> user_type) {
        if (cin.fail() || (user_type != 1 && user_type != 2)) {
            cin.clear();
            cout << "Please press 1 for a passenger or 2 for an employee" << endl;
        } else {
            break;
        }
    }

    // passes the user to the passenger or login screen
    switch (user_type) {
        case 1:
            show_passenger_options(all_seats, 12);
            break;
        case 2:
            employee_login(all_seats, 12);
            break;
    }
}