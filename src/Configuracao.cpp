#include "Configuracao.hpp"
#include "Usuario.hpp"
#include "Utils.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>  
#include <filesystem>

Configuracao::Configuracao(const std::string& nomeUsuario, const std::string& caminho)
    : nomeUsuario(nomeUsuario), caminho(caminho) {}

#include <filesystem> // Biblioteca para manipulação de arquivos

void Configuracao::alterarNome(const std::string& novoNome) {
    if (!validarNome(novoNome)) {
        std::cout << "Erro: Nome inválido! Use apenas letras e espaços.\n";
        return;
    }

    std::vector<std::string> usuarios = Usuario::carregarUsuarios(caminho);

    // Verifica se o novo nome já existe
    for (const auto& linha : usuarios) {
        std::stringstream ss(linha);
        std::string nome;
        getline(ss, nome, ';');

        if (nome == novoNome) {
            std::cout << "Erro: O nome de usuário '" << novoNome << "' já está em uso.\n";
            return;
        }
    }

    // Caminhos dos arquivos antigos
    std::string comprasAntigo = "data/compras-" + nomeUsuario + ".txt";
    std::string categoriasAntigo = "data/categorias-" + nomeUsuario + ".txt";

    // Caminhos dos arquivos novos
    std::string comprasNovo = "data/compras-" + novoNome + ".txt";
    std::string categoriasNovo = "data/categorias-" + novoNome + ".txt";

    // **PASSO 1: Criar novos arquivos e transferir os dados**
    std::ifstream arquivoComprasAntigo(comprasAntigo);
    std::ofstream arquivoComprasNovo(comprasNovo);
    if (arquivoComprasAntigo && arquivoComprasNovo) {
        arquivoComprasNovo << arquivoComprasAntigo.rdbuf(); // Copia os dados
    }
    arquivoComprasAntigo.close();
    arquivoComprasNovo.close();

    std::ifstream arquivoCategoriasAntigo(categoriasAntigo);
    std::ofstream arquivoCategoriasNovo(categoriasNovo);
    if (arquivoCategoriasAntigo && arquivoCategoriasNovo) {
        arquivoCategoriasNovo << arquivoCategoriasAntigo.rdbuf();
    }
    arquivoCategoriasAntigo.close();
    arquivoCategoriasNovo.close();

    // **PASSO 2: Atualizar o nome do usuário no sistema**
    for (auto& linha : usuarios) {
        std::stringstream ss(linha);
        std::string nome, senha, salario;
        getline(ss, nome, ';');
        getline(ss, senha, ';');
        getline(ss, salario, ';');

        if (nome == nomeUsuario) {
            linha = novoNome + ";" + senha + ";" + salario;
            break;
        }
    }

    // Atualiza a variável global nomeUsuario
    nomeUsuario = novoNome;

    // Atualiza o arquivo de usuários
    atualizarArquivo(usuarios, caminho);

    // **PASSO 3: Apagar arquivos antigos**
    std::vector<std::string> arquivosParaRemover = {comprasAntigo, categoriasAntigo};
    for (const auto& arquivo : arquivosParaRemover) {
        if (std::filesystem::exists(arquivo)) {
            std::filesystem::remove(arquivo);
            std::cout << "Arquivo antigo removido: " << arquivo << std::endl;
        }
    }

    std::cout << "Nome alterado com sucesso! Dados transferidos e arquivos antigos removidos.\n";
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
    // Validação do salário
    if (!validarSalario(novoSalario)) {
        std::cout << "Erro: Salário inválido! Use apenas números.\n";
        return;
    }

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