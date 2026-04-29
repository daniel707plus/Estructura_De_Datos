#include "Nodo.h"

Nodo::Nodo(std::string cedula, std::string nombre) {
    this->cedula = cedula;
    this->nombre = nombre;
    this->siguiente = nullptr;
    this->anterior = nullptr;
}

Nodo::~Nodo() {
}


std::string Nodo::getCedula() {
     return cedula; 
    }
std::string Nodo::getNombre()  {
     return nombre; 
    }
Nodo* Nodo::getSiguiente() { 
    return siguiente; 
}
Nodo* Nodo::getAnterior() { 
    return anterior; 
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
void Nodo::setAnterior(Nodo* anterior) { 
    this->anterior = anterior; 
}