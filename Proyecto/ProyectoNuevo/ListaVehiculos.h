#ifndef LISTA_H
#define LISTA_H

#include "Vehiculo.h"

class ListaVehiculos {
private:
    Vehiculo* cabeza;
    Vehiculo* cola;   // puntero al ultimo nodo (necesario para lista doble)

public:
    ListaVehiculos();

    void insertar(string placa);       // ya no recibe modelo
    void eliminar(string placa);
    Vehiculo* buscar(string placa);
    void imprimir();
    void reservarVehiculo(string placa, Persona p, Fecha f);
    void cancelarReserva(string placa);
};

#endif
