/***********************************************************************
 * Module:  Salto.cpp
 * Author:  USUARIO
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class Salto
 ***********************************************************************/

#include "Salto.h"

// Inicializamos las variables por seguridad
Salto::Salto() : nombre(""), intento1(0), intento2(0), intento3(0), mejorIntento(0) {}

void Salto::setNombre(std::string n) {
     nombre = n; 
    }
void Salto::setIntento1(float i) {
     intento1 = i; 
    }

void Salto::setIntento2(float i) {
     intento2 = i; 
    }
void Salto::setIntento3(float i) { 
    intento3 = i; 
}
void Salto::setMejorIntento(float m) {
     mejorIntento = m; 
    }

std::string Salto::getNombre() const {
     return nombre; 
    }
float Salto::getIntento1() const {
     return intento1; 
    }
float Salto::getIntento2() const {
     return intento2; 
    }
float Salto::getIntento3() const { 
    return intento3; 
}
float Salto::getMejorIntento() const {
     return mejorIntento; 
    }