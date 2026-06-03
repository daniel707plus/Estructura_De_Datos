#include "Reserva.h"

Reserva::Reserva(Usuario* u, Vehiculo* v, std::tm f, int hi, int mi, int hf, int mf) {
    usuario = u;
    vehiculo = v;
    fechaAsignada = f;
    hInicio = hi;
    mInicio = mi;
    hFin = hf;
    mFin = mf;
}
Reserva::~Reserva() {
}

Usuario* Reserva::getUsuario() const {
     return usuario; 
    }
Vehiculo* Reserva::getVehiculo() const {
     return vehiculo; 
    }
std::tm Reserva::getFechaAsignada() const {
     return fechaAsignada; 
    }
void Reserva::setFechaAsignada(std::tm f) {
     fechaAsignada = f; 
    }

int Reserva::getHInicio() const {
    return hInicio;
}
int Reserva::getMInicio() const {
    return mInicio;
}   
int Reserva::getHFin() const {
    return hFin;
}   
int Reserva::getMFin() const {
    return mFin;
}
