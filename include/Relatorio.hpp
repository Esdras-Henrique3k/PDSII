#ifndef RELATORIO_HPP
#define RELATORIO_HPP

#include <vector>
#include "Compra.hpp"

class Relatorio {
public:
    static void gerarRelatorioMensal(const std::vector<Compra>& compras, int mes, int ano);
    static void gerarRelatorioAnual(const std::vector<Compra>& compras, int ano);
    static bool compararPorData(const Compra& a, const Compra& b);
};

#endif