#include "ParcelaCompra.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Operacoes.hpp"

bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0;
    }
}

std::string addOneMonth(const std::string& date) {
    int day, month, year;
    std::stringstream ss(date);
    char slash;
    ss >> day >> slash >> month >> slash >> year;

    if (month == 12) {
        month = 1;
        year++;
    } else {
        month++;
    }

    int maxDaysInMonth = daysInMonth(month, year);
    if (day > maxDaysInMonth) {
        day = maxDaysInMonth;
    }

    std::stringstream result;
    result << std::setfill('0') << std::setw(2) << day << "/"
           << std::setfill('0') << std::setw(2) << month << "/"
           << year;

    return result.str();
}


void ParcelaCompra::ParcelarCompra(double valor, const std::string& categoriaEscolhida, const std::string &data, int numParcelas, Operacoes &operacoes)
{
    double parcelasValue = valor / numParcelas;
    std::string parcelaData = data;

    for (int i = 0; i < numParcelas; i++)
    {
        Compra compra(parcelasValue, categoriaEscolhida, parcelaData);
        operacoes.addCompra(compra);
        parcelaData = addOneMonth(parcelaData);
        std::cout << "Parcela " << i + 1 << ": R$ " << std::fixed << std::setprecision(2) << parcelasValue << "\n";
    }
}