#include "Matriz.h"

// Constructor: Reserva la memoria
Matriz::Matriz(int f, int c) {
    filas = f;
    columnas = c;
    m = new int*[filas];
    for (int i = 0; i < filas; i++) {
        m[i] = new int[columnas]{0}; // Inicializa en 0
    }
}

// Constructor de copia
Matriz::Matriz(const Matriz& otra) {
    filas = otra.filas;
    columnas = otra.columnas;
    m = new int*[filas];
    for (int i = 0; i < filas; i++) {
        m[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            m[i][j] = otra.m[i][j];
        }
    }
}

// Liberar memoria (para no repetir código en destructor y operador=)
void Matriz::liberarMemoria() {
    for (int i = 0; i < filas; i++) {
        delete[] m[i];
    }
    delete[] m;
}

// Destructor
Matriz::~Matriz() {
    liberarMemoria();
}

// Operador de asignación
Matriz& Matriz::operator=(const Matriz& otra) {
    if (this != &otra) {
        liberarMemoria(); // Borra lo viejo
        filas = otra.filas;
        columnas = otra.columnas;
        m = new int*[filas];
        for (int i = 0; i < filas; i++) {
            m[i] = new int[columnas];
            for (int j = 0; j < columnas; j++) {
                m[i][j] = otra.m[i][j];
            }
        }
    }
    return *this;
}

int Matriz::getFilas() const {
     return filas; 
    }
int Matriz::getColumnas() const { 
    return columnas; 
    }

void Matriz::setDato(int f, int c, int valor) {
    m[f][c] = valor;
}

int Matriz::getDato(int f, int c) const {
    return m[f][c];
}