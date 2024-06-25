#include <string>
#include <fstream>
#include <iostream>
#include "include/facility_manager.hpp"
#include "include/facility.hpp"

using namespace std;

FacilityManager::FacilityManager(const string &username, const string &password)
    : username(username), password(password), facility(nullptr), budget(0.0)
{
}

string FacilityManager::get_username() const
{
    return username;
}

shared_ptr<Facility> FacilityManager::get_facility() const
{
    return facility;
}

void FacilityManager::view_reservations(const string &file_name) const
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        cout << "Error: could not open file " << file_name << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

void FacilityManager::view_budget() const
{
    cout << "Current budget: $" << budget << endl;
}

void FacilityManager::refund_event(Event &event)
{
    time_t current_time = time(nullptr); // Get current time
    double refund_amount = event.get_price_of_event();

    // Calculate penalty if cancellation is within 7 days but not within 24 hours
    if (event.get_start_time() - current_time <= 7 * 24 * 3600 && event.get_start_time() - current_time > 24 * 3600)
    {
        refund_amount *= 0.99; // 1% penalty
    }
    else if (event.get_start_time() - current_time <= 24 * 3600)
    {
        refund_amount = 0; // No refund within 24 hours
    }

    budget -= refund_amount;
    // event.refund_users(facility);

    // Remove the event from the facility's reservations
    facility->remove_reservation(event);

    // Update users' reservations
    for (User &attendee : event.get_attendees())
    {
        // attendee.cancel_reservation(event, facility);
    }

    cout << "Refunded event and updated budget. New budget: $" << budget << endl;
}

bool FacilityManager::is_valid_event(const Event &event) const
{
    // Facility operating hours
    const time_t opening_time = 8 * 3600;  // 8 AM in seconds
    const time_t closing_time = 23 * 3600; // 11 PM in seconds

    // Check operating hours
    if (event.get_start_time() < opening_time || event.get_end_time() > closing_time)
    {
        return false;
    }

    // Check guest limit
    if (event.get_num_guests() > 40)
    {
        return false;
    }

    return true;
}

bool FacilityManager::is_valid_layout(const Event &event) const
{
    if (event.get_type() == OrganizerType::CITY || event.get_type() == OrganizerType::ORGANIZATION)
    {
        return event.get_layout() != LayoutType::WEDDING_STYLE;
    }
    return true;
}

void FacilityManager::approve_reservation(const string &event_name)
{
    if (!facility)
    {
        cout << "Facility not assigned to manager." << endl;
        return;
    }

    Event *event = nullptr;
    for (Event &e : facility->get_pending_reservations())
    {
        if (e.get_name() == event_name)
        {
            event = &e;
            break;
        }
    }

    if (event)
    {
        if (!is_overlapping(*event))
        {
            if (!is_valid_event(*event))
            {
                cout << "Cannot approve reservation due to invalid event timings or guest limit exceeded." << endl;
                return;
            }

            if (!is_valid_layout(*event))
            {
                cout << "Cannot approve reservation due to invalid layout for city/organization events." << endl;
                return;
            }

            // Cost calculation based on user type
            int hourly_rate;
            switch (event->get_type())
            {
            case OrganizerType::CITY:
                hourly_rate = 5;
                break;
            case OrganizerType::ORGANIZATION:
                hourly_rate = 20;
                break;
            case OrganizerType::RESIDENT:
                hourly_rate = 10;
                break;
            case OrganizerType::NON_RESIDENT:
                hourly_rate = 15;
                break;
            default:
                hourly_rate = 0;
                break;
            }

            int event_duration = (event->get_end_time() - event->get_start_time()) / 3600;
            int event_cost = 10 + (hourly_rate * event_duration); // 10 is the standard service charge
            event->set_ticket_price(event_cost);

            facility->approve_reservation(*event);
            cout << "Approved reservation for event: " << event_name << " with cost: $" << event_cost << endl;
        }
        else
        {
            cout << "Cannot approve reservation due to overlapping times or exceeded weekly hours." << endl;
        }
    }
    else
    {
        cout << "Pending reservation not found for event: " << event_name << endl;
    }
}

void FacilityManager::add_budget(double amount)
{
    budget += amount;
}

void FacilityManager::set_facility(shared_ptr<Facility> fac)
{
    facility = fac;
}

bool FacilityManager::is_overlapping(const Event &new_event) const
{
    for (Event &event : facility->get_approved_reservations())
    {
        if (((new_event.get_start_time() < event.get_end_time() && new_event.get_start_time() >= event.get_start_time()) ||
             (new_event.get_end_time() > event.get_start_time() && new_event.get_end_time() <= event.get_end_time())))
        {
            return true;
        }
    }
    return false;
}

bool validate_facility_manager_credentials(const string &username, const string &password, FacilityManager &manager)
{
    ifstream file("manager_credentials.txt");
    if (!file.is_open())
    {
        cout << "Error: could not open manager credentials file" << endl;
        return false;
    }

    string file_username, file_password, line;
    while (getline(file, line))
    {
        if (line.find("username: ") == 0)
        {
            file_username = line.substr(10);
        }
        else if (line.find("password: ") == 0)
        {
            file_password = line.substr(10);
        }

        if (file_username == username && file_password == password)
        {
            manager = FacilityManager(username, password);
            return true;
        }
    }

    return false;
}

void facility_manager_menu(FacilityManager &manager, Facility &facility)
{
    while (true)
    {
        cout << "Welcome Manager " << manager.get_username() << "!\n";
        cout << "1. View Reservation Requests\n";
        cout << "2. View Approved reservations\n";
        cout << "3. View Budget\n";
        cout << "4. Refund Event\n";
        cout << "5. Approve Reservation\n";
        cout << "6. Logout\n";

        int choice;
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 7)
        {
            cout << "Invalid input. Please try again. \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            manager.view_reservations("pending_reservations.txt");
            break;
        }
        case 2:
        {
            manager.view_reservations("approved_reservations.txt");
            break;
        }
        case 3:
        {
            string event_name;

            cout << "Enter the event name to refund: ";
            cin.ignore();
            getline(cin, event_name);

            const Event *event_ptr = nullptr;
            vector<Event> &reservations = manager.get_facility()->get_approved_reservations();
            for (const Event &e : reservations)
            {
                if (e.get_name() == event_name)
                {
                    event_ptr = &e;
                    break;
                }
            }

            if (event_ptr != nullptr)
            {
                Event event = *event_ptr; // Create a non-const copy
                // Assuming refund_event is a method in the Manager class that modifies the event
                manager.refund_event(event);
            }
            else
            {
                cout << "Event not found." << endl;
            }
            break;
        }
        case 4:
            manager.view_budget();
            break;
        case 5:
        {
            string event_name;
            cout << "Enter the event name to approve: ";
            cin.ignore();
            getline(cin, event_name);
            manager.approve_reservation(event_name);
            break;
        }
        case 6:
            return;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    }
}