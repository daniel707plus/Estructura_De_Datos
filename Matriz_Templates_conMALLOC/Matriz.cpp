
/***********************************************************************
 * Module:  Matriz.cpp
 * Author:  JosheP Chisaguano
 * Modified: Domingo, 19 de abril de 2026 22:31:12
 * Purpose: Implementation of the class Matriz
 ***********************************************************************/

template <typename T>
Matriz<T>::Matriz(int f, int c) {
        filas = f;
        columnas = c;
        
       // m = new T*[filas]; 
        m = (T**)malloc(filas * sizeof(T*));
        
        for (int i = 0; i < filas; i++) {
            *(m + i) = (T*)malloc(columnas * sizeof(T));
            for (int j = 0; j < columnas; j++) {
                *(*(m + i) + j) = 0;
            }
        }
}

template <typename T>
Matriz<T>::Matriz(const Matriz<T>& copia) {
        filas = copia.filas;
        columnas = copia.columnas;

        //m = new T*[filas];
        m = (T**)malloc(filas * sizeof(T*));
        for (int i = 0; i < filas; i++) {
            //m[i] = new T[columnas];
            *(m + i) = (T*)malloc(columnas * sizeof(T));
            for (int j = 0; j < columnas; j++) {
                *(*(m + i) + j) = *(*(copia.m + i) + j);
            }
        }
}

template <typename T>
Matriz<T>::~Matriz() {
        liberarMemoria();
}

template <typename T>
int Matriz<T>::getFilas() const {
         return filas; 
        }

template <typename T>
int Matriz<T>::getColumnas() const {
         return columnas; 
        }

template <typename T>
void Matriz<T>:: setDato(int f, int c, T valor) {
        *(*(m + f) + c) = valor;
        
}

template <typename T>
T Matriz<T>::getDato(int f, int c) const {
        return *(*(m + f) + c);
}
