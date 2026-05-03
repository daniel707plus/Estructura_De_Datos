/***********************************************************************
 * Module:  Proceso.cpp
 * Author:  USUARIO
 * Modified: s�bado, 2 de mayo de 2026 19:31:35
 * Purpose: Implementation of the class Proceso
 ***********************************************************************/

#include "Proceso.h"
#include <iostream>

using namespace std;

Matriz operator+(const Matriz& a, const Matriz& b) {

    Matriz resultado(a.getFilas(), a.getColumnas());

    for (int i = 0; i < a.getFilas(); i++) {
        for (int j = 0; j < a.getColumnas(); j++) {
            int suma = a.getDato(i, j) + b.getDato(i, j);
            resultado.setDato(i, j, suma);
        }
    }
    return resultado;
}

void Proceso::pedirDatosMatriz(Matriz& matriz, int numeroMatriz) {

    cout << "\n- Matriz " << numeroMatriz << " ---" << endl;

    for (int i = 0; i < matriz.getFilas(); i++) {
        for (int j = 0; j < matriz.getColumnas(); j++) {
            int valor;
            cout << "Ingrese valor para posicion [" << i << "][" << j << "]: ";
            cin >> valor;
            matriz.setDato(i, j, valor);
        }
    }
}

void Proceso::mostrarMatriz(const Matriz& matriz) {
    for (int i = 0; i < matriz.getFilas(); i++) {
        for (int j = 0; j < matriz.getColumnas(); j++) {
            
            cout << matriz.getDato(i, j) << "\t";
        }
        cout << endl;
    }
}