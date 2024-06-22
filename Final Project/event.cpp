#include "include/event.hpp"
#include "include/user.hpp"
#include "include/facility.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <fstream>
#include <utility>

using namespace std;

Event::Event(const string name, time_t date, time_t start_time, time_t end_time,
             bool is_public, int num_guests, User &organizer, LayoutType layout,
             int price_of_event, int ticket_price, OrganizerType type,
             bool open_to_residents, bool open_to_non_residents)
    : name(name), date(date), start_time(start_time), end_time(end_time),
      is_public(is_public), num_guests(num_guests), organizer(&organizer), layout(layout),
      price_of_event(price_of_event), ticket_price(ticket_price), type(type),
      open_to_residents(open_to_residents), open_to_non_residents(open_to_non_residents) {}

string Event::get_name() const { return name; }
time_t Event::get_date() const { return date; }
time_t Event::get_start_time() const { return start_time; }
time_t Event::get_end_time() const { return end_time; }
bool Event::is_public_event() const { return is_public; }
int Event::get_num_guests() const { return num_guests; }
int Event::get_price_of_event() const { return price_of_event; }
User *Event::get_organizer() const { return organizer; }
LayoutType Event::get_layout() const { return layout; }
int Event::get_ticket_price() const { return ticket_price; }
OrganizerType Event::get_type() const { return type; }
bool Event::is_open_to_residents() const { return open_to_residents; }
bool Event::is_open_to_non_residents() const { return open_to_non_residents; }
vector<User> Event::get_attendees() const { return attendees; }
void Event::set_ticket_price(int price) { ticket_price = price; }
ostream &operator<<(ostream &os, const Event &event)
{
    os << "Event Name: " << event.name << endl;
    os << "Date: " << event.date << endl;
    os << "Start Time: " << event.start_time << endl;
    os << "End Time: " << event.end_time << endl;
    os << "Number of Guests: " << event.num_guests << endl;
    os << "Organizer: " << event.organizer->get_username() << endl;
    os << "Price of Event: " << event.price_of_event << endl;
    os << "Ticket Price: " << event.ticket_price << endl;
    os << "Open to Residents: " << event.open_to_residents << endl;
    os << "Open to Non-Residents: " << event.open_to_non_residents << endl;
    return os;
}

bool Event::operator==(const Event &other) const
{
    return name == other.name && date == other.date && start_time == other.start_time &&
           end_time == other.end_time && num_guests == other.num_guests && organizer == other.organizer &&
           layout == other.layout && price_of_event == other.price_of_event && ticket_price == other.ticket_price &&
           type == other.type && open_to_residents == other.open_to_residents && open_to_non_residents == other.open_to_non_residents;
}

void Event::add_attendee(User &user)
{
    attendees.push_back(user);
}

void Event::refund_users()
{
    for (auto &attendee : attendees)
    {
        int cost = ticket_price;
        attendee.set_balance(attendee.get_balance() + cost);
        cout << "Refunded " << attendee.get_username() << " " << cost << " credits." << endl;
    }
    attendees.clear();
    cout << "All attendees have been refunded." << endl;
}

void add_event_to_file(const vector<Event> events, const string filename)
{
    ofstream outfile(filename, ios::app);

    if (!outfile)
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    for (const auto &event : events)
    {
        // Write event details to the file
        outfile << "Event Name: " << event.get_name() << endl;
        outfile << "Date: " << event.get_date() << endl;
        outfile << "Start Time: " << event.get_start_time() << endl;
        outfile << "End Time: " << event.get_end_time() << endl;
        outfile << "Is public: " << event.is_public_event() << endl;
        outfile << "Number of Guests: " << event.get_num_guests() << endl;
        if (event.get_organizer())
        {
            outfile << "Organizer: " << event.get_organizer()->get_username() << endl;
        }
        else
        {
            outfile << "Organizer: " << "None" << endl;
        }
        outfile << "Layout: " << static_cast<int>(event.get_layout()) << endl;
        outfile << "Price of Event: " << event.get_price_of_event() << endl;
        outfile << "Ticket Price: " << event.get_ticket_price() << endl;
        outfile << "Organizer Type: " << static_cast<int>(event.get_type()) << endl;
        outfile << "Open to Residents: " << event.is_open_to_residents() << endl;
        outfile << "Open to Non-Residents: " << event.is_open_to_non_residents() << endl;
        outfile << "----------------------------------------" << endl;
    }
    outfile.close();
}

vector<Event> retrieve_events_from_file(string filename, Facility &facility)
{
    ifstream infile(filename);
    vector<Event> events;
    if (!infile)
    {
        cerr << "Error opening file: " << filename << endl;
        return events;
    }

    string line;
    while (getline(infile, line))
    {
        if (line.find("Event Name: ") == 0)
        {
            string event_name = line.substr(12);

            getline(infile, line);
            time_t event_date = stoi(line.substr(6));

            getline(infile, line);
            time_t start_time = stoi(line.substr(12));

            getline(infile, line);
            time_t end_time = stoi(line.substr(10));

            getline(infile, line);
            bool is_public = stoi(line.substr(11));

            getline(infile, line);
            int num_guests = stoi(line.substr(16));

            getline(infile, line);
            string organizer_username = line.substr(11);
            User organizer = get_user_by_username(organizer_username, facility);

            getline(infile, line);
            LayoutType layout = static_cast<LayoutType>(stoi(line.substr(8)));

            getline(infile, line);
            int price_of_event = stoi(line.substr(16));

            getline(infile, line);
            int ticket_price = stoi(line.substr(14));

            getline(infile, line);
            OrganizerType organizer_type = static_cast<OrganizerType>(stoi(line.substr(16)));

            getline(infile, line);
            bool open_to_residents = stoi(line.substr(19));

            getline(infile, line);
            bool open_to_non_residents = stoi(line.substr(24));

            // Skip the separator line
            getline(infile, line);

            // Create the event
            Event event(event_name, event_date, start_time, end_time, is_public, num_guests, organizer, layout, price_of_event, ticket_price, organizer_type, open_to_residents, open_to_non_residents);
            events.push_back(event);
        }
    }

    infile.close();
    return events;
}

Event get_event_by_name(string name, vector<Event> &events)
{
    for (const auto &event : events)
    {
        if (event.get_name() == name)
        {
            return event;
        }
    }
}