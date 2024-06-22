#include "include/facility.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void Facility::add_reservation(Event &event)
{
    reservations.push_back(event);
    cout << "Added reservation for event: " << event.get_name() << endl;
}

void Facility::remove_reservation(Event &event)
{
    auto it = remove_if(reservations.begin(), reservations.end(), [&](Event &e)
                        { return e.get_name() == event.get_name(); });
    if (it != reservations.end())
    {
        reservations.erase(it, reservations.end());
        cout << "Removed reservation for event: " << event.get_name() << endl;
    }
    else
    {
        cout << "Reservation not found for event: " << event.get_name() << endl;
    }
}

const User& get_user_by_username(const string &username, const Facility &facility) {
    for (const auto &reservation : facility.get_reservations()) {
        for (const auto &attendee : reservation.get_attendees()) {
            if (attendee.get_username() == username) {
                return attendee;
            }
        }
    }
    throw runtime_error("User not found");
}

const vector<Event> &Facility::get_reservations() const
{
    return reservations;
}

void Facility::add_pending_reservation(Event &event)
{
    pending_reservations.push_back(event);
    cout << "Added pending reservation for event: " << event.get_name() << endl;
}

vector<Event> &Facility::get_pending_reservations()
{
    return pending_reservations;
}

void Facility::approve_reservation(Event &event)
{
    auto it = find(pending_reservations.begin(), pending_reservations.end(), [&](Event &e)
                   { return e.get_name() == event.get_name(); });
    if (it != pending_reservations.end())
    {
        pending_reservations.erase(it, pending_reservations.end());
        cout << "Approved reservation for event: " << event.get_name() << endl;
    }
    else
    {
        cout << "Pending reservation not found for event: " << event.get_name() << endl;
    }
    add_reservation(event);
}

bool Facility::exceeds_max_reservation_time() const
{
    int organization_time = 0;
    int city_time = 0;
    int resident_time = 0;
    int non_resident_time = 0;
    for (const auto &event : reservations)
    {
        if (event.get_type() == OrganizerType::ORGANIZATION)
        {
            organization_time += event.get_end_time() - event.get_start_time();
        }
        else if (event.get_type() == OrganizerType::CITY)
        {
            city_time += event.get_end_time() - event.get_start_time();
        }
        else if (event.get_type() == OrganizerType::RESIDENT)
        {
            resident_time += event.get_end_time() - event.get_start_time();
        }
        else
        {
            non_resident_time += event.get_end_time() - event.get_start_time();
        }
    }
    return organization_time > 36 || city_time > 48 || resident_time > 24 || non_resident_time > 24;
}