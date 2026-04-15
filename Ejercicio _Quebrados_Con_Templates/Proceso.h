/***********************************************************************
 * Module:  Proceso.h
 * Author:  USUARIO
 * Modified: mi�rcoles, 8 de abril de 2026 22:25:43
 * Purpose: Declaration of the class Proceso
 ***********************************************************************/

#ifndef PROCESO_H
#define PROCESO_H
#include "Quebrado.h"

template <typename T>  
class Proceso {
public:
    Quebrado<T> sumar(Quebrado<T> q1, Quebrado<T> q2);
    void mostrar(Quebrado<T> q);
};
#include "Proceso.cpp"
#endif 