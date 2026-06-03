#include "ListaUsuarios.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// ── Nodo ──────────────────────────────────────────────────────
NodoUsuario::NodoUsuario(Usuario* u) { usuario = u; siguiente = nullptr; }
NodoUsuario::~NodoUsuario()          { delete usuario; }
Usuario*     NodoUsuario::getUsuario()              { return usuario; }
NodoUsuario* NodoUsuario::getSiguiente()            { return siguiente; }
void         NodoUsuario::setSiguiente(NodoUsuario* s){ siguiente = s; }

// ── Lista ─────────────────────────────────────────────────────
ListaUsuarios::ListaUsuarios() { cabeza = nullptr; }
ListaUsuarios::~ListaUsuarios() {
    NodoUsuario* a = cabeza;
    while (a) { NodoUsuario* b = a; a = a->getSiguiente(); delete b; }
}

void ListaUsuarios::crear(Usuario* u) {
    NodoUsuario* nuevo = new NodoUsuario(u);
    nuevo->setSiguiente(cabeza);
    cabeza = nuevo;
}

// ── imprimir (igual al original, usada por la animacion) ──────
void ListaUsuarios::imprimir() const {
    NodoUsuario* tmp = cabeza;
    int pos = 1;
    while (tmp != nullptr) {
        cout << "  [" << pos << "] "
             << tmp->getUsuario()->getApellido()
             << ", "  << tmp->getUsuario()->getNombre()
             << "  (CI: " << tmp->getUsuario()->getCedula() << ")\n";
        tmp = tmp->getSiguiente();
        pos++;
    }
}

void ListaUsuarios::reportar() const {
    NodoUsuario* tmp = cabeza;
    if (!tmp) { cout << "  No hay usuarios registrados.\n"; return; }
    cout << "\n--- USUARIOS REGISTRADOS ---\n";
    imprimir();
}

// ── buscar ────────────────────────────────────────────────────
Usuario* ListaUsuarios::buscar(string cedula) const {
    NodoUsuario* tmp = cabeza;
    while (tmp) {
        if (tmp->getUsuario()->getCedula() == cedula) return tmp->getUsuario();
        tmp = tmp->getSiguiente();
    }
    return nullptr;
}

// ── buscarConExcepcion (try/catch) ────────────────────────────
Usuario* ListaUsuarios::buscarConExcepcion(string cedula) const {
    try {
        NodoUsuario* tmp = cabeza;
        while (tmp) {
            if (tmp->getUsuario()->getCedula() == cedula)
                return tmp->getUsuario();
            tmp = tmp->getSiguiente();
        }
        throw runtime_error("Usuario con CI [" + cedula + "] no encontrado en el sistema.");
    } catch (const runtime_error& e) {
        cout << "\n  [EXCEPCION CAPTURADA] " << e.what() << "\n";
        return nullptr;
    }
}

bool ListaUsuarios::actualizar(string cedula, string nuevoNom, string nuevoApe) {
    Usuario* u = buscar(cedula);
    if (u) {
        u->setNombre(nuevoNom);
        u->setApellido(nuevoApe);
        return true;
    }
    return false;
}

bool ListaUsuarios::eliminar(string cedula) {
    NodoUsuario* actual   = cabeza;
    NodoUsuario* anterior = nullptr;
    while (actual) {
        if (actual->getUsuario()->getCedula() == cedula) {
            if (!anterior) cabeza = actual->getSiguiente();
            else anterior->setSiguiente(actual->getSiguiente());
            delete actual;
            return true;
        }
        anterior = actual;
        actual   = actual->getSiguiente();
    }
    return false;
}

NodoUsuario* ListaUsuarios::getCabeza() const { return cabeza; }

// ============================================================
//  ORDENAMIENTO POR INTERCAMBIO  (animacion exacta pedida)
// ============================================================
void ListaUsuarios::ordenamientoIntercambio() {
    if (cabeza == nullptr || cabeza->getSiguiente() == nullptr) {
        return;
    }

    bool intercambiado;
    NodoUsuario* actual;
    NodoUsuario* ultimoLeido = nullptr;
    int paso = 1;

    do {
        intercambiado = false;
        actual = cabeza;

        while (actual->getSiguiente() != ultimoLeido) {
            Usuario* uA = actual->getUsuario();
            Usuario* uB = actual->getSiguiente()->getUsuario();

            if (uA->getApellido() > uB->getApellido()) {

                // ── Intercambio de datos ──
                string tempCedula   = uA->getCedula();
                string tempNombre   = uA->getNombre();
                string tempApellido = uA->getApellido();

                string cB = uB->getCedula();
                string nB = uB->getNombre();
                string aB = uB->getApellido();
                uA->setCedula(cB);
                uA->setNombre(nB);
                uA->setApellido(aB);

                uB->setCedula(tempCedula);
                uB->setNombre(tempNombre);
                uB->setApellido(tempApellido);

                intercambiado = true;

                // ── Animacion en vivo (exacta como el original) ──
                system("cls");
                cout << "==========================================================================" << endl;
                cout << "               ANIMACION EN VIVO: PASO DE ORDENAMIENTO #" << paso << endl;
                cout << "==========================================================================" << endl;
                imprimir();
                paso++;
                this_thread::sleep_for(chrono::milliseconds(800));
            }

            actual = actual->getSiguiente();
        }
        ultimoLeido = actual;

    } while (intercambiado);

    system("cls");
    cout << "==========================================================================" << endl;
    cout << "                    LISTA ORDENADA COMPLETAMENTE                          " << endl;
    cout << "==========================================================================" << endl;
    imprimir();
}
