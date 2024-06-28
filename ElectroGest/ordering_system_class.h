#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "order_class.h"
#include "Graph.h"

class SISTEMA_PEDIDOS {
private:
    vector<PEDIDO> pedidosPendientes;
    vector<PEDIDO> pedidosProcesados;

    string getFileNamePendientes() const { return "pending_orders.txt"; }
    string getFileNameProcesados() const { return "orders_processed.txt"; }

    // Método para cargar pedidos desde un archivo
    void cargarPedidos(const string& filename, vector<PEDIDO>& pedidos) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo " << filename << endl;
            return;
        }

        string clienteID, codigoProducto, direccionEntrega;
        int cantidad; 
        double precio;
        pedidos.clear();
        while (file >> clienteID >> codigoProducto >> cantidad >> precio >> ws && getline(file, direccionEntrega)) {
            pedidos.push_back(PEDIDO(clienteID, codigoProducto, cantidad, precio, direccionEntrega));
        }

        file.close();
    }

    // Método para guardar pedidos en un archivo
    void guardarPedidos(const string& filename, const vector<PEDIDO>& pedidos) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo " << filename << endl;
            return;
        }

        for (const auto& pedido : pedidos) {
            file << pedido.getClienteID() << " " << pedido.getCodigoProducto() << " " << pedido.getPrecio() <<" " << pedido.getCantidad() << " " << pedido.getDireccionEntrega() << endl;
        }

        file.close();
    }

