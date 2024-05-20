#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "./include/employee.hpp"
#include "./include/seat.hpp"
#include "./include/shared.hpp"
using namespace std;

void employee_login(Seat all_seats[][6], int size) {
    string username, password;

    // prompts the user for their username and password and logs them in if its correct
    while (true) {
        cout << "Enter your username: ";
        cin >> username;
        cout << "\nEnter your password: ";
        cin >> password;
        if (username != "Aaryan" || password != "Aaryan") {
            cout << "Invalid passenger, please try again" << endl;
        } else {
            cout << "Login Successful! Welcome " << username << endl;
            show_employee_options(all_seats, size, username);
            break;
        }
    }
}

void show_employee_options(Seat all_seats[][6], int size, string username) {
    int employee_selection;
    bool running = true; // displays the employee options until the program is no longer running
    cout << "Here are your options:" << endl;

    while(running) {
        // displays the employee options
        cout << "1: Display seating map" << endl;
        cout << "2: Print passenger manifest" << endl;
        cout << "3: Load Previous “Seat Assignment and Passenger Manifest”" << endl;
        cout << "4: Save current “Seat Assignment and Passenger Manifest”" << endl;
        cout << "5: Re-assign or Cancel a seat assignment" << endl;
        cout << "6: Quit the program" << endl;

        // ensure the employee inputs a valid number
        while (true) {
            cin >> employee_selection;
            if (cin.fail() || employee_selection < 1 || employee_selection > 6) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            } else {
                break;
            }
        }
        cout << endl;

        // calls the function based on the employee input
        switch (employee_selection) {
            case 1:
                display_seating_map(all_seats, 12);
                break;
            case 2:
                print_manifest("working_manifest.txt", true);
                break;
            case 3:
                print_manifest("saved_manifest.txt");
                break;
            case 4:
                save_manifest(all_seats, 12, "saved_manifest.txt");
                cout << "The seat manifest has been saved!" << endl;
                break;
            case 5:
                change_or_cancel(all_seats, 12);
                break;
            case 6:
                running = false;
                cout << "Exiting the program. Thank you!" << endl;
                break;
        }

        // runs everytime another function is completed until the program is quit
        if (employee_selection != 6) {
            cout << "\nPress Enter to return to the main menu..." << endl;
            cin.get();
        }
    }
}

void print_manifest(string filename, bool reorder) {
    vector<Seat> seats_from_manifest = read_manifest(filename);

    // checks if the array is populated and if so prints the lines in the manifest
    if (seats_from_manifest.empty()) {
        cout << "There are no passengers on this flight! Please schedule some in order to see them in the manifest" << endl;
    } else {
        cout << "Here is the seat manifest:" << endl;
        for (Seat seat : seats_from_manifest) {
            cout << seat.passenger << ": " << seat.number << ", " << seat.level << endl;
        }
        cout << endl;

        // reorders the seats if the flag is passed as true
        if (reorder) {
            reorder_manifest(seats_from_manifest);
        }
    }
}

void reorder_manifest(vector<Seat> seats_from_manifest) {

    // prompts the user for its options to reorder the manifest
    int user_option;
    cout << "To reorder the manifest, press " << endl;
    cout << "1: to order by seat numbers ascending" << endl;
    cout << "2: to order by seat numbers descending" << endl;
    cout << "3: to order by name alphabetically ascending" << endl;
    cout << "4: to order by name alphabetically descending" << endl;
    cout << "5: to order by class" << endl;
    cout << "6: to go back to the main menu" << endl;
    
    // ensures the user enters a valid option
    while (true) {
        cout << "Please enter your choice (1-6): ";
        cin >> user_option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (user_option >= 1 && user_option <= 6) {
            break;
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    // sorts the seats based on the users preference
    switch (user_option) {
        case 1:
            break;
        case 2:
            reverse(seats_from_manifest.begin(), seats_from_manifest.end());
            break;
        case 3:
            sort(seats_from_manifest.begin(), seats_from_manifest.end(), [](Seat a, Seat b) {
                return a.passenger < b.passenger;
            });
            break;
        case 4:
            sort(seats_from_manifest.begin(), seats_from_manifest.end(), [](Seat a, Seat b) {
                return a.passenger > b.passenger;
            });
            break;
        case 5:
            break;
        case 6:
            return;
    }

    // prints the manifest for the reordered seats
    cout << "Reordered seat manifest:" << endl;
    for (Seat seat : seats_from_manifest) {
        cout << seat.passenger << ": " << seat.number << ", " << seat.level << endl;
    }
}