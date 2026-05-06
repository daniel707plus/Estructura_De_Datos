#include <iostream>
#include "Pila.h"

int main() {
    // Usamos el polimorfismo llamando a la interfaz
    IOPERACION_PILAS_GRUPO2* miPila = new Pila(); 

    std::cout << "Insertando datos...\n";
    miPila->insertar(Persona("111", "Ana"));
    miPila->insertar(Persona("222", "Beto"));
    miPila->insertar(Persona("333", "Carlos")); // Esta será la cima

    miPila->imprimir();

    std::string buscarCed = "222";
    std::cout << "\nBuscando cedula " << buscarCed << "...\n";
    if (miPila->buscar(buscarCed)) {
        std::cout << "-> Resultado: Persona encontrada.\n";
    } else {
        std::cout << "-> Resultado: Persona NO encontrada.\n";
    }

    std::cout << "\nEliminando el elemento de la cima (Pop)...\n";
    Persona eliminada = miPila->eliminar();
    std::cout << "Se elimino a: " << eliminada.getNombre() << "\n\n";

    miPila->imprimir();

    delete miPila; // Fundamental para llamar al destructor y evitar memory leaks
    return 0;
}