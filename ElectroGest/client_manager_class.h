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

    // M�todo para mostrar la lista de clientes
    void displayCustomerList(string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Leer el archivo de registro de clientes
        ifstream file("client_registration.txt");

        // Si el archivo se abre correctamente
        if (file.is_open()) {
            string line;

            // Leer cada l�nea del archivo
            while (getline(file, line)) {
                // Crear un flujo de cadena a partir de la l�nea
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

                // Mostrar la informaci�n del cliente
                cout << BLUE_COLOR << menuTexts[currentLanguage][23] << RESET_COLOR << nombre << " " << apellido << endl; // Nombre completo
                cout << BLUE_COLOR << menuTexts[currentLanguage][25] << RESET_COLOR << correo << endl; // Correo electr�nico
                cout << BLUE_COLOR << menuTexts[currentLanguage][28] << RESET_COLOR << direccion << endl; // Direcci�n
                cout << BLUE_COLOR << menuTexts[currentLanguage][29] << RESET_COLOR << telefono << endl; // N�mero de tel�fono
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

    // M�todo para eliminar un nuevo cliente
    void deleteCustomer(string email, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;
        
        // Vector para almacenar las l�neas del archivo que no contienen el cliente a eliminar
        vector<string> lines;

        bool found = false; // Variable para rastrear si se encuentra el cliente
        
        // Leer el archivo de registro de clientes
        ifstream file("client_registration.txt");
        if (file.is_open()) {
            string line;

            // Leer cada l�nea del archivo
            while (getline(file, line)) {
                if (line.find(email) == string::npos) { // Si la l�nea no contiene el correo electr�nico del cliente a eliminar
                    lines.push_back(line); // Conservar la l�nea
                }
                else {
                    found = true; // Se encontr� el cliente
                    cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][140] << endl; // Cliente eliminado con �xito
                }
            }
            file.close();
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][404] << endl; // No se pudo abrir el archivo de registro de clientes
            return;
        }

        // Escribir las l�neas restantes en el archivo
        ofstream outFile("client_registration.txt");
        for (const string& line : lines) {
            outFile << line << endl;
        }
        outFile.close();

        // Si el cliente no se encontr�, imprimir un mensaje
        if (!found) {
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][141] << email << menuTexts[currentLanguage][142] << endl; // No se encontr� el cliente con el correo electr�nico
            _sleep(1500); // Esperar 1.5 segundos
        }
    }

    // M�todo para buscar clientes por nombre
    void searchCustomers(const string& searchTerm, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Leer el archivo de registro de clientes
        ifstream file("client_registration.txt");

        // Si el archivo se abre correctamente
        if (file.is_open()) {

            string line;
            bool found = false;

            // Leer cada l�nea del archivo
            while (getline(file, line)) {
                // Crear un flujo de cadena a partir de la l�nea
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
                    cout << BLUE_COLOR << menuTexts[currentLanguage][25] << RESET_COLOR << correo << endl; // Correo electr�nico
                    cout << BLUE_COLOR << menuTexts[currentLanguage][28] << RESET_COLOR << direccion << endl; // Direcci�n
                    cout << BLUE_COLOR << menuTexts[currentLanguage][29] << RESET_COLOR << telefono << endl; // N�mero de tel�fono
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

    // M�todo para buscar clientes por n�mero de tel�fono
    bool numeroExistente(const string& telefono) {
        // Leer el archivo de registro de clientes
        ifstream file("client_registration.txt");
        if (file.is_open()) {
            string line;
            // Leer cada l�nea hasta encontrar el n�mero
            while (getline(file, line)) {
                size_t pos = line.find(telefono);
                if (pos != string::npos) {
                    return true; // Si el n�mero ya existe en el archivo
                }
            }
            file.close();
        }
        return false; // Si el n�mero no existe en el archivo
    }

};