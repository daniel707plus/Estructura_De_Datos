/***********************************************************************
 * Module:  Matriz.cpp
 * Author:  Joshep Chisaguano
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class Matriz
 ***********************************************************************/

template <typename T>
Matriz<T>::Matriz(int f, int c, int p) {
    filas = f;
    columnas = c;
    prof = p;

    m = (T***)malloc(filas * sizeof(T**)); 

    for (int i = 0; i < filas; i++) {
        *(m + i) = (T**)malloc(columnas * sizeof(T*)); 

        for (int j = 0; j < columnas; j++) {
            *(*(m + i) + j) = (T*)malloc(prof * sizeof(T)); 

            for (int k = 0; k < prof; k++) {
                *(*(*(m + i) + j) + k) = 0; 
            }
        }
    }
}

// Constructor de copia
template <typename T>
Matriz<T>::Matriz(const Matriz<T>& copia) {
    filas = copia.filas;
    columnas = copia.columnas;
    prof = copia.prof;

    m = (T***)malloc(filas * sizeof(T**));
    for (int i = 0; i < filas; i++) {
        *(m + i) = (T**)malloc(columnas * sizeof(T*));
        for (int j = 0; j < columnas; j++) {
            *(*(m + i) + j) = (T*)malloc(prof * sizeof(T));
            for (int k = 0; k < prof; k++) {
                
                *(*(*(m + i) + j) + k) = *(*(*(copia.m + i) + j) + k);
            }
        }
    }
}

// Destructor
template <typename T>
Matriz<T>::~Matriz() {
    liberarMemoria();
}

// Getters basicos
template <typename T>
int Matriz<T>::getFilas() const { return filas; }

template <typename T>
int Matriz<T>::getColumnas() const { return columnas; }

template <typename T>
int Matriz<T>::getProf() const { return prof; }

// Modificar un dato
template <typename T>
void Matriz<T>::setDato(int f, int c, int p, T valor) {
    *(*(*(m + f) + c) + p) = valor;
}

// Leer un dato
template <typename T>
T Matriz<T>::getDato(int f, int c, int p) const {
    return *(*(*(m + f) + c) + p);
}