#ifndef RESERVATIONSYSTEM_HPP
#define RESERVATIONSYSTEM_HPP

#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class ReservationSystem
{
public:
    struct Reservation
    {
        string name;
        T item;
        string reserver_name;
        time_t reserver_dob;
        string reserver_id;
        string reservation_id;
        time_t reservation_time;

        Reservation(const string &name, const T &item, const string &reserver_name, time_t reserver_dob, const string &reserver_id, const string &reservation_id, time_t reservation_time)
            : name(name), item(item), reserver_name(reserver_name), reserver_dob(reserver_dob), reserver_id(reserver_id), reservation_id(reservation_id), reservation_time(reservation_time) {}

        bool operator==(const Reservation &other) const
        {
            return reservation_id == other.reservation_id;
        }
    };

    void reserve_item(const string &name, const T &item, const string &reserver_name, time_t reserver_dob, const string &reserver_id, const string &reservation_id, time_t reservation_time)
    {
        auto it = find_if(reservations.begin(), reservations.end(), [&](const Reservation &res)
                          { return res.reservation_id == reservation_id; });
        if (it != reservations.end())
        {
            it->item = item;
            it->reservation_time = reservation_time;
        }
        else
        {
            reservations.emplace_back(name, item, reserver_name, reserver_dob, reserver_id, reservation_id, reservation_time);
        }
    }

    void add_reservations(const vector<Reservation> &new_reservations)
    {
        for (const auto &res : new_reservations)
        {
            reserve_item(res.name, res.item, res.reserver_name, res.reserver_dob, res.reserver_id, res.reservation_id, res.reservation_time);
        }
    }

    int get_reservation_duration(const string &reservation_id) const
    {
        auto it = find_if(reservations.begin(), reservations.end(), [&](const Reservation &res)
                          { return res.reservation_id == reservation_id; });
        if (it != reservations.end())
        {
            return difftime(time(nullptr), it->reservation_time) / (60 * 60 * 24);
        }
        return -1;
    }

    void remove_reservation(const string &reservation_id)
    {
        reservations.erase(remove_if(reservations.begin(), reservations.end(), [&](const Reservation &res)
                                     { return res.reservation_id == reservation_id; }),
                           reservations.end());
    }

    void remove_reservations(const vector<string> &reservation_ids)
    {
        for (const auto &id : reservation_ids)
        {
            remove_reservation(id);
        }
    }

    size_t get_number_of_reservations() const
    {
        return reservations.size();
    }

    friend ostream &operator<<(ostream &os, const ReservationSystem &rs)
    {
        if (rs.reservations.empty())
        {
            os << "No reservations" << endl;
            return os;
        }
        for (const auto &res : rs.reservations)
        {
            os << "Reservation: " << res.name << ", Reserver: " << res.reserver_name << ", ID: " << res.reservation_id << ", Time: " << std::ctime(&res.reservation_time);
            os << "Item: " << res.item << endl;
            os << endl;
        }
        return os;
    }

private:
    vector<Reservation> reservations;
};

#endif
