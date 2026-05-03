#include <iostream>
#include "ListaCircular.h"
using namespace std;

int main() {
    ListaCircular lista; 
    int opcion;
    string cedula, nombre, cedulaRef;

    do {
        cout << "\n--- LISTA CIRCULAR ---\n";
        cout << "1. Insertar al inicio\n";
        cout << "2. Buscar\n";
        cout << "3. Eliminar\n";
        cout << "4. Imprimir\n";
        cout << "5. Insertar entre nodos\n";
        cout << "6. Insertar al final\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Cedula: ";
            cin >> cedula;
            cout << "Nombre: ";
            cin >> nombre;
            lista.insertarInicio(cedula, nombre);
            break;

        case 2: {
            cout << "Cedula a buscar: ";
            cin >> cedula;
            Nodo* e = lista.buscar(cedula);

            if (e != nullptr)
                cout << "Encontrado: " << e->getNombre() << endl;
            else
                cout << "No encontrado\n";
            break;
        }

        case 3:
            cout << "Cedula a eliminar: ";
            cin >> cedula;
            lista.eliminar(cedula);
            break;

        case 4:
            lista.imprimir();
            break;

        case 5:
            cout << "Cedula de REFERENCIA (antes del nuevo): ";
            cin >> cedulaRef;
            cout << "NUEVA cedula: ";
            cin >> cedula;
            cout << "NUEVO nombre: ";
            cin >> nombre;
            lista.insertarEntre(cedulaRef, cedula, nombre); 
            break;
        case 6:
            cout << "Cedula: ";
            cin >> cedula;
            cout << "Nombre: ";
            cin >> nombre;
            lista.insertarFinal(cedula, nombre);
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
            
        default:
            cout << "Opcion invalida." << endl;
            break;
        }

    } while (opcion != 0);

    return 0;
}