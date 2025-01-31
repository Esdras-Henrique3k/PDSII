#include "TxtToExcelExporter.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <filesystem>

namespace fs = std::filesystem;

double convertToDouble(const std::string& valueStr) {
    try {
        size_t pos;
        double value = std::stod(valueStr, &pos);

        if (pos != valueStr.size()) {
            std::cerr << "Aviso: Número inválido detectado '" << valueStr << "'" << std::endl;
            return 0.0;
        }

        if (value > std::numeric_limits<double>::max() || value < -std::numeric_limits<double>::max()) {
            std::cerr << "Erro: Valor fora dos limites aceitáveis '" << valueStr << "'" << std::endl;
            return 0.0;
        }

        return value;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao converter valor '" << valueStr << "': " << e.what() << std::endl;
        return 0.0;
    }
}

void TxtToExcelExporter::exportToCsv(const std::string& userName, const std::string& outputDir) {
    std::string appDir = fs::current_path().string();

    std::string filePath = appDir + "/data/compras-" + userName + ".txt";
    std::string csvFileName = outputDir + "/compras-" + userName + ".csv";


    if (!fs::exists(outputDir)) {
        fs::create_directories(outputDir);
    }

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo " << filePath << std::endl;
        return;
    }

    std::ofstream csvFile(csvFileName);
    if (!csvFile.is_open()) {
        std::cerr << "Erro ao criar o arquivo CSV no diretório " << outputDir << std::endl;
        file.close();
        return;
    }

    csvFile << "Valor,Categoria,Data\n";

    std::string line;
    int lineCount = 0;

    while (std::getline(file, line)) {
        lineCount++;

        std::stringstream ss(line);
        std::string valorStr, categoria, data;

        if (!(std::getline(ss, valorStr, ';') && std::getline(ss, categoria, ';') && std::getline(ss, data))) {
            std::cerr << "Aviso: Linha inválida ignorada (" << lineCount << "): " << line << std::endl;
            continue;
        }

        double valor = convertToDouble(valorStr);
        csvFile << std::fixed << std::setprecision(2) << valor << "," 
                << categoria << "," 
                << data << "\n";
    }

    file.close();
    csvFile.close();

    std::cout << "Arquivo CSV criado com sucesso em: " << csvFileName << std::endl;
}
