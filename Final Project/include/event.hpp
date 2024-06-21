#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include "enums.hpp"

using namespace std;

class User;

class Event {
public:
    Event(const string &name, time_t date, time_t start_time, time_t end_time, int num_guests, User &organizer, LayoutType layout, int price_of_event, int ticket_price, OrganizerType type, bool open_to_residents, bool open_to_non_residents);

    void add_attendee(User &user);
    void remove_attendee(User &user);
    void refund_users();

    // TODO: getters and setters

protected:
    string name;
    time_t date;
    time_t start_time;
    time_t end_time;
    int num_guests;
    User &organizer;
    LayoutType layout;
    int price_of_event;
    int ticket_price;
    vector<User> attendees;
    vector<User> waitlist;
    OrganizerType type;
    bool open_to_residents;
    bool open_to_non_residents;
};

#endif