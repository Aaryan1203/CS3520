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
void create_teams(vector<Student> &students, int team_size, const string &preference, map<int, vector<Student>> &teams);

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

void update_team_score(map<string, int> &team_score, Student &current_student);

void add_to_team_not_work_with(vector<string> &team_not_work_with, Student &student);
#endif