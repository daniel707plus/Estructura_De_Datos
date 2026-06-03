#pragma once
#include "Nodo.h"
#include <cstdint>

class ListaDoble {
private:
    Nodo* cabeza;
    Nodo* cola;
public:
    ListaDoble();
    ~ListaDoble();
    void agregarReserva(Reserva* r);
    void mostrarReservas() const;
    Reserva* buscarPorPlaca(std::string placa) const;
    bool eliminarReserva(std::string placa);
    void eliminarCascadaUsuario(std::string cedula);
    void eliminarCascadaVehiculo(std::string placa);

    bool hayCruceDeHorarios(int dia, int mes,
         int anio, int hIniNuevo, int mIniNuevo,
          int hFinNuevo, int mFinNuevo) const;


    Nodo* getCabeza() const;
};

template <typename T>
void ordenarListaInterno(T* cabeza, int criterio) {
    if (!cabeza) return;

    // Punteros puros para el recorrido 
    for (T* i = cabeza; i != nullptr; i = i->getSiguiente()) {
        for (T* j = i->getSiguiente(); j != nullptr; j = j->getSiguiente()) {
            
            Reserva* r1 = i->getReserva();
            Reserva* r2 = j->getReserva();
            bool debaIntercambiar = false;

            // Selección de criterio de forma interna (Como en Windows)
            if (criterio == 1) {        // Nombre
                debaIntercambiar = (r1->getUsuario()->getNombre() > r2->getUsuario()->getNombre());
            } else if (criterio == 2) { // Placa
                debaIntercambiar = (r1->getVehiculo()->getPlaca() > r2->getVehiculo()->getPlaca());
            } else if (criterio == 3) { // Cédula
                debaIntercambiar = (r1->getUsuario()->getCedula() > r2->getUsuario()->getCedula());
            } else if (criterio == 4) { // Fecha
                std::tm f1 = r1->getFechaAsignada();
                std::tm f2 = r2->getFechaAsignada();
                if (f1.tm_year != f2.tm_year) {
                    debaIntercambiar = (f1.tm_year > f2.tm_year);
                } else if (f1.tm_mon != f2.tm_mon) {
                    debaIntercambiar = (f1.tm_mon > f2.tm_mon);
                } else {
                    debaIntercambiar = (f1.tm_mday > f2.tm_mday);
                }
            } else if (criterio == 5) { // Apellido
                debaIntercambiar = (r1->getUsuario()->getApellido() > r2->getUsuario()->getApellido());
            }

            if (debaIntercambiar) {
                // INTERCAMBIO POR BITS SIN VARIABLES AUXILIARES (XOR Swap algoritmo)
                // Convertimos las direcciones de los punteros a enteros de tamaño nativo (uintptr_t)
                uintptr_t p1 = reinterpret_cast<uintptr_t>(r1);
                uintptr_t p2 = reinterpret_cast<uintptr_t>(r2);

                // Triple XOR para intercambiar los valores sin usar una variable temporal 'aux'
                p1 ^= p2;
                p2 ^= p1;
                p1 ^= p2;

                // Devolvemos los punteros modificados a los nodos mediante el setter puro
                i->setReserva(reinterpret_cast<Reserva*>(p1));
                j->setReserva(reinterpret_cast<Reserva*>(p2));
            }
        }
    }
}
