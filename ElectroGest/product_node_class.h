#pragma once
#include "product_class.h"

class NODO_PRODUCTO {
public:
    NODO_PRODUCTO(const string& _codigo, const string& _nombre, const string& _marca, double _precio, const string& _modelo, double _ancho, double _alto, double _largo, double _peso, const string& _material, const string& _color, int _garantia)
        : producto(_codigo, _nombre, _marca, _precio, _modelo, _ancho, _alto, _largo, _peso, _material, _color, _garantia), siguiente(nullptr) {}

    PRODUCTO producto;
    NODO_PRODUCTO* siguiente;

};