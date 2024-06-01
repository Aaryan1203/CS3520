#include "teams.hpp"
#include "student.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


void create_teams(vector<Student> &students, int team_size, const string &preference, map<int, vector<Student>> &teams)
{
    int team_number = 1;
    unordered_map<string, set<string>> student_groups;
    vector<Student> remaining_students;

    // Group students based on their preferences
    for (const auto &student : students)
    {
        if (!student.prefer_to_work_with.empty())
        {
            for (const auto &preferred : student.prefer_to_work_with)
            {
                student_groups[student.username].insert(preferred);
                student_groups[preferred].insert(student.username);
            }
        }
        else
        {
            remaining_students.push_back(student);
        }
    }

    // Process groups and form initial teams
    for (const auto &group : student_groups)
    {
        vector<Student> team;
        map<string, int> team_score = {{"programming", 0}, {"design", 0}, {"debugging", 0}};
        vector<string> team_not_work_with; // Reset for each team

        for (const auto &member : group.second)
        {
            auto it = find_if(students.begin(), students.end(), [&](const Student &s)
                              { return s.username == member; });
            if (it != students.end() && allowed_to_work_with(team_not_work_with, *it, team))
            {
                team.push_back(*it);
                update_team_score(team_score, *it);
                add_to_team_not_work_with(team_not_work_with, *it);
            }
        }

        if (!team.empty())
        {
            teams[team_number++] = team;
        }
    }

    // Ensure each team has at least one advanced or intermediate programmer
    for (auto &team_entry : teams)
    {
        auto &team = team_entry.second;
        bool has_advanced_programmer = any_of(team.begin(), team.end(), [](const Student &s)
                                              { return s.programming == 3; });
        bool has_intermediate_programmer = any_of(team.begin(), team.end(), [](const Student &s)
                                                  { return s.programming == 2; });

        if (!has_advanced_programmer && !has_intermediate_programmer)
        {
            auto it = find_if(remaining_students.begin(), remaining_students.end(), [](const Student &s)
                              { return s.programming >= 2; });
            if (it != remaining_students.end() && allowed_to_work_with({}, *it, team))
            {
                team.push_back(*it);
                remaining_students.erase(it);
            }
        }
    }

    // Fill remaining slots in teams
    while (!remaining_students.empty())
    {
        bool added = false;
        for (auto &team_entry : teams)
        {
            auto &team = team_entry.second;
            if (team.size() < team_size && !remaining_students.empty())
            {
                for (auto it = remaining_students.begin(); it != remaining_students.end(); ++it)
                {
                    if (allowed_to_work_with({}, *it, team))
                    {
                        team.push_back(*it);
                        remaining_students.erase(it);
                        added = true;
                        break;
                    }
                }
            }
        }
        if (!added)
        {
            break;
        }
    }

    // If there are still remaining students, create new teams for them
    while (!remaining_students.empty())
    {
        vector<Student> new_team;
        vector<string> team_not_work_with; // Reset for each team
        map<string, int> team_score = {{"programming", 0}, {"design", 0}, {"debugging", 0}};

        while (new_team.size() < team_size && !remaining_students.empty())
        {
            auto it = remaining_students.begin();
            if (allowed_to_work_with(team_not_work_with, *it, new_team))
            {
                new_team.push_back(*it);
                update_team_score(team_score, *it);
                add_to_team_not_work_with(team_not_work_with, *it);
                remaining_students.erase(it);
            }
        }

        if (!new_team.empty())
        {
            teams[team_number++] = new_team;
        }
    }
}

void add_to_team_not_work_with(vector<string> &team_not_work_with, Student &student)
{
    for (const auto &partner : student.do_not_work_with)
    {
        team_not_work_with.push_back(partner);
    }
}

bool allowed_to_work_with(const vector<string> &team_not_work_with, const Student &student, const vector<Student> &team)
{
    // Check if the student is in the team_not_work_with list
    bool student_in_team_not_work_with = find(team_not_work_with.begin(), team_not_work_with.end(), student.username) != team_not_work_with.end();

    // Check if any student in the team is in the student's do_not_work_with list
    bool team_member_in_student_not_work_with = false;
    for (const auto &team_member : team)
    {
        if (find(student.do_not_work_with.begin(), student.do_not_work_with.end(), team_member.username) != student.do_not_work_with.end())
        {
            team_member_in_student_not_work_with = true;
            break;
        }
    }

    // Return false if either condition is met
    return !(student_in_team_not_work_with || team_member_in_student_not_work_with);
}

void update_team_score(map<string, int> &team_score, Student &current_student)
{
    team_score["programming"] += current_student.programming;
    team_score["debugging"] += current_student.debugging;
    team_score["desgign"] += current_student.design;
}

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
        for (const auto &student : team.second)
        {
            cout << student.username << " ";
        }
        cout << endl;
        cout << "Programming score: " << total_programming << endl;
        cout << "Debugging score: " << total_debugging << endl;
        cout << "Design score: " << total_design << endl;
        cout << "---------------------" << endl;
    }
}