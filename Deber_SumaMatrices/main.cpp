#include <iostream>
#include "Proceso.h"
#include "Matriz.h"

using namespace std;

int main() {
    int f, c;
    cout << "filas: ";
    cin >> f;
    cout << "Columnas: ";
    cin >> c;

    Matriz m1(f, c);
    Matriz m2(f, c);

    Proceso proceso;

    proceso.pedirDatosMatriz(m1, 1);
    proceso.pedirDatosMatriz(m2, 2);

    cout << "\n--- Matriz 1 ---" << endl;
    proceso.mostrarMatriz(m1);

    cout << "\n--- Matriz 2 ---" << endl;
    proceso.mostrarMatriz(m2);

    Matriz matrizSuma = m1 + m2;

    cout << "\n--- Resultado de la Suma ---" << endl;
    proceso.mostrarMatriz(matrizSuma);

    return 0;
}