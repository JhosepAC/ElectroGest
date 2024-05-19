#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "suppliersList.h" // Supongamos que este archivo contiene la definición de la clase Proveedor y ListaProveedores

class GestionarProveedores {
public:
        
    GestionarProveedores() {}

    void cargarListaDesdeArchivo() {
        listaProveedores.cargarDesdeArchivo(archivoProveedores);
    }

    // Método para cargar datos desde el archivo
    void cargarDatosDesdeArchivo() {
        listaProveedores.cargarDesdeArchivo(archivoProveedores);
    }

    void verListaProveedores() const {
        cout << CYAN_COLOR << "=== LISTA DE PROVEEDORES ===" << RESET_COLOR << DOUBLE_SPACE;
        listaProveedores.mostrarProveedores();
    }

    void agregarProveedor(const string& archivo) {
        string nombre, direccion, telefono;

        cout << CYAN_COLOR << "=== AGREGAR NUEVO PROVEEDOR ===" << RESET_COLOR << DOUBLE_SPACE;
        cout << YELLOW_COLOR << "Ingrese el nombre del proveedor: " << RESET_COLOR;
        cin.ignore();
        getline(cin, nombre);

        // Validar si el proveedor ya existe en el archivo
        ifstream archivoProveedores(archivo);
        string linea;
        bool proveedorExiste = false;
        while (getline(archivoProveedores, linea)) {
            stringstream ss(linea);
            string nombreExistente, direccionExistente;
            int telefonoExistente;
            getline(ss, nombreExistente, ',');
            getline(ss, direccionExistente, ',');
            ss >> telefonoExistente;
            if (nombreExistente == nombre) {
                proveedorExiste = true;
                break;
            }
        }
        archivoProveedores.close();

        if (proveedorExiste) {
            cout << MAGENTA_COLOR << "El proveedor ya existe en el archivo." << endl;
            return;
        }

        cout << YELLOW_COLOR << "Ingrese la dirección del proveedor: " << RESET_COLOR;
        getline(cin, direccion);

        bool telefonoValido = false;
        string nuevoTelefono;

        while (!telefonoValido) {
            cout << YELLOW_COLOR << "Ingrese el nuevo teléfono del proveedor: " << RESET_COLOR;
            cin >> nuevoTelefono;

            // Verificar si el teléfono tiene exactamente 9 dígitos
            if (nuevoTelefono.length() == 9 && nuevoTelefono.find_first_not_of("0123456789") == string::npos) {
                telefonoValido = true;
            }
            else {
                cout << endl << MAGENTA_COLOR << "El número de teléfono debe tener exactamente 9 dígitos. Inténtelo de nuevo." << RESET_COLOR << DOUBLE_SPACE;
            }
        }

        Proveedor* proveedor = new Proveedor(nombre, direccion, nuevoTelefono);
        listaProveedores.agregarProveedor(proveedor);

        // Guardar en el archivo
        ofstream archivoProveedoresEscritura(archivo, ios::app); // Abrir en modo de añadir al final
        if (!archivoProveedoresEscritura.is_open()) {
            cout << MAGENTA_COLOR << DOUBLE_SPACE << "Error al abrir el archivo de proveedores para escritura." << endl;
            return;
        }
        archivoProveedoresEscritura << nombre << "," << direccion << "," << telefono << endl;
        archivoProveedoresEscritura.close();

        guardarListaEnArchivo();

        ShowConsoleCursor(false);
        cout << DOUBLE_SPACE << GREEN_COLOR << "Proveedor agregado correctamente." << endl;
    }

