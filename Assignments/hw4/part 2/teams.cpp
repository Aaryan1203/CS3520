#include "teams.hpp"
#include "student.hpp"
#include <iostream>
#include <string>
#include <vector>

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

void populate_team_not_work_with(vector<string> &team_not_work_with, Student &student)
{
    for (const auto &partner : student.do_not_work_with)
    {
        team_not_work_with.push_back(partner);
    }
}

void create_teams(vector<Student> &students, int team_size, const string &preference, map<int, vector<Student>> &teams)
{
    int team_number = 1;

    // if (preference == "P")
    // {
    //     vector<Student> students_copy = students;
    //     while (!students_copy.empty())
    //     {
    //         vector<Student> team;
    //         vector<Student> team_not_work_with;
    //         for (const auto &student : students)
    //         {
    //             team.push_back(student);
    //             students_copy.remove(student);
    //             for (const auto &partner : student.prefer_to_work_with)
    //             {
    //                 if (students.contains(partner))
    //                 {
    //                     team.push_back(partner);
    //                 }
    //                 else
    //                 {
    //                 }
    //             }
    //         }
    //         teams[team_number++] = team;
    //         team.clear();
    //     }
    // }
    /*else*/ if (preference == "L")
    {
        vector<Student> students; // Assume this is populated with data
        map<int, vector<Student>> programming_students;
        map<int, vector<Student>> debugging_students;
        map<int, vector<Student>> design_students;

        categorizeStudents(students, programming_students, debugging_students, design_students);

        // for (const auto& student : programming_students) {
        //     student.
        // }

        while (!programming_students[3].empty() || !programming_students[2].empty() || !programming_students[1].empty())
        {
            vector<Student> team;

            if (!programming_students[3].empty())
            {
                team.push_back(programming_students[3].back());
                programming_students[3].pop_back();
            }
            else if (!programming_students[2].empty())
            {
                team.push_back(programming_students[2].back());
                programming_students[2].pop_back();
            }
            else if (!programming_students[1].empty())
            {
                team.push_back(programming_students[1].back());
                programming_students[1].pop_back();
            }

            if (!debugging_students[3].empty())
            {
                team.push_back(debugging_students[3].back());
                debugging_students[3].pop_back();
            }
            else if (!debugging_students[2].empty())
            {
                team.push_back(debugging_students[2].back());
                debugging_students[2].pop_back();
            }
            else if (!debugging_students[1].empty())
            {
                team.push_back(debugging_students[1].back());
                debugging_students[1].pop_back();
            }

            if (!design_students[3].empty())
            {
                team.push_back(design_students[3].back());
                design_students[3].pop_back();
            }
            else if (!design_students[2].empty())
            {
                team.push_back(design_students[2].back());
                design_students[2].pop_back();
            }
            else if (!design_students[1].empty())
            {
                team.push_back(design_students[1].back());
                design_students[1].pop_back();
            }

            // removing assigned students from the main list
            for (const auto &student : team)
            {
                auto it = find_if(students.begin(), students.end(), [&](const Student &s)
                                  { return s.username == student.username; });
                if (it != students.end())
                {
                    students.erase(it);
                }
            }

            teams[team_number++] = team;

            if (team.size() < team_size)
            {
                break;
            }
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