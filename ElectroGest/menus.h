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
//################## MEN�S DE LA APLICACI�N ###########################//
//#####################################################################//

// Men� general
void generalMenu(); // Men� general

// Men�s de vendedores
void sellerLoginMenu(string _currentLanguage); // Men� de inicio de sesi�n para vendedor
void sellerMenu(string usuario, string _currentLanguag); // Men� de vendedor

// Cliente
void clientRegisterMenu(string _currentLanguag); // Men� de registro para comprador
void clientLoginMenu(string _currentLanguag); // Men� de inicio de sesi�n para comprador
void clientMenu(string _currentLanguag); // Men� de comprador
void homeClientMenu(string _currentLanguag); // Men� de inicio para comprador
void savePassword(const string& email, const string& password, string _currentLanguag); // Guardar la contrase�a cifrada
void saveClientInfo(const CLIENTE& client, string _currentLanguag); // Guardar la informaci�n del comprador en un archivo   

// Productos
void productCatalogMenu(string _currentLanguag); // Men� de cat�logo de productos
void productManagementMenu(string _currentLanguag); // Men� de gesti�n de productos 
void filtrarProductosPorCategoria(string _currentLanguag); // Filtrar productos por categor�a

// Inventario
void inventoryManagementMenu(string _currentLanguag); // Men� de gesti�n de inventario

// Proveedores
void supplierManagementMenu(string _currentLanguag); // Men� de gesti�n de proveedores

// Pedido
void orderingMenu(string _currentLanguag); // Men� de pedidos
void orderManagementMenu(string _currentLanguag); // Men� de gesti�n de pedidos

// Gesti�n de clientes
void customerManagementMenu(string _currentLanguag); // Men� de gesti�n de clientes

void sortProductsPrice(string _currentLanguag); // Ordenar productos por precio

//#####################################################################//
//################## IMPLEMENTACI�N DE LOS MEN�S #####################//
//#####################################################################//

