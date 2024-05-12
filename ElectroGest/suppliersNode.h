#pragma once
#include "suppliers_class.h"

class Nodo {
public:
    Nodo(Proveedor* proveedor) : proveedor(proveedor), siguiente(nullptr) {}

    Proveedor* getProveedor() const { return proveedor; }
    Nodo* getSiguiente() const { return siguiente; }
    void setSiguiente(Nodo* nodo) { siguiente = nodo; }

private:
    Proveedor* proveedor;
    Nodo* siguiente;

    friend class ListaProveedores; // Permitir que ListaProveedores acceda a los miembros privados
};