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