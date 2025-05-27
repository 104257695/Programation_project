#include "functions.h"
#include "utils.h"
#include <iostream>
#include <regex>
#include <ginac/ginac.h>
#include <filesystem>
namespace fs = std::filesystem;


using namespace GiNaC;

void extractFunction(const std::string& question, const std::string& symbol, std::map<std::string, std::string>& functions, bool showDetails) {
    std::regex time_regex(R"((t\s*=\s*\d+\.?\d*\s*[a-zA-Z]+))");
    std::smatch time_match;

    if (symbol == "t ") {
        if (std::regex_search(question, time_match, time_regex)) {
            functions[symbol] = time_match.str(1);
            return;
        }
    }

    size_t startPos = question.find(symbol + " =");
    if (startPos != std::string::npos) {
        startPos += symbol.length() + 3;  // Move past "symbol = "
        size_t endPos = question.find(' ', startPos);
        if (endPos == std::string::npos) endPos = question.length();

        std::string expression = question.substr(startPos, endPos - startPos);
        functions[symbol] = expression;
        if (showDetails) {
            std::cout << "Function/value of " << symbol << ": " << expression << std::endl;
        }
    }
}


std::string ex_to_string(const GiNaC::ex& e) {
    std::ostringstream oss;
    oss << e;
    return oss.str();
}

std::string differentiateFunction(const std::string& expression) {
    symbol t("t");
    symtab table;
    table["t"] = t;
    parser p(table);
    std::string processedExpr = preprocessExpression(expression);
    ex function = p(processedExpr);
    ex derivative = function.diff(t);
    return ex_to_string(derivative);
}

bool compareDerivative(const std::string& originalExpression, const std::string& studentAnswer, bool showDetails) {
    symbol t("t");
    symtab table;
    table["t"] = t;
    parser p(table);

    std::string derivativeStr = differentiateFunction(originalExpression);
    std::string studentAnswerProcessed = preprocessExpression(studentAnswer);
    ex derivative = p(derivativeStr);
    ex studentExpr = p(studentAnswerProcessed);

    ex difference = (derivative - studentExpr).expand();
    if (showDetails) {
        std::cout << "Expected derivative: " << derivative << std::endl;
    }

    return difference.is_zero();
}

double integrateNumerically(const std::string& expression, double a, double b, bool showDetails) {
    symbol t("t");
    symtab table;
    table["t"] = t;
    parser p(table);

    std::string processedExpr = preprocessExpression(expression);
    ex function = p(processedExpr);

    GiNaC::integral my_integral(t, a, b, function);
    ex numeric_result = my_integral.evalf();
    if (showDetails) {
        std::cout << "Calculated solution: " << numeric_result << std::endl;
    }
    return ex_to<numeric>(numeric_result).to_double();
}

bool compareQuestion(const std::string& question, const std::string& studentAnswer, 
                     const std::map<std::string, std::string>& correctAnswers, bool showDetails) {
    if (correctAnswers.count(question)) {
        std::string correctAnswer = correctAnswers.at(question);

        std::string normalizedStudent = normalizeAnswer(studentAnswer);
        std::string normalizedCorrect = normalizeAnswer(correctAnswer);
        if (showDetails) {
            std::cout << "  Correct answer:   \"" << correctAnswer << "\"\n";
        }
        bool result = (normalizedStudent == normalizedCorrect);

        return result;
    }

    std::cout << "  Question not found in the correct answers.\n\n";
    return false;
}

bool calculateAccelerationAndCompare(const std::string& studentAnswer, 
                                     const std::map<std::string, std::string>& extractedFunctions, 
                                     bool showDetails) {
    if (!extractedFunctions.count("F")) {
        std::cerr << "F not found in extractedFunctions.\n";
        return false;
    }

    double F = std::stod(extractedFunctions.at("F"));
    double P = std::stod(extractedFunctions.at("P"));
    const double g = 9.8;
    double m = P / g;
    double acceleration = F / m;

    double studentValue = std::stod(studentAnswer);
    if (showDetails) {
        std::cout << "Computed acceleration: " << acceleration << std::endl;
    }
    return std::abs(acceleration - studentValue) < 0.2;
}

