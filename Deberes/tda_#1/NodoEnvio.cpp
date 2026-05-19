// NodoEnvio.cpp
#include "NodoEnvio.h"

NodoEnvio::NodoEnvio(Paquete* p) {
    this->paquete = p;
    this->siguiente = nullptr;
}

NodoEnvio::~NodoEnvio() {
    delete paquete; // Cuando se destruye el nodo, también se destruye el paquete
}

Paquete* NodoEnvio::getPaquete() const { return paquete; }
NodoEnvio* NodoEnvio::getSiguiente() const { return siguiente; }
void NodoEnvio::setSiguiente(NodoEnvio* sig) { this->siguiente = sig; }