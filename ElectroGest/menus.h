#pragma once
#include "general_variables.h"
#include "client_class.h"
#include "product_manager_class.h"
#include "product_management_functions.h"
#include "supplier_manager_class.h"
#include "inventory_management_class.h"
#include "client_manager_class.h"
#include "ordering_system_class.h"
#include "shopping_cart_class.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <regex>

using namespace std;

//#####################################################################//
//################## MENÚS DE LA APLICACIÓN ###########################//
//#####################################################################//



// Menú general
void generalMenu(); // Menú general

// Menús de vendedores
void sellerLoginMenu(string currentLanguage); // Menú de inicio de sesión para vendedor
void sellerMenu(string usuario, string currentLanguage); // Menú de vendedor

// Cliente
void clientRegisterMenu(string currentLanguage); // Menú de registro para comprador
void clientLoginMenu(string currentLanguage); // Menú de inicio de sesión para comprador
void clientMenu(string currentLanguage); // Menú de comprador
void homeClientMenu(string currentLanguage); // Menú de inicio para comprador
void savePassword(const string& email, const string& password, string currentLanguage); // Guardar la contraseña cifrada
void saveClientInfo(const CLIENTE& client, string currentLanguage); // Guardar la información del comprador en un archivo   

// Productos
void productCatalogMenu(string currentLanguage); // Menú de catálogo de productos
void productManagementMenu(string currentLanguage); // Menú de gestión de productos 
void filtrarProductosPorCategoria(string currentLanguage); // Filtrar productos por categoría

// Inventario
void inventoryManagementMenu(string currentLanguage); // Menú de gestión de inventario

// Proveedores
void supplierManagementMenu(string currentLanguage); // Menú de gestión de proveedores

// Pedido
void orderingMenu(string currentLanguage); // Menú de pedidos
void orderManagementMenu(string currentLanguage); // Menú de gestión de pedidos

// Gestión de clientes
void customerManagementMenu(string currentLanguage); // Menú de gestión de clientes

void sortProductsPrice(string& currentLanguage); // Ordenar productos por precio

//#####################################################################//
//################## IMPLEMENTACIÓN DE LOS MENÚS #####################//
//#####################################################################//

// Función para mostrar el menú general
void generalMenu() {
    int opcion = 0; // Opción elegida por el usuario

    string currentLanguage = "espanol"; // Idioma predeterminado

    do {
        system("cls");

        cout << CYAN_COLOR;
        cout << "=====================================" << endl;
        cout << menuTexts[currentLanguage][1] << endl; // Sistema de gestión de ventas
        cout << "=====================================" << endl;
        cout << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> " << menuTexts[currentLanguage][2] << endl; // Iniciar sesión como vendedor
        cout << "<2> " << menuTexts[currentLanguage][3] << endl; // Iniciar sesión como cliente
        cout << "<3> " << menuTexts[currentLanguage][8] << endl; // Cambiar idioma
        cout << "<4> " << menuTexts[currentLanguage][4] << endl; // Salir
        ShowConsoleCursor(true); // Mostar cursor 
        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR; // Ingrese una opción
        cin >> opcion;

        // Verifica si la entrada falló
        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }
        else if (opcion > 4)
        {
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Opción no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        // Evaluador del menú de opciones
        switch (opcion) {
        case 1:
            sellerLoginMenu(currentLanguage); // Menú de inicio de sesión para vendedor
            break;
        case 2:
            clientMenu(currentLanguage); // Menú de cliente
            break;
        case 3:
            changeLanguage(currentLanguage); // Cambiar el idioma
            break;
        case 4:
            exit(0); // Salir del programa
            break;
        }
    } while (opcion != 4); // Continuar hasta que el usuario elija salir
}

// Menús de vendedores

// Función para mostrar el menú de vendedor
void sellerLoginMenu(string _currentLanguage) {
    ShowConsoleCursor(true); // Muestra el cursor en la consola

    system("cls"); // Limpia la consola

    // Definir variables
    string usuario, contrasena;
    string usuarioArchivo, contrasenaArchivo;

    // Idioma predeterminado
    string currentLanguage = _currentLanguage; 
  

    // Crear el objeto ProductManager
    GestionarProveedores supplierManager;

    // Solicita al usuario que ingrese sus datos
    cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][9] << " ===" << DOUBLE_SPACE; // Inicio de sesión
    cout << GRAY_COLOR << menuTexts[currentLanguage][10] << DOUBLE_SPACE; // Ingrese sus credenciales
    cout << YELLOW_COLOR << menuTexts[currentLanguage][11] << RESET_COLOR; // Usuario
    cin >> usuario; // Lee el nombre de usuario
    cout << YELLOW_COLOR << menuTexts[currentLanguage][12] << RESET_COLOR; // Contraseña

    // Oculta la contraseña mientras se escribe
    char caracter;
    contrasena = ""; // Inicializa la cadena de la contraseña
    // Bucle para leer la contraseña
    while (true) {
        caracter = _getch(); // Lee un carácter sin mostrarlo
        if (caracter == 13) // 13 es el código ASCII para la tecla Enter
            break; // Si es Enter, termina el bucle
        else if (caracter == 8) { // 8 es el código ASCII para la tecla Backspace
            if (contrasena.length() > 0) {
                cout << "\b \b"; // Retrocede y borra el último carácter
                contrasena.pop_back(); // Elimina el último carácter de la cadena
            }
        }
        else {
            cout << "*"; // Muestra un asterisco en lugar del carácter
            contrasena.push_back(caracter); // Agrega el carácter a la contraseña
        }
    }

    ifstream archivo("seller_data.txt"); // Abre el archivo

    bool encontrado = false;

    // Verifica si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][404] << endl; // Error al abrir el archivo
        return;
    }

    // Lee los datos del archivo línea por línea y compara con los ingresados por el usuario
    while (archivo >> usuarioArchivo >> contrasenaArchivo) {
        // Compara los datos del archivo con los ingresados por el usuario
        if (usuario == usuarioArchivo && contrasena == contrasenaArchivo) {
            encontrado = true;
            break; // Se encontró la coincidencia, no es necesario continuar buscando
        }
    }

    // Cierra el archivo
    archivo.close();

    // Si se encontró el usuario
    if (encontrado) {
        sellerMenu(usuario, currentLanguage); // Muestra el menú de vendedor
    }
    else {
        ShowConsoleCursor(false); // Oculta el cursor
        cout << DOUBLE_SPACE << RED_COLOR << menuTexts[currentLanguage][13] << endl; // Usuario o contraseña incorrectos
        Sleep(1500); // Espera 1.5 segundo
        system("cls"); // Limpia la consola
        ShowConsoleCursor(true); // Muestra el cursor
        sellerLoginMenu(currentLanguage); // Intenta nuevamente
    }
}

