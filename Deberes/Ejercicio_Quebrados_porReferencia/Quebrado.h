/***********************************************************************
 * Module:  Quebrado.h
 * Author:  USUARIO
 * Modified: mi�rcoles, 8 de abril de 2026 22:31:12
 * Purpose: Declaration of the class Quebrado
 ***********************************************************************/

#ifndef QUEBRADO_H
#define QUEBRADO_H

class Quebrado {
private:
    float numerador;
    float denominador;

public:
    Quebrado();
    Quebrado(float num, float den);

    void setNumerador(float num);
    void setDenominador(float den);
    float getNumerador() const;
    float getDenominador() const;
};

#endif