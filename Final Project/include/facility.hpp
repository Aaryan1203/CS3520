#ifndef FACILITY_HPP
#define FACILITY_HPP

#include <vector>
#include <string>
#include <memory>
#include "user.hpp"

class Event;
class Facility
{
public:
    void add_reservation(Event &event);
    void remove_reservation(Event &event);
    const vector<Event> &get_reservations() const;

    void add_pending_reservation(Event &event);
    vector<Event> &get_pending_reservations();
    void approve_reservation(Event &event);
    bool exceeds_max_reservation_time() const;

private:
    vector<Event> reservations;
    vector<Event> pending_reservations;
};

#endif