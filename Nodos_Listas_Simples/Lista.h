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