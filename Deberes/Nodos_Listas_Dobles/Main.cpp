#include <iostream>
#include "ListaDoble.h"
using namespace std;

int main() {
    ListaDoble lista;
    int opcion;
    string cedula, nombre;

    do {
        cout << "\n--- LISTA DOBLE ---\n";
        cout << "1. Insertar\n";
        cout << "2. Buscar\n";
        cout << "3. Eliminar\n";
        cout << "4. Imprimir\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:{
            int opc=0;
            string cedula, nombre;
            do{
                cout<<"1. Insertar al inicio\n";
                cout<<"2. Insertar al final\n";
                cout<<"3. Insertar entre\n";
                cout<<"0. Regresar\n";
                cout<<"Opcion: ";
                cin>>opc;
                if(opc==1){
                    cout << "Cedula: ";
                    cin >> cedula;
                    cout << "Nombre: ";
                    cin >> nombre;
                    lista.insertarInicio(cedula, nombre);
                }
                if(opc==2){
                    cout << "Cedula: ";
                    cin >> cedula;
                    cout << "Nombre: ";
                    cin >> nombre;
                    lista.insertarFinal(cedula, nombre);
                }
                if(opc==3){
                    string cedulaRef;
                    cout << "Cedula de referencia: ";
                    cin >> cedulaRef;
                    cout << "Nueva Cedula: ";
                    cin >> cedula;
                    cout << "Nuevo Nombre: ";
                    cin >> nombre;
                    lista.insertarEntre(cedulaRef, cedula, nombre);
                }
                if (opc == 0)
                {
                    cout << "Regresando al menu principal...\n";
                    break;
                }
                
            }while(opc != 0);              
            break;
        }

        case 2: {
            cout << "Cedula: ";
            cin >> cedula;
            Nodo* e = lista.buscar(cedula);

            if (e != nullptr)
                cout << "Encontrado: " << e->getNombre() << endl;
            else
                cout << "No encontrado\n";
            break;
        }

        case 3:
            cout << "Cedula: ";
            cin >> cedula;
            lista.eliminar(cedula);
            break;

        case 4:
            lista.imprimir();
            break;
        case 0:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo."<<endl;
            break;
        }

    } while (opcion != 0);

    return 0;
}