#include "Vehiculo.h"

Vehiculo::Vehiculo( const std::string& pla) {
    placa = pla;
}

const std::string& Vehiculo::getPlaca() const {
    return placa;
}

void Vehiculo::setPlaca(const std::string& pla) {
    placa = pla;
}