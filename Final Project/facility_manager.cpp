#include <string>
#include "include/facility_manager.hpp"
#include <iostream>

using namespace std;

FacilityManager::FacilityManager(const string &username, const string &password)
    : username(username), password(password), facility(nullptr)
{
}

string FacilityManager::get_username() const
{
    return username;
}