// Función para mostrar el menú de vendedor
void sellerMenu(string usuario, string _currentLanguage) {

    // Crear los objetos de las clases

    int opcion; // Opción elegida por el usuario
    string currentLanguage = _currentLanguage; // Idioma predeterminado

    // Bucle para mostrar el menú y obtener la opción del usuario
    do {

        system("cls"); // Limpia la consola

        cout << CYAN_COLOR << "¡" << menuTexts[currentLanguage][14] << usuario << menuTexts[currentLanguage][15] << ":)" << DOUBLE_SPACE << RESET_COLOR; // Bienvenido
        cout << "<1> " << menuTexts[currentLanguage][16] << endl; // Gestión de productos
        cout << "<2> " << menuTexts[currentLanguage][17] << endl; // Gestión de inventario
        cout << "<3> " << menuTexts[currentLanguage][18] << endl; // Gestión de proveedores
        cout << "<4> " << menuTexts[currentLanguage][19] << endl; // Gestión de pedidos
        cout << "<5> " << menuTexts[currentLanguage][20] << endl; // Gestión de clientes
        cout << "<6> " << menuTexts[currentLanguage][4]; // Salir
        ShowConsoleCursor(true); // Muestra el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR; cin >> opcion; // Ingrese una opción

        // Verifica si la entrada falló
        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }
        else if (opcion > 6)
        {
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Opción no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        // Evaluador de opciones
        switch (opcion) {
        case 1:
            productManagementMenu(currentLanguage); // Menú de gestión de productos
            break;
        case 2:
            inventoryManagementMenu(currentLanguage); // Menú de gestión de inventario
            break;
        case 3:
            supplierManagementMenu(currentLanguage); // Menú de gestión de proveedores
            break;
        case 4:
            orderManagementMenu(currentLanguage); // Menú de gestión de pedidos
            break;
        case 5:
            customerManagementMenu(currentLanguage); // Menú de gestión de clientes
            break;
        case 6:
			break;
        }
    } while (opcion != 6); // El bucle continúa hasta que se elige la opción de salir
}

// Menús de clientes 

