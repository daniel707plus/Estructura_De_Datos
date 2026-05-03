/***********************************************************************
 * Module:  Matriz.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class Matriz
 ***********************************************************************/

#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <cstdlib> // Obligatorio para malloc y free

template <typename T>
class Matriz {
private:
    int filas;
    int columnas;
    int prof; 
    T*** m;   

    void liberarMemoria() {
        if (m != nullptr) {
            for (int i = 0; i < filas; i++) {
                for (int j = 0; j < columnas; j++) {
                    free(*(*(m + i) + j)); // Liberamos la profundidad
                }
                free(*(m + i)); // Liberamos las columnas
            }
            free(m); // Liberamos las filas principales
        }
    }

public:
    Matriz(int f, int c, int p);
    Matriz(const Matriz<T>& copia);
    ~Matriz();

    int getFilas() const;
    int getColumnas() const;
    int getProf() const;
    
    void setDato(int f, int c, int p, T valor);
    T getDato(int f, int c, int p) const;
};

#include "Matriz.cpp"
#endif