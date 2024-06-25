#include "include/global.hpp"
#include "include/enums.hpp"
#include <sstream>
#include <iostream>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <iomanip>

using namespace std;

// Parses a string into a time_t object
time_t parse_datetime(const string &datetime_str)
{
    tm timeinfo = {};
    stringstream ss(datetime_str);
    ss >> get_time(&timeinfo, "%Y-%m-%d %H:%M");
    if (ss.fail())
    {
        throw invalid_argument("Invalid date and time format.");
    }
    return mktime(&timeinfo);
}

// Parses a string into a boolean
bool parse_bool(const string &bool_str)
{
    return bool_str == "yes";
}

// Parses a string into a LayoutType
LayoutType parse_layout(const string &layout_str)
{
    if (layout_str == "Meeting Style")
        return LayoutType::MEETING_STYLE;
    if (layout_str == "Lecture Style")
        return LayoutType::LECTURE_STYLE;
    if (layout_str == "Wedding Style")
        return LayoutType::WEDDING_STYLE;
    if (layout_str == "Dance Room Style")
        return LayoutType::DANCE_ROOM_STYLE;
    throw invalid_argument("Invalid layout type");
}

// Parses a string into an OrganizerType
OrganizerType parse_organizer_type(const string &organizer_type_str)
{
    if (organizer_type_str == "City")
        return OrganizerType::CITY;
    if (organizer_type_str == "Organization")
        return OrganizerType::ORGANIZATION;
    if (organizer_type_str == "Resident")
        return OrganizerType::RESIDENT;
    if (organizer_type_str == "Non Resident")
        return OrganizerType::NON_RESIDENT;
    throw invalid_argument("Invalid organizer type");
}

// Checks if a new event overlaps with any existing events
bool is_overlapping(const Event &new_event, const vector<Event> &events)
{
    for (const auto &event : events)
    {
        if ((new_event.get_start_time() < event.get_end_time() && new_event.get_end_time() > event.get_start_time()) ||
            (new_event.get_start_time() == event.get_start_time() && new_event.get_end_time() == event.get_end_time()))
        {
            return true;
        }
    }
    return false;
}