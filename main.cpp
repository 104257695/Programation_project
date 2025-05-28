#include <iostream>
#include <fstream>
#include <filesystem>
#include <ginac/ginac.h>
#include <set>
#include "functions.h"
#include "utils.h"

namespace fs = std::filesystem;
using namespace GiNaC;

void showMenu(const std::vector<StudentResult>& results,
              const std::map<std::string, std::string>& correctAnswers,
              const std::set<std::string>& allStudents) {
    while (true) {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Show all students' grades\n";
        std::cout << "2. View details of a specific student\n";
        std::cout << "3. Show course summary\n";
        std::cout << "4. Exit\n";
        std::cout << "--------------------------------------------\n";
        std::cout << "Select an option: ";
        int option;
        std::cin >> option;

        if (option == 1) {
            std::cout << "\n== GENERAL REPORT ==\n";
            std::ofstream report("students_grades.csv");
            if (!report) {
                std::cerr << "Could not create the grades file.\n";
                continue;
            }
            report << "Name,Score\n";

            for (const auto& res : results) {
                std::string name = fs::path(res.fileName).stem().string();
                std::cout << "Student: " << name << " - "
                          << "Score: " << res.score << "/" << res.totalQuestions << "\n";
                report << name << "," << res.score  << "\n";
            }
            report.close();
        } else if (option == 2) {
            std::string name;
            std::cout << "Enter the student's name (without .txt): ";
            std::cin >> name;
            showStudentDetails(name, results, correctAnswers);
        } else if (option == 3) {
            showCourseSummary(results, 0.6, allStudents);
        } else if (option == 4) {
            std::cout << "Exiting...\n";
            break;
        } else {
            std::cout << "Invalid option. Please try again.\n";
        }
    }
}

int main() {
    // Read list of all students
    std::set<std::string> allStudents = readStudentList("Students.txt");

    // Read correct answers
    std::map<std::string, std::string> correctAnswers;
    loadCorrectAnswers(correctAnswers);

    // Grade exams
    std::vector<StudentResult> results;
    std::string folder = "examenes/";
    bool showDetails = false;

    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            gradeStudentExam(entry.path().string(), correctAnswers, results, showDetails);
        }
    }

    // Show interactive menu
    showMenu(results, correctAnswers, allStudents);

    return 0;
}
