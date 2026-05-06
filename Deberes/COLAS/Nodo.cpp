/***********************************************************************
 * Module:  Nodo.cpp
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class Nodo
 ***********************************************************************/
#include "Nodo.h"

Nodo::Nodo(const Persona& p) {
    this->dato = p;
    this->siguiente = nullptr;
}

Persona Nodo::getDato() const {
     return this->dato;
    }
Nodo* Nodo::getSiguiente() const {
     return this->siguiente;
     }
void Nodo::setSiguiente(Nodo* sig) {
     this->siguiente = sig; 
    }