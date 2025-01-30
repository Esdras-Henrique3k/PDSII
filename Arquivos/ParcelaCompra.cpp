 #include "ParcelaCompra.hpp"
 #include <cmath>       // Para arredondamento
 #include <stdexcept>   // Para exceções como std::out_of_range

 ParcelaCompra::ParcelaCompra(float valor, const std::string& categoria, const std::string& data, int numParcelas)
     : Compra(valor, categoria, data), numParcelas(numParcelas) {
     if (valor <= 0.0f) {
         throw std::invalid_argument("O valor total deve ser maior que zero.");
     }
     if (numParcelas <= 0) {
         throw std::invalid_argument("O número de parcelas deve ser maior que zero.");
     }

     float valorParcela = std::round((valor / numParcelas) * 100) / 100.0f; // Arredondar para 2 casas decimais
     for (int i = 0; i < numParcelas; ++i) {
         valoresParcelas.push_back(valorParcela);
     }

     // Ajusta o valor da última parcela caso haja diferença devido ao arredondamento
     float totalParcelado = valorParcela * numParcelas;
     if (totalParcelado != valor) {
         valoresParcelas.back() += valor - totalParcelado;
     }
 }

 int ParcelaCompra::getNumParcelas() const {
     return numParcelas;
 }

 std::vector<float> ParcelaCompra::getValoresParcelas() const {
     return valoresParcelas;
 }

 float ParcelaCompra::getValorParcela(int index) const {
     if (index >= 0 && index < numParcelas) {
         return valoresParcelas[index];
     }
     throw std::out_of_range("Índice de parcela inválido");
 }