#include <iostream>
#include <regex>
#include "Sistema.hpp"
#include "TxtToExcelExporter.hpp"
#include "Usuario.hpp"
#include "Operacoes.hpp"
#include "Relatorio.hpp"
#include "Estatistica.hpp"
#include "Configuracao.hpp"
#include "Utils.hpp"

void Sistema::iniciar() {
    while (true) {
        exibirMenuPrincipal();
    }
}

void Sistema::exibirMenuPrincipal() {
    while (true) {
        std::cout << "\n--- Bem-vindo ao Sistema de Controle Financeiro ---\n";
        std::cout << "1. Criar usuário\n2. Fazer login\n3. Sair\nEscolha uma opção: ";

        int opcao;
        std::cin >> opcao;

        // Verifica se a entrada falhou
        if (std::cin.fail()) {
            limparEntrada(); // Limpa a entrada
            std::cout << "Opção inválida! Tente novamente.\n";
            continue;
        }

        std::cin.ignore();

        if (opcao == 1) {
            criarUsuario();
        } else if (opcao == 2) {
            fazerLogin();
        } else if (opcao == 3) {
            std::cout << "Saindo... Até mais!\n";
            exit(0);
        } else {
            std::cout << "Opção inválida! Tente novamente.\n";
        }
    }
}

void Sistema::criarUsuario() {
    std::string nome, senha, salario;

    std::cout << "Digite o nome do novo usuário: ";
    std::getline(std::cin, nome);

    // Validação do nome
    while (!validarNome(nome)) {
        std::cout << "Nome inválido! Use apenas letras e espaços. Digite novamente: ";
        std::getline(std::cin, nome);
    }

    std::cout << "Digite a senha: ";
    std::getline(std::cin, senha);

    std::cout << "Digite seu salário mensal em reais: ";
    std::getline(std::cin, salario);

    // Validação do salário
    while (!validarSalario(salario)) {
        std::cout << "Salário inválido! Use apenas números. Digite novamente: ";
        std::getline(std::cin, salario);
    }

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

        // Armazena o nome e o salário do usuário logado
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
        double salarioDouble = std::stod(salarioUsuario); // Converte string para double
        double gastosMensais = operacoes.calcularGastosMensais();
        double saldoDisponivel = salarioDouble - gastosMensais;
        operacoes.atualizarSaldo(saldoDisponivel); 

        std::cout << "\n--- Menu de Compras ---\n";
        std::cout << "Salário Mensal: R$ " << salarioUsuario << "\n";
        std::cout << "Saldo Disponível: R$ " << saldoDisponivel << "\n";
        std::cout << "1. Adicionar compra\n"
                  << "2. Listar compras\n"
                  << "3. Gerar relatório\n"
                  << "4. Ver estatísticas\n"
                  << "5. Mudar categorias\n"
                  << "6. Configuração\n"
                  << "7. Exportar dados para planilha\n"
                  << "8. Logout\n"
                  << "Escolha uma opção: ";
        int escolha;
        std::cin >> escolha;
        std::cin.ignore();  // Limpa o buffer de entrada

        if (std::cin.fail()) {
            limparEntrada();  // Limpa o erro de entrada
            std::cout << "Opção inválida! Tente novamente.\n";
            continue;
        }

        if (escolha == 1) {
            operacoes.adicionarCompra(std::stod(salarioUsuario));
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

                if (std::cin.fail()) {
                    limparEntrada();  // Limpa o erro de entrada
                    std::cout << "Opção inválida! Tente novamente.\n";
                    continue;
                }

                if (opcao == 1) {
                    std::string novoNome;
                    std::cout << "Digite o novo nome: ";
                    std::getline(std::cin, novoNome);
                    configuracao.alterarNome(novoNome);
                    operacoes.setUsuario(novoNome);
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
            std::string outputDir;
            
            std::cout << "Digite o diretório absoluto onde deseja salvar o arquivo CSV: ";
            std::getline(std::cin, outputDir);

            outputDir.erase(0, outputDir.find_first_not_of(" \t"));
            outputDir.erase(outputDir.find_last_not_of(" \t") + 1);

            if (outputDir.empty()) {
                std::cerr << "Erro: Nenhum diretório informado. Exportação cancelada." << std::endl;
            } else {
                TxtToExcelExporter::exportToCsv(operacoes.getUsuario(), outputDir);
            }
        } else if (escolha == 8) {
            break; 
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

    if (std::cin.fail()) {
        limparEntrada();  // Limpa o erro de entrada
        std::cout << "Opção inválida! Tente novamente.\n";
        return;
    }

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

    if (std::cin.fail()) {
        limparEntrada();
        std::cout << "Opção inválida! Tente novamente.\n";
        return;
        
    }

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

    // Converte o salário armazenado para double e passa para Estatistica
    double salario = std::stof(salarioUsuario);
    if (periodo == 2) {  
    salario *= 12;
}
    Estatistica estatistica(comprasFiltradas, salario);
    estatistica.exibirEstatisticas();
    }