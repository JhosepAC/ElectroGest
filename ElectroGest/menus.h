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
void sellerLoginMenu(string _currentLanguage); // Menú de inicio de sesión para vendedor
void sellerMenu(string usuario, string _currentLanguag); // Menú de vendedor

// Cliente
void clientRegisterMenu(string _currentLanguag); // Menú de registro para comprador
void clientLoginMenu(string _currentLanguag); // Menú de inicio de sesión para comprador
void clientMenu(string _currentLanguag); // Menú de comprador
void homeClientMenu(string _currentLanguag); // Menú de inicio para comprador
void savePassword(const string& email, const string& password, string _currentLanguag); // Guardar la contraseña cifrada
void saveClientInfo(const CLIENTE& client, string _currentLanguag); // Guardar la información del comprador en un archivo   

// Productos
void productCatalogMenu(string _currentLanguag); // Menú de catálogo de productos
void productManagementMenu(string _currentLanguag); // Menú de gestión de productos 
void filtrarProductosPorCategoria(string _currentLanguag); // Filtrar productos por categoría

// Inventario
void inventoryManagementMenu(string _currentLanguag); // Menú de gestión de inventario

// Proveedores
void supplierManagementMenu(string _currentLanguag); // Menú de gestión de proveedores

// Pedido
void orderingMenu(string _currentLanguag); // Menú de pedidos
void orderManagementMenu(string _currentLanguag); // Menú de gestión de pedidos

// Gestión de clientes
void customerManagementMenu(string _currentLanguag); // Menú de gestión de clientes

void sortProductsPrice(string _currentLanguag); // Ordenar productos por precio

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

<<<<<<< HEAD
    // Idioma predeterminado
    string currentLanguage = _currentLanguage; 
=======
    string currentLanguage = "espanol"; // Idioma predeterminado
>>>>>>> ad28a2a3f66afbc68c01c9099beaba4259d80164

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
            productManagementMenu(_currentLanguage); // Menú de gestión de productos
            break;
        case 2:
            inventoryManagementMenu(_currentLanguage); // Menú de gestión de inventario
            break;
        case 3:
            supplierManagementMenu(_currentLanguage); // Menú de gestión de proveedores
            break;
        case 4:
            orderManagementMenu(_currentLanguage); // Menú de gestión de pedidos
            break;
        case 5:
            customerManagementMenu(_currentLanguage); // Menú de gestión de clientes
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
<<<<<<< HEAD
        cout << MAGENTA_COLOR << endl << menuTexts[currentLanguage][36];

        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][37] << RESET_COLOR;
=======
        cout << MAGENTA_COLOR << endl << menuTexts[currentLanguage][36]; // Nombre no válido

        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][37] << RESET_COLOR; // Ingrese un nombre válido
>>>>>>> ad28a2a3f66afbc68c01c9099beaba4259d80164
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
    saveClientInfo(comprador, _currentLanguage);
    savePassword(input_correo, input_contrasenia, _currentLanguage); // Guardar la contraseña cifrada

    ShowConsoleCursor(false); // Oculta el cursor

    Sleep(1500); // Espera 1.5 segundos
    homeClientMenu(_currentLanguage); // Muestra el menú del vendedor
}

// Función para mostrar el menú de inicio de sesión para comprador
void clientLoginMenu(string _currentLanguage) {

    ShowConsoleCursor(true); // Muestra el cursor

    string email, password;
    bool loggedIn = false;

    string currentLanguage = _currentLanguage; // Idioma predeterminado

    cout << CYAN_COLOR << "¡Bienvenido, comprador!" << DOUBLE_SPACE;
    cout << GRAY_COLOR << "Ingrese sus datos para iniciar sesión." << DOUBLE_SPACE;

    cout << YELLOW_COLOR << "Correo electrónico: " << RESET_COLOR;
    cin.ignore();
    getline(cin, email);
    cout << YELLOW_COLOR << "Contraseña: " << RESET_COLOR;

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
                cout << DOUBLE_SPACE << GREEN_COLOR << "Inicio de sesión exitoso." << DOUBLE_SPACE;
                Sleep(2000);
                system("cls");
                homeClientMenu(_currentLanguage); // Mostrar el menú del comprador
                break;
            }
        }
        file.close();
    }
    else {
        cout << DOUBLE_SPACE << MAGENTA_COLOR << "Error: No se pudo abrir el archivo de registro." << DOUBLE_SPACE;
        return;
    }

    if (loggedIn) {
        clientMenu(_currentLanguage);
    }
    else {
        ShowConsoleCursor(false);
        cout << DOUBLE_SPACE << MAGENTA_COLOR << "Correo electrónico o contraseña incorrectos. Por favor, inténtelo de nuevo." << DOUBLE_SPACE;
        Sleep(2000);
        system("cls");
        clientLoginMenu(_currentLanguage);
    }
}

