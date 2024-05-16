#pragma once
#include "product_manager_class.h"
#include <limits>

// Funcionalidad para agregar un nuevo producto
void addNewProduct(GESTION_PRODUCTOS& manager, string _currentLanguage) {

    // Idioma predeterminado
    string currentLanguage = _currentLanguage;

    // Variables para almacenar los datos del nuevo producto
    string codigo, nombre, marca, modelo, material, color;
    double precio, ancho, alto, largo, peso;
    int garantia;

    cin.ignore(); // Limpiar el búfer de entrada antes de getline

    // Solicitar al usuario los datos del nuevo producto
    cout << YELLOW_COLOR << menuTexts[currentLanguage][171] << RESET_COLOR; // Solicitar el código del producto
    getline(cin, codigo);

    // Verificar si el código del producto ya existe
    if (codigo.empty()) {
        cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][172] << RESET_COLOR << DOUBLE_SPACE; // Mensaje de error
    }
    else if (manager.hasCodigo(codigo)) {
        cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][173] << RESET_COLOR << DOUBLE_SPACE; // Mensaje de error
        cout << YELLOW_COLOR << menuTexts[currentLanguage][174] << RESET_COLOR; // Solicitar nuevamente el código
        getline(cin, codigo);
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][175] << RESET_COLOR; // Solicitar el nombre
    getline(cin, nombre);

    // Verificar si el nombre contiene caracteres no alfabéticos
    if (nombre.empty() || any_of(nombre.begin(), nombre.end(), [](char c) { return !isalpha(c) && c != ' '; })) {
        cout << RED_COLOR << menuTexts[currentLanguage][176] << RESET_COLOR << endl; // Mensaje de error
        cout << YELLOW_COLOR << menuTexts[currentLanguage][177] << RESET_COLOR; // Solicitar nuevamente el nombre
        getline(cin, nombre);
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][178] << RESET_COLOR; // Solicitar la marca
    getline(cin, marca);

    // Verificar si la marca contiene caracteres no alfabéticos
    if (marca.empty() || any_of(marca.begin(), marca.end(), [](char c) { return !isalpha(c) && c != ' '; })) {
        cout << RED_COLOR << menuTexts[currentLanguage][176] << RESET_COLOR << endl; // Mensaje de error
        cout << YELLOW_COLOR << menuTexts[currentLanguage][179] << RESET_COLOR; // Solicitar nuevamente la marca
        getline(cin, marca);
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][180] << RESET_COLOR; // Solicitar el precio
    while (!(cin >> precio) || precio <= 0) {
        cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][181] << RESET_COLOR << DOUBLE_SPACE; // Mensaje de error
        cin.clear(); // Limpia los bits de error
        cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << menuTexts[currentLanguage][182] << RESET_COLOR; // Solicitar nuevamente el precio
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][183] << RESET_COLOR; // Solicitar el modelo
    cin.ignore();
    getline(cin, modelo);

    // Verificar si el modelo contiene caracteres no alfanuméricos
    if (modelo.empty() || any_of(modelo.begin(), modelo.end(), [](char c) { return !isalnum(c); })) {
        cout << MAGENTA_COLOR << menuTexts[currentLanguage][184] << RESET_COLOR << endl; // Mensaje de error
        cout << YELLOW_COLOR << menuTexts[currentLanguage][185] << RESET_COLOR; // Solicitar nuevamente el modelo
        getline(cin, modelo);   
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][186] << RESET_COLOR; // Solicitar el ancho
    cin >> ancho;

    // Verificar si el ancho es un número positivo
    if (ancho <= 0 || cin.fail()) {
        cout << RED_COLOR << menuTexts[currentLanguage][181] << RESET_COLOR << endl; // Mensaje de error
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << menuTexts[currentLanguage][187] << RESET_COLOR; // Solicitar nuevamente el ancho
        cin.ignore();
        cin >> ancho;
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][188] << RESET_COLOR; // Solicitar el alto
    cin >> alto;

    // Verificar si el alto es un número positivo
    if (alto <= 0 || cin.fail()) {
        cout << RED_COLOR << menuTexts[currentLanguage][181] << RESET_COLOR << endl; // Mensaje de error
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << menuTexts[currentLanguage][189] << RESET_COLOR; // Solicitar nuevamente el alto
        cin.ignore();
        cin >> alto;
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][190] << RESET_COLOR; // Solicitar el largo
    cin >> largo;

    // Verificar si el largo es un número positivo
    if (largo <= 0 || cin.fail()) {
        cout << RED_COLOR << menuTexts[currentLanguage][181] << RESET_COLOR << endl; // Mensaje de error
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << menuTexts[currentLanguage][191] << RESET_COLOR; // Solicitar nuevamente el largo
        cin.ignore();
        cin >> largo;
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][192] << RESET_COLOR; // Solicitar el peso
    cin >> peso;

    // Verificar si el peso es un número positivo
    if (peso <= 0 || cin.fail()) {
        cout << RED_COLOR << menuTexts[currentLanguage][181] << RESET_COLOR << endl; // Mensaje de error
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << menuTexts[currentLanguage][193] << RESET_COLOR; // Solicitar nuevamente el peso
        cin.ignore();
        cin >> peso;
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][194] << RESET_COLOR; // Solicitar el material
    cin.ignore();
    getline(cin, material);

    // Verificar si el material contiene caracteres no alfanuméricos
    if (material.empty() || !all_of(material.begin(), material.end(), ::isalnum)) {
        cout << RED_COLOR << menuTexts[currentLanguage][176] << RESET_COLOR << endl; // Mensaje de error
        cout << YELLOW_COLOR << menuTexts[currentLanguage][195] << RESET_COLOR; // Solicitar nuevamente el material
        getline(cin, material);
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][196] << RESET_COLOR; // Solicitar el color
    getline(cin, color);

    // Verificar si el color contiene caracteres no alfabéticos
    if (color.empty() || !all_of(color.begin(), color.end(), ::isalpha)) {
        cout << RED_COLOR << menuTexts[currentLanguage][176] << RESET_COLOR << endl; // Mensaje de error
        cout << YELLOW_COLOR << menuTexts[currentLanguage][197] << RESET_COLOR; // Solicitar nuevamente el color
        getline(cin, color);        
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][198] << RESET_COLOR; // Solicitar la garantía
    cin >> garantia;

    // Verificar si la garantía es un número positivo
    if (garantia <= 0 || cin.fail()) {
        cout << RED_COLOR << menuTexts[currentLanguage][181] << RESET_COLOR << endl; // Mensaje de error
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << menuTexts[currentLanguage][199] << RESET_COLOR; // Solicitar nuevamente la garantía
        cin.ignore();
        cin >> garantia;
    }

    PRODUCTO nuevoProducto(codigo, nombre, marca, precio, modelo, ancho, alto, largo, peso, material, color, garantia);
    manager.agregarProducto(nuevoProducto);

    // Mostrar mensaje de éxito
    ShowConsoleCursor(false);
    cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][200] << RESET_COLOR << endl; // Mensaje de éxito
    _sleep(1500); // Esperar 1.5 segundos antes de limpiar la pantalla
}

