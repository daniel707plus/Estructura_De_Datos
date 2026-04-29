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