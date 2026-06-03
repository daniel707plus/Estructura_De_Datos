#include "ListaDoble.h"
#include <iostream>

ListaDoble::ListaDoble() { cabeza = nullptr; cola = nullptr; }
ListaDoble::~ListaDoble() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* aBorrar = actual;
        actual = actual->getSiguiente();
        delete aBorrar;
    }
}
void ListaDoble::agregarReserva(Reserva* r) {
    Nodo* nuevoNodo = new Nodo(r);
    if (cabeza == nullptr) { cabeza = nuevoNodo; cola = nuevoNodo; }
    else { cola->setSiguiente(nuevoNodo); nuevoNodo->setAnterior(cola); cola = nuevoNodo; }
}
void ListaDoble::mostrarReservas() {
    Nodo* actual = cabeza;
    if(!actual) { std::cout << "No hay reservas registradas.\n"; return; }
    std::cout << "\n--- REGISTRO OFICIAL DE RESERVAS ---\n";
    while (actual != nullptr) {
        std::cout << "Cliente: " << actual->getReserva()->getUsuario()->getNombre() <<
         "\t"<< actual->getReserva()->getUsuario()->getApellido() << " | CI: " << actual->getReserva()->getUsuario()->getCedula() << "\n";
        std::cout << "Vehiculo Placa: " << actual->getReserva()->getVehiculo()->getPlaca() << "\n";
        std::tm f = actual->getReserva()->getFechaAsignada();
        std::cout << "Fecha: " << f.tm_mday << "/" << f.tm_mon+1 << "/" << f.tm_year+1900 << "\n------------------------------------\n";
        actual = actual->getSiguiente();
    }
}
Reserva* ListaDoble::buscarPorPlaca(std::string placa) {
    Nodo* actual = cabeza;
    while(actual != nullptr) {
        if(actual->getReserva()->getVehiculo()->getPlaca() == placa) return actual->getReserva();
        actual = actual->getSiguiente();
    }
    return nullptr;
}
bool ListaDoble::eliminarReserva(std::string placa) {
    Nodo* actual = cabeza;
    while(actual != nullptr) {
        if(actual->getReserva()->getVehiculo()->getPlaca() == placa) {
            if(actual->getAnterior()) actual->getAnterior()->setSiguiente(actual->getSiguiente());
            else cabeza = actual->getSiguiente();
            if(actual->getSiguiente()) actual->getSiguiente()->setAnterior(actual->getAnterior());
            else cola = actual->getAnterior();
            delete actual; return true;
        }
        actual = actual->getSiguiente();
    }
    return false;
}
void ListaDoble::eliminarCascadaUsuario(std::string cedula) {
    Nodo* actual = cabeza;
    while(actual != nullptr) {
        Nodo* siguiente = actual->getSiguiente();
        if(actual->getReserva()->getUsuario()->getCedula() == cedula) {
            eliminarReserva(actual->getReserva()->getVehiculo()->getPlaca());
        }
        actual = siguiente;
    }
}
void ListaDoble::eliminarCascadaVehiculo(std::string placa) {
    eliminarReserva(placa);
}
