/***********************************************************************
 * Module:  ProcesoExpresion.h
 * Author:  USUARIO
 * Modified: s�bado, 2 de mayo de 2026 18:55:48
 * Purpose: Declaration of the class ProcesoExpresion
 ***********************************************************************/

#ifndef PROCESOEXPRESION_H
#define PROCESOEXPRESION_H

#include <string>
#include "Pila.h"

class ProcesoExpresion {
public:
    bool validarParentesis(std::string expresion);
};

#include "ProcesoExpresion.cpp"
#endif