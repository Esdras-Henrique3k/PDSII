#ifndef CONFIGURACAO_HPP
#define CONFIGURACAO_HPP

#include <string>
#include <vector>

class Configuracao {
private:
    std::string nomeUsuario;
    std::string caminho;

public:
    Configuracao(const std::string& nomeUsuario, const std::string& caminho);

    void alterarNome(const std::string& novoNome);
    void alterarSenha(const std::string& novaSenha);
    void alterarSalario(const std::string& novoSalario);
    void excluirConta();

    static void atualizarArquivo(const std::vector<std::string>& usuarios, const std::string& caminho);
};

#endif