/***********************************************************************
 * Module:  Pila.h
 * Author:  USUARIO
 * Modified: s�bado, 2 de mayo de 2026 18:58:02
 * Purpose: Declaration of the class Pila
 ***********************************************************************/

#ifndef PILA_H
#define PILA_H

template <typename T>
class Pila {
private:
    T* datos;
    int tope;
    int capacidad;

public:
    Pila(int cap = 100);
    ~Pila();
    
    // Metodos basicos de una Pila
    void push(T valor); // Meter
    void pop();        // Sacar
    T getTope();       // Ver el de arriba
    bool estaVacia();
};

#include "Pila.cpp"
#endif