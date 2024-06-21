#include "include/facility.hpp"

using namespace std;

Facility::Facility(vector<Event> reservations, FacilityManager manager)
    : reservations(reservations), manager(manager)
{
}

void Facility::add_reservation(Event &event)
{
    reservations.push_back(event);
}
