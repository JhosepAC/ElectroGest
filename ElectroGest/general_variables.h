#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <map>
#include <limits>
#include <cctype>

using namespace std;

// Definici�n de constantes para c�digos de color ANSI
const string RESET_COLOR = "\033[0m";
const string RED_COLOR = "\033[31m";
const string GREEN_COLOR = "\033[32m";
const string YELLOW_COLOR = "\033[33m";
const string BLUE_COLOR = "\033[34m";
const string MAGENTA_COLOR = "\033[35m";
const string GRAY_COLOR = "\033[90m";
const string CYAN_COLOR = "\033[36m";
const string WHITE_COLOR = "\033[37m";

// Variables extras
const string DOUBLE_SPACE = "\n\n";

void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // Establece la visibilidad del cursor

    SetConsoleCursorInfo(out, &cursorInfo);
}

// Definici�n de textos en diferentes idiomas
map<string, map<int, string>> menuTexts = {
    {"espanol", {
        {1, "     �Bienvenido a ElectroGest!"},
        {2, "Iniciar sesi�n como vendedor"},
        {3, "Iniciar sesi�n como cliente"},
        {4, "Salir"},
        {5, "Ingrese una opci�n: "},
        {6, "Entrada no v�lida, por favor ingrese un n�mero."},
        {7, "Opci�n no v�lida, por favor intente nuevamente."},
        {8, "Cambiar idioma"},
        {9, "�Bienvenido, vendedor!"},
        {10, "Ingrese sus datos para iniciar sesi�n"},
        {11, "Usuario: "},
        {12, "Contrase�a: "},
        {13, "Usuario o contrase�a incorrectos. Por favor, int�ntelo de nuevo."},
        {14, "Bienvenido, "},
        {15, "!"},
        {16, "Gestionar productos"},
        {17, "Gestionar inventario"},
        {18, "Gestionar proveedores"},
        {19, "Gestionar pedidos"},
        {20, "Gestionar clientes"},
        {21, "�Bienvenido comprador!"},
        {22, "Por favor, complete el siguiente formulario para registrarse"},
        {23, "Nombre: "},
        {24, "Apellido: "},
        {25, "Correo electr�nico: "},
        {26, "Confirmar contrase�a: "},
        {27, "Las contrase�as no coinciden, intente de nuevo."},
        {28, "Direcci�n: "},
        {29, "Tel�fono: "},
        {30, "El tel�fono debe tener exactamente 9 d�gitos. Intente de nuevo."},
        {31, "Fecha de nacimiento: (DD/MM/AAAA): "},
        {32, "Sexo (M, F): "},
        {33, "Ingrese un sexo v�lido (M, F). Intente de nuevo."},
        {34, "Direcci�n de correo electr�nico no v�lida"},
        {35, "Fecha de nacimiento no v�lida"},
        {36, "Nombre no permitido."},
        {37, "Ingrese un nombre v�lido: "},
		{38, "Apellido no permitido."},
		{39, "Ingrese un apellido v�lido: "},
        {36, "Nombre no v�lido."},
        {37, "Ingrese un nombre v�lido: "},
        {38, "Apellido no v�lido."},
        {39, "Ingrese un apellido v�lido: "},
        {40, "Debe ingresar una contrase�a. Por favor, int�ntelo de nuevo."},
        {41, "Las contrase�as no coinciden. Por favor, int�ntelo de nuevo."},
        {42, "N�mero de tel�fono ya registrado."},
        {404, "Error al abrir el archivo" }
    }},
    {"english", {
        {1, "       Welcome to ElectroGest!"},
        {2, "Log in as a seller"},
        {3, "Log in as a client"},
        {4, "Exit"},
        {5, "Enter an option: "},
        {6, "Invalid input, please enter a number."},
        {7, "Invalid option, please try again."},
        {8, "Change language"},
        {9, "Welcome, seller!"},
		{10, "Enter your data to log in"},
		{11, "Username: "},
		{12, "Password: "},
		{13, "Incorrect username or password. Please try again."},
		{14, "Welcome, "},
		{15, " "},
        {16, "Manage products"},
		{17, "Manage inventory"},
		{18, "Manage suppliers"},
		{19, "Manage orders"},
		{20, "Manage clients"},
		{21, "Welcome buyer!"},
		{22, "Please fill out the following form to register"},
		{23, "Name: "},
		{24, "Last name: "},
		{25, "Email: "},
		{26, "Confirm password: "},
		{27, "Passwords do not match, try again."},
        {28, "Address: "},
		{29, "Phone: "},
		{30, "Phone must have exactly 9 digits. Try again."},
		{31, "Date of birth: (DD/MM/YYYY): "},
        {32, "Sex (M, F): "},
        {33, "Please enter a valid gender (M, F). Try again."},
        {34, "Invalid email address"},
		{35, "Invalid date of birth"},
        {36, "Invalid name."},
		{37, "Enter a valid name: "},
		{38, "Invalid last name."},
		{39, "Enter a valid last name: "},
		{40, "You must enter a password. Please try again."},
		{41, "Passwords do not match. Please try again."},
		{42, "Phone number already registered."},
		{404, "Error opening file" }
    }}
};

// Funci�n para cambiar el idioma del men�
void changeLanguage(string& currentLanguage) {
    string language;
    cout << DOUBLE_SPACE << YELLOW_COLOR << "Select language (espanol/english): " << RESET_COLOR;
    cin >> language;
    // Verificar si el idioma seleccionado est� disponible
    if (menuTexts.find(language) == menuTexts.end()) {
        cout << DOUBLE_SPACE << MAGENTA_COLOR << "Invalid language choice.";
        Sleep(1500);
    }
    else {
        // Cambiar el idioma
        currentLanguage = language;
    }
}

// Funci�n para verificar si una cadena contiene solo letras
bool contieneSoloLetras(const string& str) {
    for (char c : str) {
        if (!(isalpha(c) || c == '6' || c == ' ')) { // Permitir letras, espacio y el n�mero 6
            return false;
        }
    }
    return true;
}

// Funci�n para verificar si una cadena contiene solo letras
bool contieneSoloLetrasApellido(const string& str) {
    for (char c : str) {
        if (!(isalpha(c) || c == ' ')) { // Permitir letras y espacio
            return false;
        }
    }
    return true;
}