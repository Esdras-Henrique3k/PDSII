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
    float saldoDisponivel;  // Saldo disponível do usuário
    float salarioUsuario;   // Salário do usuário
    int diaAtual;           // Dia atual do sistema
    AlertaGastos alertaGastos;

public:
    Operacoes(float salario, float saldo, int dia);
    Operacoes(const std::string& nomeUsuario);
    Operacoes(const std::string& nomeUsuario, float salario, float saldo);
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

    void atualizarSaldo(float novoSaldo);
    void atualizarAlertaGastos(double saldo, double salario);
};

#endif