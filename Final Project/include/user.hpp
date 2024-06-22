#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "enums.hpp"

class Facility;
class Event;

using namespace std;

class User
{
public:
    User(const string &username, const string &password, int balance, const string &city);

    string get_username() const;
    int get_balance() const;
    void set_balance(int balance);
    void cancel_reservation(Event &event);
    void view_events();
    void view_my_reservations();
    Event create_event(Facility &facility);
    void view_my_information();
private:
    string username;
    string password;
    int balance;
    string city;
    vector<Event> reservations;
    vector<Event> events;
};

// bool validate_user_credentials(const string &username, const string &password, User &user);
void user_menu(User &user, Facility &facility);
const User &get_user_by_username(string username, Facility &facility);

#endif