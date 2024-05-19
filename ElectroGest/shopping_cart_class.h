#pragma once
#include <vector>
#include <iostream>
#include "order_class.h"

class CARRO_COMPRAS {
private:
    vector<PEDIDO> pedidos;

public:
    // Agregar pedido al carrito
    void agregarPedido(const PEDIDO& pedido) {
        pedidos.push_back(pedido);
    }

    // Ver contenido del carrito
    void verCarrito() const {
        if (pedidos.empty()) {
            cout << endl << MAGENTA_COLOR << "El carrito está vacío." << RESET_COLOR;
            Sleep(1500);
        }
        else {
            system("cls");
            cout << endl << CYAN_COLOR << "=== CARRITO DE COMPRAS ===" << DOUBLE_SPACE;
            for (const auto& pedido : pedidos) {
                cout << BLUE_COLOR << "Código: " << RESET_COLOR << pedido.getCodigoProducto() << BLUE_COLOR << ", Cantidad: " << RESET_COLOR << pedido.getCantidad() << "\n";
            }
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
            _getch();
        }
    }

    // Limpiar el carrito
    void limpiarCarrito() {
        pedidos.clear();
    }

    // Verificar si el carrito está vacío
    bool isEmpty() const {
        return pedidos.empty();
    }

    // Obtener los pedidos del carrito
    const vector<PEDIDO>& obtenerPedidos() const {
        return pedidos;
    }
};
