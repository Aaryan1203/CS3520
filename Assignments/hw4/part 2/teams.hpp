#ifndef TEAMS_HPP
#define TEAMS_HPP

#include <string>
#include <vector>
#include <map>
#include "student.hpp"

using namespace std;

/*
 * @brief This function creates teams of students based on the team size and
 * student preferences
 *
 * @param students: The vector of students to create teams from
 * @param team_size: The size of the teams to create
 * @param preference: The preference of the students to prioritize
 *
 * @return: void
 */
void create_teams(vector<Student> &students, int team_size, map<int, vector<Student>> &teams);

/*
 * @brief This function prints the teams of students
 *
 * @param students: The vector of students to print the teams from
 *
 * @return: void
 */
void print_teams(map<int, vector<Student>> &teams);

int calculate_total_score(const vector<Student> &team, string skill);

bool allowed_to_work_with(const vector<string> &team_not_work_with, const Student &student, const vector<Student> &team);

void add_students_to_team(const vector<int> &skill_levels, vector<Student> &current_team, vector<string> &team_not_work_with,
                          map<int, vector<Student>> &programming_students, vector<Student> &students_not_in_team);

void add_to_team_not_work_with(vector<string> &team_not_work_with, Student &student);
#endif