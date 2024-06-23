#include "include/user.hpp"
#include "include/facility.hpp"
#include "include/event.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <sstream>

using namespace std;

struct EventNameComparer
{
    EventNameComparer(const string &name) : name(name) {}
    bool operator()(const Event &e) const
    {
        return e.get_name() == name;
    }

private:
    string name;
};

User::User(const string &username, int balance, const string &city)
    : username(username), balance(balance), city(city)
{
}

void User::add_reservation(Event &event)
{
    reservations.push_back(event);
}

void User::add_event(Event &event)
{
    events.push_back(event);
}

ostream &operator<<(ostream &os, const User &other)
{
    os << "Username: " << other.username << std::endl;
    os << "Balance: " << other.balance << std::endl;
    os << "City: " << other.city << std::endl;
    return os;
}

string User::get_username() const
{
    return username;
}

int User::get_balance() const
{
    return balance;
}

string User::get_city() const
{
    return city;
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

vector<User> read_users_from_file(string filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error opening file: " << filename << endl;
        return vector<User>();
    }
    vector<User> users;
    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string username, balance_str, city;
        getline(ss, username, ',');
        getline(ss, balance_str, ',');
        getline(ss, city, ',');

        if (username.empty() || balance_str.empty() || city.empty())
        {
            cerr << "Invalid data in line: " << line << endl;
            continue;
        }

        double balance = stod(balance_str);
        User user(username, balance, city);
        users.push_back(user); // Assuming Facility has an add_user method
    }

    infile.close();
    return users;
}

void User::view_events()
{
    if (reservations.empty())
    {
        cout << "You have no upcoming events.\n";
        return;
    }
    for (const auto &event : reservations)
    {
        cout << event << endl;
    }
}

void User::view_my_reservations(Facility &facility)
{
    for (const auto &event : facility.get_pending_reservations())
    {
        if (event.get_organizer().get_username() == username)
        {
            cout << event.get_name() << endl;
        }
    }
    for (const auto &event : facility.get_approved_reservations())
    {
        if (event.get_organizer().get_username() == username)
        {
            cout << event.get_name() << endl;
        }
    }
    if (reservations.empty())
    {
        cout << "You have not created any events.\n";
        return;
    }
    for (const auto &event : reservations)
    {
        cout << event << endl;
    }
}

time_t prompt_for_datetime(const string &prompt)
{
    tm timeinfo = {};
    string datetime_str;
    while (true)
    {
        cout << prompt;
        getline(cin, datetime_str);
        stringstream ss(datetime_str);
        ss >> get_time(&timeinfo, "%Y-%m-%d %H:%M");
        if (ss.fail())
        {
            cout << "Invalid date and time. Please enter in YYYY-MM-DD HH:MM format.\n";
        }
        else
        {
            break;
        }
    }
    return mktime(&timeinfo);
}

int prompt_for_int(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
        {
            if (value >= 0)
            {
                break;
            }
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number.\n";
    }
    return value;
}

string prompt_for_string(const string &prompt)
{
    string value;
    cout << prompt;
    cin.ignore();
    getline(cin, value);
    return value;
}

bool prompt_for_bool(const string &prompt)
{
    string value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (value == "1" || value == "0")
        {
            break;
        }
        else
        {
            cout << "Invalid input. Please enter 1 for Yes or 0 for No.\n";
        }
    }
    return value == "1";
}

LayoutType prompt_for_layout_type()
{
    int layout_int;
    while (true)
    {
        cout << "Enter the layout type (integer value):\n";
        cout << "0: MEETING_STYLE\n";
        cout << "1: LECTURE_STYLE\n";
        cout << "2: WEDDING_STYLE\n";
        cout << "3: DANCE_ROOM_STYLE\n";
        cin >> layout_int;
        if (layout_int < 0 || layout_int > 3)
        {
            cout << "Invalid layout type. Please enter a number between 0 and 3.\n";
        }
        else
        {
            return static_cast<LayoutType>(layout_int);
        }
    }
}

OrganizerType prompt_for_organizer_type()
{
    int organizer_type_int;
    while (true)
    {
        cout << "Enter the organizer type (integer value):\n";
        cout << "0: CITY\n";
        cout << "1: ORGANIZATION\n";
        cout << "2: RESIDENT\n";
        cout << "3: NON_RESIDENT\n";
        cin >> organizer_type_int;
        if (organizer_type_int < 0 || organizer_type_int > 3)
        {
            cout << "Invalid organizer type. Please enter a number between 0 and 3.\n";
        }
        else
        {
            return static_cast<OrganizerType>(organizer_type_int);
        }
    }
}

int get_price_of_event(OrganizerType organizer_type, int hours_of_event)
{
    int price = 10;
    switch (organizer_type)
    {
    case OrganizerType::CITY:
        price += 5 * hours_of_event;
    case OrganizerType::ORGANIZATION:
        price += 20 * hours_of_event;
    case OrganizerType::RESIDENT:
        price += 10 * hours_of_event;
    case OrganizerType::NON_RESIDENT:
        price += 15 * hours_of_event;
    default:
        price = 10;
    }
    return price;
}

