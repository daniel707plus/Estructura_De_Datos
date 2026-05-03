/***********************************************************************
 * Module:  Quebrado.h
 * Author:  USUARIO
 * Modified: mi�rcoles, 8 de abril de 2026 22:31:12
 * Purpose: Declaration of the class Quebrado
 ***********************************************************************/

#ifndef QUEBRADO_H
#define QUEBRADO_H

template <typename T>
class Quebrado {
private:
    T numerador;
    T denominador;

public:
    Quebrado();
    Quebrado(T num, T den);

    void setNumerador(T num);
    void setDenominador(T den);
    T getNumerador();
    T getDenominador();
};

#include "Quebrado.cpp"

#endif