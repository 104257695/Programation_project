/*
* CS106L Assignment 1: CourseEnrollment
* Originally developed by Alex Smith with adaptations by Jordan Lee.
*
* Complete each STUDENT TODO section. No other files need modification.
*/

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

/**
  * Represents an academic course from ExploreCourses.
  
  */
struct Course {
  std::string title;
  int number_of_units;
  std::string quarter;

  Course(const std::string &name, const std::string &credits, const std::string &term)
    : title(name), number_of_units(std::stoi(credits)), quarter(term) {}

};

#include "utils.cpp" // DO NOT REMOVE

/**
  * Process CSV data and populate course listings
  * Skips header row during processing
  */
void parse_csv(const std::string &filename, std::vector<Course> &courses) {
  std::ifstream input_file(filename);
  
  std::string record;
  std::getline(input_file, record); // Skip headers
  
  while (std::getline(input_file, record)) {
    if (record.empty()) continue;
    
    auto parts = split(record, ',');
    if (parts.size() < 3) continue;
    
    courses.emplace_back(parts[0], parts[1], parts[2]);
  }
  input_file.close();
}

//----------

/**
  * Generate available courses report and update dataset
  */
void write_courses_offered(std::vector<Course>& all_courses) {
  std::ofstream output_file(COURSES_OFFERED_PATH);

  output_file << "Title,Number of Units,Quarter\n";
  std::vector<Course> remaining_courses;

  for (const auto& c : all_courses) {
      if (c.quarter != "null") {
          output_file << c.title << ',' << c.number_of_units << ',' << c.quarter << '\n';
      }
      else {
          remaining_courses.push_back(c);
      }
  }

  output_file.close();
  all_courses.swap(remaining_courses);   
}

void write_courses_not_offered(const std::vector<Course> unlisted_courses) {
  std::ofstream report_file(COURSES_NOT_OFFERED_PATH);
  report_file << "Title,Number of Units,Quarter\n";
  
  for (const auto &c : unlisted_courses) {
    report_file << c.title << ',' << c.number_of_units << ',' << c.quarter << '\n';
  } 
  report_file.close();

}   
int main() {
  static_assert(is_valid_course<Course>, "Invalid Course structure definition");
  
  std::vector<Course> courses;
  parse_csv("courses.csv", courses);
  
  write_courses_offered(courses);

  write_courses_not_offered(courses);
  
  return run_autograder();
}
