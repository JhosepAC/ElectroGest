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

    // Métodos de la clase ListaProveedores
    void cargarDesdeArchivo(const string& archivo, string _currentLanguage);
    Proveedor* obtenerProveedor(int posicion) const;
    int size() const;
    int buscarProveedorPorNombre(const string& nombreBuscar) const;
    void agregarProveedor(Proveedor* proveedor);
    void mostrarProveedores(string _currentLanguage) const;
    void eliminarProveedor(int posicion, string _currentLanguage);
    void buscarProveedor(const string& nombreBuscar, string _currentLanguage) const;

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
    // Iterar sobre la lista y eliminar cada nodo
    while (actual != nullptr) {
        Nodo* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
}

void ListaProveedores::cargarDesdeArchivo(const string& archivo, string _currentLanguage) {

    // Idioma predeterminado
    string currentLanguage = _currentLanguage;

    ifstream archivoProveedores(archivo);

    // Verificar si el archivo se abrió correctamente
    if (!archivoProveedores.is_open()) {
        cout << menuTexts[currentLanguage][404] << endl;
        return;
    }

    string linea;

    // Iterar sobre cada línea del archivo
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
    // Verificar si la posición está dentro del rango de la lista
    if (posicion < 0 || posicion >= tamano) {
        return nullptr; // Fuera de rango, devolver nullptr
    }
    Nodo* actual = primero;
    // Iterar sobre la lista hasta llegar a la posición deseada
    for (int i = 0; i < posicion; ++i) {
        actual = actual->getSiguiente();
    }
    return actual->getProveedor();
}

int ListaProveedores::size() const {
    return tamano;
}

int ListaProveedores::buscarProveedorPorNombre(const string& nombreBuscar) const {
    Nodo* actual = primero;
    int posicion = 0;
    while (actual != nullptr) {
        Proveedor* proveedor = actual->getProveedor();
        string nombre = proveedor->getNombre();

        // Convertir a minúsculas y eliminar espacios en blanco al principio y al final
        transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
        nombre.erase(remove_if(nombre.begin(), nombre.end(), ::isspace), nombre.end());

        string nombreBuscarFormatted = nombreBuscar;

        // Convertir a minúsculas y eliminar espacios en blanco al principio y al final
        transform(nombreBuscarFormatted.begin(), nombreBuscarFormatted.end(), nombreBuscarFormatted.begin(), ::tolower);
        nombreBuscarFormatted.erase(remove_if(nombreBuscarFormatted.begin(), nombreBuscarFormatted.end(), ::isspace), nombreBuscarFormatted.end());

        // Si se encuentra el proveedor, devolver la posición
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

    // Si la lista está vacía, el nuevo nodo será el primero y el último
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

void ListaProveedores::mostrarProveedores(string _currentLanguage) const {

    // Idioma predeterminado
    string currentLanguage = _currentLanguage;

    Nodo* actual = primero;

    // Imprimir encabezados de la tabla
    cout << CYAN_COLOR << left << setw(25) << menuTexts[currentLanguage][217] << setw(40) << menuTexts[currentLanguage][288] << setw(15) << menuTexts[currentLanguage][289] << endl; // Nombre, Dirección, Teléfono

    // Imprimir separador de columnas
    cout << GRAY_COLOR << setw(25) << setfill('-') << RESET_COLOR << "" << setw(40) << "" << setw(15) << "" << setfill(' ') << endl;

    // Iterar sobre la lista de proveedores e imprimir cada uno en formato de tabla
    while (actual != nullptr) {
        Proveedor* proveedor = actual->getProveedor();
        cout << left << setw(25) << proveedor->getNombre()
            << setw(40) << proveedor->getDireccion()
            << setw(15) << proveedor->getTelefono() << endl;
        actual = actual->getSiguiente();
    }
}

void ListaProveedores::eliminarProveedor(int posicion, string _currentLanguage) {

    // Idioma predeterminado
    string currentLanguage = _currentLanguage;

    // Verificar si la posición está dentro del rango de la lista
    if (posicion < 0 || posicion >= tamano) {
        cout << menuTexts[currentLanguage][290] << endl; // Posición inválida
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

    // Iterar sobre la lista hasta llegar a la posición deseada
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

void ListaProveedores::buscarProveedor(const string& nombreBuscar, string _currentLanguage) const {
    
    // Idioma predeterminado
    string currentLanguage = _currentLanguage;

    Nodo* actual = primero;
    int posicion = 0;
    bool encontrado = false;

    // Iterar sobre la lista de proveedores
    while (actual != nullptr) {
        Proveedor* proveedor = actual->getProveedor();
        string nombre = proveedor->getNombre();

        // Convertir a minúsculas y eliminar espacios en blanco al principio y al final
        transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);
        nombre.erase(remove_if(nombre.begin(), nombre.end(), ::isspace), nombre.end());

        string nombreBuscarFormatted = nombreBuscar;

        // Convertir a minúsculas y eliminar espacios en blanco al principio y al final
        transform(nombreBuscarFormatted.begin(), nombreBuscarFormatted.end(), nombreBuscarFormatted.begin(), ::tolower);
        nombreBuscarFormatted.erase(remove_if(nombreBuscarFormatted.begin(), nombreBuscarFormatted.end(), ::isspace), nombreBuscarFormatted.end());

        // Si se encuentra el proveedor, imprimir sus datos y la posición
        if (nombre == nombreBuscarFormatted) {
            encontrado = true;
            cout << menuTexts[currentLanguage][291] << posicion << ": " << proveedor->getNombre() << ", " << proveedor->getDireccion() << ", " << proveedor->getTelefono() << endl;
            break;
        }

        actual = actual->getSiguiente();
        ++posicion;
    }

    if (!encontrado) {
        cout << menuTexts[currentLanguage][278] << endl;
    }
}


#endif