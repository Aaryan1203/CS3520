#include "include/public_event.hpp"

using namespace std;

PublicEvent::PublicEvent(const string &name, time_t date, time_t start_time, time_t end_time, int num_guests, User &organizer, LayoutType layout, int price_of_event, int ticket_price, OrganizerType type, bool open_to_residents, bool open_to_non_residents)
    : Event(name, date, start_time, end_time, num_guests, organizer, layout, price_of_event, ticket_price, type, open_to_residents, open_to_non_residents) {
}