// Función para mostrar el menú de registro para comprador
void clientRegisterMenu(string _currentLanguage) {
    // Crear un objeto CLIENTE
    CLIENTE comprador;
    GESTION_CLIENTE clienteManager;

    // Definir variables
    string input;
    string currentLanguage = _currentLanguage; // Idioma predeterminado

    system("cls"); // Limpia la consola

    cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][21] << " ===" << DOUBLE_SPACE; // Registro de comprador
    cout << GRAY_COLOR << menuTexts[currentLanguage][22] << DOUBLE_SPACE; // Ingrese sus datos
    cin.ignore(); // Limpia el buffer del teclado

    // Solicitar al usuario que ingrese un nombre
    cout << YELLOW_COLOR << menuTexts[currentLanguage][23] << RESET_COLOR; // Nombre
    string input_nombre;
    getline(cin, input_nombre);

    while (!contieneSoloLetras(input_nombre)) {
        cout << MAGENTA_COLOR << endl << menuTexts[currentLanguage][36];

        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][37] << RESET_COLOR;
        cout << MAGENTA_COLOR << endl << menuTexts[currentLanguage][36]; // Nombre no válido

        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][37] << RESET_COLOR; // Ingrese un nombre válido
        getline(cin, input_nombre);
    }

    // Obtener el primer nombre
    string primer_nombre;
    size_t pos = input_nombre.find(' ');
    if (pos != string::npos) {
        primer_nombre = input_nombre.substr(0, pos);
    }
    else {
        primer_nombre = input_nombre;
    }

    comprador.setNombre(primer_nombre);

    // Solicitar al usuario que ingrese un apellido
    cout << YELLOW_COLOR << menuTexts[currentLanguage][24] << RESET_COLOR; // Apellido
    string input_apellido;
    getline(cin, input_apellido);

    while (!contieneSoloLetrasApellido(input_apellido)) {
        cout << MAGENTA_COLOR << endl << menuTexts[currentLanguage][38];

        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][39] << RESET_COLOR;
        getline(cin, input_apellido);
    }

    // Obtener el primer apellido
    string primer_apellido;
    size_t posA = input_apellido.find(' ');
    if (posA != string::npos) {
        primer_apellido = input_apellido.substr(0, posA);
    }
    else {
        primer_apellido = input_apellido;
    }

    comprador.setApellido(primer_apellido);

    string input_correo;
    regex correoRegex(R"([a-zA-Z0-9._%+-]+@(gmail|yahoo|outlook)\.(com|net|org|edu))");

    do {
        // Solicitar al usuario que ingrese un correo electrónico
        cout << YELLOW_COLOR << menuTexts[currentLanguage][25] << RESET_COLOR; // Correo electrónico
        getline(cin, input_correo);

        // Verificar si la dirección de correo electrónico cumple con la expresión regular
        if (!regex_match(input_correo, correoRegex)) {
            // La dirección de correo electrónico no es válida
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][34] << DOUBLE_SPACE;
        }
    } while (!regex_match(input_correo, correoRegex));
    comprador.setCorreoElectronico(input_correo);

    // Solicitar al usuario que ingrese una contraseña
    cout << YELLOW_COLOR << menuTexts[currentLanguage][12] << RESET_COLOR; // Contraseña
    string input_contrasenia;
    getline(cin, input_contrasenia);
    comprador.setContrasenia(input_contrasenia);

    // Validar que se haya ingresado una contraseña
    while (input_contrasenia.empty()) {
        cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][40] << RESET_COLOR << endl;
        cout << YELLOW_COLOR << menuTexts[currentLanguage][12] << RESET_COLOR; // Contraseña
        getline(cin, input_contrasenia);
        comprador.setContrasenia(input_contrasenia);
    }

    // Solicitar al usuario que confirme la contraseña
    cout << YELLOW_COLOR << menuTexts[currentLanguage][26] << RESET_COLOR; // Confirmar Contraseña
    string input_confirmar_contrasenia;
    getline(cin, input_confirmar_contrasenia);

    // Verificar si las contraseñas coinciden
    while (input_contrasenia != input_confirmar_contrasenia) {
        cout << MAGENTA_COLOR << endl << menuTexts[currentLanguage][41] << RESET_COLOR << DOUBLE_SPACE;

        // Solicitar al usuario que ingrese la contraseña nuevamente
        cout << YELLOW_COLOR << menuTexts[currentLanguage][12] << RESET_COLOR; // Contraseña
        getline(cin, input_contrasenia);
        comprador.setContrasenia(input_contrasenia);

        // Solicitar al usuario que confirme la contraseña nuevamente
        cout << YELLOW_COLOR << menuTexts[currentLanguage][26] << RESET_COLOR; // Confirmar Contraseña
        getline(cin, input_confirmar_contrasenia);
    }

    // Solicitar al usuario que ingrese la dirección
    cout << YELLOW_COLOR << menuTexts[currentLanguage][28] << RESET_COLOR; // Dirección
    string input_direccion;
    getline(cin, input_direccion);
    comprador.setDireccion(input_direccion);

    string input_telefono;
    do {
        // Solicitar al usuario que ingrese el teléfono
        cout << YELLOW_COLOR << menuTexts[currentLanguage][29] << RESET_COLOR; // Teléfono
        getline(cin, input_telefono);
        // Verificar si la entrada es un número de 9 dígitos y no existe en el archivo
        if (input_telefono.length() != 9 || !all_of(input_telefono.begin(), input_telefono.end(), ::isdigit)) {
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][30] << DOUBLE_SPACE; // Número de teléfono no válido
        }
        else if(clienteManager.numeroExistente(input_telefono))
		{
			cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][42] << DOUBLE_SPACE; // Número de teléfono ya registrado
		}
    } while (input_telefono.length() != 9 || !all_of(input_telefono.begin(), input_telefono.end(), ::isdigit) || clienteManager.numeroExistente(input_telefono));
    comprador.setTelefono(input_telefono);

    string input_nacimiento;
    do {
        // Solicitar al usuario que ingrese la fecha de nacimiento
        cout << YELLOW_COLOR << menuTexts[currentLanguage][31] << RESET_COLOR; // Fecha de nacimiento
        getline(cin, input_nacimiento);

        // Definir un stringstream para separar la entrada en día, mes y año
        istringstream iss(input_nacimiento);
        int dia, mes, anio;
        char slash1, slash2;
        iss >> dia >> slash1 >> mes >> slash2 >> anio;

        // Validar el formato de la fecha y los rangos de día, mes y año
        if (iss.fail() || slash1 != '/' || slash2 != '/' || dia < 1 || dia > 31 || mes < 1 || mes > 12 || anio < 1944 || anio > 2006) {
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][35] << DOUBLE_SPACE; // Fecha de nacimiento no válida
        }
        else {
            // La fecha de nacimiento es válida
            // Asignar la fecha de nacimiento al comprador
            string fechaNacimiento = to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
            comprador.setFechaNacimiento(fechaNacimiento);
            break;
        }
    } while (true); // Repetir hasta que se ingrese una fecha de nacimiento válida

    string input_genero;
    do {
        // Solicitar al usuario que ingrese el género
        cout << YELLOW_COLOR << menuTexts[currentLanguage][32] << RESET_COLOR; // Sexo
        getline(cin, input_genero);
        if (input_genero != "M" && input_genero != "F") {
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][33] << DOUBLE_SPACE; // Género no válido
        }
    } while (input_genero != "M" && input_genero != "F");
    comprador.setGenero(input_genero);

    // Guardar la información del comprador en un archivo
    saveClientInfo(comprador, currentLanguage);
    savePassword(input_correo, input_contrasenia, currentLanguage); // Guardar la contraseña cifrada

    ShowConsoleCursor(false); // Oculta el cursor

    Sleep(1500); // Espera 1.5 segundos
    homeClientMenu(currentLanguage); // Muestra el menú del vendedor
}

