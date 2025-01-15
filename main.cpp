#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Função para simular a criação de um usuário
void criarUsuario(vector<pair<string, string>>& usuarios) {
    string nome, senha;
    cout << "Digite o nome do usuário: ";
    getline(cin, nome);
    cout << "Digite a senha do usuário: ";
    getline(cin, senha);
    
    // Salvar usuário (simulado em um vetor)
    usuarios.push_back({nome, senha});
    cout << "Usuário criado com sucesso!" << endl;
}

// Função para simular o login de um usuário
bool loginUsuario(const vector<pair<string, string>>& usuarios, const string& nome, const string& senha) {
    for (const auto& usuario : usuarios) {
        if (usuario.first == nome && usuario.second == senha) {
            return true;
        }
    }
    return false;
}

// Função para simular a adição de compras
void addCompra(vector<string>& compras) {
    float valor;
    string categoria;
    cout << "Digite o valor da compra: ";
    cin >> valor;
    cin.ignore(); // Limpar o buffer
    cout << "Digite a categoria da compra: ";
    getline(cin, categoria);
    
    compras.push_back("Compra: R$" + to_string(valor) + " - Categoria: " + categoria);
    cout << "Compra adicionada com sucesso!" << endl;
}

// Função para listar as compras
void listarCompras(const vector<string>& compras) {
    cout << "\n--- Lista de Compras ---\n";
    if (compras.empty()) {
        cout << "Nenhuma compra registrada." << endl;
    } else {
        for (const auto& compra : compras) {
            cout << compra << endl;
        }
    }
}

void menuPrincipal() {
    cout << "--- Bem-vindo ao Sistema de Controle Financeiro ---" << endl;
    
    vector<pair<string, string>> usuarios;  // Lista para armazenar os usuários (nome, senha)
    vector<string> compras;  // Lista para armazenar as compras
    
    while (true) {
        cout << "\nMenu:\n1. Criar usuário\n2. Fazer login\n3. Sair\nEscolha uma opção: ";
        int opcao;
        cin >> opcao;
        cin.ignore(); // Limpar o buffer de entrada

        if (opcao == 1) {
            criarUsuario(usuarios);
        } else if (opcao == 2) {
            string nome, senha;
            cout << "Digite o nome do usuário: ";
            getline(cin, nome);
            cout << "Digite a senha do usuário: ";
            getline(cin, senha);

            if (usuarios.empty()) {
                cout << "Nenhum usuário cadastrado ainda." << endl;
                continue;
            }

            if (loginUsuario(usuarios, nome, senha)) {
                cout << "Bem-vindo, " << nome << "!" << endl;

                while (true) {
                    cout << "\n--- Menu de Compras ---\n1. Adicionar compra\n2. Listar compras\n3. Logout\nEscolha uma opção: ";
                    int escolha;
                    cin >> escolha;
                    cin.ignore();

                    if (escolha == 1) {
                        addCompra(compras);
                    } else if (escolha == 2) {
                        listarCompras(compras);
                    } else if (escolha == 3) {
                        break;
                    } else {
                        cout << "Opção inválida!" << endl;
                    }
                }
            } else {
                cout << "Usuário ou senha incorretos!" << endl;
            }
        } else if (opcao == 3) {
            cout << "Saindo... Até mais!" << endl;
            break;
        } else {
            cout << "Opção inválida!" << endl;
        }
    }
}

int main() {
    menuPrincipal();
    return 0;
}