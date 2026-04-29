#include "Proceso.h"

int main() {
    int fila = 2, col = 2, prof = 2;
    Proceso herramienta;

    Matriz<float> a(fila, col, prof);
    Matriz<float> b(fila, col, prof);
    
    herramienta.ingresar(a, "A");
    herramienta.ingresar(b, "B");

    herramienta.imprimir(a, "A");
    herramienta.imprimir(b, "B");

    Matriz<float> c = a + b; 
    
    herramienta.imprimir(c, "RESULTADO (A + B)");

    return 0;
}