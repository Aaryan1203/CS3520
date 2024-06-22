#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "include/user.hpp"
#include "include/facility_manager.hpp"

using namespace std;

int main()
{
    vector<User> users;               // this would loaded from a file
    vector<FacilityManager> managers; // this would be loaded from a file
    Facility facility;

    while (true)
    {
        cout << "Welcome to the Community Center Management System! Please login to continue.\n";
        cout << "Are you a user or a facility manager? \n";
        cout << "1. User \n";
        cout << "2. Facility Manager \n";
        cout << "3. Quit \n";

        int choice;
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 3)
        {
            cout << "Invalid input. Please try again. \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            {
                string username, password;
                cout << "Please enter your username: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, username);
                if (cin.fail() || username.empty())
                {
                    cout << "Invalid input. Please try again. \n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                cout << "Please enter your password: ";
                getline(cin, password);
                if (cin.fail() || password.empty())
                {
                    cout << "Invalid input. Please try again. \n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                User user(username, password, 0, "Unknown");
                if (validate_user_credentials(username, password, user))
                {
                    user_menu(user, facility);
                }
                else
                {
                    cout << "Login credentials are incorrect. Please try again. \n";
                }
                break;
            }
            cout << "user" << endl;
        case 2:
        {
            string username, password;
            cout << "Please enter your username: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, username);
            if (cin.fail() || username.empty())
            {
                cout << "Invalid input. Please try again. \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << "Please enter your password: ";
            getline(cin, password);
            if (cin.fail() || password.empty())
            {
                cout << "Invalid input. Please try again. \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            FacilityManager manager(username, password);
            if (validate_facility_manager_credentials(username, password, manager))
            {
                facility_manager_menu(manager);
            }
            else
            {
                cout << "Login credentials are incorrect. Please try again. \n";
            }
            break;
        }
        case 3:
        {
            cout << "Goodbye! \n";
            return 0;
        }
        default:
        {
            cout << "Invalid choice. Try again.\n";
            break;
        }
        }
    }

    return 0;
}