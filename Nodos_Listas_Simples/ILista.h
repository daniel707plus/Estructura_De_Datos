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