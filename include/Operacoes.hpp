#ifndef OPERACOES_HPP
#define OPERACOES_HPP

#include <vector>
#include <string>
#include "Compra.hpp"
#include "Categoria.hpp"
#include "AlertaGastos.hpp"

class Operacoes {
private:
    std::vector<Compra> compras; 
    std::string nomeUsuario; // Nome do usuário associado
    Categoria categoria; 
    double saldoDisponivel;  // Saldo disponível do usuário
    double salarioUsuario;   // Salário do usuário
    int diaAtual;           // Dia atual do sistema
    AlertaGastos alertaGastos;

public:
    Operacoes(double salario, double saldo, int dia);
    Operacoes(const std::string& nomeUsuario);
    Operacoes(const std::string& nomeUsuario, double salario, double saldo);
    double calcularGastosMensais();

    void addCompra(const Compra& compra);
    void listarCompras();
    const std::vector<Compra>& getCompras() const;

    void carregarCompras();
    void salvarCompras();
    void menuCompras();
    void adicionarCompra(double salario);

    void mudarCategorias();
    void adicionarCategoria();
    void removerCategoria();
    void listarCategorias();

    std::string getUsuario() const;  
    void setUsuario(const std::string& novoNome);

    void atualizarSaldo(double novoSaldo);
    void atualizarAlertaGastos(double saldo, double salario);
};

#endif