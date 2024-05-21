#pragma once
#include <iostream>

class PEDIDO {
private:
    string clienteID;
    string codigoProducto;
    int cantidad;

public:
    // Constructor
    PEDIDO(const string& id,const string& codigo, int cantidad) 
        : clienteID(id), codigoProducto(codigo), cantidad(cantidad) {}

    // Getters
    string getClienteID() const { return clienteID; }
    string getCodigoProducto() const { return codigoProducto; }
    int getCantidad() const { return cantidad; }

};