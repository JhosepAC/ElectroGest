#pragma once
#include <string>

class HISTORIAL_INVENTARIO {
public:
    string codigoProducto;
    int cantidad;
    bool esEntrada; // Indica si es una entrada (true) o una salida (false)

    HISTORIAL_INVENTARIO(const std::string& codigo, int cantidad, bool esEntrada)
        : codigoProducto(codigo), cantidad(cantidad), esEntrada(esEntrada) {}
};