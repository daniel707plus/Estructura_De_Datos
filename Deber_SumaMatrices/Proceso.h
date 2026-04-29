#ifndef PROCESO_H
#define PROCESO_H
#include "Matriz.h"

// Sobrecarga del operador + (Global)
Matriz operator+(const Matriz& a, const Matriz& b);

class Proceso {
public:
    // Solo dejamos las herramientas para interactuar con la matriz
    void pedirDatosMatriz(Matriz& matriz, int numeroMatriz);
    void mostrarMatriz(const Matriz& matriz);
};

#endif