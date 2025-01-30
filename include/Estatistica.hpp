#ifndef ESTATISTICA_HPP
#define ESTATISTICA_HPP

#include <vector>
#include <string>
#include <map>
#include "Compra.hpp"

class Estatistica {
public:
    // Construtor: Recebe uma lista de compras para análise estatística.
    Estatistica(const std::vector<Compra>& compras, float salario);

    // Calcula os gastos por categoria e armazena no mapa.
    void calcularGastosPorCategoria();         

    // Exibe estatísticas gerais, incluindo gastos por categoria e total.
    void exibirEstatisticas();                 

    // Analisa os gastos com base no salário do usuário.
    void analisarComBaseSalario(float salario) const; 

    // Exibe uma comparação dos gastos com o salário informado.
    void exibirComparacaoComSalario(float salario) const; 

private:
    const std::vector<Compra> compras;               // Lista de compras analisadas (imutável)
    std::map<std::string, float> gastosPorCategoria; // Mapa de categoria -> valor gasto
    float totalGasto;                                // Total gasto calculado

    // Calcula o total gasto somando os valores de todas as compras.
    void calcularTotalGasto();      

    float salarioUsuario;        
};

#endif