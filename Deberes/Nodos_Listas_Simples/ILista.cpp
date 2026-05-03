/***********************************************************************
 * Module:  ILista.cpp
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class ILista
 ***********************************************************************/
#include "ILista.h"

ILista::ILista(Lista* lista) {
    this->lista = lista;
}

ILista::~ILista() {}

void ILista::insertarCabeza(std::string cedula, std::string nombre) {
   
    Nodo* nuevo = new Nodo(cedula, nombre);

    if (lista->getCabeza() == nullptr) {
        lista->setCabeza(nuevo);
        lista->setCola(nuevo);
    } 
  
    else {
        nuevo->setSiguiente(lista->getCabeza());
        lista->setCabeza(nuevo);
    }
}