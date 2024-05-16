#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "suppliersList.h" // Supongamos que este archivo contiene la definición de la clase Proveedor y ListaProveedores

class GestionarProveedores {
public:
        
    GestionarProveedores() {}

    // Método para cargar la lista de proveedores desde el archivo
    void cargarListaDesdeArchivo(string _currentLanguage) { listaProveedores.cargarDesdeArchivo(archivoProveedores, _currentLanguage); }

    // Método para cargar datos desde el archivo
    void cargarDatosDesdeArchivo(string _currentLanguage) { listaProveedores.cargarDesdeArchivo(archivoProveedores, _currentLanguage);}

    // Método para mostrar la lista de proveedores
    void verListaProveedores(string _currenLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currenLanguage;

        cout << CYAN_COLOR << menuTexts[currentLanguage][260] << RESET_COLOR << DOUBLE_SPACE;
        listaProveedores.mostrarProveedores(_currenLanguage);
    }

    // Método para agregar un proveedor
    void agregarProveedor(const string& archivo, string _currentLanguage) {
        
        // Idioma predeterminado
        string currentLanguage = _currentLanguage;
        
        string nombre, direccion, telefono;

        cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][261] << " ===" << RESET_COLOR << DOUBLE_SPACE; // Menú de agregar proveedor
        cout << YELLOW_COLOR << menuTexts[currentLanguage][262] << RESET_COLOR; // Solicitar nombre del proveedor
        cin.ignore();
        getline(cin, nombre);

        // Validar si el proveedor ya existe en el archivo
        ifstream archivoProveedores(archivo);
        string linea;
        bool proveedorExiste = false;

        // Leer línea por línea y verificar si el proveedor ya existe
        while (getline(archivoProveedores, linea)) {
            stringstream ss(linea);
            string nombreExistente, direccionExistente;
            int telefonoExistente;
            getline(ss, nombreExistente, ',');
            getline(ss, direccionExistente, ',');
            ss >> telefonoExistente;
            // Verificar si el nombre del proveedor ya existe
            if (nombreExistente == nombre) {
                proveedorExiste = true;
                break;
            }
        }
        archivoProveedores.close();

        // Si el proveedor ya existe, mostrar un mensaje y salir
        if (proveedorExiste) {
            cout << MAGENTA_COLOR << menuTexts[currentLanguage][263] << endl; // Mensaje de proveedor existente
            return;
        }

        cout << YELLOW_COLOR << menuTexts[currentLanguage][264] << RESET_COLOR; // Solicitar dirección del proveedor
        getline(cin, direccion);

        bool telefonoValido = false;
        string nuevoTelefono;

        // Solicitar el teléfono hasta que sea válido
        while (!telefonoValido) {
            cout << YELLOW_COLOR << menuTexts[currentLanguage][265] << RESET_COLOR;
            cin >> nuevoTelefono;

            // Verificar si el teléfono tiene exactamente 9 dígitos
            if (nuevoTelefono.length() == 9 && nuevoTelefono.find_first_not_of("0123456789") == string::npos) {
                telefonoValido = true;
            }
            else {
                cout << endl << MAGENTA_COLOR << menuTexts[currentLanguage][266] << RESET_COLOR << DOUBLE_SPACE; // Mensaje de teléfono inválido
            }
        }

        Proveedor* proveedor = new Proveedor(nombre, direccion, nuevoTelefono);
        listaProveedores.agregarProveedor(proveedor);

        // Guardar en el archivo
        ofstream archivoProveedoresEscritura(archivo, ios::app); // Abrir en modo de añadir al final

        // Verificar si el archivo se abrió correctamente
        if (!archivoProveedoresEscritura.is_open()) {
            cout << MAGENTA_COLOR << DOUBLE_SPACE << menuTexts[currentLanguage][404] << endl; // Mensaje de error al abrir el archivo
            return;
        }
        archivoProveedoresEscritura << nombre << "," << direccion << "," << telefono << endl; // Escribir los datos del proveedor
        archivoProveedoresEscritura.close();

        guardarListaEnArchivo(_currentLanguage);

