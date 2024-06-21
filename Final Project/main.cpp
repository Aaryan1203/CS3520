#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "include/user.hpp"
#include "include/facility_manager.hpp"
#include "facility_manager.hpp"

using namespace std;

// TODO: functions to define properly
void user_menu(User &user);
void manager_menu(FacilityManager &manager);
bool validate_user_credentials(const string &username, const string &password, User &user);
bool validate_manager_credentials(const string &username, const string &password, FacilityManager &manager);

int main()
{
    vector<User> users;               // this would loaded from a file
    vector<FacilityManager> managers; // this would be loaded from a file

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
                user_menu(user);
            }
            else
            {
                cout << "Login credentials are incorrect. Please try again. \n";
            }
            break;
        }
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
            if (validate_manager_credentials(username, password, manager))
            {
                manager_menu(manager);
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

void user_menu(User &user)
{
    while (true)
    {
        // there is no username getter yet
        cout << "Welcome " << user.get_username() << "!\n";
        cout << "1. View Reservations\n";
        cout << "2. Make Reservation\n";
        cout << "3. Cancel Reservation\n";
        cout << "4. Buy Ticket\n";
        cout << "5. Create Event\n";
        cout << "6. Cancel Event\n";
        cout << "7. Logout\n";

        int choice;
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 7)
        {
            cout << "Invalid input. Please try again. \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            user.view_reservations();
            break;
        case 2:
        {
            // TODO
            break;
        }
        case 3:
        {
            // TODO
            break;
        }
        case 4:
        {
            // TODO
            break;
        }
        case 5:
        {
            // TODO
            break;
        }
        case 6:
        {
            // TODO
            break;
        }
        case 7:
            return;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    }
}

void manager_menu(FacilityManager &manager)
{
    while (true)
    {
        // there is no username getter yet
        cout << "Welcome Manager " << manager.get_username() << "!\n";
        cout << "1. View Reservation Requests\n";
        cout << "2. View Budget\n";
        cout << "3. Refund Event\n";
        cout << "4. View Events\n";
        cout << "5. Logout\n";

        int choice;
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 5)
        {
            cout << "Invalid input. Please try again. \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            // TODO:
            break;
        case 2:
            manager.view_budget();
            break;
        case 3:
        {
            // TODO:
            break;
        }
        case 4:
        {
            // TODO:
            break;
        }
        case 5:
            return;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    }
}

bool validate_user_credentials(const string &username, const string &password, User &user)
{
    // TODO
    return true;
}

bool validate_manager_credentials(const string &username, const string &password, FacilityManager &manager)
{
    // TODO
    return true;
}