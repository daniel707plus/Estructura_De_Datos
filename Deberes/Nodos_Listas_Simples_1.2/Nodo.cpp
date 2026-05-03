/***********************************************************************
 * Module:  Nodo.cpp
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class Nodo
 ***********************************************************************/
#include "Nodo.h"

Nodo::Nodo(string c, string n) {
    cedula = c;
    nombre = n;
    siguiente = nullptr;
}

void Nodo::setCedula(string c) {
     cedula = c;
     }
void Nodo::setNombre(string n) {
     nombre = n; 
    }
void Nodo::setSiguiente(Nodo* sig) { 
    siguiente = sig;
 }

string Nodo::getCedula() { 
    return cedula; 
}
string Nodo::getNombre() { 
    return nombre; 
}
Nodo* Nodo::getSiguiente() {
     return siguiente;    
}