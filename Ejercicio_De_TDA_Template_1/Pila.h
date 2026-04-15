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