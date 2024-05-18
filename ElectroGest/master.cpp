#include "pch.h"
#include "menus.h"

int main() {
    // Configurar la localización para que los caracteres especiales se muestren correctamente
    setlocale(LC_ALL, "");

    system("title ElectroGest");

    // Menú principal
    generalMenu();

    return 0;
}