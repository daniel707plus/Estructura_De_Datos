// Paquete.cpp
#include "Paquete.h"

Paquete::Paquete(std::string codigo, std::string destino) {
    this->codigoRastreo = codigo;
    this->ciudadDestino = destino;
}

std::string Paquete::getCodigoRastreo() const { return codigoRastreo; }
std::string Paquete::getCiudadDestino() const { return ciudadDestino; }