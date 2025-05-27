#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <map>
#include <set>

std::string trim(const std::string& str);
std::string convertExponents(const std::string& expression);
double convertToSeconds(double value, const std::string& unit);
double extractTimeInSeconds(const std::string& question);
std::string normalizeAnswer(const std::string& answer);
void loadCorrectAnswers(std::map<std::string, std::string>& correctAnswers);
std::string preprocessExpression(const std::string& expression);
std::set<std::string> readStudentList(const std::string& filename);
std::string normalizeName(const std::string& name);

#endif // UTILS_H
