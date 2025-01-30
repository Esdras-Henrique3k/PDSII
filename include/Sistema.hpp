#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include "Usuario.hpp"
#include "Operacoes.hpp"

class Sistema {
public:
    void iniciar(); 

private:
    void exibirMenuPrincipal(); // Exibe o menu principal
    void criarUsuario();        // Função para criar um novo usuário
    void fazerLogin();          // Função para realizar login
    void menuCompras(Operacoes& operacoes); // Menu de compras
    void gerarRelatorio(Operacoes& operacoes); // Geração de relatórios
    void exibirEstatisticas(Operacoes& operacoes);
    std::string salarioUsuario;
    std::string usuarioLogado;
};

#endif