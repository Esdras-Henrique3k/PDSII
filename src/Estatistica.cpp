#include "Estatistica.hpp"
#include <iostream>
#include <iomanip>
#include "Sistema.hpp"
#include "Operacoes.hpp"

Estatistica::Estatistica(const std::vector<Compra>& compras, double salario) 
    : compras(compras), totalGasto(0.0f), salarioUsuario(salario) {}

void Estatistica::calcularTotalGasto() {
    totalGasto = 0.0f;
    for (const auto& compra : compras) {
        totalGasto += compra.getValor();
    }
}

void Estatistica::analisarComBaseSalario(double salario) const {
    if (gastosPorCategoria.empty() || salario <= 0) {
        std::cout << "Nenhum dado para análise ou salário inválido." << std::endl;
        return;
    }

    std::cout << "--- Comparação com Salário ---" << std::endl;
    for (const auto& [categoria, valor] : gastosPorCategoria) {
        double porcentagemSalario = (valor / salario) * 100;
        std::cout << "Categoria: " << categoria 
                  << " - " << std::fixed << std::setprecision(2) << porcentagemSalario
                  << "% do salário" << std::endl;
    }
}

void Estatistica::exibirEstatisticas() {
    calcularGastosPorCategoria();

    std::cout << "--- Estatísticas de Gastos ---\n";
    std::cout << "Total gasto: R$ " << totalGasto << "\n";

    for (const auto& [categoria, valor] : gastosPorCategoria) {
        double porcentagem = (valor / totalGasto) * 100;
        std::cout << "Categoria: " << categoria
                  << " - R$ " << valor
                  << " (" << std::fixed << std::setprecision(2) << porcentagem << "%)\n";
    }

    std::cout << "\n--- Comparação com Salário ---\n";
    for (const auto& [categoria, valor] : gastosPorCategoria) {
        double porcentagemSalario = (valor / salarioUsuario) * 100;
        std::cout << "Categoria: " << categoria 
                  << " - " << std::fixed << std::setprecision(2) << porcentagemSalario
                  << "% do salário" << std::endl;
    }
}


void Estatistica::exibirComparacaoComSalario(double salario) const {
    std::cout << "--- Comparação com Salário ---" << std::endl;
    for (const auto& [categoria, valor] : gastosPorCategoria) {
        double porcentagemSalario = (valor / salario) * 100;
        std::cout << "Categoria: " << categoria 
                  << " - " << std::fixed << std::setprecision(2) << porcentagemSalario
                  << "% do salário" << std::endl;
    }
}

void Estatistica::calcularGastosPorCategoria() {
    gastosPorCategoria.clear(); // Limpa o mapa para evitar duplicação de valores
    totalGasto = 0.0f;          // Reinicia o total

    for (const auto& compra : compras) {
        double valor = compra.getValor();
        std::string categoria = compra.getCategoria();

        // Soma ao total e atualiza a categoria
        totalGasto += valor;
        gastosPorCategoria[categoria] += valor;
    }
}