Event User::create_event(Facility &facility)
{
    string event_name = prompt_for_string("Enter the event name: ");
    time_t start_time;
    time_t end_time;
    while (true)
    {
        start_time = prompt_for_datetime("Enter the start time (YYYY-MM-DD HH:MM): ");
        end_time = prompt_for_datetime("Enter the end time (YYYY-MM-DD HH:MM): ");
        if (start_time >= end_time)
        {
            cout << "Start time cannot be after end time. Please re-enter.\n";
        }
        else
        {
            break;
        }
    }

    bool is_public = prompt_for_bool("Is the event public? (1 for Yes, 0 for No): ");

    int num_guests;
    while (true)
    {
        num_guests = prompt_for_int("Enter the number of guests: ");
        if (num_guests > 40)
        {
            cout << "Cannot create event with more than 40 people. Please re-enter.\n";
        }
        else
        {
            break;
        }
    }
    int ticket_price = prompt_for_int("Enter the ticket price: ");
    LayoutType layout = prompt_for_layout_type();
    OrganizerType organizer_type = prompt_for_organizer_type();
    int hours_of_event = end_time - start_time;
    int price_of_event = get_price_of_event(organizer_type, hours_of_event);
    bool open_to_residents = prompt_for_bool("Is the event open to residents? (1 for Yes, 0 for No): ");
    bool open_to_non_residents = prompt_for_bool("Is the event open to non-residents? (1 for Yes, 0 for No): ");
    User *organizer = this;

    Event new_event(event_name, start_time, end_time, is_public, num_guests, *organizer, layout, price_of_event, ticket_price, organizer_type, open_to_residents, open_to_non_residents, false);
    new_event.add_attendee(*this);
    this->add_reservation(new_event);
    cout << "Event has been created. You will have to wait for the facility manager to approve the event until it is confirmed" << endl;
    return new_event;
}

void User::buy_ticket(Facility &facility)
{
    // print the upcoming events
    cout << "Upcoming Events: \n";
    for (const auto &event : reservations)
    {
        cout << event << endl;
    }

    cout << "Enter the name of the event you would like to buy a ticket for: ";
    string event_name;
    cin.ignore();
    getline(cin, event_name);

    vector<Event> available_events = retrieve_events_from_file("reservations.txt", facility);

    if (available_events.empty())
    {
        cout << "No events available for purchase.\n";
        return;
    }

    auto it = find_if(available_events.begin(), available_events.end(), EventNameComparer(event_name));
    if (it != available_events.end())
    {
        Event &event = *it;
        if (event.get_num_guests() >= 40)
        {
            cout << "No more tickets available for " << event_name << endl;
            return;
        }
        if (balance < event.get_ticket_price())
        {
            cout << "Insufficient balance to buy ticket.\n";
            return;
        }

        event.add_attendee(*this);
        balance -= event.get_ticket_price();
        reservations.push_back(*it);
        cout << "Ticket purchased for " << event_name << endl;
    }
    else
    {
        cout << "Event not found.\n";
    }
}

void user_menu(User &user, Facility &facility)
{
    cout << "Welcome User " << user.get_username() << "!\n";
    while (true)
    {
        cout << "1. My Upcoming Events\n";
        cout << "2. My Created Reservations\n";
        cout << "3. Create Reservation\n";
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
            user.view_my_reservations(facility);
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

            vector<Event>::iterator it_pending = find_if(pending_reservations.begin(), pending_reservations.end(), EventNameComparer(event_name));
            vector<Event>::iterator it_reservations = find_if(reservations.begin(), reservations.end(), EventNameComparer(event_name));

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
            user.buy_ticket(facility);
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

bool load_user_from_file(const string &username, User &user)
{
    ifstream infile("users.txt");
    if (!infile)
    {
        cerr << "Error opening file: users.txt" << endl;
        return false;
    }

    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string file_username, city;
        int balance;

        getline(ss, file_username, ',');
        if (file_username == username)
        {
            ss >> balance;
            ss.ignore(); // ignore the comma
            getline(ss, city);

            user = User(file_username, balance, city);
            return true;
        }
    }

    return false;
}

void save_user_to_file(const User &user)
{
    ofstream outfile("users.txt", ios::app);
    if (!outfile)
    {
        cerr << "Error opening file: users.txt" << endl;
        return;
    }

    outfile << user.get_username() << "," << user.get_balance() << "," << user.get_city() << "\n";
    outfile.close();
}

bool validate_user_credentials(const string &username, User &user, Facility &facility)
{
    if (load_user_from_file(username, user))
    {
        return true;
    }
    else
    {
        string city;
        int balance;

        cout << "User not found. Creating a new user.\n";
        cout << "Enter balance: ";
        cin >> balance;
        cout << "Enter city: ";
        cin.ignore();
        getline(cin, city);

        user = User(username, balance, city);
        save_user_to_file(user);
        facility.add_user(user);
        return true;
    }
}