#include "utils.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <algorithm>
#include <set>
#include <cctype>

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

void loadCorrectAnswers(std::map<std::string, std::string>& correctAnswers) {
    std::ifstream file("correct_answers.txt");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening correct answers file" << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        size_t pos = line.find(';');
        if (pos != std::string::npos) {
            std::string question = trim(line.substr(0, pos));
            std::string answer = trim(line.substr(pos + 1));
            correctAnswers[question] = answer;
        }
    }

    file.close();
}

std::string normalizeName(const std::string& name) {
    std::string clean;
    for (char c : name) {
        if (std::isalnum(c) || c == '_') {
            clean += std::tolower(c);
        }
    }
    return clean;
}

std::set<std::string> readStudentList(const std::string& filename) {
    std::set<std::string> studentList;
    std::ifstream inFile(filename);
    std::string name;
    while (std::getline(inFile, name)) {
        if (!name.empty()) {
            studentList.insert(normalizeName(name));
        }
    }
    return studentList;
}

std::string replaceEwithExp(const std::string& expression) {
    std::string result = expression;
    std::regex re_e_exp(R"(e\^\(([^()]+)\))");
    result = std::regex_replace(result, re_e_exp, "exp($1)");

    std::regex re_e_exp_simple(R"(e\^([^\s\^\+\-\*\/\)]+))");
    result = std::regex_replace(result, re_e_exp_simple, "exp($1)");

    return result;
}

std::string convertExponents(const std::string& expression) {
    std::string result = expression;
    std::regex re(R"((\w+|\([^\)]+\))\^(\d+|\([^\)]+\)))");
    while (std::regex_search(result, re)) {
        result = std::regex_replace(result, re, "pow($1,$2)");
    }
    return result;
}

std::string replacePi(const std::string& expression) {
    std::string result = expression;
    result = std::regex_replace(result, std::regex("π"), "Pi");
    return result;
}

std::string preprocessExpression(const std::string& expression) {
    std::string temp = replaceEwithExp(expression);
    temp = replacePi(temp);
    temp = convertExponents(temp);
    return temp;
}

double convertToSeconds(double value, const std::string& unit) {
    std::string u = unit;
    std::transform(u.begin(), u.end(), u.begin(), ::tolower);

    if (u == "s" || u == "sec" || u == "seconds") return value;
    if (u == "min" || u == "minute" || u == "minutes") return value * 60;
    if (u == "h" || u == "hour" || u == "hours") return value * 3600;
    if (u == "ms" || u == "millisecond" || u == "milliseconds") return value / 1000.0;

    std::cerr << "⚠️ Unrecognized time unit: " << unit << "\n";
    return value;
}

double extractTimeInSeconds(const std::string& question) {
    std::regex time_regex(R"(t\s*=\s*(\d+\.?\d*)\s*([a-zA-Z]+))");
    std::smatch match;

    if (std::regex_search(question, match, time_regex)) {
        double value = std::stod(match[1].str());
        std::string unit = match[2].str();
        return convertToSeconds(value, unit);
    }
    return -1;
}

std::string normalizeAnswer(const std::string& answer) {
    std::string copy = answer;
    std::transform(copy.begin(), copy.end(), copy.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    if (copy == "t" || copy == "true") return "T";
    if (copy == "f" || copy == "false") return "F";
    if (copy == "a") return "A";
    if (copy == "b") return "B";
    if (copy == "c") return "C";
    if (copy == "d") return "D";
    return copy;
}
