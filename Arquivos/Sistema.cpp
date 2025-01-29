#include <iostream>
#include "Sistema.hpp"
#include "Usuario.hpp"
#include "Operacoes.hpp"
#include "Relatorio.hpp"
#include "Estatistica.hpp"
#include "Configuracao.hpp"
#include <limits>

void Sistema::iniciar() {
    while (true) {
        exibirMenuPrincipal();
    }
}

void Sistema::exibirMenuPrincipal() {
     while(true){
        std::cout << "--- Bem-vindo ao Sistema de Controle Financeiro ---\n";
        std::cout << "1. Criar usuário\n2. Fazer login\n3. Sair\nEscolha uma opção: ";
        
        int opcao;
        std::cin >> opcao;
         if (std::cin.fail())
         {
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Entrada inválida! Por favor, insira um número." << std::endl;
             continue;
         }
        std::cin.ignore();
        if (opcao == 1) {
            criarUsuario();
            // break;
        } else if (opcao == 2) {
            fazerLogin();
            // break;
        } else if (opcao == 3) {
            std::cout << "Saindo... Até mais!\n";
            exit(0); // Saída do programa
        } else {
            std::cout << "Opção inválida!\n";
        }
     }
}

void Sistema::criarUsuario() {
    std::string nome, senha, salario;

    // Solicitar nome, senha e salário
    std::cout << "Digite o nome do novo usuário: ";
    std::getline(std::cin, nome);

    std::cout << "Digite a senha: ";
    std::getline(std::cin, senha);

    std::cout << "Digite seu salário mensal em reais: ";
    std::getline(std::cin, salario);

    // Carregar os usuários existentes
    std::vector<std::string> usuarios = Usuario::carregarUsuarios("data/usuarios.txt");

    // Verificar se o usuário já existe
    if (Usuario::usuarioExistente(nome, usuarios)) {
        std::cout << "Usuário já existe!\n";
    } else {
        // Criar o novo usuário com nome, senha e salário
        Usuario novoUsuario(nome, senha, salario);
        std::string dados = novoUsuario.criarUsuario();

        // Salvar o novo usuário no arquivo
        Usuario::salvarUsuario(dados, "data/usuarios.txt");
        std::cout << "Usuário criado com sucesso!\n";
    }
}


void Sistema::fazerLogin() {
    std::string nome, senha;

    std::cout << "Digite o nome de usuário: ";
    std::getline(std::cin, nome);

    std::cout << "Digite a senha: ";
    std::getline(std::cin, senha);

    std::vector<std::string> usuarios = Usuario::carregarUsuarios("data/usuarios.txt");

    std::string salario;
    if (Usuario::validarUsuario(nome, senha, usuarios, salario)) {
        std::cout << "Bem-vindo, " << nome << "!\n";
        std::cout << "Salário Mensal: R$ " << salario << "\n";

        // **Armazena o nome e o salário do usuário logado**
        this->usuarioLogado = nome;
        this->salarioUsuario = salario; 

        Operacoes operacoes(nome);
        operacoes.carregarCompras();

        // Calcular saldo disponível
        double salarioDouble = std::stod(salario); // Converte string para double
        double gastosMensais = operacoes.calcularGastosMensais();
        double saldoDisponivel = salarioDouble - gastosMensais;

        std::cout << "Saldo Disponível: R$ " << saldoDisponivel << "\n";

        menuCompras(operacoes);
    } else {
        std::cout << "Usuário ou senha incorretos!\n";
    }
}



