#include <iostream>
#include "ListaVehiculos.h"
using namespace std;

int main() {
    ListaVehiculos lista;
    int op;

    cout << "-------------------------------------\n";
    cout << "=== Sistema de Revision Vehicular ===\n";
    cout << "-------------------------------------\n";

    do {
        cout << "\n1. Insertar vehiculo\n";
        cout << "2. Eliminar vehiculo\n";
        cout << "3. Buscar vehiculo\n";
        cout << "4. Ver todos los vehiculos\n";
        cout << "5. Reservar vehiculo (revision vehicular)\n";
        cout << "6. Cancelar reserva\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        // --- INSERTAR ---
        if (op == 1) {
            string placa;
            cout << "Placa del vehiculo: ";
            cin >> placa;
            lista.insertar(placa);
        }

        // --- ELIMINAR ---
        if (op == 2) {
            string placa;
            cout << "Placa a eliminar: ";
            cin >> placa;
            lista.eliminar(placa);
        }

        // --- BUSCAR ---
        if (op == 3) {
            string placa;
            cout << "Placa a buscar: ";
            cin >> placa;

            Vehiculo* v = lista.buscar(placa);

            if (v != NULL) {
                cout << "Vehiculo encontrado: " << v->getPlaca() << "\n";

                if (v->estaReservado()) {
                    Reserva r = v->getReserva();
                    cout << "Estado: RESERVADO\n";
                    cout << "Fecha : " << r.getFecha().toString() << "\n";
                    cout << "Duenio: " << r.getPersona().getNombre() << "\n";
                    cout << "\n>>> El vehiculo " << v->getPlaca()
                         << " tiene la revision vehicular el "
                         << r.getFecha().toString()
                         << " y es el propietario "
                         << r.getPersona().getNombre() << ". <<<\n";
                } else {
                    cout << "Estado: Disponible\n";
                }
            } else {
                cout << "No existe ese vehiculo.\n";
            }
        }

        // --- IMPRIMIR LISTA ---
        if (op == 4) {
            lista.imprimir();
        }

        // --- RESERVAR ---
        if (op == 5) {
            string placa, cedula, nombre;

            cout << "Placa del vehiculo a reservar: ";
            cin >> placa;
            cout << "Cedula del propietario: ";
            cin >> cedula;
            cout << "Nombre del propietario: ";
            cin.ignore();          // limpiar el buffer antes de getline
            getline(cin, nombre);  // para que acepte nombres con espacio

            Fecha fecha = leerFecha();

            Persona p(cedula, nombre);
            lista.reservarVehiculo(placa, p, fecha);
        }

        // --- CANCELAR RESERVA ---
        if (op == 6) {
            string placa;
            cout << "Placa del vehiculo: ";
            cin >> placa;
            lista.cancelarReserva(placa);
        }

    } while (op != 0);

    cout << "Hasta luego.\n";
    return 0;
}
