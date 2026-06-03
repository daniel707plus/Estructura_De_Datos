#include <iostream>
#include "ListaVehiculos.h"
using namespace std;

ListaVehiculos::ListaVehiculos() {
    cabeza = NULL;
    cola   = NULL;
}

// Insertar al final de la lista (solo con placa)
void ListaVehiculos::insertar(string placa) {
    // Primero revisamos si ya existe esa placa para no duplicar
    if (buscar(placa) != NULL) {
        cout << "Esa placa ya esta registrada.\n";
        return;
    }

    Vehiculo* nuevo = new Vehiculo(placa);

    if (cabeza == NULL) {
        // La lista estaba vacia, el nuevo es cabeza y cola a la vez
        cabeza = nuevo;
        cola   = nuevo;
    } else {
        // Enlazar al final
        nuevo->anterior = cola;   // el nuevo apunta hacia atras al ultimo
        cola->siguiente = nuevo;  // el ultimo apunta hacia adelante al nuevo
        cola = nuevo;             // ahora el nuevo es la cola
    }

    cout << "Vehiculo con placa " << placa << " insertado.\n";
}

Vehiculo* ListaVehiculos::buscar(string placa) {
    Vehiculo* aux = cabeza;

    while (aux != NULL) {
        if (aux->getPlaca() == placa) {
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}

void ListaVehiculos::eliminar(string placa) {
    Vehiculo* aux = buscar(placa);

    if (aux == NULL) {
        cout << "Vehiculo no encontrado.\n";
        return;
    }

    // Si tiene reserva no lo dejamos eliminar
    if (aux->estaReservado()) {
        cout << "No se puede eliminar: el vehiculo tiene una reserva activa.\n";
        return;
    }

    // Reparar los enlaces de los vecinos
    if (aux->anterior != NULL) {
        aux->anterior->siguiente = aux->siguiente;
    } else {
        // Era la cabeza
        cabeza = aux->siguiente;
    }

    if (aux->siguiente != NULL) {
        aux->siguiente->anterior = aux->anterior;
    } else {
        // Era la cola
        cola = aux->anterior;
    }

    delete aux;
    cout << "Vehiculo eliminado.\n";
}

void ListaVehiculos::imprimir() {
    if (cabeza == NULL) {
        cout << "La lista esta vacia.\n";
        return;
    }

    Vehiculo* aux = cabeza;
    int numero = 1;

    while (aux != NULL) {
        cout << "\n[" << numero << "] Placa: " << aux->getPlaca() << "\n";

        if (aux->estaReservado()) {
            Reserva r = aux->getReserva();
            cout << "    Estado  : RESERVADO\n";
            cout << "    Fecha   : " << r.getFecha().toString() << "\n";
            cout << "    Propietario  : " << r.getPersona().getNombre() << "\n";
            cout << "    Cedula  : " << r.getPersona().getCedula() << "\n";

            // Este es el mensaje principal que pediste:
            cout << "\n    >>> El vehiculo " << aux->getPlaca()
                 << " tiene la revision vehicular el "
                 << r.getFecha().toString()
                 << " y es el propietario "
                 << r.getPersona().getNombre() << ". <<<\n";
        } else {
            cout << "    Estado  : Disponible\n";
        }

        cout << "    ------------------\n";
        numero++;
        aux = aux->siguiente;
    }
}

void ListaVehiculos::reservarVehiculo(string placa, Persona p, Fecha f) {
    Vehiculo* v = buscar(placa);

    if (v == NULL) {
        cout << "Vehiculo no encontrado.\n";
        return;
    }

    // Aqui esta la parte que pediste: si ya tiene reserva, bloquear y avisar
    if (v->estaReservado()) {
        Reserva r = v->getReserva();
        cout << "\nEste vehiculo ya esta reservado!\n";
        cout << "Propietario actual : " << r.getPersona().getNombre() << "\n";
        cout << "Fecha de reserva   : " << r.getFecha().toString() << "\n";
        cout << "No se puede hacer otra reserva sobre este vehiculo.\n";
        return;
    }

    // Si la fecha cae en sabado o domingo, la movemos al lunes
    if (!f.esDiaLaborable()) {
        cout << "La fecha " << f.toString() << " cae en fin de semana.\n";
        f.ajustarADiaLaborable();
        cout << "Se ajusto automaticamente al siguiente dia laborable: "
             << f.toString() << "\n";
    }

    v->reservar(p, f);

    /*cout << "\nReserva realizada con exito!\n";
    cout << "Vehiculo  : " << placa << "\n";
    cout << "Propietario: " << p.getNombre() << "\n";
    cout << "Fecha     : " << f.toString() << "\n";
    cout << "\n>>> El vehiculo " << placa
         << " tiene la revision vehicular el "
         << f.toString()
         << " y es el propietario "
         << p.getNombre() << ". <<<\n";*/
}

void ListaVehiculos::cancelarReserva(string placa) {
    Vehiculo* v = buscar(placa);

    if (v == NULL) {
        cout << "Vehiculo no encontrado.\n";
        return;
    }

    if (!v->estaReservado()) {
        cout << "Este vehiculo no tiene ninguna reserva activa.\n";
        return;
    }

    v->liberar();
    cout << "Reserva cancelada. El vehiculo quedo disponible.\n";
}
