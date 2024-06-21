#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include <string>
#include "event.hpp"

using namespace std;

class Facility;

class FacilityManager
{
public:
    FacilityManager(const string &username, const string &password);

    void view_reservation_requests(const string &file_name) const;
    void view_budget() const;
    void refund_event(Event &event);
    void view_events() const;
    string get_username() const;
private:
    string username;
    string password;
    Facility *facility;
};

#endif