// Función para mostrar el menú de inicio de sesión para comprador
void clientLoginMenu(string _currentLanguage) {

    ShowConsoleCursor(true); // Muestra el cursor

    string email, password;
    bool loggedIn = false;

    string currentLanguage = _currentLanguage; // Idioma predeterminado

    cout << CYAN_COLOR << menuTexts[currentLanguage][43] << DOUBLE_SPACE;
    cout << GRAY_COLOR << menuTexts[currentLanguage][44] << DOUBLE_SPACE;

    cout << YELLOW_COLOR << menuTexts[currentLanguage][25] << RESET_COLOR;
    cin.ignore();
    getline(cin, email);
    cout << YELLOW_COLOR << menuTexts[currentLanguage][12] << RESET_COLOR;

    // Oculta la contraseña mientras se escribe
    char caracter;
    password = "";
    while (true) {
        caracter = _getch(); // Lee un carácter sin mostrarlo
        if (caracter == 13) // 13 es el código ASCII para la tecla Enter
            break; // Si es Enter, termina el bucle
        else if (caracter == 8) { // 8 es el código ASCII para la tecla Backspace
            if (password.length() > 0) {
                cout << "\b \b"; // Retrocede y borra el último carácter
                password.pop_back(); // Elimina el último carácter de la cadena
            }
        }
        else {
            cout << "*"; // Muestra un asterisco en lugar del carácter
            password.push_back(caracter); // Agrega el carácter a la contraseña
        }
    }

    // Abrir el archivo de registro de compradores
    ifstream file("passwords.txt");
    if (file.is_open()) {
        string line;
        // Leer el archivo línea por línea
        while (getline(file, line)) {
            // Dividir la línea en tokens usando el espacio como delimitador
            istringstream iss(line);
            string emailFromFile, passwordFromFile;
            iss >> emailFromFile >> passwordFromFile;
            // Comparar el correo electrónico y la contraseña ingresados con los almacenados en el archivo
            if (email == emailFromFile && password == passwordFromFile) {
                loggedIn = true;
                ShowConsoleCursor(false);
                cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][45] << DOUBLE_SPACE;
                Sleep(2000);
                system("cls");
                homeClientMenu(currentLanguage); // Mostrar el menú del comprador
                break;
            }
        }
        file.close();
    }
    else {
        cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][46] << DOUBLE_SPACE;
        return;
    }

    if (loggedIn) {
        clientMenu(currentLanguage);
    }
    else {
        ShowConsoleCursor(false);
        cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][47] << DOUBLE_SPACE;
        Sleep(2000);
        system("cls");
        clientLoginMenu(currentLanguage);
    }
}

// Función para mostrar el menú de comprador
void clientMenu(string _currentLanguage) {

    int opcion = 0;

    string currentLanguage = _currentLanguage; // Idioma predeterminado

    do
    {
        system("cls");

        cout << CYAN_COLOR << menuTexts[currentLanguage][43] << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> " << menuTexts[currentLanguage][48] << endl;
        cout << "<2> " << menuTexts[currentLanguage][49] << endl;
        cout << "<3> " << menuTexts[currentLanguage][4];
        cout << DOUBLE_SPACE << YELLOW_COLOR;
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << menuTexts[currentLanguage][5] << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada falló
        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        switch (opcion)
        {
        case 1:
            system("cls");
            clientRegisterMenu(currentLanguage);
            break;
        case 2:
            system("cls");
            clientLoginMenu(currentLanguage);
            break;
        case 3:
			break;
        }
    } while (opcion != 3);

}

// Función para mostrar el menú de inicio para comprador
void homeClientMenu(string _currentLanguage) {
    ShowConsoleCursor(true);   

	system("cls");
    SISTEMA_PEDIDOS sistemaPedidos;

    // Idioma predeterminado
    string currentLanguage = _currentLanguage;

    sistemaPedidos.cargarPedidosPendientes(currentLanguage);
    sistemaPedidos.cargarPedidosProcesados(currentLanguage);

	int opcion = 0;

    do {
        cout << CYAN_COLOR << menuTexts[currentLanguage][43] << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> " << menuTexts[currentLanguage][52] << endl;
        cout << "<2> " << menuTexts[currentLanguage][53] << endl;
        cout << "<3> " << menuTexts[currentLanguage][54] << endl;
        cout << "<4> " << menuTexts[currentLanguage][4];
        cout << DOUBLE_SPACE << YELLOW_COLOR;
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << menuTexts[currentLanguage][5] << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada falló
        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        switch (opcion)
        {
        case 1:
            system("cls");
            productCatalogMenu(currentLanguage);
            break;
        case 2:
            orderingMenu(currentLanguage);
            break;
        case 3:
            system("cls");
            sistemaPedidos.mostrarHistorialPedidos(currentLanguage);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 4:
            break;
        }
    } while (opcion != 4);
}

// Función para guardar la información del comprador en el archivo
void saveClientInfo(const CLIENTE& client, string _currentLanguage) {

    string currentLanguage = _currentLanguage; // Idioma predeterminado

    ofstream file("client_registration.txt", ios::app); // Abre el archivo en modo append
    if (file.is_open()) {
        file << client.getNombre() << ","
            << client.getApellido() << ","
            << client.getCorreoElectronico() << ","
            << client.getContrasenia() << ","
            << client.getDireccion() << ","
            << client.getTelefono() << ","
            << client.getFechaNacimiento() << ","
            << client.getGenero() << "\n";
        file.close();

        cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][67] << endl; // Mostrar un mensaje de confirmación
    }
    else {
        cout << menuTexts[currentLanguage][404] << endl; // Error al abrir el archivo
    }
}

// Función para guardar la contraseña cifrada
void savePassword(const string& email, const string& password, string _currentLanguage) {
    string currentLanguage = _currentLanguage; // Idioma predeterminado
    ofstream passwordFile("passwords.txt", ios::app); // Abre el archivo en modo append
    if (passwordFile.is_open()) {
        passwordFile << email << " " << password << "\n"; // Escribir el correo electrónico y la contraseña en el archivo
        passwordFile.close();
    }
    else {
        cout << menuTexts[currentLanguage][404] << endl; // Error al abrir el archivo
    }
}

