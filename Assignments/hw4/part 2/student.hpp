#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>
#include <map>

using namespace std;

/*
 * @enum skill_rating
 * @brief This enum represents the skill rating of a student
 */
enum skill_rating
{
  Beginner = 1,     /**< The student is a beginner */
  Intermediate = 2, /**< The student is intermediate */
  Advanced = 3      /**< The student is advanced */
};

/*
 * @struct Student
 * @brief This struct represents a student
 */
struct Student
{
  string username;                    /**< The student's username */
  skill_rating programming;           /**< The student's programming rating */
  skill_rating debugging;             /**< The student's debugging rating */
  skill_rating design;                /**< The student's design  rating */
  vector<string> do_not_work_with;    /**< The students the student does not want to work with */
  vector<string> prefer_to_work_with; /**< The students the student prefers to work with */
};

/*
 * @brief This function reads the students' results from a file and populates
 * the students vector
 *
 * @param file_name: The name of the file to read the students' results from
 * @param students: The vector to populate with the students' results
 *
 * @return: void
 */
void read_students_results(const string &file_name, vector<Student> &students);

skill_rating convert_skill_rating(const string &level);

void categorizeStudents(const vector<Student> &students,
                        map<int, vector<Student>> &programming_students,
                        map<int, vector<Student>> &debugging_students,
                        map<int, vector<Student>> &design_students);
#endif
