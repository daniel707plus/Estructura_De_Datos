#include "ProcesoExpresion.h"

bool ProcesoExpresion::validarParentesis(std::string expresion) {
    Pila<char> pila(expresion.length()); 
    for (char c : expresion) {
        if (c == '(') {
            pila.push(c);
        } 
        else if (c == ')') {
            if (pila.estaVacia()) return false; 
            pila.pop();
        }
        
    }

    return pila.estaVacia(); 
}