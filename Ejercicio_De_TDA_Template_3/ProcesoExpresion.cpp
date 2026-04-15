#include "ProcesoExpresion.h"
#include <string>

// Auxiliar para saber qué signo "manda" más
int prioridad(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

std::string ProcesoExpresion::convertirAPostfijo(std::string infijo) {
    Pila<char> pila(infijo.length());
    std::string postfijo = "";

    for (char c : infijo) {
        // 1. Si es operando (letra o número)
        if (isalnum(c)) {
            postfijo += c;
        }
        // 2. Si es paréntesis abre
        else if (c == '(') {
            pila.push(c);
        }
        // 3. Si es paréntesis cierra
        else if (c == ')') {
            while (!pila.estaVacia() && pila.getTope() != '(') {
                postfijo += pila.getTope();
                pila.pop();
            }
            pila.pop(); // Sacar el '('
        }
        // 4. Si es operador
        else {
            while (!pila.estaVacia() && prioridad(pila.getTope()) >= prioridad(c)) {
                postfijo += pila.getTope();
                pila.pop();
            }
            pila.push(c);
        }
    }

    // Vaciar lo que quede en la pila
    while (!pila.estaVacia()) {
        postfijo += pila.getTope();
        pila.pop();
    }

    return postfijo;
}