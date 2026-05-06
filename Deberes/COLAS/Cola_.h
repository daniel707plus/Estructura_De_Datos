/***********************************************************************
 * Module:  Cola.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class Cola
 ***********************************************************************/
#ifndef COLA_H
#define COLA_H
#include "IOPERACION_COLA.h"
#include "Nodo.h"

class Cola : public IOPERACION_COLA {
private:
    Nodo* frente; 
    Nodo* final;  
public:
    Cola();
    
    ~Cola(); 


    void encolar(const Persona& p) override;
    Persona desencolar() override;
    bool buscar_G2(const std::string& cedulaBuscar) override;
    void imprimir() const override;
};
#endif