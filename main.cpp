/*
<<<<<<< HEAD
 * CS106L Assignment 0: Environment Setup!
 * Created by Fabio Ibanez
 *
 * If you're reading this welcome to CS106L! For this assignment you don't 
 * actually need to write any C++ code. Instead, you'll be setting up your
 * environment and getting familiar with the tools we'll be using in the course.
 * The code in this file will verify that your installation is correct and that 
 * the autograder is working properly.
 */

#include <iostream>
#include <sstream>
#include "autograder/utils.cpp"

int main() {
  return run_autograder();
}
=======
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Jefferson Gramal"; 

/**
 * 
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark 
 */
std::set<std::string> get_applicants(std::string filename) {
  std::set<std::string> applicants;
    std::ifstream file(filename); 

    std::string name;
    while (std::getline(file, name)) {  
        applicants.insert(name);  
    }
    file.close();
    return applicants;
}

/**
 *
 * @param name      
 * @param students  
 * @return          
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*>matches;
  size_t spacePos = name.find(' ');
  std::string initials = name.substr(0, 1) + name.substr(spacePos + 1, 1);

  for (const auto& student : students) {
      size_t studentSpacePos = student.find(' ');
      if (studentSpacePos == std::string::npos) continue; 

      std::string studentInitials = student.substr(0, 1) + student.substr(studentSpacePos + 1, 1);

      if (studentInitials == initials) {
          matches.push(&student);  
      }
  }
  return matches;
}

/**
 * @param matches 
 * @return      
 */
std::string get_match(std::queue<const std::string*>& matches) {
  if (matches.empty()) {
    return "NO MATCHES FOUND.";
  }

  const std::string* best_match = matches.front(); 
  matches.pop();

  while (!matches.empty()) {
    const std::string* current = matches.front();
    matches.pop();

    if (current->length() > best_match->length()) {
      best_match = current;
    } else if (current->length() == best_match->length()) {
      if (*current < *best_match) {
          best_match = current;
      }
    }
  }
  return *best_match;

}
/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
>>>>>>> 9a663b0 (assign 2)
