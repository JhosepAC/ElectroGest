#pragma once
#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <chrono>
#include <ctime>
#include <conio.h>
#include "general_variables.h"
#include "product_manager_class.h"
#include "inventory_history_class.h" 

class GESTION_INVENTARIO {
private:
    stack<HISTORIAL_INVENTARIO> historialMovimientos;
    map<string, int> inventario;

public:
    // Constructor
    GESTION_INVENTARIO() {}

    // Función para verificar si un producto existe en el inventario
    bool existeProducto(const string& codigoProducto) const {
        return inventario.find(codigoProducto) != inventario.end(); // Devuelve true si el producto existe en el inventario
    }

    // Función para obtener el stock de un producto
    void consultarStock(const string& codigoProducto, string _currentLanguage) const {

        // Iidioma predeterminado
        string currentLanguage = _currentLanguage;

        // Buscar el producto en el inventario
        auto it = inventario.find(codigoProducto);

        // Si el producto existe en el inventario
        if (it != inventario.end()) {
            cout << CYAN_COLOR << menuTexts[currentLanguage][146] << RESET_COLOR << endl; // Stock del producto
            cout << GRAY_COLOR << menuTexts[currentLanguage][147] << RESET_COLOR << codigoProducto << endl; // Código del producto
            cout << GRAY_COLOR << menuTexts[currentLanguage][148] << it->second << endl; // Stock del producto
            
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51] << RESET_COLOR << endl; // Presiona cualquier tecla para continuar
        }
        else {
            cout << DOUBLE_SPACE << RED_COLOR << menuTexts[currentLanguage][149] << codigoProducto << menuTexts[currentLanguage][150] << RESET_COLOR << endl; // El producto no se encuentra en el inventario
            Sleep(1500); // Esperar 1.5 segundos
        }
    }

    // Función para verificar si hay suficiente stock de un producto
    bool verificarStock(const string& codigoProducto, int cantidad) const {
        auto it = inventario.find(codigoProducto); // Buscar el producto en el inventario
        // Devolver true si el producto existe en el inventario y la cantidad es suficiente
        if (it != inventario.end()) {
            return it->second >= cantidad;
        }
        return false; // El producto no está en el inventario
    }

    // Función para mostrar el inventario
    void verInventario(string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Si el inventario está vacío
        if (inventario.empty()) {
            ShowConsoleCursor(false); // Ocultar el cursor de la consola
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][151] << RESET_COLOR << endl; // El inventario está vacío
            Sleep(1000); // Esperar 1 segundo (1000 ms)
            return;
        }

        system("cls"); // Limpiar la pantalla antes de mostrar el inventario

        cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][152] << " ===" << RESET_COLOR << DOUBLE_SPACE; // Inventario
        for (const auto& pair : inventario) {
            cout << BLUE_COLOR << menuTexts[currentLanguage][147] << RESET_COLOR << pair.first << endl; // Código del producto
            cout << BLUE_COLOR << menuTexts[currentLanguage][148] << RESET_COLOR << pair.second << endl;// Stock del producto
            cout << YELLOW_COLOR << "-------------------------" << DOUBLE_SPACE;
        }

        ShowConsoleCursor(false); // Ocultar el cursor de la consola
        cout << endl << GRAY_COLOR << menuTexts[currentLanguage][51] << RESET_COLOR << endl; // Presiona cualquier tecla para continuar
        _getch(); // Esperar a que el usuario presione una tecla
    }

    // Función para añadir stock a un producto
    void añadirStock(const string& codigoProducto, int cantidad, string _currentLanguage) {
        inventario[codigoProducto] += cantidad; // Añadir la cantidad al stock del producto
        historialMovimientos.push(HISTORIAL_INVENTARIO(codigoProducto, cantidad, true)); // Agregar el movimiento al historial
        guardarMovimientosEnArchivo(_currentLanguage); // Guardar los movimientos en el archivo después de agregar stock
        guardarInventarioEnArchivo(_currentLanguage); // Guardar el inventario en el archivo después de agregar stock
    }

    // Función para retirar stock de un producto
    void retirarStock(const string& codigoProducto, int cantidad, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Si el producto existe en el inventario
        if (inventario.find(codigoProducto) != inventario.end()) {
            // Si hay suficiente stock
            if (inventario[codigoProducto] >= cantidad) {
                inventario[codigoProducto] -= cantidad;
                historialMovimientos.push(HISTORIAL_INVENTARIO(codigoProducto, cantidad, false));
                guardarMovimientosEnArchivo(_currentLanguage); // Guardar los movimientos en el archivo después de retirar stock
                guardarInventarioEnArchivo(_currentLanguage); // Guardar el inventario en el archivo después de retirar stock
            }
            else {
                ShowConsoleCursor(false); // Ocultar el cursor de la consola
                cout << MAGENTA_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][153] << endl; // No hay suficiente stock
                Sleep(1500); // Esperar 1.5 segundos
            }
        }
        else {
            ShowConsoleCursor(false); // Ocultar el cursor de la consola
            cout << MAGENTA_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][156] << endl; // El producto no se encuentra en el inventario
            Sleep(1500); // Esperar 1.5 segundos
        }
    }

    // Método para cargar el inventario desde un archivo
    void cargarInventarioDesdeArchivo(string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        ifstream file("inventory.txt");

        // Si el archivo no se pudo abrir
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404] << endl; // No se pudo abrir el archivo inventory.txt para cargar el inventario
            return;
        }

        string codigoProducto;
        int cantidad;

        // Leer el archivo línea por línea
        while (file >> codigoProducto >> cantidad) {
            inventario[codigoProducto] = cantidad;
        }

        file.close();
    }

    // Método para guardar el inventario en un archivo
    void guardarInventarioEnArchivo(string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        ofstream file("inventory.txt");

        // Si el archivo no se pudo abrir
        if (!file.is_open()) {
            cerr << MAGENTA_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][404] << endl; // No se pudo abrir el archivo inventory.txt para guardar el inventario
            return;
        }

        // Escribir el inventario en el archivo
        for (const auto& pair : inventario) {
            file << pair.first << " " << pair.second << endl;
        }

        file.close();
    }

    // Método para guardar el historial de movimientos en un archivo
    void guardarMovimientosEnArchivo(string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        ofstream file("movement_history.txt", ios_base::app); // Abre el archivo en modo de añadir al final

        // Si el archivo no se pudo abrir
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404] << endl;
            return;
        }

        stack<HISTORIAL_INVENTARIO> copiaHistorial = historialMovimientos; // Copia el historial de movimientos

        // Escribir los movimientos en el archivo
        while (!copiaHistorial.empty()) {
            HISTORIAL_INVENTARIO movimiento = copiaHistorial.top();
            copiaHistorial.pop();
            file << movimiento.codigoProducto << " " << movimiento.cantidad << " "; // Código del producto y cantidad
            if (movimiento.esEntrada)
                file << menuTexts[currentLanguage][154]; // Entrada
            else
                file << menuTexts[currentLanguage][155]; // Salida
            file << endl;
        }

        file.close();
    }


    void mostrarHistorialMovimientos(string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Si el historial de movimientos está vacío
        if (historialMovimientos.empty()) {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][157] << RESET_COLOR << endl; // El historial de movimientos está vacío
            return;
        }

        cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][158] << " ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << BLUE_COLOR << menuTexts[currentLanguage][159] << setw(15) << menuTexts[currentLanguage][160] << setw(20) << menuTexts[currentLanguage][161] << setw(20) << menuTexts[currentLanguage][162] << endl;
        cout << RESET_COLOR;

        // Copiar el historial de movimientos para mantener el original intacto
        stack<HISTORIAL_INVENTARIO> copiaHistorial = historialMovimientos;

        while (!copiaHistorial.empty()) {
            HISTORIAL_INVENTARIO movimiento = copiaHistorial.top();
            copiaHistorial.pop();

            // Obtener la fecha y hora actual
            auto now = chrono::system_clock::now();
            time_t now_time = chrono::system_clock::to_time_t(now);
            string formatted_time = ctime(&now_time);

            cout << movimiento.codigoProducto
                << setw(19) << movimiento.cantidad
                << setw(22) << (movimiento.esEntrada ? menuTexts[currentLanguage][154] : menuTexts[currentLanguage][155]) // Entrada o Salida
                << setw(36) << formatted_time;
        }
    }

    void cargarMovimientosDesdeArchivo(string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        ifstream file("movement_history.txt");

        // Si el archivo no se pudo abrir
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404] << endl; // No se pudo abrir el archivo movement_history.txt para cargar el historial de movimientos
            return;
        }

        historialMovimientos = stack<HISTORIAL_INVENTARIO>(); // Limpiar el historial de movimientos

        string linea;

        // Leer el archivo línea por línea
        while (getline(file, linea)) {
            istringstream ss(linea);
            string codigoProducto;
            int cantidad;
            string movimiento;

            // Extraer los datos de la línea
            ss >> codigoProducto >> cantidad >> movimiento;

            // Determinar si es una entrada o una salida
            bool esEntrada = (movimiento == menuTexts[currentLanguage][154]);

            // Agregar el movimiento a la pila
            historialMovimientos.push(HISTORIAL_INVENTARIO(codigoProducto, cantidad, esEntrada));
        }

        file.close();
    }

};