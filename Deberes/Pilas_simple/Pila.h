/***********************************************************************
 * Module:  Pila.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class Pila
 ***********************************************************************/
#ifndef PILA_H
#define PILA_H

#include "IOPERACION_PILAS_GRUPO2.h"
#include "Nodo.h"

class Pila : public IOPERACION_PILAS_GRUPO2{
private:
    Nodo* cima;

public:
    Pila();
    ~Pila(); 

    bool estaVacia() const;

    
    void insertar(const Persona& p) override;
    Persona eliminar() override;
    bool buscar(const std::string& cedula) override;
    void imprimir() const override;
};

#endif