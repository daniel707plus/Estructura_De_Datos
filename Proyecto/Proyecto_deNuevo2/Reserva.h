#pragma once
#include <ctime>
#include "Usuario.h"
#include "Vehiculo.h"

class Reserva {
private:
    Usuario* usuario;
    Vehiculo* vehiculo;
    std::tm fechaAsignada; 
public:
    Reserva(Usuario* u, Vehiculo* v, std::tm f);
    ~Reserva(); 

    Usuario* getUsuario() const;
    Vehiculo* getVehiculo() const;
    std::tm getFechaAsignada() const;
    void setFechaAsignada(std::tm f);
};