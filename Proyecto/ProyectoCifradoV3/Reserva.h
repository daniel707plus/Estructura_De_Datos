#pragma once
#include <ctime>
#include "Usuario.h"
#include "Vehiculo.h"

class Reserva {
private:
    Usuario* usuario;
    Vehiculo* vehiculo;
    std::tm fechaAsignada; 
    int hInicio;
    int mInicio;
    int hFin;
    int mFin;

public:
    Reserva(Usuario* u, Vehiculo* v, std::tm f, int hi, int mi, int hf, int mf);
    ~Reserva(); 

    Usuario* getUsuario() const;
    Vehiculo* getVehiculo() const;
    std::tm getFechaAsignada() const;
    void setFechaAsignada(std::tm f);
    int getHInicio() const;
    int getMInicio() const;
    int getHFin() const;
    int getMFin() const;
};