// Funciones de gestión de productos    

// Función para mostrar el menú de catálogo de productos
void productCatalogMenu(string _currentLanguage) {

    int opcion;
    string nombre;

    GESTION_PRODUCTOS productManager;

    string currentLanguage = _currentLanguage; // Idioma predeterminado

    do
    {

        system("cls");

        cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][68] << " ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> " << menuTexts[currentLanguage][69] << endl;
        cout << "<2> " << menuTexts[currentLanguage][70] << endl;
        cout << "<3> " << menuTexts[currentLanguage][71] << endl;
        cout << "<4> " << menuTexts[currentLanguage][50];
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada falló
        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        switch (opcion)
        {
        case 1: 
            system("cls");
            productManager.mostrarTodosLosProductos(currentLanguage);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 2:
            filtrarProductosPorCategoria(currentLanguage);
            break;
        case 3:
            system("cls");
            cout << YELLOW_COLOR << menuTexts[currentLanguage][72] << RESET_COLOR;
            cin.ignore();
            getline(cin, nombre);
            cout << endl;
            productManager.buscarProductoPorNombre(nombre, currentLanguage);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");  
			break;
        case 4:
            break;
        }

    } while (opcion != 4);

}

// Función para filtrar productos por categoría
void filtrarProductosPorCategoria(string _currentLanguage) {
    int opcion;

    GESTION_PRODUCTOS productManager;

    string currentLanguage = _currentLanguage; // Idioma predeterminado

    do {

        system("cls");

        cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][83] << " ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> " << menuTexts[currentLanguage][84] << endl;
        cout << "<2> " << menuTexts[currentLanguage][85] << endl;
        cout << "<3> " << menuTexts[currentLanguage][86] << endl;
        cout << "<4> " <<  menuTexts[currentLanguage][50];
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada falló
        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            system("cls");
            productManager.filtrarPorPrecio(productManager, currentLanguage);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            productManager.filtrarPorColor(productManager, currentLanguage);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 3:
            system("cls");
            productManager.filtrarPorMarca(productManager, currentLanguage);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 4:
            break;
        }
    } while (opcion != 4);
}

// Función para mostrar el menú y manejar la interacción con el usuario
void productManagementMenu(string _currentLanguage) {
    GESTION_PRODUCTOS manager; // Crear el gestor de productos con el archivo
    int opcion;
    int opcion_ordenar;
    string currentLanguage = _currentLanguage; // Idioma predeterminado

    // Cargar los productos desde el archivo
    manager.cargarDesdeArchivo(currentLanguage);

    do{

        system("cls"); // Limpiar la pantalla en sistemas Windows

        cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][87] <<" ===" << DOUBLE_SPACE << RESET_COLOR; // Gestión de productos
        cout << "<1> " << menuTexts[currentLanguage][88] << endl;
        cout << "<2> " << menuTexts[currentLanguage][89] << endl;
        cout << "<3> " << menuTexts[currentLanguage][90] << endl;
        cout << "<4> " << menuTexts[currentLanguage][91] << endl;
        cout << "<5> " << menuTexts[currentLanguage][92] << endl;
        cout << "<6> " << menuTexts[currentLanguage][50];
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada falló
        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            system("cls");
            manager.mostrarTodosLosProductos(currentLanguage);

            do
            {

                cout << endl << YELLOW_COLOR << menuTexts[currentLanguage][93] << DOUBLE_SPACE << RESET_COLOR;
                cout << "<1> " << menuTexts[currentLanguage][94] << endl;
                cout << "<2> " << menuTexts[currentLanguage][95];
                ShowConsoleCursor(true); // Muestra el cursor
                cout << YELLOW_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][5] << RESET_COLOR;
                cin >> opcion_ordenar;

                if (opcion_ordenar == 1) {
                    sortProductsPrice(currentLanguage);
                }
				else if (opcion_ordenar == 2) {
					break;
				}
                else {
                    ShowConsoleCursor(false); // Oculta el cursor
                    cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][7] << endl;
                    _sleep(1500);
                }

            } while (opcion_ordenar != 2);
            break;
        case 2:
            system("cls");
            addNewProduct(manager, currentLanguage);
            break;
        case 3:
            system("cls");
            updateProductProcedure(manager, currentLanguage);
            break;
        case 4:
            system("cls");
            removeProductProcedure(manager, currentLanguage);
            break;
        case 5:
            system("cls");
            searchProduct(manager, currentLanguage);
            break;
        case 6:
            break;
        }
    } while (opcion != 6);
}

