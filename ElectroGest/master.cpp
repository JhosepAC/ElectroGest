#include "pch.h"
#include "menus.h"

int main() {
    // Configurar la localización para que los caracteres especiales se muestren correctamente
    setlocale(LC_ALL, "");

    // Nombre a consola
    SetConsoleTitle(L"ElectroGest");

    // Menú principal
    generalMenu();

    return 0;
}