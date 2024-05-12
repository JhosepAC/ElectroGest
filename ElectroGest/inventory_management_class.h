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
    GESTION_INVENTARIO() {
        cargarInventarioDesdeArchivo(); // Cargar el inventario desde el archivo al iniciar el programa
        cargarMovimientosDesdeArchivo(); // Cargar el historial de movimientos desde el archivo al iniciar el programa
    }

    bool existeProducto(const std::string& codigoProducto) const {
        return inventario.find(codigoProducto) != inventario.end();
    }

    void consultarStock(const std::string& codigoProducto) const {
        auto it = inventario.find(codigoProducto);
        if (it != inventario.end()) {
            cout << CYAN_COLOR << "Consulta de Stock:" << RESET_COLOR << std::endl;
            cout << GRAY_COLOR << "Código: " << RESET_COLOR << codigoProducto << std::endl;
            cout << GRAY_COLOR << "Stock actual: " << RESET_COLOR << it->second << std::endl;
            
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar..." << RESET_COLOR << endl;
        }
        else {
            std::cout << DOUBLE_SPACE << RED_COLOR << "El producto con código " << codigoProducto << " no se encuentra en el inventario." << RESET_COLOR << std::endl;
            Sleep(1000); // Esperar 1 segundo (1000 ms)
        }
    }

    bool verificarStock(const std::string& codigoProducto, int cantidad) const {
        auto it = inventario.find(codigoProducto);
        if (it != inventario.end()) {
            return it->second >= cantidad;
        }
        return false; // El producto no está en el inventario
    }

    void verInventario() const {
        if (inventario.empty()) {
            std::cout << DOUBLE_SPACE << MAGENTA_COLOR << "El inventario está vacío." << RESET_COLOR << std::endl;
            Sleep(1000); // Esperar 1 segundo (1000 ms)
            return;
        }

        system("cls"); // Limpiar la pantalla antes de mostrar el inventario

        std::cout << CYAN_COLOR << "=== INVENTARIO ===" << RESET_COLOR << std::endl;
        for (const auto& pair : inventario) {
            cout << YELLOW_COLOR << "Código: " << RESET_COLOR << pair.first << std::endl;
            cout << YELLOW_COLOR << "Stock: " << RESET_COLOR << pair.second << std::endl;
            cout << YELLOW_COLOR << "-------------------------" << std::endl;
        }
        cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar..." << RESET_COLOR << endl;
        _getch(); // Esperar a que el usuario presione una tecla
    }

    void añadirStock(const std::string& codigoProducto, int cantidad) {
        inventario[codigoProducto] += cantidad;
        historialMovimientos.push(HISTORIAL_INVENTARIO(codigoProducto, cantidad, true));
        guardarMovimientosEnArchivo(); // Guardar los movimientos en el archivo después de agregar stock
        guardarInventarioEnArchivo(); // Guardar el inventario en el archivo después de agregar stock
    }

    void retirarStock(const std::string& codigoProducto, int cantidad) {
        if (inventario.find(codigoProducto) != inventario.end()) {
            if (inventario[codigoProducto] >= cantidad) {
                inventario[codigoProducto] -= cantidad;
                historialMovimientos.push(HISTORIAL_INVENTARIO(codigoProducto, cantidad, false));
                guardarMovimientosEnArchivo(); // Guardar los movimientos en el archivo después de retirar stock
                guardarInventarioEnArchivo(); // Guardar el inventario en el archivo después de retirar stock
            }
            else {
                std::cout << MAGENTA_COLOR << DOUBLE_SPACE << "No hay suficiente stock de este producto para retirar." << std::endl;
            }
        }
        else {
            std::cout << MAGENTA_COLOR << DOUBLE_SPACE << "El producto no se encuentra en el inventario." << std::endl;
        }
    }

    // Método para cargar el inventario desde un archivo
    void cargarInventarioDesdeArchivo() {
        std::ifstream file("inventory.txt");
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo inventory.txt" << std::endl;
            return;
        }

        std::string codigoProducto;
        int cantidad;

        while (file >> codigoProducto >> cantidad) {
            inventario[codigoProducto] = cantidad;
        }

        file.close();
    }

    // Método para guardar el inventario en un archivo
    void guardarInventarioEnArchivo() const {
        std::ofstream file("inventory.txt");
        if (!file.is_open()) {
            std::cerr << MAGENTA_COLOR << DOUBLE_SPACE << "No se pudo abrir el archivo inventory.txt para guardar el inventario." << std::endl;
            return;
        }

        for (const auto& pair : inventario) {
            file << pair.first << " " << pair.second << std::endl;
        }

        file.close();
    }

    // Método para guardar el historial de movimientos en un archivo
    void guardarMovimientosEnArchivo() const {
        std::ofstream file("movement_history.txt", std::ios_base::app); // Abre el archivo en modo de añadir al final
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo movement_history.txt para guardar los movimientos." << std::endl;
            return;
        }

        std::stack<HISTORIAL_INVENTARIO> copiaHistorial = historialMovimientos; // Copia el historial de movimientos

        // Escribir los movimientos en el archivo
        while (!copiaHistorial.empty()) {
            HISTORIAL_INVENTARIO movimiento = copiaHistorial.top();
            copiaHistorial.pop();
            file << movimiento.codigoProducto << " " << movimiento.cantidad << " ";
            if (movimiento.esEntrada)
                file << "Entrada";
            else
                file << "Salida";
            file << std::endl;
        }

        file.close();
    }


    void mostrarHistorialMovimientos() const {
        if (historialMovimientos.empty()) {
            std::cout << DOUBLE_SPACE << MAGENTA_COLOR << "El historial de movimientos está vacío." << RESET_COLOR << std::endl;
            return;
        }

        cout << CYAN_COLOR << "=== Historial de Movimientos ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << BLUE_COLOR << "Código Producto" << std::setw(15) << "Cantidad" << std::setw(20) << "Movimiento" << std::setw(30) << "Fecha y Hora" << std::endl;

        // Copiar el historial de movimientos para mantener el original intacto
        std::stack<HISTORIAL_INVENTARIO> copiaHistorial = historialMovimientos;

        while (!copiaHistorial.empty()) {
            HISTORIAL_INVENTARIO movimiento = copiaHistorial.top();
            copiaHistorial.pop();

            // Obtener la fecha y hora actual
            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);
            std::string formatted_time = std::ctime(&now_time);

            cout << movimiento.codigoProducto
                << setw(20) << movimiento.cantidad
                << setw(30) << (movimiento.esEntrada ? "Entrada" : "Salida")
                << setw(40) << formatted_time;
        }
    }

    void cargarMovimientosDesdeArchivo() {
        std::ifstream file("movement_history.txt");
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo movement_history.txt" << std::endl;
            return;
        }

        historialMovimientos = std::stack<HISTORIAL_INVENTARIO>(); // Limpiar el historial de movimientos

        std::string linea;
        while (std::getline(file, linea)) {
            std::istringstream ss(linea);
            std::string codigoProducto;
            int cantidad;
            std::string movimiento;

            // Extraer los datos de la línea
            ss >> codigoProducto >> cantidad >> movimiento;

            // Determinar si es una entrada o una salida
            bool esEntrada = (movimiento == "Entrada");

            // Agregar el movimiento a la pila
            historialMovimientos.push(HISTORIAL_INVENTARIO(codigoProducto, cantidad, esEntrada));
        }

        file.close();
    }

};