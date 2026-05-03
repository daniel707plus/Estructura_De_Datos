/***********************************************************************
 * Module:  Proceso.cpp
 * Author:  USUARIO
 * Modified: mi�rcoles, 8 de abril de 2026 22:25:43
 * Purpose: Declaration of the class Proceso
 ***********************************************************************/

#include "Proceso.h"
#include <iostream>
using namespace std;

Quebrado Proceso::sumar(const Quebrado& q1, const Quebrado& q2) {
    
    float num = q1.getNumerador() * q2.getDenominador() + q2.getNumerador() * q1.getDenominador();
    float den = q1.getDenominador() * q2.getDenominador();
    Quebrado resultado;
    resultado.setNumerador(num);
    resultado.setDenominador(den);
    return resultado;
}

void Proceso::mostrar(const Quebrado& q) {
    cout << q.getNumerador() << "/" << q.getDenominador() <<endl;
}
