#pragma once
#include <vector>
#include <fstream>
#include <iomanip>
#include "order_class.h"
#include <conio.h>

class SISTEMA_PEDIDOS {
private:
    vector<PEDIDO> pedidosPendientes;
    vector<PEDIDO> pedidosProcesados;

public:

    // Método para obtener un pedido pendiente por índice
    PEDIDO getPedidoPendientePorIndice(int indice, string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Verificar si el índice es válido
        if (indice >= 0 && indice < pedidosPendientes.size()) {
            return pedidosPendientes[indice]; // Devolver el pedido pendiente
        }
        else {
            // Manejo de error: Índice fuera de rango
            throw out_of_range(menuTexts[currentLanguage][73]); // Índice de pedido inválido.
        }
    }

    // Método para guardar pedidos en un archivo
    void guardarPedidos(const vector<PEDIDO>& pedidos, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Abrir el archivo de pedidos pendientes
        ofstream file("pending_orders.txt", ios::app);
        
        // Verificar si se pudo abrir el archivo
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404] << endl; // No se pudo abrir el archivo pending_orders.txt para guardar los pedidos.
            return;
        }

        // Guardar los pedidos en el archivo
        for (const auto& pedido : pedidos) {
            file << pedido.getCodigoProducto() << " " << pedido.getCantidad() << endl; // Código: Cantidad
            pedidosPendientes.push_back(pedido); // Agregar el pedido a la lista de pedidos pendientes
        }

        file.close();
    }

    // Método para guardar pedidos pendientes en un archivo
    void guardarPedidosPendientes(string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Abrir el archivo de pedidos pendientes
        ofstream file("pending_orders.txt");

        // Verificar si se pudo abrir el archivo
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404]; // No se pudo abrir el archivo pending_orders.txt para guardar los pedidos.
            return;
        }

        // Guardar los pedidos pendientes en el archivo
        for (const auto& pedido : pedidosPendientes) {
            file << pedido.getCodigoProducto() << " " << pedido.getCantidad() << endl; // Código: Cantidad
        }

        file.close();
    }

    // Método para guardar pedidos procesados en un archivo
    void guardarPedidosProcesados(string _currentLanguage) const {
        
        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        ofstream file("orders_processed.txt");

        // Verificar si se pudo abrir el archivo
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404]; // No se pudo abrir el archivo orders_processed.txt para guardar los pedidos.
            return;
        }

        // Guardar los pedidos procesados en el archivo
        for (const auto& pedido : pedidosProcesados) {
            file << pedido.getCodigoProducto() << " " << pedido.getCantidad() << endl; // Código: Cantidad
        }

        file.close();
    }
                           
    // Método para cargar pedidos pendientes desde un archivo
    void cargarPedidosPendientes(string _currentLanguage) {
        
        string codigoProducto;
        int cantidad;

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;
        
        // Leer los pedidos pendientes desde un archivo
        ifstream file("pending_orders.txt");

        // Verificar si se pudo abrir el archivo
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404] << endl; // No se pudo abrir el archivo pending_orders.txt para cargar los pedidos.
            return;
        }

        // Leer los pedidos del archivo
        while (file >> codigoProducto >> cantidad) {
            pedidosPendientes.push_back(PEDIDO(codigoProducto, cantidad));
        }

        file.close();
    }

    // Método para cargar pedidos procesados desde un archivo
    void cargarPedidosProcesados(string _currentLanguage) {

        string codigoProducto;
        int cantidad;

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Abrir el archivo de pedidos procesados
        ifstream file("orders_processed.txt");

        // Verificar si se pudo abrir el archivo
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404] << endl; // No se pudo abrir el archivo orders_processed.txt para cargar los pedidos.
            return;
        }

        // Leer los pedidos del archivo
        while (file >> codigoProducto >> cantidad) {
            pedidosProcesados.push_back(PEDIDO(codigoProducto, cantidad)); // Código: Cantidad
        }

        file.close();
    }

    // Método para mostrar los pedidos pendientes
    void verPedidosPendientes(string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        ShowConsoleCursor(false);

        // Verificar si hay pedidos pendientes
        if (pedidosPendientes.empty()) {
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][163]; // No hay pedidos pendientes.
            _sleep(1500);
        }
        else {
            system("cls");
            cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][164] << " ===" << DOUBLE_SPACE; // Pedidos Pendientes
            
            // Mostrar los pedidos pendientes
            for (const auto& pedido : pedidosPendientes) {
                cout << BLUE_COLOR << menuTexts[currentLanguage][147] << RESET_COLOR << pedido.getCodigoProducto() << BLUE_COLOR << ", " << menuTexts[currentLanguage][160] << RESET_COLOR << pedido.getCantidad() << endl; // Código: Cantidad
            }
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51]; // Presione cualquier tecla para continuar...
            _getch();
            system("cls");
        }
    }

    // Método para mostrar los pedidos procesados
    void verPedidosProcesados(string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        ShowConsoleCursor(false);
        // Verificar si hay pedidos procesados
        if (pedidosProcesados.empty()) {
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][165]; // No hay pedidos procesados.
            _sleep(1500);
        }
        else {
            system("cls");
            cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][166] << " ===" << DOUBLE_SPACE; // Pedidos Procesados

            // Mostrar los pedidos procesados
            for (const auto& pedido : pedidosProcesados) {
                cout << BLUE_COLOR << menuTexts[currentLanguage][147] << RESET_COLOR << pedido.getCodigoProducto() << BLUE_COLOR <<", " << menuTexts[currentLanguage][160] << RESET_COLOR << pedido.getCantidad() << endl; // Código: Cantidad
            }
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51]; // Presione cualquier tecla para continuar...
            _getch();
        }
    }

    // Método para eliminar todos los pedidos
    void eliminarPedidos(string _currentLenguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLenguage;

        ShowConsoleCursor(false);

        // Verificar si hay pedidos pendientes
        if (pedidosPendientes.empty()) {
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][163]; // No hay pedidos pendientes.
            _sleep(1500);
            return;
        }

        // Confirmar si se desea eliminar todos los pedidos
        pedidosPendientes.clear();
        pedidosProcesados.clear();
        ofstream filePendientes("pending_orders.txt");
        ofstream fileProcesados("orders_processed.txt");
        filePendientes.close();
        fileProcesados.close();
        cout << endl << GREEN_COLOR << menuTexts[currentLanguage][167]; // Pedidos eliminados con éxito.
        _sleep(1500);
    }

    // Método para mostrar el historial de pedidos
    void mostrarHistorialPedidos(string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][168] << " ===" << DOUBLE_SPACE; // Historial de Pedidos

        // Mostrar pedidos pendientes
        cout << YELLOW_COLOR << menuTexts[currentLanguage][169] << RESET_COLOR << endl; // Pedidos Pendientes
        if (pedidosPendientes.empty()) {
            cout << MAGENTA_COLOR << menuTexts[currentLanguage][163] << RESET_COLOR << endl; // No hay pedidos pendientes.
        }
        else {
            for (const auto& pedido : pedidosPendientes) {
                cout << BLUE_COLOR << menuTexts[currentLanguage][147] << RESET_COLOR << pedido.getCodigoProducto() << BLUE_COLOR << ", " << menuTexts[currentLanguage][160] << RESET_COLOR << pedido.getCantidad() << endl; // Código: Cantidad
            }
        }

        // Mostrar pedidos procesados
        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][170] << RESET_COLOR << endl; // Pedidos Procesados

        // Verificar si hay pedidos procesados
        if (pedidosProcesados.empty()) {
            cout << MAGENTA_COLOR << menuTexts[currentLanguage][165] << RESET_COLOR << endl; // No hay pedidos procesados.
        }
        else {
            // Mostrar los pedidos procesados
            for (const auto& pedido : pedidosProcesados) {
                cout << BLUE_COLOR << menuTexts[currentLanguage][147] << RESET_COLOR << pedido.getCodigoProducto() << BLUE_COLOR << ", " << menuTexts[currentLanguage][160] << RESET_COLOR << pedido.getCantidad() << endl; // Código: Cantidad
            }
        }
    }

    void procesarPedido(int indice, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        if (indice >= 0 && indice < pedidosPendientes.size()) {
            PEDIDO pedido = pedidosPendientes[indice];
            // Mover el pedido a la lista de pedidos procesados
            pedidosProcesados.push_back(pedido);
            // Eliminar el pedido de la lista de pedidos pendientes
            pedidosPendientes.erase(pedidosPendientes.begin() + indice);
            // Actualizar los archivos de pedidos pendientes y procesados
            guardarPedidosPendientes(currentLanguage);
            guardarPedidosProcesados(currentLanguage);
        }
        else {
            cout << MAGENTA_COLOR << menuTexts[currentLanguage][73]; // Índice de pedido inválido.
            Sleep(1500);
        }
    }

    // Método para obtener el número de pedidos pendientes
    int getNumPedidosPendientes() const { return pedidosPendientes.size(); }

};