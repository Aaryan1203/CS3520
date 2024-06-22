#include "include/user.hpp"
#include "include/facility.hpp"
#include "include/event.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

User::User(const string &username, const string &password, int balance, const string &city)
    : username(username), password(password), balance(balance), city(city)
{
}

string User::get_username() const
{
    return username;
}

int User::get_balance() const
{
    return balance;
}

void User::set_balance(int balance)
{
    this->balance = balance;
}

void User::view_my_information()
{
    cout << "Username: " << username << endl;
    cout << "Balance: " << balance << endl;
    cout << "City: " << city << endl;
}

void User::cancel_reservation(Event &event)
{
    auto it = find(reservations.begin(), reservations.end(), event);
    if (it != reservations.end())
    {
        event.refund_users();
        reservations.erase(it);
        cout << "Reservation cancelled for " << event.get_name() << endl;
    }
    else
    {
        cout << "Reservation not found for " << event.get_name() << endl;
        return;
    }
}

void User::view_events()
{
    for (const auto &event : reservations)
    {
        cout << event << endl;
    }
}

void User::view_my_reservations()
{
    for (const auto &event : reservations)
    {
        cout << event << endl;
    }
}

Event User::create_event(Facility &facility)
{

    string event_name;
    time_t event_date;
    time_t start_time;
    time_t end_time;
    bool is_public;
    int num_guests;
    string organizer_username;
    LayoutType layout;
    int price_of_event;
    int ticket_price;
    OrganizerType organizer_type;
    bool open_to_residents;
    bool open_to_non_residents;

    // Prompt the user for each field
    cout << "Enter the event name: ";
    cin.ignore();
    getline(cin, event_name);

    cout << "Enter the event date (epoch time): ";
    cin >> event_date;

    cout << "Enter the start time (epoch time): ";
    cin >> start_time;

    cout << "Enter the end time (epoch time): ";
    cin >> end_time;

    string is_public_str;
    cout << "Enter is the event public? (1 for Yes, 0 for No): ";
    cin >> is_public_str;
    is_public = is_public_str == "1" ? true : false;

    cout << "Enter the number of guests: ";
    cin >> num_guests;

    cout << "Enter the organizer's username: ";
    cin.ignore();
    getline(cin, organizer_username);

    User *organizer = this;

    cout << "Enter the layout type (integer value):" << endl;
    cout << "0: MEETING_STYLE" << endl;
    cout << "1: LECTURE_STYLE" << endl;
    cout << "2: WEDDING_STYLE" << endl;
    cout << "3: DANCE_ROOM_STYLE" << endl;
    int layout_int;
    cin >> layout_int;
    if (layout_int < 0 || layout_int > 3)
    {
        cout << "Invalid layout type. Defaulting to MEETING_STYLE.\n";
        layout = LayoutType::MEETING_STYLE;
    }
    else
    {
        layout = static_cast<LayoutType>(layout_int);
    }

    cout << "Enter the price of event: ";
    cin >> price_of_event;

    cout << "Enter the ticket price: ";
    cin >> ticket_price;

    cout << "Enter the organizer type (integer value):" << endl;
    cout << "0: CITY" << endl;
    cout << "1: ORGANIZATION" << endl;
    cout << "2: RESIDENT" << endl;
    cout << "3: NON_RESIDENT" << endl;
    int organizer_type_int;
    cin >> organizer_type_int;
    if (organizer_type_int < 0 || organizer_type_int > 3)
    {
        cout << "Invalid organizer type. Defaulting to CITY.\n";
        organizer_type = OrganizerType::CITY;
    }
    else
    {
        organizer_type = static_cast<OrganizerType>(organizer_type_int);
    }

    cout << "Is the event open to residents? (1 for Yes, 0 for No): ";
    cin >> open_to_residents;

    cout << "Is the event open to non-residents? (1 for Yes, 0 for No): ";
    cin >> open_to_non_residents;

    // Create the Event object
    Event new_event(event_name, event_date, start_time, end_time, is_public, num_guests, organizer, layout, price_of_event, ticket_price, organizer_type, open_to_residents, open_to_non_residents, facility);

    return new_event;
}

void user_menu(User &user, Facility &facility)
{
    while (true)
    {
        cout << "Welcome User " << user.get_username() << "!\n";
        cout << "1. My Upcoming Events\n";
        cout << "2. My Created Reservations\n";
        cout << "3. Request Reservation\n";
        cout << "4. Cancel Reservation\n";
        cout << "5. Buy Ticket\n";
        cout << "6. View My Information\n";
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
            user.view_events();
            break;
        case 2:
            user.view_my_reservations();
            break;
        case 3:
        {
            Event new_event = user.create_event(facility);
            vector<Event> pending_events = retrieve_events_from_file("pending_requests.txt", facility);
            pending_events.push_back(new_event);
            add_event_to_file(pending_events, "pending_requests.txt");
            break;
        }
        case 4:
        {
            cout << "Enter the name of the event you would like to cancel: ";
            string event_name;
            cin.ignore();
            getline(cin, event_name);
            vector<Event> pending_reservations = retrieve_events_from_file("pending_requests.txt", facility);
            vector<Event> reservations = retrieve_events_from_file("reservations.txt", facility);
            auto it_pending = find_if(pending_reservations.begin(), pending_reservations.end(), [&](const Event &e)
                                      { return e.get_name() == event_name; });
            auto it_reservations = find_if(reservations.begin(), reservations.end(), [&](const Event &e)
                                           { return e.get_name() == event_name; });

            if (it_pending != pending_reservations.end())
            {
                user.cancel_reservation(*it_pending);
            }
            else if (it_reservations != reservations.end())
            {
                user.cancel_reservation(*it_reservations);
            }
            else
            {
                cout << "Event not found.\n";
            }
            break;
        }
        case 5:
            // Add functionality to buy a ticket
            break;
        case 6:
            user.view_my_information();
            break;
        case 7:
            return;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    }
}