// Funci�n para mostrar el men� general
void generalMenu() {
    int opcion = 0; // Opci�n elegida por el usuario

    string currentLanguage = "espanol"; // Idioma predeterminado

    do {
        system("cls");

        cout << CYAN_COLOR;
        cout << "=====================================" << endl;
        cout << menuTexts[currentLanguage][1] << endl; // Sistema de gesti�n de ventas
        cout << "=====================================" << endl;
        cout << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> " << menuTexts[currentLanguage][2] << endl; // Iniciar sesi�n como vendedor
        cout << "<2> " << menuTexts[currentLanguage][3] << endl; // Iniciar sesi�n como cliente
        cout << "<3> " << menuTexts[currentLanguage][8] << endl; // Cambiar idioma
        cout << "<4> " << menuTexts[currentLanguage][4] << endl; // Salir
        ShowConsoleCursor(true); // Mostar cursor 
        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR; // Ingrese una opci�n
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }
        else if (opcion > 4)
        {
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Opci�n no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        // Evaluador del men� de opciones
        switch (opcion) {
        case 1:
            sellerLoginMenu(currentLanguage); // Men� de inicio de sesi�n para vendedor
            break;
        case 2:
            clientMenu(currentLanguage); // Men� de cliente
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

// Men�s de vendedores

// Funci�n para mostrar el men� de vendedor
void sellerLoginMenu(string _currentLanguage) {
    ShowConsoleCursor(true); // Muestra el cursor en la consola

    system("cls"); // Limpia la consola

    // Definir variables
    string usuario, contrasena;
    string usuarioArchivo, contrasenaArchivo;

    // Idioma predeterminado
    string currentLanguage = _currentLanguage; 
    string currentLanguage = "espanol"; // Idioma predeterminado

    // Crear el objeto ProductManager
    GestionarProveedores supplierManager;

    // Solicita al usuario que ingrese sus datos
    cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][9] << " ===" << DOUBLE_SPACE; // Inicio de sesi�n
    cout << GRAY_COLOR << menuTexts[currentLanguage][10] << DOUBLE_SPACE; // Ingrese sus credenciales
    cout << YELLOW_COLOR << menuTexts[currentLanguage][11] << RESET_COLOR; // Usuario
    cin >> usuario; // Lee el nombre de usuario
    cout << YELLOW_COLOR << menuTexts[currentLanguage][12] << RESET_COLOR; // Contrase�a

    // Oculta la contrase�a mientras se escribe
    char caracter;
    contrasena = ""; // Inicializa la cadena de la contrase�a
    // Bucle para leer la contrase�a
    while (true) {
        caracter = _getch(); // Lee un car�cter sin mostrarlo
        if (caracter == 13) // 13 es el c�digo ASCII para la tecla Enter
            break; // Si es Enter, termina el bucle
        else if (caracter == 8) { // 8 es el c�digo ASCII para la tecla Backspace
            if (contrasena.length() > 0) {
                cout << "\b \b"; // Retrocede y borra el �ltimo car�cter
                contrasena.pop_back(); // Elimina el �ltimo car�cter de la cadena
            }
        }
        else {
            cout << "*"; // Muestra un asterisco en lugar del car�cter
            contrasena.push_back(caracter); // Agrega el car�cter a la contrase�a
        }
    }

    ifstream archivo("seller_data.txt"); // Abre el archivo

    bool encontrado = false;

    // Verifica si el archivo se abri� correctamente
    if (!archivo.is_open()) {
        cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][404] << endl; // Error al abrir el archivo
        return;
    }

    // Lee los datos del archivo l�nea por l�nea y compara con los ingresados por el usuario
    while (archivo >> usuarioArchivo >> contrasenaArchivo) {
        // Compara los datos del archivo con los ingresados por el usuario
        if (usuario == usuarioArchivo && contrasena == contrasenaArchivo) {
            encontrado = true;
            break; // Se encontr� la coincidencia, no es necesario continuar buscando
        }
    }

    // Cierra el archivo
    archivo.close();

    // Si se encontr� el usuario
    if (encontrado) {
        sellerMenu(usuario, currentLanguage); // Muestra el men� de vendedor
    }
    else {
        ShowConsoleCursor(false); // Oculta el cursor
        cout << DOUBLE_SPACE << RED_COLOR << menuTexts[currentLanguage][13] << endl; // Usuario o contrase�a incorrectos
        Sleep(1500); // Espera 1.5 segundo
        system("cls"); // Limpia la consola
        ShowConsoleCursor(true); // Muestra el cursor
        sellerLoginMenu(currentLanguage); // Intenta nuevamente
    }
}

// Funci�n para mostrar el men� de vendedor
void sellerMenu(string usuario, string _currentLanguage) {

    // Crear los objetos de las clases

    int opcion; // Opci�n elegida por el usuario
    string currentLanguage = _currentLanguage; // Idioma predeterminado

    // Bucle para mostrar el men� y obtener la opci�n del usuario
    do {

        system("cls"); // Limpia la consola

        cout << CYAN_COLOR << "�" << menuTexts[currentLanguage][14] << usuario << menuTexts[currentLanguage][15] << ":)" << DOUBLE_SPACE << RESET_COLOR; // Bienvenido
        cout << "<1> " << menuTexts[currentLanguage][16] << endl; // Gesti�n de productos
        cout << "<2> " << menuTexts[currentLanguage][17] << endl; // Gesti�n de inventario
        cout << "<3> " << menuTexts[currentLanguage][18] << endl; // Gesti�n de proveedores
        cout << "<4> " << menuTexts[currentLanguage][19] << endl; // Gesti�n de pedidos
        cout << "<5> " << menuTexts[currentLanguage][20] << endl; // Gesti�n de clientes
        cout << "<6> " << menuTexts[currentLanguage][4]; // Salir
        ShowConsoleCursor(true); // Muestra el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR; cin >> opcion; // Ingrese una opci�n

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }
        else if (opcion > 6)
        {
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Opci�n no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        // Evaluador de opciones
        switch (opcion) {
        case 1:
            productManagementMenu(_currentLanguage); // Men� de gesti�n de productos
            break;
        case 2:
            inventoryManagementMenu(_currentLanguage); // Men� de gesti�n de inventario
            break;
        case 3:
            supplierManagementMenu(_currentLanguage); // Men� de gesti�n de proveedores
            break;
        case 4:
            orderManagementMenu(_currentLanguage); // Men� de gesti�n de pedidos
            break;
        case 5:
            customerManagementMenu(_currentLanguage); // Men� de gesti�n de clientes
            break;
        case 6:
			break;
        }
    } while (opcion != 6); // El bucle contin�a hasta que se elige la opci�n de salir
}

// Men�s de clientes 

// Funci�n para mostrar el men� de registro para comprador
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
        cout << MAGENTA_COLOR << endl << menuTexts[currentLanguage][36]; // Nombre no v�lido

        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][37] << RESET_COLOR; // Ingrese un nombre v�lido
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
        // Solicitar al usuario que ingrese un correo electr�nico
        cout << YELLOW_COLOR << menuTexts[currentLanguage][25] << RESET_COLOR; // Correo electr�nico
        getline(cin, input_correo);

        // Verificar si la direcci�n de correo electr�nico cumple con la expresi�n regular
        if (!regex_match(input_correo, correoRegex)) {
            // La direcci�n de correo electr�nico no es v�lida
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][34] << DOUBLE_SPACE;
        }
    } while (!regex_match(input_correo, correoRegex));
    comprador.setCorreoElectronico(input_correo);

    // Solicitar al usuario que ingrese una contrase�a
    cout << YELLOW_COLOR << menuTexts[currentLanguage][12] << RESET_COLOR; // Contrase�a
    string input_contrasenia;
    getline(cin, input_contrasenia);
    comprador.setContrasenia(input_contrasenia);

    // Validar que se haya ingresado una contrase�a
    while (input_contrasenia.empty()) {
        cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][40] << RESET_COLOR << endl;
        cout << YELLOW_COLOR << menuTexts[currentLanguage][12] << RESET_COLOR; // Contrase�a
        getline(cin, input_contrasenia);
        comprador.setContrasenia(input_contrasenia);
    }

    // Solicitar al usuario que confirme la contrase�a
    cout << YELLOW_COLOR << menuTexts[currentLanguage][26] << RESET_COLOR; // Confirmar Contrase�a
    string input_confirmar_contrasenia;
    getline(cin, input_confirmar_contrasenia);

    // Verificar si las contrase�as coinciden
    while (input_contrasenia != input_confirmar_contrasenia) {
        cout << MAGENTA_COLOR << endl << menuTexts[currentLanguage][41] << RESET_COLOR << DOUBLE_SPACE;

        // Solicitar al usuario que ingrese la contrase�a nuevamente
        cout << YELLOW_COLOR << menuTexts[currentLanguage][12] << RESET_COLOR; // Contrase�a
        getline(cin, input_contrasenia);
        comprador.setContrasenia(input_contrasenia);

        // Solicitar al usuario que confirme la contrase�a nuevamente
        cout << YELLOW_COLOR << menuTexts[currentLanguage][26] << RESET_COLOR; // Confirmar Contrase�a
        getline(cin, input_confirmar_contrasenia);
    }

    // Solicitar al usuario que ingrese la direcci�n
    cout << YELLOW_COLOR << menuTexts[currentLanguage][28] << RESET_COLOR; // Direcci�n
    string input_direccion;
    getline(cin, input_direccion);
    comprador.setDireccion(input_direccion);

    string input_telefono;
    do {
        // Solicitar al usuario que ingrese el tel�fono
        cout << YELLOW_COLOR << menuTexts[currentLanguage][29] << RESET_COLOR; // Tel�fono
        getline(cin, input_telefono);
        // Verificar si la entrada es un n�mero de 9 d�gitos y no existe en el archivo
        if (input_telefono.length() != 9 || !all_of(input_telefono.begin(), input_telefono.end(), ::isdigit)) {
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][30] << DOUBLE_SPACE; // N�mero de tel�fono no v�lido
        }
        else if(clienteManager.numeroExistente(input_telefono))
		{
			cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][42] << DOUBLE_SPACE; // N�mero de tel�fono ya registrado
		}
    } while (input_telefono.length() != 9 || !all_of(input_telefono.begin(), input_telefono.end(), ::isdigit) || clienteManager.numeroExistente(input_telefono));
    comprador.setTelefono(input_telefono);

    string input_nacimiento;
    do {
        // Solicitar al usuario que ingrese la fecha de nacimiento
        cout << YELLOW_COLOR << menuTexts[currentLanguage][31] << RESET_COLOR; // Fecha de nacimiento
        getline(cin, input_nacimiento);

        // Definir un stringstream para separar la entrada en d�a, mes y a�o
        istringstream iss(input_nacimiento);
        int dia, mes, anio;
        char slash1, slash2;
        iss >> dia >> slash1 >> mes >> slash2 >> anio;

        // Validar el formato de la fecha y los rangos de d�a, mes y a�o
        if (iss.fail() || slash1 != '/' || slash2 != '/' || dia < 1 || dia > 31 || mes < 1 || mes > 12 || anio < 1944 || anio > 2006) {
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][35] << DOUBLE_SPACE; // Fecha de nacimiento no v�lida
        }
        else {
            // La fecha de nacimiento es v�lida
            // Asignar la fecha de nacimiento al comprador
            string fechaNacimiento = to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio);
            comprador.setFechaNacimiento(fechaNacimiento);
            break;
        }
    } while (true); // Repetir hasta que se ingrese una fecha de nacimiento v�lida

    string input_genero;
    do {
        // Solicitar al usuario que ingrese el g�nero
        cout << YELLOW_COLOR << menuTexts[currentLanguage][32] << RESET_COLOR; // Sexo
        getline(cin, input_genero);
        if (input_genero != "M" && input_genero != "F") {
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][33] << DOUBLE_SPACE; // G�nero no v�lido
        }
    } while (input_genero != "M" && input_genero != "F");
    comprador.setGenero(input_genero);

    // Guardar la informaci�n del comprador en un archivo
    saveClientInfo(comprador, _currentLanguage);
    savePassword(input_correo, input_contrasenia, _currentLanguage); // Guardar la contrase�a cifrada

    ShowConsoleCursor(false); // Oculta el cursor

    Sleep(1500); // Espera 1.5 segundos
    homeClientMenu(_currentLanguage); // Muestra el men� del vendedor
}

