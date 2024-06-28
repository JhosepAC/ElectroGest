#pragma once
#include <string>
#include <random>
#include <unordered_set>

using namespace std;

class CLIENTE {
private:
    string nombre;
    string apellido;
    string correoElectronico;
    string contrasenia;
    string confirmarContrasenia;
    string direccion;
    string telefono;
    string fechaNacimiento;
    string genero;
    string idCliente;

    // Función para generar un código de cliente aleatorio
    string generateClientId(const unordered_set<string>& existingIds) {
        string id;
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1000, 9999);

        do {
            id = "UEG_" + to_string(dis(gen));
        } while (existingIds.find(id) != existingIds.end());

        return id;
    }

public:
    // Constructor
    CLIENTE() {} // Constructor por defecto
    CLIENTE(const unordered_set<string>& existingIds) : idCliente(generateClientId(existingIds)) {}

    // Setters
    void setNombre(string nombre) { this->nombre = nombre; }
    void setApellido(string apellido) { this->apellido = apellido; }
    void setCorreoElectronico(string correoElectronico) { this->correoElectronico = correoElectronico; }
    void setContrasenia(string contrasenia) { this->contrasenia = contrasenia; }
    void setConfirmarContrasenia(string confirmarContrasenia) { this->confirmarContrasenia = confirmarContrasenia; }
    void setDireccion(string direccion) { this->direccion = direccion; }
    void setTelefono(string telefono) { this->telefono = telefono; }
    void setFechaNacimiento(string fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; }
    void setGenero(string genero) { this->genero = genero; }
    void setIdCliente(string idCliente) { this->idCliente = idCliente; }

    // Getters
    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    string getCorreoElectronico() const { return correoElectronico; }
    string getContrasenia() const { return contrasenia; }
    string getConfirmarContrasenia() const { return confirmarContrasenia; }
    string getDireccion() const { return direccion; }
    string getTelefono() const { return telefono; }
    string getFechaNacimiento() const { return fechaNacimiento; }
    string getGenero() const { return genero; }
    string getIdCliente() const { return idCliente; }

};

// Clase para almacenar el ID del cliente actual
// Se utiliza un patrón Singleton para asegurar que solo exista una instancia de la clase
// y que se pueda acceder a ella desde cualquier parte del programa sin necesidad de pasarla como parámetro

class CLIENTE_ACTUAL {
private:
    string clienteID;
    CLIENTE* cliente;
    static CLIENTE_ACTUAL* instancia;

    // Constructor privado
    CLIENTE_ACTUAL() : cliente(nullptr) {}

public:
    // Método para obtener la instancia única de la clase
    static CLIENTE_ACTUAL* obtenerInstancia() {
        if (instancia == nullptr) {
            instancia = new CLIENTE_ACTUAL();
        }
        return instancia;
    }

    // Setters
    void setClienteID(const string& id) { clienteID = id; }

    // Getters
    string getClienteID() const { return clienteID; }
    string getDireccion() const {
        return cliente->getDireccion();
    }

    // Función para cargar el ID del cliente actual desde un archivo usando el correo electrónico
    bool cargarClienteIDDesdeArchivo(const string& filePath, const string& email) {
        ifstream file(filePath);
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo: " << filePath << endl;
            return false;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, nombre, apellido, emailFromFile, username, direccion, telefono, fecha, genero;

            if (getline(ss, id, ',') && getline(ss, nombre, ',') && getline(ss, apellido, ',') &&
                getline(ss, emailFromFile, ',') && getline(ss, username, ',') && getline(ss, direccion, ',') &&
                getline(ss, telefono, ',') && getline(ss, fecha, ',') && getline(ss, genero)) {

                // Si el email coincide con el email del cliente actual, se guarda el id y se carga el cliente
                if (email == emailFromFile) {
                    clienteID = id;
                    cliente = new CLIENTE();
                    cliente->setIdCliente(id);
                    cliente->setNombre(nombre);
                    cliente->setApellido(apellido);
                    cliente->setCorreoElectronico(emailFromFile);
                    cliente->setDireccion(direccion);
                    cliente->setTelefono(telefono);
                    cliente->setFechaNacimiento(fecha);
                    cliente->setGenero(genero);
                    file.close();
                    return true;
                }
            }
        }

        file.close();
        return false;
    }

    // Función para obtener la dirección del cliente actual
    string obtenerDireccionClienteActual() const {
        return cliente->getDireccion();
    }
};

// Inicializar la instancia estática
CLIENTE_ACTUAL* CLIENTE_ACTUAL::instancia = nullptr;
