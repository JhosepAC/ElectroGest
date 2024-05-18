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