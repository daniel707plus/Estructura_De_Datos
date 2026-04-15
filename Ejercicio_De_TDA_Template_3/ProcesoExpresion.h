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