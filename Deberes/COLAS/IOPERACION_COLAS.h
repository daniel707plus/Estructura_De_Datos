/***********************************************************************
 * Module:  IOPERACION_COLAS.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class IOPERACION_COLAS
 ***********************************************************************/
#ifndef IOPERACION_COLAS_GRUPO_2_H
#define IOPERACION_COLAS_GRUPO_2_H
#include "Persona.h"
#include <string>

class IOPERACION_COLAS {
public:
    virtual ~IOPERACION_COLAS() {} 

  
    virtual void encolar(const Persona& p) = 0;       
    virtual Persona desencolar() = 0;                 
    virtual bool buscar(const std::string& cedulaBuscar) = 0;
    virtual void imprimir() const = 0;
};
#endif