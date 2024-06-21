#include "include/event.hpp"
#include <iostream>

using namespace std;

Event::Event(
    const string &name,
    time_t date,
    time_t start_time,
    time_t end_time,
    int num_guests,
    User &organizer,
    LayoutType layout,
    int price_of_event,
    int ticket_price,
    OrganizerType type,
    bool open_to_residents,
    bool open_to_non_residents)
    : name(name),
      date(date),
      start_time(start_time),
      end_time(end_time),
      num_guests(num_guests),
      organizer(organizer),
      layout(layout),
      price_of_event(price_of_event),
      ticket_price(ticket_price),
      attendees(attendees),
      waitlist(waitlist),
      type(type),
      open_to_residents(open_to_residents),
      open_to_non_residents(open_to_non_residents)
{
}