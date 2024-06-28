#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include "client_class.h"

class GESTION_CLIENTE {
private:
    ClienteBST clienteBST;

public:

    // Método para registrar un nuevo cliente
    void displayCustomerList() {
        ifstream file("client_registration.txt");
        if (file.is_open()) {
            string line;

            // Imprimir encabezados de la tabla
            cout << CYAN_COLOR
                << left << setw(15) << "ID Cliente"
                << left << setw(15) << "Nombre"
                << setw(20) << "Apellido"
                << setw(35) << "Correo"
                << setw(20) << "Dirección"
                << setw(15) << "Teléfono"
                << setw(25) << "Fecha de Nacimiento"
                << setw(10) << "Género"
                << RESET_COLOR << endl;

            // Imprimir separador de columnas
            cout << YELLOW_COLOR
                << setw(15) << setfill('-') << ""
                << setw(15) << ""
                << setw(20) << ""
                << setw(35) << ""
                << setw(20) << ""
                << setw(15) << ""
                << setw(25) << ""
                << setw(10) << ""
                << setfill(' ') << RESET_COLOR << endl;

            while (getline(file, line)) {
                istringstream iss(line);
                string idCliente, nombre, apellido, correo, contrasenia, direccion, telefono, fechaNacimiento, genero;

                // Leer los campos separados por coma
                getline(iss, idCliente, ',');
                getline(iss, nombre, ',');
                getline(iss, apellido, ',');
                getline(iss, correo, ',');
                getline(iss, contrasenia, ',');
                getline(iss, direccion, ',');
                getline(iss, telefono, ',');
                getline(iss, fechaNacimiento, ',');
                getline(iss, genero, ',');

                // Crear objeto CLIENTE y agregarlo al árbol binario
                CLIENTE cliente({});
                cliente.setIdCliente(idCliente);
                cliente.setNombre(nombre);
                cliente.setApellido(apellido);
                cliente.setCorreoElectronico(correo);
                cliente.setDireccion(direccion);
                cliente.setTelefono(telefono);
                cliente.setFechaNacimiento(fechaNacimiento);
                cliente.setGenero(genero);

                clienteBST.insert(cliente);

                // Mostrar la información del cliente en una sola línea
                cout << left
                    << setw(15) << idCliente
                    << setw(15) << nombre
                    << setw(20) << apellido
                    << setw(35) << correo
                    << setw(20) << direccion
                    << setw(15) << telefono
                    << setw(25) << fechaNacimiento
                    << setw(10) << genero << DOUBLE_SPACE;

            }
            file.close();
            ShowConsoleCurse(false);
            cout << GRAY_COLOR << "\nPresiona cualquier tecla para continuar..." << RESET_COLOR;
            _getch();
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se pudo abrir el archivo de registro de clientes." << endl;
            Sleep(1500);
        }
    }