// Función para actualizar un producto
void updateProductProcedure(GESTION_PRODUCTOS& manager, string _currentLanguage) {

    // Idioma predeterminado
    string currentLanguage = _currentLanguage;

    // Variables para almacenar los datos del producto a actualizar
    string codigo;
    double nuevoPrecio = 0;
    string nuevoCodigo;
    int nuevaGarantia;

    cout << YELLOW_COLOR << menuTexts[currentLanguage][106] << RESET_COLOR; // Solicitar el código del producto
    cin.ignore();
    getline(cin, codigo);

    // Verificar si el producto existe antes de actualizarlo
    if (!manager.existeProducto(codigo)) {
        ShowConsoleCursor(false);
        cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][201] << RESET_COLOR << endl; // Mensaje de error
        _sleep(1500);
        return;
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][202] << RESET_COLOR; // Solicitar el nuevo precio

    // Solicitar al usuario el nuevo precio del producto
    while (!(cin >> nuevoPrecio) || nuevoPrecio <= 0) {
        if (cin.fail()) {
            // Limpiar el estado de error y descartar la entrada inválida
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][181] << RESET_COLOR << DOUBLE_SPACE;  // Mensaje de error
        }
        else {
            // Verificar si la entrada contiene caracteres no numéricos
            bool contieneNoNumeros = false;
            string entradaInvalida;
            getline(cin, entradaInvalida);

            // Verificar si la entrada contiene caracteres no numéricos
            for (char c : entradaInvalida) {
                if (!isdigit(c)) {
                    contieneNoNumeros = true;
                    break;
                }
            }

            // Mostrar mensaje de error si la entrada contiene caracteres no numéricos
            if (contieneNoNumeros) {
                cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][181] << RESET_COLOR << DOUBLE_SPACE; // Mensaje de error
            }
            else {
                cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][181] << RESET_COLOR << DOUBLE_SPACE; // Mensaje de error
            }
        }
        cout << YELLOW_COLOR << menuTexts[currentLanguage][182] << RESET_COLOR; // Solicitar nuevamente el precio
    }

    cin.ignore();

    cout << YELLOW_COLOR << menuTexts[currentLanguage][203] << RESET_COLOR; // Solicitar el nuevo código del producto
    getline(cin, nuevoCodigo);

    // Verificar si el nuevo código ya existe
    while (nuevoCodigo.empty() || manager.hasCodigo(nuevoCodigo)) {
        if (nuevoCodigo.empty()) {
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][208] << RESET_COLOR << DOUBLE_SPACE; // Mensaje de error
        }
        else {
            cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][207] << RESET_COLOR << DOUBLE_SPACE; // Mensaje de error
        }
        cout << YELLOW_COLOR << menuTexts[currentLanguage][206] << RESET_COLOR; // Solicitar nuevamente el código
        getline(cin, nuevoCodigo);
    }

    cout << YELLOW_COLOR << menuTexts[currentLanguage][204] << RESET_COLOR; // Solicitar la nueva garantía

    // Solicitar al usuario la nueva garantía del producto
    while (!(cin >> nuevaGarantia) || nuevaGarantia <= 0) {
        cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][181] << RESET_COLOR << DOUBLE_SPACE; // Mensaje de error
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        cout << YELLOW_COLOR << menuTexts[currentLanguage][204] << RESET_COLOR; // Solicitar nuevamente la garantía
    }

    manager.actualizarProducto(codigo, nuevoPrecio, nuevoCodigo, nuevaGarantia);
    
    ShowConsoleCursor(false);
    cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][205]; // Mensaje de éxito
    _sleep(1500);
}

