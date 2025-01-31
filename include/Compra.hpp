#ifndef COMPRA_HPP
#define COMPRA_HPP

#include <string>
#include <vector>
#include "Categoria.hpp"

class Compra {
private:
    double valor;
    std::string categoria;
    std::string data;

public:
    Compra(double valor, const std::string& categoria, const std::string& data);

    // Adicione um destrutor virtual
    virtual ~Compra() = default;

    double getValor() const;
    std::string getCategoria() const;
    std::string getData() const;

    static bool categoriaValida(int opcao, const Categoria& categoriaManager);
};

#endif