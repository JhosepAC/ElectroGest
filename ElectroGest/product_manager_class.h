#pragma once
#include "product_simple_list_class.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <conio.h>

class GESTION_PRODUCTOS {
    LISTA_PRODUCTO listaProductos;

public:

    // Método para ocultar o mostrar el cursor en la consola
    void cargarDesdeArchivo(string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Abrir el archivo total_products.txt
        ifstream file("total_products.txt");

        // Verificar si el archivo se abrió correctamente
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404] << endl;
            return;
        }

        // Variables para almacenar los datos de cada producto
        string line, key, value;
        string nombre, codigo, marca, modelo, material, color;
        double precio, ancho, alto, largo, peso;
        int garantia;

        // Leer el archivo línea por línea
        while (getline(file, line)) {
            // Verificar si la línea es un separador
            if (line == "----------------------------------------") {
                // Verificar si se han leído los datos de un producto completo
                if (!codigo.empty()) {
                    // Al encontrar un separador, creamos el producto y lo añadimos a la lista
                    try {
                        listaProductos.agregarProducto(PRODUCTO(codigo, nombre, marca, precio, modelo, ancho, alto, largo, peso, material, color, garantia));
                    }
                    catch (const invalid_argument& e) {
                        cerr << menuTexts[currentLanguage][213] << e.what() << endl;
                    }
                    catch (const out_of_range& e) {
                        cerr << menuTexts[currentLanguage][213] << e.what() << endl;
                    }
                }
                // Restablecer variables para el próximo producto
                nombre.clear();
                codigo.clear();
                marca.clear();
                modelo.clear();
                material.clear();
                color.clear();
                precio = 0.0;
                ancho = alto = largo = peso = 0.0;
                garantia = 0;
                continue;
            }

            // Separar la línea en clave y valor
            istringstream iss(line);
            getline(iss, key, ':');
            getline(iss, value);
            value.erase(0, value.find_first_not_of(" ")); // Elimina espacios iniciales

            // Asignar el valor a la variable correspondiente
            if (key == menuTexts[currentLanguage][217]) nombre = value;
            // Si la clave es "Código", asignar el valor a la variable correspondiente
            else if (key == menuTexts[currentLanguage][218]) codigo = value;
            // Si la clave es "Marca", asignar el valor a la variable correspondiente
            else if (key == menuTexts[currentLanguage][219]) marca = value;
            // Si la clave es "Precio", asignar el valor a la variable correspondiente
            else if (key == menuTexts[currentLanguage][220]) {
                // Buscar la posición del carácter '/' en la cadena
                size_t pos = value.find_first_of('/');
                if (pos != string::npos) {
                    // Extraer el substring que contiene el valor numérico del precio
                    string precioStr = value.substr(pos + 1);
                    try {
                        // Convertir el substring a double
                        precio = stod(precioStr);
                    }
                    catch (const invalid_argument& e) {
                        cerr << menuTexts[currentLanguage][214] << e.what() << endl;
                    }
                    catch (const out_of_range& e) {
                        cerr << menuTexts[currentLanguage][215] << e.what() << endl;
                    }
                }
                else {
                    cerr << menuTexts[currentLanguage][216] << value << endl;
                }
            }
            else if (key == menuTexts[currentLanguage][221]) modelo = value;
            else if (key == menuTexts[currentLanguage][222]) {
                try {
                    ancho = stod(value);
                }
                catch (const invalid_argument& e) {
                    cerr << menuTexts[currentLanguage][223] << e.what() << endl;
                }
                catch (const out_of_range& e) {
                    cerr << menuTexts[currentLanguage][224] << e.what() << endl;
                }
            }
            else if (key == menuTexts[currentLanguage][225]) {
                try {
                    alto = stod(value);
                }
                catch (const invalid_argument& e) {
                    cerr << menuTexts[currentLanguage][226] << e.what() << endl;
                }
                catch (const out_of_range& e) {
                    cerr << menuTexts[currentLanguage][227] << e.what() << endl;
                }
            }
            else if (key == menuTexts[currentLanguage][228]) {
                try {
                    largo = stod(value);
                }
                catch (const invalid_argument& e) {
                    cerr << menuTexts[currentLanguage][229] << e.what() << endl;
                }
                catch (const out_of_range& e) {
                    cerr << menuTexts[currentLanguage][230] << e.what() << endl;
                }
            }
            else if (key == menuTexts[currentLanguage][231]) {
                try {
                    peso = stod(value);
                }
                catch (const invalid_argument& e) {
                    cerr << menuTexts[currentLanguage][232] << e.what() << endl;
                }
                catch (const out_of_range& e) {
                    cerr << menuTexts[currentLanguage][233] << e.what() << endl;
                }
            }
            else if (key == menuTexts[currentLanguage][234]) material = value;
            else if (key == menuTexts[currentLanguage][235]) color = value;
            else if (key == menuTexts[currentLanguage][236]) {
                try {
                    garantia = stoi(value);
                }
                catch (const invalid_argument& e) {
                    cerr << menuTexts[currentLanguage][237] << e.what() << endl;
                }
                catch (const out_of_range& e) {
                    cerr << menuTexts[currentLanguage][238] << e.what() << endl;
                }
            }
        }
        file.close();
    }

    // Método para guardar el catálogo de productos en un archivo
    void guardarEnArchivo(string _currentLenguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLenguage;

        ofstream file("total_products.txt");
        listaProductos.mostrarCatalogoArchivo(_currentLenguage); // Elimina el argumento file de aquí
        file.close();
    }

