/***********************************************************************
 * Module:  Nodo.h
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Declaration of the class Nodo
 ***********************************************************************/
#pragma once
#include <string>

class Nodo {
private:
    std::string cedula;
    std::string nombre;
    Nodo* siguiente;

public:
    
    Nodo(std::string cedula, std::string nombre);
    ~Nodo();

    
    std::string getCedula() const;
    std::string getNombre() const;
    Nodo* getSiguiente() const;

    
    void setCedula(std::string cedula);
    void setNombre(std::string nombre);
    void setSiguiente(Nodo* siguiente);
};