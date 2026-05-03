/***********************************************************************
 * Module:  Matriz.cpp
 * Author:  USUARIO
 * Modified: s�bado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class Matriz
 ***********************************************************************/

#include "Matriz.h"

Matriz::Matriz(int f, int c) {
    filas = f;
    columnas = c;
    m = new int*[filas];
    for (int i = 0; i < filas; i++) {
        m[i] = new int[columnas]{0}; // Inicializa en 0
    }
}

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

void Matriz::liberarMemoria() {
    for (int i = 0; i < filas; i++) {
        delete[] m[i];
    }
    delete[] m;
}

Matriz::~Matriz() {
    liberarMemoria();
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