#include <locale.h>
// #include <windows.h>
#include "Sistema.hpp"

int main() {
    // SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Sistema sistema;
    sistema.iniciar();
    return 0;
}