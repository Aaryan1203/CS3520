#include "include/facility.hpp"
#include "include/event.hpp"
#include <fstream>
#include <iostream>

using namespace std;

struct UserNameComparer
{
    UserNameComparer(const string &username) : username(username) {}

    bool operator()(const User &u) const
    {
        return u.get_username() == username;
    }

private:
    string username;
};

struct EventNameComparer
{
    EventNameComparer(const string &name) : name(name) {}
    bool operator()(const Event &e) const
    {
        return e.get_name() == name;
    }

private:
    string name;
};

Facility::Facility(string name)
    : name(name) {}

void Facility::add_user(User &user)
{
    all_users.push_back(user);
}

void Facility::add_approved_reservation(Event &event)
{
    approved_reservations.push_back(event);
}

void Facility::remove_approved_reservation(const Event &event) {
    auto it = find_if(approved_reservations.begin(), approved_reservations.end(), EventNameComparer(event.get_name()));
    if (it != approved_reservations.end()) {
        approved_reservations.erase(it);
        // Update the approved_reservations.txt file
        ofstream outfile("approved_reservations.txt");
        if (!outfile) {
            cerr << "Error opening file: approved_reservations.txt" << endl;
            return;
        }
        for (const auto &e : approved_reservations) {
            // Convert start and end times to a readable format
            time_t start_time = e.get_start_time();
            time_t end_time = e.get_end_time();
            tm *start_tm = localtime(&start_time);
            tm *end_tm = localtime(&end_time);
            // Write event details to the file
            outfile << "Event Name: " << e.get_name() << endl;
            outfile << "Start Time: " << put_time(start_tm, "%Y-%m-%d %H:%M") << endl;
            outfile << "End Time: " << put_time(end_tm, "%Y-%m-%d %H:%M") << endl;
            outfile << "Is public: " << (e.is_public_event() ? "yes" : "no") << endl;
            outfile << "Number of Guests: " << e.get_num_guests() << endl;
            if (e.get_organizer()) {
                outfile << "Organizer: " << e.get_organizer()->get_username() << endl;
            } else {
                outfile << "Organizer: None" << endl;
            }
            outfile << "Layout: " << layoutTypeToString(e.get_layout()) << endl;
            outfile << "Price of Event: " << e.get_price_of_event() << endl;
            outfile << "Ticket Price: " << e.get_ticket_price() << endl;
            outfile << "Organizer Type: " << organizerTypeToString(e.get_type()) << endl;
            outfile << "Open to Residents: " << (e.is_open_to_residents() ? "yes" : "no") << endl;
            outfile << "Open to Non-Residents: " << (e.is_open_to_non_residents() ? "yes" : "no") << endl;
            outfile << "Approved: " << (e.is_approved() ? "yes" : "no") << endl;
            outfile << "Attendees: ";
            const vector<User> &attendees = e.get_attendees();
            for (size_t i = 0; i < attendees.size(); ++i) {
                const User &user = attendees[i];
                outfile << user.get_username() << "," << user.get_balance() << "," << user.get_city();
                if (i < attendees.size() - 1) {
                    outfile << ";";
                }
            }
            outfile << endl;
            outfile << "----------------------------------------" << endl;
        }
        outfile.close();
    } else {
        cout << "Approved reservation not found: " << event.get_name() << endl;
    }
}

void Facility::remove_reservation(Event &event)
{
    auto it = find_if(approved_reservations.begin(), approved_reservations.end(), EventNameComparer(event.get_name()));
    if (it != approved_reservations.end())
    {
        approved_reservations.erase(it);
        cout << "Removed reservation for event: " << event.get_name() << endl;
    }
}

User* get_user_by_username(string username, Facility &facility) {
    for (auto &user : facility.get_all_users()) {
        if (user.get_username() == username) {
            return &user;
        }
    }
    throw runtime_error("User not found: " + username);
}

vector<User> &Facility::get_all_users()
{
    return all_users;
}

vector<Event> &Facility::get_approved_reservations()
{
    return approved_reservations;
}

void Facility::add_pending_reservation(Event &event)
{
    pending_reservations.push_back(event);
}

