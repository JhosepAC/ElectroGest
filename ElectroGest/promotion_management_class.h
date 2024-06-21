// promotion_manager.h
#pragma once
#include "promotion_class.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

class GESTION_PROMOCIONES {
    std::unordered_map<std::string, PROMOCION> promociones;

public:
    GESTION_PROMOCIONES() {
        cargarDesdeArchivo();
    }

    void cargarDesdeArchivo() {
        std::ifstream file("promotions.txt");
        if (!file.is_open()) {
            std::cerr << "Error al abrir el archivo promotions.txt" << std::endl;
            return;
        }

        std::string line, codigoProducto, descripcion;
        int descuento;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::getline(iss, codigoProducto, ',');
            iss >> descuento;
            iss.ignore(1, ',');
            std::getline(iss, descripcion);

            PROMOCION promocion(codigoProducto, descuento, descripcion);
            promociones[codigoProducto] = promocion;
        }

        file.close();
    }

    void guardarEnArchivo() {
        std::ofstream file("promotions.txt");
        if (!file.is_open()) {
            std::cerr << "Error al abrir el archivo promotions.txt" << std::endl;
            return;
        }

        for (const auto& entry : promociones) {
            const PROMOCION& promocion = entry.second;
            file << promocion.codigoProducto << "," << promocion.descuento << "," << promocion.descripcion << std::endl;
        }

        file.close();
    }

    void agregarPromocion(const PROMOCION& promocion) {
        promociones[promocion.codigoProducto] = promocion;
        guardarEnArchivo();
    }

    void eliminarPromocion(const std::string& codigoProducto) {
        promociones.erase(codigoProducto);
        guardarEnArchivo();
    }

    bool tienePromocion(const std::string& codigoProducto) const {
        return promociones.find(codigoProducto) != promociones.end();
    }

    PROMOCION obtenerPromocion(const std::string& codigoProducto) const {
        auto it = promociones.find(codigoProducto);
        if (it != promociones.end()) {
            return it->second;
        }
        return PROMOCION("", 0.0, "");
    }

    void mostrarPromociones() const {

        if (promociones.empty()) {
            std::cout << DOUBLE_SPACE << MAGENTA_COLOR << "No hay promociones disponibles." << std::endl;
        }
        else {
            system("cls");

            std::cout << CYAN_COLOR << std::setw(15) << std::left << "PRODUCTO"
                << std::setw(15) << std::left << "DESCUENTO"
                << std::setw(50) << std::left << "DESCRIPCIÓN" << std::endl;
            std::cout << GRAY_COLOR << std::string(80, '-') << std::endl;

            for (const auto& entry : promociones) {
                const PROMOCION& promocion = entry.second;
                std::cout << RESET_COLOR << std::setw(15) << std::left << promocion.codigoProducto
                    << std::setw(15) << std::left << promocion.descuento
                    << std::setw(50) << std::left << promocion.descripcion << std::endl;
            }

            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
            _getch();
        }
        
    }
};