public:
    SISTEMA_PEDIDOS() {
        cargarPedidosPendientes();
        cargarPedidosProcesados();
    }

    int getNumPedidosPendientes() const {
		return pedidosPendientes.size();
	}

    PEDIDO getPedidoPendientePorIndice(int indice) {
        if (indice >= 0 && indice < pedidosPendientes.size()) {
            return pedidosPendientes[indice];
        }
        else {
            throw out_of_range("Índice fuera de rango.");
        }
    }

    void eliminarPedidoPorIndice(int indice) {
        if (indice >= 0 && indice < pedidosPendientes.size()) {
            pedidosPendientes.erase(pedidosPendientes.begin() + indice);
        }
        else {
            throw out_of_range("Índice fuera de rango.");
        }
    }

    // Método para cargar pedidos pendientes
    void cargarPedidosPendientes() {
        cargarPedidos(getFileNamePendientes(), pedidosPendientes);
    }

    // Método para cargar pedidos procesados
    void cargarPedidosProcesados() {
        cargarPedidos(getFileNameProcesados(), pedidosProcesados);
    }

    // Método para guardar pedidos pendientes
    void guardarPedidosPendientes() const {
        guardarPedidos(getFileNamePendientes(), pedidosPendientes);
    }

    // Método para guardar pedidos procesados
    void guardarPedidosProcesados() const {
        guardarPedidos(getFileNameProcesados(), pedidosProcesados);
    }

    // Método para agregar un pedido pendiente
    void agregarPedidoPendiente(const PEDIDO& pedido) {
        pedidosPendientes.push_back(pedido);
        guardarPedidosPendientes();
    }

    // Método para procesar un pedido
    void procesarPedido(int indice) {
        if (indice >= 0 && indice < pedidosPendientes.size()) {
            PEDIDO pedido = pedidosPendientes[indice];
            pedidosProcesados.push_back(pedido);
            pedidosPendientes.erase(pedidosPendientes.begin() + indice);
            guardarPedidosPendientes();
            guardarPedidosProcesados();
        }
        else {
            cout << "Índice de pedido inválido." << endl;
        }
    }

    // Método para mostrar todos los pedidos pendientes (vendedor)
    void verTodosPedidosPendientes() const {
        ShowConsoleCursor(false);
        system("cls");
        cout << CYAN_COLOR << "=== TODOS LOS PEDIDOS PENDIENTES ===" << DOUBLE_SPACE;

        if (pedidosPendientes.empty()) {
            cout << MAGENTA_COLOR << "No hay pedidos pendientes." << endl;
        }
        else {
            for (const auto& pedido : pedidosPendientes) {
                cout << YELLOW_COLOR << "ID Cliente: " << RESET_COLOR << pedido.getClienteID() << GRAY_COLOR << "," << BLUE_COLOR << " Código: " << RESET_COLOR << pedido.getCodigoProducto() << GRAY_COLOR << "," << BLUE_COLOR << " Cantidad: " << RESET_COLOR << pedido.getCantidad() << endl;
            }
        }

        cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar..." << endl;
        _getch();
        system("cls");
    }

    void verHistorialPedidosCliente(const string& clienteID) const {
        system("cls");
        ShowConsoleCursor(false);

        cout << CYAN_COLOR << "=== PEDIDOS PROCESADOS ===" << DOUBLE_SPACE;

        bool hayPedidosProcesados = false;
        for (const auto& pedido : pedidosProcesados) {
            if (pedido.getClienteID() == clienteID) {
                hayPedidosProcesados = true;
                cout << BLUE_COLOR << "Código: " << RESET_COLOR << pedido.getCodigoProducto() << GRAY_COLOR << "," << BLUE_COLOR << " Cantidad: " << RESET_COLOR << pedido.getCantidad();
            }
        }

        if (!hayPedidosProcesados) {
            cout << MAGENTA_COLOR << "No hay pedidos procesados para el cliente " << clienteID << DOUBLE_SPACE;
        }

        cout << DOUBLE_SPACE << CYAN_COLOR << "=== PEDIDOS PENDIENTES ===" << DOUBLE_SPACE;

        bool hayPedidosPendientes = false;
        for (const auto& pedido : pedidosPendientes) {
            if (pedido.getClienteID() == clienteID) {
                hayPedidosPendientes = true;
                cout << BLUE_COLOR << "Código: " << RESET_COLOR << pedido.getCodigoProducto() << GRAY_COLOR << "," << BLUE_COLOR << " Cantidad: " << RESET_COLOR << pedido.getCantidad() << endl;
            }
        }

        if (!hayPedidosPendientes) {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "No hay pedidos pendientes para el cliente " << clienteID;
        }

        cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar..." << endl;
        _getch();
        system("cls");
    }

    // Método para mostrar todos los pedidos procesados (vendedor)
    void verTodosPedidosProcesados() const {
        ShowConsoleCursor(false);
        system("cls");
        cout << CYAN_COLOR << "=== TODOS LOS PEDIDOS PROCESADOS ===" << DOUBLE_SPACE;

        if (pedidosProcesados.empty()) {
            cout << MAGENTA_COLOR << "No hay pedidos procesados." << endl;
        }
        else {
            for (const auto& pedido : pedidosProcesados) {
                cout << YELLOW_COLOR << "ID Cliente: " << RESET_COLOR << pedido.getClienteID() << GRAY_COLOR << "," << BLUE_COLOR << " Código: " << RESET_COLOR << pedido.getCodigoProducto() << GRAY_COLOR << "," << BLUE_COLOR << " Cantidad: " << RESET_COLOR << pedido.getCantidad() << endl;
            }
        }

        cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
        _getch();
        system("cls");
    }

    void verHistorialPedidosVendedor() const {
        ShowConsoleCursor(false);
		system("cls");
		cout << CYAN_COLOR << "           === HISTORIAL DE PEDIDOS ===" << DOUBLE_SPACE;

        cout << CYAN_COLOR << "     === TODOS LOS PEDIDOS PROCESADOS === " << DOUBLE_SPACE;

        if (pedidosProcesados.empty()) {
            cout << MAGENTA_COLOR << "No hay pedidos procesados." << endl;
        }
        else {
            for (const auto& pedido : pedidosProcesados) {
                cout << YELLOW_COLOR << "ID Cliente: " << RESET_COLOR << pedido.getClienteID() << GRAY_COLOR << "," << BLUE_COLOR << " Código: " << RESET_COLOR << pedido.getCodigoProducto() << GRAY_COLOR << "," << BLUE_COLOR << " Cantidad: " << RESET_COLOR << pedido.getCantidad() << endl;
            }
        }

        cout << CYAN_COLOR << DOUBLE_SPACE << "     === TODOS LOS PEDIDOS PENDIENTES ===" << DOUBLE_SPACE;

        if (pedidosPendientes.empty()) {
            cout << MAGENTA_COLOR << "No hay pedidos pendientes." << endl;
        }
        else {
            for (const auto& pedido : pedidosPendientes) {
                cout << YELLOW_COLOR << "ID Cliente: " << RESET_COLOR << pedido.getClienteID() << GRAY_COLOR << "," << BLUE_COLOR << " Código: " << RESET_COLOR << pedido.getCodigoProducto() << GRAY_COLOR << "," << BLUE_COLOR << " Cantidad: " << RESET_COLOR << pedido.getCantidad() << endl;
            }
        }

        cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar..." << endl;
        _getch();

    }

    void procesarPedidosMenu(Graph& g) const {

        SISTEMA_PEDIDOS sistemaPedidos;
        GESTION_INVENTARIO inventario;

        inventario.cargarInventarioDesdeArchivo();

        cout << CYAN_COLOR << "     === TODOS LOS PEDIDOS PENDIENTES ===" << DOUBLE_SPACE;

        if (pedidosPendientes.empty()) {
            cout << MAGENTA_COLOR << "No hay pedidos pendientes." << endl;
        }
        else {
            for (const auto& pedido : pedidosPendientes) {
                cout << YELLOW_COLOR << "ID Cliente: " << RESET_COLOR << pedido.getClienteID() << GRAY_COLOR << "," << BLUE_COLOR << " Código: " << RESET_COLOR << pedido.getCodigoProducto() << GRAY_COLOR << "," << BLUE_COLOR << " Cantidad: " << RESET_COLOR << pedido.getCantidad() << endl;
            }
        }

        ShowConsoleCursor(true); // Muestra el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese el índice del pedido a procesar: " << RESET_COLOR;
        int indicePedido;
        cin >> indicePedido;
        if (indicePedido >= 0 && indicePedido < sistemaPedidos.getNumPedidosPendientes()) {
            PEDIDO pedido = sistemaPedidos.getPedidoPendientePorIndice(indicePedido);
            if (inventario.verificarStock(pedido.getCodigoProducto(), pedido.getCantidad())) {
                system("cls");
                // Mostrar información del pedido
                cout << CYAN_COLOR << "=== INFORMACIÓN DEL PEDIDO ===" << DOUBLE_SPACE;
                cout << YELLOW_COLOR << "Cliente ID: " << RESET_COLOR << pedido.getClienteID() << endl;
                cout << YELLOW_COLOR << "Código del producto: " << RESET_COLOR << pedido.getCodigoProducto() << endl;
                cout << YELLOW_COLOR << "Cantidad: " << RESET_COLOR << pedido.getCantidad() << endl;
                cout << YELLOW_COLOR << "Dirección de entrega: " << RESET_COLOR << pedido.getDireccionEntrega() << DOUBLE_SPACE;

                // Seleccionar sucursal más cercana
                g.showMenu();

                // Procesar el pedido
                inventario.retirarStock(pedido.getCodigoProducto(), pedido.getCantidad());
                sistemaPedidos.procesarPedido(indicePedido);
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << GREEN_COLOR << "Pedido procesado correctamente.";
                cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
                _getch();
            }
            else {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << RED_COLOR << "No hay suficiente stock para procesar este pedido.";
                Sleep(1500);
            }
        }
        else {
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Índice de pedido inválido.\n";
            Sleep(1500);
        }

    }

};