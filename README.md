# Automated Exam Grading System

This project is a **C++ automated grading system** designed to evaluate student exams involving symbolic math (derivatives, integrals), numerical answers, and true/false questions. It supports detailed and summary reporting per student and identifies students who did not take the exam.

## Features

- 📄 Reads student answers from `.txt` files.
- 🧮 Compares symbolic math answers using **GiNaC**.
- 📐 Evaluates numeric integrals and derivatives.
- ✅ Validates true/false abd multiple-choice responses.
- 📊 Displays general and detailed reports.
- 🚫 Detects absent students based on a master list.

## Project Structure

```plaintext
📁 exam-project/
├── main.cpp # Entry point and menu interface
├── functions.h / functionss.cpp # Core grading and comparison functions
├── utils.h / utils.cpp # Utility functions (e.g., input cleaning, parsing)
├── examenes/ # Folder with student answer files (.txt)
├── Students.txt # List of all expected students
├── correct_answers.txt # File with the correct answers for each question
├── students_grades.txt # Output file with general grades
```

## Dependencies

- **GiNaC** – for symbolic math operations
- **CLN** – required by GiNaC.

For details on how to install Ginac you can check this website [Install GiNaC](https://www.ginac.de/ginac.git/?p=ginac.git;a=blob_plain;f=INSTALL)

## Compile and Run code

To ejecute, first you'll need to compile it. Open up a terminal (if you are using VSCode, hit Ctrl+` or go to Terminal > New Terminal at the top). Then make sure that you are in the corrrect directory and run:

### Option 1: Using Makefile

```bash
  make
  ./exam
```
The Makefile should be configured to compile main.cpp, functions.cpp, and utils.cpp.

### Option 2:  Manually with g++
 ```bash
  g++ -std=c++17 main.cpp functions.cpp utils.cpp -o main -lginac -lcln
  ./main

```

## How to Use
Prepare the list of students in Students.txt (one name per line, without .txt).

Add student answer files to the examenes/ folder (e.g., juan.txt, ana.txt).

Define the correct answers for T/F and multiple choice questions in correct_answers.txt using a format like:

``` cpp
    True/False: The acceleration is constant?;T
    What is the SI unit of force? A-meter B-newton C-kilogram D-pascal;B
```

Use the menu to view general results, details per student, or course summary.



## Sample Questions Supported

Derivatives: d/dt x(t)

Integrals: ∫ₐᵇ f(t) dt

True/False: The acceleration is constant?;T

Kinetic energy problems, variable force with mass, etc.

## Notes
Students' symbolic answers are compared using algebraic simplification.

Numerical answers are compared with a small tolerance.

Absences are detected by checking which students from Students.txt did not submit a file.

## Future Improvements

- 🖥️ Add a GUI using Qt or web-based frontend.
- 📚 Adapt exam logic to support different subjects.

## 📄 License

MIT License – you may use, modify, and distribute this software freely. Attribution appreciated.