// Función para mostrar el menú de gestión de inventario
void inventoryManagementMenu(string _currentLanguage) {
    int opcion;
    std::string codigoProducto;
    int cantidad;

    NODO_PRODUCTO* producto = nullptr; // Declara producto fuera del switch
    GESTION_PRODUCTOS gestorProductos;
    GESTION_INVENTARIO gestionInventarios;

    string currentLanguage = _currentLanguage; // Idioma predeterminado

    gestionInventarios.cargarInventarioDesdeArchivo(currentLanguage); // Cargar el inventario desde el archivo al iniciar el programa
    gestionInventarios.cargarMovimientosDesdeArchivo(currentLanguage); // Cargar el historial de movimientos desde el archivo al iniciar el programa

    do {
        system("cls");
        std::cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][112] << " ===" << endl << RESET_COLOR << std::endl;
        std::cout << "<1> " << menuTexts[currentLanguage][113] << std::endl; // Ver inventario
        std::cout << "<2> " << menuTexts[currentLanguage][114] << std::endl; // Añadir stock
        std::cout << "<3> " << menuTexts[currentLanguage][115] << std::endl; // Retirar stock
        std::cout << "<4> " << menuTexts[currentLanguage][116] << std::endl; // Historial de movimientos
        std::cout << "<5> " << menuTexts[currentLanguage][4] << std::endl;
        ShowConsoleCursor(true); // Muestra el cursor
        std::cout << endl << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR;
        std::cin >> opcion;

        // Verifica si la entrada falló
        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            gestionInventarios.verInventario(currentLanguage);
            break;
        case 2:
            system("cls");
            std::cout << YELLOW_COLOR << menuTexts[currentLanguage][125] << RESET_COLOR;
            std::cin >> codigoProducto;
            producto = gestorProductos.buscarProducto(codigoProducto); // Obtiene un puntero al producto
            if (producto != nullptr) {
                int cantidad;
                std::cout << YELLOW_COLOR << menuTexts[currentLanguage][126] << RESET_COLOR;
                while (!(std::cin >> cantidad) || cantidad <= 0) {
                    if (std::cin.fail()) {
                        // Limpiar el estado de error y descartar la entrada inválida
                        std::cin.clear();
                        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                        std::cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][127] << RESET_COLOR << DOUBLE_SPACE;
                    }
                    else {
                        std::cout << MAGENTA_COLOR << menuTexts[currentLanguage][128] << RESET_COLOR << DOUBLE_SPACE;
                    }
                    std::cout << YELLOW_COLOR << menuTexts[currentLanguage][129] << RESET_COLOR;
                }
                gestionInventarios.añadirStock(producto->producto.getCodigo(), cantidad, currentLanguage); // Utiliza el código del producto

                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][130] << RESET_COLOR;
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false); // Oculta el cursor
                std::cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][131] << std::endl; // Producto no encontrado
                Sleep(1500);
            }
            break;
        case 3:
            system("cls");
            std::cout << YELLOW_COLOR << menuTexts[currentLanguage][132] << RESET_COLOR;
            std::cin >> codigoProducto;
            producto = gestorProductos.buscarProducto(codigoProducto); // Asigna valor a producto
            if (producto != nullptr) {
                std::cout << YELLOW_COLOR << menuTexts[currentLanguage][133] << RESET_COLOR;
                while (!(std::cin >> cantidad) || cantidad <= 0) {
                    if (std::cin.fail()) {
                        // Limpiar el estado de error y descartar la entrada inválida
                        std::cin.clear();
                        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                        std::cout << MAGENTA_COLOR << menuTexts[currentLanguage][134] << RESET_COLOR << DOUBLE_SPACE;
                    }
                    else {
                        std::cout << MAGENTA_COLOR << menuTexts[currentLanguage][128] << RESET_COLOR << DOUBLE_SPACE; // Cantidad no válida
                    }
                    std::cout << YELLOW_COLOR << menuTexts[currentLanguage][129] << RESET_COLOR; // Ingrese una cantidad válida
                }

                gestionInventarios.retirarStock(producto->producto.getCodigo(), cantidad, currentLanguage);

                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][136] << RESET_COLOR; // Stock retirado con éxito
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false); // Oculta el cursor
                std::cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][137] << std::endl; // Producto no encontrado
                Sleep(1500);
            }
            break;
        case 4:
            system("cls");
            // Mostrar historial de movimientos
            gestionInventarios.mostrarHistorialMovimientos(currentLanguage);
            ShowConsoleCursor(false); // Oculta el cursor
            std::cout << DOUBLE_SPACE << GRAY_COLOR <<  menuTexts[currentLanguage][50]; // Presione cualquier tecla para continuar
            _getch();
            break;
        case 5:
            break;
        }
    } while (opcion != 5);
}

// Función para mostrar el menú y obtener la opción del usuario
void supplierManagementMenu(string _currentLanguage) {
    int opcion;
    string nombreBuscar;
    const string archivoProveedores = "supplier_data.txt";

    string currentLanguage = _currentLanguage; // Idioma predeterminado

    GestionarProveedores supplierManager; // Crear un objeto de la clase GestionarProveedores

    supplierManager.cargarListaDesdeArchivo(currentLanguage);
    
    do {
        system("cls");
        cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][117] << " ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> " << menuTexts[currentLanguage][118] << endl;
        cout << "<2> " << menuTexts[currentLanguage][119] << endl;
        cout << "<3> " << menuTexts[currentLanguage][120] << endl;
        cout << "<4> " << menuTexts[currentLanguage][121] << endl;
        cout << "<5> " << menuTexts[currentLanguage][122] << endl;
        cout << "<6> " << menuTexts[currentLanguage][50] << DOUBLE_SPACE;
        ShowConsoleCursor(true); // Muestra el cursor
        cout << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR;
        cin >> opcion;

        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6] << endl;
            Sleep(1000);
            ShowConsoleCursor(true);
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            // Verificar si la lista de proveedores está vacía
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
				cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][123] << RESET_COLOR;
				Sleep(1500);
				break;
			}
            system("cls");
            supplierManager.verListaProveedores(currentLanguage);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            supplierManager.agregarProveedor(archivoProveedores, currentLanguage);
            Sleep(1000);
            system("cls");
            break;
        case 3:
            // Verificar si la lista de proveedores está vacía
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][123] << RESET_COLOR;
                Sleep(1500);
                break;
            }
            system("cls");
            supplierManager.actualizarProveedor(archivoProveedores, currentLanguage);
            Sleep(1000);
            system("cls");
            break;
        case 4:
            // Verificar si la lista de proveedores está vacía
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][123] << RESET_COLOR;
                Sleep(1500);
                break;
            }
            system("cls");
            supplierManager.eliminarProveedor(archivoProveedores, currentLanguage);
            Sleep(1000);
            system("cls");
            break;
        case 5:
            // Verificar si la lista de proveedores está vacía
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][123] << RESET_COLOR;
                Sleep(1500);
                break;
            }
            system("cls");
            cout << YELLOW_COLOR << menuTexts[currentLanguage][124] << RESET_COLOR; // Ingrese el nombre del proveedor a buscar
            cin.ignore();
            getline(cin, nombreBuscar);
            supplierManager.buscarProveedor(nombreBuscar, currentLanguage);
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 6:
            break;
        }
    } while (opcion != 6);
}

