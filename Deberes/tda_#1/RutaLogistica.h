// RutaLogistica.h
#ifndef RUTALOGISTICA_H
#define RUTALOGISTICA_H

#include "NodoEnvio.h"

class RutaLogistica {
private:
    NodoEnvio* cabeza;
public:
    RutaLogistica();
    ~RutaLogistica();
    void agregarPaquete(std::string codigo, std::string destino);
    void auditarRutaExpress() const;
};

#endif