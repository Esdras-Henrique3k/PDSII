#ifndef CATEGORIA_HPP
#define CATEGORIA_HPP

#include <vector>
#include <string>

class Categoria {
public:
    explicit Categoria(const std::string& nome);
    
    void adicionarCategoria(const std::string& categoria, const std::string& nomeUsuario);
    void excluirCategoria(const std::string& categoria, const std::string& nomeUsuario);
    bool categoriaValida(const std::string& categoria) const;
    
    void salvarCategorias(const std::string& nomeUsuario);
    void carregarCategorias(const std::string& nomeUsuario);

    // Agora pública para ser usada em Compra.cpp
    std::vector<std::string> obterCategorias() const;

private:
    std::vector<std::string> categorias; // Adiciona o atributo faltando
    void carregarCategoriasPadrao();
};

#endif