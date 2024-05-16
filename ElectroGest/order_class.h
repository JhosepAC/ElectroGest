#pragma once
#include <iostream>

class PEDIDO {
private:
    string codigoProducto;
    int cantidad;

public:
    // Constructor de la clase
    PEDIDO(const string& codigo, int cantidad) : codigoProducto(codigo), cantidad(cantidad) {}

    // M�todo para obtener el c�digo del producto
    string getCodigoProducto() const { return codigoProducto; }

    // M�todo para obtener la cantidad del producto
    int getCantidad() const { return cantidad; }
};