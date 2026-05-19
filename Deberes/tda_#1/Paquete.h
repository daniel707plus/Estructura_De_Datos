// Paquete.h
#ifndef PAQUETE_H
#define PAQUETE_H

#include <string>

class Paquete {
private:
    std::string codigoRastreo;
    std::string ciudadDestino;
public:
    Paquete(std::string codigo, std::string destino);
    std::string getCodigoRastreo() const;
    std::string getCiudadDestino() const;
};

#endif