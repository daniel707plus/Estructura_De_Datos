#ifndef MATRIZ_H
#define MATRIZ_H

#include <cstdlib>
#include <iostream>

template <typename T>
class Matriz {
private:
    int filas;
    int columnas;
    T** m; 

    void liberarMemoria() {
        if (m != nullptr) {
            for (int i = 0; i < filas; i++) {
                free(*(m + i));
            }
            free(m);
        }
    }

public:
    Matriz(int f, int c);
    Matriz(const Matriz<T>& copia);
    ~Matriz();

    int getFilas() const;
    int getColumnas() const;
    void setDato(int f, int c, T valor) ;
    T getDato(int f, int c) const ;
};

#include "Matriz.cpp"
#endif