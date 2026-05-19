// NodoEnvio.h
#ifndef NODOENVIO_H
#define NODOENVIO_H

#include "Paquete.h"

class NodoEnvio {
private:
    Paquete* paquete; // Puntero al objeto (Cero structs)
    NodoEnvio* siguiente;
public:
    NodoEnvio(Paquete* p);
    ~NodoEnvio(); // Importante para limpiar la RAM
    Paquete* getPaquete() const;
    NodoEnvio* getSiguiente() const;
    void setSiguiente(NodoEnvio* sig);
};

#endif