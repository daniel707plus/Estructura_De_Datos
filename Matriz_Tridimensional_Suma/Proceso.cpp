
template <typename T>
Matriz<T> operator+(const Matriz<T>& a, const Matriz<T>& b) {
    
    // Creamos la matriz C que guardara el resultado
    Matriz<T> resultado(a.getFilas(), a.getColumnas(), a.getProf());

    for (int i = 0; i < a.getFilas(); i++) {
        for (int j = 0; j < a.getColumnas(); j++) {
            for (int k = 0; k < a.getProf(); k++) {
                T suma = a.getDato(i, j, k) + b.getDato(i, j, k);
                resultado.setDato(i, j, k, suma);
            }
        }
    }
    return resultado;
}

// --- Ingresar Datos ---
template <typename T>
void Proceso::ingresar(Matriz<T>& matriz, const char* nombreMatriz) {
    cout << "\n--- Llenando Matriz " << nombreMatriz << " ---" << endl;
    for (int i = 0; i < matriz.getFilas(); i++) {
        for (int j = 0; j < matriz.getColumnas(); j++) {
            for (int k = 0; k < matriz.getProf(); k++) {
                T valor;
                cout << "Ingrese [" << i << "][" << j << "][" << k << "]: ";
                cin >> valor;
                matriz.setDato(i, j, k, valor);
            }
        }
    }
}

template <typename T>
void Proceso::imprimir(const Matriz<T>& matriz, const char* nombreMatriz) {
    cout << "\n--- Matriz " << nombreMatriz << " ---" << endl;
    for (int i = 0; i < matriz.getFilas(); i++) {
        cout << "Capa (Fila) " << i << ":" << endl;
        for (int j = 0; j < matriz.getColumnas(); j++) {
            for (int k = 0; k < matriz.getProf(); k++) {
                cout << matriz.getDato(i, j, k) << " ";
            }
            cout << endl; // Salto por columna
        }
        cout << endl; // Salto visual entre capas
    }
}