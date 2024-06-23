#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class Facility;
class Event;

using namespace std;

class User
{
public:
    User(const string &username, int balance, const string &city);

    string get_username() const;
    int get_balance() const;
    string get_city() const;
    void set_balance(int balance);
    void cancel_reservation(Event &event);
    void view_events();
    void view_my_reservations(Facility &facility);
    Event create_event(Facility &facility);
    void view_my_information();
    void buy_ticket(Facility &facility);
    void add_reservation(Event &event);
    void add_event(Event &event);
    friend ostream &operator<<(ostream &os, const User &other);
private:
    string username;
    int balance;
    string city;
    vector<Event> reservations;
    vector<Event> events;
};
vector<User> read_users_from_file(string filename);
void user_menu(User &user, Facility &facility);
const User &get_user_by_username(string username, Facility &facility);
bool validate_user_credentials(const string &username, User &user, Facility &facility);
bool load_user_from_file(const string &username, User &user);
void save_user_to_file(const User &user);

#endif