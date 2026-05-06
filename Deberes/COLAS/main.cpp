#include <iostream>
#include <string>
#include "Cola.h"

using namespace std;

int main() {
    IOPERACION_COLAS* miCola = new Cola();
    int opcion;
    do{
        cout<<"Menu:\n";
        cout<<"1. ingresar persona\n";
        cout<<"2. Desencolar persona\n";
        cout<<"3. Buscar persona\n";
        cout<<"4. Imprimir cola\n";
        cout<<"5. Salir\n";
        cout<<"Seleccione una opcion: ";
        cin>>opcion;
        switch (opcion)
        {
        case 1:{
            string cedula, nombre;
            cout<<"Ingrese la cedula de la persona: ";  
            cin>>cedula;
            cout<<"Ingrese el nombre de la persona: ";
            cin>>nombre;
            miCola->encolar(Persona(cedula, nombre));
            break;
        }
        case 2:{
            
            cout<<"Lista de personas en la cola:\n";
            miCola->imprimir();
            cout<<"Atendiendo a la persona en el frente de la cola...\n";
            Persona personaAtendida = miCola->desencolar();
            cout<<"Se atendio a: "<<personaAtendida.getNombre()<<"\n";
            break;
        }
        case 3:{
            string cedulaBuscar;
            cout<<"Ingrese la cedula a buscar: ";
            cin>>cedulaBuscar;
            if(miCola->buscar(cedulaBuscar)){
                cout<<"La persona con cedula "<<cedulaBuscar
                <<" se encuentra en la cola.\n";
            } else {
                cout<<"La persona con cedula "<<cedulaBuscar
                <<" no se encuentra en la cola.\n";
            }
            break;
        }
        case 4:
            cout<<"Estado actual de la cola:\n";
            miCola->imprimir();
            break;
        case 5:
            cout<<"Saliendo del programa...\n";
            break;
        
        default:
        cout<<"Opcion no valida, intente de nuevo.\n";
            break;
        }
    }while(opcion != 5);

    delete miCola;

    return 0;
}