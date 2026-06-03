#pragma once
#include "Nodo.h"

class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;
public:
    ListaDoble();
    ~ListaDoble();
    void agregarReserva(Reserva* r);
    void mostrarReservas();
    Reserva* buscarPorPlaca(std::string placa);
    bool eliminarReserva(std::string placa);
    void eliminarCascadaUsuario(std::string cedula); // Evita punteros huérfanos
    void eliminarCascadaVehiculo(std::string placa);
};