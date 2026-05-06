/***********************************************************************
 * Module:  Persona.cpp
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class Persona
 ***********************************************************************/
#include "Persona.h"

using namespace std;

Persona::Persona(const string &ced, const string &nom) : cedula(ced), nombre(nom) {}
Persona::Persona() : cedula(""), nombre("") {}

string Persona::getCedula() const {
     return cedula;
     }
string Persona::getNombre() const {
     return nombre;
     }