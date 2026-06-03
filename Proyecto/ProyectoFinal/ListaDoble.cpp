#include "ListaDoble.h"
#include <iostream>

ListaDoble::ListaDoble() { cabeza = nullptr; cola = nullptr; }

ListaDoble::~ListaDoble() {
    if (!cabeza) return;
    // Romper la circularidad antes de liberar
    cola->setSiguiente(nullptr);
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* aBorrar = actual;
        actual = actual->getSiguiente();
        delete aBorrar;
    }
}

// Agrega al final y cierra el circulo
void ListaDoble::agregarReserva(Reserva* r) {
    Nodo* nuevo = new Nodo(r);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola   = nuevo;
        // Circular: apunta a si mismo
        nuevo->setSiguiente(cabeza);
        nuevo->setAnterior(cola);
    } else {
        nuevo->setAnterior(cola);
        nuevo->setSiguiente(cabeza);   // cierre circular
        cola->setSiguiente(nuevo);
        cabeza->setAnterior(nuevo);    // cabeza apunta atras al nuevo
        cola = nuevo;
    }
}

void ListaDoble::mostrarReservas() {
    if (!cabeza) { std::cout << "  No hay reservas registradas.\n"; return; }
    std::cout << "\n--- REGISTRO DE RESERVAS DE TURNO ---\n";
    Nodo* actual = cabeza;
    int turno = 1;
    do {
        Reserva* res = actual->getReserva();
        std::tm f    = res->getFechaAsignada();
        const char* diasSemana[] = {"Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};
        std::cout << "Turno #" << turno++ << "\n";
        std::cout << "  Propietario : " << res->getUsuario()->getNombre()
                  << " " << res->getUsuario()->getApellido()
                  << "  |  CI: " << res->getUsuario()->getCedula() << "\n";
        std::cout << "  Vehiculo    : " << res->getVehiculo()->getPlaca() << "\n";
        std::cout << "  Fecha       : " << diasSemana[f.tm_wday] << " "
                  << f.tm_mday << "/" << (f.tm_mon+1) << "/" << (f.tm_year+1900) << "\n";
        std::cout << "  -----------------------------------\n";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

Reserva* ListaDoble::buscarPorPlaca(std::string placa) {
    if (!cabeza) return nullptr;
    Nodo* actual = cabeza;
    do {
        if (actual->getReserva()->getVehiculo()->getPlaca() == placa)
            return actual->getReserva();
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    return nullptr;
}

bool ListaDoble::eliminarReserva(std::string placa) {
    if (!cabeza) return false;
    Nodo* actual = cabeza;
    do {
        if (actual->getReserva()->getVehiculo()->getPlaca() == placa) {
            // Solo un nodo
            if (actual->getSiguiente() == actual) {
                cabeza = nullptr;
                cola   = nullptr;
            } else {
                actual->getAnterior()->setSiguiente(actual->getSiguiente());
                actual->getSiguiente()->setAnterior(actual->getAnterior());
                if (actual == cabeza) cabeza = actual->getSiguiente();
                if (actual == cola)   cola   = actual->getAnterior();
            }
            // Aislar el nodo antes de borrarlo (evitar doble free en destructor)
            actual->setSiguiente(nullptr);
            actual->setAnterior(nullptr);
            delete actual;
            return true;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    return false;
}

void ListaDoble::eliminarCascadaUsuario(std::string cedula) {
    if (!cabeza) return;
    Nodo* actual = cabeza;
    // Recolectar placas a eliminar (no modificar lista mientras se recorre)
    std::string placas[100]; int total = 0;
    do {
        if (actual->getReserva()->getUsuario()->getCedula() == cedula)
            placas[total++] = actual->getReserva()->getVehiculo()->getPlaca();
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    for (int i = 0; i < total; i++) eliminarReserva(placas[i]);
}

void ListaDoble::eliminarCascadaVehiculo(std::string placa) {
    eliminarReserva(placa);
}

void ListaDoble::mostrarTurnos() {
    mostrarReservas(); // reutiliza la misma logica
}
