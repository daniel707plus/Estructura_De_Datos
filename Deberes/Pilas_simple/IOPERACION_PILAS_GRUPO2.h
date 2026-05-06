/***********************************************************************
 * Module:  IOPERACION_PILAS_GRUPO2.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class IOPERACION_PILAS_GRUPO2
 ***********************************************************************/
#ifndef IOPERACION_PILAS_GRUPOO2_H
#define IOPERACION_PILAS_GRUPOO2_H

#include "Persona.h"
#include <string>

class IOPERACION_PILAS_GRUPO2{
public:
    
    virtual ~IOPERACION_PILAS_GRUPO2() {} 

    virtual void insertar(const Persona& p) = 0; // Push
    virtual Persona eliminar() = 0;       // Pop
    virtual bool buscar(const std::string& cedula) = 0;
    virtual void imprimir() const = 0;
};

#endif