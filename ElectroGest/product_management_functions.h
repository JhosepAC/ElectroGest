#pragma once
#include "product_manager_class.h"
#include <limits> // Agrega esta inclusión para usar numeric_limits
#include <limits> // Para obtener el límite de valores enteros

void addNewProduct(GESTION_PRODUCTOS& manager) {
    string codigo, nombre, marca, modelo, material, color;
    double precio, ancho, alto, largo, peso;
    int garantia;

    cin.ignore(); // Limpiar el búfer de entrada antes de getline

    cout << YELLOW_COLOR << "Ingrese el código del nuevo producto: " << RESET_COLOR;
    getline(cin, codigo);
    if (codigo.empty()) {
        cout << RED_COLOR << "El código del producto no puede estar vacío." << RESET_COLOR << endl;
    }
    else if (manager.hasCodigo(codigo)) {
        cout << RED_COLOR << "El código del producto ya existe." << RESET_COLOR << endl;
        cout << YELLOW_COLOR << "Ingrese nuevamente el código: " << RESET_COLOR;
        getline(cin, codigo);
    }

    cout << YELLOW_COLOR << "Ingrese el nombre del nuevo producto: " << RESET_COLOR;
    getline(cin, nombre);
    if (nombre.empty() || any_of(nombre.begin(), nombre.end(), [](char c) { return !isalpha(c) && c != ' '; })) {
        cout << RED_COLOR << "El nombre del producto solo puede contener letras y espacios." << RESET_COLOR << endl;
        cout << YELLOW_COLOR << "Ingrese nuevamente el nombre: " << RESET_COLOR;
        getline(cin, nombre);
    }

    cout << YELLOW_COLOR << "Ingrese la marca del nuevo producto: " << RESET_COLOR;
    getline(cin, marca);
    if (marca.empty() || any_of(marca.begin(), marca.end(), [](char c) { return !isalpha(c) && c != ' '; })) {
        cout << RED_COLOR << "La marca del producto solo puede contener letras y espacios." << RESET_COLOR << endl;
        cout << YELLOW_COLOR << "Ingrese nuevamente la marca: " << RESET_COLOR;
        getline(cin, marca);
    }

    cout << YELLOW_COLOR << "Ingrese el precio del nuevo producto: " << RESET_COLOR;
    while (!(cin >> precio) || precio <= 0) {
        cout << RED_COLOR << "El precio del producto debe ser un número positivo." << RESET_COLOR << endl;
        cin.clear(); // Limpia los bits de error
        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << "Ingrese nuevamente el precio: " << RESET_COLOR;
    }

    cout << YELLOW_COLOR << "Ingrese el modelo del nuevo producto: " << RESET_COLOR;
    cin.ignore();
    getline(cin, modelo);
    if (modelo.empty() || any_of(modelo.begin(), modelo.end(), [](char c) { return !isalnum(c); })) {
        cout << RED_COLOR << "El modelo del producto solo puede contener letras y números." << RESET_COLOR << endl;
        cout << YELLOW_COLOR << "Ingrese nuevamente el modelo: " << RESET_COLOR;
        getline(cin, modelo);   
    }

    cout << YELLOW_COLOR << "Ingrese el ancho (cm) del nuevo producto: " << RESET_COLOR;
    cin >> ancho;
    if (ancho <= 0 || cin.fail()) {
        cout << RED_COLOR << "El ancho del producto debe ser un número positivo." << RESET_COLOR << endl;
        cin.clear();
        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << "Ingrese nuevamente el ancho: " << RESET_COLOR;
        cin.ignore();
        cin >> ancho;
    }

    cout << YELLOW_COLOR << "Ingrese el alto (cm) del nuevo producto: " << RESET_COLOR;
    cin >> alto;
    if (alto <= 0 || cin.fail()) {
        cout << RED_COLOR << "El alto del producto debe ser un número positivo." << RESET_COLOR << endl;
        cin.clear();
        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << "Ingrese nuevamente el alto: " << RESET_COLOR;
        cin.ignore();
        cin >> alto;
    }

    cout << YELLOW_COLOR << "Ingrese el largo (cm) del nuevo producto: " << RESET_COLOR;
    cin >> largo;
    if (largo <= 0 || cin.fail()) {
        cout << RED_COLOR << "El largo del producto debe ser un número positivo." << RESET_COLOR << endl;
        cin.clear();
        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << "Ingrese nuevamente el largo: " << RESET_COLOR;
        cin.ignore();
        cin >> largo;
    }

    cout << YELLOW_COLOR << "Ingrese el peso (Kg) del nuevo producto: " << RESET_COLOR;
    cin >> peso;
    if (peso <= 0 || cin.fail()) {
        cout << RED_COLOR << "El peso del producto debe ser un número positivo." << RESET_COLOR << endl;
        cin.clear();
        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << "Ingrese nuevamente el peso: " << RESET_COLOR;
        cin.ignore();
        cin >> peso;
    }

    cout << YELLOW_COLOR << "Ingrese el material del nuevo producto: " << RESET_COLOR;
    cin.ignore();
    getline(cin, material);
    if (material.empty() || !all_of(material.begin(), material.end(), ::isalnum)) {
        cout << RED_COLOR << "El material del producto solo puede contener letras y números." << RESET_COLOR << endl;
        cout << YELLOW_COLOR << "Ingrese nuevamente el material: " << RESET_COLOR;
        getline(cin, material);
    }

    cout << YELLOW_COLOR << "Ingrese el color del nuevo producto: " << RESET_COLOR;
    getline(cin, color);
    if (color.empty() || !all_of(color.begin(), color.end(), ::isalpha)) {
        cout << RED_COLOR << "El color del producto solo puede contener letras." << RESET_COLOR << endl;
        cout << YELLOW_COLOR << "Ingrese nuevamente el color: " << RESET_COLOR;
        getline(cin, color);        
    }

    cout << YELLOW_COLOR << "Ingrese la garantia (meses) del nuevo producto: " << RESET_COLOR;
    cin >> garantia;
    if (garantia <= 0 || cin.fail()) {
        cout << RED_COLOR << "La garantía del producto debe ser un número entero positivo." << RESET_COLOR << endl;
        cin.clear();
        cin.ignore((std::numeric_limits<streamsize>::max)(), '\n'); // Ignora la entrada incorrecta
        cout << YELLOW_COLOR << "Ingrese nuevamente la garantía: " << RESET_COLOR;
        cin.ignore();
        cin >> garantia;
    }

    PRODUCTO nuevoProducto(codigo, nombre, marca, precio, modelo, ancho, alto, largo, peso, material, color, garantia);
    manager.agregarProducto(nuevoProducto);

    // Mostrar mensaje de éxito
    cout << DOUBLE_SPACE << GREEN_COLOR << "Nuevo producto agregado correctamente." << RESET_COLOR << endl;
}

