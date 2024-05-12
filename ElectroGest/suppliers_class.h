#pragma once 
#include <string>

class Proveedor
{
public:
    Proveedor(const string& nombre, const string& direccion, int telefono)
        : nombre(nombre), direccion(direccion), telefono(telefono) {}

    // Funciones para actualizar los atributos
    void setNombre(const string& nuevoNombre) { nombre = nuevoNombre; }
    void setDireccion(const string& nuevaDireccion) { direccion = nuevaDireccion; }
    void setTelefono(int nuevoTelefono) { telefono = nuevoTelefono; }

    string getNombre() const { return nombre; }
    string getDireccion() const { return direccion; }
    int getTelefono() const { return telefono; }

private:
    string nombre;
    string direccion;
    int telefono;
};