void Sistema::menuCompras(Operacoes& operacoes) {
    while (true) {
        std::cout << "\n--- Menu de Compras ---\n"
                  << "1. Adicionar compra\n"
                  << "2. Listar compras\n"
                  << "3. Gerar relatório\n"
                  << "4. Ver estatísticas\n"
                  << "5. Mudar categorias\n"
                  << "6. Configuração\n"
                  << "7. Logout\n"
                  << "Escolha uma opção: ";
        int escolha;
        std::cin >> escolha;
        std::cin.ignore();  // Limpa o buffer de entrada

        if (escolha == 1) {
            operacoes.adicionarCompra();
        } else if (escolha == 2) {
            operacoes.listarCompras();
        } else if (escolha == 3) {
            gerarRelatorio(operacoes);
        } else if (escolha == 4) {
            exibirEstatisticas(operacoes);
        } else if (escolha == 5) {
            operacoes.mudarCategorias();
        } else if (escolha == 6) {
            Configuracao configuracao(operacoes.getUsuario(), "data/usuarios.txt");
            while (true) {
                std::cout << "\n--- Configuração ---\n"
                          << "1. Alterar nome\n"
                          << "2. Alterar senha\n"
                          << "3. Alterar salário\n"
                          << "4. Excluir conta\n"
                          << "5. Voltar\n"
                          << "Escolha uma opção: ";
                int opcao;
                std::cin >> opcao;
                std::cin.ignore();

                if (opcao == 1) {
                    std::string novoNome;
                    std::cout << "Digite o novo nome: ";
                    std::getline(std::cin, novoNome);
                    configuracao.alterarNome(novoNome);
                } else if (opcao == 2) {
                    std::string novaSenha;
                    std::cout << "Digite a nova senha: ";
                    std::getline(std::cin, novaSenha);
                    configuracao.alterarSenha(novaSenha);
                } else if (opcao == 3) {
                    std::string novoSalario;
                    std::cout << "Digite o novo salário: ";
                    std::getline(std::cin, novoSalario);
                    configuracao.alterarSalario(novoSalario);
                } else if (opcao == 4) {
                    configuracao.excluirConta();
                    std::cout << "Conta excluída. Retornando ao menu principal.\n";
                    return;
                } else if (opcao == 5) {
                    break;
                } else {
                    std::cout << "Opção inválida!\n";
                }
            }
        } else if (escolha == 7) {
            break;  // Logout
        } else {
            std::cout << "Opção inválida!" << std::endl;
        }
    }
}


void Sistema::gerarRelatorio(Operacoes& operacoes) {
    std::cout << "Deseja gerar um relatório mensal ou anual? (1 para mensal, 2 para anual, 0 para não gerar): ";
    int relatorioEscolha;
    std::cin >> relatorioEscolha;
    std::cin.ignore();

    if (relatorioEscolha == 1) {
        int mes, ano;
        std::cout << "Digite o mês (1-12): ";
        std::cin >> mes;
        std::cout << "Digite o ano: ";
        std::cin >> ano;
        std::cin.ignore();
        Relatorio::gerarRelatorioMensal(operacoes.getCompras(), mes, ano);
    } else if (relatorioEscolha == 2) {
        int ano;
        std::cout << "Digite o ano: ";
        std::cin >> ano;
        std::cin.ignore();
        Relatorio::gerarRelatorioAnual(operacoes.getCompras(), ano);
    } else {
        std::cout << "Não foi gerado nenhum relatório.\n";
    }
}

void Sistema::exibirEstatisticas(Operacoes& operacoes) {
    std::cout << "--- Estatísticas de Gastos ---\n";

    if (salarioUsuario.empty()) {
        std::cout << "Erro: Nenhum usuário logado!\n";
        return;
    }

    int periodo;
    std::cout << "Escolha o período para as estatísticas:\n";
    std::cout << "1. Mensal\n2. Anual\nEscolha uma opção: ";
    std::cin >> periodo;
    std::cin.ignore();

    int mes = 0, ano = 0;
    if (periodo == 1) {
        std::cout << "Digite o mês (1-12): ";
        std::cin >> mes;
        std::cout << "Digite o ano: ";
        std::cin >> ano;
    } else if (periodo == 2) {
        std::cout << "Digite o ano: ";
        std::cin >> ano;
    } else {
        std::cout << "Opção inválida!\n";
        return;
    }

    // Filtra as compras com base no período escolhido
    std::vector<Compra> comprasFiltradas;
    for (const auto& compra : operacoes.getCompras()) {
        int compraDia = 0, compraMes = 0, compraAno = 0;
        std::sscanf(compra.getData().c_str(), "%d/%d/%d", &compraDia, &compraMes, &compraAno);

        if ((periodo == 1 && compraMes == mes && compraAno == ano) || 
            (periodo == 2 && compraAno == ano)) {
            comprasFiltradas.push_back(compra);
        }
    }

    // Converte o salário armazenado para float e passa para Estatistica
    float salario = std::stof(salarioUsuario);
    Estatistica estatistica(comprasFiltradas, salario);
    estatistica.exibirEstatisticas();
}