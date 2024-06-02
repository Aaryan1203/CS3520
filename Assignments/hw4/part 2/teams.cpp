#include "teams.hpp"
#include "student.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void add_students_to_team(const vector<int> &skill_levels,
                          vector<Student> &current_team,
                          vector<string> &team_not_work_with,
                          map<int, vector<Student>> &programming_students,
                          vector<Student> &students_not_in_team)
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

Student find_student_by_username(const vector<Student> &students,
                                 const string &username)
{
    for (const auto &student : students)
    {
        if (student.username.compare(username) == 0)
        {
            return student;
        }
    }
    return Student();
}

void create_teams(vector<Student> &students, int team_size,
                  map<int, vector<Student>> &teams, string preference)
{
    if (preference == "L")
    {

        map<int, vector<Student>> programming_students;
        for (const auto &student : students)
        {
            programming_students[student.programming].push_back(student);
        }

        map<int, vector<int>> priority_map = {
            {1, {3, 2, 1}}, {2, {2, 1, 3}}, {3, {1, 2, 3}}};

        if (team_size == 4)
        {
            priority_map[4] = {2, 3, 1};
        }

        int team_number = 1;
        while (!programming_students[1].empty() ||
               !programming_students[2].empty() ||
               !programming_students[3].empty())
        {
            vector<Student> current_team;
            vector<string> team_not_work_with;
            vector<Student> students_not_in_team;

            for (const auto &entry : priority_map)
            {
                add_students_to_team(entry.second, current_team, team_not_work_with,
                                     programming_students, students_not_in_team);
            }

            for (const auto &student : students_not_in_team)
            {
                programming_students[student.programming].push_back(student);
            }

            teams[team_number++] = current_team;
        }
    }
    else if (preference == "P")
    {
        int team_number = 1;
        map<string, vector<string>> students_and_preferred_students;

        for (const auto &student : students)
        {
            for (const auto &preferred_student : student.prefer_to_work_with)
            {
                students_and_preferred_students[student.username].push_back(preferred_student);
            }
        }

        while (!students_and_preferred_students.empty())
        {
            vector<Student> current_team;
            vector<string> team_not_work_with;
            vector<string> team_could_work_with;
            vector<Student> students_not_in_team;

            for (const auto &entry : students_and_preferred_students)
            {
                string student_username = entry.first;
                Student student = find_student_by_username(students, student_username);
                current_team.push_back(student);
                students_and_preferred_students.erase(student.username);
                add_to_team_could_work_with(team_could_work_with, student);
                add_to_team_not_work_with(team_not_work_with, student);

                while (current_team.size() < team_size)
                {
                    string preferred_student = team_could_work_with.back();
                    Student current_student =
                        find_student_by_username(students, preferred_student);
                    if (allowed_to_work_with(team_not_work_with, current_student,
                                             current_team))
                    {
                        current_team.push_back(current_student);
                        students_and_preferred_students.erase(current_student.username);
                        add_to_team_not_work_with(team_not_work_with, current_student);
                        add_to_team_could_work_with(team_could_work_with, current_student);
                        team_could_work_with.pop_back();
                    }
                    else
                    {
                        team_could_work_with.pop_back();
                        students_not_in_team.push_back(current_student);
                    }

                    if (current_team.size() != team_size &&
                        team_could_work_with.empty())
                    {
                        for (const auto &entry : students_and_preferred_students)
                        {
                            string student_username = entry.first;
                            Student student = find_student_by_username(students, student_username);
                            if (allowed_to_work_with(team_not_work_with, student,
                                                     current_team))
                            {
                                current_team.push_back(student);
                                students_and_preferred_students.erase(student.username);
                                add_to_team_not_work_with(team_not_work_with, student);
                                add_to_team_could_work_with(team_could_work_with, student);
                            }
                            else
                            {
                                students_not_in_team.push_back(student);
                            }
                            break;
                        }
                    }
                }
            }
            for (const auto &student : students_not_in_team)
            {
                for (const auto &preferred_student : student.prefer_to_work_with)
                {
                    students_and_preferred_students[student.username].push_back(
                        preferred_student);
                }
            }

            teams[team_number++] = current_team;
            current_team.clear();
            team_could_work_with.clear();
            team_not_work_with.clear();
            students_not_in_team.clear();
        }
    }
}

void add_to_team_not_work_with(vector<string> &team_not_work_with,
                               Student &student)
{
    for (const auto &partner : student.do_not_work_with)
    {
        team_not_work_with.push_back(partner);
    }
}

void add_to_team_could_work_with(vector<string> &team_could_work_with,
                                 Student &student)
{
    for (const auto &partner : student.prefer_to_work_with)
    {
        team_could_work_with.push_back(partner);
    }
}

bool allowed_to_work_with(const vector<string> &team_not_work_with,
                          const Student &student, const vector<Student> &team)
{
    // Check if the student is in the team_not_work_with list
    bool student_in_team_not_work_with =
        find(team_not_work_with.begin(), team_not_work_with.end(),
             student.username) != team_not_work_with.end();

    // Check if any student in the team is in the student's do_not_work_with list
    bool team_member_in_student_not_work_with = false;
    for (const auto &team_member : team)
    {
        if (find(student.do_not_work_with.begin(), student.do_not_work_with.end(),
                 team_member.username) != student.do_not_work_with.end())
        {
            team_member_in_student_not_work_with = true;
            break;
        }
    }

    // Return false if either condition is met
    return !(student_in_team_not_work_with ||
             team_member_in_student_not_work_with);
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
        cout << "Total score: "
             << total_debugging + total_design + total_programming << endl;
        cout << "---------------------" << endl;
    }
}

void create_teams_csv(map<int, vector<Student>> &teams)
{
    // calling the file teams.csv everytime
    ofstream file("teams.csv");
    if (!file.is_open())
    {
        cout << "Could not open file" << endl;
        return;
    }

    for (const auto &team : teams)
    {
        file << "Team " << team.first << ": ";
        for (const auto &student : team.second)
        {
            file << student.username << ", ";
        }
        file << endl;
    }
    cout << "Teams have been saved to teams.csv" << endl;
}
