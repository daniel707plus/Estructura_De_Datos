
// --- FUNCION AUXILIAR RECURSIVA ---
template <typename T>
void multiplicacionRecursiva(const Matriz<T>& a, const Matriz<T>& b, Matriz<T>& resultado, 
                             int i, int j, int k, int x, T sumaAcumulada) {
                                 
    //Caso Base 
    if (k >= a.getProf()) {
        return; 
    }

    if (i >= a.getFilas()) {
        multiplicacionRecursiva<T>(a, b, resultado, 0, 0, k + 1, 0, 0);
        return;
    }

    if (j >= b.getColumnas()) {
        multiplicacionRecursiva<T>(a, b, resultado, i + 1, 0, k, 0, 0);
        return;
    }

    if (x >= a.getColumnas()) {
        resultado.setDato(i, j, k, sumaAcumulada);
        multiplicacionRecursiva<T>(a, b, resultado, i, j + 1, k, 0, 0);
        return;
    }

    T valorA = a.getDato(i, x, k);
    T valorB = b.getDato(x, j, k);
    sumaAcumulada += valorA * valorB;
    
    multiplicacionRecursiva<T>(a, b, resultado, i, j, k, x + 1, sumaAcumulada);
}


template <typename T>
Matriz<T> operator*(const Matriz<T>& a, const Matriz<T>& b) {

    Matriz<T> resultado(a.getFilas(), b.getColumnas(), a.getProf());

    multiplicacionRecursiva<T>(a, b, resultado, 0, 0, 0, 0, 0);

    return resultado;
}

template <typename T>
Matriz<T> operator+(const Matriz<T>& a, const Matriz<T>& b) {
    
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

template <typename T>
void Proceso::diagonal(const Matriz<T>& matriz) {
    
    for(int i = 0; i < matriz.getFilas(); i++) {
        cout << "Diagonal de la capa (Fila) " << i << ": ";
        for (int j = 0; j < matriz.getColumnas(); j++) {
            for (int k = 0; k < matriz.getProf(); k++) {
                if (j == k) { // Condición para la diagonal
                    cout << matriz.getDato(i, j, k) << " ";
                }
            }
        }
        cout << endl; 
    }
}