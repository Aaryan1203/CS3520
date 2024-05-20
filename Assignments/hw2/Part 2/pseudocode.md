`main.cpp`

`main`
- initialize all the seats
- read the manifest from the working_manifest
- populate the 2d array with its classes, seat numbers, and passengers
- check if the seat has already been filled form the manifest and if so populate it
- prompts the user to login as an employee or a passenger
- passes the user to the passenger or login screen


`shared.cpp`

`display_seat_map(Seat all_seats[][6], int size)`
- print the aisel names
- loop through all the seats and determine if they are occupied
    - if so, print a 1 to indicate it is occupied, otherwise print a 0

`read_manifest(string filename)` 
- read the manifest file and populate the vector of all occupied seats
    - creates a seat object for each line read from the manifest and inputs it to the vector
    - return the populated vector

`change_or_cancel(Seat all_seats[][6], int size)`
- prompt the user for their name and seat
- alert the user if they did not give the correct username or seat number
- prompt the user if they want to change or cancel their seat
- ensure the user inputs a valid number
- gets passed to the change seat or cancel seat method depending on users choice
- saves the manifest

`handle_seat_change(Seat all_seats[][6], int size, Seat* current_seat)`
- prompt the user if they would like to upgrade or downgrade from their current class
- depending on their choice, will call the `choose_seat_manual` method with their prefered class
    - will unassign them from their current seat

`handle_seat_cancellation(Seat* current_seat)`
- cancel the users seat based on the inputted seat number

`save_manifest(Seat all_seats[][6], int size, string filename)`
- read the `all_seats` array and populates a vector to hold all of the occupied seats
- open the inputted file and print each seat from the vector onto it

`find_seat(Seat all_seats[][6], int size, const string& seat_number)`
- given a seat number, look through the all_seats array and return the address of the requested seat


`passenger.cpp`

`show_passenger_options(Seat all_seats[][6], int size)`
- show all the options the passenger has
- ensure they input a valid number
- depending on their selection, will call the method that corresponds to it
- method will keep running and ask the user to press enter to return to the main menu until they press 6

`choose_seat_random(Seat all_seats[][6], int size)`
 - add a random seed so the random numbers are actually random
 - find a random row and column and see if the seat at that row and column is empty
    - if so, ask the user to type their name to confirm their booking
    - save the passenger to the seat and save the manifest

`choose_seat_manual(Seat all_seats[][6], int size, string level, string username)`
- if a class is not passed in, prompt the user for a class they prefer
- populate an `available_seats` vector based on the specified class
- alert the user if there are no available seats
- print all the available seats
- prompt the user to pick one of the avaialble seats
- if it is a valid input, ask the user to input their name to confirm their booking
- assign the passenger to the seat and save the manifest

`print_boarding_pass(Seat all_seats[][6], int size)`
- ask the user for their seat number
- if the seat is a valid seat with a passenger, print the boarding pass
- else print an error message


`employee.cpp`

`employee_login(Seat all_seats[][6], int size)`
- ask the user for their username and password
- if they match the expected, log the user in and show them their options

`show_employee_options(Seat all_seats[][6], int size, string username)`
- show the user their options
- ensure their input is valid
- if so, pass the user on to the method that relates to their option
- method will keep running and ask the user to press enter to return to the main menu until they press 6

`print_manifest(string filename, bool reorder)`
- read the manifest 
- if the manifest is not empty, print all the seats out in the same order as it is in the manifest
- else print an error message
- if the reorder flag is passed in, call the `reorder_manifest` function

`reorder_manifest(vector<Seat> seats_from_manifest)`
- prompt the user for its options to reorder the manifest
- ensure the user enters a valid option
- sorts the seat based on the users preference
- print the reordered manifest
