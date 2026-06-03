#include "Vehiculo.h"

// El constructor solo recibe la placa, ya no el modelo
Vehiculo::Vehiculo(string p) {
    placa     = p;
    siguiente = NULL;
    anterior  = NULL;
    // reserva empieza sin activar (el constructor de Reserva lo hace solo)
}

string Vehiculo::getPlaca() {
    return placa;
}

bool Vehiculo::estaReservado() {
    return reserva.estaActiva();
}

void Vehiculo::reservar(Persona per, Fecha f) {
    reserva.activar(per, f);
}

void Vehiculo::liberar() {
    reserva.cancelar();
}

Reserva Vehiculo::getReserva() {
    return reserva;
}