        ShowConsoleCursor(false);
        cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][268] << endl; // Mensaje de proveedor agregado
    }

    void actualizarProveedor(const string& archivo, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        string nombreBuscar;
        bool telefonoValido = false;

        cout << CYAN_COLOR << "=== " << menuTexts[_currentLanguage][279] << " ===" << DOUBLE_SPACE; // Menú de actualizar proveedor
        cout << YELLOW_COLOR << menuTexts[_currentLanguage][280] << RESET_COLOR; // Solicitar nombre del proveedor a actualizar
        cin.ignore();
        getline(cin, nombreBuscar);

        // Buscar el proveedor por nombre
        int opcion = -1;

        // Iterar sobre la lista de proveedores y buscar por nombre
        for (int i = 0; i < listaProveedores.size(); ++i) {
            Proveedor* proveedor = listaProveedores.obtenerProveedor(i);

            // Si se encuentra el proveedor, almacenar la posición
            if (proveedor->getNombre() == nombreBuscar) {
                opcion = i;
                break;
            }
        }

        // Si no se encontró el proveedor, mostrar un mensaje y salir
        if (opcion == -1) {
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[_currentLanguage][281] << endl; // Mensaje de proveedor no encontrado
            _sleep(1500);
            return;
        }

        Proveedor* proveedor = listaProveedores.obtenerProveedor(opcion);

        string nuevoNombre, nuevaDireccion, nuevoTelefono;

        cout << YELLOW_COLOR << menuTexts[_currentLanguage][282] << RESET_COLOR; // Solicitar nuevo nombre
        getline(cin, nuevoNombre);
        cout << YELLOW_COLOR << menuTexts[_currentLanguage][283] << RESET_COLOR; // Solicitar nueva dirección
        getline(cin, nuevaDireccion);

        // Solicitar el teléfono hasta que sea válido
        while (!telefonoValido) {
            cout << YELLOW_COLOR << menuTexts[_currentLanguage][284] << RESET_COLOR; // Solicitar nuevo teléfono
            cin >> nuevoTelefono;

            // Verificar si el teléfono tiene exactamente 9 dígitos
            if (nuevoTelefono.length() == 9 && nuevoTelefono.find_first_not_of("0123456789") == string::npos) {
                telefonoValido = true;
            }
            else {
                cout << endl << MAGENTA_COLOR << menuTexts[_currentLanguage][285] << RESET_COLOR << DOUBLE_SPACE;
            }
        }

        // Actualizar los datos del proveedor
        if (!nuevoNombre.empty()) {
            proveedor->setNombre(nuevoNombre);
        }

        // Actualizar la dirección si no está vacía
        if (!nuevaDireccion.empty()) {
            proveedor->setDireccion(nuevaDireccion);
        }

        // Actualizar el teléfono si no está vacío
        if (!nuevoTelefono.empty()) {
            proveedor->setTelefono(nuevoTelefono);
        }

        // Actualizar el archivo
        ofstream archivoProveedores(archivo); // Abrir el archivo para escribir

        // Verificar si el archivo se abrió correctamente
        if (!archivoProveedores.is_open()) {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[_currentLanguage][404] << endl; // Mensaje de error al abrir el archivo
            return;
        }

        // Escribir los datos actualizados en el archivo
        for (int i = 0; i < listaProveedores.size(); ++i) {
            Proveedor* proveedor = listaProveedores.obtenerProveedor(i);
            archivoProveedores << proveedor->getNombre() << "," << proveedor->getDireccion() << "," << proveedor->getTelefono() << endl;
        }

        archivoProveedores.close(); // Cerrar el archivo después de escribir

        // Guardar en el archivo
        guardarListaEnArchivo(_currentLanguage);

        ShowConsoleCursor(false);
        cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[_currentLanguage][287] << endl;
    }

    // Método para eliminar un proveedor
    void eliminarProveedor(const string& archivo, string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        cout << CYAN_COLOR << "=== " << menuTexts[currentLanguage][269] << " ===" << DOUBLE_SPACE << RESET_COLOR; // Menú de eliminar proveedor
        cout << GRAY_COLOR << menuTexts[currentLanguage][270] << DOUBLE_SPACE << RESET_COLOR; // Mostrar la lista de proveedores
        listaProveedores.mostrarProveedores(_currentLanguage);

        int opcion;
        cout << DOUBLE_SPACE << YELLOW_COLOR << menuTexts[currentLanguage][271] << RESET_COLOR; // Solicitar la opción a eliminar
        cin >> opcion;
        cin.ignore();

        // Verificar si la opción es válida
        if (opcion < 1 || opcion > listaProveedores.size()) {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][272] << endl; // Mensaje de opción inválida
            return;
        }

        Proveedor* proveedorEliminar = listaProveedores.obtenerProveedor(opcion - 1);
        listaProveedores.eliminarProveedor(opcion - 1, _currentLanguage);

        // Actualizar el archivo eliminando el proveedor
        ifstream archivoProveedoresLectura(archivo);
        ofstream archivoProveedoresEscritura("temp.txt"); // Archivo temporal para escribir sin el proveedor eliminado
        string linea;
        int contador = 0;

        // Leer línea por línea y escribir en el archivo temporal sin la línea a eliminar
        while (getline(archivoProveedoresLectura, linea)) {
            ++contador;
            if (contador != opcion) {
                archivoProveedoresEscritura << linea << endl;
            }
        }
        archivoProveedoresLectura.close();
        archivoProveedoresEscritura.close();

        // Eliminar el archivo original y renombrar el archivo temporal
        remove(archivo.c_str());
        rename("temp.txt", archivo.c_str());

        // Guardar en el archivo
        guardarListaEnArchivo(_currentLanguage);

        ShowConsoleCursor(false);
        cout << DOUBLE_SPACE << GREEN_COLOR << menuTexts[currentLanguage][273] << endl;
    }

    // Método para buscar un proveedor por nombre
    void buscarProveedor(const string& nombreBuscar, string _currentLanguage) const {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        int posicion = listaProveedores.buscarProveedorPorNombre(nombreBuscar);

        // Verificar si se encontró el proveedor
        if (posicion != -1) {
            Proveedor* proveedor = listaProveedores.obtenerProveedor(posicion);
            cout << DOUBLE_SPACE << CYAN_COLOR << menuTexts[currentLanguage][274] << RESET_COLOR << endl; // Mensaje de proveedor encontrado
            cout << GRAY_COLOR << menuTexts[currentLanguage][23] << RESET_COLOR << proveedor->getNombre() << endl; // Nombre del proveedor
            cout << GRAY_COLOR << menuTexts[currentLanguage][25] << RESET_COLOR << proveedor->getDireccion() << endl; // Dirección del proveedor
            cout << GRAY_COLOR << menuTexts[currentLanguage][29] << RESET_COLOR << proveedor->getTelefono() << endl; // Teléfono del proveedor
            ShowConsoleCursor(false);
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << menuTexts[currentLanguage][278] << endl; // Mensaje de proveedor no encontrado
        }
    }

    // Método para verificar si la lista de proveedores está vacía
    bool listaProveedoresVacia() { return listaProveedores.size() == 0; }

private:
    ListaProveedores listaProveedores;
    const string archivoProveedores = "supplier_data.txt"; // Mover archivo a miembro privado

    // Agregar un método privado para guardar la lista de proveedores en el archivo
    void guardarListaEnArchivo(string _currentLanguage) {

        // Idioma predeterminado
        string currentLanguage = _currentLanguage;

        ofstream archivoProveedoresEscritura(archivoProveedores);

        // Verificar si el archivo se abrió correctamente
        if (!archivoProveedoresEscritura.is_open()) {
            cout << menuTexts[currentLanguage][404] << endl; // Mensaje de error al abrir el archivo
            return;
        }

        for (int i = 0; i < listaProveedores.size(); ++i) {
            Proveedor* proveedor = listaProveedores.obtenerProveedor(i);
            archivoProveedoresEscritura << proveedor->getNombre() << "," << proveedor->getDireccion() << "," << proveedor->getTelefono() << endl; // Escribir los datos del proveedor
        }

        archivoProveedoresEscritura.close(); // Cerrar el archivo después de escribir
    }

};