#include "Categoria.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>  // Para std::find

namespace fs = std::filesystem;

Categoria::Categoria(const std::string& nomeUsuario) {
    carregarCategoriasPadrao();  // Carrega as categorias padrão inicialmente
    carregarCategorias(nomeUsuario);  // Depois tenta carregar categorias do arquivo
}

void Categoria::carregarCategoriasPadrao() {
    // Categorias pré-definidas
    categorias = {
        "Alimentação", "Transporte", "Saúde", "Lazer", "Educação", "Outros"
    };
}

void Categoria::adicionarCategoria(const std::string& categoria, const std::string& nomeUsuario) {
    // Adiciona a categoria somente se não for uma categoria padrão
    if (!categoriaValida(categoria)) {
        categorias.push_back(categoria);  // Adiciona nova categoria
        salvarCategorias(nomeUsuario);    // Salva após adicionar uma nova categoria
    } else {
        std::cout << "Categoria já existe!" << std::endl;
    }
}

void Categoria::excluirCategoria(const std::string& categoria, const std::string& nomeUsuario) {
    // Não permite excluir categorias padrão
    if (std::find(categorias.begin(), categorias.end(), categoria) != categorias.end() &&
        std::find(categorias.begin(), categorias.begin() + 6, categoria) == categorias.begin() + 6) {
        auto it = std::find(categorias.begin(), categorias.end(), categoria);
        categorias.erase(it);  // Remove categoria
        salvarCategorias(nomeUsuario);  // Salva após remover uma categoria
    } else {
        std::cout << "Não é possível excluir categorias padrão!" << std::endl;
    }
}

bool Categoria::categoriaValida(const std::string& categoria) const {
    return std::find(categorias.begin(), categorias.end(), categoria) != categorias.end();
}

void Categoria::salvarCategorias(const std::string& nomeUsuario) {
    // Verifica se o diretório existe, caso contrário cria
    if (!fs::exists("data")) {
        fs::create_directory("data");
    }

    std::ofstream arquivo("data/categorias-" + nomeUsuario + ".txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para salvar categorias." << std::endl;
        return;
    }

    // Salva as categorias no arquivo, incluindo as padrão e as do usuário
    for (const auto& categoria : categorias) {
        arquivo << categoria << std::endl;  // Salva cada categoria
    }

    arquivo.close();
}

void Categoria::carregarCategorias(const std::string& nomeUsuario) {
    std::ifstream arquivo("data/categorias-" + nomeUsuario + ".txt");
    if (!arquivo.is_open()) return;

    std::string categoria;
    std::vector<std::string> categoriasCarregadas;

    // Carrega as categorias do arquivo, evitando sobrescrever as categorias padrão
    while (std::getline(arquivo, categoria)) {
        if (std::find(categorias.begin(), categorias.end(), categoria) == categorias.end()) {
            categoriasCarregadas.push_back(categoria);  // Carrega categoria não padrão
        }
    }

    arquivo.close();

    // Adiciona as categorias carregadas após as pré-definidas
    categorias.insert(categorias.end(), categoriasCarregadas.begin(), categoriasCarregadas.end());
}

std::vector<std::string> Categoria::obterCategorias() const {
    return categorias;  // Retorna o vetor de categorias
}