// Función para mostrar el menú de comprador
void clientMenu(string _currentLanguage) {

    int opcion = 0;

    string currentLanguage = _currentLanguage; // Idioma predeterminado

    do
    {
        system("cls");

        cout << CYAN_COLOR << "¡Bienvenido, comprador!" << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> Registrarte" << endl;
        cout << "<2> Iniciar sesión" << endl;
        cout << "<3> Salir";
        cout << DOUBLE_SPACE << YELLOW_COLOR;
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << "Ingrese una opción: " << RESET_COLOR;
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
            clientRegisterMenu(_currentLanguage);
            break;
        case 2:
            system("cls");
            clientLoginMenu(_currentLanguage);
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

    sistemaPedidos.cargarPedidosPendientes();
    sistemaPedidos.cargarPedidosProcesados();

	int opcion = 0;
    string currentLanguage = "espanol"; // Idioma predeterminado

    do {
        cout << CYAN_COLOR << "¡Bienvenido, comprador!" << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> Ver cátalogo de productos" << endl;
        cout << "<2> Realizar pedido" << endl;
        cout << "<3> Ver estado de pedidos" << endl;
        cout << "<4> Salir";
        cout << DOUBLE_SPACE << YELLOW_COLOR;
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << "Ingrese una opción: " << RESET_COLOR;
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
            productCatalogMenu(_currentLanguage);
            break;
        case 2:
            orderingMenu(_currentLanguage);
            break;
        case 3:
            system("cls");
            sistemaPedidos.mostrarHistorialPedidos();
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
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

        cout << DOUBLE_SPACE << GREEN_COLOR << "¡Registro completado exitosamente!" << endl; // Mostrar un mensaje de confirmación
    }
    else {
        cout << "No se pudo abrir el archivo para guardar la información." << endl;
    }
}

// Función para guardar la contraseña cifrada
void savePassword(const string& email, const string& password, string _currentLanguage) {
    ofstream passwordFile("passwords.txt", ios::app); // Abre el archivo en modo append
    if (passwordFile.is_open()) {
        passwordFile << email << " " << password << "\n"; // Escribir el correo electrónico y la contraseña en el archivo
        passwordFile.close();
    }
    else {
        cout << "No se pudo abrir el archivo para guardar la contraseña." << endl;
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

        cout << CYAN_COLOR << "=== Cátalogo de productos ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> Ver productos" << endl;
        cout << "<2> Filtrar productos" << endl;
        cout << "<3> Buscar productos por nombre" << endl;
        cout << "<4> Volver";
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese una opción: " << RESET_COLOR;
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
            productManager.mostrarTodosLosProductos();
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
            _getch();
            system("cls");
            break;
        case 2:
            filtrarProductosPorCategoria(_currentLanguage);
            break;
        case 3:
            system("cls");
            cout << YELLOW_COLOR << "Ingresa el nombre del producto a buscar: " << RESET_COLOR;
            cin.ignore();
            getline(cin, nombre);
            cout << endl;
            productManager.buscarProductoPorNombre(nombre);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
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

        cout << CYAN_COLOR << "=== Filtrar productos por categoría ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> Filtrar por precio" << endl;
        cout << "<2> Filtrar por color" << endl;
        cout << "<3> Filtrar por marca" << endl;
        cout << "<4> Volver";
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese una opción: " << RESET_COLOR;
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
            productManager.filtrarPorPrecio(productManager);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
            _getch();
            system("cls");  
            break;
        case 2:
            system("cls");
            productManager.filtrarPorColor(productManager);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
            _getch();
            system("cls");
            break;
        case 3:
            system("cls");
            productManager.filtrarPorMarca(productManager);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
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

    do{

        system("cls"); // Limpiar la pantalla en sistemas Windows

        cout << CYAN_COLOR << "=== Gestión de productos ===" << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> Catálogo de productos" << endl;
        cout << "<2> Agregar nuevo producto" << endl;
        cout << "<3> Actualizar producto" << endl;
        cout << "<4> Eliminar producto" << endl;
        cout << "<5> Buscar producto" << endl;
        cout << "<6> Salir";
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese una opción: " << RESET_COLOR;
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
            manager.mostrarTodosLosProductos();

            do
            {

                cout << endl << YELLOW_COLOR << "¿Desea ordenar los productos por precio?" << DOUBLE_SPACE << RESET_COLOR;
                cout << "<1> Sí" << endl;
                cout << "<2> No";
                ShowConsoleCursor(true); // Muestra el cursor
                cout << YELLOW_COLOR << DOUBLE_SPACE << "Ingrese una opción: " << RESET_COLOR;
                cin >> opcion_ordenar;

                if (opcion_ordenar == 1) {
                    sortProductsPrice(_currentLanguage);
                }
				else if (opcion_ordenar == 2) {
					break;
				}
                else {
                    ShowConsoleCursor(false); // Oculta el cursor
                    cout << endl << MAGENTA_COLOR << "Opción no válida. Por favor, intente de nuevo." << endl;
                    _sleep(1500);
                }

            } while (opcion_ordenar != 2);
            break;
        case 2:
            system("cls");
            addNewProduct(manager);
            break;
        case 3:
            system("cls");
            updateProductProcedure(manager);
            break;
        case 4:
            system("cls");
            removeProductProcedure(manager);
            break;
        case 5:
            system("cls");
            searchProduct(manager);
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

    do {
        system("cls");
        std::cout << CYAN_COLOR << "=== Menú de Gestión de Inventarios ===" << endl << RESET_COLOR << std::endl;
        std::cout << "<1> Ver Inventario" << std::endl;
        std::cout << "<2> Añadir Stock" << std::endl;
        std::cout << "<3> Retirar Stock" << std::endl;
        std::cout << "<4> Historial de Movimientos" << std::endl;
        std::cout << "<5> Salir" << std::endl;
        ShowConsoleCursor(true); // Muestra el cursor
        std::cout << endl << YELLOW_COLOR << "Ingrese la opción deseada: " << RESET_COLOR;
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
            gestionInventarios.verInventario();
            break;
        case 2:
            system("cls");
            std::cout << YELLOW_COLOR << "Ingrese el código del producto que desea agregar al inventario: " << RESET_COLOR;
            std::cin >> codigoProducto;
            producto = gestorProductos.buscarProducto(codigoProducto); // Obtiene un puntero al producto
            if (producto != nullptr) {
                int cantidad;
                std::cout << YELLOW_COLOR << "Ingrese la cantidad de stock a añadir: " << RESET_COLOR;
                while (!(std::cin >> cantidad) || cantidad <= 0) {
                    if (std::cin.fail()) {
                        // Limpiar el estado de error y descartar la entrada inválida
                        std::cin.clear();
                        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                        std::cout << endl << MAGENTA_COLOR << "Debe ingresar un número válido para la cantidad de stock." << RESET_COLOR << DOUBLE_SPACE;
                    }
                    else {
                        std::cout << MAGENTA_COLOR << "La cantidad de stock debe ser un número positivo." << RESET_COLOR << DOUBLE_SPACE;
                    }
                    std::cout << YELLOW_COLOR << "Ingrese nuevamente la cantidad de stock: " << RESET_COLOR;
                }
                gestionInventarios.añadirStock(producto->producto.getCodigo(), cantidad); // Utiliza el código del producto

                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << GREEN_COLOR << "Stock añadido exitosamente." << RESET_COLOR;
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false); // Oculta el cursor
                std::cout << endl << MAGENTA_COLOR << "El producto no se encuentra en la lista de productos." << std::endl;
                Sleep(1500);
            }
            break;
        case 3:
            system("cls");
            std::cout << YELLOW_COLOR << "Ingrese el código del producto del cual desea retirar stock: " << RESET_COLOR;
            std::cin >> codigoProducto;
            producto = gestorProductos.buscarProducto(codigoProducto); // Asigna valor a producto
            if (producto != nullptr) {
                std::cout << YELLOW_COLOR << "Ingrese la cantidad de stock a retirar: " << RESET_COLOR;
                while (!(std::cin >> cantidad) || cantidad <= 0) {
                    if (std::cin.fail()) {
                        // Limpiar el estado de error y descartar la entrada inválida
                        std::cin.clear();
                        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                        std::cout << MAGENTA_COLOR << "Debe ingresar un número válido para la cantidad de stock." << RESET_COLOR << DOUBLE_SPACE;
                    }
                    else {
                        std::cout << MAGENTA_COLOR << "La cantidad de stock debe ser un número positivo." << RESET_COLOR << DOUBLE_SPACE;
                    }
                    std::cout << YELLOW_COLOR << "Ingrese nuevamente la cantidad de stock: " << RESET_COLOR;
                }

                gestionInventarios.retirarStock(producto->producto.getCodigo(), cantidad);

                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << GREEN_COLOR << "Stock retirado exitosamente." << RESET_COLOR;
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false); // Oculta el cursor
                std::cout << DOUBLE_SPACE << MAGENTA_COLOR << "El producto no se encuentra en la lista de productos." << std::endl;
                Sleep(1500);
            }
            break;
        case 4:
            system("cls");
            // Mostrar historial de movimientos
            gestionInventarios.mostrarHistorialMovimientos();
            ShowConsoleCursor(false); // Oculta el cursor
            std::cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
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

    supplierManager.cargarListaDesdeArchivo();
    
    do {
        system("cls");
        cout << CYAN_COLOR << "=== GESTIÓN DE PROVEEDORES ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> Ver lista de proveedores" << endl;
        cout << "<2> Agregar nuevo proveedor" << endl;
        cout << "<3> Actualizar información de proveedor" << endl;
        cout << "<4> Eliminar proveedor" << endl;
        cout << "<5> Buscar proveedor" << endl;
        cout << "<6> Volver" << DOUBLE_SPACE;
        ShowConsoleCursor(true); // Muestra el cursor
        cout << YELLOW_COLOR << "Seleccione una opcion: " << RESET_COLOR;
        cin >> opcion;

        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no válida, por favor ingrese un número." << endl;
            Sleep(1000);
            ShowConsoleCursor(true);
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            // Verificar si la lista de proveedores está vacía
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
				cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se cuenta con proveedores por el momento." << RESET_COLOR;
				Sleep(1500);
				break;
			}
            system("cls");
            supplierManager.verListaProveedores();
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para salir";
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            supplierManager.agregarProveedor(archivoProveedores);
            Sleep(1000);
            system("cls");
            break;
        case 3:
            // Verificar si la lista de proveedores está vacía
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se cuenta con proveedores por el momento." << RESET_COLOR;
                Sleep(1500);
                break;
            }
            system("cls");
            supplierManager.actualizarProveedor(archivoProveedores);
            Sleep(1000);
            system("cls");
            break;
        case 4:
            // Verificar si la lista de proveedores está vacía
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se cuenta con proveedores por el momento." << RESET_COLOR;
                Sleep(1500);
                break;
            }
            system("cls");
            supplierManager.eliminarProveedor(archivoProveedores);
            Sleep(1000);
            system("cls");
            break;
        case 5:
            // Verificar si la lista de proveedores está vacía
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se cuenta con proveedores por el momento." << RESET_COLOR;
                Sleep(1500);
                break;
            }
            system("cls");
            cout << YELLOW_COLOR << "Ingrese el nombre del proveedor que desea buscar: " << RESET_COLOR;
            cin.ignore();
            getline(cin, nombreBuscar);
            supplierManager.buscarProveedor(nombreBuscar);
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presionar cualquier tecla para continuar";
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

    sistemaPedidos.cargarPedidosPendientes();
    sistemaPedidos.cargarPedidosProcesados();

    int opcion;

    bool running = true;

    std::string codigoProducto;
    string currentLanguage = _currentLanguage; // Idioma predeterminado
    int cantidad;

    while (running) {
        system("cls");
        std::cout << CYAN_COLOR << "=== REALIZAR PEDIDO ===" << RESET_COLOR << DOUBLE_SPACE;
        std::cout << "<1> Agregar Producto al Carrito\n";
        std::cout << "<2> Ver Carrito\n";
        std::cout << "<3> Confirmar Pedido\n";
        std::cout << "<4> Cancelar Pedido\n";
        std::cout << "<5> Salir";
        ShowConsoleCursor(true); // Muestra el cursor
        std::cout << YELLOW_COLOR << DOUBLE_SPACE << "Seleccione una opción: " << RESET_COLOR;
        std::cin >> opcion;

        if (cin.fail()) { // Verifica si la entrada falló
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no válida, por favor ingrese un número." << endl;
            Sleep(1000);
            ShowConsoleCursor(true);
            continue; // Continúa al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            system("cls");
            std::cout << YELLOW_COLOR << "Ingrese el código del producto a agregar: " << RESET_COLOR;
            std::cin >> codigoProducto;

            // Verificar que el producto exista
            if (!inventario.existeProducto(codigoProducto)) {
                ShowConsoleCursor(false);
                std::cout << DOUBLE_SPACE << MAGENTA_COLOR << "El producto no existe en el inventario." << RESET_COLOR;
                Sleep(1500);
                break;
            }

            std::cout << YELLOW_COLOR << "Ingrese la cantidad a agregar: " << RESET_COLOR;
            int cantidad;
            while (!(std::cin >> cantidad) || cantidad <= 0) {
                if (std::cin.fail()) {
                    // Limpiar el estado de error y descartar la entrada inválida
                    std::cin.clear();
                    cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                    std::cout << MAGENTA_COLOR << "Debe ingresar un número válido para la cantidad." << RESET_COLOR << DOUBLE_SPACE;
                }
                else {
                    std::cout << MAGENTA_COLOR << "La cantidad debe ser un número positivo." << RESET_COLOR << DOUBLE_SPACE;
                }
                std::cout << YELLOW_COLOR << "Ingrese nuevamente la cantidad a agregar: " << RESET_COLOR;
            }

            // Verificar si hay suficiente stock antes de agregar al carrito
            if (inventario.verificarStock(codigoProducto, cantidad)) {
                // Aquí puedes implementar la lógica para agregar al carrito
                carrito.agregarPedido(PEDIDO(codigoProducto, cantidad));
                ShowConsoleCursor(false);
                std::cout << DOUBLE_SPACE << GREEN_COLOR << "Producto agregado al carrito correctamente." << RESET_COLOR;
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false);
                std::cout << DOUBLE_SPACE << MAGENTA_COLOR << "No hay suficiente stock de este producto." << RESET_COLOR;
                Sleep(1500);
            }
            break;
        case 2:
            carrito.verCarrito(); // Ver el contenido del carrito
            break;
        case 3:
            if (!carrito.isEmpty()) {
                sistemaPedidos.guardarPedidos(carrito.getPedidos());
                carrito.limpiarCarrito(); // Limpiar el carrito después de confirmar el pedido
                ShowConsoleCursor(false);
                std::cout << DOUBLE_SPACE << GREEN_COLOR << "Pedido confirmado correctamente.";
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false);
                std::cout << endl << MAGENTA_COLOR << "El carrito está vacío. No se puede confirmar el pedido.";
                Sleep(1500);
            }
            break;
        case 4:
            if (!carrito.isEmpty()) {
                ShowConsoleCursor(false);
                std::cout << DOUBLE_SPACE << GREEN_COLOR << "Pedido cancelado. El carrito ha sido vaciado.";
                carrito.limpiarCarrito(); // Limpiar el carrito
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false);
                std::cout << endl << MAGENTA_COLOR << "El carrito está vacío. No se puede cancelar el pedido.";
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

    sistemaPedidos.cargarPedidosPendientes();
    sistemaPedidos.cargarPedidosProcesados();

    int opcion;
    string currentLanguage = _currentLanguage; // Idioma predeterminado

    while (true) {
        system("cls");  
        std::cout << CYAN_COLOR << "=== GESTIÓN DE PEDIDOS ==" << RESET_COLOR << DOUBLE_SPACE;
        std::cout << "<1> Ver Pedidos Pendientes" << endl;
        std::cout << "<2> Ver Pedidos Procesados" << endl;
        std::cout << "<3> Procesar Pedido" << endl;
        std::cout << "<4> Eliminar Pedidos" << endl;
        std::cout << "<5> Historial de Pedidos" << endl;
        std::cout << "<6> Volver";
        ShowConsoleCursor(true); // Muestra el cursor
        std::cout << DOUBLE_SPACE << YELLOW_COLOR << "Seleccione una opción: " << RESET_COLOR;
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
            sistemaPedidos.verPedidosPendientes();
            break;
        case 2:
            sistemaPedidos.verPedidosProcesados();
            break;
        case 3:
            system("cls");
            sistemaPedidos.verPedidosPendientes();
            ShowConsoleCursor(true); // Muestra el cursor
            cout << YELLOW_COLOR << "Ingrese el índice del pedido a procesar: " << RESET_COLOR;
            int indicePedido;
            std::cin >> indicePedido;
            if (indicePedido >= 0 && indicePedido < sistemaPedidos.getNumPedidosPendientes()) {
                PEDIDO pedido = sistemaPedidos.getPedidoPendientePorIndice(indicePedido);
                if (inventario.verificarStock(pedido.getCodigoProducto(), pedido.getCantidad())) {
                    // Procesar el pedido
                    inventario.retirarStock(pedido.getCodigoProducto(), pedido.getCantidad());
                    sistemaPedidos.procesarPedido(indicePedido);
                    ShowConsoleCursor(false); // Oculta el cursor
                    std::cout << DOUBLE_SPACE << GREEN_COLOR << "Pedido procesado correctamente.";
                    Sleep(1500);
                }
                else {
                    ShowConsoleCursor(false); // Oculta el cursor
                    std::cout << DOUBLE_SPACE << RED_COLOR << "No hay suficiente stock para procesar este pedido.";
                    Sleep(1500);
                }
            }
            else {
                ShowConsoleCursor(false); // Oculta el cursor
                std::cout << DOUBLE_SPACE << MAGENTA_COLOR << "Índice de pedido inválido.\n";
                Sleep(1500);
            }
            break;
        case 4:
            sistemaPedidos.eliminarPedidos();
            break;
        case 5:
            system("cls");
            sistemaPedidos.mostrarHistorialPedidos();
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presione cualquier tecla para continuar...";
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

        cout << CYAN_COLOR << "=== GESTIÓN DE CLIENTES ===" << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> Ver Lista de Clientes" << endl;
        cout << "<2> Eliminar Cliente" << endl;
        cout << "<3> Buscar Clientes" << endl;
        cout << "<4> Volver";
        ShowConsoleCursor(true); // Muestra el cursor
        cout << YELLOW_COLOR << DOUBLE_SPACE << "Seleccione una opcion: " << RESET_COLOR;
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
                cout << MAGENTA_COLOR << DOUBLE_SPACE << "No hay ningún cliente registrado." << endl;
                _sleep(1500); // Espera 1.5 segundos
                file.close();
                break;
            }
            system("cls");
            cout << CYAN_COLOR << "Lista de clientes:" << DOUBLE_SPACE;   
            gestionCliente.displayCustomerList();
            break;
        case 2:
            if (file.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo está vacío
                ShowConsoleCursor(false); // Oculta el cursor
                cout << MAGENTA_COLOR << DOUBLE_SPACE << "No hay ningún cliente registrado." << endl;
                _sleep(1500); // Espera 1.5 segundos
                file.close();
                break;
            }
            system("cls");
            cout << CYAN_COLOR << "Eliminar cliente:" << DOUBLE_SPACE << RESET_COLOR;
            {
                string email;
                cout << YELLOW_COLOR << "Ingrese el correo electrónico del cliente a eliminar: " << RESET_COLOR;
                cin >> email;
                gestionCliente.deleteCustomer(email);
                ShowConsoleCursor(false); // Oculta el cursor
                _sleep(1500); // Espera 1.5 segundos
            }
            break;
        case 3:
            if (file.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo está vacío
                ShowConsoleCursor(false); // Oculta el cursor
                cout << MAGENTA_COLOR << DOUBLE_SPACE << "No hay ningún cliente registrado." << endl;
                _sleep(1500); // Espera 1.5 segundos
                file.close();
                break;
            }
            system("cls");
            cout << CYAN_COLOR << "Buscar clientes: " << DOUBLE_SPACE << RESET_COLOR;
            {
                string searchTerm;
                cout << YELLOW_COLOR << "Ingrese el término de búsqueda (nombre o apellido): " << RESET_COLOR;
                cin >> searchTerm;
                gestionCliente.searchCustomers(searchTerm);
            }
            break;
        case 4:
            break;
        }
    } while (opcion != 4);
}

void sortProductsPrice(string _currentLanguage) {
    
    GESTION_PRODUCTOS productManager;

    int opcion;
	string currentLanguage = _currentLanguage; // Idioma predeterminado

	do {
		system("cls");
		cout << CYAN_COLOR << "=== Ordenar Productos por Precio ===" << RESET_COLOR << DOUBLE_SPACE;
		cout << "<1> Ordenar de menor a mayor" << endl;
		cout << "<2> Ordenar de mayor a menor" << endl;
		cout << "<3> Volver";
        ShowConsoleCursor(true); // Muestra el cursor
		cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese una opción: " << RESET_COLOR;
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
			productManager.ordenarProductosPorPrecioAscendente();
            ShowConsoleCursor(false); // Oculta el cursor
			cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
			_getch();
			system("cls");
			break;
		case 2:
			system("cls");
			productManager.ordenarProductosPorPrecioDescendente();
            ShowConsoleCursor(false); // Oculta el cursor
			cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
			_getch();
			system("cls");
			break;
		case 3:
            productManagementMenu(_currentLanguage);
			break;
		}
	} while (opcion != 3);

}