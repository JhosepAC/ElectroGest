#pragma once 
#include <string>

class Proveedor
{
public:
    Proveedor(const string& nombre, const string& direccion, const string& telefono)
        : nombre(nombre), direccion(direccion), telefono(telefono) {}

    // Setters
    void setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }
    void setDireccion(const string& nuevaDireccion) { direccion = nuevaDireccion; }
    void setTelefono(const string& nuevoTelefono) { telefono = nuevoTelefono; }

    // Getters
    string getNombre() const { return nombre; }
    string getDireccion() const { return direccion; }
    string getTelefono() const { return telefono; }

private:
    string nombre;
    string direccion;
    string telefono;
};