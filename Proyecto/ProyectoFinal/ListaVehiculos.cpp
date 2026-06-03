#include "ListaVehiculos.h"
#include <iostream>

NodoVehiculo::NodoVehiculo(Vehiculo* v) { vehiculo = v; siguiente = nullptr; }
NodoVehiculo::~NodoVehiculo() { delete vehiculo; }
Vehiculo*     NodoVehiculo::getVehiculo()   { return vehiculo;   }
NodoVehiculo* NodoVehiculo::getSiguiente()  { return siguiente;  }
void          NodoVehiculo::setSiguiente(NodoVehiculo* sig) { siguiente = sig; }

ListaVehiculos::ListaVehiculos() { cabeza = nullptr; }
ListaVehiculos::~ListaVehiculos() {
    NodoVehiculo* actual = cabeza;
    while (actual != nullptr) {
        NodoVehiculo* borrar = actual;
        actual = actual->getSiguiente();
        delete borrar;
    }
}

void ListaVehiculos::crear(Vehiculo* v) {
    NodoVehiculo* nuevo = new NodoVehiculo(v);
    nuevo->setSiguiente(cabeza);
    cabeza = nuevo;
}

void ListaVehiculos::reportar() {
    NodoVehiculo* temp = cabeza;
    if (!temp) { std::cout << "  No hay vehiculos registrados.\n"; return; }
    std::cout << "\n--- LISTA DE VEHICULOS ---\n";
    int num = 1;
    while (temp != nullptr) {
        std::cout << num++ << ". Placa: " << temp->getVehiculo()->getPlaca() << "\n";
        temp = temp->getSiguiente();
    }
}

Vehiculo* ListaVehiculos::buscar(std::string placa) {
    NodoVehiculo* temp = cabeza;
    while (temp != nullptr) {
        if (temp->getVehiculo()->getPlaca() == placa) return temp->getVehiculo();
        temp = temp->getSiguiente();
    }
    return nullptr;
}

bool ListaVehiculos::actualizar(std::string placa, std::string nuevaPlaca) {
    Vehiculo* v = buscar(placa);
    if (v) { v->setPlaca(nuevaPlaca); return true; }
    return false;
}

bool ListaVehiculos::eliminar(std::string placa) {
    NodoVehiculo* actual = cabeza;
    NodoVehiculo* ant    = nullptr;
    while (actual != nullptr) {
        if (actual->getVehiculo()->getPlaca() == placa) {
            if (ant == nullptr) cabeza = actual->getSiguiente();
            else ant->setSiguiente(actual->getSiguiente());
            delete actual;
            return true;
        }
        ant    = actual;
        actual = actual->getSiguiente();
    }
    return false;
}
