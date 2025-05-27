# Automated Exam Grading System

This project is a **C++ automated grading system** designed to evaluate student exams involving symbolic math (derivatives, integrals), numerical answers, and true/false questions. It supports detailed and summary reporting per student and identifies students who did not take the exam.

## Features

- Reads student answers from `.txt` files.
- Compares symbolic math answers using **GiNaC**.
- Evaluates numeric integrals and derivatives.
- Validates true/false responses.
- Displays general and detailed reports.
- Detects absent students based on a master list.

## Project Structure

📁 exam-project/
├── main.cpp # Entry point and menu interface
├── funciones.h / funciones.cpp # Core grading and comparison functions
├── utils.h / utils.cpp # Utility functions (e.g., input cleaning, parsing)
├── examenes/ # Folder with student answer files (.txt)
├── Estudiantes.txt # List of all expected students
├── respuestas_correctas.txt # File with the correct answers for each question
├── notas_estudiantes.txt # Output file with general grades

markdown
Copiar
Editar

## Dependencies

- **GiNaC** – for symbolic math operations
- **C++17** – uses `<filesystem>`

### Installation (Linux/macOS)

Make sure you have `g++` and GiNaC installed:

```bash
sudo apt install libginac-dev g++ make
Then compile the project:

bash
Copiar
Editar
make
The Makefile should be configured to compile main.cpp, funciones.cpp, and utils.cpp.

How to Use
Prepare the list of students in Estudiantes.txt (one name per line, without .txt).

Add student answer files to the examenes/ folder (e.g., juan.txt, ana.txt).

Define correct answers in respuestas_correctas.txt using a format like:

cpp
Copiar
Editar
¿Qué es la derivada de x^2?::2*x
Calcule ∫0^1 t^2 dt::0.333
La aceleración es constante::true
Run the program:

bash
Copiar
Editar
./examen
Use the menu to view general results, details per student, or course summary.

Example Output
pgsql
Copiar
Editar
--- MENU ---
1. Show all student scores
2. View details of a specific student
3. Show course summary
4. Exit
Sample Questions Supported
Derivatives: d/dt x(t)

Integrals: ∫ₐᵇ f(t) dt

True/False: "The acceleration is constant"::true

Kinetic energy problems, variable force with mass, etc.

Notes
Students' symbolic answers are compared using algebraic simplification.

Numerical answers are compared with a small tolerance.

Absences are detected by checking which students from Estudiantes.txt did not submit a file.

Future Improvements
Add support for multi-language questions and UI (e.g., English/Spanish).

Export results in CSV or Excel format.

Add a GUI using Qt or web-based frontend.

License
MIT License – use freely with attribution.

