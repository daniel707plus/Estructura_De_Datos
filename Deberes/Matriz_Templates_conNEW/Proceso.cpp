/***********************************************************************
 * Module:  Proceso.cpp
 * Author:  USUARIO
 * Modified: sabado, 2 de mayo de 2026 19:32:32
 * Purpose: Implementation of the class Proceso
 ***********************************************************************/
template <typename T>
Matriz<T> operator+(const Matriz<T>& a, const Matriz<T>& b) {

    Matriz<T> resultado(a.getFilas(), a.getColumnas());

    for (int i = 0; i < a.getFilas(); i++) {
        for (int j = 0; j < a.getColumnas(); j++) {
            // Sumamos usando el tipo T
            T suma = a.getDato(i, j) + b.getDato(i, j);
            resultado.setDato(i, j, suma);
        }
    }
    return resultado;
}
    
template <typename T>
void Proceso::pedirDatosMatriz(Matriz<T>& matriz, int numeroMatriz) {
        cout << "\n--- Matriz " << numeroMatriz << " ---" << endl;
        for (int i = 0; i < matriz.getFilas(); i++) {
            for (int j = 0; j < matriz.getColumnas(); j++) {
                T valor; 
                cout << "Ingrese valor para posicion [" << i << "][" << j << "]: ";
                cin >> valor;
                matriz.setDato(i, j, valor);
            }
        }
    }

template <typename T>
void Proceso::mostrarMatriz(const Matriz<T>& matriz) {
        for (int i = 0; i < matriz.getFilas(); i++) {
            for (int j = 0; j < matriz.getColumnas(); j++) {
                cout << matriz.getDato(i, j) << "\t";
            }
            cout << endl;
        }
    }