vector<Event> &Facility::get_pending_reservations()
{
    return pending_reservations;
}

void Facility::remove_pending_reservation(const Event &event) {
    auto it = find_if(pending_reservations.begin(), pending_reservations.end(), EventNameComparer(event.get_name()));
    if (it != pending_reservations.end()) {
        pending_reservations.erase(it);
        // Update the pending_reservations.txt file
        ofstream outfile("pending_reservations.txt");
        if (!outfile) {
            cerr << "Error opening file: pending_reservations.txt" << endl;
            return;
        }
        for (const auto &e : pending_reservations) {
            // Convert start and end times to a readable format
            time_t start_time = e.get_start_time();
            time_t end_time = e.get_end_time();
            tm *start_tm = localtime(&start_time);
            tm *end_tm = localtime(&end_time);
            // Write event details to the file
            outfile << "Event Name: " << e.get_name() << endl;
            outfile << "Start Time: " << put_time(start_tm, "%Y-%m-%d %H:%M") << endl;
            outfile << "End Time: " << put_time(end_tm, "%Y-%m-%d %H:%M") << endl;
            outfile << "Is public: " << (e.is_public_event() ? "yes" : "no") << endl;
            outfile << "Number of Guests: " << e.get_num_guests() << endl;
            if (e.get_organizer()) {
                outfile << "Organizer: " << e.get_organizer()->get_username() << endl;
            } else {
                outfile << "Organizer: None" << endl;
            }
            outfile << "Layout: " << layoutTypeToString(e.get_layout()) << endl;
            outfile << "Price of Event: " << e.get_price_of_event() << endl;
            outfile << "Ticket Price: " << e.get_ticket_price() << endl;
            outfile << "Organizer Type: " << organizerTypeToString(e.get_type()) << endl;
            outfile << "Open to Residents: " << (e.is_open_to_residents() ? "yes" : "no") << endl;
            outfile << "Open to Non-Residents: " << (e.is_open_to_non_residents() ? "yes" : "no") << endl;
            outfile << "Approved: " << (e.is_approved() ? "yes" : "no") << endl;
            outfile << "Attendees: ";
            const vector<User> &attendees = e.get_attendees();
            for (size_t i = 0; i < attendees.size(); ++i) {
                const User &user = attendees[i];
                outfile << user.get_username() << "," << user.get_balance() << "," << user.get_city();
                if (i < attendees.size() - 1) {
                    outfile << ";";
                }
            }
            outfile << endl;
            outfile << "----------------------------------------" << endl;
        }
        outfile.close();
    } else {
        cout << "Pending reservation not found: " << event.get_name() << endl;
    }
}

void Facility::approve_reservation(Event &event)
{
    auto it = find_if(pending_reservations.begin(), pending_reservations.end(), EventNameComparer(event.get_name()));
    if (it != pending_reservations.end())
    {
        pending_reservations.erase(it, pending_reservations.end());
        cout << "Approved reservation for event: " << event.get_name() << endl;
    }
    else
    {
        cout << "Pending reservation not found for event: " << event.get_name() << endl;
    }
    add_approved_reservation(event);
}

bool Facility::exceeds_max_reservation_time() const
{
    int organization_time = 0;
    int city_time = 0;
    int resident_time = 0;
    int non_resident_time = 0;
    for (const auto &event : approved_reservations)
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

void Facility::update_user(const User &user)
{
    auto it = find_if(all_users.begin(), all_users.end(), UserNameComparer(user.get_username()));
    if (it != all_users.end())
    {
        *it = user;
    }
}

void Facility::update_approved_reservation(const Event &event)
{
    auto it = find_if(approved_reservations.begin(), approved_reservations.end(), EventNameComparer(event.get_name()));
    if (it != approved_reservations.end())
    {
        *it = event;
    }
}

void Facility::update_pending_reservation(const Event &event)
{
    auto it = find_if(pending_reservations.begin(), pending_reservations.end(), EventNameComparer(event.get_name()));
    if (it != pending_reservations.end())
    {
        *it = event;
    }
}