void updateProductProcedure(GESTION_PRODUCTOS& manager) {
    string codigo;
    double nuevoPrecio;
    string nuevoCodigo;
    int nuevaGarantia;

    // Solicitar al usuario el código del producto a actualizar
    cout << YELLOW_COLOR << "Ingrese el código del producto que desea actualizar: " << RESET_COLOR;
    cin.ignore(); // Limpiar el búfer de entrada antes de getline
    getline(cin, codigo);

    // Verificar si el código del producto existe en el gestor
    if (!manager.existeProducto(codigo)) {
        cout << DOUBLE_SPACE << MAGENTA_COLOR << "El producto con el código ingresado no existe." << RESET_COLOR << endl;
        return; // Salir de la función si el producto no existe
    }

    // Solicitar al usuario los nuevos detalles del producto
    cout << DOUBLE_SPACE << YELLOW_COLOR << "Ingrese el nuevo precio del producto: " << RESET_COLOR;
    cin >> nuevoPrecio;
    cout << YELLOW_COLOR << "Ingrese el nuevo código del producto: " << RESET_COLOR;
    cin.ignore(); // Limpiar el búfer de entrada antes de getline
    getline(cin, nuevoCodigo);
    cout << YELLOW_COLOR << "Ingrese la nueva garantía (meses) del producto: " << RESET_COLOR;
    cin >> nuevaGarantia;

    // Actualizar el producto en el gestor de productos
    manager.actualizarProducto(codigo, nuevoPrecio, nuevoCodigo, nuevaGarantia);

    // Mostrar mensaje de éxito
    cout << DOUBLE_SPACE << GREEN_COLOR << "Producto actualizado correctamente." << endl;
}

void removeProductProcedure(GESTION_PRODUCTOS& manager) {
    string codigo;

    // Solicitar al usuario el código del producto a eliminar
    cout << YELLOW_COLOR << "Ingrese el código del producto que desea eliminar: " << RESET_COLOR;
    cin.ignore(); // Limpiar el búfer de entrada antes de getline
    getline(cin, codigo);

    // Verificar si el producto existe antes de eliminarlo
    if (manager.existeProducto(codigo)) {
        // Eliminar el producto del gestor de productos
        manager.eliminarProducto(codigo);

        // Mostrar mensaje de éxito
        cout << DOUBLE_SPACE << GREEN_COLOR << "Producto eliminado correctamente." << endl;
    }
    else {
        // Mostrar mensaje de error si el producto no existe
        cout << DOUBLE_SPACE << MAGENTA_COLOR << "Error: El producto con código " << codigo << " no existe." << endl;
    }
}

void searchProduct(GESTION_PRODUCTOS& manager) {
    string codigo;

    // Solicitar al usuario el código del producto a buscar
    cout << YELLOW_COLOR << "Ingrese el código del producto que desea buscar: " << RESET_COLOR;
    cin.ignore(); // Limpiar el búfer de entrada antes de getline
    getline(cin, codigo);
    cout << endl;

    // Buscar y mostrar la información del producto
    manager.buscarYMostrarProducto(codigo);
}