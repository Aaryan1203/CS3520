#ifndef PUBLICEVENT_H
#define PUBLICEVENT_H

#include "event.hpp"

class PublicEvent : public Event
{
public:
    PublicEvent(const string &name, time_t date, time_t start_time, time_t end_time, int num_guests, User &organizer, LayoutType layout, int price_of_event, int ticket_price, OrganizerType type, bool open_to_residents, bool open_to_non_residents);

    void set_ticket_price(int price);

private:
    int ticket_price;
};

#endif