#pragma once
#include "Nodo.h"

// Lista Doblemente Enlazada Circular para las Reservas de turno
class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;
public:
    ListaDoble();
    ~ListaDoble();

    void     agregarReserva(Reserva* r);
    void     mostrarReservas();
    Reserva* buscarPorPlaca(std::string placa);
    bool     eliminarReserva(std::string placa);
    void     eliminarCascadaUsuario(std::string cedula);
    void     eliminarCascadaVehiculo(std::string placa);

    // Recorre la lista circularmente e imprime en formato de turno
    void mostrarTurnos();
};
