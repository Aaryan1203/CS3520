#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "student.hpp"
#include "teams.hpp"

using namespace std;

int calculate_total_score(const vector<Student> &team, string skill)
{
    int sum = 0;
    if (skill == "programming")
    {
        for (const auto &student : team)
        {
            sum += student.programming;
        }
    }
    if (skill == "debugging")
    {
        for (const auto &student : team)
        {
            sum += student.debugging;
        }
    }
    if (skill == "design")
    {
        for (const auto &student : team)
        {
            sum += student.design;
        }
    }
    return sum;
}

void create_teams(vector<Student> &students, int team_size, const string &preference, map<int, vector<Student>> &teams)
{
    int team_num = 1;
    vector<Student> team;
    for (size_t i = 0; i < students.size(); ++i)
    {
        team.push_back(students[i]);
        if (team.size() == team_size)
        {
            teams[team_num] = team;
            team.clear();
            ++team_num;
        }
    }
}

// prints each team with the scores of each skill
void print_teams(map<int, vector<Student>> &teams)
{
    cout << "All teams: " << endl;
    for (const auto &team : teams)
    {
        int total_programming = calculate_total_score(team.second, "programming");
        int total_debugging = calculate_total_score(team.second, "debugging");
        int total_design = calculate_total_score(team.second, "design");
        cout << "Team " << team.first << ": " << endl;
        cout << "Programming score: " << total_programming << endl;
        cout << "Debugging score: " << total_debugging << endl;
        cout << "Design score: " << total_design << endl;
        cout << "---------------------" << endl;
    }
}
