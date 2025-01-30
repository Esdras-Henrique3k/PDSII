#include "Configuracao.hpp"
#include "Usuario.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>


Configuracao::Configuracao(const std::string& nomeUsuario, const std::string& caminho)
    : nomeUsuario(nomeUsuario), caminho(caminho) {}

void Configuracao::alterarNome(const std::string& novoNome) {
    std::vector<std::string> usuarios = Usuario::carregarUsuarios(caminho);

    // Verifica se o novo nome já existe
    for (const auto& linha : usuarios) {
        std::stringstream ss(linha);
        std::string nome;
        getline(ss, nome, ';');

        if (nome == novoNome) {
            std::cout << "Erro: O nome de usuário '" << novoNome << "' já está em uso.\n";
            return; // Sai do método sem alterar nada
        }
    }

    // Procura o usuário atual e altera o nome
    for (auto& linha : usuarios) {
        std::stringstream ss(linha);
        std::string nome, senha, salario;
        getline(ss, nome, ';');
        getline(ss, senha, ';');
        getline(ss, salario, ';');

        if (nome == nomeUsuario) {
            linha = novoNome + ";" + senha + ";" + salario;
            nomeUsuario = novoNome; // Atualiza o nome do usuário
            break;
        }
    }

    // Atualiza o arquivo com a nova lista de usuários
    atualizarArquivo(usuarios, caminho);
    std::cout << "Nome alterado com sucesso!\n";
}


void Configuracao::alterarSenha(const std::string& novaSenha) {
    std::vector<std::string> usuarios = Usuario::carregarUsuarios(caminho);
    for (auto& linha : usuarios) {
        std::stringstream ss(linha);
        std::string nome, senha, salario;
        getline(ss, nome, ';');
        getline(ss, senha, ';');
        getline(ss, salario, ';');

        if (nome == nomeUsuario) {
            linha = nome + ";" + novaSenha + ";" + salario;
            break;
        }
    }
    atualizarArquivo(usuarios, caminho);
    std::cout << "Senha alterada com sucesso!\n";
}

void Configuracao::alterarSalario(const std::string& novoSalario) {
    std::vector<std::string> usuarios = Usuario::carregarUsuarios(caminho);
    for (auto& linha : usuarios) {
        std::stringstream ss(linha);
        std::string nome, senha, salario;
        getline(ss, nome, ';');
        getline(ss, senha, ';');
        getline(ss, salario, ';');

        if (nome == nomeUsuario) {
            linha = nome + ";" + senha + ";" + novoSalario;
            break;
        }
    }
    atualizarArquivo(usuarios, caminho);
    std::cout << "Salário alterado com sucesso!\n";
}

void Configuracao::excluirConta() {
    std::vector<std::string> usuarios = Usuario::carregarUsuarios(caminho);
    usuarios.erase(
        std::remove_if(usuarios.begin(), usuarios.end(), [&](const std::string& linha) {
            std::stringstream ss(linha);
            std::string nome;
            getline(ss, nome, ';');
            return nome == nomeUsuario;
        }),
        usuarios.end()
    );
    atualizarArquivo(usuarios, caminho);
    std::cout << "Conta excluída com sucesso!\n";
}

void Configuracao::atualizarArquivo(const std::vector<std::string>& usuarios, const std::string& caminho) {
    std::ofstream arquivo(caminho, std::ios::trunc);
    if (arquivo) {
        for (const auto& usuario : usuarios) {
            arquivo << usuario << "\n";
        }
    } else {
        std::cerr << "Erro ao atualizar o arquivo!" << std::endl;
    }
}