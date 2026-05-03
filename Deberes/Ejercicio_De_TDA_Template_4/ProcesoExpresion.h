/***********************************************************************
 * Module:  ProcesoExpresion.h
 * Author:  USUARIO
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class ProcesoExpresion
 ***********************************************************************/
#ifndef PROCESOEXPRESION_H
#define PROCESOEXPRESION_H

#include <string>
#include "Pila.h"

class ProcesoExpresion {
public:
    // Retorna la expresión en notación postfija
    std::string convertirAPostfijo(std::string expresion);
};

#include "ProcesoExpresion.cpp"
#endif