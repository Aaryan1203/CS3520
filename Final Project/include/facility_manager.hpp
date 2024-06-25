#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include <string>
#include <memory>
#include "event.hpp"

using namespace std;

class Facility;

class FacilityManager
{
public:
    FacilityManager(const string &username, const string &password);

    string get_username() const;

    void view_reservations(const string &file_name) const;
    void view_budget() const;

    void add_budget(double amount);

private:
    string username;
    string password;
    double budget;

    bool is_valid_event(const Event &event) const;
    bool is_valid_layout(const Event &event) const;
};

bool validate_facility_manager_credentials(const string &username, const string &password, FacilityManager &manager);
void facility_manager_menu(FacilityManager &manager, Facility &facility);
void view_events_for_next_week(Facility &facility);
void approve_reservation(Event &event, Facility &facility);

#endif