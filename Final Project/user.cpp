#include <string>
#include <iostream>
#include "user.hpp"

using namespace std;

User::User(const string &username, const string &password, int balance, const string &city)
    : username(username), password(password), balance(balance), city(city)
{
}

string User::get_username() const
{
    return username;
}   
