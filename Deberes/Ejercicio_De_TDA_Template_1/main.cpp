#include <iostream>
#include <string>
#include "ProcesoExpresion.h"

using namespace std;

int main(){
    // 1. Instanciamos nuestra clase de lógica
    // Nota: ProcesoExpresion no es template en sí misma, 
    // pero usa internamente el TDA Pila<char> que sí lo es.
    ProcesoExpresion motor;
    string expresion;

    cout << "=== Validador de Parentesis (Pila TDA) ===" << endl;
    cout << "Introduce una expresion matematica: ";
    getline(cin, expresion); // Usamos getline para aceptar espacios

    // 2. Llamamos a la lógica de validación
    if (motor.validarParentesis(expresion)) {
        cout << "\n[OK] La expresion esta correctamente balanceada." << endl;
    } else {
        cout << "\n[ERROR] Los parentesis estan mal cerrados o faltan." << endl;
    }

    return 0;
}