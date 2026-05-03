/***********************************************************************
 * Module:  ListaSimple.cpp
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class ListaSimple
 ***********************************************************************/
#include <iostream>
#include "ListaSimple.h" 

using namespace std;

ListaSimple::ListaSimple() {
    cabeza = nullptr;
    cola = nullptr;
}

void ListaSimple::insertarInicio(string c, string n) {
    Nodo* nuevo = new Nodo(c, n);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        nuevo->setSiguiente(cabeza);
        cabeza = nuevo;
    }
    cout << "Insertado al inicio: " << n << endl;
}

void ListaSimple::insertarFinal(string c, string n) {
    Nodo* nuevo = new Nodo(c, n);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->setSiguiente(nuevo);
        cola = nuevo;
    }
    cout << "Insertado al final: " << n << endl;
}

void ListaSimple::insertarEntre(string cedulaRef, string c, string n) {
    Nodo* actual = cabeza;
    
    while (actual != nullptr && actual->getCedula() != cedulaRef) {
        actual = actual->getSiguiente();
    }
    
    if (actual != nullptr) {
        Nodo* nuevo = new Nodo(c, n);
        
        nuevo->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(nuevo);
        
        // Si lo insertamos al final de todo, debemos actualizar la cola
        if (nuevo->getSiguiente() == nullptr) {
            cola = nuevo; 
        }
        
        cout << "Insertado entre nodos: " << n << endl;
    } else {
        cout << "Error: No se encontro la cedula (" << cedulaRef << ")" << endl;
    }
}

void ListaSimple::eliminar(string c) {
    Nodo* actual = cabeza;
    Nodo* previo = nullptr; // <--- NUEVO: Nos ayudara a recordar el nodo anterior
    
    // Recorremos la lista buscando la cedula
    while (actual != nullptr && actual->getCedula() != c) {
        previo = actual; // El previo se pone donde esta el actual
        actual = actual->getSiguiente(); // El actual avanza un paso
    }
    
    if (actual != nullptr) { // Si lo encontramos
        if (previo == nullptr) {
            // Significa que estamos eliminando la cabeza (el primer nodo)
            cabeza = actual->getSiguiente();
            if (cabeza == nullptr) {
                cola = nullptr; // Si la lista se quedo vacia
            }
        } else {
            // Conectamos el previo con el siguiente del que vamos a borrar
            previo->setSiguiente(actual->getSiguiente());
            
            // Si estamos borrando el ultimo nodo, la cola retrocede al previo
            if (actual->getSiguiente() == nullptr) {
                cola = previo;
            }
        }
        
        delete actual;
        cout << "Nodo con cedula " << c << " eliminado." << endl;
    } else {
        cout << "Error: No se encontro la cedula para eliminar." << endl;
    }
}

Nodo* ListaSimple::buscar(string c) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getCedula() == c) {
            return actual;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

void ListaSimple::imprimir() {
    Nodo* actual = cabeza;
    cout << "\n--- Estado actual de la lista ---" << endl;
    if (actual == nullptr) {
        cout << "La lista esta vacia." << endl;
        return;
    }
    while (actual != nullptr) {
        cout << "[" << actual->getCedula() << " - " << actual->getNombre() << "] -> ";
        actual = actual->getSiguiente();
    }
    cout << "NULL\n" << endl;
}