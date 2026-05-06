/***********************************************************************
 * Module:  Pila.cpp
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class Pila
 ***********************************************************************/
#include "Pila.h"
#include <iostream>
#include <stdexcept>

Pila::Pila() : cima(nullptr) {}

Pila::~Pila() {
    while (!estaVacia()) {
        eliminar(); 
    }
}

bool Pila::estaVacia() const {
    return cima == nullptr;
}

void Pila::insertar(const Persona& p) {
    Nodo* nuevoNodo = new Nodo(p);
    nuevoNodo->setSiguiente(cima);
    cima = nuevoNodo;
}

Persona Pila::eliminar() {
    if (estaVacia()) {
        throw std::runtime_error("Error: La pila esta vacia.");
    }
    
    Nodo* aux = cima;
    Persona dato = aux->getDato();
    
    cima = cima->getSiguiente();
    delete aux; 
    
    return dato;
}


bool Pila::buscar(const std::string& cedula) {
    Pila pilaAuxiliar;
    bool encontrado = false;

    while (!estaVacia()) {
        Persona actual = eliminar();
        pilaAuxiliar.insertar(actual); 
        
        if (actual.getCedula() == cedula) {
            encontrado = true;
            break; 
        }
    }

    while (!pilaAuxiliar.estaVacia()) {
        insertar(pilaAuxiliar.eliminar());
    }

    return encontrado;
}


void Pila::imprimir() const {
    if (estaVacia()) {
        std::cout << "La pila esta vacia.\n";
        return;
    }

    Nodo* actual = cima;
    std::cout << "--- ESTADO DE LA PILA (Cima a Base) ---\n";
    while (actual != nullptr) {
        std::cout << "Cedula: " << actual->getDato().getCedula() 
                  << " | Nombre: " << actual->getDato().getNombre() << "\n";
        actual = actual->getSiguiente();
    }
    std::cout << "---------------------------------------\n";
}