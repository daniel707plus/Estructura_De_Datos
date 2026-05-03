/***********************************************************************
 * Module:  Proceso.h
 * Author:  USUARIO
 * Modified: s�bado, 2 de mayo de 2026 19:31:35
 * Purpose: Declaration of the class Proceso
 ***********************************************************************/

#ifndef PROCESO_H
#define PROCESO_H
#include "Matriz.h"

Matriz operator+(const Matriz& a, const Matriz& b);

class Proceso {
public:
    
    void pedirDatosMatriz(Matriz& matriz, int numeroMatriz);
    void mostrarMatriz(const Matriz& matriz);
};

#endif