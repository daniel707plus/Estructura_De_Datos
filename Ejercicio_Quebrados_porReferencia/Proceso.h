/***********************************************************************
 * Module:  Proceso.h
 * Author:  USUARIO
 * Modified: mi�rcoles, 8 de abril de 2026 22:25:43
 * Purpose: Declaration of the class Proceso
 ***********************************************************************/

#ifndef PROCESO_H
#define PROCESO_H
#include "Quebrado.h"

class Proceso {
public:
    Quebrado sumar(const Quebrado& q1, const Quebrado& q2);
    void mostrar(const Quebrado& q);
};
#endif 