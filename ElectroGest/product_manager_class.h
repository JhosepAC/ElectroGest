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

    void cargarDesdeArchivo() {
        std::ifstream file("total_products.txt");
        if (!file.is_open()) {
            std::cerr << "Error al abrir el archivo total_products.txt" << std::endl;
            return;
        }

        std::string line, key, value;
        std::string nombre, codigo, marca, modelo, material, color;
        double precio, ancho, alto, largo, peso;
        int garantia;

        while (std::getline(file, line)) {
            if (line == "----------------------------------------") {
                if (!codigo.empty()) {
                    // Al encontrar un separador, creamos el producto y lo añadimos a la lista
                    try {
                        listaProductos.agregarProducto(PRODUCTO(codigo, nombre, marca, precio, modelo, ancho, alto, largo, peso, material, color, garantia));
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "Error al agregar el producto: " << e.what() << std::endl;
                    }
                    catch (const std::out_of_range& e) {
                        std::cerr << "Error al agregar el producto: " << e.what() << std::endl;
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

            std::istringstream iss(line);
            std::getline(iss, key, ':');
            std::getline(iss, value);
            value.erase(0, value.find_first_not_of(" ")); // Elimina espacios iniciales

            if (key == "Nombre") nombre = value;
            else if (key == "Codigo") codigo = value;
            else if (key == "Marca") marca = value;
            else if (key == "Precio") {
                // Buscar la posición del carácter '/' en la cadena
                size_t pos = value.find_first_of('/');
                if (pos != std::string::npos) {
                    // Extraer el substring que contiene el valor numérico del precio
                    std::string precioStr = value.substr(pos + 1);
                    try {
                        // Convertir el substring a double
                        precio = std::stod(precioStr);
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "Error de conversión de precio: " << e.what() << std::endl;
                    }
                    catch (const std::out_of_range& e) {
                        std::cerr << "Error de rango de precio: " << e.what() << std::endl;
                    }
                }
                else {
                    std::cerr << "Formato de precio no válido: " << value << std::endl;
                }
            }
            else if (key == "Modelo") modelo = value;
            else if (key == "Ancho (cm)") {
                try {
                    ancho = std::stod(value);
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error de conversión de ancho: " << e.what() << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Error de rango de ancho: " << e.what() << std::endl;
                }
            }
            else if (key == "Alto (cm)") {
                try {
                    alto = std::stod(value);
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error de conversión de alto: " << e.what() << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Error de rango de alto: " << e.what() << std::endl;
                }
            }
            else if (key == "Largo (cm)") {
                try {
                    largo = std::stod(value);
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error de conversión de largo: " << e.what() << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Error de rango de largo: " << e.what() << std::endl;
                }
            }
            else if (key == "Peso (Kg)") {
                try {
                    peso = std::stod(value);
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error de conversión de peso: " << e.what() << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Error de rango de peso: " << e.what() << std::endl;
                }
            }
            else if (key == "Material") material = value;
            else if (key == "Color") color = value;
            else if (key == "Garantia (meses)") {
                try {
                    garantia = std::stoi(value);
                }
                catch (const std::invalid_argument& e) {
                    std::cerr << "Error de conversión de garantía: " << e.what() << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Error de rango de garantía: " << e.what() << std::endl;
                }
            }
        }
        file.close();
    }

    void guardarEnArchivo() {
        std::ofstream file("total_products.txt");
        listaProductos.mostrarCatalogoArchivo(); // Elimina el argumento file de aquí
        file.close();
    }

public:
    GESTION_PRODUCTOS() {
        cargarDesdeArchivo();
    }

    bool hasCodigo(const std::string& codigo) const {
        NODO_PRODUCTO* actual = listaProductos.obtenerPrimero();
        while (actual != nullptr) {
            if (actual->producto.getCodigo() == codigo) {
                return true; // Si se encuentra el producto con el código especificado, retornamos true
            }
            actual = actual->siguiente;
        }
        return false; // Si no se encuentra el producto con el código especificado, retornamos false
    }

    NODO_PRODUCTO* buscarProducto(const std::string& codigo) {
        return listaProductos.buscarProducto(codigo);
    }

    // Método para verificar si un producto existe dado su código
    bool existeProducto(const std::string& codigo) const {
        NODO_PRODUCTO* actual = listaProductos.obtenerPrimero();
        while (actual != nullptr) {
            if (actual->producto.getCodigo() == codigo) {
                return true; // Si se encuentra el producto, retornamos true
            }
            actual = actual->siguiente;
        }
        return false; // Si no se encuentra el producto, retornamos false
    }

    void mostrarTodosLosProductos() const {
        listaProductos.mostrarCatalogo();
    }

    void agregarProducto(PRODUCTO producto) {
        listaProductos.agregarProducto(producto);
        guardarEnArchivo();
    }

    void eliminarProducto(const std::string& codigo) {
        listaProductos.eliminarProducto(codigo);
        guardarEnArchivo();
    }

    void actualizarProducto(const std::string& codigo, double nuevoPrecio, const std::string& nuevoCodigo, int nuevaGarantia) {
        listaProductos.actualizarProducto(codigo, nuevoPrecio, nuevoCodigo, nuevaGarantia);
        guardarEnArchivo();
    }

    void buscarYMostrarProducto(const std::string& codigo) {
        NODO_PRODUCTO* producto = listaProductos.buscarProducto(codigo);
        ShowConsoleCursor(false); // Oculta el cursor
        if (producto != nullptr) {
            producto->producto.mostrarInformacion();

            cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
            _getch();
        }
        else {

            std::cout << MAGENTA_COLOR << "Producto no encontrado." << std::endl;
            _sleep(1500); // Esperar 1.5 segundos antes de limpiar la pantalla)
        }
    }

    void buscarProductoPorNombre(const std::string& nombre) {
        bool encontrado = false;
        std::ifstream file("total_products.txt");

        if (!file.is_open()) {
            std::cerr << "Error al abrir el archivo total_products.txt" << std::endl;
            return;
        }

        std::string line;
        while (getline(file, line)) {
            if (line.find("Nombre:") != std::string::npos) {
                std::string nombreProducto = line.substr(line.find(":") + 1);
                // Eliminar espacios en blanco del principio y final del nombre
                nombreProducto.erase(0, nombreProducto.find_first_not_of(" \t\r\n"));
                nombreProducto.erase(nombreProducto.find_last_not_of(" \t\r\n") + 1);

                // Convertir ambos nombres a minúsculas antes de comparar
                std::transform(nombreProducto.begin(), nombreProducto.end(), nombreProducto.begin(), ::tolower);
                std::string nombreMinusculas = nombre;
                std::transform(nombreMinusculas.begin(), nombreMinusculas.end(), nombreMinusculas.begin(), ::tolower);

                // Verificar si el nombre del producto contiene la cadena ingresada
                if (nombreProducto.find(nombreMinusculas) != std::string::npos) {
                    // Si se encuentra el producto, mostrar su información
                    encontrado = true;
                    std::cout << YELLOW_COLOR << "Producto encontrado: " << RESET_COLOR << nombreProducto << std::endl;
                    for (int i = 0; i < 12; ++i) {
                        if (!getline(file, line)) break; // Asegurar que no se lea más allá del final del archivo
                        std::string::size_type pos = line.find(":");
                        if (pos != std::string::npos) {
                            std::string label = line.substr(0, pos);
                            std::string value = line.substr(pos + 1);
                            std::cout << BLUE_COLOR << label << RESET_COLOR << value << std::endl;
                        }
                        else {
                            std::cout << line << std::endl;
                        }
                    }
                    std::cout << YELLOW_COLOR << "----------------------------------------" << RESET_COLOR << std::endl;
                }
            }
        }

        file.close();

        if (!encontrado) {
            ShowConsoleCursor(false); // Oculta el cursor
            std::cout << MAGENTA_COLOR << "No se encontraron productos con el nombre '" << nombre << "'." << std::endl << RESET_COLOR;
            Sleep(1500); // Esperar 1.5 segundos antes de limpiar la pantalla
            system("cls");
        }
        else {
            ShowConsoleCursor(false); // Oculta el cursor
            std::cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
            _getch();
            system("cls");
        }
    }

    void filtrarPorPrecio(GESTION_PRODUCTOS& productManager) {
        double precioMinimo, precioMaximo;
        cout << YELLOW_COLOR << "Ingrese el precio mínimo: " << RESET_COLOR;
        cin >> precioMinimo;
        cout << YELLOW_COLOR << "Ingrese el precio máximo: " << RESET_COLOR;
        cin >> precioMaximo;

        // Crear una nueva lista de productos filtrados por precio
        LISTA_PRODUCTO productosFiltrados;

        // Recorrer todos los productos en el catálogo y agregar aquellos que estén dentro del rango de precios especificado
        for (NODO_PRODUCTO* actual = productManager.listaProductos.obtenerPrimero(); actual != nullptr; actual = actual->siguiente) {
            double precioProducto = actual->producto.getPrecio();
            if (precioProducto >= precioMinimo && precioProducto <= precioMaximo) {
                // Agregar el producto a la lista de productos filtrados
                productosFiltrados.agregarProducto(actual->producto);
            }
        }

        // Mostrar la lista de productos filtrados
        if (productosFiltrados.estaVacia()) {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se encontraron productos dentro del rango de precios especificado." << endl;
            Sleep(1500); // Esperar 1.5 segundos antes de limpiar la pantalla
            system("cls");
        }
        else {
            cout << DOUBLE_SPACE << CYAN_COLOR << "Productos dentro del rango de precios especificado:" << endl;
            productosFiltrados.mostrarCatalogo();

            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
            _getch();
            system("cls");
        }


    }

    void filtrarPorColor(GESTION_PRODUCTOS& productManager) {
        string color;
        cout << YELLOW_COLOR << "Ingrese el color por el que desea filtrar: " << RESET_COLOR;
        cin >> color;

        // Convertir el color ingresado a minúsculas para comparación sin distinción de mayúsculas y minúsculas
        transform(color.begin(), color.end(), color.begin(), ::tolower);

        // Crear una nueva lista de productos filtrados por color
        LISTA_PRODUCTO productosFiltrados;

        // Recorrer todos los productos en el catálogo y agregar aquellos que coincidan con el color especificado
        NODO_PRODUCTO* actual = productManager.listaProductos.obtenerPrimero();
        while (actual != nullptr) {
            string colorProducto = actual->producto.getColor();
            // Convertir el color del producto a minúsculas para comparación sin distinción de mayúsculas y minúsculas
            transform(colorProducto.begin(), colorProducto.end(), colorProducto.begin(), ::tolower);

            // Verificar si el color del producto contiene la cadena ingresada o si es similar
            if (colorProducto.find(color) != string::npos) {
                // Agregar el producto a la lista de productos filtrados
                productosFiltrados.agregarProducto(actual->producto);
            }
            actual = actual->siguiente;
        }

        // Mostrar la lista de productos filtrados
        if (productosFiltrados.estaVacia()) {
            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se encontraron productos con el color especificado." << endl;
            Sleep(1500); // Esperar 1.5 segundos antes de limpiar la pantalla
            system("cls");
        }
        else {
            cout << DOUBLE_SPACE << CYAN_COLOR << "Productos con el color especificado:" << endl;
            productosFiltrados.mostrarCatalogo();

            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
            _getch();
            system("cls");
        }
    }

    void filtrarPorMarca(GESTION_PRODUCTOS& productManager) {
        string marca;
        cout << YELLOW_COLOR << "Ingrese la marca por la que desea filtrar: " << RESET_COLOR;
        cin >> marca;

        // Convertir la marca ingresada a minúsculas para comparación sin distinción de mayúsculas y minúsculas
        transform(marca.begin(), marca.end(), marca.begin(), ::tolower);

        // Crear una nueva lista de productos filtrados por marca
        LISTA_PRODUCTO productosFiltrados;

        // Recorrer todos los productos en el catálogo y agregar aquellos que coincidan con la marca especificada
        NODO_PRODUCTO* actual = productManager.listaProductos.obtenerPrimero();
        while (actual != nullptr) {
            string marcaProducto = actual->producto.getMarca();
            // Convertir la marca del producto a minúsculas para comparación sin distinción de mayúsculas y minúsculas
            transform(marcaProducto.begin(), marcaProducto.end(), marcaProducto.begin(), ::tolower);

            // Verificar si la marca del producto contiene la cadena ingresada o si es similar
            if (marcaProducto.find(marca) != string::npos) {
                // Agregar el producto a la lista de productos filtrados
                productosFiltrados.agregarProducto(actual->producto);
            }
            actual = actual->siguiente;
        }

        // Mostrar la lista de productos filtrados
        if (productosFiltrados.estaVacia()) {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "No se encontraron productos con la marca especificada." << endl;
            Sleep(1500); // Esperar 1.5 segundos antes de limpiar la pantalla
            system("cls");
        }
        else {
            cout << DOUBLE_SPACE << CYAN_COLOR << "Productos con la marca especificada:" << endl;
            productosFiltrados.mostrarCatalogo();

            ShowConsoleCursor(false); // Oculta el cursor
            cout << DOUBLE_SPACE << GRAY_COLOR << "Presiona cualquier tecla para continuar...";
            _getch();
            system("cls");
        }
    }

    void ordenarProductosPorPrecioAscendente() {
        // Convertir la lista de productos a un vector para facilitar el ordenamiento
        vector<PRODUCTO> productosVector;
        for (NODO_PRODUCTO* actual = listaProductos.obtenerPrimero(); actual != nullptr; actual = actual->siguiente) {
            productosVector.push_back(actual->producto);
        }

        // Ordenar el vector de productos por precio de forma ascendente
        sort(productosVector.begin(), productosVector.end(), [](const PRODUCTO& a, const PRODUCTO& b) {
            return a.getPrecio() < b.getPrecio();
            });

        // Mostrar los productos ordenados
        cout << CYAN_COLOR << "Productos ordenados por precio (ascendente):" << DOUBLE_SPACE;
        for (const auto& producto : productosVector) {
            producto.mostrarInformacion();
            cout << endl;
        }
    }

    void ordenarProductosPorPrecioDescendente() {
        // Convertir la lista de productos a un vector para facilitar el ordenamiento
        vector<PRODUCTO> productosVector;
        for (NODO_PRODUCTO* actual = listaProductos.obtenerPrimero(); actual != nullptr; actual = actual->siguiente) {
            productosVector.push_back(actual->producto);
        }

        // Ordenar el vector de productos por precio de forma descendente
        sort(productosVector.begin(), productosVector.end(), [](const PRODUCTO& a, const PRODUCTO& b) {
            return a.getPrecio() > b.getPrecio();
            });

        // Mostrar los productos ordenados
        cout << CYAN_COLOR << "Productos ordenados por precio (descendente):" << DOUBLE_SPACE;
        for (const auto& producto : productosVector) {
            producto.mostrarInformacion();
            cout << endl;
        }
    }

    int getCantidadProductos() {
        int cantidadProductos = listaProductos.contarProductos();
        return cantidadProductos;
    }

};