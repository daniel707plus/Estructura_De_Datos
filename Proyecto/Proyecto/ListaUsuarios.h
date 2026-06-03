#pragma once
#include "Usuario.h"
#include <stdexcept>
#include <string>

class NodoUsuario {
private:
    Usuario* usuario;
    NodoUsuario* siguiente;
public:
    NodoUsuario(Usuario* u);
    ~NodoUsuario();
    Usuario* getUsuario();
    NodoUsuario* getSiguiente();
    void setSiguiente(NodoUsuario* sig);
};

class ListaUsuarios {
private:
    NodoUsuario* cabeza;

    // Imprime la lista igual que en el ejemplo original
    void imprimir() const;

public:
    ListaUsuarios();
    ~ListaUsuarios();
    void crear(Usuario* u);
    void reportar() const;

    Usuario* buscar(std::string cedula) const;

    // Busqueda con try/catch
    Usuario* buscarConExcepcion(std::string cedula) const;

    bool actualizar(std::string cedula, std::string nuevoNom, std::string nuevoApe);
    bool eliminar(std::string cedula);

    // Ordenamiento por INTERCAMBIO con animacion en vivo
    void ordenamientoIntercambio();

    NodoUsuario* getCabeza() const;
};
