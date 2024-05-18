#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "product_node_class.h"

class LISTA_PRODUCTO {
public:
    // Constructor
    LISTA_PRODUCTO() : primero(nullptr), ultimo(nullptr) {}

    // Destructor
    ~LISTA_PRODUCTO() {
        while (primero != nullptr) {
            NODO_PRODUCTO* temp = primero;
            primero = primero->siguiente;
            delete temp;
        }
    }

    // Check if the list is empty
    bool estaVacia() const { return primero == nullptr; }

    // Get the first node
    NODO_PRODUCTO* obtenerPrimero() const { return primero; }

    // Método para agregar un producto a la lista
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
        // Si la lista está vacía
        if (primero == nullptr) {
            primero = nuevoNodo;
            ultimo = nuevoNodo;
        }
        else {
            ultimo->siguiente = nuevoNodo;
            ultimo = nuevoNodo;
        }
    }

    // Count the number of products
    int contarProductos() const {
        int contador = 0;
        NODO_PRODUCTO* actual = primero;
        while (actual != nullptr) {
            contador++;
            actual = actual->siguiente;
        }
        return contador;
    }

    // Display the product catalog
    void mostrarCatalogo(const string& currentLanguage) const {
        int cantidadProductos = contarProductos();

        if (primero == nullptr) {
            cout << MAGENTA_COLOR << menuTexts[currentLanguage][254] << endl;
            return;
        }

        cout << CYAN_COLOR << menuTexts[currentLanguage][255] << RESET_COLOR << cantidadProductos << menuTexts[currentLanguage][256] << DOUBLE_SPACE;

        NODO_PRODUCTO* actual = primero;
        while (actual != nullptr) {
            actual->producto.mostrarInformacion();
            cout << endl;
            actual = actual->siguiente;
        }
    }

    void mostrarCatalogoArchivo(const string& currentLanguage) const {
        ofstream file("total_products.txt");
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404] << endl;
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

    // Find a product by code
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

    // Delete a product by code
    void eliminarProducto(const string& codigo) {
        if (primero == nullptr) return;

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

    // Update a product by code
    void actualizarProducto(const string& codigo, double nuevoPrecio, const string& nuevoCodigo, int nuevaGarantia) {
        NODO_PRODUCTO* producto = buscarProducto(codigo);
        if (producto != nullptr) {
            producto->producto.setPrecio(nuevoPrecio);
            producto->producto.setCodigo(nuevoCodigo);
            producto->producto.setGarantia(nuevaGarantia);
        }
    }

private:
    NODO_PRODUCTO* primero;
    NODO_PRODUCTO* ultimo;
};