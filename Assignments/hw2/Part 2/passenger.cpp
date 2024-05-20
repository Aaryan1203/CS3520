#include <string>
#include <iostream>
#include <vector>
#include "./include/passenger.hpp"
#include "./include/seat.hpp"
#include "./include/shared.hpp"
using namespace std;

void show_passenger_options(Seat all_seats[][6], int size) {
    int passenger_selection;
    bool running = true; // displays the passenger options until the program is no longer running
    cout << "Welcome Passanger, here are your options:" << endl;
    while(running) {
        // displays passenger options
        cout << "1: Display seating map" << endl;
        cout << "2: Random seat selection" << endl;
        cout << "3: Manual seat selection" << endl;
        cout << "4: Change or Cancel seat assignment" << endl;
        cout << "5: Print borading pass" << endl;
        cout << "6: Quit the program" << endl;

        // ensure the passenger inputs a valid number
        while (true) {
            cin >> passenger_selection;
            if (cin.fail() || passenger_selection < 1 || passenger_selection > 6) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            } else {
                break;
            }
        }

        // calls the function based on the passenger input
        switch (passenger_selection) {
            case 1:
                display_seating_map(all_seats, 12);
                break;
            case 2:
                choose_seat_random(all_seats, 12);
                break;
            case 3:
                choose_seat_manual(all_seats, 12);
                break;
            case 4:
                change_or_cancel(all_seats, 12);
                break;
            case 5:
                print_boarding_pass(all_seats, 12);
                break;
            case 6:
                // save_manifest(all_seats, 12, "saved_manifest.txt");
                running = false;
                cout << "Exiting the program. Thank you!" << endl;
                break;
        }

        // runs everytime another function is completed until the program is quit
        if (passenger_selection != 6) {
            cout << "\nPress Enter to return to the main menu..." << endl;
            cin.get();
        }
    }
}

void choose_seat_random(Seat all_seats[][6], int size) {
    // random seed
    srand(time(0)); 

    // flag to keep this running until an empty seat has been found
    bool seat_found = false;
    for (int i = 0; i < 72; i++) {
        int row = rand() % 12;
        int col = rand() % 6;

        // finding the random seat and assigning the user to it
        if (all_seats[row][col].passenger.empty()) {
            cout << "Congrats, we found seat for you: " << all_seats[row][col].number << endl;
            cout << "Please type your name to confirm the booking or press 'q' to go back to the options screen: ";

            string user_name;
            cin.ignore();
            getline(cin, user_name);

            // returning to main menu if user types q
            if (user_name == "q") {
                return;
            } else {
                // assigns the user to the seat
                cout << "Congrats " << user_name << ", your seat is booked at " << all_seats[row][col].number << endl;
                all_seats[row][col].passenger = user_name;
                save_manifest(all_seats, 12, "working_manifest.txt");
                return;
            }
            break;
        }
    }

    // alerts the user if there is no available seat 
    if (!seat_found) {
        cout << "No available seat, the next flight leaves in 3 hours!" << endl;
    }
}

void choose_seat_manual(Seat all_seats[][6], int size, string level, string username) {
    // only prompts for a class if the level is empty
    if (level == "") {
        cout << "You can now pick a seat manually, here is a map of all seats" << endl;
        display_seating_map(all_seats, 12);
        cout << "Please type 'f' for a seat in First Class (Row 1)" << endl;
        cout << "Please type 'b' for a seat in Business Class (Row 2 - 4)" << endl;
        cout << "Please type anything else for a seat in Economy (Row 5 - 12)" << endl;

        cin >> level;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
    }

    // all the available seats for a specific plane class
    vector<string> available_seats;

    // used to determine the row of the specific class
    int start_row, end_row;
    if (level == "f") {
        start_row = 0; end_row = 1;
    } else if (level == "b") {
        start_row = 1; end_row = 4;
    } else {
        start_row = 4; end_row = size;
    }

    // populates the available_seats vector
    for (int row = start_row; row < end_row; row++) {
        for (int col = 0; col < 6; col++) {
            if (all_seats[row][col].passenger.empty()) {
                available_seats.push_back(all_seats[row][col].number);
            }
        }
    }

    // alerts the user if there are no available seats
    if (available_seats.empty()) {
        cout << "No available seats in the selected class." << endl;
        return;
    }

    // flag to keep this running until the user types a valid input
    bool seat_picked = false;
    while (!seat_picked) {

        // prints all the available seats
        for (int i = 1; i <= available_seats.size(); i++) {
            cout << available_seats[i - 1] << " ";
            if (i % 9 == 0) {
                cout << endl;
            }
        }
        cout << endl;
        cout << "Above are all the available seats. Please pick one: ";

        // chooses a seat for a user
        string seat_number;
        while (cin >> seat_number) {
            if (find(available_seats.begin(), available_seats.end(), seat_number) != available_seats.end()) {
                Seat* current_seat = find_seat(all_seats, 12, seat_number);
                if (current_seat != nullptr) {
                            // only asking for username if one is not provided already
                            if (username.empty()) {
                                cout << "Great, now just enter your username and your seat will be booked: ";
                                cin.ignore();
                                getline(cin, username);
                            }
                            // assigns a passenger to the seat
                            current_seat->passenger = username;
                            save_manifest(all_seats, 12, "working_manifest.txt");
                            cout << "Congrats " << username << " your seat is booked at " << seat_number << endl;
                            seat_picked = true;
                            return;
                }
            } else {
                cout << "Please pick a valid seat!" << endl;
                break;
            }
        }
    }
}

void print_boarding_pass(Seat all_seats[][6], int size) {
    cout << "You can now print your boarding pass" << endl;

    // prompts the user for their seat number
    cout << "What is your seat number: "; 
    string seat_number;
    cin >> seat_number;

    // finds the current seat and prints the boarding pass if it is a valid seat and has a passenger
    Seat* current_seat = find_seat(all_seats, 12, seat_number);
    if (current_seat != nullptr && !current_seat->passenger.empty()) {
        cout << "Boarding Pass: " << current_seat->passenger << ", Seat: " << current_seat->number << ", Level: " << current_seat->level << endl;
    } else {
        cout << "Seat Unassigned - No Boarding pass available. Try Again!”" << endl;
        return;
    }
}