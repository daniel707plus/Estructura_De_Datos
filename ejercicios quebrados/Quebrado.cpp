/***********************************************************************
 * Module:  Quebrado.cpp
 * Author:  USUARIO
 * Modified: mi�rcoles, 8 de abril de 2026 22:31:12
 * Purpose: Implementation of the class Quebrado
 ***********************************************************************/

#include "Quebrado.h"

Quebrado::Quebrado() {
    numerador = 0;
    denominador = 1;
}
Quebrado::Quebrado(float n, float d) {
    numerador = n;
    denominador =  d; 
}

void Quebrado::setNumerador(float n) { 
    numerador = n; 
}
void Quebrado::setDenominador(float d) {
     denominador = d; 
}
float Quebrado::getNumerador(){
     return numerador;
}
float Quebrado::getDenominador() { 
    return denominador; 
}
