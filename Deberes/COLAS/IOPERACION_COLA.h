/***********************************************************************
 * Module:  IOPERACION_COLA.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class IOPERACION_COLA
 ***********************************************************************/
#ifndef IOPERACION_COLA_H
#define IOPERACION_COLA_H
#include "Persona.h"
#include <string>

class IOPERACION_COLA {
public:
    virtual ~IOPERACION_COLA() {} 

    virtual void encolar(const Persona& p) = 0;       
    virtual Persona desencolar() = 0;            
    virtual bool buscar_G2(const std::string& cedulaBuscar) = 0;
    virtual void imprimir() const = 0;
};
#endif