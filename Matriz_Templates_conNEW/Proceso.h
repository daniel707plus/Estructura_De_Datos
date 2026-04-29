#ifndef PROCESO_H
#define PROCESO_H

#include "Matriz.h"
#include <iostream>

using namespace std;

template <typename T>
Matriz<T> operator+(const Matriz<T>& a, const Matriz<T>& b);


class Proceso {
public:
    template <typename T>   
    void pedirDatosMatriz(Matriz<T>& matriz, int numeroMatriz);

    template <typename T>
    void mostrarMatriz(const Matriz<T>& matriz);
};

#include "Proceso.cpp"
#endif