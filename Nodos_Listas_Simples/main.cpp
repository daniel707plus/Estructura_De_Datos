#include "Lista.h"
#include "ILista.h"
#include <iostream>

int main() {
    Lista* miLista = new Lista();
    ILista* gestor = new ILista(miLista);

    gestor->insertarCabeza("123", "Juan");
    gestor->insertarCabeza("456", "Maria");

    std::cout << "Cabeza actual: " <<
     miLista->getCabeza()->getNombre() << std::endl;

    delete gestor;
    delete miLista;
    return 0;
}