// Funci�n para mostrar el men� de inicio de sesi�n para comprador
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

    // Oculta la contrase�a mientras se escribe
    char caracter;
    password = "";
    while (true) {
        caracter = _getch(); // Lee un car�cter sin mostrarlo
        if (caracter == 13) // 13 es el c�digo ASCII para la tecla Enter
            break; // Si es Enter, termina el bucle
        else if (caracter == 8) { // 8 es el c�digo ASCII para la tecla Backspace
            if (password.length() > 0) {
                cout << "\b \b"; // Retrocede y borra el �ltimo car�cter
                password.pop_back(); // Elimina el �ltimo car�cter de la cadena
            }
        }
        else {
            cout << "*"; // Muestra un asterisco en lugar del car�cter
            password.push_back(caracter); // Agrega el car�cter a la contrase�a
        }
    }

    // Abrir el archivo de registro de compradores
    ifstream file("passwords.txt");
    if (file.is_open()) {
        string line;
        // Leer el archivo l�nea por l�nea
        while (getline(file, line)) {
            // Dividir la l�nea en tokens usando el espacio como delimitador
            istringstream iss(line);
            string emailFromFile, passwordFromFile;
            iss >> emailFromFile >> passwordFromFile;
            // Comparar el correo electr�nico y la contrase�a ingresados con los almacenados en el archivo
            if (email == emailFromFile && password == passwordFromFile) {
                loggedIn = true;
                ShowConsoleCursor(false);
                cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][45] << DOUBLE_SPACE;
                Sleep(2000);
                system("cls");
                homeClientMenu(_currentLanguage); // Mostrar el men� del comprador
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
        clientMenu(_currentLanguage);
    }
    else {
        ShowConsoleCursor(false);
        cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][47] << DOUBLE_SPACE;
        Sleep(2000);
        system("cls");
        clientLoginMenu(_currentLanguage);
    }
}

