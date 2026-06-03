#ifndef VEHICULO_H
#define VEHICULO_H

#include "Reserva.h"

class Vehiculo {
private:
    string placa;
    Reserva reserva;  // guarda todos los datos de la reserva (persona + fecha)

public:
    // Punteros para la lista doblemente enlazada
    Vehiculo* siguiente;
    Vehiculo* anterior;

    // Ahora solo se pide la placa, NO el modelo
    Vehiculo(string p);

    string getPlaca();

    // Dice si el vehiculo tiene una reserva activa
    bool estaReservado();

    // Hace la reserva con persona y fecha
    void reservar(Persona per, Fecha f);

    // Cancela la reserva
    void liberar();

    // Devuelve los datos de la reserva
    Reserva getReserva();
};

#endif
