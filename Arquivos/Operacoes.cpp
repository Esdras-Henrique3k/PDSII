#include "Operacoes.hpp"
#include "Compra.hpp"
#include "ParcelaCompra.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <limits>

Operacoes::Operacoes(const std::string& nomeUsuario) : nomeUsuario(nomeUsuario), categoria(nomeUsuario) {} 

std::string Operacoes::getUsuario() const {
    return nomeUsuario;
}

void Operacoes::addCompra(const Compra& compra) {
    compras.push_back(compra);
    salvarCompras(); // Salva as compras no arquivo após adicionar
}

bool compararPorData(const Compra& a, const Compra& b) {
    std::string dataA = a.getData();
    std::string dataB = b.getData();

    int anoA = std::stoi(dataA.substr(6, 4));
    int anoB = std::stoi(dataB.substr(6, 4));
    if (anoA != anoB) return anoA < anoB;

    int mesA = std::stoi(dataA.substr(3, 2));
    int mesB = std::stoi(dataB.substr(3, 2));
    if (mesA != mesB) return mesA < mesB;

    int diaA = std::stoi(dataA.substr(0, 2));
    int diaB = std::stoi(dataB.substr(0, 2));
    return diaA < diaB;
}

void Operacoes::listarCompras() {
    if (compras.empty()) {
        std::cout << "Nenhuma compra registrada." << std::endl;
        return;
    }

    std::vector<Compra> comprasOrdenadas = compras;
    std::sort(comprasOrdenadas.begin(), comprasOrdenadas.end(), compararPorData);

    std::cout << "--- Lista de Compras ---" << std::endl;
    for (size_t i = 0; i < comprasOrdenadas.size(); ++i) {
        std::cout << i + 1 << ". Valor: R$ " << std::fixed << std::setprecision(2) << comprasOrdenadas[i].getValor()
                  << ", Categoria: " << comprasOrdenadas[i].getCategoria()
                  << ", Data: " << comprasOrdenadas[i].getData() << std::endl;
    }

    size_t opcaoExcluir;
    std::cout << "\nDigite o número da compra que deseja remover (0 para voltar): ";
    std::cin >> opcaoExcluir;
    std::cin.ignore();

    if (opcaoExcluir > 0 && opcaoExcluir <= comprasOrdenadas.size()) {
        compras.erase(compras.begin() + opcaoExcluir - 1);
        salvarCompras();
        std::cout << "Compra removida com sucesso!\n";
    } else if (opcaoExcluir != 0) {
        std::cout << "Opção inválida!\n";
    }
}

const std::vector<Compra>& Operacoes::getCompras() const {
    return compras;
}

void Operacoes::carregarCompras() {
    std::ifstream arquivo("data/compras-" + nomeUsuario + ".txt");
    if (!arquivo.is_open()) return;

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string valorStr, categoria, data;

        std::getline(ss, valorStr, ';');
        std::getline(ss, categoria, ';');
        std::getline(ss, data, ';');

        float valor = std::stof(valorStr);
        Compra compra(valor, categoria, data);
        compras.push_back(compra);
    }
}

void Operacoes::salvarCompras() {
    std::ofstream arquivo("data/compras-" + nomeUsuario + ".txt");
    for (const auto& compra : compras) {
        // Verifica se a compra é uma compra parcelada
         if (auto parcelaCompra = dynamic_cast<const ParcelaCompra*>(&compra)) {
             // Compra parcelada
             arquivo << compra.getValor() << ";" << compra.getCategoria() << ";" << compra.getData() << std::endl;
             for (int i = 0; i < parcelaCompra->getNumParcelas(); ++i) {
                 arquivo << parcelaCompra->getValorParcela(i) << ";" << compra.getCategoria() << ";" << compra.getData() << std::endl;
             }
         } else {
             // Compra à vista
            arquivo << compra.getValor() << ";" << compra.getCategoria() << ";" << compra.getData() << std::endl;
         }
    }
}

void Operacoes::menuCompras() {
    while (true) {
        std::cout << "\n--- Menu de Compras ---\n1. Adicionar compra\n2. Listar compras\n3. Logout\nEscolha uma opção: ";
        int escolha;
        std::cin >> escolha;
        
        std::cin >> escolha;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida! Por favor, insira um número." << std::endl;
            continue;
        }

        if (escolha == 1) {
            adicionarCompra();
        } else if (escolha == 2) {
            listarCompras();
        } else if (escolha == 3) {
            break;
        } else {
            std::cout << "Opção inválida!" << std::endl;
        }
    }
}

