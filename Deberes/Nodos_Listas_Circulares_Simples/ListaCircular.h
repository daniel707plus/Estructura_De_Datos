/***********************************************************************
 * Module:  ListaCircular.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class ListaCircular
 ***********************************************************************/
#pragma once
#include <string>
#include "Nodo.h"

using namespace std;

class ListaCircular {
private:
    Nodo* cabeza;
    Nodo* cola;

public:
    ListaCircular();

    void insertarInicio(string c, string n);
    void insertarFinal(string c, string n);
    void insertarEntre(string cedulaRef, string c, string n);
    void eliminar(string c);
    Nodo* buscar(string c);
    void imprimir();
    int contarTerminanEn39();
};