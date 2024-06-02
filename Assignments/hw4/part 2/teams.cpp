#include "teams.hpp"
#include "student.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void add_students_to_team(const vector<int> &skill_levels, vector<Student> &current_team, vector<string> &team_not_work_with,
                          map<int, vector<Student>> &programming_students, vector<Student> &students_not_in_team)
{
    for (const auto skill_level : skill_levels)
    {
        if (!programming_students[skill_level].empty())
        {
            Student student = programming_students[skill_level].back();
            programming_students[skill_level].pop_back();
            if (allowed_to_work_with(team_not_work_with, student, current_team))
            {
                current_team.push_back(student);
                add_to_team_not_work_with(team_not_work_with, student);
            }
            else
            {
                students_not_in_team.push_back(student);
            }
            return;
        }
    }
}

void create_teams(vector<Student> &students, int team_size, map<int, vector<Student>> &teams)
{
    map<int, vector<Student>> programming_students;
    for (const auto &student : students)
    {
        programming_students[student.programming].push_back(student);
    }

    map<int, vector<int>> priority_map = {
        {1, {3, 2, 1}},
        {2, {2, 1, 3}},
        {3, {1, 2, 3}}};

    if (team_size == 4)
    {
        priority_map[4] = {2, 3, 1};
    }

    int team_number = 1;
    while (!programming_students[1].empty() || !programming_students[2].empty() || !programming_students[3].empty())
    {
        vector<Student> current_team;
        vector<string> team_not_work_with;
        vector<Student> students_not_in_team;

        for (const auto &entry : priority_map)
        {
            add_students_to_team(entry.second, current_team, team_not_work_with, programming_students, students_not_in_team);
        }

        for (const auto &student : students_not_in_team)
        {
            programming_students[student.programming].push_back(student);
        }

        teams[team_number++] = current_team;
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
        cout << "Total score: " << total_debugging + total_design + total_programming << endl;
        cout << "---------------------" << endl;
    }
}