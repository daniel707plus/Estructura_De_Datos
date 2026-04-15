#include "Pila.h"
#include <iostream>

template <typename T>
Pila<T>::Pila(int cap) {
    capacidad = cap;
    datos = new T[capacidad];
    tope = -1; // La pila inicia vacía
}

template <typename T>
Pila<T>::~Pila() {
    delete[] datos;
}

template <typename T>
void Pila<T>::push(T valor) {
    if (tope < capacidad - 1) {
        datos[++tope] = valor;
    }
}

template <typename T>
void Pila<T>::pop() {
    if (!estaVacia()) {
        tope--;
    }
}

template <typename T>
T Pila<T>::getTope() {
    return datos[tope];
}

template <typename T>
bool Pila<T>::estaVacia() {
    return tope == -1;
}