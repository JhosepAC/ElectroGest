#pragma once
#include <iostream>
#include <string>

class PEDIDO {
private:
    string clienteID;
    string codigoProducto;
    int cantidad;
    string direccionEntrega; // Nueva dirección de entrega

public:
    // Constructor
    PEDIDO(const string& id, const string& codigo, int cantidad, const string& direccionEntrega = "")
        : clienteID(id), codigoProducto(codigo), cantidad(cantidad), direccionEntrega(direccionEntrega) {}

    // Getters
    string getClienteID() const { return clienteID; }
    string getCodigoProducto() const { return codigoProducto; }
    int getCantidad() const { return cantidad; }
    string getDireccionEntrega() const { return direccionEntrega; }

    // Setters
    void setDireccionEntrega(const string& direccion) { direccionEntrega = direccion; }
};