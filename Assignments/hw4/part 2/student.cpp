#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "student.hpp"

using namespace std;

skill_rating convert_skill_rating(const string &level)
{
    if (level == "Beginner")
    {
        return Beginner;
    }
    else if (level == "Intermediate")
    {
        return Intermediate;
    }
    else if (level == "Advanced")
    {
        return Advanced;
    }
    else
    {
        throw invalid_argument("Invalid skill rating level");
    }
}

void read_students_results(const string &file_name, vector<Student> &students)
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        throw runtime_error("Could not open file");
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line))
    {
        stringstream ss(line);
        string username, level_prog, level_debug, level_design, do_not_work_with, prefer_to_work_with;

        getline(ss, username, ',');
        getline(ss, level_prog, ',');
        getline(ss, level_debug, ',');
        getline(ss, level_design, ',');
        getline(ss, do_not_work_with, ',');
        getline(ss, prefer_to_work_with, ',');

        Student student;
        student.username = username;
        student.programming = convert_skill_rating(level_prog);
        student.debugging = convert_skill_rating(level_debug);
        student.design = convert_skill_rating(level_design);

        stringstream ss_donot(do_not_work_with);
        string name;
        while (getline(ss_donot, name, ';'))
        {
            student.do_not_work_with.push_back(name);
        }

        stringstream ss_prefer(prefer_to_work_with);
        while (getline(ss_prefer, name, ';'))
        {
            student.prefer_to_work_with.push_back(name);
        }

        students.push_back(student);
    }
    file.close();
}

