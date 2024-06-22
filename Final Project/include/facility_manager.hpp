#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include <string>
#include <memory>
#include "event.hpp"
#include "facility.hpp"

using namespace std;

class Facility;

class FacilityManager {
public:
    FacilityManager(const string &username, const string &password);
    // ~FacilityManager();
    // FacilityManager(const FacilityManager& other);
    // FacilityManager(FacilityManager&& other) noexcept;
    // FacilityManager& operator=(const FacilityManager& other);
    // FacilityManager& operator=(FacilityManager&& other) noexcept;

    string get_username() const;
    shared_ptr<Facility> get_facility() const;

    void view_reservation_requests(const string &file_name) const;
    void view_budget() const;
    void refund_event(Event &event);
    void view_events() const;
    void view_pending_reservations() const;
    void approve_reservation(const string &event_name);

    void set_facility(shared_ptr<Facility> fac);
    void add_budget(double amount);

private:
    string username;
    string password;
    shared_ptr<Facility> facility;
    double budget;

    bool is_overlapping(const Event &new_event) const;
    bool is_valid_event(const Event &event) const;
    bool is_valid_layout(const Event &event) const;
};

bool validate_facility_manager_credentials(const string &username, const string &password, FacilityManager &manager);
void facility_manager_menu(FacilityManager &manager);

#endif