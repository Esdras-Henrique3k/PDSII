#ifndef ALERTA_GASTOS_HPP
#define ALERTA_GASTOS_HPP

#include <iostream>

class AlertaGastos {
private:
    double salario;
    double saldoRestante;
    int diaAtual;

public:
    AlertaGastos(double salarioInicial, double saldoInicial, int dia)
        : salario(salarioInicial), saldoRestante(saldoInicial), diaAtual(dia) {}
        
    void verificarAlerta() const;
    void atualizarSaldo(double novoSaldo);
    void atualizarSalario(double salario);
};

#endif