#include <iostream>
#include "ProcesoExpresion.h"

using namespace std;

int main() {
    ProcesoExpresion motor;
    string infijo;

    cout << "Ingresa expresion en Infijo (ej: (A+B)*C): ";
    cin >> infijo;

    string resultado = motor.convertirAPostfijo(infijo);

    cout << "Resultado en Postfijo: " << resultado << endl;

    return 0;
}