    // Método para eliminar un nuevo cliente
    void deleteCustomer(string email) {
        vector<string> lines;
        bool found = false; // Variable para rastrear si se encuentra el cliente
        ifstream file("client_registration.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (line.find(email) == string::npos) { // Si la línea no contiene el correo electrónico del cliente a eliminar
                    lines.push_back(line); // Conservar la línea
                }
                else {
                    found = true; // Se encontró el cliente
                    cout << DOUBLE_SPACE << GREEN_COLOR << "Cliente eliminado correctamente." << endl;
                }
            }
            file.close();
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se pudo abrir el archivo de registro de clientes." << endl;
            return;
        }

        // Escribir las líneas restantes en el archivo
        ofstream outFile("client_registration.txt");
        for (const string& line : lines) {
            outFile << line << endl;
        }
        outFile.close();

        // Si el cliente no se encontró, imprimir un mensaje
        if (!found) {
            ShowConsoleCurse(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "El cliente con el correo electrónico " << email << " no se encontró en el archivo." << endl;
            _sleep(1500); // Esperar 1.5 segundos
        }
    }

    // Método para buscar clientes por nombre o apellido
    void searchCustomers(const string& criterion, const string& searchTerm) {
        vector<CLIENTE> results = clienteBST.search(searchTerm, criterion);

        if (results.empty()) {
            ShowConsoleCurse(false);
            cout << MAGENTA_COLOR << DOUBLE_SPACE << "No se encontraron clientes con el criterio proporcionado." << endl;
            _sleep(1500); // Esperar 1.5 segundos
        }
        else {
            ShowConsoleCurse(false);
            cout << CYAN_COLOR << DOUBLE_SPACE << "Clientes encontrados:" << RESET_COLOR << endl;
            for (const CLIENTE& cliente : results) {
                cout << BLUE_COLOR << "Nombres: " << RESET_COLOR << cliente.getNombre() << " " << cliente.getApellido() << endl;
                cout << BLUE_COLOR << "Correo: " << RESET_COLOR << cliente.getCorreoElectronico() << endl;
                cout << BLUE_COLOR << "Dirección: " << RESET_COLOR << cliente.getDireccion() << endl;
                cout << BLUE_COLOR << "Teléfono: " << RESET_COLOR << cliente.getTelefono() << endl;
                cout << BLUE_COLOR << "Fecha de nacimiento: " << RESET_COLOR << cliente.getFechaNacimiento() << endl;
                cout << BLUE_COLOR << "Género: " << RESET_COLOR << cliente.getGenero() << endl;
                cout << DOUBLE_SPACE;
            }
            cout << GRAY_COLOR << "Presiona cualquier tecla para continuar..." << RESET_COLOR;
            _getch();
        }
    }
    void modificarCliente(const string& email) {
        vector<string> lines;
        bool found = false;
        ifstream file("client_registration.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                if (line.find(email) != string::npos) {
                    found = true;
                    CLIENTE cliente({});
                    istringstream iss(line);
                    string idCliente, nombre, apellido, correo, contrasenia, direccion, telefono, fechaNacimiento, genero;
                    getline(iss, idCliente, ',');
                    getline(iss, nombre, ',');
                    getline(iss, apellido, ',');
                    getline(iss, correo, ',');
                    getline(iss, contrasenia, ',');
                    getline(iss, direccion, ',');
                    getline(iss, telefono, ',');
                    getline(iss, fechaNacimiento, ',');
                    getline(iss, genero, ',');

                    cliente.setIdCliente(idCliente);
                    cliente.setNombre(nombre);
                    cliente.setApellido(apellido);
                    cliente.setCorreoElectronico(correo);
                    cliente.setDireccion(direccion);
                    cliente.setTelefono(telefono);
                    cliente.setFechaNacimiento(fechaNacimiento);
                    cliente.setGenero(genero);

                    cout << YELLOW_COLOR << "Modificar los datos del cliente:" << RESET_COLOR << endl;
                    cout << BLUE_COLOR << "Nombre [" << nombre << "]: " << RESET_COLOR;
                    getline(cin, nombre);
                    if (!nombre.empty()) cliente.setNombre(nombre);

                    cout << BLUE_COLOR << "Apellido [" << apellido << "]: " << RESET_COLOR;
                    getline(cin, apellido);
                    if (!apellido.empty()) cliente.setApellido(apellido);

                    cout << BLUE_COLOR << "Correo [" << correo << "]: " << RESET_COLOR;
                    getline(cin, correo);
                    if (!correo.empty()) cliente.setCorreoElectronico(correo);

                    cout << BLUE_COLOR << "Dirección [" << direccion << "]: " << RESET_COLOR;
                    getline(cin, direccion);
                    if (!direccion.empty()) cliente.setDireccion(direccion);

                    cout << BLUE_COLOR << "Teléfono [" << telefono << "]: " << RESET_COLOR;
                    getline(cin, telefono);
                    if (!telefono.empty()) cliente.setTelefono(telefono);

                    cout << BLUE_COLOR << "Fecha de Nacimiento [" << fechaNacimiento << "]: " << RESET_COLOR;
                    getline(cin, fechaNacimiento);
                    if (!fechaNacimiento.empty()) cliente.setFechaNacimiento(fechaNacimiento);

                    cout << BLUE_COLOR << "Género [" << genero << "]: " << RESET_COLOR;
                    getline(cin, genero);
                    if (!genero.empty()) cliente.setGenero(genero);

                    ostringstream oss;
                    oss << cliente.getIdCliente() << ","
                        << cliente.getNombre() << ","
                        << cliente.getApellido() << ","
                        << cliente.getCorreoElectronico() << ","
                        << contrasenia << ","
                        << cliente.getDireccion() << ","
                        << cliente.getTelefono() << ","
                        << cliente.getFechaNacimiento() << ","
                        << cliente.getGenero();
                    lines.push_back(oss.str());
                }
                else {
                    lines.push_back(line);
                }
            }
            file.close();
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se pudo abrir el archivo de registro de clientes." << endl;
            return;
        }

        ofstream outFile("client_registration.txt");
        for (const string& line : lines) {
            outFile << line << endl;
        }
        outFile.close();

        if (found) {
            cout << DOUBLE_SPACE << GREEN_COLOR << "Cliente modificado correctamente." << endl;
        }
        else {
            ShowConsoleCurse(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "El cliente con el correo electrónico " << email << " no se encontró en el archivo." << endl;
            _sleep(1500);
        }
    }
    bool numeroExistente(const string& telefono) {
        ifstream file("client_registration.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos = line.find(telefono);
                if (pos != string::npos) {
                    return true; // Si el número ya existe en el archivo
                }
            }
            file.close();
        }
        return false; // Si el número no existe en el archivo
    }

};