bool correctKineticEnergy(double P, double time, const std::string& energyExpr, 
                          const std::string& studentAnswer, bool showDetails) {
    const double g = 9.8;
    double m = P / g;

    std::string derivativeStr = differentiateFunction(energyExpr);

    GiNaC::symbol t("t");
    GiNaC::symbol m_sym("m");
    GiNaC::symtab table;
    table["t"] = t;
    table["m"] = m_sym;
    GiNaC::parser p(table);

    GiNaC::ex derivative = p(derivativeStr);
    GiNaC::ex powerExpr = derivative.subs(m_sym == m);
    double calculatedPower = GiNaC::ex_to<GiNaC::numeric>(powerExpr.subs(t == time)).to_double();

    double studentValue = std::stod(studentAnswer);
    if (showDetails) {
        std::cout << "Calculated power: " << calculatedPower << std::endl;
    }
    return std::abs(calculatedPower - studentValue) < 0.3;
}

bool calculateVelocityFromVariableForce(const std::string& forceExprStr, double mass, double finalTime, 
                                        const std::string& studentAnswer, bool showDetails) {
    GiNaC::symbol t("t"), m("m");
    GiNaC::symtab table;
    table["t"] = t;
    table["m"] = m;
    GiNaC::parser p(table);

    std::string formattedForce = preprocessExpression(forceExprStr);
    GiNaC::ex forceExpr = p(formattedForce);
    GiNaC::ex accelerationExpr = forceExpr / mass;

    std::stringstream ss;
    ss << accelerationExpr;
    std::string accelerationExprStr = ss.str();

    double velocity = integrateNumerically(accelerationExprStr, 0, finalTime, showDetails);

    double answer = std::stod(studentAnswer);
    if (showDetails) {
        std::cout << "Calculated velocity: " << velocity << std::endl;
    }
    return std::abs(velocity - answer) < 0.1;
}


// En funciones.cpp-----------------------------------------------------------------------------------
void gradeStudentExam(const std::string& filename,
                      const std::map<std::string, std::string>& correctAnswers,
                      std::vector<StudentResult>& results,
                      bool showDetails) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open file: " << filename << "\n";
        return;
    }

    std::map<std::string, std::string> extractedFunctions;
    std::string line;
    int questionNumber = 1, score = 0;

    while (std::getline(file, line)) {
        size_t pos = line.find(';');
        if (pos == std::string::npos) continue;

        std::string question = trim(line.substr(0, pos));
        std::string answer = trim(line.substr(pos + 1));

        std::vector<std::string> symbols = {"x(t)", "v(t)", "a(t)", "E(t)", "F(t)", "m ", "F", "P", "t "};
        for (const std::string& symbol : symbols) {
            extractFunction(question, symbol, extractedFunctions, showDetails);
        }

        bool isCorrect = false;

        if (correctAnswers.count(question)) {
            isCorrect = compareQuestion(question, answer, correctAnswers, showDetails);

        } else if (question.find("instantaneous velocity") != std::string::npos && extractedFunctions.count("x(t)")) {
            isCorrect = compareDerivative(extractedFunctions["x(t)"], answer, showDetails);
            extractedFunctions["dx(t)"] = differentiateFunction(extractedFunctions["x(t)"]);

        } else if (question.find("previously obtained velocity") != std::string::npos && extractedFunctions.count("dx(t)")) {
            isCorrect = compareDerivative(extractedFunctions["dx(t)"], answer, showDetails);

        } else if (question.find("displacement") != std::string::npos && extractedFunctions.count("v(t)")) {
            double finalTime = extractTimeInSeconds(extractedFunctions["t "]);
            if (finalTime < 0) {
                finalTime = std::stod(extractedFunctions["t "]);
            }

            double displacement = integrateNumerically(extractedFunctions["v(t)"], 0.0, finalTime, showDetails);
            double studentAnswer = std::stod(answer);

            isCorrect = std::abs(displacement - studentAnswer) < 0.01;

        } else if (question.find("what is its acceleration") != std::string::npos) {
            isCorrect = calculateAccelerationAndCompare(answer, extractedFunctions, showDetails);

        } else if (question.find("the velocity starting from rest") != std::string::npos &&
                   extractedFunctions.count("a(t)") && extractedFunctions.count("t ")) {
            double finalTime;
            if (extractedFunctions.count("t ")) {
                finalTime = extractTimeInSeconds(extractedFunctions["t "]);
                double velocity = integrateNumerically(extractedFunctions["a(t)"], 0.0, finalTime, showDetails);
                double studentAnswer = std::stod(answer);
                isCorrect = std::abs(velocity - studentAnswer) < 0.01;
            }

        } else if (question.find("kinetic energy at time") != std::string::npos &&
                   extractedFunctions.count("E(t)") &&
                   extractedFunctions.count("P") &&
                   extractedFunctions.count("t ")) {
            double P = std::stod(extractedFunctions.at("P"));
            double time = extractTimeInSeconds(extractedFunctions["t "]);
            std::string exprE = extractedFunctions.at("E(t)");
            isCorrect = correctKineticEnergy(P, time, exprE, answer, showDetails);

        } else if (question.find("Given a force") != std::string::npos &&
                   extractedFunctions.count("F(t)") &&
                   extractedFunctions.count("m ") &&
                   extractedFunctions.count("t ")) {
            std::string F_expr_str = extractedFunctions.at("F(t)");
            double mass = std::stod(extractedFunctions.at("m "));
            double finalTime = extractTimeInSeconds(extractedFunctions["t "]);
            isCorrect = calculateVelocityFromVariableForce(F_expr_str, mass, finalTime, answer, showDetails);
        }

        if (showDetails) {
            std::cout << "Question " << questionNumber << ": " << question << std::endl;
            std::cout << "Student answer: " << answer << std::endl;
        }
        if (showDetails) {
            std::cout << (isCorrect ? "\u2705 Correct answer\n" : "\u274c Incorrect answer\n");
            std::cout << " ----------------------------------\n";
        }
        if (isCorrect) score++;
        questionNumber++;
    }

    if (showDetails) {
        std::cout << "Grade: " << score << std::endl;
    }

    results.push_back({filename, score, questionNumber - 1});
}

