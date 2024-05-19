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
    GESTION_INVENTARIO() {}

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
            ShowConsoleCursor(false); // Ocultar el cursor de la consola
            std::cout << DOUBLE_SPACE << MAGENTA_COLOR << "El inventario está vacío." << RESET_COLOR << std::endl;
            Sleep(1000); // Esperar 1 segundo (1000 ms)
            return;
        }
        
        system("cls"); // Limpiar la pantalla antes de mostrar el inventario

        cout << CYAN_COLOR << "=== INVENTARIO ===" << RESET_COLOR << DOUBLE_SPACE;

        // Imprimir encabezado de la tabla
        cout << BLUE_COLOR << setw(30) << left << "CÓDIGO DEL PRODUCTO" << "STOCK" << RESET_COLOR << endl;
        cout << YELLOW_COLOR << setw(30) << left << "--------------------" << "-----" << RESET_COLOR << endl;
        cout << endl;

        // Imprimir contenido de la tabla
        for (const auto& pair : inventario) {
            cout << setw(30) << left << pair.first << pair.second << endl;
            cout << YELLOW_COLOR << "---------------------------------" << GRAY_COLOR << endl;
        }

        ShowConsoleCursor(false); // Ocultar el cursor de la consola
        cout << endl << GRAY_COLOR << "Presiona cualquier tecla para continuar..." << RESET_COLOR << endl;
        _getch(); // Esperar a que el usuario presione una tecla
    }

    void añadirStock(const std::string& codigoProducto, int cantidad) {
        inventario[codigoProducto] += cantidad;

        // Obtener la fecha y hora actual
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %X");
        std::string formatted_time = ss.str();

        HISTORIAL_INVENTARIO movimiento(codigoProducto, cantidad, true, formatted_time);
        historialMovimientos.push(movimiento);
        guardarMovimientoEnArchivo(movimiento); // Guardar solo el nuevo movimiento
        guardarInventarioEnArchivo(); // Guardar el inventario en el archivo después de agregar stock
    }

    void retirarStock(const std::string& codigoProducto, int cantidad) {
        if (inventario.find(codigoProducto) != inventario.end()) {
            if (inventario[codigoProducto] >= cantidad) {
                inventario[codigoProducto] -= cantidad;

                // Obtener la fecha y hora actual
                auto now = std::chrono::system_clock::now();
                std::time_t now_time = std::chrono::system_clock::to_time_t(now);
                std::stringstream ss;
                ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %X");
                std::string formatted_time = ss.str();

                HISTORIAL_INVENTARIO movimiento(codigoProducto, cantidad, false, formatted_time);
                historialMovimientos.push(movimiento);
                guardarMovimientoEnArchivo(movimiento); // Guardar solo el nuevo movimiento
                guardarInventarioEnArchivo(); // Guardar el inventario en el archivo después de retirar stock
            }
            else {
                ShowConsoleCursor(false); // Ocultar el cursor de la consola
                std::cout << MAGENTA_COLOR << DOUBLE_SPACE << "No hay suficiente stock de este producto para retirar." << std::endl;
                Sleep(1500); // Esperar 1 segundo (1000 ms)
            }
        }
        else {
            ShowConsoleCursor(false); // Ocultar el cursor de la consola
            std::cout << MAGENTA_COLOR << DOUBLE_SPACE << "El producto no se encuentra en el inventario." << std::endl;
            Sleep(1500); // Esperar 1 segundo (1000 ms)
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
    void guardarMovimientoEnArchivo(const HISTORIAL_INVENTARIO& movimiento) const {
        std::ofstream file("movement_history.txt", std::ios_base::app); // Abre el archivo en modo de añadir al final
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo movement_history.txt para guardar los movimientos." << std::endl;
            return;
        }

        file << movimiento.codigoProducto << " "
            << movimiento.cantidad << " "
            << (movimiento.esEntrada ? "Entrada" : "Salida") << " "
            << movimiento.fechaHora << std::endl;

        file.close();
    }

    void mostrarHistorialMovimientos() const {
        if (historialMovimientos.empty()) {
            std::cout << DOUBLE_SPACE << MAGENTA_COLOR << "El historial de movimientos está vacío." << RESET_COLOR << std::endl;
            return;
        }

        std::cout << CYAN_COLOR << "=== Historial de Movimientos ===" << RESET_COLOR << std::endl;
        std::cout << DOUBLE_SPACE;
        std::cout << BLUE_COLOR << std::left << std::setw(20) << "Código Producto"
            << std::setw(15) << "Cantidad"
            << std::setw(20) << "Movimiento"
            << std::setw(20) << "Fecha y Hora"
            << RESET_COLOR << std::endl;
        std::cout << std::string(70, '=') << std::endl;

        // Crear una copia del historial de movimientos para mostrarlo sin modificar el original
        std::stack<HISTORIAL_INVENTARIO> copiaHistorial = historialMovimientos;
        while (!copiaHistorial.empty()) {
            HISTORIAL_INVENTARIO movimiento = copiaHistorial.top();
            copiaHistorial.pop();

            std::cout << DOUBLE_SPACE;
            std::cout << std::left << std::setw(20) << movimiento.codigoProducto
                << std::setw(15) << movimiento.cantidad
                << std::setw(20) << (movimiento.esEntrada ? "Entrada" : "Salida")
                << std::setw(20) << movimiento.fechaHora
                << std::endl;
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
            std::string fechaHora;

            // Leer y parsear cada línea del archivo
            ss >> codigoProducto >> cantidad >> movimiento;
            std::getline(ss, fechaHora); // Leer el resto de la línea como fecha y hora

            // Eliminar cualquier espacio inicial en la fecha y hora
            if (!fechaHora.empty() && fechaHora[0] == ' ') {
                fechaHora.erase(0, 1);
            }

            bool esEntrada = (movimiento == "Entrada");

            // Agregar el movimiento a la pila
            historialMovimientos.push(HISTORIAL_INVENTARIO(codigoProducto, cantidad, esEntrada, fechaHora));
        }

        file.close();
    }

};