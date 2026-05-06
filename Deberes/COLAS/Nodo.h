/***********************************************************************
 * Module:  Nodo.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class Nodo
 ***********************************************************************/
#ifndef NODO_H
#define NODO_H
#include "Persona.h"

class Nodo {
private:
    Persona dato;
    Nodo* siguiente;

public:
    Nodo(const Persona& p);

    Persona getDato() const;
    Nodo* getSiguiente() const;
    void setSiguiente(Nodo* sig);
};
#endif