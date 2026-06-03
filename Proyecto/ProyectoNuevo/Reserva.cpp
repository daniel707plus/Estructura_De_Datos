#include "Reserva.h"

Reserva::Reserva() {
    activa = false;
}

Reserva::Reserva(Persona p, Fecha f) {
    persona = p;
    fecha   = f;
    activa  = true;
}

Persona Reserva::getPersona() {
    return persona;
}

Fecha Reserva::getFecha() {
    return fecha;
}

bool Reserva::estaActiva() {
    return activa;
}

void Reserva::activar(Persona p, Fecha f) {
    persona = p;
    fecha   = f;
    activa  = true;
}

void Reserva::cancelar() {
    activa = false;
}
