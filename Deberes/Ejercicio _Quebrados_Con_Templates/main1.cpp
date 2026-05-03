
#include <iostream>
#include "Quebrado.h"
#include "Proceso.h"

using namespace std;

int main() {
    float n, d;
    Quebrado<float> q1, q2, resultado; 

    cout << "--- Ingrese el primer quebrado ---" << endl;
    cout << "Numerador: ";
    cin >> n;
    q1.setNumerador(n);
    cout << "Denominador: "; 
    cin >> d;
    q1.setDenominador(d);

    cout << "\n--- Ingrese el segundo quebrado ---" << endl;
    cout << "Numerador: "; cin >> n;
    q2.setNumerador(n);
    cout << "Denominador: "; cin >> d;
    q2.setDenominador(d);

    Proceso<float> proceso;
    resultado= proceso.sumar(q1, q2);

    cout << "\n--- Resultado de la Suma ---" << endl;
    proceso.mostrar(q1);
    cout << " + ";
    proceso.mostrar(q2);
    cout << " = ";
    proceso.mostrar(resultado);
    cout << endl;

    return 0;
}