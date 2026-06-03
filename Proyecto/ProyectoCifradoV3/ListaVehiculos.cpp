#include "ListaVehiculos.h"
#include <iostream>
#include <cstdlib>
#include <cstdint>

NodoVehiculo::NodoVehiculo(Vehiculo* v) { vehiculo = v; siguiente = nullptr; }
NodoVehiculo::~NodoVehiculo() { delete vehiculo; }
Vehiculo* NodoVehiculo::getVehiculo() { return vehiculo; }
NodoVehiculo* NodoVehiculo::getSiguiente() { return siguiente; }
void NodoVehiculo::setSiguiente(NodoVehiculo* sig) { siguiente = sig; }

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
void ListaVehiculos::reportar() const {
    NodoVehiculo* temp = cabeza;
    if (!temp) { std::cout << "  No hay vehiculos registrados.\n"; return; }
    std::cout << "\n--- VEHICULOS REGISTRADOS ---\n";
    while (temp != nullptr) {
        std::cout << "  Placa: " << temp->getVehiculo()->getPlaca() << "\n";
        temp = temp->getSiguiente();
    }
}
Vehiculo* ListaVehiculos::buscar(std::string placa) const {
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
    NodoVehiculo* anterior = nullptr;
    while (actual != nullptr) {
        if (actual->getVehiculo()->getPlaca() == placa) {
            if (anterior == nullptr) cabeza = actual->getSiguiente();
            else anterior->setSiguiente(actual->getSiguiente());
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    }
    return false;
}
NodoVehiculo* ListaVehiculos::getCabeza() const { return cabeza; }

Vehiculo* ListaVehiculos::busquedaBinariaPorPlaca(std::string placaBuscada) const {
    if (!cabeza) return nullptr;

    // 1. Contar nodos
    int n = 0;
    for (NodoVehiculo* aux = cabeza; aux != nullptr; aux = aux->getSiguiente()) {
        n++;
    }

    // 2. Crear arreglo temporal de punteros SIN CORCHETES
    Vehiculo** arreglo = (Vehiculo**)malloc(n * sizeof(Vehiculo*));
    if (!arreglo) return nullptr;

    // 3. Llenar usando aritmética de punteros
    NodoVehiculo* actual = cabeza;
    for (int i = 0; i < n; i++) {
        *(arreglo + i) = actual->getVehiculo();
        actual = actual->getSiguiente();
    }

    // 4. ORDENAMIENTO DE BITS (XOR Swap) - Obligatorio para la Binaria
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((*(arreglo + i))->getPlaca() > (*(arreglo + j))->getPlaca()) {
                // Conversión a enteros nativos para manipular bits
                uintptr_t p1 = reinterpret_cast<uintptr_t>(*(arreglo + i));
                uintptr_t p2 = reinterpret_cast<uintptr_t>(*(arreglo + j));
                
                // Intercambio XOR triple sin 'aux'
                p1 ^= p2;
                p2 ^= p1;
                p1 ^= p2;
                
                *(arreglo + i) = reinterpret_cast<Vehiculo*>(p1);
                *(arreglo + j) = reinterpret_cast<Vehiculo*>(p2);
            }
        }
    }

    // 5. BÚSQUEDA BINARIA
    int izquierda = 0;
    int derecha = n - 1;
    Vehiculo* encontrado = nullptr;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        
        // Extracción de la placa en la posición media
        std::string placaMedio = (*(arreglo + medio))->getPlaca();

        if (placaMedio == placaBuscada) {
            encontrado = *(arreglo + medio);
            break; 
        }
        
        if (placaMedio < placaBuscada) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    // 6. Limpieza estricta de memoria RAM
    free(arreglo);

    return encontrado;
}