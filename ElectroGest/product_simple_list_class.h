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

    // Verifica si la lista está vacía
    bool estaVacia() const { return primero == nullptr; }

    // Método de acceso
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

    // Método para agregar un producto a la lista
    int contarProductos() const {
        int contador = 0;
        NODO_PRODUCTO* actual = primero;
        // Recorrer la lista
        while (actual != nullptr) {
            contador++;
            actual = actual->siguiente;
        }
        return contador;
    }

    // Método para mostrar el catálogo de productos
    void mostrarCatalogo(string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        int cantidadProductos = contarProductos();

        // Si la lista está vacía
        if (primero == nullptr) {
            cout << MAGENTA_COLOR << menuTexts[currentLanguage][254] << endl;
            return;
        }

        cout << CYAN_COLOR << menuTexts[currentLanguage][255] << RESET_COLOR << cantidadProductos << menuTexts[currentLanguage][256] << DOUBLE_SPACE;

        NODO_PRODUCTO* actual = primero;

        // Recorrer la lista
        while (actual != nullptr) {
            actual->producto.mostrarInformacion();
            cout << endl;
            actual = actual->siguiente;
        }
    }

    void mostrarCatalogoArchivo(string _currentLenguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLenguage;

        ofstream file("total_products.txt");

        // Si no se pudo abrir el archivo
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404] << endl;
            return;
        }

        NODO_PRODUCTO* actual = primero;
        
        // Recorrer la lista
        while (actual != nullptr) {
            actual->producto.mostrarInformacionArchivo(file);
            file << endl;
            actual = actual->siguiente;
        }

        file.close();
    }

    // Método para buscar un producto por código
    NODO_PRODUCTO* buscarProducto(const string& codigo) {
        NODO_PRODUCTO* actual = primero;

        // Recorrer la lista
        while (actual != nullptr) {
            // Si se encuentra el producto
            if (actual->producto.getCodigo() == codigo) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    // Método para buscar un producto por nombre
    void eliminarProducto(const string& codigo) {

        // Si la lista está vacía
        if (primero == nullptr) {
            return;
        }

        // Si el producto a eliminar es el primero
        if (primero->producto.getCodigo() == codigo) {
            NODO_PRODUCTO* temp = primero;
            primero = primero->siguiente;
            delete temp;
            return;
        }

        NODO_PRODUCTO* actual = primero;

        // Recorrer la lista
        while (actual->siguiente != nullptr) {
            // Si se encuentra el producto
            if (actual->siguiente->producto.getCodigo() == codigo) {
                NODO_PRODUCTO* temp = actual->siguiente;
                actual->siguiente = temp->siguiente;
                delete temp;
                return;
            }
            actual = actual->siguiente;
        }
    }

    // Método para buscar un producto por nombre
    void actualizarProducto(const string& codigo, double nuevoPrecio, const string& nuevoCodigo, int nuevaGarantia) {
        NODO_PRODUCTO* producto = buscarProducto(codigo);
        // Si se encuentra el producto
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