#include "Compra.hpp"
#include "Relatorio.hpp"
#include <iostream>
#include <iomanip> // Para std::fixed e std::setprecision
#include <sstream> // Para manipular strings
#include <algorithm> // Para std::sort

bool Relatorio::compararPorData(const Compra& a, const Compra& b) {
    auto parseData = [](const std::string& data) {
        int dia, mes, ano;
        char sep1, sep2;
        std::istringstream iss(data);
        iss >> dia >> sep1 >> mes >> sep2 >> ano;
        return std::tuple(ano, mes, dia);
    };
    return parseData(a.getData()) < parseData(b.getData());
}

void Relatorio::gerarRelatorioMensal(const std::vector<Compra>& compras, int mes, int ano) {
    double total = 0.0;

    std::cout << "\n--- Relatório Mensal ---\n";
    std::vector<Compra> comprasFiltradas;

    for (const auto& compra : compras) {
        std::string data = compra.getData();
        int dia, mesCompra, anoCompra;
        char separador1, separador2;

        std::istringstream iss(data);
        if (iss >> dia >> separador1 >> mesCompra >> separador2 >> anoCompra &&
            separador1 == '/' && separador2 == '/') {
            if (mesCompra == mes && anoCompra == ano) {
                comprasFiltradas.push_back(compra);
                total += compra.getValor();
            }
        }
    }

    // Ordenar as compras filtradas por data
    std::sort(comprasFiltradas.begin(), comprasFiltradas.end(), compararPorData);

    // Exibir as compras
    for (const auto& compra : comprasFiltradas) {
        std::cout << "Valor: R$ " << std::fixed << std::setprecision(2) << compra.getValor()
                  << ", Categoria: " << compra.getCategoria()
                  << ", Data: " << compra.getData() << "\n";
    }

    std::cout << "Total do mês " << mes << "/" << ano << ": R$ " << std::fixed << std::setprecision(2) << total << "\n";
}

void Relatorio::gerarRelatorioAnual(const std::vector<Compra>& compras, int ano) {
    double total = 0.0;

    std::cout << "\n--- Relatório Anual ---\n";
    std::vector<Compra> comprasFiltradas;

    for (const auto& compra : compras) {
        std::string data = compra.getData();
        int dia, mesCompra, anoCompra;
        char separador1, separador2;

        std::istringstream iss(data);
        if (iss >> dia >> separador1 >> mesCompra >> separador2 >> anoCompra &&
            separador1 == '/' && separador2 == '/') {
            if (anoCompra == ano) {
                comprasFiltradas.push_back(compra);
                total += compra.getValor();
            }
        }
    }

    // Ordenar as compras filtradas por data
    std::sort(comprasFiltradas.begin(), comprasFiltradas.end(), compararPorData);

    // Exibir as compras
    for (const auto& compra : comprasFiltradas) {
        std::cout << "Valor: R$ " << std::fixed << std::setprecision(2) << compra.getValor()
                  << ", Categoria: " << compra.getCategoria()
                  << ", Data: " << compra.getData() << "\n";
    }

    std::cout << "Total do ano " << ano << ": R$ " << std::fixed << std::setprecision(2) << total << "\n";
}
