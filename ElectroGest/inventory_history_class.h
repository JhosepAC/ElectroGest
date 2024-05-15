#pragma once
#include <string>

class HISTORIAL_INVENTARIO {
public:
    // Atributos
    string codigoProducto;
    int cantidad;
    bool esEntrada; // Indica si es una entrada (true) o una salida (false)

    // Constructor
    HISTORIAL_INVENTARIO(const string& codigo, int cantidad, bool esEntrada)
        : codigoProducto(codigo), cantidad(cantidad), esEntrada(esEntrada) {}
};