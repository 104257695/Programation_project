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
 
 const std::string OFFERED_COURSES_FILE = "student_output/courses_offered.csv";
 const std::string UNOFFERED_COURSES_FILE = "student_output/courses_not_offered.csv";
 
 /**
  * Represents an academic course from ExploreCourses.
  *
  * Structure contains:
  * - course_title: Name of course (std::string)
  * - units: Credit value (int)
  * - term_available: Offering quarter (std::string)
  */
 struct Course {
   std::string course_title;
   int units;
   std::string term_available;
 
   Course() : course_title(""), units(0), term_available("") {}
   
   Course(const std::string &name, const std::string &credits, const std::string &term)
       : term_available(term), units(std::stoi(credits)), course_title(name) {}
 };
 
 #include "utils.cpp" // DO NOT REMOVE
 
 /**
  * Process CSV data and populate course listings
  * Skips header row during processing
  */
 void process_csv_data(const std::string &filename, std::vector<Course> &course_list) {
   std::ifstream input_file(filename);
   if (!input_file) {
     std::cerr << "Failed to open: " << filename << '\n';
     return;
   }
   
   std::string record;
   std::getline(input_file, record); // Skip headers
   
   while (std::getline(input_file, record)) {
     if (record.empty()) continue;
     
     auto parts = split(record, ',');
     if (parts.size() < 3) continue;
     
     course_list.emplace_back(parts[0], parts[1], parts[2]);
   }
   input_file.close();
 }
 
 /**
  * Generate list of unavailable courses
  */
 void generate_unavailable_report(const std::vector<Course> &course_data) {
   std::ofstream report_file(UNOFFERED_COURSES_FILE);
   if (!report_file) {
     std::cerr << "Error creating: " << UNOFFERED_COURSES_FILE << '\n';
     return;
   }
   
   report_file << "Title,Number of Units,Quarter\n";
   for (const auto &c : course_data) {
     report_file << c.course_title << ',' << c.units << ',' << c.term_available << '\n';
   }
   report_file.close();
 }
 
 /**
  * Generate available courses report and update dataset
  */
 void generate_available_report(std::vector<Course> &course_data) {
   std::ofstream output_file(OFFERED_COURSES_FILE);
   if (!output_file) {
     std::cerr << "Cannot open: " << OFFERED_COURSES_FILE << '\n';
     return;
   }
   
   output_file << "Title,Number of Units,Quarter\n";
   std::vector<Course> remaining_courses;
   
   for (const auto &c : course_data) {
     if (c.term_available != "null") {
       output_file << c.course_title << ',' << c.units << ',' << c.term_available << '\n';
     } else {
       remaining_courses.push_back(c);
     }
   }
   output_file.close();
   
   course_data = std::move(remaining_courses);
 }
 
 int main() {
   static_assert(is_valid_course<Course>, "Invalid Course structure definition");
   
   std::vector<Course> all_courses;
   process_csv_data("courses.csv", all_courses);
   
   generate_available_report(all_courses);
   generate_unavailable_report(all_courses);
   
   return run_autograder();
 }
 