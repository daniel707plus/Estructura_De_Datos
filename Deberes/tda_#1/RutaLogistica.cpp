// RutaLogistica.cpp
#include <iostream>
#include "RutaLogistica.h"

using namespace std;

RutaLogistica::RutaLogistica() {
    cabeza = nullptr;
}

RutaLogistica::~RutaLogistica() {
    NodoEnvio* actual = cabeza;
    while (actual != nullptr) {
        NodoEnvio* temp = actual->getSiguiente();
        delete actual; // Llama en cascada al destructor de NodoEnvio
        actual = temp;
    }
}

void RutaLogistica::agregarPaquete(string codigo, string destino) {
    // 1. Instanciamos el objeto independiente
    Paquete* nuevoPaquete = new Paquete(codigo, destino);
    // 2. Lo guardamos en el nodo
    NodoEnvio* nuevoNodo = new NodoEnvio(nuevoPaquete);

    // Inserción simple al final de la ruta
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        NodoEnvio* actual = cabeza;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevoNodo);
    }
}

void RutaLogistica::auditarRutaExpress() const {
    NodoEnvio* actual = cabeza;
    if (actual == nullptr) {
        cout << "La ruta de envios esta vacia." << endl;
        return;
    }

    // =================================================================
    // LAMBDA: Detector de envíos Express usando PUNTEROS PUROS
    // Determina si el código termina exactamente en "EXP"
    // =================================================================
    auto esEnvioExpress = [](string codigo) -> bool {
        const char* ptr = codigo.c_str();
        int longitud = 0;
        
        // 1. Avanzar el puntero hasta el final para saber el tamaño
        while (*(ptr + longitud) != '\0') {
            longitud++;
        }
        
        // Si el código es muy corto, es imposible que termine en EXP
        if (longitud < 3) return false;
        
        // 2. Retroceder 3 espacios desde el final y revisar carácter por carácter
        const char* ptrFinal = ptr + (longitud - 3);
        
        bool e = (*ptrFinal == 'E' || *ptrFinal == 'e');
        bool x = (*(ptrFinal + 1) == 'X' || *(ptrFinal + 1) == 'x');
        bool p = (*(ptrFinal + 2) == 'P' || *(ptrFinal + 2) == 'p');
        
        return (e && x && p);
    };
    // =================================================================

    cout << "\n--- AUDITORIA DE RUTA DE ENTREGAS ---" << endl;
    int contadorExpress = 0;

    while (actual != nullptr) {
        // Doble indirección limpia: actual -> paquete -> atributos
        string cod = actual->getPaquete()->getCodigoRastreo();
        string dest = actual->getPaquete()->getCiudadDestino();

        cout << "Destino: " << dest << " \t| Rastreo: " << cod;

        // Evaluamos usando la lambda
        if (esEnvioExpress(cod)) {
            cout << "  [ALERTA: Prioridad EXPRESS, enrutar primero!]";
            contadorExpress++;
        }
        cout << endl;

        actual = actual->getSiguiente();
    }
    cout << "---------------------------------------" << endl;
    cout << "Total de paquetes Express en la ruta: " << contadorExpress << endl;
}