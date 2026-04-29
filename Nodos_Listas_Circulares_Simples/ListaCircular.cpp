#include <iostream>
#include "ListaCircular.h" 

using namespace std;

ListaCircular::ListaCircular() {
    cabeza = nullptr;
    cola = nullptr;
}

void ListaCircular::insertarInicio(string c, string n) {
    Nodo* nuevo = new Nodo(c, n);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
        cola->setSiguiente(cabeza); // <-- Regla de oro: la cola apunta a la cabeza
    } else {
        nuevo->setSiguiente(cabeza);
        cabeza = nuevo;
        cola->setSiguiente(cabeza); // <-- Mantenemos el círculo cerrado
    }
    cout << "Insertado al inicio: " << n << endl;
}

void ListaCircular::insertarFinal(string c, string n) {
    Nodo* nuevo = new Nodo(c, n);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
        cola->setSiguiente(cabeza);
    } else {
        cola->setSiguiente(nuevo);
        cola = nuevo;
        cola->setSiguiente(cabeza); // <-- Mantenemos el círculo cerrado
    }
    cout << "Insertado al final: " << n << endl;
}

void ListaCircular::insertarEntre(string cedulaRef, string c, string n) {
    if (cabeza == nullptr) {
        cout << "Error: La lista esta vacia." << endl;
        return;
    }

    Nodo* actual = cabeza;
    bool encontrado = false;

    // Usamos do-while para dar exactamente una vuelta al círculo
    do {
        if (actual->getCedula() == cedulaRef) {
            encontrado = true;
            break;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    if (encontrado) {
        Nodo* nuevo = new Nodo(c, n);
        nuevo->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(nuevo);
        
        // Si lo insertamos justo después de la cola, el nuevo pasa a ser la cola
        if (actual == cola) {
            cola = nuevo;
            // No necesitamos conectar a la cabeza
             //aquí porque nuevo->setSiguiente ya agarró.
            // el antiguo siguiente de la cola, que
             //ERA la cabeza. ¡Magia de la lista circular!
        }
        cout << "Insertado entre nodos: " << n << endl;
    } else {
        cout << "Error: No se encontro la cedula (" << cedulaRef << ")" << endl;
    }
}

void ListaCircular::eliminar(string c) {
    if (cabeza == nullptr) {
        cout << "Error: Lista vacia." << endl;
        return;
    }

    Nodo* actual = cabeza;
    Nodo* previo = cola; // ¡OJO A ESTO! En una lista circular,
     //el nodo anterior a la cabeza es la cola
    bool encontrado = false;

    do {
        if (actual->getCedula() == c) {
            encontrado = true;
            break;
        }
        previo = actual;
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    if (encontrado) {
        // Caso 1: Hay un solo nodo en toda la lista
        if (actual == cabeza && actual == cola) {
            cabeza = nullptr;
            cola = nullptr;
        } 
        // Caso 2: Vamos a borrar la cabeza
        else if (actual == cabeza) {
            cabeza = cabeza->getSiguiente();
            cola->setSiguiente(cabeza); // Cerramos el círculo con la nueva cabeza
        } 
        // Caso 3: Vamos a borrar la cola
        else if (actual == cola) {
            previo->setSiguiente(cabeza);
            cola = previo; // La cola retrocede
        } 
        // Caso 4: Vamos a borrar un nodo en el medio
        else {
            previo->setSiguiente(actual->getSiguiente());
        }
        
        delete actual;
        cout << "Nodo con cedula " << c << " eliminado." << endl;
    } else {
        cout << "Error: No se encontro la cedula para eliminar." << endl;
    }
}

Nodo* ListaCircular::buscar(string c) {
    if (cabeza == nullptr) return nullptr;

    Nodo* actual = cabeza;
    do {
        if (actual->getCedula() == c) {
            return actual;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    return nullptr;
}

void ListaCircular::imprimir() {
    if (cabeza == nullptr) {
        cout << "\nLa lista esta vacia." << endl;
        return;
    }

    Nodo* actual = cabeza;
    cout << "\n--- Estado actual de la lista Circular ---" << endl;
    
    // Imprimimos la primera vuelta
    do {
        cout << "[" << actual->getCedula() << " - " << actual->getNombre() << "] -> ";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    
    // Mostramos visualmente que vuelve a conectar con la cabeza
    cout << "(Vuelve a la cabeza: " << cabeza->getCedula() << ")\n" << endl;
}

int ListaCircular::contarTerminanEn39() {
    if (cabeza == nullptr) return 0; // Regla 1 en pruebas: siempre validar si está vacía
    
    int contador = 0;
    Nodo* actual = cabeza;
    
    do {
        string c = actual->getCedula();
        // Verificamos que la cédula tenga al menos 2 caracteres y que los últimos dos sean "39"
        if (c.length() >= 2 && c.substr(c.length() - 2) == "39") {
            contador++;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);
    
    return contador;
}