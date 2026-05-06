/***********************************************************************
 * Module:  Nodo.cpp
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class Nodo
 ***********************************************************************/
#include "Nodo.h"

Nodo::Nodo(Persona p) : dato(p), siguiente(nullptr) {}

Persona Nodo::getDato() const {
    return dato;
 }
void Nodo::setDato(Persona p) {
     dato = p;
     }

Nodo* Nodo::getSiguiente() const { 
    return siguiente; 
}
void Nodo::setSiguiente(Nodo* sig) {
     siguiente = sig;
     }