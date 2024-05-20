#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>
#include "./include/seat.hpp"
#include "./include/passenger.hpp"
#include "./include/employee.hpp"
#include "./include/shared.hpp"

using namespace std;

void display_seating_map(Seat all_seats[][6], int size) {
    cout << "Seating map" << endl;
    cout << "0 - Unoccupied" << endl;
    cout << "1 - Occupied" << endl;

    // prints the aisle
    cout << setw(23) << "Aisle" << setw(35) << "Aisle" << endl;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < 6; col++) {
            // determines if the seat is occupied or not
            bool occupied = !all_seats[row][col].passenger.empty();
            ostringstream seat_info;
            seat_info << all_seats[row][col].number << " - " << (occupied ? 1 : 0);

            // prints the seat info
            cout << setw(10) << left << seat_info.str();
            if (col == 1 || col == 4) {
                cout << setw(5) << " ";
            }
        }
        cout << endl;
    }
}

vector<Seat> read_manifest(string filename) {
    vector<Seat> seats_from_manifest;

    // reads the manifest file and populates the seats from manifest vector
    ifstream input_file(filename);
    if (input_file.is_open()) {
        string line;
        while (getline(input_file, line)) {
            stringstream ss(line);
            string passenger, number, level;

            getline(ss, number, ':');
            ss.ignore(1, ' ');
            getline(ss, passenger, ',');
            ss.ignore(1, ' ');
            getline(ss, level);

            Seat seat = {passenger, number, level};
            seats_from_manifest.push_back(seat);
        }
        input_file.close();
    } else {
        cerr << "Unable to open file" << endl;
    }

    return seats_from_manifest;
}

void change_or_cancel(Seat all_seats[][6], int size) {
    // prompts the user for their name and seat
    string seat_number, user_name;
    cout << "In order to change or cancel your seat, we need to first find the seat!" << endl;
    cout << "What is the Seat Number: ";
    cin >> seat_number;
    cin.ignore();
    cout << "What is the User name: ";
    getline(cin, user_name);

    Seat* current_seat = find_seat(all_seats, 12, seat_number);

    // alerts the user if they did not give the correct username or seat number
    if (current_seat == nullptr || current_seat->passenger != user_name) {
        cout << "We were not able to find the seat. Make sure you have the right seat number and username and try again" << endl;
        cout << "Or return to the main menu and press 3 to choose a seat" << endl;
        return;
    } 
    
    // ensures the user's seat and username are valid
    if (current_seat->passenger == user_name) {
        cout << "We have found the seat for " << user_name << " what would you like to do now?" << endl;
    }

    // prompts the user about their choice
    cout << "Press 1 to change the seat or press 2 to cancel the seat assignment" << endl;
    int user_change_or_cancel;

    // ensures the user inputs a valid number
    while (true) {
        cin >> user_change_or_cancel;
        if (cin.fail() || user_change_or_cancel != 1 && user_change_or_cancel != 2) {
            cin.clear();
            cin.ignore();
            cout << "Invalid input. Please enter 1 or 2." << endl;
        } else {
            break;
        }
    }

    // handles seat operation based on the users input
    if (user_change_or_cancel == 1) {
        handle_seat_change(all_seats, size, current_seat);
    } else if (user_change_or_cancel == 2) {
        handle_seat_cancellation(current_seat);
    }
    
    // saves the manifest
    save_manifest(all_seats, 12, "working_manifest.txt");
}

void handle_seat_change(Seat all_seats[][6], int size, Seat* current_seat) {
    cout << "The class of the seat is currently: " << current_seat->level << endl;
    char user_level;
    
    // flag to check if input is valid
    bool valid_input = false; 

    // prompting the user if they would like to upgrade or downgrade from their current class
    while (!valid_input) {
        if (current_seat->level == "First Class") {
            cout << "If you would like to downgrade to business press 'b' or economy press 'e' or if you want to quit press 'q'" << endl;
            cin >> user_level;
        } else if (current_seat->level == "Business Class") {
            cout << "If you would like to upgrade to first class press 'f' or downgrade to economy press 'e' or if you want to quit press 'q'" << endl;
            cin >> user_level;
        } else if (current_seat->level == "Economy Class") {
            cout << "If you would like to upgrade to first class press 'f' or upgrade to business press 'b' or if you want to quit press 'q'" << endl;
            cin >> user_level;
        }

        // calls the choose manual function depending on their class preference or quits the function
        // cancels the users seat if they succesfully change seats
        switch (user_level) {
            case 'q':
                return;
            case 'f':
                choose_seat_manual(all_seats, 12, "f", current_seat->passenger);
                cout << "Your seat at " << current_seat->number << " has been cancelled!" << endl;
                current_seat->passenger = "";
                valid_input = true;
                break;
            case 'b':
                choose_seat_manual(all_seats, 12, "b", current_seat->passenger);
                cout << "Your seat at " << current_seat->number << " has been cancelled!" << endl;
                current_seat->passenger = "";
                valid_input = true;
                break;
            case 'e':
                choose_seat_manual(all_seats, 12, "e", current_seat->passenger);
                cout << "Your seat at " << current_seat->number << " has been cancelled!" << endl;
                current_seat->passenger = "";
                valid_input = true;
                break;
            default:
                cout << "Please enter a valid input" << endl;
                break;
        }
    }
}

void handle_seat_cancellation(Seat* current_seat) {
    // cancels the users seat
    cout << "Cancelling your seat at " << current_seat->number << endl;
    current_seat->passenger = "";
}

void save_manifest(Seat all_seats[][6], int size, string filename) {
    // populates the occupied_seats vector with all the seats that have passengers
    vector<Seat> occupied_seats;
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < 6; col++) {
            if (!all_seats[row][col].passenger.empty()) {
                occupied_seats.push_back(all_seats[row][col]);
            }
        }
    }

    // outputs the all the passengers information into a txt file called manifest.txt
    ofstream output_file(filename);
    if (output_file.is_open()) {
        for (Seat seat : occupied_seats) {
            output_file << seat.passenger << ": " << seat.number << ", " << seat.level << endl;
        }
        output_file.close();
    } else {
        cerr << "Unable to open file";
    }
}

// returns a seat in the airplane with the given seat number
Seat* find_seat(Seat all_seats[][6], int size, const string& seat_number) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < 6; col++) {
            if (all_seats[row][col].number == seat_number) {
                return &all_seats[row][col];
            }
        }
    }
    return nullptr;
}