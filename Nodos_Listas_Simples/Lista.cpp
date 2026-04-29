#include "Lista.h"

// Constructor
Lista::Lista() {
    this->cabeza = nullptr;
    this->cola = nullptr;
}

// Destructor para evitar fugas de memoria
Lista::~Lista() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* aEliminar = actual;
        actual = actual->getSiguiente();
        delete aEliminar;
    }
}


Nodo* Lista::getCabeza() const { 
    return cabeza;
}
Nodo* Lista::getCola() const { 
    return cola; 
}


void Lista::setCabeza(Nodo* cabeza) { 
    this->cabeza = cabeza;
 }
void Lista::setCola(Nodo* cola) {
     this->cola = cola;
    }