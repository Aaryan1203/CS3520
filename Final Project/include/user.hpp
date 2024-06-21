#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "event.hpp"
#include "enums.hpp"

using namespace std;

class User {
public:
    User(const string &username, const string &password, int balance, const string &city);

    void make_reservation(Event &event);
    void cancel_reservation(Event &event);
    void view_reservations() const;
    void buy_ticket(Event &event);
    void make_event(const string &name, time_t date, time_t start_time, time_t end_time, int num_guests, LayoutType layout, int ticket_price, OrganizerType type, bool open_to_residents, bool open_to_non_residents);
    void cancel_event(Event &event);
    string get_username() const;
private:
    string username;
    string password;
    int balance;
    string city;
    vector<Event> organized_events;
};

#endif