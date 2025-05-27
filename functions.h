#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <set>

struct StudentResult {
    std::string fileName;
    int score;
    int totalQuestions;
};

// In functions.h
void gradeStudentExam(const std::string& fileName,
                      const std::map<std::string, std::string>& correctAnswers,
                      std::vector<StudentResult>& results,
                      bool showDetails);

void extractFunction(const std::string& question, const std::string& symbol,
                     std::map<std::string, std::string>& functions, bool showDetails);

std::string differentiateFunction(const std::string& expression);

bool compareDerivative(const std::string& originalExpression,
                       const std::string& studentAnswer, bool showDetails);

double integrateNumerically(const std::string& expression, double a, double b, bool showDetails);

bool compareQuestion(const std::string& question, const std::string& studentAnswer,
                     const std::map<std::string, std::string>& correctAnswers, bool showDetails);

bool calculateAccelerationAndCompare(const std::string& studentAnswer,
                                     const std::map<std::string, std::string>& extractedFunctions,
                                     bool showDetails);

bool correctKineticEnergy(double P, double time, const std::string& expressionE,
                        const std::string& studentAnswer, bool showDetails);

bool calculateVelocityByVariableForce(const std::string& F_expr_str, double mass,
                                      double finalTime, const std::string& studentAnswer,
                                      bool showDetails);

void showStudentDetails(const std::string& studentName,
                        const std::vector<StudentResult>& results,
                        const std::map<std::string, std::string>& correctAnswers);

void showCourseSummary(const std::vector<StudentResult>& results,
                       double passingThreshold,
                       const std::set<std::string>& allStudents);

#endif
