#include "Compra.hpp"

Compra::Compra(double valor, const std::string& categoria, const std::string& data)
    : valor(valor), categoria(categoria), data(data) {}

double Compra::getValor() const {
    return valor;
}

std::string Compra::getCategoria() const {
    return categoria;
}

std::string Compra::getData() const {
    return data;
}

bool Compra::categoriaValida(int opcao, const Categoria& categoriaManager) {
    return opcao > 0 && opcao <= static_cast<int>(categoriaManager.obterCategorias().size());
}