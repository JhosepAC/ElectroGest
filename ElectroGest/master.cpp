#include "pch.h"
#include "menus.h"

int main() {
    // Configurar la localizaci�n para que los caracteres especiales se muestren correctamente
    setlocale(LC_ALL, "");

    // Nombre a consola
    SetConsoleTitle(L"ElectroGest");

    // Men� principal
    generalMenu();

    return 0;
}