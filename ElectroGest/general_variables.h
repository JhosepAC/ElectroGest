#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <map>
#include <limits>
#include <cctype>

using namespace std;

// Definición de constantes para códigos de color ANSI
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

// Definición de textos en diferentes idiomas
map<string, map<int, string>> menuTexts = {
    {"espanol", {
        {1, "     ¡Bienvenido a ElectroGest!"},
        {2, "Iniciar sesión como vendedor"},
        {3, "Iniciar sesión como cliente"},
        {4, "Salir"},
        {5, "Ingrese una opción: "},
        {6, "Entrada no válida, por favor ingrese un número."},
        {7, "Opción no válida, por favor intente nuevamente."},
        {8, "Cambiar idioma"},
        {9, "¡Bienvenido, vendedor!"},
        {10, "Ingrese sus datos para iniciar sesión"},
        {11, "Usuario: "},
        {12, "Contraseña: "},
        {13, "Usuario o contraseña incorrectos. Por favor, inténtelo de nuevo."},
        {14, "Bienvenido, "},
        {15, "!"},
        {16, "Gestionar productos"},
        {17, "Gestionar inventario"},
        {18, "Gestionar proveedores"},
        {19, "Gestionar pedidos"},
        {20, "Gestionar clientes"},
        {21, "¡Bienvenido comprador!"},
        {22, "Por favor, complete el siguiente formulario para registrarse"},
        {23, "Nombre: "},
        {24, "Apellido: "},
        {25, "Correo electrónico: "},
        {26, "Confirmar contraseña: "},
        {27, "Las contraseñas no coinciden, intente de nuevo."},
        {28, "Dirección: "},
        {29, "Teléfono: "},
        {30, "El teléfono debe tener exactamente 9 dígitos. Intente de nuevo."},
        {31, "Fecha de nacimiento: (DD/MM/AAAA): "},
        {32, "Sexo (M, F): "},
        {33, "Ingrese un sexo válido (M, F). Intente de nuevo."},
        {34, "Dirección de correo electrónico no válida"},
        {35, "Fecha de nacimiento no válida"},
        {36, "Nombre no permitido."},
        {37, "Ingrese un nombre válido: "},
        {38, "Apellido no permitido."},
        {39, "Ingrese un apellido válido: "},
        {36, "Nombre no válido."},
        {37, "Ingrese un nombre válido: "},
        {38, "Apellido no válido."},
        {39, "Ingrese un apellido válido: "},
        {40, "Debe ingresar una contraseña. Por favor, inténtelo de nuevo."},
        {41, "Las contraseñas no coinciden. Por favor, inténtelo de nuevo."},
        {42, "Número de teléfono ya registrado."},
        {43, "¡Bienvenido, cliente!"},
        {44, "Ingrese sus datos para iniciar sesión."},
        {45, "Inicio de sesión exitoso."},
        {46, "Error: No se pudo abrir el archivo de registro"},
        {47, "Correo electrónico o contraseña incorrectos. Por favor, inténtelo de nuevo."},
        {48, "Registrarse"},
        {49, "Iniciar sesión"},
        {50, "Volver"},
        {51, "Presiona cualquier tecla para continuar..."},
        {52, "Ver cátalogo de productos"},
        {53, "Realizar pedido"},
        {54, "Ver estado de pedidos"},
        {55, "Ordenar de menor a mayor"},
        {56, "Ordenar de mayor a menor"},
        {57, "Ingrese el término de búsqueda (nombre o apellido): "},
        {58, "Buscar clientes: "},
        {59, "No hay ningún cliente registrado."},
        {60, "Ingrese el correo electrónico del cliente a eliminar: "},
        {61, "Eliminar cliente: "},
        {62, "GESTIÓN DE CLIENTES"},
        {63, "Ver lista de clientes"},
        {64, "Eliminar cliente"},
        {65, "Buscar cliente"},
        {66, "Lista de clientes:"},
        {67, "¡Registro completado exitosamente!"},
        {68, "CÁTALOGO DE PRODUCTOS"},
        {69, "Ver productos"},
        {70, "Filtrar productos"},
        {71, "Buscar productos por nombres"},
        {72, "Ingresa el nombre del producto a buscar: "},
        {73, "Índice de pedido inválido."},
        {74, "No hay suficiente stock para procesar este pedido."},
        {75, "Pedido procesado correctamente."},
        {76, "Ingrese el índice del pedido a procesar: "},
        {77, "GESTIÓN DE PEDIDOS"},
        {78, "Ver pedidos pendientes"},
        {79, "Ver pedidos procesados"},
        {80, "Procesar pedido"},
        {81, "Eliminar pedidos"},
        {82, "Historial de pedidos"},
        {83, "FILTRAR PRODUCTOS POR CATEGORÍA"},
        {84, "Filtrar por precio"},
        {85, "Filtrar por color"},
        {86, "Filtrar por marca"},
        {87, "GESTIÓN DE PRODUCTOS"},
        {88, "Catálogo de productos"},
        {89, "Agregar nuevo producto"},
        {90, "Actualizar producto"},
        {91, "Eliminar producto"},
        {92, "Buscar producto"},
        {93, "¿Desea ordenar los productos por precio?"},
        {94, "Sí"},
        {95, "No"},
        {96, "El carrito está vacío. No se puede realizar el proceso."},
        {97, "Pedido cancelado. El carrito ha sido vaciado."},
        {98, "Pedido confirmado correctamente."},
        {99, "No hay suficiente stock de este producto."},
        {100, "Producto agregado al carrito correctamente."},
        {101, "Ingrese nuevamente la cantidad a agregar: "},
        {102, "La cantidad debe ser un número positivo."},
        {103, "Debe ingresar un número válido para la cantidad." },
        {104, "Ingrese la cantidad a agregar: " },
        {105, "El producto no existe en el inventario." },
        {106, "Ingrese el código del producto a agregar: " },
        {107, "REALIZAR PEDIDO" },
        {108, "Agregar producto al carrrito" },
        {109, "Ver carrito" },
        {110, "Confirmar pedido" },
        {111, "Cancelar pedido" },
        {112, "GESTIÓN DE INVENTARIO" },
        {113, "Ver inventario" },
        {114, "Añadir stock" },
        {115, "Retirar stock" },
        {116, "Historial de movimientos" },
        {117, "GESTIÓN DE PROVEEDORES" },
        {118, "Ver lista de proveedores" },
        {119, "Agregar nuevo proveedor" },
        {120, "Actualizar información de proveedor" },
        {121, "Eliminar proveedor" },
        {122, "Buscar proveedor" },
        {123, "No se cuenta con proveedores por el momento." },
        {124, "Ingrese el nombre del proveedor que desea buscar: " },
        {125, "Ingrese el código del producto que desea agregar al inventario: " },
        {126, "Ingrese la cantidad de stock a añadir: " },
        {127, "Debe ingresar un número válido para la cantidad de stock." },
        {128, "La cantidad de stock debe ser un número positivo." },
        {129, "Ingrese nuevamente la cantidad de stock: " },
        {130, "Stock añadido exitosamente." },
        {131, "El producto no se encuentra en la lista de productos." },
        {132, "Ingrese el código del producto del cual desea retirar stock: " },
        {133, "Ingrese la cantidad de stock a retirar: " },
        {134, "Debe ingresar un número válido para la cantidad de stock." },
        {135, "Ingrese nuevamente la cantidad de stock: " },
        {136, "Stock retirado exitosamente." },
        {137, "El producto no se encuentra en la lista de productos." },
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
        {43, "Welcome, client!"},
		{44, "Enter your data to log in."},
		{45, "Login successful."},
		{46, "Error: Could not open log file"},
		{47, "Incorrect email or password. Please try again."},
        {48, "Sign up"},
		{49, "Log in"},
        {50, "Back"},
        {51, "Press any key to continue..."},
        {52, "View product catalog"},
        {53, "Place order"},
        {54, "View order status"},
		{55, "Sort from lowest to highest"},
		{56, "Sort from highest to lowest"},
		{57, "Enter search term (name or last name): "},
		{58, "Search clients: "},
		{59, "No clients registered."},
        {60, "Enter the email of the client to delete: "},
		{61, "Delete client: "},
		{62, "CLIENT MANAGEMENT"},
		{63, "View client list"},
		{64, "Delete client"},
		{65, "Search client"},
		{66, "Client list:"},
        {67, "Registration completed successfully!"},
		{68, "PRODUCT CATALOG"},
		{69, "View products"},
		{70, "Filter products"},
		{71, "Search products by name"},
		{72, "Enter the name of the product to search: "},
		{73, "Invalid order index."},
		{74, "There is not enough stock to process this order."},
		{75, "Order processed successfully."},
		{76, "Enter the index of the order to process: "},
		{77, "ORDER MANAGEMENT"},
		{78, "View pending orders"},
		{79, "View processed orders"},
		{80, "Process order"},
		{81, "Delete orders"},
		{82, "Order history"},
		{83, "FILTER PRODUCTS BY CATEGORY"},
		{84, "Filter by price"},
		{85, "Filter by color"},
		{86, "Filter by brand"},
		{87, "PRODUCT MANAGEMENT"},
		{88, "Product catalog"},
		{89, "Add new product"},
		{90, "Update product"},
		{91, "Delete product"},
		{92, "Search product"},
		{93, "Do you want to order the products by price?"},
		{94, "Yes"},
		{95, "No"},
		{96, "The cart is empty. The process cannot be completed."},
		{97, "Order canceled. The cart has been emptied."},
		{98, "Order confirmed successfully."},
		{99, "There is not enough stock of this product."},
		{100, "Product added to cart successfully."},
		{101, "Enter the quantity to add again: "},
		{102, "The quantity must be a positive number."},
		{103, "You must enter a valid number for the quantity." },
		{104, "Enter the quantity to add: " },
		{105, "The product does not exist in the inventory." },
		{106, "Enter the product code to add: " },
		{107, "PLACE ORDER" },
		{108, "Add product to cart" },
		{109, "View cart" },
        {110, "Confirm order" },
		{111, "Cancel order" },
		{112, "INVENTORY MANAGEMENT" },
		{113, "View inventory" },
		{114, "Add stock" },
		{115, "Remove stock" },
		{116, "Movement history" },
		{117, "SUPPLIER MANAGEMENT" },
		{118, "View supplier list" },
		{119, "Add new supplier" },
		{120, "Update supplier information" },
		{121, "Delete supplier" },
		{122, "Search supplier" },
		{123, "There are no suppliers available at the moment." },
		{124, "Enter the name of the supplier you want to search: " },
		{125, "Enter the product code you want to add to the inventory: " },
		{126, "Enter the amount of stock to add: " },
		{127, "You must enter a valid number for the stock amount." },
		{128, "The stock amount must be a positive number." },
		{129, "Enter the stock amount again: " },
		{130, "Stock added successfully." },
		{131, "The product is not in the list of products." },
		{132, "Enter the product code from which you want to remove stock: " },
		{133, "Enter the amount of stock to remove: " },
		{134, "You must enter a valid number for the stock amount." },
		{135, "Enter the stock amount again: " },
		{136, "Stock removed successfully." },
		{137, "The product is not in the list of products." },
		{404, "Error opening file" }
    }}
};

// Función para cambiar el idioma del menú
void changeLanguage(string& currentLanguage) {
    string language;
    cout << DOUBLE_SPACE << YELLOW_COLOR << "Select language (espanol/english): " << RESET_COLOR;
    cin >> language;
    // Verificar si el idioma seleccionado está disponible
    if (menuTexts.find(language) == menuTexts.end()) {
        cout << DOUBLE_SPACE << MAGENTA_COLOR << "Invalid language choice.";
        Sleep(1500);
    }
    else {
        // Cambiar el idioma
        currentLanguage = language;
    }
}//sex mod it's active now

// Función para verificar si una cadena contiene solo letras
bool contieneSoloLetras(const string& str) {
    for (char c : str) {
        if (!(isalpha(c) || c == '6' || c == ' ')) { // Permitir letras, espacio y el número 6
            return false;
        }
    }
    return true;
}

// Función para verificar si una cadena contiene solo letras
bool contieneSoloLetrasApellido(const string& str) {
    for (char c : str) {
        if (!(isalpha(c) || c == ' ')) { // Permitir letras y espacio
            return false;
        }
    }
    return true;
}