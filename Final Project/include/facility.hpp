#ifndef FACILITY_HPP
#define FACILITY_HPP

#include <vector>
#include <string>
#include <memory>
#include "user.hpp"

class Event;
class User;
class Facility
{
public:
    Facility(string name);
    void add_approved_reservation(Event &event);
    void remove_approved_reservation(const Event &event);
    void remove_reservation(Event &event);
    vector<Event> &get_approved_reservations();

    void add_pending_reservation(Event &event);
    void remove_pending_reservation(const Event &event);
    vector<Event> &get_pending_reservations();
    void approve_reservation(Event &event);
    bool exceeds_max_reservation_time() const;
    void add_user(User &user);
    vector<User> &get_all_users();
    void update_user(const User &user);
    void update_approved_reservation(const Event &event);
    void update_pending_reservation(const Event &event);

private:
    vector<Event> approved_reservations;
    vector<Event> pending_reservations;
    vector<User> all_users;
    string name;
};

#endif