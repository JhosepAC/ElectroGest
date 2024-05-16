#pragma once
#include "order_class.h"
#include <vector>
#include <conio.h>

class CARRO_COMPRAS {
private:
    vector<PEDIDO> pedidos;

public:
    // Agregar un pedido al carrito
    void agregarPedido(const PEDIDO& pedido) { pedidos.push_back(pedido); }

    // Ver el contenido del carrito
    void verCarrito(string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Mostrar el contenido del carrito
        if (pedidos.empty()) {
            ShowConsoleCursor(false);
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][258]; // Carrito vac�o
            Sleep(1500);
        }
        else {
            system("cls");
            cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][259] << " ===" << DOUBLE_SPACE; // CARRITO DE COMPRAS
            for (const auto& pedido : pedidos) {
                cout << BLUE_COLOR << menuTexts[currentLanguage][147] << RESET_COLOR << pedido.getCodigoProducto() << BLUE_COLOR << ", " << menuTexts[currentLanguage][160] << RESET_COLOR <<pedido.getCantidad() << "\n"; // Producto, Cantidad
            }
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51]; // Presione cualquier tecla para continuar
            _getch();
        }
    }

    // M�todo para limpiar el carrito
    void limpiarCarrito() { pedidos.clear(); }

    // M�todo para verificar si el carrito est� vac�o
    bool isEmpty() const { return pedidos.empty(); }

    // M�todo para obtener los pedidos del carrito
    const vector<PEDIDO>& getPedidos() const { return pedidos; }
};