#pragma once
#include <string>
#include <random>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <iomanip>

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
    double totalGastado;

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
    CLIENTE() {}
    CLIENTE(const unordered_set<string>& existingIds) : idCliente(generateClientId(existingIds)) {}
    CLIENTE(const string& idCliente, const string& nombre, const string& email)
        : idCliente(idCliente), nombre(nombre), correoElectronico(email), totalGastado(0.0) {}
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
    double getTotalGastado() const { return totalGastado; }
    void añadirGasto(double cantidad) {
        totalGastado += cantidad;
    }
};

// Clase para almacenar el ID del cliente actual
// Se utiliza un patrón Singleton para asegurar que solo exista una instancia de la clase
// y que se pueda acceder a ella desde cualquier parte del programa sin necesidad de pasarla como parámetro

class CLIENTE_ACTUAL {
private:
    string clienteID;
    static CLIENTE_ACTUAL* instancia;
    CLIENTE* cliente;
    // Constructor privado
    CLIENTE_ACTUAL() {}

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

                // Si el email coincide con el email del cliente actual, se guarda el id
                if (email == emailFromFile) {
                    clienteID = id;
                    file.close();
                    return true;
                }
            }
        }


        file.close();
        return false;
    }
    string obtenerDireccionClienteActual() const {
        return cliente->getDireccion();
    }
};

// Inicializar la instancia estática
CLIENTE_ACTUAL* CLIENTE_ACTUAL::instancia = nullptr;
#define CYAN_COLOR "\033[36m"
#define YELLOW_COLOR "\033[33m"
#define GREEN_COLOR "\033[32m"
#define MAGENTA_COLOR "\033[35m"
#define BLUE_COLOR "\033[34m"
#define GRAY_COLOR "\033[37m"
#define RESET_COLOR "\033[0m"
#define DOUBLE_SPACE "\n\n"

void ShowConsoleCurse(bool showFlag) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut == INVALID_HANDLE_VALUE) {
        return;
    }

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = showFlag; // Establece la visibilidad del cursor
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

// Nodo del árbol binario de búsqueda
struct ClienteNode {
    CLIENTE cliente;
    ClienteNode* left;
    ClienteNode* right;

    ClienteNode(const CLIENTE& cliente) : cliente(cliente), left(nullptr), right(nullptr) {}
};

// Árbol binario de búsqueda para clientes
class ClienteBST {
private:
    ClienteNode* root;

    void insertNode(ClienteNode*& node, const CLIENTE& cliente) {
        if (!node) {
            node = new ClienteNode(cliente);
        }
        else if (cliente.getTotalGastado() < node->cliente.getTotalGastado()) {
            insertNode(node->left, cliente);
        }
        else {
            insertNode(node->right, cliente);
        }
    }


    void searchNode(ClienteNode* node, const string& searchTerm, const string& criterion, vector<CLIENTE>& results) const {
        if (node == nullptr) return;
        bool match = false;
        if (criterion == "nombre" && node->cliente.getNombre().find(searchTerm) != string::npos) {
            match = true;
        }
        else if (criterion == "apellido" && node->cliente.getApellido().find(searchTerm) != string::npos) {
            match = true;
        }
        else if (criterion == "codigo" && node->cliente.getIdCliente().find(searchTerm) != string::npos) {
            match = true;
        }
        else if (criterion == "telefono" && node->cliente.getTelefono().find(searchTerm) != string::npos) {
            match = true;
        }
        else if (criterion == "correo" && node->cliente.getCorreoElectronico().find(searchTerm) != string::npos) {
            match = true;
        }

        if (match) {
            results.push_back(node->cliente);
        }
        searchNode(node->left, searchTerm, criterion, results);
        searchNode(node->right, searchTerm, criterion, results);
    }

    void inorderDisplay(ClienteNode* node) const {
        if (node == nullptr) return;
        inorderDisplay(node->left);
        cout << left << setw(15) << node->cliente.getIdCliente()
            << setw(15) << node->cliente.getNombre()
            << setw(20) << node->cliente.getApellido()
            << setw(35) << node->cliente.getCorreoElectronico()
            << setw(20) << node->cliente.getDireccion()
            << setw(15) << node->cliente.getTelefono()
            << setw(25) << node->cliente.getFechaNacimiento()
            << setw(10) << node->cliente.getGenero() << DOUBLE_SPACE;
        inorderDisplay(node->right);
    }

public:
    ClienteBST() : root(nullptr) {}

    void insert(const CLIENTE& cliente) {
        insertNode(root, cliente);
    }

    vector<CLIENTE> search(const string& searchTerm, const string& criterion) const {
        vector<CLIENTE> results;
        searchNode(root, searchTerm, criterion, results);
        return results;
    }

    void display() const {
        inorderDisplay(root);
    }
};