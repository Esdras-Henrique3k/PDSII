#ifndef ALERTA_GASTOS_HPP
#define ALERTA_GASTOS_HPP

#include <iostream>

class AlertaGastos {
private:
    float salario;
    float saldoRestante;
    int diaAtual;

public:
    AlertaGastos(float salarioInicial, float saldoInicial, int dia)
        : salario(salarioInicial), saldoRestante(saldoInicial), diaAtual(dia) {}
        
    void verificarAlerta() const;
    void atualizarSaldo(float novoSaldo);
    void atualizarSalario(double salario);
};

#endif