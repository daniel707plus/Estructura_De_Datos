/***********************************************************************
 * Module:  Persona.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class Persona
 ***********************************************************************/
#ifndef PERSONA_H
#define PERSONA_H

#include <string>
using namespace std;

class Persona {
private:
    string cedula;
    string nombre;

public:
    Persona(const string &ced, const string &nom);
    Persona(); 

    string getCedula() const;
    string getNombre() const;
};

#endif