void showStudentDetails(const std::string& studentName,
                        const std::vector<StudentResult>& results,
                        const std::map<std::string, std::string>& correctAnswers) {
    for (const auto& res : results) {
        std::string name = fs::path(res.fileName).stem();
        if (name == studentName) {
            // Simply re-run the grading with showDetails = true
            gradeStudentExam(res.fileName, correctAnswers,
                             const_cast<std::vector<StudentResult>&>(results), true);
            return;
        }
    }
    std::cout << "Student not found: " << studentName << "\n";
}



void showCourseSummary(
    const std::vector<StudentResult>& results,
    double passingThreshold,
    const std::set<std::string>& allStudents) {
    
    int totalStudents = results.size();
    if (totalStudents == 0) {
        std::cout << "No data to display.\n";
        return;
    }

    double totalScores = 0.0;
    int passed = 0, failed = 0;
    int maxScore = results[0].score;
    int minScore = results[0].score;

    std::set<std::string> studentsPresent;
    for (const auto& r : results) {
        std::string nameWithoutExtension = std::filesystem::path(r.fileName).stem().string();
        std::string normalizedName = normalizeName(nameWithoutExtension);
        studentsPresent.insert(normalizedName);

        double percentage = static_cast<double>(r.score) / r.totalQuestions;
        totalScores += percentage;

        if (percentage >= passingThreshold)
            passed++;
        else
            failed++;

        if (r.score > maxScore) maxScore = r.score;
        if (r.score < minScore) minScore = r.score;
    }

    double average = (totalScores / totalStudents) * 100;

    std::cout << "\n=== Course Summary ===\n";
    std::cout << "Total students evaluated: " << totalStudents << "\n";
    std::cout << "Overall average: " << average << "%\n";
    std::cout << "Students passed (>= " << passingThreshold * 100 << "%): " << passed << "\n";
    std::cout << "Students failed: " << failed << "\n";
    std::cout << "Highest score obtained: " << maxScore << "/" << results[0].totalQuestions << "\n";
    std::cout << "Lowest score obtained: " << minScore << "/" << results[0].totalQuestions << "\n";

    std::cout << "\nStudents who DID NOT take the exam:\n";
    bool anyAbsent = false;
    for (const auto& name : allStudents) {
        if (studentsPresent.find(name) == studentsPresent.end()) {
            std::cout << "- " << name << "\n";
            anyAbsent = true;
        }
    }
    if (!anyAbsent)
        std::cout << "None, all attended.\n";
}