void Operacoes::adicionarCompra() {
    float valor;
    std::string categoriaEscolhida;

    std::cout << "Digite o valor da compra: ";
    std::cin >> valor;
    std::cin.ignore();

    if (valor <= 0) {
        std::cout << "O valor da compra deve ser maior que zero.\n";
        return;
    }

    // Acessa as categorias disponíveis
    const auto& categorias = categoria.obterCategorias(); 
    if (categorias.empty()) {
        std::cout << "Nenhuma categoria disponível. Adicione uma antes de continuar." << std::endl;
        return;
    }

    std::cout << "\nEscolha a categoria da compra:\n";
    for (size_t i = 0; i < categorias.size(); ++i) {
        std::cout << i + 1 << ". " << categorias[i] << std::endl;
    }

    int opcaoCategoria;
    std::cout << "Digite o número da categoria: ";
    std::cin >> opcaoCategoria;
    std::cin.ignore();

    if (opcaoCategoria < 1 || static_cast<std::size_t>(opcaoCategoria) > categorias.size()) {
        std::cout << "Opção inválida!" << std::endl;
        return;
    }

    categoriaEscolhida = categorias[opcaoCategoria - 1];

    // Perguntar se é à vista ou parcelado
    std::cout << "\nA compra será:\n1. À vista\n2. Parcelada\nEscolha uma opção: ";
    int opcaoPagamento;
    std::cin >> opcaoPagamento;
    std::cin.ignore();

    if (opcaoPagamento == 1) {
        // Compra à vista
        std::string data;
        std::cout << "Digite a data da compra (formato: dd/mm/aaaa): ";
        std::getline(std::cin, data);

        if (data.size() != 10 || data[2] != '/' || data[5] != '/') {
            std::cout << "Formato de data inválido! Por favor, use o formato dd/mm/aaaa." << std::endl;
            return;
        }

        addCompra(Compra(valor, categoriaEscolhida, data));

        std::cout << "Compra à vista adicionada com sucesso!" << std::endl;

    } else if (opcaoPagamento == 2) {
        int numParcelas;
        std::cout << "Digite o número de parcelas: ";
        std::cin >> numParcelas;
        std::cin.ignore();

        if (numParcelas <= 0) {
            std::cout << "Número de parcelas inválido!\n";
            return;
        }

        std::string data;
        std::cout << "Digite a data da primeira parcela (formato: dd/mm/aaaa): ";
        std::getline(std::cin, data);

        if (data.size() != 10 || data[2] != '/' || data[5] != '/') {
            std::cout << "Formato de data inválido! Por favor, use o formato dd/mm/aaaa." << std::endl;
            return;
        }

        //ParcelaCompra::ParcelarCompra(valor, categoriaEscolhida, data, numParcelas, *this);
        
        // addCompra(parcelaCompra);
        // Exibir os valores de cada parcela
        // const auto& parcelas = parcelaCompra.getValoresParcelas();
        // std::cout << "Detalhamento das parcelas:\n";
        // for (size_t i = 0; i < parcelas.size(); ++i) {
        //     std::cout << "Parcela " << i + 1 << ": R$ " << parcelas[i] << "\n";
        // }
        std::cout << "Compra parcelada adicionada com sucesso!\n";
    } else {
        std::cout << "Opção de pagamento inválida!\n";
    }
}

void Operacoes::mudarCategorias() {
    while (true) {
        std::cout << "\n--- Mudar Categorias ---\n1. Adicionar categoria\n2. Remover categoria\n3. Listar categorias\n4. Voltar\nEscolha uma opção: ";
        int escolha;
        std::cin >> escolha;
        std::cin.ignore();

        if (escolha == 1) {
            adicionarCategoria();
        } else if (escolha == 2) {
            removerCategoria();
        } else if (escolha == 3) {
            listarCategorias();
        } else if (escolha == 4) {
            break;
        } else {
            std::cout << "Opção inválida!" << std::endl;
        }
    }
}

void Operacoes::adicionarCategoria() {
    std::string novaCategoria;
    std::cout << "Digite o nome da nova categoria: ";
    std::getline(std::cin, novaCategoria);

    categoria.adicionarCategoria(novaCategoria, nomeUsuario); // Passando nomeUsuario
    std::cout << "Categoria adicionada com sucesso!" << std::endl;
}

void Operacoes::removerCategoria() {
    listarCategorias();

    int opcao;
    std::cout << "Digite o número da categoria que deseja remover: ";
    std::cin >> opcao;
    std::cin.ignore();

    if (opcao < 1 || static_cast<std::size_t>(opcao) > categoria.obterCategorias().size()) {
        std::cout << "Opção inválida!" << std::endl;
        return;
    }

    std::string categoriaRemover = categoria.obterCategorias()[opcao - 1];
    categoria.excluirCategoria(categoriaRemover, nomeUsuario); // Passando nomeUsuario
    std::cout << "Categoria removida com sucesso!" << std::endl;
}

void Operacoes::listarCategorias() {
    const auto& categorias = categoria.obterCategorias();
    if (categorias.empty()) {
        std::cout << "Nenhuma categoria cadastrada." << std::endl;
        return;
    }

    std::cout << "--- Categorias ---\n";
    for (size_t i = 0; i < categorias.size(); ++i) {
        std::cout << i + 1 << ". " << categorias[i] << std::endl;
    }
}

double Operacoes::calcularGastosMensais() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    int mesAtual = now->tm_mon + 1;
    int anoAtual = now->tm_year + 1900;

    double totalGasto = 0.0;

    for (const auto& compra : compras) {
        int dia, mes, ano;
        sscanf(compra.getData().c_str(), "%d/%d/%d", &dia, &mes, &ano);

        if (mes == mesAtual && ano == anoAtual) {
            totalGasto += compra.getValor();
        }
    }
    return totalGasto;
}
