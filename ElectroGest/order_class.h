#pragma once
#include <iostream>

// Clase para representar un pedido
class PEDIDO {
private:
    string codigoProducto;
    int cantidad;

public:
    PEDIDO(const string& codigo, int cantidad) : codigoProducto(codigo), cantidad(cantidad) {}

    // Método para obtener el código del producto
    string getCodigoProducto() const {
        return codigoProducto;
    }

    // Método para obtener la cantidad del producto
    int getCantidad() const {
        return cantidad;
    }
};