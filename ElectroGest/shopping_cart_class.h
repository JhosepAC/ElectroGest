#pragma once
#include "order_class.h"
#include <vector>
#include <conio.h>

class CARRO_COMPRAS {
private:
    std::vector<PEDIDO> pedidos;

public:
    // Agregar un pedido al carrito
    void agregarPedido(const PEDIDO& pedido) {
        pedidos.push_back(pedido);
    }

    // Ver el contenido del carrito
    void verCarrito() const {
        if (pedidos.empty()) {
            std::cout << DOUBLE_SPACE << MAGENTA_COLOR << "El carrito está vacío.";
            Sleep(1500);
        }
        else {
            system("cls");
            std::cout << CYAN_COLOR << "=== Carrito de Compras ===" << DOUBLE_SPACE;
            for (const auto& pedido : pedidos) {
                std::cout << GRAY_COLOR << "Código: " << RESET_COLOR << pedido.getCodigoProducto() << GRAY_COLOR << ", Cantidad: " << RESET_COLOR <<pedido.getCantidad() << "\n";
            }
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";      
            _getch();
        }
    }

    // Método para limpiar el carrito
    void limpiarCarrito() {
        pedidos.clear();
    }

    // Método para verificar si el carrito está vacío
    bool isEmpty() const {
        return pedidos.empty();
    }

    // Método para obtener los pedidos del carrito
    const std::vector<PEDIDO>& getPedidos() const {
        return pedidos;
    }
};