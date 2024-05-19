#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "product_node_class.h"

using namespace std;

class LISTA_PRODUCTO {
public:
    LISTA_PRODUCTO() : primero(nullptr), ultimo(nullptr) {}
    ~LISTA_PRODUCTO() {
        while (primero != nullptr) {
            NODO_PRODUCTO* temp = primero;
            primero = primero->siguiente;
            delete temp;
        }
    }

    bool estaVacia() const {
        return primero == nullptr;
    }

    NODO_PRODUCTO* obtenerPrimero() const {
        return primero;
    }

    void agregarProducto(const PRODUCTO& producto) {
        NODO_PRODUCTO* nuevoNodo = new NODO_PRODUCTO(
            producto.getCodigo(),
            producto.getNombre(),
            producto.getMarca(),
            producto.getPrecio(),
            producto.getModelo(),
            producto.getAncho(),
            producto.getAlto(),
            producto.getLargo(),
            producto.getPeso(),
            producto.getMaterial(),
            producto.getColor(),
            producto.getGarantia()
        );
        if (primero == nullptr) {
            primero = nuevoNodo;
            ultimo = nuevoNodo;
        }
        else {
            ultimo->siguiente = nuevoNodo;
            ultimo = nuevoNodo;
        }
    }

    int contarProductos() const {
        int contador = 0;
        NODO_PRODUCTO* actual = primero;
        while (actual != nullptr) {
            contador++;
            actual = actual->siguiente;
        }
        return contador;
    }

    void mostrarCatalogo() const {
        int cantidadProductos = contarProductos();

        if (primero == nullptr) {
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "El catálogo está vacío." << endl;
            Sleep(1500);
            return;
        }

        system("cls");

        cout << CYAN_COLOR << "Cantidad de productos en el catálogo: " << RESET_COLOR << cantidadProductos << " productos." << DOUBLE_SPACE;

        NODO_PRODUCTO* actual = primero;
        while (actual != nullptr) {
            actual->producto.mostrarInformacion();
            cout << endl;
            actual = actual->siguiente;
        }

    }

    void mostrarCatalogoArchivo() const {
        ofstream file("total_products.txt");
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo total_products.txt" << endl;
            return;
        }

        NODO_PRODUCTO* actual = primero;
        while (actual != nullptr) {
            actual->producto.mostrarInformacionArchivo(file);
            file << endl;
            actual = actual->siguiente;
        }

        file.close();
    }

    NODO_PRODUCTO* buscarProducto(const string& codigo) {
        NODO_PRODUCTO* actual = primero;
        while (actual != nullptr) {
            if (actual->producto.getCodigo() == codigo) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    void eliminarProducto(const string& codigo) {
        if (primero == nullptr) {
            return;
        }

        if (primero->producto.getCodigo() == codigo) {
            NODO_PRODUCTO* temp = primero;
            primero = primero->siguiente;
            delete temp;
            return;
        }

        NODO_PRODUCTO* actual = primero;
        while (actual->siguiente != nullptr) {
            if (actual->siguiente->producto.getCodigo() == codigo) {
                NODO_PRODUCTO* temp = actual->siguiente;
                actual->siguiente = temp->siguiente;
                delete temp;
                return;
            }
            actual = actual->siguiente;
        }
    }

    void actualizarProducto(const string& codigo, double nuevoPrecio, const string& nuevoCodigo, int nuevaGarantia) {
        NODO_PRODUCTO* producto = buscarProducto(codigo);
        if (producto != nullptr) {
            // Solo se actualizan el precio, código y garantía
            producto->producto.setPrecio(nuevoPrecio);
            producto->producto.setCodigo(nuevoCodigo);
            producto->producto.setGarantia(nuevaGarantia);
        }
    }

private:
    NODO_PRODUCTO* primero;
    NODO_PRODUCTO* ultimo;
};