    void actualizarProveedor(const string& archivo) {
        string nombreBuscar;
        bool telefonoValido = false;

        cout << CYAN_COLOR << "=== ACTUALIZAR PROVEEDOR ===" << DOUBLE_SPACE;
        cout << YELLOW_COLOR << "Ingrese el nombre del proveedor que desea actualizar: " << RESET_COLOR;
        cin.ignore();
        getline(cin, nombreBuscar);

        // Buscar el proveedor por nombre
        int opcion = -1;
        for (int i = 0; i < listaProveedores.size(); ++i) {
            Proveedor* proveedor = listaProveedores.obtenerProveedor(i);
            if (proveedor->getNombre() == nombreBuscar) {
                opcion = i;
                break;
            }
        }

        if (opcion == -1) {
            ShowConsoleCursor(false);
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Proveedor no encontrado. Actualización cancelada." << endl;
            _sleep(1500);
            return;
        }

        Proveedor* proveedor = listaProveedores.obtenerProveedor(opcion);

        string nuevoNombre, nuevaDireccion, nuevoTelefono;

        cout << YELLOW_COLOR << "Ingrese el nuevo nombre del proveedor (deje vacío para mantener el mismo): " << RESET_COLOR;
        getline(cin, nuevoNombre);
        cout << YELLOW_COLOR << "Ingrese la nueva dirección del proveedor (deje vacío para mantener la misma): " << RESET_COLOR;
        getline(cin, nuevaDireccion);
        while (!telefonoValido) {
            cout << YELLOW_COLOR << "Ingrese el nuevo teléfono del proveedor (deje 0 para mantener el mismo): " << RESET_COLOR;
            cin >> nuevoTelefono;

            // Si ingresa 0, mantener el mismo teléfono
            if (nuevoTelefono == "0") {
				nuevoTelefono = proveedor->getTelefono();
				telefonoValido = true;
			}

            // Verificar si el teléfono tiene exactamente 9 dígitos
            if (nuevoTelefono.length() == 9 && nuevoTelefono.find_first_not_of("0123456789") == string::npos) {
                telefonoValido = true;
            }
            else {
                cout << endl << MAGENTA_COLOR << "El número de teléfono debe tener exactamente 9 dígitos. Inténtelo de nuevo." << RESET_COLOR << DOUBLE_SPACE;
            }
        }

        if (!nuevoNombre.empty()) {
            proveedor->setNombre(nuevoNombre);
        }
        if (!nuevaDireccion.empty()) {
            proveedor->setDireccion(nuevaDireccion);
        }
        if (nuevoTelefono.empty()) {
            proveedor->setTelefono(nuevoTelefono);
        }

        // Actualizar el archivo
        ofstream archivoProveedores(archivo); // Abrir el archivo para escribir
        if (!archivoProveedores.is_open()) {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Error al abrir el archivo de proveedores." << endl;
            return;
        }

        for (int i = 0; i < listaProveedores.size(); ++i) {
            Proveedor* proveedor = listaProveedores.obtenerProveedor(i);
            archivoProveedores << proveedor->getNombre() << "," << proveedor->getDireccion() << "," << proveedor->getTelefono() << endl;
        }

        archivoProveedores.close(); // Cerrar el archivo después de escribir

        // Guardar en el archivo
        guardarListaEnArchivo();

        ShowConsoleCursor(false);
        cout << DOUBLE_SPACE << GREEN_COLOR << "Proveedor actualizado correctamente." << endl;
    }

    void eliminarProveedor(const string& archivo) {
        cout << CYAN_COLOR << "=== ELIMINAR PROVEEDOR ===" << DOUBLE_SPACE << RESET_COLOR;
        cout << GRAY_COLOR << "Lista de Proveedores:" << DOUBLE_SPACE << RESET_COLOR;
        listaProveedores.mostrarProveedores();

        int opcion;
        cout << DOUBLE_SPACE << YELLOW_COLOR << "Seleccione el proveedor a eliminar (ingrese el número de orden): " << RESET_COLOR;
        cin >> opcion;
        cin.ignore();

        if (opcion < 1 || opcion > listaProveedores.size()) {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Opción no válida." << endl;
            return;
        }

        Proveedor* proveedorEliminar = listaProveedores.obtenerProveedor(opcion - 1);
        listaProveedores.eliminarProveedor(opcion - 1);

        // Actualizar el archivo eliminando el proveedor
        ifstream archivoProveedoresLectura(archivo);
        ofstream archivoProveedoresEscritura("temp.txt"); // Archivo temporal para escribir sin el proveedor eliminado
        string linea;
        int contador = 0;
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
        guardarListaEnArchivo();

        ShowConsoleCursor(false);
        cout << DOUBLE_SPACE << GREEN_COLOR << "Proveedor eliminado correctamente." << endl;
    }

    void buscarProveedor(const string& nombreBuscar) const {
        int posicion = listaProveedores.buscarProveedorPorNombre(nombreBuscar);
        if (posicion != -1) {
            Proveedor* proveedor = listaProveedores.obtenerProveedor(posicion);
            cout << DOUBLE_SPACE << CYAN_COLOR << "Proveedor encontrado:" << RESET_COLOR << endl;
            cout << BLUE_COLOR << "Nombre: " << RESET_COLOR << proveedor->getNombre() << endl;
            cout << BLUE_COLOR << "Dirección: " << RESET_COLOR << proveedor->getDireccion() << endl;
            cout << BLUE_COLOR << "Teléfono: " << RESET_COLOR << proveedor->getTelefono() << endl;
            ShowConsoleCursor(false);
        }
        else {
            cout << DOUBLE_SPACE << MAGENTA_COLOR << "Proveedor no encontrado." << endl;
        }
    }

    bool listaProveedoresVacia() {
		return listaProveedores.size() == 0;
	}

private:
    ListaProveedores listaProveedores;
    const string archivoProveedores = "supplier_data.txt"; // Mover archivo a miembro privado

    // Agregar un método privado para guardar la lista de proveedores en el archivo
    void guardarListaEnArchivo() {
        ofstream archivoProveedoresEscritura(archivoProveedores);
        if (!archivoProveedoresEscritura.is_open()) {
            cout << MAGENTA_COLOR << "Error al abrir el archivo de proveedores para escritura." << endl;
            return;
        }

        for (int i = 0; i < listaProveedores.size(); ++i) {
            Proveedor* proveedor = listaProveedores.obtenerProveedor(i);
            archivoProveedoresEscritura << proveedor->getNombre() << "," << proveedor->getDireccion() << "," << proveedor->getTelefono() << endl;
        }

        archivoProveedoresEscritura.close(); // Cerrar el archivo después de escribir
    }

};