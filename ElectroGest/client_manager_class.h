#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include "client_class.h"

using namespace std;

class GESTION_CLIENTE {
public:

    // Método para mostrar la lista de clientes
    void displayCustomerList(string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Leer el archivo de registro de clientes
        ifstream file("client_registration.txt");

        // Si el archivo se abre correctamente
        if (file.is_open()) {
            string line;

            // Leer cada línea del archivo
            while (getline(file, line)) {
                // Crear un flujo de cadena a partir de la línea
                istringstream iss(line);
                // Leer los campos separados por coma
                string nombre, apellido, correo, contrasenia, direccion, telefono, fechaNacimiento, genero;

                // Leer los campos separados por coma
                getline(iss, nombre, ',');
                getline(iss, apellido, ',');
                getline(iss, correo, ',');
                getline(iss, contrasenia, ',');
                getline(iss, direccion, ',');
                getline(iss, telefono, ',');
                getline(iss, fechaNacimiento, ',');
                getline(iss, genero, ',');

                // Mostrar la información del cliente
                cout << BLUE_COLOR << menuTexts[currentLanguage][23] << RESET_COLOR << nombre << " " << apellido << endl; // Nombre completo
                cout << BLUE_COLOR << menuTexts[currentLanguage][25] << RESET_COLOR << correo << endl; // Correo electrónico
                cout << BLUE_COLOR << menuTexts[currentLanguage][28] << RESET_COLOR << direccion << endl; // Dirección
                cout << BLUE_COLOR << menuTexts[currentLanguage][29] << RESET_COLOR << telefono << endl; // Número de teléfono
                cout << BLUE_COLOR << menuTexts[currentLanguage][138] << RESET_COLOR << fechaNacimiento << endl; // Fecha de nacimiento
                cout << BLUE_COLOR << menuTexts[currentLanguage][139] << RESET_COLOR << genero << DOUBLE_SPACE; // Sexo
                cout << YELLOW_COLOR << "-------------------" << DOUBLE_SPACE;
            }
            file.close();
            ShowConsoleCursor(false);
            cout << GRAY_COLOR << menuTexts[currentLanguage][51]; // Presione cualquier tecla para continuar
            _getch();
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][404] << endl; // No se pudo abrir el archivo de registro de clientes
            Sleep(1500);
        }
    }

    // Método para eliminar un nuevo cliente
    void deleteCustomer(string email, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;
        
        // Vector para almacenar las líneas del archivo que no contienen el cliente a eliminar
        vector<string> lines;

        bool found = false; // Variable para rastrear si se encuentra el cliente
        
        // Leer el archivo de registro de clientes
        ifstream file("client_registration.txt");
        if (file.is_open()) {
            string line;

            // Leer cada línea del archivo
            while (getline(file, line)) {
                if (line.find(email) == string::npos) { // Si la línea no contiene el correo electrónico del cliente a eliminar
                    lines.push_back(line); // Conservar la línea
                }
                else {
                    found = true; // Se encontró el cliente
                    cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][140] << endl; // Cliente eliminado con éxito
                }
            }
            file.close();
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][404] << endl; // No se pudo abrir el archivo de registro de clientes
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
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][141] << email << menuTexts[currentLanguage][142] << endl; // No se encontró el cliente con el correo electrónico
            _sleep(1500); // Esperar 1.5 segundos
        }
    }

    // Método para buscar clientes por nombre
    void searchCustomers(const string& searchTerm, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Leer el archivo de registro de clientes
        ifstream file("client_registration.txt");

        // Si el archivo se abre correctamente
        if (file.is_open()) {

            string line;
            bool found = false;

            // Leer cada línea del archivo
            while (getline(file, line)) {
                // Crear un flujo de cadena a partir de la línea
                istringstream iss(line);
                // Leer los campos separados por coma
                string nombre, apellido, correo, direccion, telefono, fechaNacimiento, genero;

                // Leer los campos separados por coma
                getline(iss, nombre, ',');
                getline(iss, apellido, ',');
                getline(iss, correo, ',');
                getline(iss, direccion, ',');
                getline(iss, telefono, ',');
                getline(iss, fechaNacimiento, ',');
                getline(iss, genero, ',');

                if (nombre.find(searchTerm) != string::npos || apellido.find(searchTerm) != string::npos) {
                    cout << CYAN_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][144] << RESET_COLOR << endl; // Cliente encontrado
                    cout << BLUE_COLOR << menuTexts[currentLanguage][143] << RESET_COLOR << nombre << " " << apellido << endl; // Nombre completo
                    cout << BLUE_COLOR << menuTexts[currentLanguage][25] << RESET_COLOR << correo << endl; // Correo electrónico
                    cout << BLUE_COLOR << menuTexts[currentLanguage][28] << RESET_COLOR << direccion << endl; // Dirección
                    cout << BLUE_COLOR << menuTexts[currentLanguage][29] << RESET_COLOR << telefono << endl; // Número de teléfono
                    cout << BLUE_COLOR << menuTexts[currentLanguage][138] << RESET_COLOR << fechaNacimiento << endl; // Fecha de nacimiento
                    cout << BLUE_COLOR << menuTexts[currentLanguage][139] << RESET_COLOR << genero << endl; // Sexo
                    found = true;
                }
            }

            file.close();
            if (!found) {
                ShowConsoleCursor(false);
                cout << MAGENTA_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][145] << endl; // No se encontraron clientes con el nombre o apellido
                _sleep(1500); // Esperar 1.5 segundos
            }
            else {
                ShowConsoleCursor(false);
				cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51]; // Presione cualquier tecla para continuar
				_getch();
			
            }
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][404] << endl; // No se pudo abrir el archivo de registro de clientes
        }
    }

    // Método para buscar clientes por número de teléfono
    bool numeroExistente(const string& telefono) {
        // Leer el archivo de registro de clientes
        ifstream file("client_registration.txt");
        if (file.is_open()) {
            string line;
            // Leer cada línea hasta encontrar el número
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