// Funci�n para mostrar el men� de comprador
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

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
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

// Funci�n para mostrar el men� de inicio para comprador
void homeClientMenu(string _currentLanguage) {
    ShowConsoleCursor(true);   

	system("cls");
    SISTEMA_PEDIDOS sistemaPedidos;

    sistemaPedidos.cargarPedidosPendientes();
    sistemaPedidos.cargarPedidosProcesados();

	int opcion = 0;
    string currentLanguage = "espanol"; // Idioma predeterminado

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

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
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
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 4:
            break;
        }
    } while (opcion != 4);
}

// Funci�n para guardar la informaci�n del comprador en el archivo
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

        cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][67] << endl; // Mostrar un mensaje de confirmaci�n
    }
    else {
        cout << menuTexts[currentLanguage][404] << endl; // Error al abrir el archivo
    }
}

// Funci�n para guardar la contrase�a cifrada
void savePassword(const string& email, const string& password, string _currentLanguage) {
    string currentLanguage = _currentLanguage; // Idioma predeterminado
    ofstream passwordFile("passwords.txt", ios::app); // Abre el archivo en modo append
    if (passwordFile.is_open()) {
        passwordFile << email << " " << password << "\n"; // Escribir el correo electr�nico y la contrase�a en el archivo
        passwordFile.close();
    }
    else {
        cout << menuTexts[currentLanguage][404] << endl; // Error al abrir el archivo
    }
}

