/***********************************************************************
 * Module:  Salto.h
 * Author:  USUARIO
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class Salto
 ***********************************************************************/
#ifndef SALTO_H
#define SALTO_H

#include <string>

class Salto {
private:
    std::string nombre;
    float intento1;
    float intento2;
    float intento3;
    float mejorIntento;

public:
    Salto(); 

    void setNombre(std::string n);
    void setIntento1(float i);
    void setIntento2(float i);
    void setIntento3(float i);
    void setMejorIntento(float m);

    std::string getNombre() const;
    float getIntento1() const;
    float getIntento2() const;
    float getIntento3() const;
    float getMejorIntento() const;
};

#endif