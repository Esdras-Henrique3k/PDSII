#include "AlertaGastos.hpp"
#include <iostream>

void AlertaGastos::atualizarSalario(double salario) {
    this->salario = salario;  // Atualiza o salário
}

void AlertaGastos::atualizarSaldo(double novoSaldo) {
    this->saldoRestante = novoSaldo;  // Atualiza o saldo restante
}

void AlertaGastos::verificarAlerta() const {
    // Limites de alerta baseados no salário
    double limiteCritico = salario * 0.1;  // Se gastar mais de 90% do salário


    // Verifica o saldo e gera alertas
    if (saldoRestante < 0) {  // Saldo negativo
         std::cout << "[ALERTA] Você ultrapassou seu saldo! Evite novas compras.\n";
    } else if (saldoRestante == 0) {  // Saldo exatamente zerado
        std::cout << "[ALERTA] Você utilizou todo o seu saldo! Gerencie bem seus próximos gastos.\n";
    } else if (saldoRestante <= limiteCritico) {  // Saldo próximo ao crítico
         std::cout << "[ALERTA] Seu saldo está quase esgotado! Planeje seus gastos.\n";
    }   
}