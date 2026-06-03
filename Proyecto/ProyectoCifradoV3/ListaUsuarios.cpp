#include "ListaUsuarios.h"
#include <iostream>
#include <cstdlib> // Obligatorio para malloc y free
#include <cstdint> // Obligatorio para uintptr_t


NodoUsuario::NodoUsuario(Usuario* u) { usuario = u; siguiente = nullptr; }
NodoUsuario::~NodoUsuario() { delete usuario; }
Usuario* NodoUsuario::getUsuario() { return usuario; }
NodoUsuario* NodoUsuario::getSiguiente() { return siguiente; }
void NodoUsuario::setSiguiente(NodoUsuario* sig) { siguiente = sig; }

ListaUsuarios::ListaUsuarios() { cabeza = nullptr; }
ListaUsuarios::~ListaUsuarios() {
    NodoUsuario* actual = cabeza;
    while (actual != nullptr) {
        NodoUsuario* borrar = actual;
        actual = actual->getSiguiente();
        delete borrar;
    }
}
void ListaUsuarios::crear(Usuario* u) {
    NodoUsuario* nuevo = new NodoUsuario(u);
    nuevo->setSiguiente(cabeza);
    cabeza = nuevo;
}
void ListaUsuarios::reportar() const {
    NodoUsuario* temp = cabeza;
    if (!temp) { std::cout << "  No hay usuarios registrados.\n"; return; }
    std::cout << "\n--- USUARIOS REGISTRADOS ---\n";
    while (temp != nullptr) {
        std::cout << "  CI: " << temp->getUsuario()->getCedula()
                  << " | " << temp->getUsuario()->getNombre()
                  << " " << temp->getUsuario()->getApellido() << "\n";
        temp = temp->getSiguiente();
    }
}
Usuario* ListaUsuarios::buscar(std::string cedula) const {
    NodoUsuario* temp = cabeza;
    while (temp != nullptr) {
        if (temp->getUsuario()->getCedula() == cedula) return temp->getUsuario();
        temp = temp->getSiguiente();
    }
    return nullptr;
}
bool ListaUsuarios::actualizar(std::string cedula, std::string nuevoNom, std::string nuevoApe) {
    Usuario* u = buscar(cedula);
    if (u) { u->setNombre(nuevoNom); u->setApellido(nuevoApe); return true; }
    return false;
}
bool ListaUsuarios::eliminar(std::string cedula) {
    NodoUsuario* actual = cabeza;
    NodoUsuario* anterior = nullptr;
    while (actual != nullptr) {
        if (actual->getUsuario()->getCedula() == cedula) {
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
NodoUsuario* ListaUsuarios::getCabeza() const { return cabeza; }

Usuario* ListaUsuarios::busquedaBinariaPorCedula(std::string cedulaBuscada) const {
    if (!cabeza) return nullptr;

    // 1. Contar los nodos (Aritmética básica de punteros)
    int n = 0;
    for (NodoUsuario* aux = cabeza; aux != nullptr; aux = aux->getSiguiente()) {
        n++;
    }

    // 2. Crear el arreglo temporal SIN CORCHETES (Asignación a nivel de C puro)
    Usuario** arreglo = (Usuario**)malloc(n * sizeof(Usuario*));
    if (!arreglo) return nullptr; // Seguridad de memoria

    // 3. Llenar el arreglo usando aritmética de punteros pura
    NodoUsuario* actual = cabeza;
    for (int i = 0; i < n; i++) {
        *(arreglo + i) = actual->getUsuario();
        actual = actual->getSiguiente();
    }

    // 4. ORDENAMIENTO INTERNO DEL ARREGLO POR BITS (Obligatorio para que la Binaria funcione)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // Comparamos las cédulas
            if ((*(arreglo + i))->getCedula() > (*(arreglo + j))->getCedula()) {
                // Intercambio XOR sin variables auxiliares (pura manipulación de bits)
                uintptr_t p1 = reinterpret_cast<uintptr_t>(*(arreglo + i));
                uintptr_t p2 = reinterpret_cast<uintptr_t>(*(arreglo + j));
                
                p1 ^= p2;
                p2 ^= p1;
                p1 ^= p2;
                
                *(arreglo + i) = reinterpret_cast<Usuario*>(p1);
                *(arreglo + j) = reinterpret_cast<Usuario*>(p2);
            }
        }
    }

    // 5. BÚSQUEDA BINARIA SIN CORCHETES
    int izquierda = 0;
    int derecha = n - 1;
    Usuario* encontrado = nullptr;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        
        // Extracción del valor medio usando aritmética
        std::string cedMedio = (*(arreglo + medio))->getCedula();

        if (cedMedio == cedulaBuscada) {
            encontrado = *(arreglo + medio);
            break; 
        }
        
        if (cedMedio < cedulaBuscada) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    // 6. Liberar la memoria temporal estrictamente
    free(arreglo);

    return encontrado;
}