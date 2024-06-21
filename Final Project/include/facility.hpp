#ifndef FACILITY_H
#define FACILITY_H

#include <vector>
#include "event.hpp"
#include "facility_manager.hpp"

class FacilityManager;

class Facility
{
public:
    Facility(vector<Event> reservations, FacilityManager manager);
    void add_reservation(Event &event);
    void remove_reservation(Event &event);
    void save_reservations_to_file(const string &filename) const;
    void load_reservations_from_file(const string &filename);

private:
    vector<Event> reservations;
    FacilityManager manager;
};

#endif