// Función para realizar un pedido
void orderingMenu(string _currentLanguage) {
    GESTION_INVENTARIO inventario;
    CARRO_COMPRAS carrito; // Crear un objeto de la clase CarritoCompra
    SISTEMA_PEDIDOS sistemaPedidos;

    // Idioma predeterminado
    string currentLanguage = _currentLanguage;

    sistemaPedidos.cargarPedidosPendientes(currentLanguage);
    sistemaPedidos.cargarPedidosProcesados(currentLanguage);

    int opcion;

    bool running = true;

    std::string codigoProducto;
    int cantidad;

    while (running) {
        system("cls");
        std::cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][107] << " ===" << RESET_COLOR << DOUBLE_SPACE;
        std::cout << "<1> " << menuTexts[currentLanguage][108] << endl;
        std::cout << "<2> " << menuTexts[currentLanguage][109] << endl;
        std::cout << "<3> " << menuTexts[currentLanguage][110] << endl;
        std::cout << "<4> " << menuTexts[currentLanguage][111] << endl;
        std::cout << "<5> " << menuTexts[currentLanguage][4];
        ShowConsoleCursor(true); // Muestra el cursor
        std::cout << YELLOW_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][5] << RESET_COLOR;
        std::cin >> opcion;

        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6] << endl;
            Sleep(1000);
            ShowConsoleCursor(true);
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            system("cls");
            std::cout << YELLOW_COLOR << menuTexts[currentLanguage][106] << RESET_COLOR;
            std::cin >> codigoProducto;

            // Verificar que el producto exista
            if (!inventario.existeProducto(codigoProducto)) {
                ShowConsoleCursor(false);
                std::cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][105] << RESET_COLOR; // Producto no encontrado
                Sleep(1500);
                break;
            }

            std::cout << YELLOW_COLOR << menuTexts[currentLanguage][104] << RESET_COLOR;
            int cantidad;
            while (!(std::cin >> cantidad) || cantidad <= 0) {
                if (std::cin.fail()) {
                    // Limpiar el estado de error y descartar la entrada inválida
                    std::cin.clear();
                    cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                    std::cout << MAGENTA_COLOR << menuTexts[currentLanguage][103] << RESET_COLOR << DOUBLE_SPACE;
                }
                else {
                    std::cout << MAGENTA_COLOR << menuTexts[currentLanguage][102] << RESET_COLOR << DOUBLE_SPACE;
                }
                std::cout << YELLOW_COLOR << menuTexts[currentLanguage][101] << RESET_COLOR;
            }

            // Verificar si hay suficiente stock antes de agregar al carrito
            if (inventario.verificarStock(codigoProducto, cantidad)) {
                // Aquí puedes implementar la lógica para agregar al carrito
                carrito.agregarPedido(PEDIDO(codigoProducto, cantidad));
                ShowConsoleCursor(false);
                std::cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][100] << RESET_COLOR; // Producto agregado al carrito
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false);
                std::cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][99] << RESET_COLOR; // No hay suficiente stock
                Sleep(1500);
            }
            break;
        case 2:
            carrito.verCarrito(currentLanguage); // Ver el contenido del carrito
            break;
        case 3:
            if (!carrito.isEmpty()) {
                sistemaPedidos.guardarPedidos(carrito.getPedidos(), currentLanguage);
                carrito.limpiarCarrito(); // Limpiar el carrito después de confirmar el pedido
                ShowConsoleCursor(false);
                std::cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][98];
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false);
                std::cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][96];
                Sleep(1500);
            }
            break;
        case 4:
            if (!carrito.isEmpty()) {
                ShowConsoleCursor(false);
                std::cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][97];
                carrito.limpiarCarrito(); // Limpiar el carrito
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false);
                std::cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][96];
                Sleep(1500);
            }
            break;
        case 5:
            break;
        }
    }
}

