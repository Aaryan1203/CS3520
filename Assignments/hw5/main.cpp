#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include "include/cell.hpp"
#include "include/critter.hpp"
#include "include/grid.hpp"
#include "include/simulation.hpp"

using namespace std;

// Function to print a prompt and get an integer input from the user
int print_prompt(const string &prompt, int default_value)
{
    cout << prompt;
    string input;
    getline(cin, input);
    if (input.empty())
    {
        return default_value;
    }
    stringstream ss(input);
    int value;
    ss >> value;
    if (ss.fail() || value < 0)
    {
        cout << "Invalid input. Using default value of " << default_value << "." << endl;
        return default_value;
    }
    return value;
}

int main()
{
    // Seed the random number generator
    srand(time(0));

    // Prompt the user with the defaul values
    cout << "Welcome to the Critter Simulation" << endl;
    cout << "You will be asked to enter the number of doodlebugs, ants, and queens you would like to start with, as well as the size of the grid." << endl;
    cout << "If you do not enter a value, the default value will be used." << endl;
    int num_doodlebugs = print_prompt("Number of doodlebugs. Default 15: ", 15);
    int num_ants = print_prompt("Number of ants. Default 50: ", 50);
    int num_queens = print_prompt("Number of queens. Default 2: ", 2);
    int width = print_prompt("Number of rows. Default 50: ", 50);
    int height = print_prompt("Number of columns. Default 50: ", 50);

    // error checking
    if (num_doodlebugs < 1)
    {
        cout << "The number of doodlebugs must be at least 1." << endl;
        return 1;
    }
    if (num_ants < 1)
    {
        cout << "The number of ants must be at least 1." << endl;
        return 1;
    }
    if (num_queens < 1)
    {
        cout << "The number of queens must be at least 1." << endl;
        return 1;
    }

    if (num_doodlebugs + num_ants + num_queens > width * height)
    {
        cout << "The total number of doodlebugs, ants, and queens must be less than or equal to the number of cells in the grid." << endl;
        return 1;
    }

    if (width < 10 || height < 10)
    {
        cout << "The grid size is too small. Please use a larger grid." << endl;
        return 1;
    }
    Simulation simulation(width, height, num_doodlebugs, num_ants, num_queens);
    simulation.run();

    return 0;
}
