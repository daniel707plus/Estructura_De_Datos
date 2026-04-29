#ifndef PROCESO_H
#define PROCESO_H

#include "Matriz.h"
#include <iostream>

using namespace std;

template <typename T>
Matriz<T> operator*(const Matriz<T>& a, const Matriz<T>& b);

template <typename T>
void multiplicacionRecursiva(const Matriz<T>& a, const Matriz<T>& b, Matriz<T>& resultado,
    int i, int j, int k, int x, T sumaAcumulada);

template <typename T>
Matriz<T> operator+(const Matriz<T>& a, const Matriz<T>& b); 

class Proceso {
public:
    template <typename T>
    void ingresar(Matriz<T>& matriz, const char* nombreMatriz);

    template <typename T>
    void imprimir(const Matriz<T>& matriz, const char* nombreMatriz);

    template <typename T>
    void diagonal(const Matriz<T>& matriz);
};

#include "Proceso.cpp"
#endif