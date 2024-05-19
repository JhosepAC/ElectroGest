#pragma once
#include <vector>
#include <fstream>
#include <iomanip>
#include "order_class.h"
#include <conio.h>
#include <stdexcept> // para manejar excepciones

class SISTEMA_PEDIDOS {
private:
    std::vector<PEDIDO> pedidosPendientes;
    std::vector<PEDIDO> pedidosProcesados;

public:
    // Método para obtener el número de pedidos pendientes
    int getNumPedidosPendientes() const {
        return pedidosPendientes.size();
    }

    // Método para obtener un pedido pendiente por índice
    PEDIDO getPedidoPendientePorIndice(int indice) const {
        if (indice >= 0 && indice < pedidosPendientes.size()) {
            return pedidosPendientes[indice];
        }
        else {
            // Manejo de error: Índice fuera de rango
            throw std::out_of_range("Índice de pedido pendiente fuera de rango.");
        }
    }

    // Método para agregar un pedido pendiente
    void agregarPedidoPendiente(const PEDIDO& pedido) {
        pedidosPendientes.push_back(pedido);
        guardarPedidosPendientes(); // Actualizamos el archivo inmediatamente
    }

    // Método para guardar pedidos pendientes en un archivo
    void guardarPedidosPendientes() const {
        std::ofstream file("pending_orders.txt");
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo pending_orders.txt para guardar los pedidos pendientes.\n";
            return;
        }

        for (const auto& pedido : pedidosPendientes) {
            file << pedido.getCodigoProducto() << " " << pedido.getCantidad() << std::endl;
        }