public:

    // Constructor predeterminado
    GESTION_PRODUCTOS() {}

    // Método para verificar si un producto existe dado su código
    bool hasCodigo(const string& codigo) const {
        // Obtener el primer nodo de la lista de productos
        NODO_PRODUCTO* actual = listaProductos.obtenerPrimero();

        // Recorrer la lista de productos y verificar si existe un producto con el código especificado
        while (actual != nullptr) {
            if (actual->producto.getCodigo() == codigo) {
                return true; // Si se encuentra el producto con el código especificado, retornamos true
            }
            actual = actual->siguiente; // Pasar al siguiente nodo de la lista de productos
        }
        return false; // Si no se encuentra el producto con el código especificado, retornamos false
    }

    // Método para buscar un producto por su código
    NODO_PRODUCTO* buscarProducto(const string& codigo) {
        return listaProductos.buscarProducto(codigo); // Devuelve el nodo del producto con el código especificado
    }

    // Método para verificar si un producto existe dado su código
    bool existeProducto(const string& codigo) const {

        // Obtener el primer nodo de la lista de productos
        NODO_PRODUCTO* actual = listaProductos.obtenerPrimero();

        // Recorrer la lista de productos y verificar si existe un producto con el código especificado
        while (actual != nullptr) {
            if (actual->producto.getCodigo() == codigo) {
                return true; // Si se encuentra el producto, retornamos true
            }
            actual = actual->siguiente; // Pasar al siguiente nodo de la lista de productos
        }
        return false; // Si no se encuentra el producto, retornamos false
    }

    // Método para mostrar todos los productos en el catálogo
    void mostrarTodosLosProductos(string _currentLenguage) const {
        
        // Idioma predeterminado
        string currentLanguage = _currentLenguage;

        listaProductos.mostrarCatalogo(_currentLenguage);
    }

    // Método para agregar un producto al catálogo
    void agregarProducto(PRODUCTO producto, string _currentLenguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLenguage;

        listaProductos.agregarProducto(producto);
        guardarEnArchivo(_currentLenguage);
    }

    // Método para eliminar un producto del catálogo
    void eliminarProducto(const string& codigo, string _currentLenguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLenguage;

        listaProductos.eliminarProducto(codigo);
        guardarEnArchivo(_currentLenguage);
    }

    // Método para actualizar un producto en el catálogo
    void actualizarProducto(const string& codigo, double nuevoPrecio, const string& nuevoCodigo, int nuevaGarantia, string _currentLenguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLenguage;

        listaProductos.actualizarProducto(codigo, nuevoPrecio, nuevoCodigo, nuevaGarantia);
        guardarEnArchivo(_currentLenguage);
    }

    // Método para buscar un producto por su nombre
    void buscarYMostrarProducto(const string& codigo, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        // Buscar el producto en el catálogo
        NODO_PRODUCTO* producto = listaProductos.buscarProducto(codigo);
        ShowConsoleCursor(false); // Oculta el cursor

        // Mostrar la información del producto si se encuentra
        if (producto != nullptr) {
            producto->producto.mostrarInformacion();

            cout << DOUBLE_SPACE << GRAY_COLOR << menuTexts[currentLanguage][51]; // Presione cualquier tecla para continuar
            _getch();
        }
        else {

            cout << MAGENTA_COLOR << menuTexts[currentLanguage][239] << endl; // No se encontró ningún producto con el código especificado
            _sleep(1500); // Esperar 1.5 segundos antes de limpiar la pantalla)
        }
    }

    // Método para buscar un producto por su nombre
    void buscarProductoPorNombre(const string& nombre, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        bool encontrado = false;

        // Abrir el archivo total_products.txt
        ifstream file("total_products.txt");

        // Verificar si el archivo se abrió correctamente
        if (!file.is_open()) {
            cerr << menuTexts[currentLanguage][404] << endl; // No se pudo abrir el archivo total_products.txt
            return;
        }

        string line;

        // Leer el archivo línea por línea
        while (getline(file, line)) {
            // Verificar si la línea contiene el texto "Nombre del producto"
            if (line.find(menuTexts[currentLanguage][240]) != string::npos) {
                // Extraer el nombre del producto de la línea
                string nombreProducto = line.substr(line.find(":") + 1);
                // Eliminar espacios en blanco del principio del nombre
                nombreProducto.erase(0, nombreProducto.find_first_not_of(" \t\r\n"));
                // Eliminar espacios en blanco del final del nombre
                nombreProducto.erase(nombreProducto.find_last_not_of(" \t\r\n") + 1);

                // Convertir ambos nombres a minúsculas antes de comparar
                transform(nombreProducto.begin(), nombreProducto.end(), nombreProducto.begin(), ::tolower);
                string nombreMinusculas = nombre;
                // Eliminar espacios en blanco del principio y final del nombre
                transform(nombreMinusculas.begin(), nombreMinusculas.end(), nombreMinusculas.begin(), ::tolower);

                // Verificar si el nombre del producto coincide con el nombre especificado
                if (nombreProducto.compare(nombreMinusculas) == 0) {
                    // Si se encuentra el producto, mostrar su información
                    encontrado = true;
                    cout << endl;
                    // Mostrar la información del producto
                    for (int i = 0; i < 12; ++i) {
                        getline(file, line);
                        string::size_type pos = line.find(":"); // Verificar si la línea contiene un carácter ':'
                        // Verificar si la línea contiene un carácter ':'
                        if (pos != string::npos) {
                            string label = line.substr(0, pos); // Extraer la etiqueta de la línea
                            string value = line.substr(pos + 1); // Extraer el valor de la línea
                            cout << BLUE_COLOR << label << RESET_COLOR;
                            cout << value << endl;
                        }
                        else {
                            cout << line << endl;
                        }
                    }
                    cout << YELLOW_COLOR << "----------------------------------------" << RESET_COLOR << endl;
                }
            }
        }

        file.close();

        // Mostrar un mensaje si no se encontró ningún producto con el nombre especificado
        if (!encontrado) {
            cout << MAGENTA_COLOR << menuTexts[currentLanguage][241] << nombre << "'." << endl << RESET_COLOR; // No se encontró ningún producto con el nombre 'nombre'.
        }
    }

    void filtrarPorPrecio(GESTION_PRODUCTOS& productManager, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        double precioMinimo, precioMaximo;
        cout << YELLOW_COLOR << menuTexts[currentLanguage][242] << RESET_COLOR; // Introduzca el precio mínimo:
        cin >> precioMinimo;
        cout << YELLOW_COLOR << menuTexts[currentLanguage][243] << RESET_COLOR; // Introduzca el precio máximo:
        cin >> precioMaximo;

        // Crear una nueva lista de productos filtrados por precio
        LISTA_PRODUCTO productosFiltrados;

        // Recorrer todos los productos en el catálogo y agregar aquellos que estén dentro del rango de precios especificado
        for (NODO_PRODUCTO* actual = productManager.listaProductos.obtenerPrimero(); actual != nullptr; actual = actual->siguiente) {
            double precioProducto = actual->producto.getPrecio();
            // Verificar si el precio del producto está dentro del rango especificado
            if (precioProducto >= precioMinimo && precioProducto <= precioMaximo) {
                // Agregar el producto a la lista de productos filtrados
                productosFiltrados.agregarProducto(actual->producto);
            }
        }

        // Mostrar la lista de productos filtrados
        if (productosFiltrados.estaVacia()) {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][244] << endl; // No se encontraron productos que coincidan con los criterios de búsqueda.
        }
        else {
            cout << DOUBLE_SPACE << CYAN_COLOR << menuTexts[currentLanguage][245] << endl; // Se encontraron los siguientes productos que coinciden con los criterios de búsqueda:
            productosFiltrados.mostrarCatalogo(_currentLanguage);
        }
    }

    // Método para filtrar productos por color
    void filtrarPorColor(GESTION_PRODUCTOS& productManager, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        string color;
        cout << YELLOW_COLOR << menuTexts[currentLanguage][246] << RESET_COLOR; // Introduzca el color
        cin >> color;

        // Crear una nueva lista de productos filtrados por color
        LISTA_PRODUCTO productosFiltrados;

        // Obtener el primer nodo de la lista de productos
        NODO_PRODUCTO* actual = productManager.listaProductos.obtenerPrimero();

        // Recorrer todos los productos en el catálogo y agregar aquellos que coincidan con el color especificado
        while (actual != nullptr) {
            // Verificar si el color del producto coincide con el color especificado
            if (actual->producto.getColor() == color) {
                // Agregar el producto a la lista de productos filtrados
                productosFiltrados.agregarProducto(actual->producto);
            }
            actual = actual->siguiente; // Pasar al siguiente nodo de la lista de productos
        }

        // Mostrar la lista de productos filtrados
        if (productosFiltrados.estaVacia()) {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][247] << endl; // No se encontraron productos que coincidan con los criterios de búsqueda.
        }
        else {
            cout << DOUBLE_SPACE << CYAN_COLOR << menuTexts[currentLanguage][248] << endl; // Se encontraron los siguientes productos que coinciden con los criterios de búsqueda:
            productosFiltrados.mostrarCatalogo(_currentLanguage);
        }
    }


    // Método para filtrar productos por marca
    void filtrarPorMarca(GESTION_PRODUCTOS& productManager, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        string marca;
        cout << YELLOW_COLOR << menuTexts[currentLanguage][249] << RESET_COLOR; // Introduzca la marca
        cin >> marca;

        // Crear una nueva lista de productos filtrados por marca
        LISTA_PRODUCTO productosFiltrados;

        // Obtener el primer nodo de la lista de productos
        NODO_PRODUCTO* actual = productManager.listaProductos.obtenerPrimero();

        // Recorrer todos los productos en el catálogo y agregar aquellos que coincidan con la marca especificada
        while (actual != nullptr) {
            // Verificar si la marca del producto coincide con la marca especificada
            if (actual->producto.getMarca() == marca) {
                // Agregar el producto a la lista de productos filtrados
                productosFiltrados.agregarProducto(actual->producto);
            }
            actual = actual->siguiente;
        }

        // Mostrar la lista de productos filtrados
        if (productosFiltrados.estaVacia()) {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][250] << endl; // No se encontraron productos que coincidan con los criterios de búsqueda.
        }
        else {
            cout << DOUBLE_SPACE << CYAN_COLOR << menuTexts[currentLanguage][251] << endl; // Se encontraron los siguientes productos que coinciden con los criterios de búsqueda:
            productosFiltrados.mostrarCatalogo(_currentLanguage);
        }
    }

    // Método para ordenar productos por precio de forma ascendente
    void ordenarProductosPorPrecioAscendente(string _currentLenguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLenguage;

        // Convertir la lista de productos a un vector para facilitar el ordenamiento
        vector<PRODUCTO> productosVector;

        // Recorrer la lista de productos y agregar cada producto al vector
        for (NODO_PRODUCTO* actual = listaProductos.obtenerPrimero(); actual != nullptr; actual = actual->siguiente) {
            productosVector.push_back(actual->producto); // Agregar el producto al vector
        }

        // Ordenar el vector de productos por precio de forma ascendente
        sort(productosVector.begin(), productosVector.end(), [](const PRODUCTO& a, const PRODUCTO& b) {
            return a.getPrecio() < b.getPrecio();
            });

        // Mostrar los productos ordenados
        cout << CYAN_COLOR << menuTexts[currentLanguage][252] << DOUBLE_SPACE;

        // Recorrer el vector de productos y mostrar la información de cada producto
        for (const auto& producto : productosVector) {
            producto.mostrarInformacion();
            cout << endl;
        }
    }

    // Método para ordenar productos por precio de forma descendente
    void ordenarProductosPorPrecioDescendente(string _currentLenguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLenguage;

        // Convertir la lista de productos a un vector para facilitar el ordenamiento
        vector<PRODUCTO> productosVector;

        // Recorrer la lista de productos y agregar cada producto al vector
        for (NODO_PRODUCTO* actual = listaProductos.obtenerPrimero(); actual != nullptr; actual = actual->siguiente) {
            productosVector.push_back(actual->producto); // Agregar el producto al vector
        }

        // Ordenar el vector de productos por precio de forma descendente
        sort(productosVector.begin(), productosVector.end(), [](const PRODUCTO& a, const PRODUCTO& b) {
            return a.getPrecio() > b.getPrecio(); // Ordenar de forma descendente
            });

        cout << CYAN_COLOR << menuTexts[currentLanguage][253] << DOUBLE_SPACE; // Productos ordenados por precio de forma descendente:

        // Recorrer el vector de productos y mostrar la información de cada producto
        for (const auto& producto : productosVector) {
            producto.mostrarInformacion();
            cout << endl;
        }
    }

};