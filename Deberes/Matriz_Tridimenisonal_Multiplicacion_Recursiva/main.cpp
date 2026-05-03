#include <iostream>
#include "Proceso.h" 

using namespace std;

int main() {
    int filasA = 2, colA = 3, prof = 2;
    int filasB = 3, colB = 2; 

    Proceso herramienta;

    Matriz<int> a(filasA, colA, prof);
    Matriz<int> b(filasB, colB, prof);

    cout << "--- INGRESANDO DATOS MATRIZ A ---" << endl;
    herramienta.ingresar(a, "A");
    
    cout << "\n--- INGRESANDO DATOS MATRIZ B ---" << endl;
    herramienta.ingresar(b, "B");

    cout << "\n=========================================" << endl;
    cout << "           MATRICES ORIGINALES           " << endl;
    cout << "=========================================" << endl;
    herramienta.imprimir(a, "A");
    herramienta.imprimir(b, "B");

    Matriz<int> c = a * b;

    cout << "\n=========================================" << endl;
    cout << "           RESULTADO DE A * B            " << endl;
    cout << "=========================================" << endl;
    herramienta.imprimir(c, "C (Resultado Multiplicacion)");

    cout<< "DIAGONAL"<< endl;
    herramienta.diagonal(c);

    return 0; 
}