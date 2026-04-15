/***********************************************************************
 * Module:  Quebrado.cpp
 * Author:  USUARIO
 * Modified: mi�rcoles, 8 de abril de 2026 22:31:12
 * Purpose: Implementation of the class Quebrado
 ***********************************************************************/

#include "Quebrado.h"

template <typename T>

Quebrado<T>::Quebrado() {
    numerador = 0;
    denominador = 1;
}

template <typename T>
Quebrado<T>::Quebrado(T n, T d) {
    numerador = n;
    denominador =  d; 
}
template <typename T>
void Quebrado<T>::setNumerador(T n) { 
    numerador = n; 
}
template <typename T>

void Quebrado<T>::setDenominador(T d) {
     denominador = d; 
}
template <typename T>
T Quebrado<T>::getNumerador(){
     return numerador;
}
template <typename T>
T Quebrado<T>::getDenominador() { 
    return denominador; 
}
