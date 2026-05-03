/***********************************************************************
 * Module:  Nodo.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class Nodo
 ***********************************************************************/
#ifndef NODO_H
#define NODO_H

#include <string>
using namespace std;

class Nodo {
    
private:
    string cedula;
    string nombre;
    Nodo* siguiente;
    Nodo* anterior;

public:
    Nodo(string, string);
    ~Nodo();

    void setCedula(string);
    void setNombre(string);
    void setSiguiente(Nodo*);
    void setAnterior(Nodo*);
    string getCedula();
    string getNombre();
    Nodo* getSiguiente();
    Nodo* getAnterior();
};

#endif