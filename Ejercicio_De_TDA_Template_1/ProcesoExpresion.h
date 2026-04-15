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