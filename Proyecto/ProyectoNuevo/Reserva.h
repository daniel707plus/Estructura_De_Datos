#ifndef RESERVA_H
#define RESERVA_H

#include "Persona.h"
#include "Fecha.h"

// Esta clase guarda toda la informacion de una reserva:
// quien reservo el vehiculo y en que fecha
class Reserva {
private:
    Persona persona;
    Fecha   fecha;
    bool    activa;  // true = hay reserva, false = no hay reserva

public:
    Reserva();
    Reserva(Persona p, Fecha f);

    Persona getPersona();
    Fecha   getFecha();
    bool    estaActiva();

    void activar(Persona p, Fecha f);
    void cancelar();
};

#endif
