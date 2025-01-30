#include "Usuario.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Usuario::Usuario(const std::string& nome, const std::string& senha, const std::string& salario)
    : nome(nome), senha(senha), salario(salario) {}

std::string Usuario::criarUsuario() const {
    std::ostringstream oss;
    oss << nome << ";" << senha << ";" << salario;
    return oss.str();
}

void Usuario::salvarUsuario(const std::string& dados, const std::string& caminho) {
    std::ofstream arquivo(caminho, std::ios::app);
    if (arquivo) {
        arquivo << dados << "\n";
    } else {
        std::cerr << "Erro ao salvar o usuário!" << std::endl;
    }
}

std::vector<std::string> Usuario::carregarUsuarios(const std::string& caminho) {
    std::vector<std::string> usuarios;
    std::ifstream arquivo(caminho);
    std::string linha;
    while (getline(arquivo, linha)) {
        usuarios.push_back(linha);
    }
    return usuarios;
}

bool Usuario::validarUsuario(const std::string& nome, const std::string& senha, 
                             const std::vector<std::string>& usuarios, std::string& salario) {
    for (const auto& usuario : usuarios) {
        std::stringstream ss(usuario);
        std::string nomeArquivo, senhaArquivo, salarioArquivo;
        getline(ss, nomeArquivo, ';');
        getline(ss, senhaArquivo, ';');
        getline(ss, salarioArquivo, ';');

        if (nomeArquivo == nome && senhaArquivo == senha) {
            salario = salarioArquivo;
            return true;
        }
    }
    return false;
}


bool Usuario::usuarioExistente(const std::string& nome, const std::vector<std::string>& usuarios) {
    for (const auto& usuario : usuarios) {
        std::stringstream ss(usuario);
        std::string nomeArquivo;
        getline(ss, nomeArquivo, ';');
        if (nomeArquivo == nome) {
            return true;  // Usuário já existe
        }
    }
    return false;  // Usuário não encontrado
}