        file.close();
    }

    // Método para guardar pedidos procesados en un archivo
    void guardarPedidosProcesados() const {
        std::ofstream file("orders_processed.txt");
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo orders_processed.txt para guardar los pedidos procesados.\n";
            return;
        }

        for (const auto& pedido : pedidosProcesados) {
            file << pedido.getCodigoProducto() << " " << pedido.getCantidad() << std::endl;
        }

        file.close();
    }

    // Método para cargar pedidos pendientes desde un archivo
    void cargarPedidosPendientes() {
        std::ifstream file("pending_orders.txt");
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo pending_orders.txt" << std::endl;
            return;
        }

        std::string codigoProducto;
        int cantidad;

        pedidosPendientes.clear();
        while (file >> codigoProducto >> cantidad) {
            pedidosPendientes.push_back(PEDIDO(codigoProducto, cantidad));
        }

        file.close();
    }

    // Método para cargar pedidos procesados desde un archivo
    void cargarPedidosProcesados() {
        std::ifstream file("orders_processed.txt");
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo orders_processed.txt" << std::endl;
            return;
        }

        std::string codigoProducto;
        int cantidad;

        pedidosProcesados.clear();
        while (file >> codigoProducto >> cantidad) {
            pedidosProcesados.push_back(PEDIDO(codigoProducto, cantidad));
        }

        file.close();
    }

    // Método para mostrar los pedidos pendientes
    void verPedidosPendientes() const {
        ShowConsoleCursor(false);
        if (pedidosPendientes.empty()) {
            std::cout << std::endl << MAGENTA_COLOR << "No hay pedidos pendientes.";
            Sleep(1500);
        }
        else {
            system("cls");
            std::cout << CYAN_COLOR << "=== PEDIDOS PENDIENTES ===" << DOUBLE_SPACE;
            std::cout << std::left << std::setw(10) << "Índice" << std::setw(20) << "Código Producto" << std::setw(10) << "Cantidad" << std::endl;
            std::cout << std::string(42, '=') << std::endl;
            for (size_t i = 0; i < pedidosPendientes.size(); ++i) {
                std::cout << BLUE_COLOR << std::setw(10) << i << RESET_COLOR
                    << std::setw(20) << pedidosPendientes[i].getCodigoProducto()
                    << std::setw(10) << pedidosPendientes[i].getCantidad() << "\n";
            }
        }
    }

    // Método para mostrar los pedidos procesados
    void verPedidosProcesados() const {
        ShowConsoleCursor(false);
        if (pedidosProcesados.empty()) {
            std::cout << std::endl << MAGENTA_COLOR << "No hay pedidos procesados.";
            Sleep(1500);
        }
        else {
            system("cls");
            std::cout << CYAN_COLOR << "=== PEDIDOS PROCESADOS ===" << DOUBLE_SPACE;
            std::cout << std::left << std::setw(10) << "Índice" << std::setw(20) << "Código Producto" << std::setw(10) << "Cantidad" << std::endl;
            std::cout << std::string(42, '=') << std::endl;
            for (size_t i = 0; i < pedidosProcesados.size(); ++i) {
                std::cout << BLUE_COLOR << std::setw(10) << i << RESET_COLOR
                    << std::setw(20) << pedidosProcesados[i].getCodigoProducto()
                    << std::setw(10) << pedidosProcesados[i].getCantidad() << "\n";
            }
            std::cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
            _getch();
        }
    }

    // Método para eliminar todos los pedidos
    void eliminarPedidos() {
        ShowConsoleCursor(false);
        if (pedidosPendientes.empty()) {
            std::cout << std::endl << MAGENTA_COLOR << "No hay pedidos pendientes que eliminar.";
            Sleep(1500);
            return;
        }
        pedidosPendientes.clear();
        pedidosProcesados.clear();
        std::ofstream filePendientes("pending_orders.txt");
        std::ofstream fileProcesados("orders_processed.txt");
        filePendientes.close();
        fileProcesados.close();
        std::cout << std::endl << GREEN_COLOR << "Todos los pedidos han sido eliminados.";
        Sleep(1500);
    }

    // Método para mostrar el historial de pedidos
    void mostrarHistorialPedidos() const {
        std::cout << CYAN_COLOR << "=== HISTORIAL DE PEDIDOS ===" << DOUBLE_SPACE;

        // Mostrar pedidos pendientes
        std::cout << YELLOW_COLOR << "Pedidos Pendientes:" << RESET_COLOR << std::endl;
        if (pedidosPendientes.empty()) {
            std::cout << MAGENTA_COLOR << "No hay pedidos pendientes." << RESET_COLOR << std::endl;
        }
        else {
            for (const auto& pedido : pedidosPendientes) {
                std::cout << BLUE_COLOR << "Código: " << RESET_COLOR << pedido.getCodigoProducto() << BLUE_COLOR << ", Cantidad: " << RESET_COLOR << pedido.getCantidad() << std::endl;
            }
        }

        // Mostrar pedidos procesados
        std::cout << DOUBLE_SPACE << YELLOW_COLOR << "Pedidos Procesados:" << RESET_COLOR << std::endl;
        if (pedidosProcesados.empty()) {
            std::cout << MAGENTA_COLOR << "No hay pedidos procesados." << RESET_COLOR << std::endl;
        }
        else {
            for (const auto& pedido : pedidosProcesados) {
                std::cout << BLUE_COLOR << "Código: " << RESET_COLOR << pedido.getCodigoProducto() << BLUE_COLOR << ", Cantidad: " << RESET_COLOR << pedido.getCantidad() << std::endl;
            }
        }

        ShowConsoleCursor(false);
        std::cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
        _getch();
    }

    // Método para procesar un pedido
    void procesarPedido(int indice) {
        if (indice >= 0 && indice < pedidosPendientes.size()) {
            PEDIDO pedido = pedidosPendientes[indice];
            // Mover el pedido a la lista de pedidos procesados
            pedidosProcesados.push_back(pedido);
            // Eliminar el pedido de la lista de pedidos pendientes
            pedidosPendientes.erase(pedidosPendientes.begin() + indice);
            // Actualizar los archivos de pedidos pendientes y procesados
            guardarPedidosPendientes();
            guardarPedidosProcesados();
        }
        else {
            std::cout << MAGENTA_COLOR << "Índice de pedido inválido.";
            Sleep(1500);
        }
    }
};