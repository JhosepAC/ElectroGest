#ifndef SUPPLIERS_LIST_H
#define SUPPLIERS_LIST_H

#include "suppliersNode.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

class ListaProveedores {
public:
    ListaProveedores();
    ~ListaProveedores();

    void cargarDesdeArchivo(const std::string& archivo);
    Proveedor* obtenerProveedor(int posicion) const;
    int size() const;
    int buscarProveedorPorNombre(const std::string& nombreBuscar) const;
    void agregarProveedor(Proveedor* proveedor);
    void mostrarProveedores() const;
    void eliminarProveedor(int posicion);
    void buscarProveedor(const std::string& nombreBuscar) const;

    bool ListaProveedores::proveedorEncontrado() const {
        return tamano > 0; // Si el tamaño de la lista es mayor que cero, se considera que se ha encontrado al menos un proveedor
    }

private:
    Nodo* primero;
    Nodo* ultimo;
    int tamano; // Nuevo miembro para mantener el tamaño de la lista
};

ListaProveedores::ListaProveedores() : primero(nullptr), ultimo(nullptr), tamano(0) {}

ListaProveedores::~ListaProveedores() {
    Nodo* actual = primero;
    while (actual != nullptr) {
        Nodo* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

void ListaProveedores::cargarDesdeArchivo(const std::string& archivo) {
    std::ifstream archivoProveedores(archivo);
    if (!archivoProveedores.is_open()) {
        std::cout << "Error al abrir el archivo de proveedores." << std::endl;
        return;
    }

    std::string linea;
    while (getline(archivoProveedores, linea)) {
        stringstream ss(linea);
        string nombre, direccion;
        string telefono;
        getline(ss, nombre, ',');
        getline(ss, direccion, ',');
        ss >> telefono;
        Proveedor* proveedor = new Proveedor(nombre, direccion, telefono);
        agregarProveedor(proveedor);
    }
    archivoProveedores.close();
}

Proveedor* ListaProveedores::obtenerProveedor(int posicion) const {
    if (posicion < 0 || posicion >= tamano) {
        return nullptr; // Fuera de rango, devolver nullptr
    }
    Nodo* actual = primero;
    for (int i = 0; i < posicion; ++i) {
        actual = actual->getSiguiente();
    }
    return actual->getProveedor();
}

int ListaProveedores::size() const {
    return tamano;
}

int ListaProveedores::buscarProveedorPorNombre(const std::string& nombreBuscar) const {
    Nodo* actual = primero;
    int posicion = 0;
    while (actual != nullptr) {
        Proveedor* proveedor = actual->getProveedor();
        std::string nombre = proveedor->getNombre();

        // Convertir a minúsculas y eliminar espacios en blanco al principio y al final
        transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
        nombre.erase(remove_if(nombre.begin(), nombre.end(), ::isspace), nombre.end());

        std::string nombreBuscarFormatted = nombreBuscar;
        transform(nombreBuscarFormatted.begin(), nombreBuscarFormatted.end(), nombreBuscarFormatted.begin(), ::tolower);
        nombreBuscarFormatted.erase(remove_if(nombreBuscarFormatted.begin(), nombreBuscarFormatted.end(), ::isspace), nombreBuscarFormatted.end());

        if (nombre == nombreBuscarFormatted) {
            return posicion;
        }

        actual = actual->getSiguiente();
        ++posicion;
    }

    return -1; // Proveedor no encontrado
}

void ListaProveedores::agregarProveedor(Proveedor* proveedor) {
    Nodo* nuevoNodo = new Nodo(proveedor);
    if (primero == nullptr) {
        primero = nuevoNodo;
        ultimo = nuevoNodo;
    }
    else {
        ultimo->setSiguiente(nuevoNodo);
        ultimo = nuevoNodo;
    }
    tamano++;
}

void ListaProveedores::mostrarProveedores() const {
    Nodo* actual = primero;
    int indice = 1;  // Variable para el índice de los proveedores

    // Imprimir encabezados de la tabla
    cout << CYAN_COLOR << left << setw(5) << "No." << setw(25) << "Nombre" << setw(20) << "Dirección" << setw(15) << "Teléfono" << endl;

    // Imprimir separador de columnas
    cout << GRAY_COLOR << setw(5) << setfill('-') << "" << setw(25) << "" << setw(20) << "" << setw(15) << "" << setfill(' ') << RESET_COLOR << endl;

    // Iterar sobre la lista de proveedores e imprimir cada uno en formato de tabla
    while (actual != nullptr) {
        Proveedor* proveedor = actual->getProveedor();
        cout << left << setw(5) << indice
            << setw(25) << proveedor->getNombre()
            << setw(20) << proveedor->getDireccion()
            << setw(15) << proveedor->getTelefono() << endl;
        actual = actual->getSiguiente();
        indice++;  // Incrementar el índice
    }
}

void ListaProveedores::eliminarProveedor(int posicion) {
    if (posicion < 0 || posicion >= tamano) {
        std::cout << "Posición no válida." << std::endl;
        return;
    }

    // Si se va a eliminar el primer nodo
    if (posicion == 0) {
        Nodo* nodoEliminar = primero;
        primero = primero->getSiguiente();
        delete nodoEliminar;
        --tamano;
        return;
    }

    // Buscar el nodo anterior al que se va a eliminar
    Nodo* anterior = nullptr;
    Nodo* actual = primero;
    for (int i = 0; i < posicion; ++i) {
        anterior = actual;
        actual = actual->getSiguiente();
    }

    // Enlazar el nodo anterior con el siguiente al que se va a eliminar
    anterior->setSiguiente(actual->getSiguiente());

    // Si se va a eliminar el último nodo, actualizar 'ultimo'
    if (actual == ultimo) {
        ultimo = anterior;
    }

    delete actual;
    --tamano;
}

void ListaProveedores::buscarProveedor(const std::string& nombreBuscar) const {
    Nodo* actual = primero;
    int posicion = 0;
    bool encontrado = false;
    while (actual != nullptr) {
        Proveedor* proveedor = actual->getProveedor();
        std::string nombre = proveedor->getNombre();

        // Convertir a minúsculas y eliminar espacios en blanco al principio y al final
        transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
        nombre.erase(remove_if(nombre.begin(), nombre.end(), ::isspace), nombre.end());

        std::string nombreBuscarFormatted = nombreBuscar;
        transform(nombreBuscarFormatted.begin(), nombreBuscarFormatted.end(), nombreBuscarFormatted.begin(), ::tolower);
        nombreBuscarFormatted.erase(remove_if(nombreBuscarFormatted.begin(), nombreBuscarFormatted.end(), ::isspace), nombreBuscarFormatted.end());

        if (nombre == nombreBuscarFormatted) {
            encontrado = true;
            std::cout << "Proveedor encontrado en la posición " << posicion << ": " << proveedor->getNombre() << ", " << proveedor->getDireccion() << ", " << proveedor->getTelefono() << std::endl;
            break;
        }

        actual = actual->getSiguiente();
        ++posicion;
    }

    if (!encontrado) {
        std::cout << "Proveedor no encontrado." << std::endl;
    }
}


#endif