// Funciones de gesti�n de productos    

// Funci�n para mostrar el men� de cat�logo de productos
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

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion)
        {
        case 1: 
            system("cls");
            productManager.mostrarTodosLosProductos();
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 2:
            filtrarProductosPorCategoria(_currentLanguage);
            break;
        case 3:
            system("cls");
            cout << YELLOW_COLOR << menuTexts[currentLanguage][72] << RESET_COLOR;
            cin.ignore();
            getline(cin, nombre);
            cout << endl;
            productManager.buscarProductoPorNombre(nombre);
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

// Funci�n para filtrar productos por categor�a
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

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            system("cls");
            productManager.filtrarPorPrecio(productManager);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 2:
            system("cls");
            productManager.filtrarPorColor(productManager);
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            system("cls");
            break;
        case 3:
            system("cls");
            productManager.filtrarPorMarca(productManager);
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

// Funci�n para mostrar el men� y manejar la interacci�n con el usuario
void productManagementMenu(string _currentLanguage) {
    GESTION_PRODUCTOS manager; // Crear el gestor de productos con el archivo
    int opcion;
    int opcion_ordenar;
    string currentLanguage = _currentLanguage; // Idioma predeterminado

    do{

        system("cls"); // Limpiar la pantalla en sistemas Windows

        cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][87] <<" ===" << DOUBLE_SPACE << RESET_COLOR;
        cout << "<1> " << menuTexts[currentLanguage][88] << endl;
        cout << "<2> " << menuTexts[currentLanguage][89] << endl;
        cout << "<3> " << menuTexts[currentLanguage][90] << endl;
        cout << "<4> " << menuTexts[currentLanguage][91] << endl;
        cout << "<5> " << menuTexts[currentLanguage][92] << endl;
        cout << "<6> " << menuTexts[currentLanguage][50];
        ShowConsoleCursor(true); // Mostrar el cursor
        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR;
        cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            system("cls");
            manager.mostrarTodosLosProductos();

            do
            {

                cout << endl << YELLOW_COLOR << menuTexts[currentLanguage][93] << DOUBLE_SPACE << RESET_COLOR;
                cout << "<1> " << menuTexts[currentLanguage][94] << endl;
                cout << "<2> " << menuTexts[currentLanguage][95];
                ShowConsoleCursor(true); // Muestra el cursor
                cout << YELLOW_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][5] << RESET_COLOR;
                cin >> opcion_ordenar;

                if (opcion_ordenar == 1) {
                    sortProductsPrice(_currentLanguage);
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

// Funci�n para mostrar el men� de gesti�n de inventario
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
        std::cout << CYAN_COLOR << "=== Men� de Gesti�n de Inventarios ===" << endl << RESET_COLOR << std::endl;
        std::cout << "<1> Ver Inventario" << std::endl;
        std::cout << "<2> A�adir Stock" << std::endl;
        std::cout << "<3> Retirar Stock" << std::endl;
        std::cout << "<4> Historial de Movimientos" << std::endl;
        std::cout << "<5> " << menuTexts[currentLanguage][4] << std::endl;
        ShowConsoleCursor(true); // Muestra el cursor
        std::cout << endl << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR;
        std::cin >> opcion;

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            gestionInventarios.verInventario();
            break;
        case 2:
            system("cls");
            std::cout << YELLOW_COLOR << "Ingrese el c�digo del producto que desea agregar al inventario: " << RESET_COLOR;
            std::cin >> codigoProducto;
            producto = gestorProductos.buscarProducto(codigoProducto); // Obtiene un puntero al producto
            if (producto != nullptr) {
                int cantidad;
                std::cout << YELLOW_COLOR << "Ingrese la cantidad de stock a a�adir: " << RESET_COLOR;
                while (!(std::cin >> cantidad) || cantidad <= 0) {
                    if (std::cin.fail()) {
                        // Limpiar el estado de error y descartar la entrada inv�lida
                        std::cin.clear();
                        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                        std::cout << endl << MAGENTA_COLOR << "Debe ingresar un n�mero v�lido para la cantidad de stock." << RESET_COLOR << DOUBLE_SPACE;
                    }
                    else {
                        std::cout << MAGENTA_COLOR << "La cantidad de stock debe ser un n�mero positivo." << RESET_COLOR << DOUBLE_SPACE;
                    }
                    std::cout << YELLOW_COLOR << "Ingrese nuevamente la cantidad de stock: " << RESET_COLOR;
                }
                gestionInventarios.a�adirStock(producto->producto.getCodigo(), cantidad); // Utiliza el c�digo del producto

                ShowConsoleCursor(false); // Oculta el cursor
                cout << DOUBLE_SPACE << GREEN_COLOR << "Stock a�adido exitosamente." << RESET_COLOR;
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
            std::cout << YELLOW_COLOR << "Ingrese el c�digo del producto del cual desea retirar stock: " << RESET_COLOR;
            std::cin >> codigoProducto;
            producto = gestorProductos.buscarProducto(codigoProducto); // Asigna valor a producto
            if (producto != nullptr) {
                std::cout << YELLOW_COLOR << "Ingrese la cantidad de stock a retirar: " << RESET_COLOR;
                while (!(std::cin >> cantidad) || cantidad <= 0) {
                    if (std::cin.fail()) {
                        // Limpiar el estado de error y descartar la entrada inv�lida
                        std::cin.clear();
                        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                        std::cout << MAGENTA_COLOR << "Debe ingresar un n�mero v�lido para la cantidad de stock." << RESET_COLOR << DOUBLE_SPACE;
                    }
                    else {
                        std::cout << MAGENTA_COLOR << "La cantidad de stock debe ser un n�mero positivo." << RESET_COLOR << DOUBLE_SPACE;
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

// Funci�n para mostrar el men� y obtener la opci�n del usuario
void supplierManagementMenu(string _currentLanguage) {
    int opcion;
    string nombreBuscar;
    const string archivoProveedores = "supplier_data.txt";

    string currentLanguage = _currentLanguage; // Idioma predeterminado

    GestionarProveedores supplierManager; // Crear un objeto de la clase GestionarProveedores

    supplierManager.cargarListaDesdeArchivo();
    
    do {
        system("cls");
        cout << CYAN_COLOR << "=== GESTI�N DE PROVEEDORES ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << "<1> Ver lista de proveedores" << endl;
        cout << "<2> Agregar nuevo proveedor" << endl;
        cout << "<3> Actualizar informaci�n de proveedor" << endl;
        cout << "<4> Eliminar proveedor" << endl;
        cout << "<5> Buscar proveedor" << endl;
        cout << "<6> " << menuTexts[currentLanguage][50] << DOUBLE_SPACE;
        ShowConsoleCursor(true); // Muestra el cursor
        cout << YELLOW_COLOR << "Seleccione una opcion: " << RESET_COLOR;
        cin >> opcion;

        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero." << endl;
            Sleep(1000);
            ShowConsoleCursor(true);
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            // Verificar si la lista de proveedores est� vac�a
            if (supplierManager.listaProveedoresVacia()) {
                ShowConsoleCursor(false); // Oculta el cursor
				cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se cuenta con proveedores por el momento." << RESET_COLOR;
				Sleep(1500);
				break;
			}
            system("cls");
            supplierManager.verListaProveedores();
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
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
            // Verificar si la lista de proveedores est� vac�a
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
            // Verificar si la lista de proveedores est� vac�a
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
            // Verificar si la lista de proveedores est� vac�a
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

// Funci�n para realizar un pedido
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
        std::cout << "<5> " << menuTexts[currentLanguage][4];
        ShowConsoleCursor(true); // Muestra el cursor
        std::cout << YELLOW_COLOR << DOUBLE_SPACE << "Seleccione una opci�n: " << RESET_COLOR;
        std::cin >> opcion;

        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Entrada no v�lida, por favor ingrese un n�mero." << endl;
            Sleep(1000);
            ShowConsoleCursor(true);
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        switch (opcion) {
        case 1:
            system("cls");
            std::cout << YELLOW_COLOR << "Ingrese el c�digo del producto a agregar: " << RESET_COLOR;
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
                    // Limpiar el estado de error y descartar la entrada inv�lida
                    std::cin.clear();
                    cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
                    std::cout << MAGENTA_COLOR << "Debe ingresar un n�mero v�lido para la cantidad." << RESET_COLOR << DOUBLE_SPACE;
                }
                else {
                    std::cout << MAGENTA_COLOR << "La cantidad debe ser un n�mero positivo." << RESET_COLOR << DOUBLE_SPACE;
                }
                std::cout << YELLOW_COLOR << "Ingrese nuevamente la cantidad a agregar: " << RESET_COLOR;
            }

            // Verificar si hay suficiente stock antes de agregar al carrito
            if (inventario.verificarStock(codigoProducto, cantidad)) {
                // Aqu� puedes implementar la l�gica para agregar al carrito
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
                carrito.limpiarCarrito(); // Limpiar el carrito despu�s de confirmar el pedido
                ShowConsoleCursor(false);
                std::cout << DOUBLE_SPACE << GREEN_COLOR << "Pedido confirmado correctamente.";
                Sleep(1500);
            }
            else {
                ShowConsoleCursor(false);
                std::cout << endl << MAGENTA_COLOR << "El carrito est� vac�o. No se puede confirmar el pedido.";
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
                std::cout << endl << MAGENTA_COLOR << "El carrito est� vac�o. No se puede cancelar el pedido.";
                Sleep(1500);
            }
            break;
        case 5:
            break;
        }
    }
}

// Funci�n para gestionar pedidos
void orderManagementMenu(string _currentLanguage) {
    SISTEMA_PEDIDOS sistemaPedidos;
    // Antes del bucle o en alg�n lugar antes de utilizarlo en tu c�digo
    GESTION_INVENTARIO inventario;

    sistemaPedidos.cargarPedidosPendientes();
    sistemaPedidos.cargarPedidosProcesados();

    int opcion;
    string currentLanguage = _currentLanguage; // Idioma predeterminado

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

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            std::cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
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
            cout << YELLOW_COLOR << menuTexts[currentLanguage][76] << RESET_COLOR;
            int indicePedido;
            std::cin >> indicePedido;
            if (indicePedido >= 0 && indicePedido < sistemaPedidos.getNumPedidosPendientes()) {
                PEDIDO pedido = sistemaPedidos.getPedidoPendientePorIndice(indicePedido);
                if (inventario.verificarStock(pedido.getCodigoProducto(), pedido.getCantidad())) {
                    // Procesar el pedido
                    inventario.retirarStock(pedido.getCodigoProducto(), pedido.getCantidad());
                    sistemaPedidos.procesarPedido(indicePedido);
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
                std::cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][73]; // �ndice no v�lido
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
            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
            _getch();
            break;
        case 6:
            break;
        }
    }
}

// Funci�n para mostrar el men� de gesti�n de clientes
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

        // Verifica si la entrada fall�
        if (cin.fail()) { // Verifica si la entrada fall�
            cin.clear(); // Limpia el estado de cin
            cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no v�lida
            Sleep(1500); // Espera 1.5 segundos
            continue; // Contin�a al siguiente ciclo del bucle do-while
        }

        ifstream file("client_registration.txt");

        switch (opcion) {
        case 1:
            if (file.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo est� vac�o
                ShowConsoleCursor(false); // Oculta el cursor
                cout << MAGENTA_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][59] << endl;
                _sleep(1500); // Espera 1.5 segundos
                file.close();
                break;
            }
            system("cls");
            cout << CYAN_COLOR << menuTexts[currentLanguage][66] << DOUBLE_SPACE;
            gestionCliente.displayCustomerList();
            break;
        case 2:
            if (file.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo est� vac�o
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
                gestionCliente.deleteCustomer(email);
                ShowConsoleCursor(false); // Oculta el cursor
                _sleep(1500); // Espera 1.5 segundos
            }
            break;
        case 3:
            if (file.peek() == ifstream::traits_type::eof()) { // Verificar si el archivo est� vac�o
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
		cout << "<1> " << menuTexts[currentLanguage][55] << endl;
		cout << "<2> " << menuTexts[currentLanguage][56] << endl;
		cout << "<3> " << menuTexts[currentLanguage][50];
        ShowConsoleCursor(true); // Muestra el cursor
		cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][5] << RESET_COLOR;
		cin >> opcion;

		// Verifica si la entrada fall�
		if (cin.fail()) { // Verifica si la entrada fall�
			cin.clear(); // Limpia el estado de cin
			cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
			ShowConsoleCursor(false); // Oculta el cursor
			cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][6]; // Entrada no v�lida
			Sleep(1500); // Espera 1.5 segundos
			continue; // Contin�a al siguiente ciclo del bucle do-while
		}

		switch (opcion) {
		case 1:
			system("cls");
			productManager.ordenarProductosPorPrecioAscendente();
            ShowConsoleCursor(false); // Oculta el cursor
			cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
			_getch();
			system("cls");
			break;
		case 2:
			system("cls");
			productManager.ordenarProductosPorPrecioDescendente();
            ShowConsoleCursor(false); // Oculta el cursor
			cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51];
			_getch();
			system("cls");
			break;
		case 3:
            productManagementMenu(_currentLanguage);
			break;
		}
	} while (opcion != 3);

}