// Función para eliminar un producto
void removeProductProcedure(GESTION_PRODUCTOS& manager, string _currentLenguage) {

    // Idioma predeterminado
    string currentLanguage = _currentLenguage;

    string codigo;

    // Solicitar al usuario el código del producto a eliminar
    cout << YELLOW_COLOR << "Ingrese el código del producto que desea eliminar: " << RESET_COLOR;
    cin.ignore(); // Limpiar el búfer de entrada antes de getline
    getline(cin, codigo);

    ShowConsoleCursor(false); // Ocultar el cursor para evitar errores de visualización

    // Verificar si el producto existe antes de eliminarlo
    if (manager.existeProducto(codigo)) {
        // Eliminar el producto del gestor de productos
        manager.eliminarProducto(codigo);

        // Mostrar mensaje de éxito
        cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][210] << endl;
        _sleep(1500); // Esperar 1.5 segundos antes de limpiar la pantalla
    }
    else {
        // Mostrar mensaje de error si el producto no existe
        cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][211] << codigo << menuTexts[currentLanguage][212] << endl;
        _sleep(1500); // Esperar 1.5 segundos antes de limpiar la pantalla
    }
}

// Función para mostrar el menú de gestión de productos
void searchProduct(GESTION_PRODUCTOS& manager, string _currentLenguage) {
    
    // Idioma predeterminado
    string currentLanguage = _currentLenguage;

    string codigo;

    // Solicitar al usuario el código del producto a buscar
    ShowConsoleCursor(true);

    cout << YELLOW_COLOR << menuTexts[currentLanguage][209] << RESET_COLOR; // Solicitar el código del producto
    cin.ignore(); // Limpiar el búfer de entrada antes de getline
    getline(cin, codigo);
    cout << endl;

    // Buscar y mostrar la información del producto
    manager.buscarYMostrarProducto(codigo);
}