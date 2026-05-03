/***********************************************************************
 * Module:  ListaDoble.cpp
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class ListaDoble
 ***********************************************************************/
#include <iostream>
#include "ListaDoble.h" 

using namespace std;

// Constructor
ListaDoble::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
}

void ListaDoble::insertarInicio(string c, string n) {
    Nodo* nuevo = new Nodo(c, n);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        //nuevo->siguiente = cabeza;
        nuevo->setSiguiente(cabeza);
        //cabeza->anterior = nuevo;
        cabeza->setAnterior(nuevo);
        cabeza = nuevo;
    }
    cout << "Insertado al inicio: " << n << endl;
}

void ListaDoble::insertarFinal(string c, string n) {
    Nodo* nuevo = new Nodo(c, n);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->setSiguiente(nuevo);
        //cola->siguiente = nuevo;
        nuevo->setAnterior(cola);
        //nuevo->anterior = cola;
        cola = nuevo;
    }
    cout << "Insertado al final: " << n << endl;
}

void ListaDoble::insertarEntre(string cedulaRef, string c, string n) {
    Nodo* actual = cabeza;
    while (actual != nullptr && actual->getCedula() != cedulaRef) {
        actual = actual->getSiguiente();
        //actual = actual->siguiente;
    }
    if (actual != nullptr) {
        Nodo* nuevo = new Nodo(c, n);
        nuevo->setSiguiente(actual->getSiguiente());
        //nuevo->siguiente = actual->siguiente;
        nuevo->setAnterior(actual);
        //nuevo->anterior = actual;
        

        if(actual->getSiguiente() != nullptr) {
            actual->getSiguiente()->setAnterior(nuevo);
            //actual->siguiente->anterior = nuevo;
        } else {
            cola = nuevo; 
        }
        actual->setSiguiente(nuevo);
        /*if (actual->siguiente != nullptr) {
            actual->siguiente->anterior = nuevo;
        } else {
            cola = nuevo; 
        }
        actual->siguiente = nuevo;
        cout << "Insertado entre nodos: " << n << endl;*/
    } else {
        cout << "Error: No se encontro la cedula (" << cedulaRef << ")" << endl;
    }
}

void ListaDoble::eliminar(string c) {
    Nodo* actual = cabeza;

    while(actual != nullptr && actual->getCedula() != c) {
        actual = actual->getSiguiente();
    }

    if(actual != nullptr) {
        if(actual->getAnterior() != nullptr) {
            actual->getAnterior()->setSiguiente(actual->getSiguiente());
        } else {
            cabeza = actual->getSiguiente();
        }

        if(actual->getSiguiente() != nullptr) {
            actual->getSiguiente()->setAnterior(actual->getAnterior());
        } else {
            cola = actual->getAnterior();
        }

        delete actual;
        cout << "Nodo con cedula " << c << " eliminado." << endl;
    } else {
        cout << "Error: No se encontro la cedula para eliminar." << endl;
    }
    /*while (actual != nullptr && actual->cedula != c) {
        actual = actual->siguiente;
    }
    if (actual != nullptr) {
        if (actual->anterior != nullptr) {
            actual->anterior->siguiente = actual->siguiente;
        } else {
            cabeza = actual->siguiente;
        }
        if (actual->siguiente != nullptr) {
            actual->siguiente->anterior = actual->anterior;
        } else {
            cola = actual->anterior;
        }
        delete actual;
        cout << "Nodo con cedula " << c << " eliminado." << endl;
    } else {
        cout << "Error: No se encontro la cedula para eliminar." << endl;
    }*/
}

Nodo* ListaDoble::buscar(string c) {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getCedula() == c) {

            cout << "Encontrado -> Cedula: " << actual->getCedula() <<
             " | Nombre: " << actual->getNombre() << endl;

            return actual;
        }
        actual = actual->getSiguiente();
    }
    cout << "La cedula " << c << " no existe." << endl;
    return nullptr;
}


void ListaDoble::imprimir() {
    Nodo* actual = cabeza;
    cout << "\n--- Estado actual de la lista ---" << endl;
    if (actual == nullptr) {
        cout << "La lista esta vacia." << endl;
        return;
    }
    while (actual != nullptr) {
        cout << "[" << actual->getCedula() << " - " << actual->getNombre() << "] <-> ";
        actual = actual->getSiguiente();
    }
    cout << "NULL\n" << endl;
}