#include <iostream>
#include <cmath>
#include <utility>

using namespace std;

std::pair<bool, std::pair<double, double>> solveQuadratic(double a, double b, double c) {
   

    double discriminante = b * b - 4 * a * c;

    if (discriminante >= 0) {
        double x1 = (-b + sqrt(discriminante)) / (2 * a);
        double x2 = (-b - sqrt(discriminante)) / (2 * a);
        return {true, {x1, x2}};
    } else {
        return {false, {0, 0}};
    }
}

int main() {
    double a, b, c;
    cout << "Coeficientes ";
    cin >> a >> b >> c;

    auto result = solveQuadratic(a, b, c);
    cout << (result.first ? "true" : "false") << endl;
    if (result.first) {

        cout << "Solucion: " << result.second.first << " y " << result.second.second << endl;
    } 

    return 0;
}
