#pragma once
#include <string>
#include <ctime>

class HISTORIAL_INVENTARIO {
public:
    string codigoProducto;
    int cantidad;
    bool esEntrada; // Indica si es una entrada (true) o una salida (false)
    string fechaHora; // Almacena la fecha y hora del movimiento

    HISTORIAL_INVENTARIO(const string& codigo, int cantidad, bool esEntrada, const string& fechaHora)
        : codigoProducto(codigo), cantidad(cantidad), esEntrada(esEntrada), fechaHora(fechaHora) {}
};