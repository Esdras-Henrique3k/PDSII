#ifndef PARCELACOMPRA_HPP
#define PARCELACOMPRA_HPP

#include "Compra.hpp"
#include <vector>
#include <string>
#include "Operacoes.hpp"

class ParcelaCompra
{
public:
    static void ParcelarCompra(double valor, const std::string& categoriaEscolhida, const std::string& data, int numParcelas, Operacoes& operacoes);
};

#endif