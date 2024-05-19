#pragma once
#include <string>
#include <ctime>

class HISTORIAL_INVENTARIO {
public:
    std::string codigoProducto;
    int cantidad;
    bool esEntrada; // Indica si es una entrada (true) o una salida (false)
    std::string fechaHora; // Almacena la fecha y hora del movimiento

    HISTORIAL_INVENTARIO(const std::string& codigo, int cantidad, bool esEntrada, const std::string& fechaHora)
        : codigoProducto(codigo), cantidad(cantidad), esEntrada(esEntrada), fechaHora(fechaHora) {}
};