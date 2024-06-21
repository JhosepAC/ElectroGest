#pragma once
#include <string>

class PROMOCION {
public:
    string codigoProducto;
    int descuento;
    string descripcion;

    // Constructor predeterminado
    PROMOCION() : codigoProducto(""), descuento(0.0), descripcion("") {}

    // Constructor con parámetros
    PROMOCION(const string& codigo, int desc, const string& descp)
        : codigoProducto(codigo), descuento(desc), descripcion(descp) {}
};
