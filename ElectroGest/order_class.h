#pragma once
#include <iostream>

// Clase para representar un pedido
class PEDIDO {
private:
    std::string codigoProducto;
    int cantidad;

public:
    PEDIDO(const std::string& codigo, int cantidad) : codigoProducto(codigo), cantidad(cantidad) {}

    // Método para obtener el código del producto
    std::string getCodigoProducto() const {
        return codigoProducto;
    }

    // Método para obtener la cantidad del producto
    int getCantidad() const {
        return cantidad;
    }
};