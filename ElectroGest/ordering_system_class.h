#pragma once
#include <vector>
#include <fstream>
#include <iomanip>
#include "order_class.h"
#include <conio.h>

class SISTEMA_PEDIDOS {
private:
    std::vector<PEDIDO> pedidosPendientes;
    std::vector<PEDIDO> pedidosProcesados;

public:

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

    // Método para guardar pedidos en un archivo
    void guardarPedidos(const std::vector<PEDIDO>& pedidos) {
        std::ofstream file("pending_orders.txt", std::ios::app);
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo pending_orders.txt para guardar los pedidos." << std::endl;
            return;
        }

        for (const auto& pedido : pedidos) {
            file << pedido.getCodigoProducto() << " " << pedido.getCantidad() << std::endl;
            pedidosPendientes.push_back(pedido);
        }

        file.close();
    }

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

        while (file >> codigoProducto >> cantidad) {
            pedidosProcesados.push_back(PEDIDO(codigoProducto, cantidad));
        }

        file.close();
    }

    // Método para mostrar los pedidos pendientes
    void verPedidosPendientes() const {
        ShowConsoleCursor(false);
        if (pedidosPendientes.empty()) {
            std::cout << endl << MAGENTA_COLOR << "No hay pedidos pendientes.";
            _sleep(1500);
        }
        else {
            system("cls");
            std::cout << CYAN_COLOR << "=== PEDIDOS PENDIENTES ===" << DOUBLE_SPACE;
            for (const auto& pedido : pedidosPendientes) {
                std::cout << BLUE_COLOR << "Código: " << RESET_COLOR << pedido.getCodigoProducto() << BLUE_COLOR << ", Cantidad: " << RESET_COLOR << pedido.getCantidad() << "\n";
            }
            std::cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
            _getch();
            system("cls");
        }
    }

    // Método para mostrar los pedidos procesados
    void verPedidosProcesados() const {
        ShowConsoleCursor(false);
        if (pedidosProcesados.empty()) {
            std::cout << endl << MAGENTA_COLOR << "No hay pedidos procesados.";
            _sleep(1500);
        }
        else {
            system("cls");
            std::cout << CYAN_COLOR << "=== Pedidos Procesados ===" << DOUBLE_SPACE;
            for (const auto& pedido : pedidosProcesados) {
                std::cout << BLUE_COLOR <<  "Código: " << RESET_COLOR << pedido.getCodigoProducto() << BLUE_COLOR <<", Cantidad: " << RESET_COLOR << pedido.getCantidad() << "\n";
            }
            std::cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
            _getch();
        }
    }

    // Método para eliminar todos los pedidos
    void eliminarPedidos() {
        ShowConsoleCursor(false);
        if (pedidosPendientes.empty()) {
            std::cout << endl << MAGENTA_COLOR << "No hay pedidos pendientes que eliminar.";
            _sleep(1500);
            return;
        }
        pedidosPendientes.clear();
        pedidosProcesados.clear();
        std::ofstream filePendientes("pending_orders.txt");
        std::ofstream fileProcesados("orders_processed.txt");
        filePendientes.close();
        fileProcesados.close();
        std::cout << endl << GREEN_COLOR << "Todos los pedidos han sido eliminados.";
        _sleep(1500);
    }

    // Método para mostrar el historial de pedidos
    void mostrarHistorialPedidos() const {
        std::cout << CYAN_COLOR << "=== Historial de Pedidos ===" << DOUBLE_SPACE;

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
    }

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