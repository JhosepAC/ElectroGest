#pragma once
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <fstream>
#include "general_variables.h"

class PRODUCTO {
protected:
    string codigo;
    string nombre;
    string marca;
    double precio;
    string modelo;
    double ancho;
    double alto;
    double largo;
    double peso;
    string material;
    string color;
    int garantia;

public:

    // Constructor
    PRODUCTO(const string& _codigo, const string& _nombre, const string& _marca, double _precio, const string& _modelo, double _ancho, double _alto, double _largo, double _peso, const string& _material, const string& _color, int _garantia)
        : codigo(_codigo), nombre(_nombre), marca(_marca), precio(_precio), modelo(_modelo), ancho(_ancho), alto(_alto), largo(_largo), peso(_peso), material(_material), color(_color), garantia(_garantia) {}

    // Destructor
    virtual ~PRODUCTO() {}

    // Método virtual puro para mostrar la información del producto
    virtual void mostrarInformacion() const {
        const int columnWidth = 25;

        cout << BLUE_COLOR << left << setw(columnWidth) << "Nombre:" << RESET_COLOR << setw(columnWidth) << nombre;
        cout << BLUE_COLOR << left << setw(columnWidth) << "Codigo:" << RESET_COLOR << setw(columnWidth) << codigo << endl;
        cout << BLUE_COLOR << left << setw(columnWidth) << "Marca:" << RESET_COLOR << setw(columnWidth) << marca;
        cout << BLUE_COLOR << left << setw(columnWidth) << "Precio:" << RESET_COLOR << "S/" << setw(columnWidth - 3) << precio << endl;
        cout << BLUE_COLOR << left << setw(columnWidth) << "Modelo:" << RESET_COLOR << setw(columnWidth) << modelo;
        cout << BLUE_COLOR << left << setw(columnWidth) << "Ancho (cm):" << RESET_COLOR << setw(columnWidth) << ancho << endl;
        cout << BLUE_COLOR << left << setw(columnWidth) << "Alto (cm):" << RESET_COLOR << setw(columnWidth) << alto;
        cout << BLUE_COLOR << left << setw(columnWidth) << "Largo (cm):" << RESET_COLOR << setw(columnWidth) << largo << endl;
        cout << BLUE_COLOR << left << setw(columnWidth) << "Peso (Kg):" << RESET_COLOR << setw(columnWidth) << peso;
        cout << BLUE_COLOR << left << setw(columnWidth) << "Material:" << RESET_COLOR << setw(columnWidth) << material << endl;
        cout << BLUE_COLOR << left << setw(columnWidth) << "Color:" << RESET_COLOR << setw(columnWidth) << color;
        cout << BLUE_COLOR << left << setw(columnWidth) << "Garantia (meses):" << RESET_COLOR << setw(columnWidth) << garantia << endl;
        cout << endl << YELLOW_COLOR << "--------------------------------------------------------------------------------------------" << RESET_COLOR;
    }

    // Método para mostrar la información del producto en un archivo
    void mostrarInformacionArchivo(ofstream& file) const {
        const int columnWidth = 25;

        file << left << setw(columnWidth) << "Nombre:" << nombre << endl;
        file << left << setw(columnWidth) << "Codigo:" << codigo << endl;
        file << left << setw(columnWidth) << "Marca:" << marca << endl;
        file << left << setw(columnWidth) << "Precio:" << "S/" << fixed << setprecision(2) << setw(columnWidth - 5) << precio << endl;
        file << left << setw(columnWidth) << "Modelo:" << modelo << endl;
        file << left << setw(columnWidth) << "Ancho (cm):" << fixed << setprecision(2) << setw(columnWidth - 10) << ancho << endl;
        file << left << setw(columnWidth) << "Alto (cm):" << fixed << setprecision(2) << setw(columnWidth - 9) << alto << endl;
        file << left << setw(columnWidth) << "Largo (cm):" << fixed << setprecision(2) << setw(columnWidth - 10) << largo << endl;
        file << left << setw(columnWidth) << "Peso (Kg):" << fixed << setprecision(2) << setw(columnWidth - 9) << peso << endl;
        file << left << setw(columnWidth) << "Material:" << material << endl;
        file << left << setw(columnWidth) << "Color:" << color << endl;
        file << left << setw(columnWidth) << "Garantia (meses):" << setw(columnWidth - 15) << garantia << endl;

        file << endl;
        // Agregar una línea de separación después de cada producto
        file << "----------------------------------------" << endl;
    }

    // Setters y Getters
    void setCodigo(const string& _codigo) { codigo = _codigo; }
    void setNombre(const string& _nombre) { nombre = _nombre; }
    void setMarca(const string& _marca) { marca = _marca; }
    void setPrecio(double _precio) { precio = _precio; }
    void setModelo(const string& _modelo) { modelo = _modelo; }
    void setAncho(double _ancho) { ancho = _ancho; }
    void setAlto(double _alto) { alto = _alto; }
    void setLargo(double _largo) { largo = _largo; }
    void setPeso(double _peso) { peso = _peso; }
    void setMaterial(const string& _material) { material = _material; }
    void setColor(const string& _color) { color = _color; }
    void setGarantia(int _garantia) { garantia = _garantia; }

    // Getters
    const string& getCodigo() const { return codigo; }
    const string& getNombre() const { return nombre; }
    const string& getMarca() const { return marca; }
    double getPrecio() const { return precio; }
    const string& getModelo() const { return modelo; }
    double getAncho() const { return ancho; }
    double getAlto() const { return alto; }
    double getLargo() const { return largo; }
    double getPeso() const { return peso; }
    const string& getMaterial() const { return material; }
    const string& getColor() const { return color; }
    int getGarantia() const { return garantia; }

};