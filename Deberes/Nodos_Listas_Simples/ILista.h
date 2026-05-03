/***********************************************************************
 * Module:  ILista.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class ILista
 ***********************************************************************/
#pragma once
#include "Lista.h"
#include <string>

class ILista {
private:
    Lista* lista;
public:
    ILista(Lista* lista);
    virtual ~ILista() = default;
    virtual void insertarCabeza(std::string cedula,
         std::string nombre) = 0;
};