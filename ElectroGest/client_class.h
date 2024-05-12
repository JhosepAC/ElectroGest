#pragma once
#include <string>

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

public:
    // Constructor
    CLIENTE() {};

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

};