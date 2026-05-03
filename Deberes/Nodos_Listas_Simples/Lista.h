/***********************************************************************
 * Module:  Lista.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class Lista
 ***********************************************************************/
#pragma once
#include "Nodo.h"

class Lista {
private:
    Nodo* cabeza;
    Nodo* cola;

public:
  
    Lista();
    ~Lista();

   
    Nodo* getCabeza() const;
    Nodo* getCola() const;


    void setCabeza(Nodo* cabeza);
    void setCola(Nodo* cola);
};