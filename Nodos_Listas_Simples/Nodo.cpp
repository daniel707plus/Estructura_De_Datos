#include "Nodo.h"

Nodo::Nodo(std::string cedula, std::string nombre) {
    this->cedula = cedula;
    this->nombre = nombre;
    this->siguiente = nullptr;
}

Nodo::~Nodo() {
}


std::string Nodo::getCedula() const {
     return cedula; 
    }
std::string Nodo::getNombre() const {
     return nombre; 
    }
Nodo* Nodo::getSiguiente() const { 
    return siguiente; 
}


void Nodo::setCedula(std::string cedula) { 
    this->cedula = cedula; 
}
void Nodo::setNombre(std::string nombre) { 
    this->nombre = nombre;
}
void Nodo::setSiguiente(Nodo* siguiente) { 
    this->siguiente = siguiente; 
}