// Función para gestionar pedidos
void orderManagementMenu(string _currentLanguage) {
    SISTEMA_PEDIDOS sistemaPedidos;
    // Antes del bucle o en algún lugar antes de utilizarlo en tu código
    GESTION_INVENTARIO inventario;

    // Idioma predeterminado
    string currentLanguage = _currentLanguage;

    sistemaPedidos.cargarPedidosPendientes(currentLanguage);
    sistemaPedidos.cargarPedidosProcesados(currentLanguage);

    int opcion;

    while (true) {
        system("cls");  
        std::cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][77] << " ==" << RESET_COLOR << DOUBLE_SPACE;
        std::cout << "<1> " << menuTexts[currentLanguage][78] << endl;
        std::cout << "<2> " << menuTexts[currentLanguage][79] << endl;
        std::cout << "<3> " << menuTexts[currentLanguage][80] << endl;
        std::cout << "<4> " << menuTexts[currentLanguage][81] << endl;
        std::cout << "<5> " << menuTexts[currentLanguage][82] << endl;
        std::cout << "<6> " << menuTexts[currentLanguage][50];
        ShowConsoleCursor(true); // Muestra el cursor
        std::cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR;
        std::cin >> opcion;

        // Verifica si la entrada falló
        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            std::cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            sistemaPedidos.verPedidosPendientes(currentLanguage);
            break;
        case 2:
            sistemaPedidos.verPedidosProcesados(currentLanguage);
            break;
        case 3:
            system("cls");
            sistemaPedidos.verPedidosPendientes(currentLanguage);
            ShowConsoleCursor(true); // Muestra el cursor
            cout << YELLOW_COLOR << menuTexts[currentLanguage][76] << RESET_COLOR;
            int indicePedido;
            std::cin >> indicePedido;
            if (indicePedido >= 0 && indicePedido < sistemaPedidos.getNumPedidosPendientes()) {
                PEDIDO pedido = sistemaPedidos.getPedidoPendientePorIndice(indicePedido, currentLanguage);
                if (inventario.verificarStock(pedido.getCodigoProducto(), pedido.getCantidad())) {
                    // Procesar el pedido
                    inventario.retirarStock(pedido.getCodigoProducto(), pedido.getCantidad(), currentLanguage);
                    sistemaPedidos.procesarPedido(indicePedido, currentLanguage);
                    ShowConsoleCursor(false); // Oculta el cursor
                    std::cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][75];
                    Sleep(1500);
                }
                else {
                    ShowConsoleCursor(false); // Oculta el cursor
                    std::cout << DOUBLE_SPACE << RED_COLOR << menuTexts[currentLanguage][74];
                    Sleep(1500);
                }
            }
            else {
                ShowConsoleCursor(false); // Oculta el cursor
                std::cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][73]; // Índice no válido
                Sleep(1500);
            }
            break;
        case 4:
            sistemaPedidos.eliminarPedidos(currentLanguage);
            break;
        case 5:
            system("cls");
            sistemaPedidos.mostrarHistorialPedidos(currentLanguage);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            break;
        case 6:
            break;
        }
    }
}

// Función para mostrar el menú de gestión de clientes
void customerManagementMenu(string _currentLanguage) {
    GESTION_CLIENTE gestionCliente;
    
    string currentLanguage = "espanol"; // Idioma predeterminado
    int opcion;

    do {
        system("cls");

        cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][62] << " ===" << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> " << menuTexts[currentLanguage][63] << endl;
        cout << "<2> " << menuTexts[currentLanguage][64] << endl;
        cout << "<3> " << menuTexts[currentLanguage][65] << endl;
        cout << "<4> " << menuTexts[currentLanguage][50];
        ShowConsoleCursor(true); // Muestra el cursor
        cout << YELLOW_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][5] << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada falló
        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no válida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        ifstream file("client_registration.txt");

        switch (opcion) {
        case 1:
            if (file.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo está vacío
                ShowConsoleCursor(false); // Oculta el cursor
                cout << MAGENTA_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][59] << endl;
                _sleep(1500); // Espera 1.5 segundos
                file.close();
                break;
            }
            system("cls");
            cout << CYAN_COLOR << menuTexts[currentLanguage][66] << DOUBLE_SPACE;
            gestionCliente.displayCustomerList(currentLanguage);
            break;
        case 2:
            if (file.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo está vacío
                ShowConsoleCursor(false); // Oculta el cursor
                cout << MAGENTA_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][59] << endl;
                _sleep(1500); // Espera 1.5 segundos
                file.close();
                break;
            }
            system("cls");
            cout << CYAN_COLOR << menuTexts[currentLanguage][61] << DOUBLE_SPACE << RESET_COLOR;
            {
                string email;
                cout << YELLOW_COLOR << menuTexts[currentLanguage][60] << RESET_COLOR;
                cin >> email;
                gestionCliente.deleteCustomer(email, currentLanguage);
                ShowConsoleCursor(false); // Oculta el cursor
                _sleep(1500); // Espera 1.5 segundo
            }
            break;
        case 3:
            if (file.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo está vacío
                ShowConsoleCursor(false); // Oculta el cursor
                cout << MAGENTA_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][59] << endl;
                _sleep(1500); // Espera 1.5 segundos
                file.close();
                break;
            }
            system("cls");
            cout << CYAN_COLOR << menuTexts[currentLanguage][58] << DOUBLE_SPACE << RESET_COLOR;
            {
                string searchTerm;
                cout << YELLOW_COLOR << menuTexts[currentLanguage][57] << RESET_COLOR;
                cin >> searchTerm;
                gestionCliente.searchCustomers(searchTerm, currentLanguage);
            }
            break;
        case 4:
            break;
        }
    } while (opcion != 4);
}

void sortProductsPrice(string& currentLanguage) {
    
    GESTION_PRODUCTOS productManager;

    int opcion;

	do {
		system("cls");
		cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][292] << " ===" << RESET_COLOR << DOUBLE_SPACE;
		cout << "<1> " << menuTexts[currentLanguage][55] << endl; // Ordenar por precio ascendente
		cout << "<2> " << menuTexts[currentLanguage][56] << endl; // Ordenar por precio descendente 
		cout << "<3> " << menuTexts[currentLanguage][50];
        ShowConsoleCursor(true); // Muestra el cursor
		cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR;
		cin >> opcion;

		// Verifica si la entrada falló
		if (cin.fail()) { // Verifica si la entrada falló
			cin.clear(); // Limpia el estado de cin
			cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
			ShowConsoleCursor(false); // Oculta el cursor
			cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no válida
			Sleep(1500); // Espera 1.5 segundos
			continue; // Continúa al siguiente ciclo del bucle do-while
		}

		switch (opcion) {
		case 1:
			system("cls");
			productManager.ordenarProductosPorPrecioAscendente(currentLanguage);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            productManager.ordenarProductosPorPrecioDescendente(currentLanguage);
            ShowConsoleCursor(false); // Oculta el cursor
			cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
			_getch();
			system("cls");
			break;
		case 3:
            productManagementMenu(currentLanguage);
			break;
		}
	} while (opcion != 3);

}