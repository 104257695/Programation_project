#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <CLI/CLI.hpp>
#include <barkeep/barkeep.h>  
#include <CLI/CLI.hpp>


int main(int argc, char** argv) {
    CLI::App app{"Data Analytics Retail"};

    std::string countryFilter;
    bool onlyUK = false;

    app.add_option("-c,--country", countryFilter, "Country to filter transactions");
    app.add_flag("--only-uk", onlyUK, "Calculate only UK transactions");

    CLI11_PARSE(app, argc, argv);

    // Abrir archivo de datos (usa tu ruta)
    std::ifstream file("OnlineRetail.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    // Contadores
    std::unordered_map<std::string, int> countryCounts;
    double totalAmount = 0.0;

    // Configura la barra de progreso Barkeep
    barkeep::ProgressBar bar;
    bar.setMax(100); // pon un valor adecuado según tu dataset

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        lineNumber++;
        // Aquí parsea tu línea CSV para extraer país, monto, etc.
        // Ejemplo ficticio:
        std::string country = "UK";  // extraer país de la línea real
        double amount = 10.0;         // extraer monto real

        if ((!countryFilter.empty() && country != countryFilter))
            continue;

        if (onlyUK && country != "UK")
            continue;

        countryCounts[country]++;
        totalAmount += amount;

        // Actualiza barra de progreso
        bar.setProgress(lineNumber * 100 / 1000); // ajusta 1000 al total de líneas reales
    }

    bar.finish();

    if (!countryFilter.empty()) {
        std::cout << "Transactions in " << countryFilter << ": " << countryCounts[countryFilter] << "\n";
    } else {
        std::cout << "Transactions per country:\n";
        for (auto& [c, count] : countryCounts)
            std::cout << c << ": " << count << "\n";
    }

    if (onlyUK) {
        std::cout << "Total amount for UK: " << totalAmount << "\n";
    } else {
        std::cout << "Total amount (all): " << totalAmount << "\n";
    }

    return 0;
}
